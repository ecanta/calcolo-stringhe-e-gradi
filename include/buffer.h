#pragma once

// inclusioni
#include <iostream>
#include <string>
#include <Windows.h>
#include "../include/tensor.h"
using namespace std;
extern HANDLE hConsole;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;
extern const short SizeLimit;

// blocco del preprocessore attivo
using _TENSOR tensor;
#ifndef __BUFFER__
#define __BUFFER__

// output artificiali
struct Console
{
	wstring Text;
	WORD Attribute{ 15 };

	void log() const;

	bool operator!=(const Console& other) const;
	friend wostream& operator<<(wostream& wos, const Console& T);
};
class ConsoleStream : public tensor<Console>
{
	// costruttori e operatori
public:
	ConsoleStream();
	ConsoleStream(initializer_list<Console> init);
	ConsoleStream operator+(ConsoleStream other) const;

	// visualizzazione
	inline void output() const;
	inline void log();
	friend wostream& operator<<(wostream& wos, const ConsoleStream& T);
};
extern ConsoleStream ConsoleText;

// visualizzazione
inline void ConsoleStream::output() const
{
	for (int i = 0; i < this->size(); ++i)
	{
		wcout << (*this)[i];
	}
}
inline void ConsoleStream::log()
{
	this->output();
	this->clear();
}

// console artificiale
class Buffer
{
	// definizioni
private:
	using Funct = void(*)(wostringstream&);
	const int WindowHeight{ 40 };

	tensor<Funct> held;
	tensor<tensor<wchar_t>> memory;
	tensor<tensor<WORD>> attributes;
	COORD CursorPosition;
	WORD CurrentAttribute;
	short WindowStep;

	// ridimensionamento
	void UpdateSize();

	// costruttore
public:
	Buffer();

	// distruttore
	void reset();

	// assegnazione
	void operator=(const Buffer& other);

	// uguaglianze e disuguaglianze
	bool AbsolutelyEqual(const Buffer& other) const;
	bool operator==(const Buffer& other) const;
	bool operator!=(const Buffer& other) const;

	// cambio attributo della console
	void SetBufferTextAttribute(WORD attribute);

	// riposizionamento cursore
	void SetBufferCursorPosition(COORD position);

	// ottenimento di informazioni specifiche
	void GetBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO info) const;

	// applicazione delle funzioni
	Buffer& operator<<(Funct function);

	// scrittura di un elemento
	template<typename Arg> Buffer& operator<<(Arg written);

	// scrittura di un Console
	Buffer& operator<<(const Console& text);

	// scrittura del buffer intero
	void output() const;

	// trasferimento
	void log();
};
wostream& operator<<(wostream& wos, const Buffer& buff);

// scrittura di un elemento
template<typename Arg> Buffer& Buffer::operator<<(Arg written)
{
	// conversione in stringa
	wostringstream calculator;
	for (auto& funct : held)
	{
		funct(calculator);
	}
	calculator << written;
	auto text{ calculator.str() };

	// sostituzione dei tab con degli spazi
	size_t pos = 0;
	while ((pos = text.find(L'\t', pos)) != wstring::npos)
	{
		text.replace(pos, 1, wstring(8, L' '));
		pos += 8;
	}

	// scrittura del testo
	for (const auto& ch : text)
	{
		// carattere non stampabile
		if (ch < 32 or !isprint(ch))
		{
			continue;
		}

		// a capo
		if (ch == L'\n')
		{
			CursorPosition.X = SizeLimit;
			UpdateSize();
			continue;
		}

		// aggiunta carattere
		UpdateSize();
		memory[CursorPosition.Y + WindowStep][CursorPosition.X] = ch;
		attributes[CursorPosition.Y + WindowStep][CursorPosition.X] =
			CurrentAttribute;
		CursorPosition.X++;
	}

	ret* this;
}

#endif // __BUFFER__
