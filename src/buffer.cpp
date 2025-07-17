#pragma once

// definizioni di macro
#define ret return
#define ResetAttribute() SetConsoleTextAttribute(hConsole, 15)
#define _GetCursorPos() GetConsoleScreenBufferInfo(hConsole, &csbi)

// inclusioni
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include "../include/buffer.h"
#include "../include/tensor.h"
using namespace std;
using _TENSOR tensor;

#pragma region Console

void Console::log() const
{
	SetConsoleTextAttribute(hConsole, Attribute);
	wcout << Text;
	ResetAttribute();
}

bool Console::operator!=(const Console& other) const
{
	ret Text != other.Text or Attribute != other.Attribute;
}
wostream& operator<<(wostream& wos, const Console& T)
{
	SetConsoleTextAttribute(hConsole, T.Attribute);
	wos << T.Text;
	ResetAttribute();
	ret wos;
}

#pragma endregion

#pragma region ConsoleStream

ConsoleStream ConsoleText;

// costruttori e operatori
ConsoleStream::ConsoleStream() {}
ConsoleStream::ConsoleStream(initializer_list<Console> init)
{
	for (const auto& item : init)
	{
		(*this) << item;
	}
}
ConsoleStream ConsoleStream::operator+(ConsoleStream other) const
{
	auto This{ *this };
	for (const auto& item : other)
	{
		This << item;
	}
	ret This;
}

// output
wostream& operator<<(wostream& wos, const ConsoleStream& T)
{
	for (int i = 0; i < T.size(); ++i)
	{
		wos << T[i];
	}
	ret wos;
}

#pragma endregion

#pragma region Buffer

// ridimensionamento
void Buffer::UpdateSize()
{
	// cursore nella finestra di scrittura
	if (CursorPosition.X < SizeLimit)
	{
		ret;
	}

	// spostamento a capo
	CursorPosition.X = 0;
	CursorPosition.Y++;

	// cursore sempre all'interno della finestra
	if (CursorPosition.Y < WindowHeight)
	{
		ret;
	}

	// slittamento della finestra
	WindowStep++;

	// finestra contenuta nel buffer
	if (WindowStep + WindowHeight <= memory.size())
	{
		ret;
	}

	// aggiunta di memoria nel buffer
	memory(memory.size() + 20, tensor<wchar_t>(SizeLimit, L'\0'));
	attributes(attributes.size() + 20, tensor<WORD>(SizeLimit, 15));
}

// costruttore
Buffer::Buffer() :
	held(),
	WindowStep(0),
	CurrentAttribute(15),
	CursorPosition(COORD{ 0, 0 }),
	memory(tensor<tensor<wchar_t>>(40, tensor<wchar_t>(SizeLimit, L'\0'))),
	attributes(tensor<tensor<WORD>>(40, tensor<WORD>(SizeLimit, 15)))
{}

// distruttore
void Buffer::reset()
{
	held.clear();
	memory = tensor<tensor<wchar_t>>(
		WindowHeight, tensor<wchar_t>(SizeLimit, L'\0')
	);
	attributes =
		tensor<tensor<WORD>>(WindowHeight, tensor<WORD>(SizeLimit, 15));
	CursorPosition = COORD{ 0, 0 };
	CurrentAttribute = 15;
	WindowStep = 0;
}

// assegnazione
void Buffer::operator=(const Buffer& other)
{
	if (this == &other)
	{
		ret;
	}

	held = other.held;
	memory = other.memory;
	attributes = other.attributes;
	WindowStep = other.WindowStep;
	CursorPosition = other.CursorPosition;
	CurrentAttribute = other.CurrentAttribute;
}

// uguaglianze e disuguaglianze
bool Buffer::AbsolutelyEqual(const Buffer& other) const
{
	ret held == other.held and
		memory == other.memory and
		attributes == other.attributes and
		CursorPosition.X == other.CursorPosition.X and
		CursorPosition.Y == other.CursorPosition.Y and
		CurrentAttribute == other.CurrentAttribute and
		WindowStep == other.WindowStep;
}
bool Buffer::operator==(const Buffer& other) const
{
	ret held == other.held and
		memory == other.memory and
		attributes == other.attributes;
}
bool Buffer::operator!=(const Buffer& other) const
{
	ret !(*this == other);
}

// cambio attributo della console
void Buffer::SetBufferTextAttribute(WORD attribute)
{
	CurrentAttribute = attribute;
}

// riposizionamento cursore
void Buffer::SetBufferCursorPosition(COORD position)
{
	if (position.X < 0 or position.Y < 0)
	{
		ret;
	}
	if (position.X >= SizeLimit or position.Y >= WindowHeight)
	{
		ret;
	}
	CursorPosition = position;
}

// ottenimento di informazioni specifiche
void Buffer::GetBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO info) const
{
	info->dwMaximumWindowSize = COORD{ SizeLimit, (short)WindowHeight };
	info->dwSize = COORD{ SizeLimit, (short)WindowHeight };
	info->wAttributes = CurrentAttribute;
	info->srWindow = SMALL_RECT{
		0, 0, static_cast<short>(SizeLimit - 1),
		static_cast<short>(WindowHeight - 1)
	};
	info->dwCursorPosition = CursorPosition;
}

// applicazione delle funzioni
Buffer& Buffer::operator<<(Funct function)
{
	held << function;
	ret *this;
}

// scrittura di un Console
Buffer& Buffer::operator<<(const Console& text)
{
	SetBufferTextAttribute(text.Attribute);
	*this << text.Text;
	SetBufferTextAttribute(15);
	ret* this;
}

// scrittura del buffer intero
void Buffer::output() const
{
	// inizio
	ResetAttribute();
	WORD Attrib{ 15 };
	short CharsSkipped{};

	// scrittura
	for (size_t i = 0; i < memory; ++i)
	{
		// aggiunta di altro spazio nella console
		if (i % 10 == 0)
		{
			_GetCursorPos();
			auto start{ csbi.dwCursorPosition };
			wcout << wstring(11, L'\n');
			_GetCursorPos();
			if (csbi.dwCursorPosition.Y >= start.Y)
				start.Y -= 11 - csbi.dwCursorPosition.Y + start.Y;
			SetConsoleCursorPosition(hConsole, start);
		}

		for (size_t j = 0; j < SizeLimit; ++j)
		{
			// carattere trasparente
			if (memory[i][j] == L'\0')
			{
				CharsSkipped++;
				continue;
			}

			// spostamento del cursore
			if (CharsSkipped > 0)
			{
				// calcoli
				_GetCursorPos();
				auto position{ csbi.dwCursorPosition };
				auto remaining{ SizeLimit - position.X };

				// una sola riga da scrivere
				if (CharsSkipped < remaining)
				{
					position.X += CharsSkipped;
				}

				// spostamento tra più righe
				else
				{
					CharsSkipped -= remaining;
					position.Y += CharsSkipped / SizeLimit + 1;
					position.X = CharsSkipped % SizeLimit;
				}

				// impostazione
				SetConsoleCursorPosition(hConsole, position);
				CharsSkipped = 0;
			}

			// impostazione attributo
			if (Attrib != attributes[i][j])
			{
				SetConsoleTextAttribute(hConsole, attributes[i][j]);
			}
			wcout << memory[i][j];
			Attrib = attributes[i][j];
		}

		// nuova riga
		if (CharsSkipped == 0)
		{
			wcout << L'\n';
		}
	}
	ResetAttribute();
}

// trasferimento
void Buffer::log()
{
	output();
	reset();
}

// output
wostream& operator<<(wostream& wos, const Buffer& buff)
{
	_GetCursorPos();
	auto attrib{ csbi.wAttributes };
	buff.output();
	SetConsoleTextAttribute(hConsole, attrib);
	ret wos;
}

#pragma endregion
