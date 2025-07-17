#pragma once

// inclusioni
#include "../include/buffer.h"

// funzioni di unificazione tra console e buffer
template<typename T>class OutputDevice;
template<>class OutputDevice<HANDLE>
{
public:
	void SetCursorPosition(COORD pos);
	static void SetTextAttribute(WORD attr);
	void GetBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO info) const;
	template<typename U> static void Print(U text);
};
template<>class OutputDevice<Buffer>
{
private:
	Buffer* buff;
public:
	OutputDevice(Buffer& entity);

	void SetCursorPosition(COORD pos);
	void SetTextAttribute(WORD attr);
	void GetBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO info) const;
	template<typename U> void Print(U text);
};

#pragma region OutputDevice

inline void OutputDevice<HANDLE>::SetCursorPosition(COORD pos)
{
	SetConsoleCursorPosition(hConsole, pos);
}
inline void OutputDevice<HANDLE>::SetTextAttribute(WORD attr)
{
	SetConsoleTextAttribute(hConsole, attr);
}
inline void OutputDevice<HANDLE>::GetBufferInfo(
	PCONSOLE_SCREEN_BUFFER_INFO info
) const
{
	GetConsoleScreenBufferInfo(hConsole, info);
}
template<typename U> inline void OutputDevice<HANDLE>::Print(U text)
{
	wcout << text;
}

inline OutputDevice<Buffer>::OutputDevice(Buffer& entity) : buff(&entity) {}
inline void OutputDevice<Buffer>::SetCursorPosition(COORD pos)
{
	buff->SetBufferCursorPosition(pos);
}
inline void OutputDevice<Buffer>::SetTextAttribute(WORD attr)
{
	buff->SetBufferTextAttribute(attr);
}
inline void OutputDevice<Buffer>::GetBufferInfo(
	PCONSOLE_SCREEN_BUFFER_INFO info
) const
{
	buff->GetBufferInfo(info);
}
template<typename U> inline void OutputDevice<Buffer>::Print(U text)
{
	(*buff) << text;
}

#pragma endregion
