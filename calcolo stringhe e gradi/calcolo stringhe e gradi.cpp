// inizio del codice ---------------------------------------------------------------
// ATTENZIONE: il codice del programma è molto avanzato
// e deve essere eseguito in c++20 o c++23 e su Windows
#pragma region Files

// pragma
#pragma once

// macro di pragma
#define RUIN    __pragma(optimize("off", off))
#define OPT     __pragma(optimize(""   , off))
#define UNOPT   __pragma(optimize(""   , on ))
#define IMPROVE __pragma(optimize("on" , on ))

// macro di definizione
#define BUGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

// macro di switch
#ifndef BUGS
#define HIDECURSOR SetConsoleCursorInfo(hConsole, &cursorInfo)
#else // BUGS
#define HIDECURSOR
#endif // BUGS

// macro di rinominazione
#define POS false
#define NEG true
#define ret return

// funzioni macro
#define _GetCursorPos() GetConsoleScreenBufferInfo(hConsole, &csbi)
#define ResetAttribute() SetConsoleTextAttribute(hConsole, 15)
#define V1converter(func, param) To1V(func(ToXV(param)))
#define VXconverter(func, param) ToXV(func(To1V(param)))
#define DECLARE_TIME_POINT(x) LARGE_INTEGER x; QueryPerformanceCounter(&(x))

// funzioni macro importanti
#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)
#define issign(x)  (x == L'+' || x == L'-')
#define cstr(x)	   (x).c_str(), (x).size()
#define Last(x)    (x).at((x).size() - 1)
#define _SQ(x)     x * x

// messaggi
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")

#ifdef BUGS
RUIN UNOPT
#else // BUGS
IMPROVE OPT
#endif // BUGS

// file header
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <io.h>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <ppl.h>
#include <random>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <Windows.h>
#include "../tensor/tensor.cpp"

// namespace globali
#define stddef using namespace std;
using namespace std;
using namespace _STD chrono;
using Concurrency::parallel_for, this_thread::sleep_for;

#pragma endregion
#pragma region Globals

int __NULL__ = 0;

// oggetti windows
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

CONSOLE_CURSOR_INFO cursorInfo{ 10, FALSE };
CONSOLE_CURSOR_INFO cursor{ 10, TRUE };
CONSOLE_SCREEN_BUFFER_INFO csbi;

// funzioni e variabili globali
static wchar_t charVariable(L'x');
ptrdiff_t GlobalMax(0);
const ptrdiff_t GLOBAL_CAP(5e10);
bool BOOLALPHA(true);
bool PRINTN(true);
double CORRECTION_RATIO(1.0);

// variabili globali e atomiche
atomic_bool GlobalInterr(false);
atomic_bool interrupted(false);
atomic_bool computing(false);
atomic_bool IsDone(false);
atomic_bool RunMonitor(true);
condition_variable cv, Cv, MonitorCV;
mutex CoutMutex, mtx, MonitorMTX;
COORD Min{ 25, 15 };
LARGE_INTEGER ProgramFrequency;

// strutture locali
struct compost
{
	ptrdiff_t factors;
	int exp;
};
struct divisor
{
	ptrdiff_t DivNumber{ 1 };
	ptrdiff_t DivSum{ 1 };
	ptrdiff_t DivProduct{ 1 };
	wstring Div_pr;
};
struct digitRatio
{
	int digitSumRatioNum{};
	int digitSumRatioDen{};
	int digitProductRatioNum{};
	int digitProductRatioDen{};
};
digitRatio items;
struct coord
{
	double X;
	double Y;
	
	coord() : X(0), Y(0) {}
	coord(double _x, double _y) : X(_x), Y(_y) {}
	coord(COORD _coord) : X(_coord.X), Y(_coord.Y) {}

	operator COORD() const
	{
		ret
		{
			static_cast<short>(X),
			static_cast<short>(Y)
		};
	}
};

// enum e mappe
enum switchcase
{
	DoSimpleCode        ,
	DoComplexCode       ,
	DoSimpleFactor      ,
	DoComplexFactor     ,
	DoCodeFactor        ,
	DoAll               ,
	DebugSimpleCode     ,
	DebugComplexCode    ,
	DebugSimpleFactor   ,
	DebugComplexFactor  ,
	DebugCodeFactor     ,
	DebugAll            ,
	DebugDigits         ,
	DebugDigitsAndCode  ,
	DebugDigitsAndFactor,
	DebugComplete       ,
	ConvertCodeInverse  ,
	SeriesExpansion     ,
	SolveSystem         ,
	FactorPolynomial    ,
	FactorFraction      ,
	FactorMatrix        ,
	Random              ,
	NotAssigned
};
switchcase usefree;
unordered_map<wstring, switchcase> stringToEnumMap
{
	{ L"cc" , switchcase::DoSimpleCode         },
	{ L"ccc", switchcase::DoComplexCode        },
	{ L"cf" , switchcase::DoSimpleFactor       },
	{ L"cff", switchcase::DoComplexFactor      },
	{ L"ccf", switchcase::DoCodeFactor         },
	{ L"ct" , switchcase::DoAll                },
	{ L"dc" , switchcase::DebugSimpleCode      },
	{ L"dcc", switchcase::DebugComplexCode     },
	{ L"df" , switchcase::DebugSimpleFactor    },
	{ L"dff", switchcase::DebugComplexFactor   },
	{ L"dcf", switchcase::DebugCodeFactor      },
	{ L"dt" , switchcase::DebugAll             },
	{ L"dr" , switchcase::DebugDigits          },
	{ L"drc", switchcase::DebugDigitsAndCode   },
	{ L"drf", switchcase::DebugDigitsAndFactor },
	{ L"drt", switchcase::DebugComplete        },
	{ L"ctn", switchcase::ConvertCodeInverse   },
	{ L"cod", switchcase::SeriesExpansion      },
	{ L"sys", switchcase::SolveSystem          },
	{ L"pol", switchcase::FactorPolynomial     },
	{ L"alg", switchcase::FactorFraction       },
	{ L"mtx", switchcase::FactorMatrix         },
	{ L"rnd", switchcase::Random               }
};
unordered_map<switchcase, wstring> enumToStringMap
{
	{ switchcase::DoSimpleCode        , L"cc"  },
	{ switchcase::DoComplexCode       , L"ccc" },
	{ switchcase::DoSimpleFactor      , L"cf"  },
	{ switchcase::DoComplexFactor     , L"cff" },
	{ switchcase::DoCodeFactor        , L"ccf" },
	{ switchcase::DoAll               , L"ct"  },
	{ switchcase::DebugSimpleCode     , L"dc"  },
	{ switchcase::DebugComplexCode    , L"dcc" },
	{ switchcase::DebugSimpleFactor   , L"df"  },
	{ switchcase::DebugComplexFactor  , L"dff" },
	{ switchcase::DebugCodeFactor     , L"dcf" },
	{ switchcase::DebugAll            , L"dt"  },
	{ switchcase::DebugDigits         , L"dr"  },
	{ switchcase::DebugDigitsAndCode  , L"drc" },
	{ switchcase::DebugDigitsAndFactor, L"drf" },
	{ switchcase::DebugComplete       , L"drt" },
	{ switchcase::ConvertCodeInverse  , L"ctn" },
	{ switchcase::SeriesExpansion     , L"cod" },
	{ switchcase::SolveSystem         , L"sys" },
	{ switchcase::FactorPolynomial    , L"pol" },
	{ switchcase::FactorFraction      , L"alg" },
	{ switchcase::FactorMatrix        , L"mtx" },
	{ switchcase::Random              , L"rnd" }
};
unordered_map<wstring, wstring> ConvertFromSuperScript
{
	{ L"⁰", L"0" },
	{ L"¹", L"1" },
	{ L"²", L"2" },
	{ L"³", L"3" },
	{ L"⁴", L"4" },
	{ L"⁵", L"5" },
	{ L"⁶", L"6" },
	{ L"⁷", L"7" },
	{ L"⁸", L"8" },
	{ L"9", L"9" },
};

#pragma endregion
#pragma region Classes

wstring Variables{ L"x" };
using _TENSOR tensor, _TENSOR tensor_t;

// numeri complessi
template<typename Ty> class complex
{
public:

	// dati
	Ty RealPart;
	Ty ImaginaryPart;
	Ty norm() const
	{
		ret sqrt(RealPart * RealPart + ImaginaryPart * ImaginaryPart);
	}

	// costruttori
	complex() : RealPart(0), ImaginaryPart(0) {}
	complex(Ty real) : RealPart(real), ImaginaryPart(0) {}
	complex(Ty real, Ty imag) : RealPart(real), ImaginaryPart(imag) {}

	// metodi matematici
	inline complex conjugate() const
	{
		ret complex(RealPart, -ImaginaryPart);
	}
	inline complex opposite() const
	{
		ret complex(-RealPart, -ImaginaryPart);
	}

	// addizione
	complex operator+(complex value) const
	{
		ret complex(
			RealPart + value.RealPart,
			ImaginaryPart + value.ImaginaryPart
		);
	}
	inline complex& operator+=(complex value)
	{
		*this = *this + value;
		ret *this;
	}
	inline complex& operator++()
	{
		*this = *this + 1;
		ret *this;
	}
	inline complex& operator++(int)
	{
		*this = *this + 1;
		ret *this;
	}

	// sottrazione
	complex operator-(complex value) const
	{
		ret complex(
			RealPart - value.RealPart,
			ImaginaryPart - value.ImaginaryPart
		);
	}
	inline complex& operator-=(complex value)
	{
		*this = *this - value;
		ret *this;
	}
	inline complex& operator--()
	{
		*this = *this - 1;
		ret *this;
	}
	inline complex& operator--(int)
	{
		*this = *this - 1;
		ret *this;
	}

	// moltiplicazione e divisione
	complex operator*(complex value) const
	{
		Ty a{ RealPart }, b{ ImaginaryPart };
		Ty c{ value.RealPart }, d{ value.ImaginaryPart };

		ret complex(
			a * c - b * d,
			b * c + a * d
		);
	}
	inline complex& operator*=(complex value)
	{
		*this = *this * value;
		ret *this;
	}
	complex operator/(complex value) const
	{
		Ty a{ RealPart }, b{ ImaginaryPart };
		Ty c{ value.RealPart }, d{ value.ImaginaryPart };

		ret complex(
			(a * c + b * d) / (c * c + d * d),
			(b * c - a * d) / (c * c + d * d)
		);
	}
	inline complex operator/=(complex value)
	{
		*this = *this / value;
		ret *this;
	}

	// output
	wstring str() const
	{
		wostringstream output;
		if (ImaginaryPart)
		{
			output << setprecision(10) << L'(';
		}
		output << RealPart;
		if (ImaginaryPart)
		{
			ImaginaryPart > 0 ? output << L" + " : output << L" - ";
			if (!integer(ImaginaryPart))
			{
				output << L'i';
			}

			if (fabs(ImaginaryPart) != 1)
			{
				output << fabs(ImaginaryPart);
			}

			if (integer(ImaginaryPart))
			{
				output << L'i';
			}
			output << L')';
		}
		ret output.str();
	}

	friend wostream& operator<<(wostream& os, const complex& obj)
	{
		os << obj.str();
		ret os;
	}
};
template<typename Ty> static complex<Ty> InitExponentialForm(Ty radius, Ty angle)
{
	ret complex<Ty>(radius * cos(angle), radius * sin(angle));
}

// algoritmo di cooley-tukey per la trasformata di fourier veloce
#define MOVE_DOWN 0
#define MOVE_SIDE 1
#define MOVE_UP 2
tensor<complex<long double>> Omega;
static void FFT(tensor<complex<long double>>& List, bool inverse = false)
{
	// invarianza
	if (List == 1)
	{
		ret;
	}

	// calcolo di omega
	auto N{ List.size() };
	tensor<complex<long double>> Helper(N);
	if (Omega < N)
	{
		auto omega{ Omega };
		Omega.clear();
		size_t Ratio = omega.empty() ? 1 : N / (2 * omega.size());
		for (size_t i = 0; i < N / 2; ++i)
		{
			Omega << (i % Ratio == 0 and !omega.empty() ? omega[i / Ratio] :
				InitExponentialForm<long double>(1, -2 * M_PI * i / N));
		}
	}

	// iterazione non ricorsiva
	int StarterIndex{}, Step = N / 2, command{};
	for (;;)
	{
		// caso base
		if (N == 2 * Step)
		{
			auto FinalIndex{ StarterIndex + Step };
			auto temp{ List[StarterIndex] - List[FinalIndex] };
			List[StarterIndex] += List[FinalIndex];
			List[FinalIndex] = temp;
		}

		// fusione delle FFT inferiori
		else
		{
			int i{};
			auto OmegaStep{ 2 * Step * Omega.size() / N };
			for (size_t I = StarterIndex; I < N / 2; I += Step)
			{
				auto W = inverse ?
					Omega[OmegaStep * i].conjugate() : Omega[OmegaStep * i];

				Helper[I + N / 2] = List[2 * I - StarterIndex]
					- W * List[2 * I - StarterIndex + Step];

				Helper[I] = List[2 * I - StarterIndex]
					+ W * List[2 * I - StarterIndex + Step];

				i++;
			}
			for (size_t I = StarterIndex; I < N; I += Step)
			{
				List[I] = Helper[I];
			}
		}

		// vari spostamenti
		if (command == MOVE_UP)
		{
			// uscita
			if (Step == 1)
			{
				ret;
			}

			// spostamento in fondo al nodo parallelo
			if (Step > 2 * StarterIndex)
			{
				command = MOVE_DOWN;
				StarterIndex += Step / 2;
				Step = N / 2;
				continue;
			}

			// spostamento verso l'alto
			StarterIndex -= (Step /= 2);
		}

		// spostamento verso l'alto
		if (command == MOVE_SIDE)
		{
			command = MOVE_UP;
			StarterIndex -= (Step /= 2);
			continue;
		}

		// spostamento parallelo
		command = MOVE_SIDE;
		StarterIndex += Step / 2;
	}
}

// numeri grandi con precisione di long double
class big
{
private:

	// dati
	tensor<int> Integer;
	bool sign;
	long double decimal;

	// funzioni minori
	void construct(ptrdiff_t param)
	{
		tensor<int> temp;
		while (param > 0)
		{
			temp << param % 10;
			param /= 10;
		}
		if (temp.empty())
		{
			temp = { 0 };
		}
		auto size{ temp.size() };

		for (ptrdiff_t i = size - 1; i >= 0; --i)
		{
			Integer << temp[i];
		}
	}
	void shift()
	{
		wstring str;
		wostringstream oss;
		oss << fixed << setprecision(25) << decimal;
		str = oss.str();
		str.erase(0, 2);
		bool Do{ false };
		for (ptrdiff_t i = str.size() - 1; i >= 0; --i)
		{
			int element = str.at(i) - L'0';
			if (element != 0)
			{
				Do = true;
			}
			if (Do)
			{
				Integer << element;
			}
		}
	}

	// confronti
	bool compare(const big& A, const big& B) const
	{
		auto integ{ A.Integer };
		auto oth_integ{ B.Integer };

		while (integ > 1 and integ[0] == 0)
		{
			--integ;
		}
		while (oth_integ > 1 and oth_integ[0] == 0)
		{
			--oth_integ;
		}

		if (integ % oth_integ)
		{
			ret integ < oth_integ;
		}
		for (size_t i = 0; i < integ; ++i)
		{
			if (integ[i] != oth_integ[i])
			{
				ret integ[i] < oth_integ[i];
			}
		}

		ret A.decimal < B.decimal;
	}

	// addizione e sottrazione
	big Add(const big& __This, const big& __Val, bool changesign) const
	{
		big This(__This), Val(__Val);
		if (changesign)
		{
			This.sign = !This.sign;
		}
		bool carry;

		// ridimensionamento
		if (This.Integer < Val.Integer)
		{
			swap(This, Val);
		}
		Val.Integer.insert(
			Val.Integer.begin(),
			This.Integer.size() - Val.Integer.size(),
			0
		);

		// somma
		This.decimal += Val.decimal;
		This.decimal -= (carry = This.decimal >= 1);
		for (ptrdiff_t i = This.Integer.size() - 1; i >= 0; --i)
		{
			This.Integer[i] += Val.Integer[i] + carry;
			This.Integer[i] -= 10 * (carry = This.Integer[i] >= 10);
		}

		// riporto
		if (carry)
		{
			This.Integer >> 1;
		}
		ret This;
	}
	big Sub(const big& __This, const big& __Val, bool changesign) const
	{
		big This(__This), Val(__Val);
		if (changesign)
		{
			This.sign = !This.sign;
		}
		bool carry;

		// ridimensionamento
		Val.Integer.insert(
			Val.Integer.begin(),
			This.Integer.size() - Val.Integer.size(),
			0
		);

		// differenza
		This.decimal -= Val.decimal;
		This.decimal += (carry = This.decimal < 0);
		for (ptrdiff_t i = This.Integer.size() - 1; i >= 0; --i)
		{
			This.Integer[i] -= Val.Integer[i] + carry;
			This.Integer[i] += 10 * (carry = This.Integer[i] < 0);
		}

		// rimozione zeri iniziali
		while (This.Integer > 1 and This.Integer[0] == 0)
		{
			--This.Integer;
		}
		ret This;
	}
	big AlgebricOperation1(const big& A, const big& B, bool sign) const
	{
		// addizione tra valori assoluti
		if (!(A.sign xor B.sign xor sign))
		{
			ret Add(A, B, false);
		}

		// zero
		if (A.Integer == B.Integer and A.decimal == B.decimal)
		{
			ret 0;
		}

		// sottrazione tra valori assoluti
		ret compare(A, B) ? Sub(B, A, sign) : Sub(A, B, !sign);
	}

	// moltiplicazione
	big Multiply(const big& value) const
	{
		if ((value.Integer[0] == 0 and value.decimal == 0) or
			(Integer[0] == 0 and decimal == 0))
		{
			ret 0;
		}
		big Val = value, This = *this;
		Val.shift();
		This.shift();
		int decprecision = Val.Integer.size() - value.Integer.size()
			+ This.Integer.size() - Integer.size();
		Val.sign = This.sign = POS;

		// moltiplicazione
		tensor<big> add;
		for (size_t a = 0; a < Val.Integer.size(); ++a)
		{
			int factor{ Val.Integer.at(a) };
			if (factor == 0)
			{
				continue;
			}
			int carry{}, prod{};

			auto _Number{ This.Integer };
			for (ptrdiff_t i = _Number.size() - 1; i >= 0; --i)
			{
				prod = (_Number.at(i)) * factor + carry;
				carry = prod / 10;
				_Number[i] = prod % 10;
			}
			if (carry != 0)
			{
				_Number >> carry;
			}
			for (ptrdiff_t i = Val.Integer.size() - a - 2; i >= 0; --i)
			{
				_Number << 0;
			}
			add << big(_Number);
		}

		// somma
		This.Integer.clear();
		for (auto big : add)
		{
			This += big;
		}

		// cifre decimali
		int dec{};
		auto decdigits{ This.Integer };
		while (decdigits.size() - decprecision < 0)
		{
			decdigits >> 0;
		}
		This.Integer = decdigits;
		if (decprecision > 0)
		{
			This.Integer.erase(decdigits.size() - decprecision);
		}
		decdigits.erase(0, decdigits.size() - decprecision);
		for (size_t i = 0; i < decdigits; ++i)
		{
			dec += decdigits[i] * pow(10, decdigits.size() - i - 1);
		}

		if (This.Integer.empty())
		{
			This.Integer = { 0 };
		}
		This.decimal = dec / pow(10, decprecision);
		This.sign = sign xor value.sign;
		ret This;
	}
	big FFT_Multiplication(const big& value) const
	{
		// calcolo dimensione
		size_t N{ 1 };
		auto sizeA{ Integer.size() };
		auto sizeB{ value.Integer.size() };
		while (N < sizeA + sizeB)
		{
			N <<= 1;
		}

		// preparazione tensori
		tensor<complex<long double>> A(N), B(N);
		for (size_t i = 0; i < sizeA; ++i)
		{
			A[i] = complex<long double>(Integer[sizeA - i - 1]);
		}
		for (size_t i = 0; i < sizeB; ++i)
		{
			B[i] = complex<long double>(value.Integer[sizeB - i - 1]);
		}

		// operazioni con le trasformate di fourier veloci
		FFT(A);
		FFT(B);
		for (size_t i = 0; i < N; ++i)
		{
			A[i] *= B[i];
		}
		FFT(A, true);
		for (auto& num : A)
		{
			num /= N;
		}

		// conversione
		big result;
		ptrdiff_t carry{};
		result.Integer(N);
		for (size_t i = 0; i < N; ++i)
		{
			ptrdiff_t value = _STD round(A[i].RealPart) + carry;
			result.Integer[N - i - 1] = value % 10;
			carry = value / 10;
		}

		// rimozione zeri inutili
		while (result.Integer > 1 and result.Integer[0] == 0)
		{
			--result.Integer;
		}
		result.sign = sign xor value.sign;

		ret result;
	}

public:
	template<typename t> t Number()
	{
		if constexpr (is_same_v<t, size_t>)
		{
			ret nan("");
		}
		ptrdiff_t val{};

		// calcolo parte intera
		for (size_t i = 0; i < Integer; ++i)
		{
			val += Integer[i] * pow(10, Integer.size() - i - 1);
			if (val != 0 and
				(val < numeric_limits<t>::min() or val > numeric_limits<t>::max()))
			{
				ret nan("");
			}
		}
		t res = val;

		// parte decimale e segno
		if constexpr (is_floating_point_v<t>)
		{
			res += decimal;
		}
		if constexpr (is_signed_v<t>)
		{
			if (sign == NEG)
			{
				res *= -1;
			}
		}
		ret res;
	}

	// costruttori
	big() : sign(POS), Integer(0), decimal(0) {}
	big(int param) : sign(param < 0), Integer(0), decimal(0)
	{
		construct(abs(param));
	}
	big(ptrdiff_t param) : sign(param < 0), Integer(0), decimal(0)
	{
		construct(abs(param));
	}
	big(double param) : sign(param < 0), Integer(0), decimal(0)
	{
		param = _STD fabs(param);
		auto Intpart{ static_cast<ptrdiff_t>(param) };
		decimal = param - Intpart;
		construct(Intpart);
	}
	big(long double param) : sign(param < 0), Integer(0), decimal(0)
	{
		param = _STD fabs(param);
		auto Intpart{ static_cast<ptrdiff_t>(param) };
		decimal = param - Intpart;
		construct(Intpart);
	}
	big(tensor<int> Big) : sign(POS), Integer(Big), decimal(0)
	{
		if (Integer.empty())
		{
			Integer = { 0 };
		}
		while (Integer > 1 and Integer[0] == 0)
		{
			--Integer;
		}
	}
	big(wstring wstr) : sign(POS), Integer(0), decimal(0)
	{
		tensor<int> Big;
		for (auto c : wstr)
		{
			if (iswdigit(c))
			{
				Integer << c - L'0';
			}
		}
	}

	// confronto primario e assegnazione
	big& operator=(const big& other)
	{
		if (this == &other)
		{
			ret *this;
		}

		sign = other.sign;
		Integer = other.Integer;
		decimal = other.decimal;
		ret *this;
	}
	inline bool operator==(const big& other) const
	{
		ret sign == other.sign and Integer == other.Integer
			and decimal == other.decimal;
	}
	inline bool operator!=(const big& other) const
	{
		ret !(*this == other);
	}

	// confronto secondario
	bool operator<(const big& other) const
	{
		ret(sign xor other.sign) ? sign : (compare(*this, other) xor sign);
	}
	inline bool operator<=(const big& other) const
	{
		ret *this < other or *this == other;
	}
	inline bool operator>=(const big& other) const
	{
		ret !(*this < other);
	}
	inline bool operator>(const big& other) const
	{
		ret !(*this == other or *this < other);
	}

	// addizione
	big operator+(const big& value) const
	{
		ret AlgebricOperation1(*this, value, POS);
	}
	inline big& operator+=(const big& value)
	{
		*this = *this + value;
		ret *this;
	}
	inline big& operator++()
	{
		*this = *this + 1;
		ret *this;
	}
	inline big& operator++(int)
	{
		*this = *this + 1;
		ret *this;
	}

	// sottrazione
	big operator-(const big& value) const
	{
		ret AlgebricOperation1(*this, value, NEG);
	}
	inline big& operator-=(const big& value)
	{
		*this = *this - value;
		ret *this;
	}
	inline big& operator--()
	{
		*this = *this - 1;
		ret *this;
	}
	inline big& operator--(int)
	{
		*this = *this - 1;
		ret *this;
	}

	// moltiplicazione
	big operator<<(int shift) const
	{
		big result = *this;
		for (size_t i = 0; i < shift; ++i)
		{
			result.Integer << 0;
		}
		ret result;
	}
	inline big& operator<<=(int shift)
	{
		*this = *this << shift;
		ret *this;
	}
	big operator*(const big& value) const
	{
		// casi particolari
		if (value == 0 or *this == 0)
		{
			big result;
			result.sign = POS;
			result.Integer = { 0 };
			result.decimal = 0;
			ret result;
		}

		////////////////////////----------------------------------------------------
		// // // TESTER // // //

		steady_clock::time_point begin = steady_clock::now();
		big A = FFT_Multiplication(value);
		steady_clock::time_point end = steady_clock::now();
		wcout << "FFT: ";
		wcout << duration_cast<microseconds>(end - begin).count() << L'\n';

		// begin = steady_clock::now();
		// big B = Multiply(value);
		// end = steady_clock::now();
		// wcout << "Normal: ";
		// wcout << duration_cast<microseconds>(end - begin).count() << L'\n';

		wcout << L'\n';
		ret A;

		// // // TESTER // // //----------------------------------------------------
		////////////////////////
	}

	inline big& operator*=(const big& value)
	{
		*this = *this * value;
		ret *this;
	}

	// divisione intera
	big operator/(const big& value) const
	{
		if (value == 0)
		{
			throw invalid_argument("Division by zero!");
		}

		big This = *this, result, current;
		result.Integer.clear();
		result.sign = This.sign != value.sign;

		// divisione lunga
		for (size_t i = 0; i < This.Integer; ++i)
		{
			// correzione
			int quotient{};
			current.Integer << This.Integer[i];
			while (current.Integer > 1 and current.Integer[0] == 0)
			{
				--current.Integer;
			}

			// divisione
			while (current >= value.fabs())
			{
				current -= value.fabs();
				quotient++;
			}
			result.Integer << quotient;
		}

		// ridimensionamento
		while (result.Integer > 1 and result.Integer[0] == 0)
		{
			--result.Integer;
		}
		result.decimal = 0;
		ret result;

		// if (value == 0)
		// {
		// 	throw invalid_argument("Division by zero!");
		// }
		// 
		// // metodo di newton-raphson
		// big old, result = 0.0001;
		// for (;;)
		// {
		// 	old = result;
		// 	result = result * 2 - value * result * result;
		// 	if ((result - old).fabs() < 1e-17)
		// 	{
		// 		break;
		// 	}
		// }
		// 
		// auto output{ (*this) * result };
		// output.decimal = 0;
		// ret output;
	}
	inline big& operator/=(const big& value)
	{
		*this = *this / value;
		ret *this;
	}

	// modulo
	big operator%(const big& value) const
	{
		if (value == 0)
		{
			throw invalid_argument("Modulo by zero!");
		}

		// segni
		big This = *this, Val = value;
		Val.sign = This.sign = POS;

		// calcolo
		while (This >= Val)
		{
			big temp = Val, factor = 1;

			while ((temp << 1) <= This)
			{
				factor <<= 1;
				temp <<= 1;
			}
			This -= temp;
		}

		ret This;
	}
	inline big& operator%=(const big& value)
	{
		*this = *this % value;
		ret *this;
	}

	// potenza
	big operator^(const big& exp) const
	{
		big power = 1, NewExp = exp + 1, NewBase = *this;
		if (*this < 0)
		{
			NewBase.invert();
		}
		while (--NewExp > 0)
		{
			power *= NewBase;
			if (power < 0)
			{
				ret - 1;
			}
		}
		if (exp % 2 == 1 and *this < 0)
		{
			power.invert();
		}
		ret power;
	}
	inline big& operator^=(const big& exp)
	{
		*this = *this ^ exp;
		ret *this;
	}

	// metodi matematici
	inline bool intg() const
	{
		ret decimal == 0;
	}
	inline big fabs() const
	{
		big other = *this;
		other.sign = POS;
		ret other;
	}
	inline big floor()
	{
		decimal = 0;
		ret *this;
	}
	inline big ceil()
	{
		bool integ = decimal == 0;
		decimal = 0;
		if (integ)
		{
			(*this)++;
		}
		ret *this;
	}
	inline big round()
	{
		*this += _STD round(decimal);
		decimal = 0;
		ret *this;
	}
	inline big invert()
	{
		sign = !sign;
		ret *this;
	}
	inline int log(int base)
	{
		for (int i = 0;; ++i)
		{
			if (*this < base)
			{
				ret i;
			}
			*this /= base;
		}
	}

	// output
	wostringstream c_str(int precision) const
	{
		wostringstream oss, result;
		if (sign)
		{
			result << L'-';
		}
		for (size_t i = 0; i < Integer; ++i)
		{
			result << Integer[i];
		}
		if (precision > 0)
		{
			oss << setprecision(precision) << decimal;
		}
		auto str{ oss.str() };
		str.erase(0, 1);
		if (!str.empty())
		{
			result << L'.' << str;
		}
		ret result;
	}
	inline wstring str() const
	{
		ret c_str(0).str();
	}
	friend wostream& operator<<(wostream& os, const big& obj)
	{
		os << obj.str();
		ret os;
	}
};
big LCM(1);

// monomi
template<typename T_int = long double>struct MONOMIAL
{
	int degree;
	T_int coefficient;
	bool operator == (const MONOMIAL& other) const
	{
		ret coefficient == other.coefficient and
			degree == other.degree;
	}
};
template<typename T_int = long double>class monomial
{
public:
	T_int coefficient{};
	tensor<int> exp;

	bool operator==(const monomial& other) const
	{
		ret coefficient == other.coefficient and exp == other.exp;
	}
	int degree() const
	{
		int sum{};
		for (size_t i = 0; i < exp; ++i)
		{
			sum += exp[i];
		}
		ret sum;
	}
	bool IsSquare() const
	{
		if (!integer(sqrt(fabs(this->coefficient))))
		{
			ret false;
		}
		for (size_t i = 0; i < exp; ++i)
		{
			if (exp[i] % 2 == 1)
			{
				ret false;
			}
		}
		ret true;
	}
	monomial Root(int order) const
	{
		monomial result;

		result.coefficient = pow(this->coefficient, 1.0 / order);
		for (size_t i = 0; i < exp; ++i)
		{
			result.exp << (exp[i] / order);
		}

		ret result;
	}
};

// fattori di polinomi
template<typename T_int = long double>class factor : public tensor<monomial<T_int>>
{
public:
	factor() {}
	factor(initializer_list<monomial<T_int>> init): tensor<monomial<T_int>>(init) {}
	factor(size_t size, const monomial<T_int>& initial_value)
	{
		this->resize(size);
		count = size;
		fill(data, data + count, initial_value);
	}
	factor(size_t size)
	{
		this->resize(size);
		this->count = size;
	}
	factor(tensor<monomial<T_int>> vect)
	{
		for (const auto& value : vect)
		{
			this->push_back(value);
		}
	}

	void SortByDegree()
	{
		for (size_t i = 0; i < this->size(); ++i)
		{
			for (size_t j = i + 1; j < this->size(); ++j)
			{
				if (this->at(i).degree() < this->at(j).degree())
				{
					swap(this->at(i), this->at(j));
				}
			}
		}
	}
	void SortByExponents()
	{
		if (this->empty())
		{
			ret;
		}
		size_t size{ Variables.size() };
		for (size_t i = 0; i < this->size(); ++i)
		{
			for (size_t j = i + 1; j < this->size(); ++j)
			{
				bool swap{ false };
				for (size_t k = 0; k < size; ++k)
				{
					if (this->at(i).exp[k] > this->at(j).exp[k])
					{
						break;
					}
					if (this->at(i).exp[k] == this->at(j).exp[k])
					{
						continue;
					}
					swap = true;
					break;
				}
				if (swap)
				{
					::swap(this->at(i), this->at(j));
				}
			}
		}
	}
	
	factor derivate(size_t Vpos) const
	{
		tensor<int> null(Variables.size(), 0);
		if (this->empty())
		{
			ret { { 0, null } };
		}
		auto Derivative{ *this };
		for (ptrdiff_t i = Derivative.size() - 1; i >= 0; --i)
		{
			if (Derivative[i].exp[Vpos] == 0)
			{
				Derivative.erase(Derivative.begin() + i);
				continue;
			}
			Derivative[i].coefficient *= Derivative[i].exp[Vpos]--;
		}
		if (Derivative.empty())
		{
			ret { { 0, null } };
		}
		ret Derivative;
	}

	T_int operator()(tensor<long double> params) const
	{
		if (params > Variables.size())
		{
			throw out_of_range("Too many parameters");
		}
		while (params < Variables.size())
		{
			params << 0;
		}

		auto This{ *this };
		for (size_t i = 0; i < Variables.size(); ++i)
		{
			This = This(params[i], i, 0);
		}
		if (This.empty())
		{
			ret 0;
		}
		ret This[0].coefficient / LCM.Number<T_int>();
	}
	factor operator()(T_int x, size_t Vpos, int) const;
	bool operator()(T_int x, size_t Vpos, bool) const
	{
		big X = x, y;
		for (size_t i = 0; i < this->size(); ++i)
		{
			y += (X ^ (*this)[i].exp[Vpos]) * (*this)[i].coefficient;
		}
		ret y >= 0;
	}

	inline factor neg() const
	{
		auto This{ *this };
		for (auto& mon : This)
		{
			mon.coefficient *= -1;
		}
		ret This;
	}
	inline factor operator-(const factor& other) const;
	inline factor operator*(const factor& other) const;
	inline factor& operator-=(const factor& other);
	inline factor& operator*=(const factor& other);

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		wstring polynomial;
		for (auto data : *this)
		{
			// caso nullo
			if (data.coefficient == 0)
			{
				continue;
			}

			// aggiunta coefficiente
			wstring Monomial;
			Monomial = data.coefficient > 0 ? L'+' : L'-';
			if ((data.coefficient != 1 and data.coefficient != -1)
				or data.exp == tensor<int>(data.exp.size(), 0))
			{
				if constexpr (is_same_v<T_int, long double>)
				{
					Monomial += to_wstring((int)fabs(data.coefficient));
				}
				else if constexpr (is_same_v<T_int, big>)
				{
					Monomial += data.coefficient.fabs().str();
				}
			}

			// aggiunta variabili ed esponenti
			for (size_t i = 0; i < Variables.size(); ++i)
			{
				if (data.exp[i] != 0)
				{
					Monomial += size == Variables.size() ?
						Variables.at(i) :
						Variables.at(Variables.find(charVariable));
					if (data.exp[i] > 1)
					{
						Monomial += L"^" + to_wstring((int)data.exp[i]);
					}
				}
			}
			polynomial += Monomial;
		}
		
		if (polynomial.empty())
		{
			ret L"0";
		}
		if (polynomial.at(0) == L'+')
		{
			polynomial.erase(0, 1);
		}
		ret polynomial;
	}

	friend wostream& operator<<(wostream& os, factor& obj)
	{
		os << obj.str();
		ret os;
	}
};
template<typename T_int = long double>class FACTOR : public tensor<MONOMIAL<T_int>>
{
public:
	FACTOR() {}
	FACTOR(initializer_list<MONOMIAL<T_int>> init): tensor<MONOMIAL<T_int>>(init) {}
	FACTOR(size_t size, const MONOMIAL<T_int>& initial_value)
	{
		this->resize(size);
		count = size;
		fill(data, data + count, initial_value);
	}
	FACTOR(size_t size)
	{
		this->resize(size);
		this->count = size;
	}
	FACTOR(tensor<MONOMIAL<T_int>> vect)
	{
		for (const auto& value : vect)
		{
			this->push_back(value);
		}
	}

	void sort()
	{
		for (size_t i = 0; i < this->size(); ++i)
		{
			for (size_t j = i + 1; j < this->size(); ++j)
			{
				if (this->at(i).degree < this->at(j).degree)
				{
					swap(this->at(i), this->at(j));
				}
			}
		}
	}
	void complete(int s)
	{
		// riempimento buchi
		for (ptrdiff_t i = this->size() - 1; i > 0; --i)
		{
			for (int j = 1; j < (*this)[i - 1].degree - (*this)[i].degree; ++j)
			{
				this->insert(this->begin() + i, { (*this)[i - 1].degree - j, 0 });
			}
		}

		// riempimento buchi agli estremi
		if (this->empty())
		{
			for (size_t i = 0; i < s; ++i)
			{
				this->push_back({ (int)i, 0 });
			}
		}
		if (this->size() < s)
		{
			while ((*this)[0].degree < s - 1)
			{
				this->insert(this->begin(), { (*this)[0].degree + 1, 0 });
			}

			while ((*this)[this->size() - 1].degree > 0)
			{
				this->push_back({ (*this)[this->size() - 1].degree - 1, 0 });
			}
		}
	}

	FACTOR derivate() const
	{
		if (this->size() == 0)
		{
			ret { { 0, 0 } };
		}
		auto Derivative{ *this };
		Derivative.sort();
		Derivative.complete(Derivative[0].degree + 1);
		if (Derivative.size() == 1 and Derivative[0].degree == 0)
		{
			ret { { 0, 0 } };
		}
		for (size_t j = 0; j < Derivative; ++j)
		{
			Derivative[j].coefficient *= Derivative[j].degree--;
		}
		Derivative--;
		if (Derivative.empty())
		{
			Derivative = { { 0, (*this)[0].coefficient } };
		}
		ret Derivative;
	}

	T_int operator()(T_int x) const
	{
		T_int fx{};
		for (size_t i = 0; i < this->size(); ++i)
		{
			fx += (
				(*this)[i].coefficient * pow(x, (*this)[i].degree)
			) / LCM.Number<long double>();
		}
		ret fx;
	}

	inline FACTOR neg() const
	{
		auto This{ *this };
		for (auto& mon : This)
		{
			mon.coefficient *= -1;
		}
		ret This;
	}
	inline FACTOR operator-(const FACTOR& other) const;
	inline FACTOR operator*(const FACTOR& other) const;
	inline FACTOR& operator-=(const FACTOR& other);
	inline FACTOR& operator*=(const FACTOR& other);

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		factor<T_int> traduction;
		int _FirstPos = Variables.find(charVariable);
		for (const auto& Monomial : *this)
		{
			monomial<T_int> element;
			element.coefficient = Monomial.coefficient;
			element.exp(Variables.size(), 0);
			element.exp[_FirstPos] = Monomial.degree;
			traduction << element;
		}
		ret traduction.str(1);
	}

	friend wostream& operator<<(wostream& os, const FACTOR& obj)
	{
		os << obj.str();
		ret os;
	}
};
static factor<> ToXV(FACTOR<> vect)
{
	factor<> output;
	int _FirstPos = Variables.find(charVariable);
	for (const auto& Monomial : vect)
	{
		monomial<> element;
		element.coefficient = Monomial.coefficient;
		element.exp(Variables.size(), 0);
		element.exp[_FirstPos] = Monomial.degree;
		output << element;
	}
	ret output;
}
static FACTOR<> To1V(factor<> vect)
{
	FACTOR<> output;
	int _FirstPos = Variables.find(charVariable);
	for (const auto& Monomial : vect)
	{
		MONOMIAL<> element{ 0, 0 };
		element.coefficient = Monomial.coefficient;
		if (_FirstPos != wstring::npos)
		{
			element.degree = Monomial.exp[_FirstPos];
		}
		output << element;
	}
	ret output;
}

// polinomi completi
static wstring ElabExponents(wstring& str);
template<typename T_int = long double>class polynomial
	: public tensor<factor<T_int>>
{
public:
	polynomial() {}
	polynomial(initializer_list<factor<T_int>> init): tensor<factor<T_int>>(init) {}
	polynomial(size_t size, const factor<T_int>& initial_value)
	{
		this->resize(size);
		count = size;
		fill(data, data + count, initial_value);
	}
	polynomial(size_t size)
	{
		this->resize(size);
		this->count = size;
	}
	polynomial(tensor<factor<T_int>> vect)
	{
		for (const auto& value : vect)
		{
			this->push_back(value);
		}
	}

	void open()
	{
		for (size_t i = 0; i < this->count; ++i)
		{
			if ((*this)[i][0].exp[0] == -1)
			{
				auto repeat = (*this)[i][0].coefficient;
				this->erase(this->begin() + i);
				auto push{ (*this)[i] };
				for (big j = 0; j < repeat - 1; ++j)
				{
					this->push_front(push);
				}
			}
		}
	}
	void close()
	{
		tensor<int> modifier(Variables.size());
		modifier[0] = -1;
		factor<T_int> CommonFactor;
		if (this->count == 0)
		{
			ret;
		}

		for (size_t i = 0; i < this->count; ++i)
		{
			for (ptrdiff_t j = this->count - 1; j > i; --j)
			{
				if ((*this)[i] == (*this)[j] and (*this)[i][0].exp[0] >= 0)
				{
					CommonFactor = (*this)[i];
					
					// caso di eccezione
					if (i <= 0)
					{
						this->push_front({ { 2, modifier } });
						this->erase(this->begin() + j + 1);
						continue;
					}

					// caso con esponente
					if ((*this)[i - 1].size() == 1 and
						(*this)[i - 1][0].exp[0] < 0)
					{
						(*this)[i - 1][0].coefficient++;
						this->erase(this->begin() + j);
						continue;
					}

					// caso senza esponente
					int setK = 0;
					this->erase(this->begin() + j);
					this->insert(this->begin() + i, { { 2, modifier } });
					for (size_t k = 0; k < this->size(); ++k)
					{
						if ((*this)[k] == CommonFactor)
						{
							setK = k;
							break;
						}
					}
					if ((*this)[i + 1] != CommonFactor)
					{
						swap((*this)[i + 1], (*this)[setK]);
					}
				}
			}
		}
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		if (this->count == 0)
		{
			ret L"0";
		}

		wstring output, exp, coeffstr{ L"1" };
		bool IsAModifier{ false };
		for (auto T : *this)
		{
			// caso di monomio modificatore
			if (!T[0].exp.empty()) if (T[0].exp[0] < 0)
			{
				if constexpr (is_same_v<T_int, long double>)
				{
					exp = to_wstring((int)T[0].coefficient);
				}
				else if constexpr (is_same_v<T_int, big>)
				{
					exp = T[0].coefficient.str();
				}
				IsAModifier = true;
				continue;
			}
			auto xout{ T.str(size) };

			// caso con elevamento a potenza
			if (IsAModifier)
			{
				xout = L"(" + xout + L")^" + exp;
				IsAModifier = false;
				output += xout;
				continue;
			}

			// caso coefficiente
			if (T == 1)
			{
				coeffstr = xout;
				continue;
			}

			// caso comune
			else if ((int)this->size() - (coeffstr != L"1") > 1)
			{
				xout = L"(" + xout + L")";
			}
			output += xout;
		}
		
		// aggiunta del denominatore
		if (!output.empty())
		{
			output = L'[' + output + L']';
		}
		else if (LCM != 1)
		{
			output.clear();
		}
		else
		{
			ret ElabExponents(coeffstr);
		}
		if (LCM.fabs() != 1 or coeffstr != L"1")
		{
			// polinomio piccolo
			if constexpr (is_same_v<T_int, long double>)
			{
				if (LCM.fabs() != 1)
				{
					output = L'/' + LCM.str() + L']' + output;
				}
				output = coeffstr + output;
				if (LCM.fabs() != 1)
				{
					output = L'[' + output;
				}
			}

			// polinomio grande
			else if constexpr (is_same_v<T_int, big>)
			{
				if (LCM.fabs() != 1)
				{
					if (!output.empty())
					{
						output += L'/';
					}
					output = output + L'[' + LCM.str() + L']';
				}
				output = coeffstr + output;
			}
		}
		if (LCM < 0)
		{
			output = L'-' + output;
		}
		if (output == L"-" and coeffstr == L"1")
		{
			output = L"-1";
		}

		// eliminazioni parentesi quadre se non sono necessarie
		else if (output.at(0) == L'[' and Last(output) == L']')
		{
			output.erase(0, 1);
			output.pop_back();
			if (output.find(L'[') != wstring::npos and
				output.find(L']') != wstring::npos)
			{
				output = L'[' + output + L']';
			}
		}

		ret ElabExponents(output);
	}

	friend wostream& operator<<(wostream& os, polynomial& obj)
	{
		os << obj.str();
		ret os;
	}
};
template<typename T_int = long double>class POLYNOMIAL
	: public tensor<FACTOR<T_int>>
{
public:
	POLYNOMIAL() {}
	POLYNOMIAL(initializer_list<FACTOR<T_int>> init): tensor<FACTOR<T_int>>(init) {}
	POLYNOMIAL(size_t size, const FACTOR<T_int>& initial_value)
	{
		this->resize(size);
		count = size;
		fill(data, data + count, initial_value);
	}
	POLYNOMIAL(size_t size)
	{
		this->resize(size);
		this->count = size;
	}
	POLYNOMIAL(tensor<FACTOR<T_int>> vect)
	{
		for (const auto& value : vect)
		{
			push_back(value);
		}
	}

	void open()
	{
		polynomial<T_int> NewClass;
		for (size_t i = 0; i < this->count; ++i)
		{
			NewClass << ToXV((*this)[i]);
		}
		NewClass.open();
		this->clear();
		for (size_t i = 0; i < NewClass; ++i)
		{
			this->push_back(To1V(NewClass[i]));
		}
	}
	void close()
	{
		polynomial<T_int> NewClass;
		for (size_t i = 0; i < this->count; ++i)
		{
			NewClass.push_back(ToXV((*this)[i]));
		}
		NewClass.close();
		this->clear();
		for (size_t i = 0; i < NewClass; ++i)
		{
			this->push_back(To1V(NewClass[i]));
		}
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		polynomial<T_int> traduction;
		for (const auto& vector : *this)
		{
			traduction << ToXV(vector);
		}
		ret traduction.str(1);
	}

	friend wostream& operator<<(wostream& os, const POLYNOMIAL& obj)
	{
		os << obj.str();
		ret os;
	}
};

static polynomial<> ToXV(POLYNOMIAL<> vect)
{
	polynomial<> output;
	for (const auto& vector : vect)
	{
		output << ToXV(vector);
	}
	ret output;
}
static POLYNOMIAL<> To1V(polynomial<> vect)
{
	POLYNOMIAL<> output;
	for (const auto& vector : vect)
	{
		output << To1V(vector);
	}
	ret output;
}
static polynomial<> FromBigToDefault(polynomial<big> BigPolynomial)
{
	polynomial<> traduction;
	for (auto fact : BigPolynomial)
	{
		factor<> element;
		for (auto mon : fact)
		{
			monomial<> unity;
			unity.coefficient = mon.coefficient.Number<long double>();

			if (isnan(unity.coefficient))
			{
				ret polynomial<>{ { { 1, tensor<int>(1, -2) } } };
			}
			unity.exp = mon.exp;
			element << unity;
		}
		traduction << element;
	}
	ret traduction;
}

template<typename T_int = long double>
static factor<T_int> PolynomialSum(factor<T_int> vect);
template<typename T_int = long double>
static factor<T_int> PolynomialMultiply(polynomial<T_int> Polynomial);

template <class T_int>
factor<T_int> factor<T_int>::operator()(T_int x, size_t Vpos, int) const
{
	auto This{ *this };
	for (size_t i = 0; i < this->size(); ++i)
	{
		This[i].coefficient *= pow(x, This[i].exp[Vpos]);
		This[i].exp[Vpos] = 0;
	}
	ret PolynomialSum<T_int>(This);
}

template<class T_int> inline factor<T_int>
factor<T_int>::operator-(const factor& other) const
{
	ret PolynomialSum<T_int>(*this + other.neg());
}
template<class T_int> inline factor<T_int>
factor<T_int>::operator*(const factor& other) const
{
	ret PolynomialMultiply<T_int>({ *this, other });
}
template<class T_int> inline factor<T_int>&
factor<T_int>::operator-=(const factor& other)
{
	*this = *this - other;
	ret *this;
}
template<class T_int> inline factor<T_int>&
factor<T_int>::operator*=(const factor& other)
{
	*this = *this * other;
	ret *this;
}

template<class T_int> inline FACTOR<T_int>
FACTOR<T_int>::operator-(const FACTOR& other) const
{
	ret To1V(ToXV(*this) - ToXV(other));
}
template<class T_int> inline FACTOR<T_int>
FACTOR<T_int>::operator*(const FACTOR& other) const
{
	ret To1V(ToXV(*this) * ToXV(other));
}
template<class T_int> inline FACTOR<T_int>&
FACTOR<T_int>::operator-=(const FACTOR& other)
{
	*this = *this - other;
	ret *this;
}
template<class T_int> inline FACTOR<T_int>&
FACTOR<T_int>::operator*=(const FACTOR& other)
{
	*this = *this * other;
	ret *this;
}

// frazioni
template<typename T> T ObjectOperations
(wstring& errcode, tensor<T> list, tensor<wstring> ops, wstring disposition = L"");
template<class T = long double>class Fraction
{
public:
	polynomial<T> num, den;

	Fraction() :
		num(polynomial<T>{ { { 0, tensor<int>(Variables.size(), 0) } } }),
		den(polynomial<T>{ { { 1, tensor<int>(Variables.size(), 0) } } })
	{}
	Fraction(polynomial<T> numerator) :
		num(numerator),
		den(polynomial<T>{ { { 1, tensor<int>(Variables.size(), 0) } } })
	{}
	Fraction(polynomial<T> numerator, polynomial<T> denominator) :
		num(numerator), den(denominator) {}

	Fraction extend()
	{
		num = { PolynomialMultiply<T>(num) };
		den = { PolynomialMultiply<T>(den) };
		ret *this;
	}
	Fraction derivate(size_t Vpos) const
	{
		Fraction derivative{
			{ num[0].derivate(Vpos) * den[0] - num[0] * den[0].derivate(Vpos) },
			{ den[0] * factor<T>(den[0]) }
		};
		bool empty{ true };
		for (const auto& term : derivative.num)
		{
			if (!term.empty())
			{
				empty = false;
				break;
			}
		}
		if (empty)
		{
			derivative.num = { { { 0, tensor<int>(Variables.size(), 0) } } };
		}
		ret derivative;
	}

	Fraction operator+(const Fraction& other) const
	{
		Fraction res;
		res.num = {
			PolynomialMultiply<T>(num + other.den) -
			PolynomialMultiply<T>(other.num + den).neg()
		};
		res.den = { PolynomialMultiply<T>(den + other.den) };
		ret res;
	}
	Fraction operator+=(const Fraction& other)
	{
		*this = *this + other;
		ret *this;
	}
	Fraction operator-(const Fraction& other) const
	{
		Fraction res;
		res.num = {
			PolynomialMultiply<T>(num + other.den) -
			PolynomialMultiply<T>(other.num + den)
		};
		res.den = { PolynomialMultiply<T>(den + other.den) };
		ret res;
	}
	Fraction operator-=(const Fraction& other)
	{
		*this = *this - other;
		ret *this;
	}

	Fraction operator*(const Fraction& other) const
	{
		Fraction res;
		res.num = { PolynomialMultiply<T>(num + other.num) };
		res.den = { PolynomialMultiply<T>(den + other.den) };
		ret res;
	}
	Fraction operator*=(const Fraction& other)
	{
		*this = *this * other;
		ret *this;
	}
	Fraction invert()
	{
		Fraction res;
		res.num = den;
		res.den = num;
		ret res;
	}
	Fraction operator/(const Fraction& other) const
	{
		Fraction res;
		res.num = { PolynomialMultiply<T>(num + other.den) };
		res.den = { PolynomialMultiply<T>(den + other.num) };
		ret res;
	}
	Fraction operator/=(const Fraction& other)
	{
		*this = *this / other;
		ret *this;
	}

	T operator()(tensor<long double> params) const
	{
		T res{ 1 };
		for (size_t i = 0; i < num.size(); ++i)
		{
			res *= num[i](params);
		}
		for (size_t i = 0; i < den.size(); ++i)
		{
			res /= den[i](params);
		}
		ret res;
	}
	bool operator==(const Fraction& other) const
	{
		ret num == other.num and den == other.den;
	}

	wstring str()
	{
		// frazione semplice
		wstring output{ num.str() };
		if (
			den == polynomial<T>{ { {
					1, tensor<int>(Variables.size(), 0)
				} } }
		)
		{
			ret output;
		}
		
		// frazione complicata
		if (output.find(L'+') != wstring::npos or
			output.find(L'-') != wstring::npos)
		{
			output = L'(' + output + L')';
		}
		output += L" / " + den.str();
		
		ret output;
	}

	friend wostream& operator<<(wostream& os, const Fraction& obj)
	{
		os << obj.str();
		ret os;
	}
};
static void ClearArea(COORD WinCenter, COORD Dimensions);
template<typename T> void GeneralizedHeapify(tensor<T>& arr, int n, int i)
{
	int largest{ i }, left{ 2 * i + 1 }, right{ 2 * i + 2 };
	if (left < n and arr[left] > arr[largest])
	{
		largest = left;
	}
	if (right < n and arr[right] > arr[largest])
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		GeneralizedHeapify(arr, n, largest);
	}
}
template<typename T> void GeneralizedHeapSort(tensor<T>& arr)
{
	auto n{ arr.size() };
	for (ptrdiff_t i = n / 2 - 1; i >= 0; --i)
	{
		GeneralizedHeapify(arr, n, i);
	}
	for (ptrdiff_t i = n - 1; i > 0; --i)
	{
		swap(arr[0], arr[i]);
		GeneralizedHeapify(arr, i, 0);
	}
}
class key : public tensor<int>
{
public:
	using tensor<int>::tensor;

	key(tensor<int> val)
	{
		this->count = 0;
		for (const auto& el : val) *this << el;
	}

	// nuovi operatori di confronto
	_NODISCARD inline bool operator<(const tensor& other) const override
	{
		// base
		if (*this == other)
		{
			ret false;
		}

		// iterazione
		auto min_size{ min(this->size(), other.size()) };
		for (size_t i = 0; i < min_size; ++i)
		{
			if ((*this)[i] == other[i]) continue;
			if ((*this)[i] < other[i]) ret true;
			if ((*this)[i] > other[i]) ret false;
		}

		// eccezione
		ret this->size() < other.size();
	}
	_NODISCARD inline bool operator<=(const tensor& other) const override
	{
		ret *this < other or *this == other;
	}
	_NODISCARD inline bool operator>(const tensor& other) const override
	{
		ret !(*this < other) and *this != other;
	}
	_NODISCARD inline bool operator>=(const tensor& other) const override
	{
		ret !(*this < other);
	}
};
class Expression
{
private:
	bool activator;

	_STD map<key, wstring> terms{ { {}, L"" } };
	tensor<key> lines, lister{ {} };

	tensor<COORD> FractionLinesPos;
	tensor<short> FractionLinesLenght;

	_STD map<key, COORD> dimensions, positions;

public:
	Expression() : activator(false) {};

	bool contains(key index) const
	{
		for (size_t i = 0; i < lister; ++i)
		{
			if (lister[i] == index)
			{
				ret true;
			}
		}
		ret false;
	}

	void clean()
	{
		// controllo sul nodo maggiore
		tensor<key> keys, ops;
		if (terms.find({}) != terms.end())
		{
			terms.erase(key());
		}

		// ricerca nodi non terminali
		for (const auto& item : lister)
		{
			auto term{ item };
			if (terms.find(item + 0) != terms.end())
			{
				for (;;)
				{
					keys << term;
					if (term.empty())
					{
						break;
					}
					term--;
				}
			}
		}

		// prima eliminazione
		for (const auto& Key : keys)
		{
			if (terms.find(Key) != terms.end())
			{
				terms.erase(Key);
			}
		}
		keys.clear();

		// ricerca nodi sbagliati
		for (const auto& line : lines)
		{
			for (int Last = 2; contains(line + Last); ++Last)
			{
				auto Tensor{ line + Last };
				if (terms.find(Tensor) != terms.end())
				{
					keys << Tensor;
				}
				ops << Tensor;
			}
		}

		// seconda eliminazione
		for (const auto& Key : keys)
		{
			terms.erase(Key);
		}
		for (const auto& op : ops)
		{
			for (size_t i = 0; i < lister; ++i)
			{
				if (lister[i] == op)
				{
					lister.erase(lister.begin() + i);
				}
			}
		}
	}

	tensor<key> underbranch(key node) const
	{
		tensor<key> output;
		if (!contains(node))
		{
			ret {};
		}

		for (int Last = 0; contains(node + Last); ++Last)
		{
			output << node + Last;
		}
		ret output;
	}
	
	void Insert(key where, wstring Num = L"", wstring Den = L"@")
	{
		// ottenimento ramo principale
		activator = true;
		key branch{ where };
		branch--;

		// iterazione per trovare elementi del ramo
		for (auto& ind : lister)
		{
			// esclusione elementi maggiori
			if (ind <= branch)
			{
				continue;
			}

			// esclusione elementi di rami diversi
			bool Continue{ false };
			for (size_t i = 0; i < branch.size(); ++i)
			{
				if (ind[i] != branch[i])
				{
					Continue = true;
					break;
				}
			}
			if (Continue)
			{
				continue;
			}

			// spostamento elementi che seguono la posizione in avanti
			if (ind[branch.size()] >= where.last())
			{
				auto old{ ind };
				ind[branch.size()]++;

				// spostamento delle linee di frazione
				for (auto& line : lines)
				{
					if (line == old)
					{
						line = ind;
						break;
					}
				}

				// spostamento anche nei nodi terminali
				if (terms.find(old) != terms.end())
				{
					auto temp{ terms[old] };
					terms.erase(old);
					terms[ind] = temp;
				}
			}
		}

		// inserimento stringa
		if (Den == L"@")
		{
			lister << where;
			terms[where] = Num;
		}

		// inserimento frazione
		else
		{
			lines << where;
			lister << where << where + 0 << where + 1;
			lister << where + 0 + 0 << where + 1 + 0;
			terms[where + 0 + 0] = Num;
			terms[where + 1 + 0] = Den;
		}
		
		// pulizia
		clean();
	}

	void Remove(key node)
	{
		// rimozione di tutti i termini sottostanti al nodo
		auto New{ node };
		bool ExecLoop{ true };
		tensor<tensor<bool>> shifted{
			tensor<bool>(lines.size(), false), tensor<bool>(lister.size(), false)
		};
		auto remove{ shifted };
		tensor<tensor<key>> container{ lines, lister };
	loop:
		for (size_t i = 0; i < container[ExecLoop]; ++i)
		{
			// caso semplice
			if (container[ExecLoop][i].size() < New.size())
			{
				continue;
			}

			// controllo corrispondenza
			bool ContinueLoop{ false };
			for (size_t j = 0; j < New; ++j)
			{
				// shift
				if (j == New.size() - 1 and New[j] < container[ExecLoop][i][j])
				{
					shifted[ExecLoop][i] = true;
					ContinueLoop = true;
					break;
				}

				// ricerca
				if (New[j] != container[ExecLoop][i][j])
				{
					ContinueLoop = true;
					break;
				}
			}
			if (ContinueLoop)
			{
				continue;
			}

			remove[ExecLoop][i] = true;
		}

		if (ExecLoop)
		{

			// rimozione nei termini
			for (size_t i = 0; i < container[1]; ++i)
			{
				if (terms.find(container[1][i]) != terms.end() and remove[1][i])
				{
					terms.erase(container[1][i]);
				}
			}

			// // esecuzione shift nei termini

			// ordinamento chiavi
			tensor<key> ListOfKeys;
			for (size_t i = 0; i < container[1]; ++i)
			{
				if (shifted[1][i])
				{
					ListOfKeys << container[1][i];
				}
			}
			if (ListOfKeys > 1)
			{
				GeneralizedHeapSort(ListOfKeys);
			}

			// sostituzione
			for (size_t i = 0; i < ListOfKeys; ++i)
			{
				if (terms.find(ListOfKeys[i]) != terms.end())
				{
					auto location{ ListOfKeys[i] };
					auto temp{ terms[location] };
					terms.erase(location);
					location[node.size() - 1]--;
					terms[location] = temp;
				}
			}

			// //
		}
		
		for (
			ptrdiff_t i = container[ExecLoop].size() - 1;
			i >= 0;
			--i
			)
		{
			// rimozione
			if (remove[ExecLoop][i])
			{
				container[ExecLoop].erase(
					container[ExecLoop].begin() + i
				);
				continue;
			}
			
			// salto
			if (shifted[ExecLoop][i])
			{
				container[ExecLoop][i][node.size() - 1]--;
			}
		}

		// ridirezionamento
		if (ExecLoop)
		{
			ExecLoop = false;
			goto loop;
		}

		lines = container[0];
		lister = container[1];
	}

	COORD GetDimensions(key node = {})
	{
		// fine ricorsione
		if (terms.find(node) != terms.end())
		{
			auto str{ terms[node] };
			auto size{ str.size() };
			if (BOOLALPHA)
			{
				for (ptrdiff_t i = 0; i < (int)str.size() - 1; ++i)
				{
					if (str.at(i) == L'^' and isdigit(str.at(i + 1)))
					{
						size--;
					}
				}
			}
			ret dimensions[node] = COORD{ short(size), 1 };
		}

		// caso con frazione
		bool fraction{ false };
		for (const auto& line : lines)
		{
			if (line == node)
			{
				fraction = true;
				break;
			}
		}
		if (fraction)
		{
			// ricorsione
			COORD num{ GetDimensions(node + 0) }, den{ GetDimensions(node + 1) };
			COORD result{ max(num.X, den.X), short(num.Y + den.Y + 1) };

			// aumento dimensione se la frazione è di ordine superiore
			if (terms.find(node + 0 + 0) == terms.end() or
				terms.find(node + 1 + 0) == terms.end())
			{
				result.X += 2;
			}

			// assegnazione
			dimensions[node] = result;
			ret result;
		}

		// caso con operazioni di termini diversi
		auto branch{ underbranch(node) };
		if (branch.empty())
		{
			ret COORD();
		}
		tensor<COORD> branchcoords;
		for (const auto& index : branch)
		{
			branchcoords << GetDimensions(index);
		}

		// calcolo coordinate con le formule
		COORD result{};
		for (const auto& coord_ : branchcoords)
		{
			if (result.Y < coord_.Y)
			{
				result.Y = coord_.Y;
			}
		}
		for (int i = -1; i <= branch.last().last(); ++i)
		{
			key Key{ node + i };
			if (i >= 0)
			{
				result.X += dimensions[branch[i]].X;
			}
		}

		dimensions[node] = result;
		ret result;
	}

	void GetPositions()
	{
		// calcolo dimensioni
		if (dimensions.empty() or activator)
		{
			dimensions.clear();
			GetDimensions();
		}
		if (dimensions.empty())
		{
			ret;
		}

		// reset
		positions.clear();
		FractionLinesPos.clear();
		FractionLinesLenght.clear();

		// iterazione su ogni singolo nodo
		key node;
		positions[{}] = { 0, 0 };
		if (!activator)
		{
			ret;
		}
		for (;;)
		{
			// ottenimento dati calcolati in precedenza
			auto directordim{ dimensions[node] };
			auto directorpos{ positions[node] };

			// caso con una frazione
			bool fraction{ false };
			for (const auto& index : lines)
			{
				if (index == node)
				{
					fraction = true;
					break;
				}
			}
			if (fraction)
			{
				// calcolo posizioni
				positions[node + 0] = COORD{
					short(
						directorpos.X +
						(directordim.X - dimensions[node + 0].X) / 2
					),
					directorpos.Y
				};
				positions[node + 1] = COORD{
					short(
						directorpos.X +
						(directordim.X - dimensions[node + 1].X) / 2
					),
					short(directorpos.Y + dimensions[node + 0].Y + 1)
				};

				// creazione delle linee di frazione
				FractionLinesPos << COORD{
					directorpos.X, short(directorpos.Y + dimensions[node + 0].Y)
				};
				FractionLinesLenght << directordim.X;
			}

			// caso con sequenza di operazioni
			else
			{
				bool start{ true };
				auto branch{ underbranch(node) };
				tensor<short> lenghts(branch.size()), widths(branch.size());

				// calcolo ordinate
				for (size_t i = 0; i < branch; ++i)
				{
					widths[i] = (directordim.Y - dimensions[branch[i]].Y) / 2;
				}

				// calcolo ascisse a intervalli
				for (size_t i = 0; i < branch; ++i)
				{
					lenghts[i] = (start ? 0 : 1) + dimensions[branch[i]].X;
				}

				// calcolo ascisse dirette
				for (size_t i = 1; i < lenghts; ++i)
				{
					lenghts[i] += lenghts[i - 1];
				}

				// assegnazione
				for (size_t i = 0; i < branch; ++i)
				{
					positions[branch[i]] = COORD{
						short(directorpos.X + lenghts[i] - dimensions[branch[i]].X),
						short(directorpos.Y + widths[i])
					};
				}
			}

			// scelta nodo successivo
			if (terms.find(node) != terms.end())
			{
				node.last()++;
				continue;
			}
			if (contains(node) or node.empty())
			{
				node << 0;
				continue;
			}
			if (node == 1)
			{
				break;
			}
			node--;
			node.last()++;
		}
	}

	void out(COORD StarterCoord = { -1, -1 })
	{
		// console
		setlocale(LC_ALL, "");
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
		wcout.imbue(locale(""));
		HIDECURSOR;

		// parametro di default
		_GetCursorPos();
		if (StarterCoord.X == -1)
		{
			StarterCoord = csbi.dwCursorPosition;
		}
		auto SizeLimit{ csbi.dwSize };

		// calcolo dimensioni
		if (positions.empty() or activator)
		{
			GetPositions();
		}
		if (positions.empty())
		{
			ret;
		}
		activator = false;

		// output linee di frazione
		SetConsoleTextAttribute(hConsole, 10);
		for (size_t i = 0; i < FractionLinesPos; ++i)
		{
			FractionLinesPos[i].X += StarterCoord.X;
			FractionLinesPos[i].Y += StarterCoord.Y;
			
			// testo fuori dalla console
			if (FractionLinesPos[i].X + FractionLinesLenght[i] >= SizeLimit.X
				or FractionLinesPos[i].Y >= SizeLimit.Y)
			{
				continue;
			}

			SetConsoleCursorPosition(hConsole, FractionLinesPos[i]);
			wcout << wstring(FractionLinesLenght[i], L'-') << L'\n';
		}

		// output stringhe
		ResetAttribute();
		for (const auto& Key : lister)
		{
			// filtro
			if (terms.find(Key) == terms.end())
			{
				continue;
			}

			// calcolo posizione
			auto pos{ positions[Key] };
			pos.X += StarterCoord.X;
			pos.Y += StarterCoord.Y;

			// testo fuori dalla console
			if (pos.X + terms[Key].size() >= SizeLimit.X or pos.Y >= SizeLimit.Y)
			{
				continue;
			}

			// output
			SetConsoleCursorPosition(hConsole, pos);
			auto write{ terms[Key] };
			wcout << ElabExponents(write) << L'\n';
		}

		SetConsoleCursorInfo(hConsole, &cursor);
	}

	COORD CursorPosition(key at)
	{
		// calcolo dimensioni
		if (positions.empty() or activator)
		{
			GetPositions();
		}
		if (positions.empty())
		{
			ret COORD();
		}
		activator = false;

		if (at.last() < 0)
		{
			at.last() = 0;
			ret COORD{
				short(positions[at].X),
				short(positions[at].Y + dimensions[at].Y / 2)
			};
		}

		ret COORD{
			short(positions[at].X + dimensions[at].X),
			short(positions[at].Y + dimensions[at].Y / 2)
		};
	}
	
	Fraction<> in()
	{
		// carattere per le frecce
		using type = char;
		int EscapeCode, diff{};
		if constexpr (is_same_v<type, char>)
		{
			EscapeCode = -32;
		}
		else
		{
			EscapeCode = 224;
		}

		//// blocco temporaneo di debug
		// Insert({ 0 }, L"(");
		// Insert({ 1 }, L"2x", L"y+3");
		// Insert({ 2 }, L" - ");
		// Insert({ 3 }, L"1", L"2");
		// Insert({ 4 }, L"4xy + ");
		Insert({ 0 }, L"", L"");
		Insert({ 0, 0, 0 }, L"2", L"3");
		Insert({ 0, 1, 0 }, L"25x^2", L"3");
		// Insert({ 6 }, L") * (");
		// Insert({ 7 }, L"2", L"5x");
		// Insert({ 8 }, L")^2");
		////

		// aggiunta di spazio
		_GetCursorPos();
		wcout << wstring(csbi.dwSize.Y, L'\n');
		COORD begin{};
		SetConsoleCursorPosition(hConsole, begin);
		out(begin);
		bool arrow{ false };
		key CursorIndex({ 0 });

		// ciclo dei comandi
		for (;;)
		{
			// aggiunta frazione
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
				GetAsyncKeyState(VK_MENU) & 0x8000)
			{
				// blocco
				while (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
					GetAsyncKeyState(VK_MENU) & 0x8000);

				// aggiunta termini
				CursorIndex.last()++;
				lines << CursorIndex;
				lister << CursorIndex;
				lister << CursorIndex + 0 << CursorIndex + 0 + 0;
				lister << CursorIndex + 1 << CursorIndex + 1 + 0;

				// pulizia e aggiornamento cursore
				terms[CursorIndex + 1 + 0] = L"";
				CursorIndex << 0 << 0;
				terms[CursorIndex] = L"";
				activator = true;
				clean();
			}

			// switch boolalpha
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
				GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				// blocco
				while (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
					GetAsyncKeyState(VK_SHIFT) & 0x8000);

				BOOLALPHA = !BOOLALPHA;
				activator = true;
			}

			// tasti
			if (_kbhit())
			{
				// lettura
				char c = _getch();

				// carattere illegale
				if (c == L'@')
				{
					continue;
				}

				// frecce
				if (c == EscapeCode)
				{
					arrow = true;
					continue;
				}
				if (arrow)
				{
					switch (c)
					{
						// freccia sinistra
					case L'K':
					{
						bool ExecuteMove{ false };
						if (terms.find(CursorIndex) != terms.end())
						{
							// spostamento all'interno di un termine
							wstring current{ terms[CursorIndex] };
							ElabExponents(current);
							if (diff < current.size())
							{
								diff++;
								break;
							}

							// cursore all'inizio
							if (CursorIndex == key{ 0 })
							{
								break;
							}

							// cursore all'inizio di numeratore o denominatore
							if (CursorIndex.last() == 0)
							{
								ExecuteMove = true;
							}
						}

						if (CursorIndex.last() < 0 or ExecuteMove)
						{
							// spostamento verso l'esterno della frazione
							if (CursorIndex[CursorIndex.size() - 2] == 0)
							{
								CursorIndex[CursorIndex.size() - 2] = 1;
								CursorIndex--;
								CursorIndex = underbranch(CursorIndex).last();
								diff = 0;
								break;
							}

							// spostamento verso il numeratore
							if (CursorIndex[CursorIndex.size() - 2] == 1)
							{
								CursorIndex -= 2;
								CursorIndex.last()--;
								diff = 0;
								break;
							}
						}

						// spostamento verso il denominatore
						CursorIndex.last()--;
						CursorIndex = underbranch(CursorIndex + 0).last();
						diff = 0;
					}
					break;

					// freccia destra
					case L'M':
					{
						if (terms.find(CursorIndex) != terms.end())
						{
							// spostamento all'interno di un termine
							if (diff > 0)
							{
								diff--;
								break;
							}

							// cursore alla fine
							if (CursorIndex == underbranch({}).last())
							{
								break;
							}

							// cursore alla fine di numeratore o denominatore
							auto branch{ CursorIndex };
							branch--;
							if (CursorIndex == underbranch(branch).last())
							{
								// spostamento verso il numeratore
								if (CursorIndex[CursorIndex.size() - 2] == 1)
								{
									CursorIndex[CursorIndex.size() - 2] = 0;
									CursorIndex.last() = 0;
									if (terms.find(CursorIndex) == terms.end())
									{
										CursorIndex.last() = -1;
										diff = 0;
									}
									else
									{
										wstring current{ terms[CursorIndex] };
										ElabExponents(current);
										diff = current.size();
									}
									break;
								}

								// spostamento verso l'esterno della frazione
								if (CursorIndex[CursorIndex.size() - 2] == 0)
								{
									CursorIndex -= 2;
									CursorIndex.last()++;

									wstring current{ terms[CursorIndex] };
									ElabExponents(current);
									diff = current.size();
									break;
								}
							}
						}

						// spostamento verso il denominatore
						CursorIndex.last()++;
						CursorIndex << 1 << 0;
						if (terms.find(CursorIndex) == terms.end())
						{
							CursorIndex.last() = -1;
						}
						else
						{
							wstring current{ terms[CursorIndex] };
							ElabExponents(current);
							diff = current.size();
						}
					}
					break;

					// canc
					case L'S':

						// rimozione carattere dall'ultimo termine
						if (terms.find(CursorIndex) != terms.end())
						{
							if (!terms[CursorIndex].empty())
							{
								terms[CursorIndex].pop_back();
								if (diff > 0)
								{
									diff--;
								}
								if (!terms[CursorIndex].empty())
								{
									break;
								}
							}
						}

						// ctrl + canc
					case -109:

						// nulla da cancellare
						if (CursorIndex.last() >=
							underbranch(key(CursorIndex) -= 1).last().last())
						{
							break;
						}

						// rimozione
						CursorIndex.last()++;
						Remove(CursorIndex);
						break;

						// ctrl + freccia sinistra
					case L's':
						if (terms.find(CursorIndex) != terms.end())
						{
							wstring current{ terms[CursorIndex] };
							ElabExponents(current);
							diff = current.size();
						}

						break;

						// ctrl + freccia destra
					case L't':
						if (terms.find(CursorIndex) != terms.end())
						{
							diff = 0;
						}

						break;

						// spostamento da denominatore a numeratore
					case L'H':
					{
						if (CursorIndex.size() < 2)
						{
							continue;
						}
						CursorIndex[CursorIndex.size() - 2] = 0;
						CursorIndex.last() = 0;

						wstring current{ terms[CursorIndex] };
						ElabExponents(current);
						if (diff > current.size())
						{
							diff = current.size();
						}
					}
					break;

					// spostamento da numeratore a denominatore
					case L'P':
					{
						if (CursorIndex.size() < 2)
						{
							continue;
						}
						CursorIndex[CursorIndex.size() - 2] = 1;
						CursorIndex.last() = 0;

						wstring current{ terms[CursorIndex] };
						ElabExponents(current);
						if (diff > current.size())
						{
							diff = current.size();
						}
					}
					break;
					}

					arrow = false;
					continue;
				}

				// switch tasti
				switch (c)
				{
					// termine programma
				case L'.':
					ret Fraction<>{ polynomial<>{ { { 0, { -3 } } } }, {} };

					// backspace
				case L'\b':

					// rimozione carattere dall'ultimo termine
					if (terms.find(CursorIndex) != terms.end())
					{
						if (terms[CursorIndex].empty())
						{
							// rimozione termine
							terms.erase(CursorIndex);
							for (ptrdiff_t i = lister.size() - 1; i >= 0; --i)
							{
								if (lister[i] == CursorIndex)
								{
									lister.erase(lister.begin() + i);
									break;
								}
							}

							// aggiornamento
							CursorIndex.last()--;
							diff = 0;
						}
						else
						{
							terms[CursorIndex].pop_back();
							if (diff > 0)
							{
								diff--;
							}
							break;
						}
					}

					// ctrl + backspace
				case 127:

					// nulla
					if (CursorIndex.last() < 0)
					{
						break;
					}

					// rimozione
					Remove(CursorIndex);
					CursorIndex.last()--;

					// aggiunta di un posto per il cursore
					if (CursorIndex.last() < 0)
					{
						CursorIndex.last()++;
						lister << CursorIndex;
						terms[CursorIndex] = L"";
					}
					break;

					// conferma
				case L'\r': ret Export();

					// aggiunta carattere
				default:

					// aggiunta in un termine già esistente
					if (terms.find(CursorIndex) != terms.end())
					{
						terms[CursorIndex] += c;
						break;
					}

					// aggiunta di un nuovo termine
					CursorIndex.last()++;
					lister << CursorIndex;
					terms[CursorIndex] = wstring(1, c);
				}

				// pulizia oggetto e aggiornamento
				clean();
				activator = true;
				_GetCursorPos();
			}

			if (activator)
			{
				// pulizia console e scrittura
				ClearArea(
					{
						short(csbi.dwSize.X + begin.X / 2),
						short(dimensions[{}].Y / 2 + begin.Y)
					},
					{
						short(csbi.dwSize.X - begin.X / 2),
						short(dimensions[{}].Y / 2)
					}
				);
				out(begin);
			}
				
			// posizionamento del cursore
			auto position{ CursorPosition(CursorIndex) };
			position.X += begin.X - diff;
			position.Y += begin.Y;
			SetConsoleCursorPosition(hConsole, position);
		}
	}

	Fraction<> Export()
	{
		// eliminazione spazi bianchi
		for (auto& term : terms)
		{
			auto& str{ term.second };
			for (ptrdiff_t i = str.size() - 1; i >= 0; --i)
			{
				if (str.at(i) == L' ' or str.at(i) == L'\t')
				{
					str.erase(i, 1);
				}
			}
		}

		// semplificazione profondità
		int sizemax, index;
		for (;;)
		{
			if (lines.empty())
			{
				break;
			}

			// ricerca di una frazione doppia
			sizemax = index = 0;
			for (size_t i = 0; i < lines; ++i)
			{
				if (sizemax < lines[i].size())
				{
					sizemax = lines[i].size();
					index = i;
				}
			}
			if (sizemax == 1)
			{
				break;
			}
			auto main{ lines[index] };
			int delta{};
			main -= 2;

			// salvataggio numeratore e denominatore
			tensor<tensor<key>> fractal{ {}, {} };
			for (const auto& Key : terms)
			{
				// caso semplice
				if (Key.first.size() < main)
				{
					continue;
				}

				// accertamento nodo appartenente
				bool Continue{ false };
				for (size_t i = 0; i < main; ++i)
				{
					if (Key.first[i] != main[i])
					{
						Continue = true;
						break;
					}
				}
				if (Continue)
				{
					continue;
				}

				fractal[Key.first[main.size()]] << Key.first;
			}
			
			// operazioni iniziali
			GeneralizedHeapSort(fractal[0]);
			GeneralizedHeapSort(fractal[1]);
			Insert(main, L"(");

			// aggiunta numeratore
			bool skip{ false };
			for (size_t i = 0; i < fractal[0]; ++i)
			{
				if (skip)
				{
					skip = false;
					continue;
				}

				// termine semplice
				delta++;
				main.last()++;
				if (fractal[0][i] == sizemax)
				{
					fractal[0][i][main.size() - 1] += delta;
					Insert(main, terms[fractal[0][i]]);
					continue;
				}

				// frazione
				fractal[0][i][main.size() - 1] += delta;
				fractal[0][i + 1][main.size() - 1] += delta;
				Insert(main, terms[fractal[0][i]], terms[fractal[0][i + 1]]);
				skip = true;
			}

			// aggiunta denominatore
			delta++;
			main.last()++;
			Insert(main, L")/(");
			skip = false;
			for (size_t i = 0; i < fractal[1]; ++i)
			{
				if (skip)
				{
					skip = false;
					continue;
				}

				// termine semplice
				delta++;
				main.last()++;
				if (fractal[1][i] == sizemax)
				{
					fractal[1][i][main.size() - 1] += delta;
					Insert(main, terms[fractal[1][i]]);
					continue;
				}

				// frazione
				fractal[1][i][main.size() - 1] += delta;
				fractal[1][i + 1][main.size() - 1] += delta;
				Insert(main, terms[fractal[1][i]], terms[fractal[1][i + 1]]);
				skip = true;
			}

			// operazioni finali
			main.last()++;
			Insert(main, L")");
			main.last()++;
			Remove(main);
			clean();
		}



		// traduci tutte le frazioni (nuova funzione molto utile)

		// per ogni termine polinomiale

			// gestisci gli esponenti
			
			// suddividilo in operatori e polinomi tradotti

		// usa ObjectOperations

		// cancella gli inputer vecchi e sostituiscili

		ret Fraction<>{};
	}
};
tensor_t PrimeNumbers;
_STD map<int, wstring> CalculatedData;

// stream
struct Console
{
	wstring Text;
	WORD Attribute{ 15 };

	void log() const
	{
		SetConsoleTextAttribute(hConsole, Attribute);
		wcout << Text;
		ResetAttribute();
	}

	bool operator!=(const Console& other) const
	{
		ret Text != other.Text and Attribute != other.Attribute;
	}
	friend wostream& operator<<(wostream& wos, const Console& T)
	{
		SetConsoleTextAttribute(hConsole, T.Attribute);
		wos << T.Text;
		ResetAttribute();
		ret wos;
	}
};

class ConsoleStream : public tensor<Console>
{
public:

	// costruttori e operatori
	ConsoleStream() {}
	ConsoleStream(initializer_list<Console> init)
	{
		for (const auto& item : init)
		{
			(*this) << item;
		}
	}
	ConsoleStream operator+(ConsoleStream other) const
	{
		auto This{ *this };
		for (const auto& item : other)
		{
			This << item;
		}
		ret This;
	}

	inline void output() const
	{
		for (int i = 0; i < this->size(); ++i)
		{
			wcout << (*this)[i];
		}
	}
	inline void log()
	{
		this->output();
		this->clear();
	}
	friend wostream& operator<<(wostream& wos, const ConsoleStream& T)
	{
		for (int i = 0; i < T.size(); ++i)
		{
			wos << T[i];
		}
		ret wos;
	}
};
ConsoleStream ConsoleText;

// matrici
static void SendCtrlPlusMinus(bool plus);
static ptrdiff_t intpow(ptrdiff_t base, int exp);
template<typename _Ty = long double> class Matrix : public tensor<tensor<_Ty>>
{
public:
	Matrix() {}
	using tensor<tensor<_Ty>>::tensor;

	int output(
		COORD SelectedElement = { -1, -1 },
		int& extension = __NULL__,
		WORD Attribute = 15
	) const
	{

		// aggiunta di spazio
		_GetCursorPos();
		auto size{ this->size() };
		auto begin{ csbi.dwCursorPosition };
		wcout << wstring(4 * size + 1, L'\n');
		_GetCursorPos();
		if (csbi.dwCursorPosition.Y >= begin.Y)
		{
			begin.Y -= 4 * size + 1 - csbi.dwCursorPosition.Y + begin.Y;
		}
		SetConsoleCursorPosition(hConsole, begin);
		csbi.dwCursorPosition = begin;

		// calcolo stringhe e trasposizione matrice stringhe
		tensor<tensor<wstring>> StrMatrix(size), StrDenominators(size);
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < (*this)[i]; ++j)
			{
				auto element{ (*this)[j][i] };

				// elemento intero
				if (SelectedElement.Y >= 0 or integer(element))
				{
					StrDenominators[i] << L"";
					StrMatrix[i] << to_wstring((int)element);
					continue;
				}

				// elemento decimale
				int I{ -1 };
				for (int k = 2; k < 1'000; ++k)
				{
					if (integer(k * element))
					{
						I = k;
						break;
					}
				}
				if (I == -1)
				{
					// elemento sottoforma di numero decimale
					StrMatrix[i] << to_wstring(element);
					StrDenominators[i] << L"";
				}
				else
				{
					// elemento sottoforma di frazione
					StrMatrix[i] << to_wstring(int(element * I));
					StrDenominators[i] << to_wstring(I);
				}
			}
		}

		// correzione lunghezza stringhe
		int sum{};
		for (size_t i = 0; i < size; ++i)
		{
			auto column{ StrMatrix[i] };
			auto denom{ StrDenominators[i] };
			int maxlenght{ 3 };

			// calcolo della lunghezza massima e correzione
			for (auto& num : column)
			{
				if (num.size() > maxlenght)
				{
					maxlenght = num.size();
				}
			}
			for (auto& den : denom)
			{
				if (den.size() > maxlenght)
				{
					maxlenght = den.size();
				}
			}
			for (auto& num : column)
			{
				if (num.size() < maxlenght)
				{
					int TotalLenght = maxlenght - num.size();
					num = wstring(TotalLenght / 2, L' ') +
						num + wstring(TotalLenght - TotalLenght / 2, L' ');
				}
			}
			for (auto& den : denom)
			{
				if (den.size() < maxlenght)
				{
					int TotalLenght = maxlenght - den.size();
					den = wstring(TotalLenght / 2, L' ') +
						den + wstring(TotalLenght - TotalLenght / 2, L' ');
				}
			}

			StrMatrix[i] = column;
			StrDenominators[i] = denom;
			sum += maxlenght;
		}
		sum += size * 2;

		// calcolo delle righe con e senza frazioni
		tensor<bool> HaveTheyFractions(size, false);
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				if (StrDenominators[j][i].at(
					(StrDenominators[j][i].size() - 1) / 2) != L' '
					)
				{
					HaveTheyFractions[i] = true;
					break;
				}
			}
		}
		int row{};
		size_t index{};

		// iterazione e stampa matrice
		int line{};
		if (extension)
		{
			extension = sum + 3;
		}
		for (size_t i = 0; index <= 2 * size; ++i)
		{

			// inizio e fine matrice
			if (index == 2 * size)
			{
				line = i;
			}
			if (index == 0 or index == 2 * size)
			{
				wcout << L'+' << wstring(sum + 1, L'-') << L'+';
				csbi.dwCursorPosition.Y++;
				SetConsoleCursorPosition(
					hConsole, { begin.X, csbi.dwCursorPosition.Y }
				);
				index++;
				continue;
			}
			wcout << L"| ";

			// calcolo linea di frazione e indice
			if (index % 2 == 0)
			{
				wcout << wstring(sum, L' ') << L'|';
				index++;
				csbi.dwCursorPosition.Y++;
				SetConsoleCursorPosition(
					hConsole, { begin.X, csbi.dwCursorPosition.Y }
				);
				continue;
			}
			if (HaveTheyFractions[(index - 1) / 2])
			{
				row++;
			}
			if (row == 4)
			{
				row = 1;
			}

			// output elemento (la matrice delle stringhe è trasposta)
			for (size_t j = 0; j < size; ++j)
			{
				// evindenziazione cursore
				if (j == SelectedElement.X and (index - 1) / 2 == SelectedElement.Y)
				{
					SetConsoleTextAttribute(hConsole, 12);
				}

				// caso senza frazioni
				auto TempDenominator{ StrDenominators[j][(index - 1) / 2] };
				if (
					!HaveTheyFractions[(index - 1) / 2] or
					(row == 2 and TempDenominator.at(
						(TempDenominator.size() - 1) / 2) == L' ')
					)
				{
					wcout << StrMatrix[j][(index - 1) / 2];
					if (j == SelectedElement.X and
						(index - 1) / 2 == SelectedElement.Y)
					{
						SetConsoleTextAttribute(hConsole, 4);
						wcout << L'.';
					}
					else
					{
						wcout << L' ';
					}
				}

				// caso con almeno una frazione nella riga
				else switch (row)
				{
					// numeratori
				case 1:
					if (
						TempDenominator.at((TempDenominator.size() - 1) / 2)
						== L' ')
					{
						wcout << wstring(
							StrMatrix[j][(index - 1) / 2].size() + 1, L' '
						);
					}
					else
					{
						wcout << StrMatrix[j][(index - 1) / 2] << L' ';
					}
					break;

					// linee di frazione e numeri
				case 2:
					wcout << wstring(StrMatrix[j][(index - 1) / 2].size(), L'-');
					wcout << L' ';
					break;

					// denominatori non nulli
				case 3:
					if (TempDenominator.at(
						(TempDenominator.size() - 1) / 2) == L' ')
					{
						wcout << wstring(
							StrMatrix[j][(index - 1) / 2].size() + 1, L' '
						);
					}
					else
					{
						wcout << StrDenominators[j][(index - 1) / 2] << L' ';
					}
					break;
				}

				SetConsoleTextAttribute(hConsole, Attribute);
				wcout << L' ';
			}
			if (row == 0 or row == 3)
			{
				index++;
			}

			// fine riga
			wcout << L'|';
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(
				hConsole, { begin.X, csbi.dwCursorPosition.Y }
			);
		}

		// riposizionamento cursore
		if (SelectedElement.Y == -2)
		{
			line = max(line, (int)SelectedElement.X);
			begin.Y += line + 1;
		}
		if (SelectedElement.X == -1) begin.X += sum + 3;
		SetConsoleCursorPosition(hConsole, begin);

		__NULL__ = 0;
		ret line;
	}

	bool input(wstring& errcode)
	{
		setlocale(LC_ALL, "");
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
		wcout.imbue(locale(""));
		const int EscapeCode{ -32 };

		// aggiunta di spazio
		_GetCursorPos();
		auto start{ csbi.dwCursorPosition };
		wcout << wstring(29, L'\n');
		_GetCursorPos();
		if (csbi.dwCursorPosition.Y >= start.Y)
		{
			start.Y -= 29 - csbi.dwCursorPosition.Y + start.Y;
		}
		SetConsoleCursorPosition(hConsole, start);
		csbi.dwCursorPosition = start;

		// inizio
		_GetCursorPos();
		COORD begin{ csbi.dwCursorPosition };
		size_t size_s{ 2 };
		tensor<Matrix<_Ty>> Displayed;
		const wstring operatorsAllowed{ L"(+-*/)," };

		tensor<wstring> operators{ L"" };
		wstring ToConvalidate;
		bool Continue{ true }, keep{ false }, skip{ false };

		for (;;)
		{
			if (_kbhit() or (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
				GetAsyncKeyState(VK_MENU) & 0x8000))
			{

				// lettura
				skip = false;
				tensor<long double> unit(size_s, 0);
				int sizemin = size_s, lenght{ 1 }, depth = 2 * size_s + 1;
				char c = _kbhit() ? tolower(_getch()) : L',';

				// termine
				switch (c)
				{
				case L'.': this->clear();
					ret true;
				case L'\r': goto end;
				case L'\b':
					operators.last().empty() ?
						(void)operators-- : operators.last().pop_back();
					if (!ToConvalidate.empty())
					{
						if (Last(ToConvalidate) == L'\'')
						{
							Displayed--;
						}
						ToConvalidate.pop_back();
					}
					if (operators.empty())
					{
						operators = { {} };
					}
					goto output;
				}

				// casi illegali
				if (c == 0 or c == EscapeCode)
				{
					skip = true;
					continue;
				}
				if (operatorsAllowed.find(c) == wstring::npos)
				{
					continue;
				}

				// aggiunta carattere
				if (c != L',')
				{
					operators.last() += c;
					ToConvalidate += c;
					goto output;
				}

				// calcolo dimensioni minime
			input:
				sizemin = 2;
				unit(size_s, 0);
				for (const auto& matrix : Displayed)
				{
					// dimensione minima rispetto alle righe
					int localmin{ 1 };
					for (ptrdiff_t i = size_s - 1; i >= 0; --i)
					{
						if (matrix[i] != unit)
						{
							localmin = i;
							break;
						}
					}
					if (localmin == size_s)
					{
						sizemin = size_s;
						break;
					}

					// dimensione minima rispetto alle colonne
					for (ptrdiff_t i = size_s - 1; i >= 0; --i)
					{
						for (size_t j = 0; j < size_s; ++j)
						{
							if (matrix[j][i] != 0)
							{
								if (localmin < i)
								{
									localmin = i;
								}
								break;
							}
						}
					}

					if (localmin > sizemin)
					{
						sizemin = localmin;
					}
					if (sizemin == size_s)
					{
						break;
					}
				}

				// correzione matrice
				while (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
					GetAsyncKeyState(VK_MENU) & 0x8000);
				if (!keep)
				{
					Displayed << Matrix<_Ty>(size_s, tensor<long double>(size_s, 0));
				}
				{
					// inizio dell'input principale
					auto& inputer{ Displayed.last() };
					Continue = true;
					keep = false;
					HIDECURSOR;

					// inizializzazione
					if (inputer.size() < 2)
					{
						inputer(2);
					}
					Matrix<bool> Signs(inputer.size());
					for (auto& row : inputer)
					{
						row(inputer.size(), 0);
					}
					for (auto& row : Signs)
					{
						row(Signs.size(), POS);
					}
					for (size_t i = 0; i < inputer; ++i)
					{
						for (size_t j = 0; j < inputer[i]; ++j)
						{
							Signs[i][j] = inputer[i][j] < 0;
						}
					}
					if (inputer[0][0] == 0)
					{
						inputer[0][0] = 1;
					}

					bool arrow{ false };
					depth = inputer.output({ 0, 0 }, lenght);
					COORD IndexAccesser{};
					wstring MatrixAtIndex;
					for (;;)
					{
						char C;

						// operatori
						if (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
							GetAsyncKeyState(VK_MENU))
						{
							goto inputend;
						}

						if (_kbhit())
						{
							C = tolower(_getch());

							// casi speciali
							if (C == EscapeCode)
							{
								arrow = true;
								continue;
							}
							if (C <= 0)
							{
								continue;
							}
							if (arrow)
							{
								switch (C)
								{
								case L'h': C = L'w';
									break;
								case L'p': C = L's';
									break;
								case L'm': C = L'd';
									break;
								case L'k': C = L'a';
									break;
								}
								arrow = false;
							}

							// // scelta carattere
							size_t size;

							// casi che non modificano la matrice
							switch (C)
							{
								// wasd per cambiare l'elemento da modificare
							case L'w':
								IndexAccesser.Y =
									(IndexAccesser.Y - 1) % inputer.size();
								break;
							case L's':
								IndexAccesser.Y =
									(IndexAccesser.Y + 1) % inputer.size();
								break;
							case L'a':
								IndexAccesser.X =
									(IndexAccesser.X - 1) % inputer.size();
								break;
							case L'd':
								IndexAccesser.X =
									(IndexAccesser.X + 1) % inputer.size();
								break;
							}

							MatrixAtIndex = to_wstring(
								(int)inputer[IndexAccesser.Y][IndexAccesser.X]
							);

							// casi che modificano la matrice
							switch (C)
							{
								// L'z' riempie la matrice
							case L'z':
							{
								random_device rng;
								mt19937 gen(rng());
								uniform_int_distribution<> dis(-100, 100);
								for (size_t i = 0; i < inputer; ++i)
								{
									for (size_t j = 0; j < inputer[i]; ++j)
									{
										if (inputer[i][j] == 0)
										{
											int rand{ dis(gen) };
											Signs[i][j] = rand < 0;
											inputer[i][j] = rand;
										}
									}
								}
							}
								break;

								// L'r' azzera il determinante
							case L'r':
								inputer.last() = inputer[inputer.size() - 2];
								MatrixAtIndex = to_wstring(
									(int)inputer[IndexAccesser.Y][IndexAccesser.X]
								);
								break;

								// L'\b' cancella un carattere
							case L'\b':
								if (MatrixAtIndex == L"0" and
									Signs[IndexAccesser.Y][IndexAccesser.X])
								{
									Signs[IndexAccesser.Y][IndexAccesser.X] = POS;
									break;
								}
								if (MatrixAtIndex.size() == 1)
								{
									MatrixAtIndex = L"0";
									break;
								}
								MatrixAtIndex.pop_back();
								break;

								// ctrl + alt + L'\b' cancella tutto
							case 127:
								if (GetAsyncKeyState(VK_MENU) & 0x8000)
								{
									for (size_t i = 0; i < inputer; ++i)
									{
										for (size_t j = 0; j < inputer[i]; ++j)
										{
											inputer[i][j] = 0;
											Signs[i][j] = POS;
										}
									}
									break;
								}

								// ctrl + L'\b' cancella un numero
								MatrixAtIndex = L"0";
								Signs[IndexAccesser.Y][IndexAccesser.X] = POS;
								break;

								// L'>' aumenta la dimensione
							case L'>':
								if (inputer > 6)
								{
									break;
								}
								size = inputer.size() + 1;
								Signs(size);
								inputer(size);
								for (size_t i = 0; i < size; ++i)
								{
									inputer[i](size, 0);
									Signs[i](size, POS);
								}

								keep = true;
								goto inputend;

								// L'<' riduce la dimensione
							case L'<':
								if (inputer.size() <= max(2, sizemin))
								{
									break;
								}
								Signs--;
								inputer--;
								for (auto& row : Signs)
								{
									row--;
								}
								for (auto& row : inputer)
								{
									row--;
								}
								IndexAccesser.X %= inputer.size();
								IndexAccesser.Y %= inputer.size();

								keep = true;
								goto inputend;

								// L'\r' invia la matrice
							case L'\r':
								Continue = false;
							inputend:
								_GetCursorPos();
								csbi.dwCursorPosition.Y += 2 * inputer.size() + 1;
								SetConsoleCursorPosition(
									hConsole, csbi.dwCursorPosition
								);
								SetConsoleCursorInfo(hConsole, &cursor);
								goto exit;

								// termine programma
							case L'.':
								SetConsoleCursorInfo(hConsole, &cursor);
								this->clear();
								ret true;

							default:

								// aggiunta di carattere numerico o segno
								if (isdigit(C) or
									(C == L'-' and MatrixAtIndex == L"0")
									and !Signs[IndexAccesser.Y][IndexAccesser.X])
								{
									if (Signs[IndexAccesser.Y][IndexAccesser.X]
										and MatrixAtIndex.at(0) != L'-')
									{
										MatrixAtIndex = L'-' + MatrixAtIndex;
									}

									if (C == L'-')
									{
										Signs[IndexAccesser.Y][IndexAccesser.X]
											= NEG;
									}
									if (MatrixAtIndex.size() >
										4 + (MatrixAtIndex.at(0) == L'-'))
									{
										break;
									}
									if (MatrixAtIndex == L"0")
									{
										MatrixAtIndex.clear();
									}
									MatrixAtIndex += C;
								}
							}
							// //

							// stampa matrice di input
							inputer[IndexAccesser.Y][IndexAccesser.X] =
								MatrixAtIndex == L"-" ? 0 : stoi(MatrixAtIndex);
							_GetCursorPos();
							auto CursorPos{ csbi.dwCursorPosition };
							ClearArea(
								{ (short)(CursorPos.X + 30), (short)(CursorPos.Y + 8) },
								{ 30, 8 }
							);
							depth = inputer.output(IndexAccesser, lenght);
							SetConsoleCursorInfo(hConsole, &cursor);
						}

						// uscita dal programma
						if (!RunMonitor) {
							_GetCursorPos();
							csbi.dwCursorPosition.Y += 2 * inputer.size() + 1;
							SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
							SetConsoleCursorInfo(hConsole, &cursor);

							*this = Matrix<_Ty>(
								inputer.size(), tensor<long double>(inputer.size(), 0)
							);
							ret true;
						}
					}
				}

				// termine dell'input principale
			exit:
				if (Displayed.last() ==
					Matrix<_Ty>(size_s, tensor<long double>(size_s, 0)))
				{
					*this = Matrix<_Ty>(size_s, tensor<long double>(size_s, 0));
					ret true;
				}
				while (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
					GetAsyncKeyState(VK_MENU) & 0x8000);
				if (!keep)
				{
					operators << L"";
					ToConvalidate += L'\'';
				}

				// ridimensionamento se richiesto
				if (keep)
				{
					for (auto& matrix : Displayed)
					{
						size_s = Displayed.last().size();
						matrix(size_s);
						for (auto& row : matrix)
						{
							row(size_s, 0);
						}
					}
				}

				// termine
				if (!Continue)
				{
				end:
					_GetCursorPos();
					auto D = Continue ? depth + 1 : 0;
					SetConsoleCursorPosition(
						hConsole, { 0, short(csbi.dwCursorPosition.Y + D) }
					);
					break;
				}

			output: HIDECURSOR;

				// pulizia
				SetConsoleCursorPosition(hConsole, { 0, begin.Y });
				short extension = csbi.dwSize.X - 1;
				short limit = csbi.dwCursorPosition.Y + depth + 1;
				for (short i = begin.Y; i <= limit; ++i)
				{
					wcout << wstring(extension, L' ') << L'\n';
				}

				// primo output
				SetConsoleCursorInfo(hConsole, &cursor);
				SetConsoleCursorPosition(hConsole, begin);
				_GetCursorPos();
				SetConsoleCursorPosition(
					hConsole,
					{
						short(csbi.dwCursorPosition.X + 1),
						short(csbi.dwCursorPosition.Y + depth / 2)
					}
				);
				wcout << operators[0];

				// output
				_GetCursorPos();
				SetConsoleCursorPosition(
					hConsole, { short(csbi.dwCursorPosition.X + 1), begin.Y }
				);
				for (size_t i = 0; i < Displayed.size() - keep; ++i)
				{

					// controllo iniziale
					_GetCursorPos();
					if (csbi.dwSize.X <= csbi.dwCursorPosition.X + 11 * size_s + 1)
					{
						Displayed.erase(i);
						if (i + 1 < operators)
						{
							operators.erase(i + 1);
						}

						int sum{};
						for (const auto& op : operators)
						{
							sum += op.size();
						}

						sum += Displayed.size();
						if (ToConvalidate.size() > sum)
						{
							ToConvalidate.erase(sum);
						}
						break;
					}
					Displayed[i].output();

					// riposizionamento operatore
					_GetCursorPos();
					SetConsoleCursorPosition(
						hConsole,
						{
							short(csbi.dwCursorPosition.X + 1),
							short(csbi.dwCursorPosition.Y + depth / 2)
						}
					);
					if (i + 1 < operators)
					{
						if (csbi.dwCursorPosition.X + operators[i + 1].size()
							>= csbi.dwSize.X)
						{
							operators.erase(i + 1);
							break;
						}
						wcout << operators[i + 1];
					}

					// riposizionamento finale
					_GetCursorPos();
					SetConsoleCursorPosition(
						hConsole,
						{
							short(csbi.dwCursorPosition.X + 1),
							short(csbi.dwCursorPosition.Y - depth / 2)
						}
					);
				}
				if (keep)
				{
					goto input;
				}
			}
		}

		if (Displayed.empty())
		{
			_GetCursorPos();
			csbi.dwCursorPosition.Y += 2 * size_s + 1;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			SetConsoleCursorInfo(hConsole, &cursor);

			*this = Matrix<_Ty>(size_s, tensor<long double>(size_s, 0));
			ret true;
		}

		// calcolo matrice
		*this = ObjectOperations(errcode, Displayed, operators, ToConvalidate);
		ret *this != Matrix<_Ty>{};
	}

	void DisplayWith(const Matrix other) const
	{
		_GetCursorPos();

		// console ristretta
		if (csbi.dwSize.X <= 22 * this->size() + 2)
		{
			this->output({ 0, -2 });
			other.output({ 0, -2 });
			wcout << L'\n';
			ret;
		}

		// console di dimensioni corrette
		other.output({ (short)this->output(), -2 });
		wcout << L'\n';
	}
	void DisplayWith(const Matrix A, const Matrix B) const
	{
		_GetCursorPos();

		// console ristretta
		if (csbi.dwSize.X <= 33 * this->size() + 3)
		{
			this->output({ 0, -2 });
			A.output({ 0, -2 });
			B.output({ 0, -2 });
			wcout << L'\n';
			ret;
		}

		// console di dimensioni corrette
		int line{ this->output() };
		line = max(line, A.output());
		B.output({ (short)line, -2 });
		wcout << L'\n';
	}

	Matrix operator+(const Matrix other) const
	{
		Matrix result(*this);
		for (size_t i = 0; i < result; ++i)
		{
			for (size_t j = 0; j < other; ++j)
			{
				result[i][j] += other[i][j];
			}
		}
		ret result;
	}
	Matrix operator+=(const Matrix other)
	{
		*this = *this + other;
		ret *this;
	}

	Matrix operator-(const Matrix other) const
	{
		Matrix result(*this);
		for (size_t i = 0; i < result; ++i)
		{
			for (size_t j = 0; j < other; ++j)
			{
				result[i][j] -= other[i][j];
			}
		}
		ret result;
	}
	Matrix operator-=(const Matrix other)
	{
		*this = *this - other;
		ret *this;
	}

	tensor<_Ty> operator*(const tensor<_Ty> vector) const
	{
		if (vector.size() != this->size())
		{
			throw out_of_range("Wrong size!");
		}
		tensor<_Ty> product(vector.size());
		for (size_t i = 0; i < product; ++i)
		{
			_Ty DotProduct{};
			for (size_t j = 0; j < product; ++j)
			{
				DotProduct += (*this)[i][j] * vector[j];
			}
			product[i] = DotProduct;
		}
		ret product;
	}

	Matrix operator*(const _Ty scalar) const
	{
		auto This{ *this };
		for (auto& row : This)
		{
			for (auto& el : row)
			{
				el *= scalar;
			}
		}
		ret This;
	}
	Matrix& operator*=(const _Ty scalar)
	{
		*this = *this * scalar;
		ret *this;
	}

	Matrix operator*(const Matrix other) const
	{
		if (*this % other)
		{
			ret {};
		}
		size_t size{ this->size() };
		Matrix<_Ty> res(size);

		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				double scalar_prod{};
				for (size_t k = 0; k < size; ++k)
				{
					scalar_prod += (*this)[i][k] * other[k][j];
				}
				res[i] << scalar_prod;
			}
		}

		ret res;
	}
	Matrix& operator*=(const Matrix other)
	{
		*this = *this * other;
		ret *this;
	}

	template<typename T = _Ty> T det()
	{
		if constexpr (is_same_v<T, factor<>>)
		{
			factor<> det;
			int s = this->size();

			// casi speciali del calcolo del determinante
			switch (s)
			{
			case 1: ret (*this)[0][0];
			case 2:
				ret (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			}

			// caso generale del calcolo del determinante
			for (size_t i = 0; i < s; ++i)
			{
				Matrix<factor<>> MX(s - 1);
				for (size_t I = 0; I < s - 1; ++I)
				{
					for (size_t J = 0; J < s; ++J)
					{
						if (i == J)
						{
							continue;
						}
						MX[I] << (*this)[I + 1][J];
					}
				}

				auto MiddleDet{ MX.det() };
				if (MiddleDet != 0)
				{
					auto adder{ (*this)[0][i] * MiddleDet };
					for (auto& mon : adder)
					{
						mon.coefficient *= -1;
					}
					det -= adder.neg();
				}
			}

			ret det;
		}
		if constexpr (is_integral_v<T> or is_floating_point_v<T>)
		{
			T det{};
			size_t s{ this->size() };

			// casi speciali del calcolo del determinante
			switch (s)
			{
			case 1: ret (*this)[0][0];
			case 2:
				ret (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			}

			// caso generale
			for (size_t i = 0; i < s; ++i)
			{
				Matrix MX(s - 1);
				for (size_t I = 0; I < s - 1; ++I)
				{
					for (size_t J = 0; J < s; ++J)
					{
						if (i == J)
						{
							continue;
						}
						MX[I] << (*this)[I + 1][J];
					}
				}

				det += intpow(-1, i) * (*this)[0][i] * MX.det();
			}

			ret det;
		}

		ret T();
	}
	
	Matrix invert(_Ty det = 0)
	{
		Matrix<_Ty> result(this->size());
		if (det == 0)
		{
			det = this->det();
		}

		// matrice non invertibile
		if (det == _Ty())
		{
			result = *this;
			result[0][0] = nan("");
			ret result;
		}

		// matrice invertibile
		for (size_t i = 0; i < this->size(); ++i)
		{
			for (size_t j = 0; j < this->size(); ++j)
			{
				auto second{ *this };
				second.erase(second.begin() + i);
				for (size_t k = 0; k < second; ++k)
				{
					second[k].erase(second[k].begin() + j);
				}
				result[i] << ((i + j) % 2 == 0 ? 1 : -1) * second.det() / det;
			}
		}

		ret result;
	}

	tensor<double> EigenValues()
	{

		// inizializzazione
		size_t s{ this->size() };
		Matrix<factor<>> PolynomialMatrix(s, tensor<factor<>>(s));
		for (size_t i = 0; i < s; ++i)
		{
			for (size_t j = 0; j < s; ++j)
			{
				PolynomialMatrix[i][j]
					<< monomial<>{ (long double)(*this)[i][j], { 0 } };
			}
		}

		for (size_t i = 0; i < s; ++i)
		{
			PolynomialMatrix[i][i] >> monomial<>{ -1, { 1 } };
		}

		// calcolo autovalori
		tensor<double> eigenvalues;
		wchar_t save_char{ charVariable };
		wstring save_wstring{ Variables };
		charVariable = L'x';
		Variables = L"x";
		auto EigenStrings{ EquationSolver(PolynomialMatrix.det()) };
		for (auto str : EigenStrings)
		{
			str.erase(0, str.find(L'=') + 1);
			if (str.find(L'i') == wstring::npos)
			{
				eigenvalues << stod(str);
			}
		}

		// ordinamento in ordine decrescente
		for (size_t i = 0; i < eigenvalues; ++i)
		{
			for (size_t j = i + 1; j < eigenvalues; ++j)
			{
				if (eigenvalues[i] < eigenvalues[j])
				{
					swap(eigenvalues[i], eigenvalues[j]);
				}
			}
		}

		// rispristino e fine
		charVariable = save_char;
		Variables = save_wstring;
		ret eigenvalues;
	}

	Matrix EigenVectors(tensor<double> EigenV = {})
	{
		size_t size{ this->size() };
		if (EigenV.empty())
		{
			EigenV = this->EigenValues();
		}
		if (EigenV.size() != size)
		{
			ret {};
		}
		tensor<double> result;
		Matrix<_Ty> eigenvectors(size);

		// risoluzione sistemi lineari
		for (size_t i = 0; i < size; ++i)
		{

			// sottrazione autovalore e rimozione fine
			auto NewMx{ *this };
			for (size_t j = 0; j < size; ++j)
			{
				NewMx[j][j] -= EigenV[i];
			}
			for (size_t j = 0; j < size - 1; ++j)
			{
				result << -NewMx[j].last();
			}
			NewMx--;
			for (size_t j = 0; j < size - 1; ++j)
			{
				NewMx[j]--;
			}
			auto Det{ NewMx.det() };

			// calcolo soluzioni e determinanti
			for (size_t j = 0; j < size - 1; ++j)
			{
				auto NewMatrix{ NewMx };
				for (size_t k = 0; k < size - 1; ++k)
				{
					NewMatrix[k][k] = result[k];
				}
				eigenvectors[i] << NewMatrix.det() / Det;
			}
			eigenvectors[i] << 1;

			// normalizzazione autovettori
			double norm{};
			for (size_t j = 0; j < size; ++j)
			{
				norm += eigenvectors[i][j] * eigenvectors[i][j];
			}
			norm = sqrt(norm);
			if (isnan(norm))
			{
				ret {};
			}
			for (size_t j = 0; j < size; ++j)
			{
				eigenvectors[i][j] /= norm;
			}
		}

		ret eigenvectors;
	}
};

// punti
HDC GHDC;
static void DrawLine(int firstX, int firstY, int secondX, int secondY, HPEN Hpen);
static void ProjectPoint(tensor<long double> point, int& pointX, int& pointY);
static void ProjectAndDrawLine
(tensor<long double> start, tensor<long double> end, HPEN Hpen);
class Point__
{
private:
	int ScreenX, ScreenY;
	tensor<long double> Normal;
public:
	long double x, y, z;

	Point__() : x(0), y(0), z(0), ScreenX(-1), ScreenY(-1), Normal(3) {}
	Point__(long double _x, long double _y, long double _z)
		: x(_x), y(_y), z(_z), ScreenX(-1), ScreenY(-1), Normal(3)
	{}
	Point__(factor<> funct, long double _x, long double _y)
		: x(_x), y(_y), z(funct({ x, y })), ScreenX(-1), ScreenY(-1), Normal(3)
	{}
	Point__(Fraction<> funct, long double _x, long double _y)
		: x(_x), y(_y), z(funct({ x, y })), ScreenX(-1), ScreenY(-1), Normal(3)
	{}

	int GetScreenX()
	{
		if (ScreenX == -1)
		{
			ProjectPoint({ x, y, z }, ScreenX, ScreenY);
		}
		ret ScreenX;
	}
	int GetScreenY()
	{
		if (ScreenY == -1)
		{
			ProjectPoint({ x, y, z }, ScreenX, ScreenY);
		}
		ret ScreenY;
	}
	tensor<long double> GetNormalVector() const
	{
		ret Normal;
	}
	
	bool Void() const
	{
		ret x == 0 and y == 0 and z == 0 and
			ScreenX == -1 and ScreenY == -1 and Normal == tensor<long double>(3);
	}

	Point__& operator=(const Point__& other)
	{
		if (this != &other)
		{
			ScreenX = other.ScreenX;
			ScreenY = other.ScreenY;
			Normal = other.Normal;
			x = other.x;
			y = other.y;
			z = other.z;
		}
		ret *this;
	}

	tensor<long double> SetNormalVector(Fraction<> dfx, Fraction<> dfy)
	{
		Normal(3);
		Normal[0] = dfx({ x, y });
		Normal[1] = dfy({ x, y });
		Normal[2] = 1;

		long double norm{ hypot(Normal[0], Normal[1], Normal[2]) };
		for (auto& component : Normal)
		{
			component /= norm;
		}
		ret Normal;
	}

	void Display(int width, COLORREF color)
	{
		if (ScreenX == -1 or ScreenY == -1)
		{
			ProjectPoint({ x, y, z }, ScreenX, ScreenY);
		}
		
		int w2{ width / 2 };
		for (int i = -w2; i < width - w2; ++i)
		{
			for (int j = -w2; j < width - w2; ++j)
			{
				SetPixel(GHDC, ScreenX, ScreenY, color);
			}
		}
	}

	void StdDisplay
	(Fraction<> fx, Fraction<> dfx, Fraction<> dfy, tensor<long double> light)
	{
		Point__ P{ fx, x, y };
		auto normal{ P.SetNormalVector(dfx, dfy) };
		auto dot{
			normal[0] * light[0] + normal[1] * light[1] + normal[2] * light[2]
		};

		int RgbValue = clamp(int(255 * dot), 0, 255);
		P.Display(2, RGB(RgbValue, RgbValue, RgbValue));
	}
};
static void DrawLine(Point__ P1, Point__ P2, HPEN hpen);

// dati
template<typename T> bool isnan(Fraction<T> object)
{
	ret false;
}
template<typename T> bool isnan(Matrix<T> object)
{
	ret isnan(object[0][0]);
}
class NumberData
{
public:
	ptrdiff_t number{};
	wstring code;
	int degree{};
	wstring expression;
	tensor<ptrdiff_t> sequence;
	divisor div;
	digitRatio digit;

	NumberData() = default;
	NumberData(
		ptrdiff_t num,
		const wstring& c,
		int deg,
		const wstring& expr,
		const tensor<ptrdiff_t>& seq,
		const divisor& d,
		const digitRatio& dr
	) :
		number(num),
		code(c),
		degree(deg),
		expression(expr),
		sequence(seq),
		div(d),
		digit(dr)
	{}

	void printf()
	{
		setlocale(LC_ALL, "");
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
		wcout.imbue(locale(""));

		// stampa numero
		if (PRINTN)
		{
			wcout << L"numero " << number << L":\n";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"in esadecimale è " << hex << uppercase;
			wcout << number << L'\n' << dec << nouppercase;
			if (number - 1 < PrimeNumbers.list_primes)
			{
				wcout << L"Numero Primo #" << number << L" = ";
				wcout << PrimeNumbers.list_primes[number - 1] << L'\n';
			}
		}

		// stampa dati cifre
		else if (number >= 10)
		{

			// stampa numero
			if (
				digit.digitSumRatioNum == 0 and
				digit.digitProductRatioNum == 0
				)
			{
				ret;
			}

			wcout << L"numero " << number << L":\n";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"in esadecimale è " << hex << uppercase;
			wcout << number << L'\n' << dec << nouppercase;
			if (number - 1 < PrimeNumbers.list_primes)
			{
				wcout << L"Numero Primo #" << number << L" = ";
				wcout << PrimeNumbers.list_primes[number - 1] << L'\n';
			}
			SetConsoleTextAttribute(hConsole, 13);

			// stampa somma cifre
			if (digit.digitSumRatioNum != 0)
			{
				wcout << L"la somma delle cifre è ";
				wcout << L'(' << digit.digitSumRatioNum;
				wcout << L'/' << digit.digitSumRatioDen;
				wcout << L")x\n";
			}

			// stampa prodotto cifre
			if (digit.digitProductRatioNum != 0)
			{
				wcout << L"il prodotto delle cifre è ";
				if (digit.digitProductRatioDen != 1)
				{
					wcout << L'(';
				}
				
				wcout << digit.digitProductRatioNum;
				if (digit.digitProductRatioDen != 1)
				{
					wcout << L'/';
					wcout << digit.digitProductRatioDen;
					wcout << L')';
				}
				wcout << L"x\n";
			}
		}

		// stampa stringa
		if (!code.empty())
		{
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"il codice è <" << code << L">\n";
		}

		// stampa grado e sequenza
		if (degree != 0)
		{
			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"il grado è " << degree << L'\n';
			SetConsoleTextAttribute(hConsole, 3);
			wcout << L"la sequenza del grado è :\n(";
			for (size_t i = 0; i < sequence.size() - 1; ++i)
			{
				wcout << sequence[i] << L", ";
			}
			wcout << sequence.last() << L")\n";
		}

		if (!expression.empty())
		{

			// se il numero è primo
			if (PrimeNumbers.is_prime[number])
			{
				SetConsoleTextAttribute(hConsole, 240);
				wcout << L"il numero è primo";
				ResetAttribute();
				wcout << L'\n';
			}

			// altrimenti stampa scomposizione
			else
			{
				SetConsoleTextAttribute(hConsole, 11);
				wcout << L"la fattorizzazione è ";
				wcout << expression << L'\n';
				if (div.DivNumber != 1)
				{
					SetConsoleTextAttribute(hConsole, 8);

					// stampa numero divisori
					wcout << L"il numero dei divisori è ";
					wcout << div.DivNumber << L'\n';

					// stampa somma divisori
					wcout << L"la somma dei divisori è ";
					wcout << div.DivSum << L'\n';

					// stampa prodotto divisori
					wcout << L"il prodotto dei divisori è ";
					if (div.DivProduct != 1)
					{
						wcout << div.DivProduct << L'\n';
					}
					else
					{
						wcout << div.Div_pr << L'\n';
					}
				}
			}

		}
		ResetAttribute();
	}
};
class NumberDataTensor : public tensor<NumberData>
{
private:
	void heapify(int n, int i)
	{
		int largest{ i };
		int left{ 2 * i + 1 };
		int right{ 2 * i + 2 };
		if (left < n and this->at(left).number > this->at(largest).number)
		{
			largest = left;
		}
		if (right < n and this->at(right).number > this->at(largest).number)
		{
			largest = right;
		}
		if (largest != i)
		{
			iter_swap(this->begin() + i, this->begin() + largest);
			heapify(n, largest);
		}
	}
public:
	NumberDataTensor() : tensor<NumberData>() {}
	NumberDataTensor(initializer_list<NumberData> init) :
		tensor<NumberData>(init)
	{}

	void printf()
	{
		for (auto& Data : *this)
		{
			Data.printf();
		}
	}
	void HeapSort()
	{
		int n = this->size();
		for (ptrdiff_t i = n / 2 - 1; i >= 0; --i)
		{
			heapify(n, i);
		}
		for (ptrdiff_t i = n - 1; i > 0; --i)
		{
			iter_swap(this->begin(), this->begin() + i);
			heapify(i, 0);
		}
	}
};

// tensori
tensor<wstring> commands
{
	L"cc" ,
	L"ccc",
	L"cf" ,
	L"cff",
	L"ccf",
	L"ct" ,
	L"dc" ,
	L"dcc",
	L"df" ,
	L"dff",
	L"dcf",
	L"dt" ,
	L"dr" ,
	L"drc",
	L"drf",
	L"drt",
	L"ctn",
	L"cod",
	L"sys",
	L"pol",
	L"alg",
	L"mtx",
	L"rnd"
};
tensor<wstring> Numbers, Polynomials, Expressions;
tensor<tensor<wstring>> GlobalNumerators, GlobalDenominators, GlobalOperators;
tensor<tensor<short>> ActionsList;

#pragma endregion
#pragma region Declarations

static wstring Handler(wstring test);
static size_t Factorial(size_t n);
static size_t BinomialCoeff(size_t n, size_t k);
static ptrdiff_t Gcd(ptrdiff_t A, ptrdiff_t B);
template<typename T> static int Gcd(tensor<T> terms);
static wstring ConvertEnumToWString(switchcase Enum);
static switchcase ConvertWStringToEnum(wstring str);
static void ReassigneEnum(switchcase& option);
static void WriteFraction
(wstring Num, wstring Den, wstring& command, COORD START = { -1, -1 });
static void PrintPFrame
(double deg, int sides, double radius, COORD WinCenter);
static void DrawFrame
(int arc, double __i, int centerX, int centerY, double DIM);
static void DrawCircleSquare(COORD CircleCenter);
static void CS_CenterPrinter();
static void CS_CornerPrinter();
static void ProgressBar(long double ratio, double barWidth);
static long double WaitingScreen(auto begin, auto end);
static wstring CTSuperScript(wchar_t input);
static wstring CFSuperScript(wstring script);
static void DeduceFromExponents(wstring& str);
static void GetFraction(wstring& numerator, wstring& denominator, COORD& Off);
#define GRAPHED (1 << 2)
#define CHANGEDVALUE (1 << 1)
#define BOOLALPHACHANGED 1
static Fraction<> GetFractionAdvanced(wstring& errcode, int& BoolData);
static wstring GetLine(tensor<wstring>& sugg, bool ShowSuggestions = true);
static wstring GetUserNum
(wstring txt, ptrdiff_t low, ptrdiff_t high, bool ShowSuggestions);
static void SetDebug(wstring message, switchcase& opt, bool& Return,
	ptrdiff_t& LowerBound, ptrdiff_t& UpperBound, ptrdiff_t& datalenght
);
static void MonitorConsoleSize(COORD min, atomic_bool& runMonitor);
static void UserInputThread();
static void DrawAxis(double pInc, double vInc);
static LRESULT CALLBACK WindowProcessor2D(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
static BOOL CreateGraph(Fraction<> funct = { {}, {} });
static LRESULT CALLBACK WindowProcessor3D(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
static void Project3DGraph(Fraction<> funct);
static bool Prime(ptrdiff_t number);
static void PrimeNCalculator(ptrdiff_t max, ptrdiff_t min = 0);
static tensor<compost> DecomposeNumber(ptrdiff_t input);
static tensor<wstring> Fractioner(wstring polinomial);
static tensor<int> DecomposeStrings(wstring Terminal);
static wstring Cript(ptrdiff_t input);
static wstring FactNumber(ptrdiff_t input);
static int ExeStrings(wstring input);
static divisor DivisorCalculator(wstring factor);
static digitRatio DigitRationalizer(ptrdiff_t inpt);
static tensor<int> DivisorCounter(int num);
static NumberData ExecuteSimpledeg(ptrdiff_t input);
static NumberData ExecuteDegree(ptrdiff_t input);
static NumberData ExecuteSimpleFact(ptrdiff_t input);
static NumberData ExecuteFactor(ptrdiff_t input);
static NumberData ExecuteSimpleDF(ptrdiff_t input);
static NumberData ExecuteDigit(ptrdiff_t input);
static NumberData ExecuteDegFactor(ptrdiff_t input);
static NumberData ExecuteDegDigit(ptrdiff_t input);
static NumberData ExecuteFactDigit(ptrdiff_t input);
static NumberData ExecuteAll(ptrdiff_t input);
static wstring PolynomialSyntax(wstring pol);
static wstring PolynomialSyntaxDirector(wstring pol);
static wstring UpdateString(wstring& ToEvaluate);
static wstring NumberCodeSyntax(wstring ToEvaluate);
static ptrdiff_t NumberConverter(size_t root, wstring M);
static ptrdiff_t StringConverter(wstring ToEvaluate);
static void CodeConverter
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static void LongComputation
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static factor<big> GetMonomials(wstring pol);
static polynomial<big> GetMonomialsRedirector(wstring pol);
static polynomial<big> GetMonomialsAssister(wstring pol);
static tensor<tensor<long double>> FromPolynomialToPos(
	factor<> vect,
	int& StartIndex,
	tensor<int>& CorrectSizes,
	tensor<int>& VDirectorTerm,
	tensor<int>& VKnownTerm,
	tensor<tensor<int>>& VDirectorSeq,
	tensor<tensor<int>>& VKnownSeq
);
static void PolynomialDivide
(
	FACTOR<> dividend, FACTOR<> divisor,
	FACTOR<>& quotient, FACTOR<>& rest
);
static polynomial<> Total(factor<> vect);
static polynomial<> Partial(factor<> vect);
static polynomial<> Binomial(factor<> vect);
static polynomial<> Trinomial(factor<> vect);
static polynomial<> SquareDifference(factor<> vect);
static polynomial<> Ruffini(factor<> vect);
static polynomial<> CompleteTheSquare(factor<> vect);
static polynomial<> TrinomialSquare(factor<> vect);
static FACTOR<> Complementary(POLYNOMIAL<> Polynomial, FACTOR<> factor, int exp);
static void Simplify(Fraction<>& fr, int& ncoeff, int& dcoeff);
static void Approximator(tensor<long double>& Equation, long double& root);
static tensor<wstring> EquationSolver(factor<> equation);
static tensor<long double> RootExtractor(polynomial<> vect);
static tensor<tensor<long double>> SystemSolver(tensor<factor<>> functions);
static void FractDisequationMain(
	polynomial<> Num, polynomial<> Den,

	tensor<wstring>& Roots,
	tensor<bool>& ItsFromDenominator,

	bool& InitSign, bool& Invert
);
static ConsoleStream GetAlgebricSolution(
	tensor<wstring> roots,
	tensor<bool> ItsFromDenominator,

	bool InitialSign,
	bool ExpectedSign,
	bool CanBeNull = false
);
static bool ParamDisequationSetup(
	polynomial<>& Num, polynomial<>& Den, polynomial<>& Sum,

	tensor<bool>& FromDenominator,
	tensor<long double>& AdditionalRoots,
	factor<>& Parametric,

	tensor<factor<>>& tops,
	tensor<factor<>>& bottoms,

	bool& InitSign,
	bool& InvertSign
);
static void ParamDisequationMain(
	polynomial<> Un,
	tensor<factor<>> tops,
	tensor<factor<>> bottoms,
	tensor<long double> AdditionalRoots,

	size_t& Unisize,
	tensor<tensor<factor<>>>& TableOfMains,
	tensor<long double>& RootSet,
	tensor<long double>& RootExamples,
	tensor<wstring>& vals
);
static ConsoleStream GetParametricSolution(
	wchar_t parameter,
	size_t Unisize, size_t Vpos,
	bool InitialSign, bool ExpectedSign, bool CanBeNull,

	tensor<bool> TermsFromDenominator,
	polynomial<>& Num, polynomial<>& Den, factor<> Parametric,
	tensor<factor<>> tops, tensor<factor<>> bottoms,

	tensor<tensor<factor<>>> TableOfMains,
	tensor<long double> RootSet, tensor<long double> RootExamples,
	tensor<wstring> vals
);
#define LESS_THAN        1
#define LESS_EQUAL_THAN (1 << 1)
#define MORE_THAN       (1 << 2)
#define MORE_EQUAL_THAN (1 << 3)
static ConsoleStream DisequationSolutionPrinter(
	polynomial<> Num,
	polynomial<> Den,
	int behaviour,
	bool ChangeSign,
	bool PrintCondition = true
);
static void PrintFraction
(int NC, int DC, int& LINE, bool WritePlus, Fraction<> fract);
static void PrintFractionaryResult
(
	int NC, int DC, int& lines, Fraction<> Fract,

	POLYNOMIAL<> NScomp = { {} }, POLYNOMIAL<> DScomp = { {} },

	bool HasMoreVariables = true, bool correct = false,

	tensor<double> roots = {}, tensor<POLYNOMIAL<>> Denominators = {}
);
static void CodeToNumber(switchcase& argc);
static wstring ExpandNumber(
	switchcase& argc,
	big Number = big(),
	int Base = 0,
	bool access = true
);
static void Repeater(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input)
);
static void Loop(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input),
	bool select = false
);
static void SystemSolverGeneral(switchcase& argc);
template<typename Type>
static polynomial<> DecompPolynomial(switchcase& argc, Type Polynomial);
static void DecompFraction(switchcase& argc);
static void DecompMatrices(switchcase& argc);

#pragma endregion

// programma principale
int main()
{
	int ErrorCode{}, ErrMessage;
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	////////////////////////////////////////////////////////////////////////////////
	// wcout << L"inserisci una frazione algebrica.\n";
	// SetConsoleTextAttribute(hConsole, 12);
	// wcout << L"Per inserire una singola frazione premere CTRL + ALT\n";
	// wcout << L"Per cambiare lo stato degli esponenti premere CTRL + SHIFT\n";
	// ResetAttribute();
	// if (Expression().in() == Fraction<>{ polynomial<>{ { { 0, { -3 } } } }, {} })
	// {
	// 	ret -111;
	// }
	
	srand(time(NULL));
	for (int digitnumber = 3;; ++digitnumber) {
		tensor<int> A(digitnumber), B(digitnumber);

		wcout << "numero di cifre: " << digitnumber << L'\n';
		for (auto& I : A) I = rand() % 10;
		for (auto& I : B) I = rand() % 10;

		big first(A), second(B);
		auto product = first * second;

		if (digitnumber % 50 == 0) {
			wcout << first << L'\n';
			wcout << L" * \n";
			wcout << second << L'\n';
			wcout << L" = \n";
			wcout << product << L'\n';
		}
	}
	////////////////////////////////////////////////////////////////////////////////

	// avvio
	QueryPerformanceFrequency(&ProgramFrequency);
	Beep(1'000, 50);
	Beep(1'000, 50);

	// // dichiarazione stringhe
	wstring simpledeg{ L"Il PROGRAMMA calcola solo la codifica di un intero" };

	wstring simplefact{ L"Il PROGRAMMA calcola solo la fattorizzazione di un intero" };

	wstring def_sct{ L"Il PROGRAMMA calcola solo codifica e fattorizzazione" };

	wstring desimpledeg{ L"Il PROGRAMMA calcola solo la codifica di una serie" };

	wstring desimplefact{ L"Il PROGRAMMA calcola solo la fattorizzazione di una serie" };

	wstring defact_message{ L"Il PROGRAMMA calcola la fattorizzazione di una serie" };
	defact_message += L"\ne numero, somma e prodotto dei divisori";

	wstring deg_message{ L"Il PROGRAMMA calcola codice, sequenza e grado di una serie" };

	wstring fact_message{ L"Il PROGRAMMA calcola la fattorizzazione di un intero" };
	fact_message += L"\ne numero, somma e prodotto dei divisori";

	wstring message{ L"Il PROGRAMMA calcola codice, sequenza e grado di un intero" };

	wstring AllMessage{ L"Il PROGRAMMA calcola \"tutti\" i dati di alcuni interi" };

	wstring de_digit{ L"Il PROGRAMMA ricerca numeri con particolari" };
	de_digit += L" occorrenze di somma e prodotto cifre";

	wstring deg_digit{ L"Il PROGRAMMA calcola cifre, codice, sequenza e grado" };

	wstring fact_digit{ L"Il PROGRAMMA calcola cifre, fattorizzazione, e divisori" };

	wstring defact_digit{ L"Il PROGRAMMA calcola tutti i dati, cifre comprese" };

	wstring vel;
	switchcase option;
	// //

	bool start{ true };
	bool LockPrimeNumbersInput{ false };
	ptrdiff_t global{ 1 };
	long double ComputationTime{};
	size_t Timer{ 6'500'000'000 };
	for (;;)
	{
		if (!LockPrimeNumbersInput) {
		Start:
			system("cls");
			SetConsoleTitle(L"schermata START");

			// // output
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"~~~~~.";
#ifndef BUGS
			wcout << L"~~";
#endif // BUGS
			wcout << L"[> CALCOLO-STRINGHE-E-GRADI V";
#ifndef BUGS
			wcout << L' ';
#endif // BUGS
			wcout << L"1.6.4 ";
#ifdef BUGS
			wcout << L"BETA ";
#endif // BUGS
			wcout << L"<]";
#ifndef BUGS
			wcout << L"~~";
#endif // BUGS
			wcout << L".~~~~~\n";
			wcout << L"*****.*****.*****.[> CALCOLATRICE <].*****.*****.*****\n\n";

			SetConsoleTextAttribute(hConsole, 10);
			wcout << L"Scegliere il limite per la ricerca dei numeri primi\n";
			wcout << L"Un limite più alto comporta un tempo di attesa più lungo\n";
			wcout << L"Inserire un numero tra compreso 10 milioni e 50 miliardi\n\n";

			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"*****.*****.*****.*****.******.*****.*****.*****.*****\n\n";
			SetConsoleTextAttribute(hConsole, 9);
			wcout << L"Per bloccare l'input inserire 0\n";
			// //

			// inserimento punti
			wstring Timer_t{ to_wstring(Timer) };
			for (ptrdiff_t i = Timer_t.size() - 3; i > 0; i -= 3)
				Timer_t.insert(Timer_t.begin() + i, L'.');
			wcout << L"ESEMPIO: " << Timer_t << L" = ~1 minuto di attesa\n";

			// input controllato
			wstring G{ GetUserNum(L"", 0, GLOBAL_CAP, false) };
			if (G == L".") {
				ErrorCode = 3;
				goto End;
			}
			if (G.empty()) global = 0;
			else if (!isdigit(G.at(0))) global = 0;

			// casi 0 e 1
			else global = stoull(G);
			if (global < 10'000'000) {
				if (!start and global == 0) LockPrimeNumbersInput = true;
				global = start ? 10'000'000 : 0;
			}
			ResetAttribute();

			// output del tempo e calcolo primi
			auto OldGlobalMax{ GlobalMax };
			if (global != 0) {
				DECLARE_TIME_POINT(begin);
				GlobalMax = global;
				HIDECURSOR;
				PrimeNCalculator(GlobalMax + 1'000, OldGlobalMax);

				DECLARE_TIME_POINT(end);
				if (GlobalMax / (OldGlobalMax + 1) > 10)
					ComputationTime = WaitingScreen(begin, end);
				else WaitingScreen(begin, end);

				SetConsoleCursorInfo(hConsole, &cursor);
				start = false;
			}
			if (GlobalMax > 9'000 and global > 1 and
				GlobalMax / (OldGlobalMax + 1) > 10)
			{
				ComputationTime /= 1'000'000;
				Timer = (GlobalMax + 1'000) * 60'000 / ComputationTime;
			}
		}

		// titolo e audio
		system("cls");
		SetConsoleTitle(L"schermata HOME");
		Beep(750, 300);

		// scelta
		wcout << L"Scegliere la modalità di calcolo::\n";
		SetConsoleTextAttribute(hConsole, 4);
		wcout << L"Se stringa di un carattere:\n";
		wcout << L"\t'0' = Blocca input numeri primi ~[~sempre]\n";
		wcout << L"\t'1' = Sblocca input numeri primi\n";
		wcout << L"\t'x' = TORNA ALLA SCHERMATA START\n";
		wcout << L"\t'.' = Fine programma [sempre]\n";
		SetConsoleTextAttribute(hConsole, 9);
		wcout << L"altrimenti:\n";
		wcout << L"\t\"rnd\" = casuale\n";
		wcout << L"\t\"ctn\" = da codice a numero\n";
		wcout << L"\t\"cod\" = da numero a espansione in serie e viceversa\n";
		wcout << L"\t\"sys\" = risolutore di sistemi non lineari o parametrici\n";
		wcout << L"\t\"pol\" = scomposizione polinomi\n";
		wcout << L"\t\"alg\" = scomposizione frazioni algebriche\n";
		wcout << L"\t\"mtx\" = scomposizione matrici\n";
		SetConsoleTextAttribute(hConsole, 11);
		wcout << L"Oppure:\n";
		wcout << L"Primi caratteri:\n";
		wcout << L"\t'c' = calcolo\n";
		wcout << L"\t'd' = debug\n";
		wcout << L"\t\"dr\" = debug ristretto\n";
		SetConsoleTextAttribute(hConsole, 14);
		wcout << L"Caratteri seguenti:\n";
		wcout << L"\t'c' = solo codifica\n";
		wcout << L"\t'f' = scomposizione in fattori primi\n";
		wcout << L"\t\"cc\" = codifica, sequenza e grado\n";
		wcout << L"\t\"ff\" = fattoizzazione e dati dei divisori\n";
		wcout << L"\t\"cf\" = codifica e fattorizzazione\n";
		wcout << L"\t't' = tutti i dati\n";
		SetConsoleTextAttribute(hConsole, 6);
		wcout << L"Solo per il debug ristretto:\n";
		wcout << L"\t'' = solo dati sulle cifre dei numeri\n";
		wcout << L"\t'c' = cifre, codifica, sequenza e grado\n";
		wcout << L"\t'f' = fattorizzazione, cifre e divisori\n";
		wcout << L"\t't' = tutti i dati compresi quelli sulle cifre\n";
		ResetAttribute();
		wcout << L"Selezionando più operazioni, il tempo di calcolo aumenta\n";

		vel = GetLine(Numbers);
		if (vel.empty()) vel = L"rnd";
		option = ConvertWStringToEnum(vel);
		
		// gestione input numeri primi
		assigne:
		if (vel.size() == 1) {
			switch (vel.at(0)) {
			case L'0':
				LockPrimeNumbersInput = true;
				wcout << L"\ng++ - Input numeri primi bloccato";
				goto option_choice;
			case L'1':
				LockPrimeNumbersInput = false;
				wcout << L"\ng++ - Input numeri primi sbloccato";
				goto option_choice;
			case L'x': goto Start;
			case L'.':
				ErrorCode = -1073741510;
				goto End;
			default: vel += L' ';
			}
		}

		// caso input non assegnato correttamente
		option = ConvertWStringToEnum(vel);
		if (option == NotAssigned) {

			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"NON CORRETTO !!\a";
			ResetAttribute();

		option_choice:

			wcout << L"\ng++ - Scegli opzioni:: (...)\n";
			vel = GetLine(Numbers);
			goto assigne;
		}

		// cambio titolo
		wcout << L"\n\n";
		ReassigneEnum(option);
		auto wtitle{ ConvertEnumToWString(option) };
		system("cls");
		SetConsoleTitle(wtitle.c_str());

		// scelta funzioni e opzioni
		thread calculator, monitor;
		RunMonitor = true;
		do {
			Beep(500, 200);
			bool Threading{ false };

			switch (option)
			{
			case DoSimpleCode:
				Repeater(option, simpledeg, ExecuteSimpledeg);
				break;
			case DoComplexCode:
				Repeater(option, message, ExecuteDegree);
				break;
			case DoSimpleFactor:
				Repeater(option, simplefact, ExecuteSimpleFact);
				break;
			case DoComplexFactor:
				Repeater(option, fact_message, ExecuteFactor);
				break;
			case DoCodeFactor:
				Repeater(option, def_sct, ExecuteSimpleDF);
				break;
			case DoAll:
				Repeater(option, AllMessage, ExecuteDegFactor);
				break;
			case DebugSimpleCode:
				Loop(option, desimpledeg, ExecuteSimpledeg);
				break;
			case DebugComplexCode:
				Loop(option, deg_message, ExecuteDegree);
				break;
			case DebugSimpleFactor:
				Loop(option, desimplefact, ExecuteSimpleFact);
				break;
			case DebugComplexFactor:
				Loop(option, defact_message, ExecuteFactor);
				break;
			case DebugCodeFactor:
				Loop(option, def_sct, ExecuteSimpleDF);
				break;
			case DebugAll:
				Loop(option, AllMessage, ExecuteDegFactor);
				break;
			case DebugDigits:
				Loop(option, de_digit, ExecuteDigit, true);
				break;
			case DebugDigitsAndCode:
				Loop(option, deg_digit, ExecuteDegDigit, true);
				break;
			case DebugDigitsAndFactor:
				Loop(option, fact_digit, ExecuteFactDigit, true);
				break;
			case DebugComplete:
				Loop(option, defact_digit, ExecuteAll, true);
				break;
			case ConvertCodeInverse: CodeToNumber(option);
				break;
			case SeriesExpansion: ExpandNumber(option);
				break;

			case SolveSystem: Threading = true;
				calculator = thread(SystemSolverGeneral, ref(option));
				monitor = thread(MonitorConsoleSize, COORD{ 60, 30 }, ref(RunMonitor));
				break;

			case FactorPolynomial: Threading = true;
				calculator = thread(DecompPolynomial<wstring>, ref(option), L"");
				monitor = thread(MonitorConsoleSize, COORD{ 50, 20 }, ref(RunMonitor));
				break;

			case FactorFraction: Threading = true;
				calculator = thread(DecompFraction, ref(option));
				monitor = thread(
					MonitorConsoleSize, COORD{ 60, 30 }, ref(RunMonitor)
				);
				break;

			case FactorMatrix: Threading = true;
				calculator = thread(DecompMatrices, ref(option));
				monitor = thread(
					MonitorConsoleSize, COORD{ 80, 45 }, ref(RunMonitor)
				);
				break;
			}
			if (Threading) {

				// thread
				SetThreadAffinityMask(calculator.native_handle(), 1 << 0);
				SetThreadAffinityMask(monitor.native_handle(), 1 << 1);
				if (calculator.joinable()) calculator.join();
				if (monitor.joinable()) monitor.join();

				// errore
				if (!RunMonitor) {
					RunMonitor = true;
					system("cls");
					continue;
				}

			}
			if (option == Random) goto MB;

		} while (option != NotAssigned);
	}


	// messaggio
MB:
	wcout << L'\a';
	ErrorCode = 0;
	ErrMessage = MessageBox(
		NULL,
		L"\t\t DEBUG ERROR\
		\n\n   g++ - Terminare il programma??\
		\n\n   [riprova] per tornare all'inizio del programma\
		\n\n",
		L"Microsoft Visual C++ Runtime Library",
		MB_ABORTRETRYIGNORE | MB_ICONWARNING
	);

	// pulizia dati globali
	Numbers.clear();
	Polynomials.clear();
	Expressions.clear();
	GlobalNumerators.clear();
	GlobalDenominators.clear();
	GlobalOperators.clear();
	ActionsList.clear();

	// se l'utente clicca su [riprova]
	if (ErrMessage == IDRETRY) {
		LockPrimeNumbersInput = false;
		goto Start;
	}

	// se l'utente clicca su [ignora]
	if (ErrMessage == IDIGNORE) goto MB;

	// fine del programma
End:
	system("cls");
	SetConsoleTextAttribute(hConsole, 4);
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	ret ErrorCode;
}

#pragma region Functions

// funzioni matematiche
#pragma region Math

// elaboratore di numeri sottoforma di stringa
static wstring Handler(wstring test)
{
	if (test.find(L'.') != wstring::npos or test.find(L',') != wstring::npos)
		while (Last(test) == L'0') test.pop_back();
	if (Last(test) == L',' or Last(test) == L'.') test.pop_back();
	ret ElabExponents(test);
}

// fattoriale x! = x*(x-1)*...*2*1
static size_t Factorial(size_t n)
{
	if (n <= 1) ret 1;
	ret n * Factorial(n - 1);
}

// coefficiente binomiale: (n k) = n! / (k! (n-k)!)
static size_t BinomialCoeff(size_t n, size_t k)
{
	long double coeff{ 1.0 };

	// limite di sicurezza per prevenire crash
	if (n <= 20) coeff = Factorial(n) /
		(static_cast<long double>(Factorial(k)) * Factorial(n - k));
	else for (size_t j = 1; j <= n - k; ++j)
		coeff *= (static_cast<long double>(k) + j) / j;

	ret static_cast<size_t>(coeff);
}

// massimo comune divisore tra due interi
static ptrdiff_t Gcd(ptrdiff_t A, ptrdiff_t B)
{
	if (A < B) swap(A, B);
	while (B != 0) {
		auto temp{ B };
		B = A % B;
		A = temp;
	}
	ret A;
}

// massimo comune divisore tra due interi grandi
static big Gcd(big A, big B)
{
	if (A < B) swap(A, B);
	while (B != 0) {
		big temp = B;
		B = A % B;
		A = temp;
	}
	ret A;
}

// massimo comune divisore tra più termini
template<typename T>static int Gcd(tensor<T> terms)
{
	int gcd{};
	if (terms.empty()) ret 0;

	// tensore di interi
	if constexpr (is_same_v<T, int>) {
		if (terms == 1) ret terms[0];
		gcd = terms[0];
		for (const auto& term : terms) {
			gcd = Gcd(gcd, term);
			if (gcd == 1) break;
		}
	}

	// fattore
	else if constexpr (is_same_v<T, MONOMIAL<>> or is_same_v<T, monomial<>>)
	{
		if (terms == 1) ret terms[0].coefficient;
		gcd = terms[0].coefficient;
		for (const auto& term : terms) {
			gcd = Gcd(gcd, term.coefficient);
			if (gcd == 1) break;
		}
	}

	ret gcd;
}

// massimo comune divisore tra numeri molto grandi
static big Gcd(tensor<big> terms)
{
	if (terms == 1) ret terms[0];
	auto gcd{ terms[0] };
	for (const auto& term : terms) {
		gcd = Gcd(gcd, term);
		if (gcd == 1) break;
	}
	ret gcd;
}

// potenza sugli interi (per precisione)
static ptrdiff_t intpow(ptrdiff_t base, int exp)
{
	ptrdiff_t power{ 1 };
	auto NewExp{ exp + 1 };
	auto NewBase{ base };
	if (base < 0) NewBase *= -1;
	while (--NewExp > 0) {
		power *= NewBase;
		if (power < 0) ret -1;
	}
	if (exp % 2 == 1 and base < 0) ret -power;
	ret power;
}

#pragma endregion

// funzioni per gestrire l'enum
#pragma region EnumMod

// da enum a stringa
inline static wstring ConvertEnumToWString(switchcase Enum)
{
	auto it = enumToStringMap.find(Enum);
	if (it != enumToStringMap.end()) ret it->second;
	ret L"";
}

// da stringa a enum
inline static switchcase ConvertWStringToEnum(wstring str)
{
	auto it = stringToEnumMap.find(str);
	if (it != stringToEnumMap.end()) ret it->second;
	else {
		stringToEnumMap.insert({ str , NotAssigned });
		it = stringToEnumMap.find(str);
		ret it->second;
	}
}

// riassegna l'opzione casuale dell'enum
static void ReassigneEnum(switchcase& option)
{
	if (option != Random) ret;
	random_device rng;
	mt19937 gen(rng());
	uniform_int_distribution<> dis(0, commands.size() - 1);
	switch (dis(gen)) {
	case 0: option = DoSimpleCode;
		ret;
	case 1: option = DoComplexCode;
		ret;
	case 2: option = DoSimpleFactor;
		ret;
	case 3: option = DoComplexFactor;
		ret;
	case 4: option = DoCodeFactor;
		ret;
	case 5: option = DebugCodeFactor;
		ret;
	case 6: option = DoAll;
		ret;
	case 7: option = DebugSimpleCode;
		ret;
	case 8: option = DebugComplexCode;
		ret;
	case 9: option = DebugSimpleFactor;
		ret;
	case 10: option = DebugComplexFactor;
		ret;
	case 11: option = DebugComplexFactor;
		ret;
	case 12: option = DebugAll;
		ret;
	case 13: option = DebugDigits;
		ret;
	case 14: option = DebugDigitsAndCode;
		ret;
	case 15: option = DebugDigitsAndCode;
		ret;
	case 16: option = DebugDigitsAndFactor;
		ret;
	case 17: option = ConvertCodeInverse;
		ret;
	case 18: option = SeriesExpansion;
		ret;
	case 19: option = SolveSystem;
		ret;
	case 20: option = FactorPolynomial;
		ret;
	case 21: option = FactorFraction;
		ret;
	case 22: option = FactorMatrix;
		ret;
	}
}

#pragma endregion

// funzioni necessarie per disegnare
#pragma region BasicPrints

namespace ConsoleLogData
{
	int RotAngle{ 270 }, PolygDegree{}, PolygonSides{ 4 };
	int CircleCenterX, CircleCenterY, CircleRotDegreeAngle{};
	bool DecreaseAngle{ true }, DecreaseWidth{ true };
	double DWidth{ 1.9 };

	const tensor<int> spectrum{ 9, 9, 9, 11, 11, 3, 3, 12, 4 };
};

// cancella un'area rettangolare di spazio
static void ClearArea(COORD WinCenter, COORD Dimensions)
{
	_GetCursorPos();
	DWORD written;
	COORD coord{
		short(WinCenter.X - Dimensions.X), short(WinCenter.Y - Dimensions.Y)
	};

	for (int y = WinCenter.Y; y <= WinCenter.Y + 2 * Dimensions.Y; ++y) {
		coord.Y = y - Dimensions.Y;
		FillConsoleOutputCharacter
		(hConsole, L' ', 2 * Dimensions.X + 1, coord, &written);
	}
}

// stampa una frazione di stringhe
static void WriteFraction(wstring Num, wstring Den, wstring& command, COORD START)
{

	// ricerca suggerimento giusto
	int spaces = fabs(((int)Num.size() - (int)Den.size()) / 2);
	bool script = true;
	if (Num.size() > 0) for (const auto& comma : commands) {
		command = comma;
		auto back{ command };
		if (back.size() == Num.size()) continue;
		if (back.size() > Num.size()) back.erase(Num.size());
		if (back == Num) {
			script = false;
			break;
		}
	}

	// stampa frazione algebrica
	HIDECURSOR;
	_GetCursorPos();
	if (START.X < 0) START = csbi.dwCursorPosition;
	_GetCursorPos();

	SetConsoleCursorPosition(hConsole, START);
	wstring S(csbi.dwSize.X - START.X, L' ');
	wcout << S << L'\n';
	SetConsoleCursorPosition(hConsole, START);

	// caso con numeratore maggiore
	if (Num.size() > Den.size()) {
		if (!script) {
			SetConsoleTextAttribute(hConsole, 6);
			wcout << command << L'\n';
			SetConsoleCursorPosition(hConsole, START);
			ResetAttribute();
		}

		wcout << Num << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 1) });
		wcout << S << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 1) });
		wcout << wstring(Num.size(), L'-') << L'\n';

		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 2) });
		wcout << S << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 2) });
		wcout << wstring(spaces, L' ') << Den << L'\n';
	}

	// caso con denominatore maggiore
	else {
		if (!script) {
			SetConsoleTextAttribute(hConsole, 6);
			wcout << wstring(spaces, L' ') << command << L'\n';
			SetConsoleCursorPosition(hConsole, START);
			ResetAttribute();
		}

		wcout << wstring(spaces, L' ') << Num << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 1) });
		wcout << S << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 1) });
		wcout << wstring(Den.size(), L'-') << L'\n';

		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 2) });
		wcout << S << L'\n';
		SetConsoleCursorPosition(hConsole, { START.X, short(START.Y + 2) });
		wcout << Den << L'\n';
	}

	wcout << L'\n';
}

// stampa il poligono
static void PrintPFrame
(double deg, int sides, double radius, COORD WinCenter)
{
	ResetAttribute();

	COORD coord{};
	const double DIM{ 1.9 };
	const short centerX{ WinCenter.X };
	const short centerY{ WinCenter.Y };
	long double setX, setY;
	long double theta{ 2 * M_PI / sides };

	// calcolo apotema e lato con la goniometria e le formule
	long double sidelenght{ sqrt(2 * radius * radius * (1 - cos(theta))) };
	long double apotem{ sqrt(pow(radius, 2) - pow(sidelenght / 2, 2)) };

	// stringa dei caratteri per l'illuminazione del poligono
	wstring prints{ L"@$#/*!+=~;:-,." };

	for (long double rad = 0; rad < 2 * M_PI; rad += theta) {
		for (int i = 0; i < sidelenght; ++i) {

			// calcolo punti del poligono
			setX = i - sidelenght / 2;
			setY = apotem;
			rad += deg;

			// rotazione punti
			coord.X = setX * cos(rad) - setY * sin(rad);
			coord.Y = setX * sin(rad) + setY * cos(rad);

			// traslazione e ridimensionamento X
			coord.X *= DIM;
			coord.X += centerX;
			coord.Y += centerY;

			rad -= deg;

			// illuminazione
			SetConsoleCursorPosition(hConsole, coord);
			int index = coord.Y - centerY + radius;
			index *= (long double)prints.size() / (2 * radius);
			wcout << prints[index];
		}
	}
}

// stampa il cerchio
static void DrawFrame
(int arc, double __i, int centerX, int centerY, double DIM)
{
	using ConsoleLogData::spectrum;
	COORD coord{};
	int setX, setY;
	const double R{ 8 };

	for (int deg = 0; deg < arc; ++deg) {

		// da gradi a radianti
		long double rad{ (double)deg / 180 * M_PI };

		// calcolo punti della circonferenza del cerchio
		setX = R * cos(rad);
		setY = R * sin(rad);

		// rotazione punti
		coord.X = setX * cos(__i) - setY * sin(__i);
		coord.Y = setX * sin(__i) + setY * cos(__i);

		// ridimensionamento X
		coord.X *= DIM;

		// traslazione
		coord.X += centerX;
		coord.Y += centerY;

		SetConsoleCursorPosition(hConsole, coord);
		WORD Color{ 15 };

		// generatore casuale numeri
		random_device rng;
		mt19937 gen(rng());
		uniform_int_distribution<> dis(0, 9);

		// generatore casuale colori
		random_device Random;
		mt19937 Gen(Random());
		uniform_int_distribution<> Dis(0, spectrum.size() - 1);
		int DisGen{ Dis(Gen) };

		// assegnazione colori
		for (size_t j = 0; j < spectrum; ++j) if (DisGen == j) Color = spectrum[j];

		// stampa
		SetConsoleTextAttribute(hConsole, Color);
		wcout << dis(gen);
	}
}

// gestisce la stampa del poligono e del cerchio
static void DrawCircleSquare(COORD CircleCenter)
{
	using namespace ConsoleLogData;

	// calcolo variabili
	COORD Cursor{ 0, CircleCenter.Y };
	Cursor.Y -= Min.Y;
	const double SPEED{ 50 };
	const double GAP{ 0.05 };
	const int const_x{ CircleCenter.X };
	const int const_y{ CircleCenter.Y };
	const double R2{ 5 };
	bool DoNotSkip{ true };

	for (CircleRotDegreeAngle;; CircleRotDegreeAngle += 7) {

		// termine funzione
		if (IsDone.load() and !DoNotSkip) {
			ClearArea(CircleCenter, Min);
			SetConsoleCursorPosition(hConsole, Cursor);
			ret;
		}
		DoNotSkip = false;

		// variazione centro del cerchio principale
		// secondo lo spostamento su un secondo cerchio
		long double i{ (double)CircleRotDegreeAngle / 180 * M_PI };
		CircleCenterX = const_x + R2 * cos(i);
		CircleCenterY = const_y + R2 * sin(i);

		// variazione dati cerchio
		if (DWidth <= 1 or DWidth >= 2.5) DecreaseWidth = !DecreaseWidth;
		if (RotAngle <= 0 or RotAngle >= 360) DecreaseAngle = !DecreaseAngle;

		// stampa cerchio
		DrawFrame(RotAngle, i, CircleCenterX, CircleCenterY, DWidth);

		// stampa poligono e cambio variabili
		DecreaseWidth ? DWidth -= GAP : DWidth += GAP;
		DecreaseAngle ? RotAngle -= SPEED * GAP : RotAngle += SPEED * GAP;
		PrintPFrame(PolygDegree * M_PI / 180, PolygonSides, 10, CircleCenter);
		PolygDegree += 2;

		// riassegnazione dei lati
		if (PolygDegree % 180 == 0)
			switch (PolygonSides) {
			case 4: PolygonSides = 6;
				break;
			case 6: PolygonSides = 8;
				break;
			case 8: PolygonSides = 4;
				break;
			}
		sleep_for(microseconds(1));
		ClearArea(CircleCenter, Min);
	}
}

#pragma endregion

// funzioni di stampa avanzate
#pragma region Print

// stampa poligono e cerchio al centro della finestra
inline static void CS_CenterPrinter()
{

	// assegnazione delle coordinate del centro
	_GetCursorPos();
	COORD WinCenter{};
	if (csbi.dwSize.X / 2 < Min.X) WinCenter.X = Min.X;
	else WinCenter.X = csbi.dwSize.X / 2;
	if (csbi.dwSize.Y / 2 < Min.Y) WinCenter.Y = Min.Y + 1;
	else WinCenter.Y = csbi.dwSize.Y / 2 + 1;

	// animazione
	DrawCircleSquare(WinCenter);

}

// stampa poligono e cerchio in un angolo della finestra
inline static void CS_CornerPrinter()
{

	// lettura coordinate
	_GetCursorPos();
	wcout << wstring(csbi.dwSize.Y - 1, L'\n');

	// animazione
	SetConsoleCursorPosition(hConsole, { 0, 0 });
	DrawCircleSquare(Min);

}

// stampa una barra di avanzamento
static void ProgressBar(long double ratio, double barWidth)
{
	if (barWidth <= 10) ret;

	// necessario per poter scrivere messaggi 
	// sotto alla barra di progresso
	SetConsoleCursorPosition(hConsole, { 0, 1 });

	// stampa della barra principale
	wcout << L"[[";
	int pos{ int(barWidth * ratio) };
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) wcout << L'=';
		else i == pos ? wcout << L'>' : wcout << L' ';
	}

	// calcolo della percentuale
	ratio *= 100.0;
	wostringstream stream;
	stream << fixed << setprecision(1) << ratio;
	wcout << L"]] " << stream.str() << L"%\r";
}

// stampa il tempo del calcolo
static long double WaitingScreen(auto begin, auto end)
{
	system("cls");

	// calcolo dati
	long double delta = 1'000 *
		static_cast<double>(end.QuadPart - begin.QuadPart)
		/ (ProgramFrequency.QuadPart);
	wostringstream output;
	output << fixed << setprecision(1) << L"tempo di calcolo numeri primi = ";

	// calcolo output
	if (delta <= 10)
	{
		output << delta * 1'000;
		output << L" microsecondi\n\n";
	}
	else if (delta <= 10'000)
	{
		output << delta;
		output << L" millisecondi\n\n";
	}
	else if (delta <= 600'000)
	{
		output << delta / 1'000;
		output << L" secondi\n\n";
	}
	else
	{
		output << delta / 60'000;
		output << L" minuti\n\n";
	}
	_GetCursorPos();
	SetConsoleTextAttribute(hConsole, 6);

	// output
	COORD Cursor{
		short((csbi.dwSize.X - output.str().size()) / 2 - 1),
		csbi.dwSize.Y / 2 - 1
	};
	SetConsoleCursorPosition(hConsole, Cursor);
	wcout << output.str();
	sleep_for(seconds(1));

	ResetAttribute();
	ret delta * 1'000'000;
}

#pragma endregion

// funzioni per gestire gli esponenti
#pragma region SuperScript

// converte da numero ad apice
static wstring CTSuperScript(wchar_t input)
{
	switch (input) {
	case L'0': ret L"⁰";
		break;
	case L'1': ret L"¹";
		break;
	case L'2': ret L"²";
		break;
	case L'3': ret L"³";
		break;
	case L'4': ret L"⁴";
		break;
	case L'5': ret L"⁵";
		break;
	case L'6': ret L"⁶";
		break;
	case L'7': ret L"⁷";
		break;
	case L'8': ret L"⁸";
		break;
	case L'9': ret L"9";
		break;
	}
	ret wstring(1, input);
}

// converte da apice a numero
static wstring CFSuperScript(wstring script)
{
	wstring output;
	for (const auto& ch : script) {
		auto it = ConvertFromSuperScript.find(script);
		if (it != ConvertFromSuperScript.end()) output += it->second;
		else output += wstring(1, ch);
	}
	ret output;
}

// cambia una stringa da formato numeri a formato esponenti
static wstring ElabExponents(wstring& str)
{
	if (!BOOLALPHA) ret str;
	int J{ 1 };
	bool dobreak{ false };
	for (size_t I = 0; I < str.size(); ++I) {
		auto pointer{ I + 1 };
		if (str.at(I) == L'^' and I != str.size() - 1) {
			
			while (str.at(pointer) < 128 and isdigit(str.at(pointer)))
			{
				// scelta carattere
				dobreak = false;
				wstring replacer;
				if (str.at(pointer) == L'0') {
					if (J > 1) replacer = L"⁰";
					else dobreak = true;
				}
				else replacer = CTSuperScript(str.at(pointer));
				if (dobreak) break;

				// cambio caratteri e ridimensionamento stringa
				str.replace(pointer, 1, replacer);
				if (I < str.size() - 1 and J == 1) str.erase(I, 1);
				J++;
				pointer = I + J - 1 + (J == 1);
				if (pointer >= str.size()) break;
			}
			J = 1;
		}
	}
	ret str;
}

// calcola la stringa originaria da quella con gli esponenti
static void DeduceFromExponents(wstring& str)
{
	for (ptrdiff_t i = str.size() - 1; i >= 0; --i) {
		auto script{ wstring(1, str.at(i)) };
		auto unscript{ CFSuperScript(script) };
		if (unscript != script) {
			str.erase(i, 1);
			str.insert(str.begin() + i, L'^');
			str.insert(str.begin() + i + 1, unscript.at(0));
		}
	}
}

#pragma endregion

// funzioni di input utente
#pragma region Input

// inputa una frazione algebrica
static void GetFraction(wstring& numerator, wstring& denominator, COORD& Off)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	const int EscapeCode{ -32 };
	int diff{};
	size_t sizevel;
	numerator.clear();
	denominator.clear();
	wstring vel, command{ L"rnd" }, Num, Den;
	bool arrow{ false }, system{ false }, IsTheCursorAtStart{ true };

	// aggiunta di spazio
	wstring Ncopy{ L"0" }, Dcopy;
	_GetCursorPos();
	auto START{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	_GetCursorPos();
	if (csbi.dwCursorPosition.Y >= START.Y)
	{
		Off.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
		START.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
	}
	SetConsoleCursorPosition(hConsole, START);

	for (;;) {

		// fine input di una singola frazione
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
			GetAsyncKeyState(VK_MENU))
		{
			while (GetAsyncKeyState(VK_CONTROL) & 0x8000 and
				GetAsyncKeyState(VK_MENU));

			_GetCursorPos();
			csbi.dwCursorPosition.X += diff + 1;
			IsTheCursorAtStart ?
				csbi.dwCursorPosition.Y++ : csbi.dwCursorPosition.Y--;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);

			if (denominator.empty()) denominator = L"1";
			ret;
		}

		if (_kbhit()) {
			_GetCursorPos();
			short maxsize = csbi.dwSize.X;

			// overflow di caratteri nella console
			if (numerator.size() >= maxsize or denominator.size() >= maxsize)
			{
				numerator.clear();
				denominator.clear();
				continue;
			}

			char c = _getch();
			_GetCursorPos();

			bool cond{
				c == L'\b' or c == L'\t' or c == L'\r' or c == L' '
				or c == L'K' or c == L'M' or c > 31 or c == -109
			};
			if (c == EscapeCode) arrow = true;
			if (c == 0) {
				system = true;
				continue;
			}
			auto testN{ Num };
			auto testD{ Den };

			if (cond) switch (c) {

				// L'.' termina il programma
			case L'.':
				numerator = L".";
				ret;

				// L'\r' termina l'input
			case L'\r':
				START.Y += 4;
				SetConsoleCursorPosition(hConsole, START);
				if (denominator.empty()) denominator = L"1";
				ret;

				// L'\b' cancella indietro
			case L'\b': vel = IsTheCursorAtStart ? Num : Den;

				if (vel.size() > 1 and vel.size() - diff > 0)
					vel.erase(vel.size() - 1 - diff, 1);
				else if (vel.size() == 1 and diff == 0) vel.clear();

				if (IsTheCursorAtStart) Num = vel;
				else Den = vel;
				break;

				// tab per scegliere il suggerimento
			case L'\t': numerator = command;
				break;

				// ctrl + L'\b' cancella la prima parte della stringa
			case 127: vel = IsTheCursorAtStart ? Num : Den;

				vel.erase(0, vel.size() - diff);
				if (IsTheCursorAtStart) Num = vel;
				else Den = vel;
				break;

			default: vel = IsTheCursorAtStart ? numerator : denominator;
				wstring E_Vel = IsTheCursorAtStart ? Num : Den;

				// aggiunta carattere
				if (!arrow) {

					// calcolo differenza in più
					auto copy{ E_Vel };
					copy.erase(0, E_Vel.size() - diff);
					int new_diff{ (int)vel.size() - diff };
					for (const auto& ch : copy)
						if (CFSuperScript(wstring(1, ch)) != wstring(1, ch))
							new_diff--;

					if (new_diff < 0) new_diff = 0;
					vel = vel.substr(0, new_diff) + wstring(1, c)
						+ vel.substr(new_diff, vel.size());

					if (IsTheCursorAtStart) numerator = vel;
					else denominator = vel;
					break;
				}

				// frecce
				vel = IsTheCursorAtStart ? Num : Den;
				sizevel = vel.size();
				switch (c) {
				case L'K': if (diff < sizevel) diff++;
					break;
				case L'M': if (diff > 0) diff--;
					break;

					// canc cancella in avanti
				case L'S':
					if (diff <= 0) break;
					vel.erase(vel.size() - diff, 1);
					diff--;
					break;

					// ctrl + canc cancella la seconda parte della stringa
				case -109:
					vel.erase(vel.size() - diff);
					diff = 0;
					break;

				case L's': diff = sizevel;
					break;
				case L't': diff = 0;
					break;
				}
				if (arrow) arrow = false;
				if (IsTheCursorAtStart) Num = vel;
				else Den = vel;
			}
			system = false;

			// calcolo dimensione stringhe
			if (BOOLALPHA) {
				ElabExponents(Num);
				ElabExponents(Den);

				if (Num != testN) {
					numerator = Num;
					DeduceFromExponents(numerator);
				}
				else {
					Num = numerator;
					ElabExponents(Num);
				}
			
				if (Den != testD) {
					denominator = Den;
					DeduceFromExponents(denominator);
				}
				else {
					Den = denominator;
					ElabExponents(Den);
				}
			}
			else {
				if (Num == testN) Num = numerator;
				else numerator = Num;
				if (Den == testD) Den = denominator;
				else denominator = Den;
			}

			// stampa frazione algebrica
			WriteFraction(Num, Den, command, START);
			int spaces = fabs(((int)Num.size() - (int)Den.size()) / 2);

			// reset riga
			if (c == L'H') IsTheCursorAtStart = true;
			else if (c == L'P') IsTheCursorAtStart = false;

			// reset cursore
			COORD startPos{ START };
			if (IsTheCursorAtStart) {
				startPos.X += Num.size();
				if (diff < Num.size()) startPos.X -= diff;
				else startPos.X = START.X;
				if (Num.size() < Den.size()) startPos.X += spaces;
			}
			else {
				startPos.X += Den.size();
				if (diff < Den.size()) startPos.X -= diff;
				else startPos.X = START.X;
				if (Num.size() > Den.size()) startPos.X += spaces;
				startPos.Y += 2;
			}

			SetConsoleCursorPosition(hConsole, startPos);
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		if (!RunMonitor) {
			numerator = L"0";
			denominator.clear();
			ret;
		}
	}
}

// inputa una frazione tramite interfaccia avanzata
static Fraction<> GetFractionAdvanced(wstring& errcode, int& BoolData)
{

	// inizio
	BoolData = 0;
	bool start{ true }, copied{ false }, pasting{ false };
	_GetCursorPos();
	const wstring OperatorsAllowed{ L"(+-*/=)\\" };
	COORD START{ csbi.dwCursorPosition };
	SetConsoleCursorPosition(
		hConsole, { csbi.dwCursorPosition.X, short(START.Y + 1) }
	);

	short linetracker{};
	size_t TensorIndex{}, LocalIndex{};
	tensor<short> actions{ 0 };
	tensor<wstring> Numerators, Denominators, Operators{ L"" };
	for (;;) if (_kbhit() or
		(GetAsyncKeyState(VK_CONTROL) & 0x8000 and
			GetAsyncKeyState(VK_MENU) & 0x8000))
	{
		wstring num_, den_;

		// output operatore
		if (pasting) {
			wcout << GlobalOperators[TensorIndex][LocalIndex];

			// termine scrittura suggerimento
			if (LocalIndex > GlobalNumerators[TensorIndex].size() - 1) {

				// aggiornamento dati locali
				Numerators = GlobalNumerators[TensorIndex];
				Denominators = GlobalDenominators[TensorIndex];
				Operators = GlobalOperators[TensorIndex];
				actions = ActionsList[TensorIndex];
				copied = true;
				pasting = false;
				
				// aggiunta di uno spazio
				_GetCursorPos();
				SetConsoleCursorPosition(
					hConsole,
					{ short(csbi.dwCursorPosition.X + 1), csbi.dwCursorPosition.Y }
				);

				continue;
			}
		}

		// input operatore
		else if (_kbhit()) {

			// lettura carattere senza consumarlo
			bool suggest{ false };
			char c;
			INPUT_RECORD inptrc;
			DWORD eventf;
			for (;;) {
				PeekConsoleInput(hConsoleInput, &inptrc, 1, &eventf);
				if (inptrc.EventType == KEY_EVENT
					and inptrc.Event.KeyEvent.bKeyDown)
				{
					c = inptrc.Event.KeyEvent.uChar.UnicodeChar;

					// pressione di F1
					if (inptrc.Event.KeyEvent.wVirtualKeyCode == VK_F1) {
						if (TensorIndex > 0) TensorIndex--;
						else TensorIndex = GlobalOperators.size() - 1;
						suggest = true;
						break;
					}

					// pressione di F2
					if (inptrc.Event.KeyEvent.wVirtualKeyCode == VK_F2) {
						if (TensorIndex < GlobalOperators.size() - 1) TensorIndex++;
						else TensorIndex = 0;
						suggest = true;
						break;
					}

					if (c != 0) break;
				}
				ReadConsoleInput(hConsoleInput, &inptrc, 1, &eventf);
			}

			// aggiornamento dati con i suggerimenti
			if (suggest) {

				// pulizia iniziale
				wstring S(csbi.dwCursorPosition.X, L' ');
				SetConsoleCursorPosition(hConsole, { 0, START.Y });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { 0, short(START.Y + 1) });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { 0, short(START.Y + 2) });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { 0, short(START.Y + 1) });

				c = _getch();
				linetracker = LocalIndex = 0;
				pasting = true;
				continue;
			}

			// termine programma
			if (c == L'.') {
				c = _getch();
				errcode = L"_";
				ret Fraction<>{};
			}
			
			// termine input
			if (c == L'\r' and !start) {
				c = _getch();
				break;
			}

			// pulizia
			if (c == L'\b' and !start) {
				copied = false;
				c = _getch();

				// dati e variabili
				_GetCursorPos();
				if (actions == 1) continue;
				actions--;
				if (Operators.last().empty()) {
					Numerators--;
					Denominators--;
					Operators--;
				}
				else Operators.last().pop_back();

				// sovrascrittura
				auto Cursor{ actions.last() };
				wstring S(csbi.dwCursorPosition.X - Cursor + 1, L' ');
				SetConsoleCursorPosition(hConsole, { Cursor, START.Y });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { Cursor, short(START.Y + 1) });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { Cursor, short(START.Y + 2) });
				wcout << S;
				SetConsoleCursorPosition(hConsole, { Cursor, short(START.Y + 1) });
				continue;
			}

			// scrittura
			copied = false;
			if (OperatorsAllowed.find(c) != wstring::npos) {
				c = _getch();
				Operators.last() += c;
				wcout << c;

				_GetCursorPos();
				actions << csbi.dwCursorPosition.X;
				continue;
			}
		}
		start = false;
		copied = false;

		// blocco
		_GetCursorPos();
		while (
			GetAsyncKeyState(VK_CONTROL) & 0x8000 and
			GetAsyncKeyState(VK_MENU) & 0x8000
		);
		SetConsoleCursorPosition(
			hConsole, { short(csbi.dwCursorPosition.X + 1), START.Y }
		);

		if (pasting) {
			
			// output della frazione
			wstring no_use;
			WriteFraction(
				GlobalNumerators[TensorIndex][LocalIndex],
				GlobalDenominators[TensorIndex][LocalIndex],
				no_use
			);

			// aggiornamento
			linetracker += max(
				GlobalNumerators[TensorIndex][LocalIndex].size(),
				GlobalDenominators[TensorIndex][LocalIndex].size()
			) + 1;
			LocalIndex++;

			// riposizionamento cursore sulla posizione iniziale
			SetConsoleCursorPosition(hConsole, { linetracker, short(START.Y + 1) });
			continue;
		}

		// input della frazione
		else GetFraction(num_, den_, START);
		
		// uscita
		if (num_ == L".") {
			errcode = L"_";
			ret Fraction<>{};
		}
		auto arg{ ConvertWStringToEnum(num_) };
		ReassigneEnum(arg);
		if (arg != NotAssigned) {
			errcode = num_;
			ret Fraction<>{};
		}

		// esponenti con gli apici
		if (num_ == L"boolalpha")
		{
			BoolData = CHANGEDVALUE | BOOLALPHACHANGED;
			BOOLALPHA = true;
			continue;
		}
		if (num_ == L"noboolalpha")
		{
			BoolData = CHANGEDVALUE;
			BOOLALPHA = false;
			continue;
		}

		// push
		if (num_.empty()) num_ = L"0";
		Numerators << num_;
		Denominators << den_;
		Operators << L"";

		// reset cursore
		_GetCursorPos();
		actions << csbi.dwCursorPosition.X;
		SetConsoleCursorPosition(
			hConsole, { csbi.dwCursorPosition.X, short(START.Y + 1) }
		);
		if (csbi.dwCursorPosition.Y > START.Y + 2) break;
	}

	// salvataggio dati
	if (!copied) {
		GlobalNumerators << Numerators;
		GlobalDenominators << Denominators;
		GlobalOperators << Operators;
		ActionsList << actions;
	}

	// eliminazione comandi
	for (size_t i = 0; i < Numerators; ++i)
		if (Numerators[i] == L"boolalpha" or Numerators[i] == L"noboolalpha")
		{
			Numerators.erase(Numerators.begin() + i);
			Denominators.erase(Denominators.begin() + i);
			Operators[i] += Operators[i + 1];
			Operators.erase(Operators.begin() + i + 1);
		}

	// controllo caratteri di escape
	if (!Operators.empty()) if (!Operators[0].empty())
		if (Operators[0].at(0) == L'\\')
		{
			BoolData += 4;
			Operators[0].erase(0, 1);
		}
	for (const auto& op : Operators) if (op.find(L'\\') != wstring::npos) {
		errcode = L"E' ammesso un carattere di escape solo all'inizio";
		ret Fraction<>{};
	}

	// calcolo variabili
	tensor<Fraction<big>> fractions;
	auto un{ Numerators + Denominators };
	for (auto& str : un) for (const auto& c : str)
		if (isalpha(c) and Variables.find(c) == wstring::npos) Variables += c;
	auto savx{ Variables };
	tensor<int> null(Variables.size(), 0);

	// traduzione
	for (size_t i = 0; i < 2 * Numerators.size(); ++i) {
		bool isnum{ i % 2 == 0 };
		if (isnum) fractions << Fraction<big>{};

		// scelta stringhe
		auto str = isnum ? Numerators[i / 2] : Denominators[i / 2];
		if (!(errcode = PolynomialSyntaxDirector(str)).empty()) ret Fraction<>{};

		// traduzione stringhe
		auto old{ PolynomialMultiply<big>(GetMonomialsAssister(str)) };
		if (Variables == savx or savx.empty()) {
			savx = Variables;
			isnum ? fractions.last().num = { old } : fractions.last().den = { old };
			continue;
		}
		for (auto& mon : old) mon.exp(savx.size(), 0);

		// correzione
		factor<big> correct;
		for (const auto& mono : old)
			correct << monomial<big>{ mono.coefficient, null };
		for (size_t j = 0; j < Variables.size(); ++j) {
			auto pos{ savx.find(Variables.at(j)) };
			if (pos == wstring::npos) continue;
			for (size_t k = 0; k < correct; ++k)
				correct[k].exp[pos] = old[k].exp[j];
		}

		// impostazione
		isnum ?
			fractions.last().num = { correct } : fractions.last().den = { correct };
		Variables = savx;
	}

	tensor<Fraction<>> list;
	for (const auto& fract : fractions) {
		Fraction<> Fract;
		Fract.num = FromBigToDefault(fract.num);
		Fract.den = FromBigToDefault(fract.den);

		if (Fract.num[0][0].exp[0] == -2 or
			Fract.den[0][0].exp[0] == -2)
		{
			errcode = L"Il risultato è troppo grande";
			ret Fraction{};
		}

		if (Fract.den[0][0].coefficient == 0) {
			errcode = L"Il denominatore non può essere nullo";
			ret Fraction<>{};
		}

		list << Fract;
	}

	wcout << L"\n\n";
	ret ObjectOperations(errcode, list, Operators);
}

// inputa un polinomio
static wstring GetLine(tensor<wstring>& sugg, bool ShowSuggestions)
{
	using type = char;
	int EscapeCode;
	if constexpr (is_same_v<type, char>) EscapeCode = -32;
	else EscapeCode = 224;

	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// variabili
	int diff{}, maxsize;
	wstring vel, E_Vel, command{ L"rnd" };
	bool script{ false }, arrow{ false }, Continue{ false };
	ptrdiff_t TensorIndex{};
	wstring StringCopy;

	for (;;) {
		if (_kbhit()) {
			script = false;

			// controllo della dimensione della console
			_GetCursorPos();
			maxsize = csbi.dwSize.X;

			// overflow di caratteri nella console
			if (vel.size() >= maxsize) {
				short height = csbi.dwCursorPosition.Y -
					(vel.size() - 1) / maxsize;
					
				SetConsoleCursorPosition(hConsole, { 0, height });
				wcout << wstring(vel.size(), L' ');
				SetConsoleCursorPosition(
					hConsole, { (short)(maxsize - 1), height }
				);

				vel.erase(maxsize - 1);
				continue;
			}

			// input
			type c = _getch();
			if (c != EscapeCode and c != -109 and c < 0) continue;
			if (c == L'\r') break;
			auto Test{ E_Vel };
			
			// ignora alcuni caratteri
			bool cond{
				(
				c == L'\b' or c == L'\t' or c == L'K' or
				c == L'M' or c == L' ' or c > 31 or c == -109
				)
				and c != EscapeCode
			};
			if (c == EscapeCode) arrow = true;
			if (c == 0) {
				Continue = true;
				continue;
			}
			if (Continue) {
				Continue = false;
				continue;
			}
			if (!cond) continue;

			switch (c) {

				// L'.' termina il programma
			case L'.': ret L".";

				// L'\b' cancella indietro
			case L'\b':
				if (E_Vel.size() > 1 and E_Vel.size() - diff > 0)
					E_Vel.erase(E_Vel.size() - 1 - diff, 1);
				else if (E_Vel.size() == 1 and diff == 0) E_Vel.clear();
				break;

				// tab per scegliere il suggerimento
			case L'\t':
				if (ShowSuggestions) vel = command;
				break;

				// ctrl + L'\b' cancella la prima parte della stringa
			case 127: E_Vel.erase(0, E_Vel.size() - diff);
				break;

			default:

				// calcolo differenza in più
				auto copy{ E_Vel };
				copy.erase(0, E_Vel.size() - diff);
				int new_diff{ (int)vel.size() - diff };
				for (const auto& ch : copy)
					if (CFSuperScript(wstring(1, ch)) != wstring(1, ch))
						new_diff--;

				// aggiunta carattere
				if (!arrow) {
					if (new_diff < 0) new_diff = 0;
					vel = vel.substr(0, new_diff) + wstring(1, c)
						+ vel.substr(new_diff, vel.size());
					break;
				}

				// frecce
				switch (c) {
				case L'K': if (diff < E_Vel.size()) diff++;
					break;
				case L'M': if (diff > 0) diff--;
					break;
				case L'H':
					if (sugg.empty()) break;
					TensorIndex++;
					if (TensorIndex >= sugg) TensorIndex = 0;
					StringCopy = vel = sugg[TensorIndex];
					break;
				case L'P':
					if (sugg.empty()) break;
					TensorIndex--;
					if (TensorIndex < 0) TensorIndex = sugg.size() - 1;
					StringCopy = vel = sugg[TensorIndex];
					break;

					// canc cancella in avanti
				case L'S':
					if (diff <= 0) break;
					E_Vel.erase(E_Vel.size() - diff, 1);
					diff--;
					break;

					// ctrl + canc cancella la seconda parte della stringa
				case -109:
					E_Vel.erase(E_Vel.size() - diff);
					diff = 0;
					break;

				case L's': diff = E_Vel.size();
					break;
				case L't': diff = 0;
					break;
				}
				if (arrow) arrow = false;
			}

			// calcolo stringhe
			if (BOOLALPHA) {
				ElabExponents(E_Vel);
				if (E_Vel != Test) {
					vel = E_Vel;
					DeduceFromExponents(vel);
				}
				else {
					E_Vel = vel;
					ElabExponents(E_Vel);
				}
			}
			
			else if (E_Vel == Test) E_Vel = vel;
			else vel = E_Vel;
			auto Velpart{ E_Vel };
			if (Velpart.size() - diff >= 0) Velpart.erase(Velpart.size() - diff);
			else Velpart.clear();

			if (vel.size() > maxsize) {
				vel.clear();
				E_Vel.clear();
				Velpart.clear();
				diff = 0;
			}

			// stampa dei caratteri immessi
			if (vel.size() > maxsize) {
				wcout << L'\r' << wstring(maxsize, L' ');
				script = true;
			}
			HIDECURSOR;
			if (ShowSuggestions and !vel.empty())

				// ricerca suggerimento giusto
				for (const auto& comma : commands) {
					command = comma;
					auto back{ command };
					if (back.size() == vel.size() and back != vel) continue;
					if (back.size() > vel.size()) back.erase(vel.size());
					if (back == E_Vel) {
						SetConsoleTextAttribute(hConsole, 6);
						wcout << L'\r' << wstring(maxsize, ' ');
						wcout << L'\r' << command;
						ResetAttribute();

						wcout << L'\r' << E_Vel << L'\r' << Velpart;
						script = true;
						break;
					}
				}
			if (!script) {
				wcout << L'\r' << wstring(maxsize, L' ');
				wcout << L'\r' << E_Vel << L'\r' << Velpart;
			}
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		if (!RunMonitor) ret L"0";
	}

	if (vel != StringCopy) sugg << vel;
	ret vel;
}

// inputa un numero dati valore minimo e valore massimo
static wstring GetUserNum
(wstring txt, ptrdiff_t low, ptrdiff_t high, bool ShowSuggestions)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	switchcase option;
	ptrdiff_t UserNum;
	wstring check;
	do {

		// input
		wcout << txt;
		check = GetLine(Numbers, ShowSuggestions);
		wcout << L'\n';
		for (ptrdiff_t i = check.size() - 1; i >= 0; --i)
			if (check.at(i) == L'\'' or check.at(i) == L' ' or check.at(i) == L'\t')
				check.erase(i, 1);
		if (check == L"." or check.empty()) ret check;
		option = ConvertWStringToEnum(check);
		ReassigneEnum(option);
		if (option != NotAssigned) ret ConvertEnumToWString(option);

		// controllo
		if (regex_search(check, wregex(L"\\D"))) {
			if (!PolynomialSyntaxDirector(check).empty()) {
				UserNum = 0;
				goto exit;
			}
			factor<big> operation{
				PolynomialMultiply<big>(GetMonomialsAssister(check))
			};
			if (operation > 1 or operation.empty()) {
				UserNum = 0;
				goto exit;
			}
			UserNum = operation[0].coefficient.Number<ptrdiff_t>();
		}
		else UserNum = big(check).Number<ptrdiff_t>();
		if (UserNum <= numeric_limits<ptrdiff_t>::min() or
			UserNum >= numeric_limits<ptrdiff_t>::max()) UserNum = 0;
	exit:

		if (UserNum < low or UserNum > high) {
			wcout << L'\a';
			if (txt.empty()) {
				_GetCursorPos();
				SetConsoleCursorPosition(
					hConsole,
					{
						csbi.dwCursorPosition.X,
						(short)(csbi.dwCursorPosition.Y - 1)
					}
				);
				wcout << wstring(14, L' ') << L'\r';
			}
		}
	} while (UserNum < low or UserNum > high);
	ret to_wstring(UserNum);
}

// inputa gli estremi della ricerca debug
static void SetDebug(wstring message, switchcase& opt, bool& Return,
	ptrdiff_t& LowerBound, ptrdiff_t& UpperBound, ptrdiff_t& datalenght
)
{
	wstring n_{ to_wstring(GlobalMax) }, Input, txt;
	Return = false;
	wcout << L"Gli estremi dell'intervallo devono essere compresi";
	wcout << L" tra 1 e " << n_ << L"\n\n";

	// input e controllo valore iniziale
	ResetAttribute();
	txt = L"Inserisci il valore di inizio della ricerca\n";
	do Input = GetUserNum(txt, 1, GlobalMax, true);
	while (Input.empty());
	if (Input == L".") {
		opt = Random;
		Return = true;
		ret;
	}
	opt = ConvertWStringToEnum(Input);
	ReassigneEnum(opt);
	if (opt != NotAssigned) {
		system("cls");
		SetConsoleTitle(Input.c_str());
		Return = true;
		ret;
	}
	LowerBound = stoull(Input) + 1;

	// input e controllo valore finale
	txt = L"Inserisci il valore finale della ricerca\n";
	do Input = GetUserNum(txt, 1, GlobalMax, true);
	while (Input.empty());
	if (Input == L".") {
		opt = Random;
		Return = true;
	}
	opt = ConvertWStringToEnum(Input);
	ReassigneEnum(opt);
	if (opt != NotAssigned) {
		system("cls");
		SetConsoleTitle(Input.c_str());
		Return = true;
		ret;
	}
	UpperBound = stoull(Input) + 1;

	if (UpperBound < LowerBound) swap(LowerBound, UpperBound);
	datalenght = UpperBound - LowerBound;
}

#pragma endregion

// funzioni thread
#pragma region Threads

// funzione che invia ctrl + / -
static void SendCtrlPlusMinus(bool plus)
{
	INPUT inputs[4]{};

	// premere ctrl
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_CONTROL;

	// premere + / -
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = plus ? VK_OEM_PLUS : VK_OEM_MINUS;

	// rilasciare + / -
	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = plus ? VK_OEM_PLUS : VK_OEM_MINUS;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	// rilasciare ctrl
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_CONTROL;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	// invio comandi
	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

// funzione che riduce lo zoom se la console è piccola
static void MonitorConsoleSize(COORD min, atomic_bool& runMonitor)
{
	int time{ 50 };
	unique_lock<mutex> lk(MonitorMTX);
	while (RunMonitor) {

		// gestione del tempo
		MonitorCV.wait_for(lk, milliseconds(time), [&] { ret !RunMonitor; });
		if (!RunMonitor) ret;
			
		// prima della riduzione dello zoom
		_GetCursorPos();
		auto oldLength{ csbi.dwSize.X };
		if (oldLength >= min.X and csbi.dwSize.Y >= min.Y) {
			time = 50;
			continue;
		}
			
		// dopo la riduzione dello zoom
		SendCtrlPlusMinus(false);
		_GetCursorPos();
		auto newLength{ csbi.dwSize.X };

		// zoom al minimo
		if (oldLength == newLength and GetConsoleWindow() == GetForegroundWindow())
		{
			runMonitor = false;
			ret;
		}
		time /= 2;
	}
}

// gestisce il secondo thread del code to number
static void UserInputThread()
{
	while (computing) {

		// riduzione uso della CPU
		sleep_for(milliseconds(100));

		if (_kbhit()) {

			// controllo
			char choice = _getch();
			if (choice == L'S' or choice == L's') {
				{
					lock_guard<mutex> lock(mtx);
					GlobalInterr = true;
					interrupted = true;
				}
				Cv.notify_all();
				ret;
			}
		}
	}
}

#pragma endregion

#pragma region BasicWindows

RECT ClientRect;
namespace WindowData
{
	bool redo{ false };

	#define FUNCTION_REMOVE 0
	#define FUNCTION_DERIVATIVE 1
	#define FUNCTION_LABEL 2

	enum states {
		MIN,
		MAX,
		H_FLX,
		A_FLX,
		D_FLX
	};
	LPARAM Coords{}, Current{};
	bool enable{ false };
	double Zoom{ 1 };
	wchar_t __save;
	
	int gIndex{};
	tensor<int> Indexlist;
	int shiftX{}, shiftY{};
	tensor<tensor<int>> memory{ {} };
	class DATA
	{
	public:
		COLORREF Color;
		Fraction<> Function;
		wstring ID;

		tensor<int> States;
		tensor<long double> StatX, StatY;

		DATA() : Color(0) {}
		DATA(Fraction<> funct);

		bool operator==(DATA other)
		{
			ret ID == other.ID;
		}
	};
	tensor<DATA> List;

	DATA::DATA(Fraction<> funct) : Function(funct), ID(funct.str())
	{
		const double DeltaX{ 0.01 };
		auto Derivative{ funct.derivate(0) };

		// eliminazione di eventuali doppi
		StatX = RootExtractor({ Derivative.num });
		for (ptrdiff_t i = StatX.size() - 1; i > 0; --i)
			if (StatX[i] == StatX[i - 1]) StatX.erase(i, 1);
		size_t I{};

		// calcolo punti stazionari
		for (; I < StatX; ++I) {
			auto x{ StatX[I] };
			auto y{ funct.num[0]({ x }) / funct.den[0]({ x }) };

			StatY << y;
			x -= DeltaX;
			bool before{ funct.num[0]({ x }) / funct.den[0]({ x }) > y };
			x += 2 * DeltaX;
			bool after{ funct.num[0]({ x }) / funct.den[0]({ x }) > y };
			if (before and after) States << MIN;
			else if (!(before or after)) States << MAX;
			else States << H_FLX;
		}

		// calcolo flessi
		auto NewStatX{ RootExtractor({ Derivative.derivate(0).num }) };
		for (ptrdiff_t j = NewStatX.size() - 1; j > 0; --j)
			if (NewStatX[j] == NewStatX[j - 1]) NewStatX.erase(j, 1);
		for (; I < NewStatX; ++I) {
			auto x{ NewStatX[I] };
			auto y{ funct.num[0]({ x }) / funct.den[0]({ x }) };

			StatX << x;
			StatY << y;
			x -= DeltaX;
			bool before{ funct.num[0]({ x }) / funct.den[0]({ x }) > y };
			States << (before ? D_FLX : A_FLX);
		}

		// calcolo del colore
		random_device rng;
		mt19937 gen(rng());
		uniform_int_distribution<> dis(0, 127);
		int rgbValues[3]{};
		auto i{ List.size() };
		if ((i | FOREGROUND_BLUE) != i) rgbValues[2] += dis(gen);
		if ((i | FOREGROUND_GREEN) != i) rgbValues[1] += dis(gen);
		if ((i | FOREGROUND_RED) != i) rgbValues[0] += dis(gen);
		if ((i | FOREGROUND_INTENSITY) != i) {
			rgbValues[0] += 128;
			rgbValues[1] += 128;
			rgbValues[2] += 128;
		}
		Color = RGB(rgbValues[0], rgbValues[1], rgbValues[2]);
	}
};
namespace Window3Data
{
	enum states {
		MINIMUM,
		MAXIMUM,
		SADDLE,
		UNKNOWN,
	};
	tensor<int> def;

	tensor<int> Light{ 0, 0, -1 };
	double Zoom{ 1 };
	bool enable{ false };

	LPARAM Coords{}, Current{};
	tensor<long double> StatX, StatY, StatZ;
	Fraction<> Function, PartialXder, PartialYder;
	auto Theta{ M_PI / 4 };
	auto Phi{ M_PI / 3 };

	#define X2D(X, Y, Z) OriginX + (X) * cos(Theta) + (Y) * sin(Theta)
	#define Y2D(X, Y, Z) OriginY - \
	((Z) * sin(Phi) - (X) * sin(Theta) * cos(Phi) + (Y) * cos(Theta) * cos(Phi))
};

// funzione per disegnare una linea
static void DrawLine(int firstX, int firstY, int secondX, int secondY, HPEN Hpen)
{
	SelectObject(GHDC, Hpen);
	MoveToEx(GHDC, firstX, firstY, NULL);
	LineTo(GHDC, secondX, secondY);
	DeleteObject(Hpen);
}

// funzione per disegnare una linea avendo due punti
static void DrawLine(Point__ P1, Point__ P2, HPEN hpen)
{
	SelectObject(GHDC, hpen);
	MoveToEx(GHDC, P1.GetScreenX(), P1.GetScreenY(), NULL);
	LineTo(GHDC, P2.GetScreenX(), P2.GetScreenY());
	DeleteObject(hpen);
}

// funzione per calcolare l'incremento dei valori e dei pixel
static void IncrementCalculator(double zoom, double& pInc, double& vInc)
{
	// calcolo ordine di grandezza
	bool less;
	double comparator{ 1 };
	vInc = zoom;
	do (less = comparator < vInc) ? comparator *= 10 : comparator /= 10;
	while (comparator < vInc == less);
	less ? comparator /= 10 : comparator *= 10;

	// approssimazione
	if (vInc <= comparator) vInc = comparator;
	else if (vInc <= 4 * comparator) vInc = 2 * comparator;
	else vInc = 5 * comparator;
	pInc = 20 * vInc / zoom;
	if (pInc > 100) {
		pInc /= 10;
		vInc /= 10;
	}
	else if (pInc < 10) {
		pInc *= 10;
		vInc *= 10;
	}
}

// funzione per proiettare un punto in 2 dimensioni
static void ProjectPoint(tensor<long double> point, int& pointX, int& pointY)
{
	using namespace Window3Data;

	Phi += M_PI / 2;
	Matrix<> Rotation{
		{ cos(Theta), -sin(Theta), 0 },
		{ sin(Theta) * sin(Phi), cos(Theta) * sin(Phi), cos(Phi) },
		{ sin(Theta) * cos(Phi), cos(Theta) * cos(Phi), -sin(Phi) }
	};
	Phi -= M_PI / 2;

	auto Projection{ Rotation * point };
	pointX = Projection[0] * 20 / Zoom + ClientRect.right / 2;
	pointY = Projection[1] * 20 / Zoom + ClientRect.bottom / 2;
}

// funzione per proiettare una retta dallo spazio sullo schermo
static void ProjectAndDrawLine
(tensor<long double> start, tensor<long double> end, HPEN Hpen)
{
	int p1x, p1y, p2x, p2y;
	ProjectPoint(start, p1x, p1y);
	ProjectPoint(end, p2x, p2y);
	DrawLine(p1x, p1y, p2x, p2y, Hpen);
}

// funzione per disegnare 3 assi
static void DrawAxis(double pInc, double vInc)
{
	using namespace Window3Data;
	int OriginX{ ClientRect.right / 2 }, OriginY{ ClientRect.bottom / 2 };
	const int MarkLenght{ 5 };
	
	// Disegno assi completi
	tensor<int> pixelX, pixelY;
	tensor<wstring> PixelValues;
	for (int i = 0; i < 3; ++i) {
		double point_pos[3]{}, point_neg[3]{};
		double Value{ 300 };

		point_pos[i] = i == 1 ? -Value : Value;
		point_neg[i] = i == 1 ? Value : -Value;

		// calcolo punti
		int X1 = X2D(point_pos[0], point_pos[1], point_pos[2]);
		int Y1 = Y2D(point_pos[0], point_pos[1], point_pos[2]);
		int X2 = X2D(point_neg[0], point_neg[1], point_neg[2]);
		int Y2 = Y2D(point_neg[0], point_neg[1], point_neg[2]);

		// calcolo colore
		auto color{
			RGB(
				abs(point_pos[0]) / 100 * 255,
				abs(point_pos[2]) / 100 * 255,
				abs(point_pos[1]) / 100 * 255
			)
		};

		// output assi
		LOGBRUSH lb;
		lb.lbStyle = BS_SOLID;
		lb.lbColor = color;
		lb.lbHatch = 0;
		HPEN UsedPen = ExtCreatePen(PS_DOT, 1, &lb, 0, NULL);
		DrawLine(X1, Y1, OriginX, OriginY, CreatePen(PS_SOLID, 1, color));
		DrawLine(OriginX, OriginY, X2, Y2, UsedPen);

		// output valori degli assi
		auto Pxf{ X2 - OriginX };
		auto Pyf{ Y2 - OriginY };
		auto hyp{ hypot(Pxf, Pyf) };
		double _x{};
		
		// calcolo angoli
		auto PerpAngle = Pyf == 0 ? M_PI / 2 : atan(-double(Pxf) / Pyf);
		auto cX{ MarkLenght * cos(PerpAngle) };
		auto cY{ MarkLenght * sin(PerpAngle) };

		// iterazione
		for (double pixel = 0; pixel < hyp; pixel += pInc) {
			if (pixel == 0) continue;

			// calcolo coordinate del punto
			auto y = Pyf == 0 ? 0 :
				sqrt(fabs(pixel * pixel / (1 + pow((double(Pxf) / Pyf), 2))));
			auto x = Pyf == 0 ? pixel : y * double(Pxf) / Pyf ;
			if (x > 0 == Pxf > 0) x = -x;
			if (y > 0 != Pyf > 0) y = -y;

			// push
			auto X{ Handler(to_wstring(x)) };
			pixelX << OriginX + x << OriginX - x;
			pixelY << OriginY - y << OriginY + y;
			PixelValues << X << L"-" + X;

			// output tratti degli assi
			DrawLine(
				OriginX + x - cX,
				OriginY - y - cY,
				OriginX + x + cX,
				OriginY - y + cY,
				UsedPen
			);
			DrawLine(
				OriginX - x - cX,
				OriginY + y - cY,
				OriginX - x + cX,
				OriginY + y + cY,
				UsedPen
			);

			_x += vInc;
		}

		// nome asse
		wstring name{ wstring(1, L'x' + i) };
		TextOut(GHDC, X1, Y1, cstr(name));
	}
}

#pragma endregion

// funzioni per creare delle finestre e gestirle
#pragma region Windows

// funzione per elaborare gli input della finestra del grafico a una variabile
static LRESULT CALLBACK WindowProcessor2D(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	using namespace WindowData;
	switch (uMsg)
	{

		// finestra chiusa
	case WM_DESTROY:
		Zoom = 1;
		shiftX = 0;
		shiftY = 0;
		charVariable = __save;
		Variables = wstring(1, __save);
		PostQuitMessage(0);
		ret 0;

		// finestra ridimensionata
	case WM_SIZE: InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

		// pulsante
	case WM_COMMAND: {
		auto id{ LOWORD(wParam) };
		if ((id | 2) == id) {
			SetFocus(hwnd);
			ret 0;
		}
		bool derivate{ (id | FUNCTION_DERIVATIVE) == id };
		int index = id >> 2;
		
		// rimozione della funzione
		if (!derivate) {
			Indexlist.erase(Indexlist.begin() + index);
			memory(gIndex + 1);
			memory << Indexlist;
			gIndex++;
			redo = !Indexlist.empty();
			charVariable = __save;
			Variables = wstring(1, __save);

			// salvataggio dati
			auto shiftx{ shiftX };
			auto shifty{ shiftY };
			auto zoom{ Zoom };
			DestroyWindow(hwnd);
			shiftX = shiftx;
			shiftY = shifty;
			Zoom = zoom;
			ret 0;
		}
		
		// aggiunta della derivata
		auto derivative{ List[memory[gIndex][index]].Function.derivate(0) };
		if (derivative.num ==
			polynomial<>{ { { 0, tensor<int>(Variables.size(), 0) } } })
		{
			SetFocus(hwnd);
			ret 0;
		}
		DATA new_data{ derivative };
		for (const auto& indx : Indexlist) if (List[indx] == new_data) {
			SetFocus(hwnd);
			ret 0;
		}
		Indexlist << List.size();
		List << new_data;
		gIndex++;
		if (Indexlist > 10) {
			--Indexlist;
			gIndex--;
		}
		memory(gIndex);
		memory << Indexlist;
		redo = true;
		charVariable = __save;
		Variables = wstring(1, __save);

		// salvataggio dati
		auto shiftx{ shiftX };
		auto shifty{ shiftY };
		auto zoom{ Zoom };
		DestroyWindow(hwnd);
		shiftX = shiftx;
		shiftY = shifty;
		Zoom = zoom;
		ret 0;
	}

		// pressione tasto sinistro
	case WM_LBUTTONDOWN:
		enable = true;
		WindowData::Current = Coords = lParam;
		ret 0;

		// rilascio tasto sinistro
	case WM_LBUTTONUP:
		enable = false;
		WindowData::Current = lParam;
		ret 0;

		// traslazione
	case WM_MOUSEMOVE: {
		WindowData::Current = lParam;
		if (!enable) break;
		int OldXpos = (short)LOWORD(Coords), OldYpos = (short)HIWORD(Coords);
		int xPos = (short)LOWORD(lParam), yPos = (short)HIWORD(lParam);
		shiftX -= OldXpos - xPos;
		shiftY += OldYpos - yPos;
		Coords = lParam;
		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;
	}

		// zoom
	case WM_MOUSEWHEEL: {
		int WheelData = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		bool decrease{ WheelData < 0 };
		double amount = (GetKeyState(VK_MENU) & 0x8000) != 0 ? 3 : 1.2;
		WheelData = abs(WheelData);
		for (int i = 0; i < WheelData; ++i) {
			if (Zoom < 10000000 and decrease) Zoom *= amount;
			if (Zoom > 0.00001 and !decrease) Zoom /= amount;
		}
	}
		WindowData::Current = lParam;
		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

		// tasto premuto
	case WM_KEYDOWN:
		switch (wParam)
		{

			// invio
		case 13:
			Zoom = 1;
			shiftX = 0;
			shiftY = 0;
			charVariable = __save;
			Variables = wstring(1, __save);
			DestroyWindow(hwnd);
			ret 0;

			// reset
		case L'R':
			enable = false;
			Zoom = 1;
			shiftX = 0;
			shiftY = 0;
			break;

			// traslazione
		case L'D': shiftX += 10;
			break;
		case L'A': shiftX -= 10;
			break;
		case L'W': shiftY += 10;
			break;
		case L'S': shiftY -= 10;
			break;

			// zoom
		case 189: if (Zoom < 10000000) Zoom *= 1.2;
			break;
		case 187: if (Zoom > 0.00001) Zoom /= 1.2;
			break;

			// ctrl + y
		case L'Y': {
			if ((GetKeyState(VK_CONTROL) & 0x8000) == 0 or gIndex + 1 >= memory)
				ret 0;
			gIndex++;
			Indexlist = memory[gIndex];

			// salvataggio dati
			redo = true;
			auto shiftx{ shiftX };
			auto shifty{ shiftY };
			auto zoom{ Zoom };
			DestroyWindow(hwnd);
			shiftX = shiftx;
			shiftY = shifty;
			Zoom = zoom;
		}
			ret 0;

			// ctrl + z
		case L'Z': {
			if ((GetKeyState(VK_CONTROL) & 0x8000) == 0 or gIndex <= 0)
				ret 0;
			gIndex--;
			Indexlist = memory[gIndex];

			// salvataggio dati
			redo = true;
			auto shiftx{ shiftX };
			auto shifty{ shiftY };
			auto zoom{ Zoom };
			DestroyWindow(hwnd);
			shiftX = shiftx;
			shiftY = shifty;
			Zoom = zoom;
		}
			ret 0;

		default: ret DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

	case WM_PAINT: {
	
		// inizio disegno
		PAINTSTRUCT ps;
		RECT client;
		GetClientRect(hwnd, &client);
		if (client.right == 0 and client.bottom == 0)
			ret DefWindowProc(hwnd, uMsg, wParam, lParam);
		HDC hdc = BeginPaint(hwnd, &ps);
		GHDC = hdc;
		int OriginX{ client.right / 2 + shiftX };
		int OriginY{ client.bottom / 2 - shiftY };
		const int markLenght{ 3 };

		// impostazioni
		SetBkMode(hdc, TRANSPARENT);
		HFONT hFont = CreateFontW(
			16, 0, 0, 0,
			FW_BOLD,
			FALSE, FALSE, FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			L"Consolas"
		);
		SelectObject(hdc, hFont);
		double ValueIncrement, PixelIncrement;
		IncrementCalculator(Zoom, PixelIncrement, ValueIncrement);
		
		// calcolo valori e posizioni dei numeri degli assi
		tensor<int> NumbersX, NumbersY;
		tensor<wstring> ValsX, ValsY;
		int OldPixelValue{ OriginX };
		SIZE TextSize{ -50, 0 }, OldTextSize{ TextSize };
		double x{};

		// output valori di riferimento asse x positivo
		for (
			int pixel = OriginX;
			pixel < client.right;
			pixel += PixelIncrement
			)
		{
			HPEN hpen;
			DrawLine(
				pixel, OriginY - markLenght, pixel, OriginY + markLenght,
				CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
			);

			auto X{ Handler(to_wstring(x)) };
			GetTextExtentPoint32(hdc, cstr(X), &TextSize);
			if (OldPixelValue + OldTextSize.cx / 2
				- pixel + TextSize.cx / 2 + 10 < 0)
			{
				OldPixelValue = pixel;
				OldTextSize = TextSize;
				NumbersX << pixel - TextSize.cx / 2;
				ValsX << X;
				hpen = CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
			}
			else hpen = CreatePen(PS_DOT, 1, RGB(64, 64, 64));

			DrawLine(pixel, 0, pixel, client.bottom, hpen);
			x += ValueIncrement;
		}

		// output valori di riferimento asse x negativo
		OldPixelValue = OriginX;
		OldTextSize = TextSize = {};
		x = -ValueIncrement;
		for (
			int pixel = OriginX - PixelIncrement;
			pixel > 0;
			pixel -= PixelIncrement
			)
		{
			HPEN hpen;
			DrawLine(
				pixel, OriginY - markLenght, pixel, OriginY + markLenght,
				CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
			);

			auto X{ Handler(to_wstring(x)) };
			GetTextExtentPoint32(hdc, cstr(X), &TextSize);
			if (OldPixelValue - OldTextSize.cx / 2
				- pixel - TextSize.cx / 2 - 10 > 0)
			{
				OldPixelValue = pixel;
				OldTextSize = TextSize;
				NumbersX << pixel - TextSize.cx / 2;
				ValsX << X;
				hpen = CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
			}
			else hpen = CreatePen(PS_DOT, 1, RGB(64, 64, 64));

			DrawLine(pixel, 0, pixel, client.bottom, hpen);
			x -= ValueIncrement;
		}
					
		// output valori di riferimento asse y positivo
		OldPixelValue = OriginY;
		OldTextSize = TextSize = {};
		double y{ ValueIncrement };
		for (
			int pixel = OriginY - PixelIncrement;
			pixel > 0;
			pixel -= PixelIncrement
			)
		{
			HPEN hpen;
			DrawLine(
				OriginX - markLenght, pixel, OriginX + markLenght, pixel,
				CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
			);

			auto Y{ Handler(to_wstring(y)) };
			GetTextExtentPoint32(hdc, cstr(Y), &TextSize);
			if (pixel - OldTextSize.cy / 2
				- OldPixelValue - TextSize.cy / 2 < 0)
			{
				OldPixelValue = pixel;
				OldTextSize = TextSize;
				NumbersY << pixel - TextSize.cy / 2;
				ValsY << Y;
				hpen = CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
			}
			else hpen = CreatePen(PS_DOT, 1, RGB(64, 64, 64));
		
			DrawLine(0, pixel, client.right, pixel, hpen);
			y += ValueIncrement;
		}

		// output valori di riferimento asse y negativo
		OldPixelValue = OriginY;
		OldTextSize = TextSize = { 0, 26 };
		y = -ValueIncrement;
		for (
			int pixel = OriginY + PixelIncrement;
			pixel < client.bottom;
			pixel += PixelIncrement
			)
		{
			HPEN hpen;
			DrawLine(
				OriginX - markLenght, pixel, OriginX + markLenght, pixel,
				CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
			);
			
			auto Y{ Handler(to_wstring(y)) };
			GetTextExtentPoint32(hdc, cstr(Y), &TextSize);
			if (OldPixelValue + OldTextSize.cy / 2
				- pixel + TextSize.cy / 2 < 0)
			{
				OldPixelValue = pixel;
				OldTextSize = TextSize;
				NumbersY << pixel - TextSize.cy / 2;
				ValsY << Y;
				hpen = CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
			}
			else hpen = CreatePen(PS_DOT, 1, RGB(64, 64, 64));

			DrawLine(0, pixel, client.right, pixel, hpen);
			y -= ValueIncrement;
		}

		// output valori degli assi
		SetTextColor(hdc, RGB(192, 255, 255));
		for (size_t i = 0; i < NumbersX; ++i)
			TextOut(hdc, NumbersX[i], OriginY, cstr(ValsX[i]));
		for (size_t i = 0; i < NumbersY; ++i)
			TextOut(hdc, OriginX, NumbersY[i], cstr(ValsY[i]));

		// calcolo punti della funzione
		for (size_t i = 0; i < memory[gIndex]; ++i) {
			bool write{ false }, Enable{ true };
			tensor<int> Xcoord, Ycoord, asintothes;

			for (
				double __x = (-client.right / 2 - shiftX) * Zoom / 20;
				__x < (client.right / 2 - shiftX) * Zoom / 20;
				__x += 0.1 * Zoom
				)
			{

				// calcolo ordinate
				auto _den{
					List[memory[gIndex][i]].Function.den[0]({ __x })
					* LCM.Number<long double>()
				};
				if (_den == 0) continue;
				auto fx{ List[memory[gIndex][i]].Function.num[0]({ __x }) / _den };

				// output pixel
				int X = OriginX + __x * 20 / Zoom, Y = OriginY - fx * 20 / Zoom;
				if (Y > 0 and Y <= client.bottom and X > 0 and X <= client.right)
				{
					write = true;
					Enable = true;
					Xcoord << X;
					Ycoord << Y;
				}

				// gestione asintoti
				else if (write) {
					if (Enable) asintothes << X;
					Enable = false;
				}
			}

			// output grafico della funzione
			for (ptrdiff_t j = 0; j < (ptrdiff_t)Xcoord.size() - 1; ++j) {
				bool Continue{ false };
				for (const auto& asintothe : asintothes)
					if (Xcoord[j] < asintothe and asintothe < Xcoord[j + 1])
					{
						Continue = true;
						break;
					}

				if (Continue) continue;
				DrawLine(
					Xcoord[j], Ycoord[j], Xcoord[j + 1], Ycoord[j + 1],
					CreatePen(PS_SOLID, 2, List[memory[gIndex][i]].Color)
				);
			}
		}

		// assi x e y 
		DrawLine(
			OriginX, 0, OriginX, client.bottom,
			CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
		);
		DrawLine(
			0, OriginY, client.right, OriginY,
			CreatePen(PS_SOLID, 2, RGB(0, 128, 0))
		);

		// output punti stazionari
		tensor<wstring> PriorityLabels;
		tensor<int> PriorityLabelsX, PriorityLabelsY;
		tensor<int> PriorityLabelsCenterX, PriorityLabelsCenterY;
		int cursorX = (short)LOWORD(WindowData::Current);
		int cursorY = (short)HIWORD(WindowData::Current);
		for (size_t i = 0; i < memory[gIndex]; ++i)
			for (size_t j = 0; j < List[memory[gIndex][i]].States; ++j)
			{

				// impostazione colore
				SetTextColor(hdc, List[memory[gIndex][i]].Color);
				int X = OriginX + List[memory[gIndex][i]].StatX[j] * 20 / Zoom;
				int Y = OriginY - List[memory[gIndex][i]].StatY[j] * 20 / Zoom;
				for (int k = -2; k < 2; ++k) for (int l = -2; l < 2; ++l)
					SetPixel(hdc, X + k, Y + l, RGB(255, 255, 255));

				// calcolo testo
				wstring Out;
				switch (List[memory[gIndex][i]].States[j]) {
				case MIN: Out = L"minimo: (";
					break;
				case MAX: Out = L"massimo: (";
					break;
				case H_FLX: Out = L"flesso orizzontale: (";
					break;
				case A_FLX: Out = L"flesso ascendente: (";
					break;
				case D_FLX: Out = L"flesso discendente: (";
					break;
				}
				auto _X{ Handler(to_wstring(List[memory[gIndex][i]].StatX[j])) };
				auto _Y{ Handler(to_wstring(List[memory[gIndex][i]].StatY[j])) };

				// calcolo messaggio
				Out += _X + L"; " + _Y + L')';
				SIZE _TextSize;
				GetTextExtentPoint32(hdc, cstr(Out), &_TextSize);

				// calcolo priorità e output
				int CX{ X - _TextSize.cx / 2 }, CY{ Y - _TextSize.cy };
				int CX2{ X + _TextSize.cx / 2 }, CY2{ Y + _TextSize.cy / 2 };
				if (CX < cursorX and cursorX < CX2 and
					CY < cursorY and cursorY < CY2)
				{
					PriorityLabels << Out;
					PriorityLabelsX << CX;
					PriorityLabelsY << CY;
					PriorityLabelsCenterX << X;
					PriorityLabelsCenterY << Y;
				}
				else TextOut(hdc, CX, CY, cstr(Out));
			
				if (PriorityLabels.empty()) continue;
			
				// calcolo messaggio selezionato
				int MinRadius{ -1 }, MinRadiusIndex{};
				for (size_t k = 0; k < PriorityLabels; ++k) {
					int radius = hypot(
						cursorX - PriorityLabelsCenterX[k],
						cursorY - PriorityLabelsCenterY[k]
					);
					if (MinRadius < 0 or MinRadius > radius) {
						MinRadius = radius;
						MinRadiusIndex = k;
					}
				}

				// output messaggi restanti
				for (size_t k = 0; k < PriorityLabels; ++k) {
					if (k == MinRadiusIndex) {
						SetBkColor(hdc, RGB(255, 255, 255));
						SetTextColor(hdc, RGB(0, 0, 0));
						SetBkMode(hdc, OPAQUE);
						TextOut(
							hdc,
							PriorityLabelsX[k],
							PriorityLabelsY[k],
							cstr(PriorityLabels[k])
						);
						SetBkMode(hdc, TRANSPARENT);
						continue;
					}
					TextOut(
						hdc,
						PriorityLabelsX[k],
						PriorityLabelsY[k],
						cstr(PriorityLabels[k])
					);
				}
			}

		// fine disegno
		EndPaint(hwnd, &ps);
		ret 0;
	}

	default: ret DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	ret DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// funzione per creare la finestra del grafico a una variabile
static BOOL CreateGraph(Fraction<> funct)
{
	if (Variables.size() != 1) ret false;
	using namespace WindowData;

	// inizio
	__save = charVariable;
	charVariable = L'x';
	Variables = L"x";
	HINSTANCE hInstance = GetModuleHandle(0);
	
	// aggiunta
	bool present{ false };
	DATA new_data;
	if (funct.num.empty() and funct.den.empty()) goto WindowCreation;
	new_data = funct;
	for (const auto idx : memory[gIndex]) if (List[idx] == new_data) {
		present = true;
		break;
	}
	if (!present) {
		Indexlist << List.size();
		List << new_data;
		gIndex++;
		if (List > 10) {
			--Indexlist;
			gIndex--;
		}
	} 
	memory(gIndex);
	memory << Indexlist;
	if (memory == 2) {
		--memory;
		gIndex--;
	}

	// dati finestra
WindowCreation:
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProcessor2D;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"2Dgraph";
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	RegisterClass(&wc);

	// creazione finestra
	HWND hwnd = CreateWindowEx(
		0,
		L"2Dgraph", L"Grafico",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1200, 700,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd) ret false;
	ShowWindow(hwnd, SW_SHOW);

	// calcolo lunghezza massima
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	SIZE Maxlenght{};
	for (size_t i = 0; i < memory[gIndex]; ++i) {
		auto Text{ List[memory[gIndex][i]].ID };
		SIZE lenght{};
		GetTextExtentPoint32(hdc, cstr(Text), &lenght);

		if (Maxlenght.cx < lenght.cx) Maxlenght.cx = lenght.cx;
		if (Maxlenght.cy < lenght.cy) Maxlenght.cy = lenght.cy;
	}
	EndPaint(hwnd, &ps);

	// creazione pulsanti per ogni funzione
	tensor<HWND> ButtonList;
	for (size_t i = 0; i < memory[gIndex]; ++i) {

		// pulsante della funzione
		ButtonList << CreateWindowEx(
			0,
			L"BUTTON", List[memory[gIndex][i]].ID.c_str(),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			30, 30 + i * (2 * Maxlenght.cy + 20),
			Maxlenght.cx + 10, Maxlenght.cy + 10,
			hwnd,
			HMENU((i << 2) | FUNCTION_LABEL),
			hInstance,
			NULL
		);

		// pulsante della derivata
		ButtonList << CreateWindowEx(
			0,
			L"BUTTON", L"D",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			50 + Maxlenght.cx, 30 + i * (2 * Maxlenght.cy + 20),
			2 * Maxlenght.cy, 2 * Maxlenght.cy,
			hwnd,
			HMENU((i << 2) | FUNCTION_DERIVATIVE),
			hInstance,
			NULL
		);

		// pulsante di eliminazione
		ButtonList << CreateWindowEx(
			0,
			L"BUTTON", L"X",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			60 + Maxlenght.cx + 2 * Maxlenght.cy, 30 + i * (2 * Maxlenght.cy + 20),
			2 * Maxlenght.cy, 2 * Maxlenght.cy,
			hwnd,
			HMENU((i << 2) | FUNCTION_REMOVE),
			hInstance,
			NULL
		);
	}
	InvalidateRect(hwnd, NULL, FALSE);

	// ciclo dei messaggi
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bool result{ redo };
	redo = false;
	ret result;
}

// funzione per elaborare gli input della finestra del grafico a due variabili
static LRESULT CALLBACK WindowProcessor3D(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	using namespace Window3Data;
	switch (uMsg)
	{

		// finestra chiusa
	case WM_DESTROY:
		Zoom = 1;
		PostQuitMessage(0);
		ret 0;

		// finestra ridimensionata
	case WM_SIZE: InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

		// pressione tasto sinistro
	case WM_LBUTTONDOWN:
		enable = true;
		Window3Data::Current = Window3Data::Coords = lParam;
		ret 0;

		// rilascio tasto sinistro
	case WM_LBUTTONUP:
		enable = false;
		Window3Data::Current = lParam;
		ret 0;

		// traslazione
	case WM_MOUSEMOVE: {
		
		// premesse
		Window3Data::Current = lParam;
		if (!enable) break;
		int OldXpos = (short)LOWORD(Coords), OldYpos = (short)HIWORD(Coords);
		int xPos = (short)LOWORD(lParam), yPos = (short)HIWORD(lParam);
		
		// calcolo angoli nuovi
		long double radius{
			hypot(OldXpos - ClientRect.right / 2, OldYpos - ClientRect.bottom / 2)
		};
		Theta += 2 * asin((OldXpos - xPos) / (2 * radius));
		Phi += 2 * asin((OldYpos - yPos) / (2 * radius));
		
		// controlli
		if (Theta < 0) Theta += 2 * M_PI;
		if (Theta > 2 * M_PI) Theta -= 2 * M_PI;
		if (Phi < 0) Phi += 2 * M_PI;
		if (Phi > 2 * M_PI) Phi -= 2 * M_PI;

		Coords = lParam;
		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;
	}

		// zoom
	case WM_MOUSEWHEEL: {
		int WheelData = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		bool decrease{ WheelData < 0 };
		double amount = (GetKeyState(VK_MENU) & 0x8000) != 0 ? 3 : 1.2;
		WheelData = abs(WheelData);
		for (int i = 0; i < WheelData; ++i) {
			if (Zoom < 10000000 and decrease) Zoom *= amount;
			if (Zoom > 0.00001 and !decrease) Zoom /= amount;
		}
	}
		Window3Data::Current = lParam;
		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

	case WM_KEYDOWN:
		switch (wParam)
		{

			// invio
		case 13:
			DestroyWindow(hwnd);
			ret 0;

			// reset
		case L'R':
			Theta = M_PI / 4;
			Phi = M_PI / 3;
			Zoom = 1;
			break;

			// movimento
		case L'A':
			Theta += M_PI / 36;
			if (Theta < 0) Theta += 2 * M_PI;
			if (Theta > 2 * M_PI) Theta -= 2 * M_PI;
			break;
		case L'D':
			Theta -= M_PI / 36;
			if (Theta < 0) Theta += 2 * M_PI;
			if (Theta > 2 * M_PI) Theta -= 2 * M_PI;
			break;
		case L'W':
			Phi += M_PI / 36;
			if (Phi < 0) Phi += 2 * M_PI;
			if (Phi > 2 * M_PI) Phi -= 2 * M_PI;
			break;
		case L'S':
			Phi -= M_PI / 36;
			if (Phi < 0) Phi += 2 * M_PI;
			if (Phi > 2 * M_PI) Phi -= 2 * M_PI;
			break;

			// zoom
		case 189: if (Zoom < 10000000) Zoom *= 1.2;
			break;
		case 187: if (Zoom > 0.00001) Zoom /= 1.2;
			break;

		default: ret 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		ret 0;

		// disegno
	case WM_PAINT: {
		
		// inizio disegno
		PAINTSTRUCT ps;
		RECT client;
		GetClientRect(hwnd, &client);
		ClientRect = client;
		if (client.right == 0 and client.bottom == 0)
			ret DefWindowProc(hwnd, uMsg, wParam, lParam);
		HDC hdc = BeginPaint(hwnd, &ps);
		GHDC = hdc;
		
		// impostazioni
		SetTextColor(hdc, RGB(128, 128, 255));
		SetBkMode(hdc, TRANSPARENT);
		HFONT hFont = CreateFontW(
			16, 0, 0, 0,
			FW_BOLD,
			FALSE, FALSE, FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			L"Consolas"
		);
		SelectObject(hdc, hFont);

		double PixelIncrement, ValueIncrement;
		IncrementCalculator(Zoom, PixelIncrement, ValueIncrement);
		DrawAxis(PixelIncrement, ValueIncrement);

		// calcolo dei vertici dei quadrilateri
		tensor<tensor<Point__>> mesh;
		for (double x = -15 * Zoom; x < 15 * Zoom; x += 0.5 * Zoom)
		{
			tensor<Point__> points;
			for (double y = -15 * Zoom; y < 15 * Zoom; y += 0.5 * Zoom) {
				Point__ P{ Function, x, y };

				if (P.GetScreenY() < 0 or P.GetScreenY() > client.bottom) {
					points << Point__();
					continue;
				}
				P.SetNormalVector(PartialXder, PartialYder);
				points << P;
			}
			mesh << points;
		}
		
		// output quadrilateri
		for (size_t i = 0; i < mesh.size() - 1; ++i)
			for (size_t j = 0; j < mesh[i].size() - 1; ++j)
			{

				// esclusione di punti in più
				tensor<Point__> square{
					mesh[i][j], mesh[i][j + 1], mesh[i + 1][j], mesh[i + 1][j + 1]
				};
				for (const auto& P : square) if (P.Void()) continue;

				// vettori normali dei punti
				auto ii{ square[0].GetNormalVector() };
				auto ij{ square[1].GetNormalVector() };
				auto ji{ square[2].GetNormalVector() };
				auto jj{ square[3].GetNormalVector() };

				// calcolo vettore normale del quadrilatero
				tensor<long double> Normal{
					ii[0] + ij[0] + ji[0] + jj[0],
					ii[1] + ij[1] + ji[1] + jj[1],
					ii[2] + ij[2] + ji[2] + jj[2]
				};
				long double norm{ hypot(Normal[0], Normal[1], Normal[2]) };
				for (auto& component : Normal) component /= norm;

				// calcolo colore
				tensor<double> light{ 0, 0, 1 };
				auto dot{
					Normal[0] * light[0] +
					Normal[1] * light[1] +
					Normal[2] * light[2]
				};
				int RgbValue = clamp(int(255 * dot), 0, 255);
				if (RgbValue < 0) continue;

				// output
				DrawLine(
					square[0], square[1],
					CreatePen(PS_SOLID, 1, RGB(RgbValue, RgbValue, RgbValue))
				);
				DrawLine(
					square[0], square[2],
					CreatePen(PS_SOLID, 1, RGB(RgbValue, RgbValue, RgbValue))
				);
			}

		DrawAxis(PixelIncrement, ValueIncrement);

		// output punti stazionari
		for (size_t i = 0; i < StatX; ++i) {

			// output punto
			int pointX, pointY;
			ProjectPoint({ StatX[i], StatY[i], StatZ[i] }, pointX, pointY);
			for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k)
				SetPixel(hdc, pointX + j, pointY + k, RGB(255, 255, 255));

			// calcolo testo
			wstring Out;
			switch (def[i]) {
			case MINIMUM: Out = L"minimo: (";
				break;
			case MAXIMUM: Out = L"massimo: (";
				break;
			case SADDLE: Out = L"sella: (";
				break;
			case UNKNOWN: Out = L"punto stazionario: (";
				break;
			}
			auto _X{ Handler(to_wstring(StatX[i])) };
			auto _Y{ Handler(to_wstring(StatY[i])) };
			auto _Z{ Handler(to_wstring(StatZ[i])) };
			Out += _X + L"; " + _Y + L"; " + _Z + L')';

			// scrittura
			SIZE txtsize;
			GetTextExtentPoint32(hdc, cstr(Out), &txtsize);
			TextOut(hdc, pointX - txtsize.cx / 2, pointY + 10, cstr(Out));
		}

		// fine disegno
		EndPaint(hwnd, &ps);
		ret 0;
	}

	default: ret DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	ret DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// funzione per creare la finestra del grafico a due variabili
static void Project3DGraph(Fraction<> funct)
{
	if (Variables.size() != 2) ret;

	// calcolo dati della funzione
	using namespace Window3Data;
	Function = funct;
	PartialXder = Function.derivate(0);
	PartialYder = Function.derivate(1);
	StatX.clear();
	StatY.clear();
	StatZ.clear();
	auto StationaryPoints{
		SystemSolver({ PartialXder.num[0], PartialYder.num[0] })
	};
	for (size_t i = 0; i < StationaryPoints; ++i) {
		StatX << StationaryPoints[i][0];
		StatY << StationaryPoints[i][1];
		StatZ << Function({ StationaryPoints[i][0], StationaryPoints[i][1] });
	}

	// calcolo matrice hessiana
	Matrix<Fraction<>> Hessian{
		{ PartialXder.derivate(0), PartialXder.derivate(1) },
		{ PartialYder.derivate(0), PartialYder.derivate(1) },
	};
	for (size_t i = 0; i < StatX; ++i) {
		Matrix<> hessian(2);
		for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k)
			hessian[j] << Hessian[j][k]({ StatX[i], StatY[i] });

		// calcolo del delta
		long double A{ hessian[0][0] }, B{ hessian[0][1] };
		long double C{ hessian[1][0] }, D{ hessian[1][1] };
		long double delta{ A * A + D * D - 2 * A * D + 4 * B * C };

		// autovalori immaginari
		if (delta < 0) {
			def << UNKNOWN;
			continue;
		}

		// calcolo degli autovalori
		delta = sqrt(delta);
		long double e1{ (A + D + delta) / 2 }, e2{ (A + D - delta) / 2 };

		// decisione
		if (e1 == 0 or e2 == 0) def << UNKNOWN;
		else if (e1 > 0 != e2 > 0) def << SADDLE;
		else if (e1 > 0 and e2 > 0) def << MINIMUM;
		else def << MAXIMUM;
	}

	// dati finestra
	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProcessor3D;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"3Dgraph";
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	RegisterClass(&wc);

	// creazione finestra
	HWND hwnd = CreateWindowEx(
		0,
		L"3Dgraph", L"Grafico",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1200, 700,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd) ret;
	ShowWindow(hwnd, SW_SHOW);

	// ciclo dei messaggi
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

#pragma endregion

// funzioni di scomposizione di base per i numeri primi
#pragma region Operators

// calcola se un numero è primo
static bool Prime(ptrdiff_t number)
{
	if (number <= 1) ret false;
	if (number <= 3) ret true;
	if (number < GlobalMax) ret PrimeNumbers.is_prime[number];
	if (number % 2 == 0 or number % 3 == 0) ret false;
	for (size_t i = 5; i * i <= number; i += 6)
		if (number % i == 0 or number % (i + 2) == 0) ret true;
	ret true;
}

// calcola i numeri primi con il crivello di eratostene
static void PrimeNCalculator(ptrdiff_t max, ptrdiff_t min)
{
	_GetCursorPos();
	PrimeNumbers.is_prime(max + 1, true);

	const int BARWIDTH{ csbi.dwSize.X - 11 };
	int speed{ 50 }, iter{};
	const int SQUARE{ (int)sqrt(max) + 2 };

	// inizio
	system("cls");
	SetConsoleTextAttribute(hConsole, 4);
	wstring warning{
		L"ATTENIONE: Il tempo rimanente non è accurato all'inizio;"
	};
	warning.append(L" LIMITE DI CALCOLO = " + to_wstring(GlobalMax));
	if (BARWIDTH + 11 > warning.size()) wcout << warning;
	DECLARE_TIME_POINT(begin);
	ResetAttribute();

	for (ptrdiff_t p = 2; p < SQUARE; ++p)
	{
		if (!PrimeNumbers.is_prime[p]) continue;
		for (ptrdiff_t i = min - (min % p) + (p * p); i <= max; i += p)
			PrimeNumbers.is_prime[i] = false;

		// stampa barra di avanzamento
		if (iter % speed == 0) {
			DECLARE_TIME_POINT(stop);

			// output barra di avanzamento
			long double progress{ (long double)p / SQUARE };
			if (progress > 1) progress = 1;
			else if (progress > 0.5) speed = 15;
			ProgressBar(progress, BARWIDTH);

			// calcolo tempo rimanente
			int time = 1'000 * static_cast<double>(stop.QuadPart - begin.QuadPart)
				/ (ProgramFrequency.QuadPart);
			long double time_rem{ (time / progress) * (1 - progress) };
			long double time_seconds{ (long double)time_rem / 1'000 };

			// calcolo cifre decimali
			wostringstream stream;
			stream << fixed << setprecision(1) << time_seconds;
			wcout << L"\nTempo rimanente: " << stream.str() << L" [secondi]  ";
			if (speed < 75) speed += 5;
		}
		iter++;
	}

	// rimozione barra di avanzamento
	SetConsoleCursorPosition(hConsole, { 0, 0 });
	wcout << wstring(BARWIDTH + 11, L'§') << L"\n\n\r";
	wcout << wstring(BARWIDTH + 11, L' ') << L"attendere\r";
	
	// multithreading
	thread t1([&]() {
		for (ptrdiff_t p = min == 0 ? 2 : min + 1001; p < max + 1; ++p)
			if (PrimeNumbers.is_prime[p]) PrimeNumbers.list_primes << p;
		lock_guard<mutex> lock(mtx);
		IsDone = true;
		cv.notify_one();
		}
	);
	thread t2(CS_CenterPrinter);
	if (t1.joinable()) t1.join();
	if (t2.joinable()) t2.join();
}

// scompone un numero nei suoi fattori sottoforma di struttura
static tensor<compost> DecomposeNumber(ptrdiff_t input)
{

	// scomposizione
	int index{};
	tensor<compost> output(12, compost{ 0, 1 });
	for (size_t i = 0; _SQ(PrimeNumbers.list_primes[i]) <= input; ++i)
		if (input != 1) if (input % PrimeNumbers.list_primes[i] == 0)
		{
			// se un fattore è gia presente, incrementa l'esponente
			if (output[index].factors == PrimeNumbers.list_primes[i])
				output[index].exp++;

			// altrimenti aggiunge il fattore alla lista
			else output[index].factors = PrimeNumbers.list_primes[i];
			input /= PrimeNumbers.list_primes[i];

			// incrementa l'indice
			if (input % PrimeNumbers.list_primes[i] != 0) index++;
			i--;
		}

	// eccezione
	if (output[index].factors == input) output[index].exp++;
	else output[index].factors = input;

	ret output;
}

// divide una scomposizione singola
static tensor<int> DecomposeStrings(wstring terminal)
{
	int pass{}, CiphresElement;
	tensor<int> ciphres;
	for (size_t i = 0; i < terminal.size(); ++i) {

		// salta se pass è vero
		while (pass != 0) {
			pass--;
			i++;
		}

		// eccezioni
		if (i >= terminal.size()) ret ciphres;
		if (i == terminal.size() - 1) CiphresElement = terminal.at(i) - L'0';

		// caso di seconda eccezione
		else if (i > terminal.size() - 3) {
			if (terminal.at(i + 1) == L'0') {
				CiphresElement = 10 * (terminal.at(i) - L'0');
				pass = 1;
			}
			else CiphresElement = terminal.at(i) - L'0';
		}

		// caso con L'.'
		else if (terminal.at(i) == L'.') {
			CiphresElement = 10 * (terminal.at(i + 1) - L'0')
				+ (terminal.at(i + 2) - L'0');
			pass = 2;
		}

		// caso con gli zeri
		else {
			if (terminal.at(i + 1) == L'0') {
				CiphresElement = 10 * (terminal.at(i) - L'0');
				pass = 1;
			}

			// caso comune
			else CiphresElement = terminal.at(i) - L'0';
		}

		// aggiunta
		ciphres << CiphresElement;
	}

	ret ciphres;
}

// divide una scomposizione doppia
static tensor<wstring> Fractioner(wstring str)
{
	tensor<wstring> monomials;
	wstring temp;
	auto backup{ str };
	int ParenthesisBalance{}, Parenthesis{}, find{};
	for (const auto& ch : backup) {
		if (ch == L'(') ParenthesisBalance++;

		// solo in caso di bilancio tra le parentesi e carattere L'+'
		if (ParenthesisBalance == 0 and ch == L'+') {
			temp = str;
			for (size_t finder = 0; finder < temp.size(); ++finder) {

				// scomposizione in monomi
				if (find == 0) {
					if (temp.at(finder) == L'(') Parenthesis++;
					if (Parenthesis == 0 and temp.at(finder) == L'+')
						find = finder;
					if (temp.at(finder) == L')') Parenthesis--;
				}
			}

			// aggiunta dei monomi alla lista
			temp.erase(find);
			monomials << temp;
			str.erase(0, find + 1);
			find = 0;
		}
		if (ch == L')') ParenthesisBalance--;
	}
	monomials << str;

	ret monomials;
}

// scompone un polinomio nelle sue parti (non fattori)
static tensor<tensor<wstring>> FractPolynomial(wstring pol)
{

	// controllo estremi
	while (issign(Last(pol))) pol.pop_back();
	if (!issign(pol.at(0))) pol = L'+' + pol;

	// suddivisione in parti
	tensor<wstring> adders;
	int Parenthesis{};
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i) {

		switch (pol.at(i)) {
		case L'(': Parenthesis++;
			break;
		case L')': Parenthesis--;
			break;
		}

		if (issign(pol.at(i)) and Parenthesis == 0) {
			auto part{ pol };
			part.erase(0, i);
			if (part.at(0) == L'+') part.erase(0, 1);
			pol.erase(i);
			adders << part;
		}
	}

	// seconda suddivisione
	tensor<tensor<wstring>> factors(adders.size());
	for (size_t i = 0; i < adders; ++i) {

		auto adder{ adders[i] };
		for (ptrdiff_t j = adders[i].size() - 1; j >= 0;) {

			auto J{ j };
			auto FactorPart{ adder };
			int parenthesis{ adders[i].at(j) != L')' };
			for (ptrdiff_t k = FactorPart.size() - 1; k >= 0; --k) {

				switch (FactorPart.at(k)) {
				case L'(': parenthesis++;
					break;
				case L')': parenthesis--;
					break;
				}

				if (parenthesis == 0) {
					FactorPart.erase(0, k + (adders[i].at(j) != L')'));
					adder.erase(adder.size() - FactorPart.size());
					j = k;
					break;
				}
			}

			if (FactorPart == L"-") FactorPart = L"-1";
			factors[i] << FactorPart;
			if (j == J) break;
		}
	}

	// rimozione elementi nulli
	for (size_t i = 0; i < factors; ++i)
		for (ptrdiff_t j = factors[i].size() - 1; j >= 0; --j)
			if (factors[i][j].empty()) factors[i].erase(factors[i].begin() + j);
	for (ptrdiff_t i = factors.size() - 1; i >= 0; --i)
		if (factors[i].empty()) factors.erase(factors.begin() + i);

	ret factors;
}

#pragma endregion

// funzioni avanzate di scomposizione
#pragma region Calc

// esegue la scomposizione doppia
static wstring Cript(ptrdiff_t input)
{

	// calcolo già eseguito
	if (CalculatedData.find(input) != CalculatedData.end())
		ret CalculatedData[input];

	// scomposizione
	auto expfactors{ DecomposeNumber(input) };
	while (expfactors.last().factors == 0) expfactors--;
	wstring OutputString, ExpVerify, ExpString, PrimeExp_String, result;
	ptrdiff_t WhatFactor, prime_exp;
	int sizestring, presence;
	bool repeat;

	// itera sui fattori primi
	for (
		size_t FactorIndexAccesser = 0;
		FactorIndexAccesser < expfactors;
		++FactorIndexAccesser
		)
	{
		repeat = false;
		presence = 0;

		// esponente
		ExpVerify = to_wstring(expfactors[FactorIndexAccesser].exp);
		WhatFactor = expfactors[FactorIndexAccesser].factors;
		wstring start{ L"(" }, end{ L")" };

		// se l'esponente ha una cifra ed è maggiore di 1
		if (expfactors[FactorIndexAccesser].exp != 1 and
			expfactors[FactorIndexAccesser].exp < 11)
		{
			end += ExpVerify;
			presence = 1;
		}

		// se l'esponente ha due cifre
		else if (expfactors[FactorIndexAccesser].exp > 10) {
			end += L"." + ExpVerify;
			presence = 2;
		}

		// si esclude il caso di un esponente a tre cifre
		auto WhatFactorString{ to_wstring(WhatFactor) };
		OutputString = start + WhatFactorString + end;

		do {
			// caso con argomento primo
			while (Prime(WhatFactor)) {

				// ricerca binaria
				ptrdiff_t index = PrimeNumbers.list_primes.size() / 2;
				ptrdiff_t position{ -1 }, incr{ index };
				for (;;) {
					incr /= 2;
					if (incr == 0) incr = 1;
					if (PrimeNumbers.list_primes[index] > WhatFactor)
						index -= incr;
					else if (PrimeNumbers.list_primes[index] < WhatFactor)
						index += incr;
					else {
						position = index + 1;
						break;
					}
				}

				WhatFactor = position;
				WhatFactorString = to_wstring(WhatFactor);
				OutputString.erase(0, OutputString.find(L')'));
				OutputString = start + WhatFactorString + OutputString;

				// temporanea eliminazione dell'esponente normale
				switch (presence) {
				case 1:
					ExpString = wstring(1, Last(OutputString));
					OutputString.erase(OutputString.size() - 1);
					break;
				case 2:
					ExpString =
						L'.' +
						wstring(1, OutputString.at(OutputString.size() - 2)) +
						wstring(1, Last(OutputString));
					OutputString.erase(OutputString.size() - 3);
					break;
				}

				// aggiunta dell'esponente primo
				if (repeat) {
					PrimeExp_String = wstring(1, Last(OutputString));
					OutputString.erase(OutputString.size() - 1);
					prime_exp = stoull(PrimeExp_String) + 1;
					PrimeExp_String = to_wstring(prime_exp);

					if (prime_exp > 10) PrimeExp_String = L'.' + PrimeExp_String;
					OutputString += PrimeExp_String;
				}

				// riaggiunta dell'esponente normale
				else OutputString += L"1";
				if (presence > 0) OutputString += ExpString;
				repeat = true;
			}

			// caso con argomento composto
			if (WhatFactor != 1 and !Prime(WhatFactor)) {

				WhatFactorString = Cript(WhatFactor);

				OutputString.erase(0, OutputString.find(L')'));
				OutputString = start + WhatFactorString + OutputString;
				WhatFactor = 1;
			}

		} while (WhatFactor != 1);
		result += L'+' + OutputString;
	}
	result.erase(0, 1);

	// rimozione basi
	int position[12]{}, j{};
	for (int i = 0; i < result.size() - 2; ++i)
		if (
			result.at(i) == L'('
			and result.at(i + 1) == L'1'
			and result.at(i + 2) == L')'
			) position[j++] = i;
	for (int k = j - 1; k >= 0; --k) result.erase(position[k], 3);

	// eliminazione parentesi in più
	int l{};
	sizestring = result.size();
	if (sizestring > 4) {

		for (int m = 0; m < result.size() - 3; ++m)
			if ((result.at(m) == L'(') and (result.at(m + 3) == L')'))
				position[l++] = m;
		
		for (int m = l - 1; m >= 0; --m) {
			result.erase(position[m] + 3, 1);
			result.erase(position[m], 1);
		}
	}

	CalculatedData[input] = result;
	ret result;
}

// esegue la scomposizione singola
static wstring FactNumber(ptrdiff_t input)
{
	auto expfactors{ DecomposeNumber(input) };
	while (expfactors.last().factors == 0) expfactors--;

	// unione dei monomi
	wstring output;
	for (size_t i = 0; i < expfactors; ++i) {
		output += to_wstring(expfactors[i].factors);
		if (expfactors[i].exp != 1) output += L'^' + to_wstring(expfactors[i].exp);
		output += L" * ";
	}

	// rimozione della fine
	output.erase(output.size() - 3);
	
	ret output;
}

// calcola il valore aritmetico di un'espressione
static int ExeStrings(wstring input)
{
	bool presence{ true };
	int output{}, location{}, values[12]{};
	for (size_t i = 0; i < input.size(); ++i) if (input.at(i) == L'.')
		input.erase(i, 1);
	auto parts{ Fractioner(input) };

	for (size_t i = 0; i < parts; ++i)
	{
		// caso con le parentesi
		if (parts[i].at(0) == L'(') {

			// acquisizione dati
			for (ptrdiff_t j = parts[i].size() - 1; j >= 0; --j)
				if ((presence) and (parts[i].at(j) == L')')) {
					presence = false;
					location = j;
				}

			// calcolo risultato
			auto temp{ parts[i] };
			temp.erase(location);
			temp.erase(0, 1);
			parts[i].erase(0, location + 1);
			values[i] = ExeStrings(temp) * stoi(parts[i]);
		}

		// caso senza parentesi
		else values[i] = stoi(parts[i]);
		presence = true;
	}

	// somma dei monomi
	for (size_t end = 0; end < parts.size(); ++end) output += values[end];

	ret output;
}

// calcola i dati riguardanti i divisori di un numero
static divisor DivisorCalculator(wstring factor)
{
	divisor output{ 1, 1, 1, L"" };
	tensor<wstring> parts;
	tensor<ptrdiff_t> values;
	tensor<int> exponents;
	bool ExpPresence{ false };

	// scompozizione in monomi
	for (ptrdiff_t i = factor.size() - 1; i >= 0; --i) if (factor.at(i) == L'*')
	{
		auto backup{ factor };
		backup.erase(0, i + 2);
		if (Last(backup) == L' ') backup.pop_back();
		parts << backup;
		factor.erase(i);
	}

	// eccezione
	if (Last(factor) == L' ') factor.pop_back();
	parts << factor;

	// ricavo della scomposizione
	for (size_t i = 0; i < parts.size(); ++i) {
		ptrdiff_t value{}, exp{ 1 };
		ExpPresence = false;
		for (size_t j = 1; j < parts[i].size(); ++j)
			if (parts[i].at(j) == L'^') {
				value = stoull(parts[i].substr(0, j));
				exp = stoull(parts[i].substr(j + 1, parts[i].size() - 1));
				ExpPresence = true;
			}
		if (!ExpPresence) value = stoull(parts[i]);
		values << value;
		exponents << exp;
	}

	// calcolo del numero dei divisori
	for (size_t i = 0; i < parts; ++i) output.DivNumber *= exponents[i] + 1;

	// calcolo del numero risultato e della sua somma dei divisori
	ptrdiff_t x{ 1 };
	for (size_t i = 0; i < parts; ++i) {
		ptrdiff_t num = -1 + intpow(values[i], exponents[i] + 1);
		ptrdiff_t den{ values[i] - 1 };
		if (den != 0) output.DivSum *= (num / den);
		x *= intpow(values[i], exponents[i]);
	}

	// eccezione
	if (output.DivSum < 0) output.DivSum = -1;

	// calcolo del prodotto dei divisori
	if (output.DivNumber > 0) {
		double out{ (double)output.DivNumber / 2 };
		ptrdiff_t y;
		if (integer(out)) y = intpow(x, out);
		else y = intpow(x, out) * sqrt(x);
		if (y > 0) output.DivProduct = y;

		// caso di overflow
		else if (output.DivNumber % 2 == 0)
			output.Div_pr = to_wstring(x) + L'^' + to_wstring((ptrdiff_t)out);

		// caso di un quadrato perfetto pari
		else {
			output.Div_pr = to_wstring((ptrdiff_t)sqrt(x));
			output.Div_pr += L'^' + to_wstring((ptrdiff_t)(out * 2));
		}
	}

	// eccezione
	else {
		output.DivNumber = -1;
		output.DivProduct = -1;
	}

	ret output;
}

// calcola i dati riguardanti le cifre di un numero
static digitRatio DigitRationalizer(ptrdiff_t inpt)
{

	// calcolo somma e prodotto cifre
	digitRatio output;
	int digit_sum{}, digit_product{ 1 };
	auto input{ to_string(inpt) };
	for (size_t i = 0; i < input.size(); ++i) {
		digit_sum += input.at(i) - L'0';
		digit_product *= input.at(i) - L'0';
	}

	// calcolo rapporto per la somma
	if (items.digitSumRatioNum == 0 and inpt % digit_sum == 0)
	{
		output.digitSumRatioNum = 1;
		output.digitSumRatioDen = inpt / digit_sum;
	}
	else if (
		items.digitSumRatioNum * inpt ==
		items.digitSumRatioDen * digit_sum
		)
	{
		output.digitSumRatioNum = items.digitSumRatioNum;
		output.digitSumRatioDen = items.digitSumRatioDen;
	}

	// calcolo rapporto per il prodotto
	if (digit_product == 0) {
		output.digitProductRatioNum = 0;
		output.digitProductRatioDen = 0;
	}
	else if (items.digitProductRatioNum == 0 and inpt % digit_product == 0)
	{
		output.digitProductRatioNum = 1;
		output.digitProductRatioDen = inpt / digit_product;
	}
	else if (
		items.digitProductRatioNum * inpt ==
		items.digitProductRatioDen * digit_product
		)
	{
		output.digitProductRatioNum = items.digitProductRatioNum;
		output.digitProductRatioDen = items.digitProductRatioDen;
	}
	ret output;
}

// elenca i divisori di un numero
static tensor<int> DivisorCounter(int num)
{

	// creazione dei tensori con i principali fattori
	tensor<int> vec;
	auto expfact{ DecomposeNumber(num) };
	while (expfact.last().factors == 0) expfact--;

	tensor<tensor<int>> MainDiv;
	for (size_t i = 0; i < expfact; ++i) {
		MainDiv++;
		int EFelement{ 1 };
		for (int j = 0; j <= expfact[i].exp; ++j) {
			MainDiv[i] << EFelement;
			EFelement *= expfact[i].factors;
		}
	}

	// prodotto cartesiano
	tensor<int> temp;
	for (ptrdiff_t i = MainDiv.size() - 1; i > 0; --i) {
		for (const auto& a : MainDiv[i]) for (const auto& b : MainDiv[i - 1])
			temp << a * b;
		MainDiv[i - 1] = temp;
		MainDiv--;
	}

	ret MainDiv[0];
}

#pragma endregion

// funzioni con le istruzioni su quali calcoli eseguire e quali no
#pragma region Execute

// calcola il codice
static NumberData ExecuteSimpledeg(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	ret output;
}

// calcola codice, grado e sequenza
static NumberData ExecuteDegree(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	ptrdiff_t copy = input, counter{};

	// iterazione per ottenere grado e sequenza
	do {
		output.sequence << copy;
		copy = ExeStrings(Cript(copy));
		counter++;
		if (copy < 4) output.degree = counter + copy;
	} while (copy != 1);

	output.sequence << 1;
	copy = input;
	ret output;
}

// calcola la fattorizzazione
static NumberData ExecuteSimpleFact(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.expression = FactNumber(input);
	ret output;
}

// calcola fattorizzazione e divisori
static NumberData ExecuteFactor(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.expression = FactNumber(input);
	auto D{ DivisorCalculator(output.expression) };
	output.div = D;
	ret output;
}

// calcola fattorizzazione e codice
static NumberData ExecuteSimpleDF(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	output.expression = FactNumber(input);
	ret output;
}

// calcola le cifre (beta)
static NumberData ExecuteDigit(ptrdiff_t input)
{
	NumberData output;
	auto D{ DigitRationalizer(input) };
	output.number = input;
	output.digit = D;
	ret output;
}

// calcola codice, grado, sequenza, fattorizzazione e divisori
static NumberData ExecuteDegFactor(ptrdiff_t input)
{
	auto A{ ExecuteDegree(input) };
	auto B{ ExecuteFactor(input) };
	A.expression = B.expression;
	A.div = B.div;
	ret A;
}

// calcola codice, grado, sequenza e cifre
static NumberData ExecuteDegDigit(ptrdiff_t input)
{
	auto B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0) ret B;

	auto A{ ExecuteDegree(input) };
	A.digit = B.digit;
	ret A;
}

// calcola fattorizzazione, divisori e cifre
static NumberData ExecuteFactDigit(ptrdiff_t input)
{
	auto B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0) ret B;

	auto A{ ExecuteFactor(input) };
	A.digit = B.digit;
	ret A;
}

// calcola codice, grado, sequenza, fattorizzazione, divisori e cifre
static NumberData ExecuteAll(ptrdiff_t input)
{
	auto C{ ExecuteDigit(input) };
	if (C.digit.digitSumRatioNum == 0 and
		C.digit.digitProductRatioNum == 0) ret C;

	auto A{ ExecuteDegree(input) };
	auto B{ ExecuteFactor(input) };
	A.expression = B.expression;
	A.div = B.div;
	A.digit = C.digit;
	ret A;
}

#pragma endregion

// funzioni per validare un input utente
#pragma region Convalid

// convalida un polinomio senza parentesi
static wstring PolynomialSyntax(wstring pol)
{

	// caso vuoto
	if (pol.empty()) ret L"Il polinomio non può essere void";

	// controllo caratteri ammessi
	for (const auto& c : pol)
		if (!isalnum(c) and !issign(c) and c != L'^' and c != L' ' and c != L'/')
			ret L"Il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	for (size_t i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1)))
			ret L"Manca un monomio";
	if (!issign(pol.at(0))) pol = L'+' + pol;
	if (issign(Last(pol))) ret L"Manca un monomio";

	// controllo esponenti in forma di numero
	for (size_t i = 0; i < pol.size() - 1; ++i)
		if (pol.at(i) == L'^' and !isdigit(pol.at(i + 1)))
			ret L"Gli esponenti devono essere costanti";

	// suddivisione in parti
	tensor<wstring> parts;
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i) if (issign(pol.at(i))) {
		auto part{ pol };
		part.erase(0, i + 1);
		pol.erase(i);
		parts << part;
	}

	for (auto part : parts) {

		// controllo doppia divisione
		auto New{ part };
		if (New.find(L'/') != wstring::npos) New.erase(New.find(L'/'), 1);
		if (!New.empty()) if (New.find(L'/') != wstring::npos)
			ret L"E' possibile eseguire massimo una divisione per monomio";

		// controllo del denominatore
		if (part.find(L'/') != wstring::npos) {
			if (part.at(0) == L'/') ret L"Manca un numeratore";
			if (Last(part) == L'/') ret L"Manca un denominatore";
			if (!isdigit(Last(part))) ret L"Denominatore non valido";
			while (isdigit(Last(part))) {
				if (part.empty()) break;
				part.pop_back();
				if (Last(part) == L'/') {
					part.pop_back();
					break;
				}
				if (!isdigit(Last(part))) ret L"Denominatore non valido";
			}
		}
		if (part.empty()) continue;

		// cancellamento coefficiente
		while (isdigit(part.at(0))) {
			part.erase(0, 1);
			if (part.empty()) break;
		}
		if (part.empty()) continue;

		// controllo estremi
		if (part.at(0) == L'^' or Last(part) == L'^')
			ret L"Manca la base rispetto al relativo esponente";

		// controllo variabili ripetute
		for (size_t i = 0; i < part.size(); ++i)
			for (size_t j = i + 1; j < part.size(); ++j)
				if (isalpha(part.at(i)) and part.at(i) == part.at(j))
					ret L"Non è possibile ripetere le variabili nello stesso monomio";

		// controllo limite esponenti
		for (size_t i = 0; i < part.size() - 1; ++i) if (isdigit(part.at(i)))
			for (size_t j = i; j < part.size(); ++j) {
				if (j >= part.size()) break;
				if (!isdigit(part.at(j))) break;
				if (j - i >= 2) ret L"Gli esponenti sono troppo grandi";
			}

		// controllo coefficienti corretti
		for (size_t i = 1; i < part.size(); ++i) if (
			isdigit(part.at(i)) and
			!isdigit(part.at(i - 1)) and
			part.at(i - 1) != L'^'
			)
			ret L"Il coefficiente deve precedere il monomio";
	}

	ret L"";
}

// gestisce la convalidazione di un polinomio con le parentesi
static wstring PolynomialSyntaxDirector(wstring pol)
{
	
	// controllo asterischi
	if (pol.at(0) == L'*' or Last(pol) == L'*')
		ret L"Manca un termine";
	for (ptrdiff_t i = pol.size() - 2; i > 0; --i) if (pol.at(i) == L'*') {
		if (pol.at(i - 1) == '(' or pol.at(i + 1) == ')')
			ret L"Un asterisco non può essere racchiuso tra parentesi";
		if (pol.at(i - 1) == ')' or pol.at(i + 1) == '(') {
			pol.erase(i, 1);
			continue;
		}
		if (!isalnum(pol.at(i - 1)) or !isalnum(pol.at(i + 1)))
			ret L"Asterisco nel punto sbagliato";
		pol.erase(i, 1);
	}

	// caso vuoto
	for (ptrdiff_t i = 0; i < (ptrdiff_t)pol.size() - 2; ++i)
		if (pol.at(i) == L'(' and pol.at(i + 1) == L')')
			ret L"Il polinomio non può essere void";
	if (pol.empty()) ret L"Il polinomio non può essere void";

	// senza parentesi
	auto copy{ pol };
	if (copy.size() >= 2) {
		if (copy.at(0) == L'(') copy.erase(0, 1);
		if (Last(copy) == L')') copy.pop_back();
	}
	if (copy.find(L'(') == wstring::npos and copy.find(L')') == wstring::npos)
		ret PolynomialSyntax(copy);

	// controllo bilancio parentesi
	bool balanced{ false };
balance:
	int ParenthesisBalance{};
	for (const auto& c : copy) {
		switch (c) {
		case L'(': ParenthesisBalance++;
			break;
		case L')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) {
			if (!balanced) break;
			ret L"Le parentesi sono invertite";
		}
		if (ParenthesisBalance >= 100) ret L"Ci sono troppe parentesi";
	}
	if (ParenthesisBalance == 0) pol = copy;
	else if (!balanced) {
		balanced = true;
		copy = pol;
		goto balance;
	}
	else ret L"Le parentesi sono sbilanciate";

	// rimozione spazi
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i)
		if (pol.at(i) == L' ' or pol.at(i) == L'\t') pol.erase(i, 1);

	// controllo caratteri non ammessi
	for (const auto& c : pol)
		if (!isalnum(c) and !issign(c)
			and c != L'(' and c != L')' and c != L'^' and c != L'/'
			)
			ret L"Il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	bool error{ true };
	for (const auto& c : pol) if (!issign(c)) error = false;
	if (error) ret L"Non è presente alcun monomio";
	for (size_t i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1))) ret L"Manca un monomio";
	if (pol.at(0) == L'^') ret L"Manca la base rispetto al relativo esponente";

	// controllo di ogni parte
	auto fact = FractPolynomial(pol);
	for (const auto& adder : fact) if (adder > 10)
		ret L"Il polinomio è troppo grande";
	for (auto adder : fact) for (auto element : adder) {
		if (PolynomialSyntaxDirector(element).empty()) continue;

		// controlli aggiuntivi
		if (element.find(L'/') != wstring::npos) if (!isdigit(Last(element)))
			ret L"I denominatori devono essere costanti";

		bool exp{ element.size() > 1 and element.size() < 4 };
		if (exp) if (element.at(0) == L'^')
			for (size_t i = 1; i < element.size(); ++i) if (!isdigit(element.at(i)))
				ret L"Gli esponenti devono essere costanti";
	}

	ret L"";
}

// aggiorna una stringa di codice
static wstring UpdateString(wstring& ToEvaluate)
{
	// controllo sulle doppie parentesi
	int BoundaryBalance{};
	for (const auto& c : ToEvaluate) {
		switch (c) {
		case L'<': BoundaryBalance++;
			break;
		case L'>': BoundaryBalance--;
			break;
		}
		if (BoundaryBalance > 1 or BoundaryBalance < 0)
			ret L"Le parentesi di delimitazione non possono essere doppie";
	}

	// suddivisione della stringa in pezzi
	tensor<wstring> pieces;
	bool start{ true };
	for (ptrdiff_t i = ToEvaluate.size() - 1; i >= 0; --i) {

		wstring piece{ ToEvaluate };
		if (ToEvaluate.at(i) == L'>') {
			piece.erase(0, i + 1);
			if (i + 1 < ToEvaluate.size()) ToEvaluate.erase(i + 1);
			if (start) start = false;
		}
		else if (ToEvaluate.at(i) == L'<' and !start) {
			piece.erase(0, i);
			ToEvaluate.erase(i);
		}
		else continue;
		pieces << piece;
	}
	if (!ToEvaluate.empty()) pieces << ToEvaluate;

	// controllo parentesi
	for (auto piece : pieces) {
		if (piece.empty()) continue;
		if (piece.at(0) == L'<' and Last(piece) == L'>') {
			piece.pop_back();
			piece.erase(0, 1);
		}
		if (piece.find(L'<') != wstring::npos or piece.find(L'>') != wstring::npos)
			ret L"Le parentesi di delimitazione sono al contrario";
	}

	// creazione nuova stringa
	ToEvaluate.clear();
	for (auto piece : pieces) {
		if (piece.empty()) continue;
		if (piece.at(0) == L'<') {
			piece.pop_back();
			piece.erase(0, 1);
			ToEvaluate = piece + ToEvaluate;
		}
		else {
			for (ptrdiff_t i = piece.size() - 1; i >= 0; --i)
				if (!isdigit(piece.at(i)) or piece.at(i) > 127) piece.erase(i, 1);
			if (piece.empty()) continue;
			int number = stoi(piece);
			if (number > GlobalMax or number <= 0) ret L"XRANGE";
			ToEvaluate = Cript(number) + ToEvaluate;
		}
	}
	ret L"";
}

// convalida una stringa di codice
static wstring NumberCodeSyntax(wstring ToEvaluate)
{
	if (ToEvaluate == L"f") ret L"";
	tensor<wstring> mono;
	bool LocError{ true };
	int ParenthesisBalance{};

	// eliminazione degli spazi e dei tab
	for (ptrdiff_t space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
			ToEvaluate.erase(space, 1);

	// ricerca del bilancio tra le parentesi
	for (size_t i = 0; i < ToEvaluate.size(); ++i) {
		switch (ToEvaluate.at(i)) {
		case L'(': ParenthesisBalance++;
			break;
		case L')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) ret L"Le parentesi sono invertite";
		if (ParenthesisBalance >= 100) ret L"Ci sono troppe parentesi";
	}
	if (ParenthesisBalance != 0) ret L"Le parentesi sono sbilanciate";
	
	// se la stringa è vuota
	if (ToEvaluate.empty()) ret L"La stringa è vuota";

	// se la stringa contiene caratteri non ammessi
	if (regex_search(ToEvaluate, wregex(L"[^\\d+()._]")))
		ret L"Sono presenti dei caratteri non ammessi";

	// controllo sugli estremi
	if (ToEvaluate.at(0) == L'+') ret L"Manca un monomio a inizio stringa";
	if (ToEvaluate.at(0) == L'0') ret L"Un monomio non può essere null";
	if (ToEvaluate.at(0) == L')') ret L"Le parentesi sono al contrario";
	if (Last(ToEvaluate) == L'+') ret L"Manca un monomio alla fine della stringa";

	// controllo sulla non consecutività dei L'+'
	if (regex_search(ToEvaluate, wregex((L"\\+{2,}"))))
		ret L"Manca un monomio al centro della stringa";

	// controlli sugli zeri
	if (regex_search(ToEvaluate, wregex(L"0{2,}")))
		ret L"Le cifre null non possono essere consecutive";
	if (regex_search(ToEvaluate, wregex(L"\\.")))
		if (!regex_search(ToEvaluate, wregex(L"[_\\d]\\.[_1-9][_\\d]")))
			ret L"Esponente a due cifre impostato in modo errato";
	if (regex_search(ToEvaluate, wregex(L"[\\r\\D]0")))
		ret L"Un monomio non può essere null";

	mono = Fractioner(ToEvaluate);

	// per ogni monomio
	for (size_t indexof = 0; indexof < mono; ++indexof) {
		ptrdiff_t stackfinder{ -1 }, stickfinder{ -1 }, FindIndex{ -1 };
		bool stop{ false };
		int res{};
		tensor<int> min_ciphres, max_ciphres;
		tensor<int> ciphr_min, ciphr_max;
		wstring min, max;
		auto stack{ mono[indexof] };

		// per ogni secondo monomio
		for (size_t second = 1; second < mono; ++second) {
			if (indexof != second) {
				if (mono[indexof] == mono[second]) ret L"1";
				wstring stick{ mono[second] };

				// paragone tra le dimensioni dei monomi
				if (stack.size() < stick.size()) {
					min = stack;
					max = stick;
				}
				else {
					min = stick;
					max = stack;
				}

				// caso con le parentesi
				if (stack.at(0) == L'(' or stick.at(0) == L')') {

					// ricerca delle parentesi
					stackfinder = stack.find(L')');
					stickfinder = stick.find(L')');
					if (stackfinder == wstring::npos) stackfinder = -1;
					if (stickfinder == wstring::npos) stickfinder = -1;

					// caso con solo un monomio dotato di parentesi
					if (stackfinder * stickfinder < 0) {
						if (stackfinder > 0) FindIndex = stackfinder;
						else FindIndex = stickfinder;
					}

					// caso con i monomi corrispondenti
					else if (stickfinder == stackfinder) {
						FindIndex = stackfinder;
						for (int l = 0; l <= FindIndex + 1; ++l) if (l < min.size())
							if (stick.at(l) != stack.at(l)) stop = true;
						auto min_backup{ min };
						auto max_backup{ max };
						min_backup.erase(0, FindIndex + 2);
						max_backup.erase(0, FindIndex + 2);
						min_ciphres = DecomposeStrings(min_backup);
						max_ciphres = DecomposeStrings(max_backup);
						if (min_ciphres < max_ciphres) {
							ciphr_min = min_ciphres;
							ciphr_max = max_ciphres;
						}
						else {
							ciphr_min = max_ciphres;
							ciphr_max = min_ciphres;
						}
						for (size_t l = 0; l < ciphr_min; ++l) {
							if (!stop and ciphr_min[l] == ciphr_max[l]) {
								res++;
								if (ciphr_min[l] != ciphr_max[l]) stop = true;
							}
							else stop = true;
						}
					}
				}

				// caso senza le parentesi
				else {

					// paragone tra il numero dei fattori
					min_ciphres = DecomposeStrings(min);
					max_ciphres = DecomposeStrings(max);
					if (min_ciphres < max_ciphres) {
						ciphr_min = min_ciphres;
						ciphr_max = max_ciphres;
					}
					else {
						ciphr_min = max_ciphres;
						ciphr_max = min_ciphres;
					}

					// conta delle ripetizioni
					for (size_t l = 0; l < ciphr_min; ++l) {
						if (!stop and ciphr_min[l] == ciphr_max[l]) {
							res++;
							if (ciphr_min[l] != ciphr_max[l]) stop = true;
						}
						else stop = true;
					}
				}

				if (
					res % 2 == 1 and
					ciphr_max.size() - ciphr_min.size() <= 1 and
					ciphr_max <= 1 + res and ciphr_min <= 1 + res
					)
					ret L"2";
			}
		}

		// // controlli sugli oggetti adiacenti alle parentesi
		for (ptrdiff_t i = stack.size() - 1; i >= 0; --i) if (stack.at(i) == ')') {
			FindIndex = i;
			break;
		}
		if (Last(stack) == L')') ret L"Manca l'esponente di fianco a una parentesi";
		if (Last(stack) == L'(') ret L"Le parentesi sono al contrario";
		if (stack.at(0) == L'(') {

			// controllo sulla necessità delle parentesi
			LocError = true;
			for (ptrdiff_t checkplus = 1; checkplus < FindIndex; ++checkplus)
				if (stack.at(checkplus) == L'+') LocError = false;
			if (LocError) ret L"Ci sono troppe parentesi";

			stack.erase(0, 1);
			stack.erase(FindIndex - 1);
			auto message{ NumberCodeSyntax(stack) };
			if (!message.empty()) ret message;
		}
		else if (mono[indexof].at(0) == L')') ret L"Le parentesi sono al contrario";
		else for (size_t check = 1; check < mono[indexof].size(); ++check)
			if (mono[indexof].at(check) == L'(' or mono[indexof].at(check) == L')')
				ret L"L'esponente non può precedere una parentesi";
		// //
	}

	ret L"";
}

#pragma endregion

// funzioni per convertire da codice a numero
#pragma region Converters

// calcola il valore di un singolo elemento del codice
static ptrdiff_t NumberConverter(size_t root, wstring M)
{
	bool WhichWay{ true }, XOutOfRange{ false };
	bool UselessExponent{ false };
	bool XSubscriptOutOfRange{ false };
	int size = PrimeNumbers.list_primes.size(), nums;
	auto ciphres{ DecomposeStrings(M) };

	// per ogni cifra
	for (size_t iter = 0; iter < ciphres; ++iter) {

		WhichWay = !WhichWay;
		nums = ciphres[iter];

		// caso esponente
		if (!XOutOfRange and WhichWay) {
			UselessExponent = nums == 1;
			root = intpow(root, nums);
		}

		// caso esponente primo
		else do {
			if (!XOutOfRange and root < size) {
				if (root > 0) root = PrimeNumbers.list_primes[root - 1];
				else XSubscriptOutOfRange = true;
				nums--;
			}
			else XOutOfRange = true;
		} while (!XSubscriptOutOfRange and !XOutOfRange and nums != 0);
		
	}

	// eccezioni
	if (XSubscriptOutOfRange) ret -3;
	if (UselessExponent) ret -2;
	if (XOutOfRange) ret -1;

	ret root;
}

// calcola il valore del codice di codice
static ptrdiff_t StringConverter(wstring ToEvaluate)
{
	size_t integer{ 1 };
	auto mono{ Fractioner(ToEvaluate) };

	// per ogni monomio
	for (size_t indexof = 0; indexof < mono; ++indexof) {

		// calcolo indice
		auto M{ mono[indexof] };
		ptrdiff_t FindIndex{ -1 };
		for (ptrdiff_t i = M.size() - 1; i >= 0; --i) if (M.at(i) == ')') {
			FindIndex = i;
			break;
		}
		ptrdiff_t root;
		if (M.at(0) != L'(') root = NumberConverter(1, M);
		
		// calcolo valori
		else root = NumberConverter(
			StringConverter(M.substr(1, FindIndex - 1)),
			M.substr(FindIndex + 1, M.size() - 1)
		);

		if (root < 0) ret root; // eccezione
		else integer *= root; // caso comune
	}

	ret integer;
}

// gestisce i messaggi di errore riguardanti il codice
static void CodeConverter
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));
	ptrdiff_t number;
	if (ToEvaluate == L"f") ret;

	for (ptrdiff_t space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
			ToEvaluate.erase(space, 1);
	if (NecBoundary) UpdateString(ToEvaluate);
	number = StringConverter(ToEvaluate);

	// caso normale
	if (ShowErrors or number > 0) {
		auto text{ L"codice <" + ToEvaluate + L"> :\n" };
		ConsoleText << Console{ text , 11 };
	}

	// caso con overflow interno
	if (number < -2 and ShowErrors) {
		auto text{ L"ERR[413]: X_SUBSCRIPT_OUT_OF_RANGE\n" };
		ConsoleText << Console{ text , 12 };
	}

	// caso di comune overflow
	if (number == -1 and ShowErrors) {
		auto text{ L"ERR[413]: X_OUT_OF_RANGE\n" };
		ConsoleText << Console{ text , 12 };
	}

	// caso errato per esponente inutile
	if (number == -2 and ShowErrors) {
		auto text{ L"ERR[413]: USELESS_EXPONENT\n" };
		ConsoleText << Console{ text , 6 };
	}

	// caso errato con correzione
	if (!message.empty() and ShowErrors and number > 0) {

		wstring text{
			message == L"1" ?
			L"ERR[400]: EQUAL_MONOMIALS\n" :
			L"ERR[400]: SIMILIAR_MONOMIALS\n"
		};
		ConsoleText << Console{ text , 15 };

		if (number < GlobalMax) text = L"codice corretto: <" + Cript(number) + L">\n";
		else text = L"codice corretto non disponibile\n";

		ConsoleText << Console{ text , 2 };
	}

	// caso con errori nascosti per scelta utente
	if (number > 0) {
		auto text{ L"il numero corrispondente e' " };
		ConsoleText << Console{ text , 15 };
		ConsoleText << Console{ to_wstring(number) + L'\n' , 4 };
	}
}

// gestisce i codici da calcolare in numero
static void LongComputation
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
{
	computing = true;
	interrupted = false;

	// conta dei caratteri L'_' e archivio della posizione
	auto backup{ ToEvaluate };
	int counter{};
	tensor<size_t> pos;
	for (size_t i = 0; i < ToEvaluate.size(); ++i) if (ToEvaluate.at(i) == L'_')
	{
		pos << i;
		counter++;
	}

	// caso di stringa univoca
	if (counter == 0) {
		lock_guard<mutex> lock(CoutMutex);
		CodeConverter(ToEvaluate, message, ShowErrors, NecBoundary);
		ConsoleText.log();
	}

	// caso di stringa ripetuta
	else for (size_t i = 0; i < intpow(10, counter); ++i) {

		// uscita
		{
			lock_guard<mutex> lock(mtx);
			if (GlobalInterr) break;
		}

		// passa variabili per indirizzo
		thread comp_thread([&]() {

			auto j{ to_wstring(i) };
			backup = ToEvaluate;
			int ZerosCount = counter - j.size();
			for (int k = 0; k < ZerosCount; ++k) j = L"0" + j;
			for (size_t k = 0; k < j.size(); ++k)
				backup.replace(pos[k], 1, wstring(1, j.at(k)));
			if (NecBoundary) UpdateString(backup);
			message = NumberCodeSyntax(backup);

			// eventuale stampa degli errori
			{
				lock_guard<mutex> lock(mtx);
				if (message.size() > 1 and ShowErrors) {

					auto text{ L"codice <" + backup + L"> :\n" };
					ConsoleText << Console{ text , 11 };

					text = L"ERR[404]: " + message + L"\n";
					ConsoleText << Console{ text , 4 };
				}
				else CodeConverter(backup, message, ShowErrors, false);
				if (interrupted) ret;

				IsDone = true;
				cv.notify_one();
			}

			}
		);
		thread output_thread(CS_CornerPrinter);
		if (comp_thread.joinable()) comp_thread.join();
		if (output_thread.joinable()) output_thread.join();

		ConsoleText.log();

		// uscita
		{
			lock_guard<mutex> lock(mtx);
			if (GlobalInterr) break;
		}
	}

	Cv.notify_all();
	computing = false;
	interrupted = true;
}

#pragma endregion

// funzioni necessarie per tradurre i polinomi in strutture
#pragma region Translate

// traduce un polinomio senza parentesi
static factor<big> GetMonomials(wstring pol)
{
	factor<big> out;
	if (pol.empty()) ret {};
	if (!issign(pol.at(0))) pol = L'+' + pol;
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i) if (issign(pol.at(i))) {
		auto part{ pol };
		pol.erase(i);
		part.erase(0, i);

		// calcolo del numeratore
		big Numerator = LCM;
		if (part.find(L'/') != wstring::npos) {
			auto Denominator{ part };
			Denominator.erase(0, part.find(L'/'));
			Numerator /= Denominator;
		}

		// calcolo segno
		monomial<big> mono{ 1, tensor<int>(Variables.size(), 0) };
		if (part.at(0) == L'-') mono.coefficient = -1;
		part.erase(0, 1);

		// calcolo coefficiente
		wstring coeff;
		while (isdigit(part.at(0))) {
			coeff += part.at(0);
			part.erase(0, 1);
			if (part.empty()) break;
		}
		big Coeff = 0;
		for (size_t j = 0; j < coeff.size(); ++j) {
			Coeff += coeff.at(j) - '0';
			if (j < coeff.size() - 1) Coeff *= 10;
		}
		if (coeff.empty()) Coeff = 1;
		if (mono.coefficient < 0) Coeff.invert();
		mono.coefficient = Coeff * Numerator;
		if (part.empty()) {
			out << mono;
			continue;
		}

		// calcolo gradi
		for (ptrdiff_t j = 0; j < part.size(); ++j) if (isalpha(part.at(j))) {

			// calcolo posizione
			size_t VariableIndex{};
			for (size_t k = 0; k < Variables.size(); ++k)
				if (Variables.at(k) == part.at(j)) {
					VariableIndex = k;
					break;
				}

			// calcolo grado
			int degree{ 1 };
			if (j < (ptrdiff_t)part.size() - 2)
				if (part.at(j + 1) == L'^' and isdigit(part.at(j + 2))) {
					degree = part.at(j + 2) - L'0';
					if (j < (ptrdiff_t)part.size() - 3) if (isdigit(part.at(j + 3)))
						degree = 10 * degree + part.at(j + 3) - L'0';
				}
			mono.exp[VariableIndex] = degree;
		}
		out << mono;
	}

	ret out;
}

// gestisce la traduzione di un polinomio con le parentesi
static polynomial<big> GetMonomialsRedirector(wstring pol)
{

	// caso senza parentesi
	auto copy{ pol };
	if (copy.size() >= 2) {
		if (copy.at(0) == L'(') copy.erase(0, 1);
		if (Last(copy) == L')') copy.pop_back();
	}
	if (copy.find(L'(') == wstring::npos and copy.find(L')') == wstring::npos)
		ret polynomial<big>{ PolynomialSum<big>(GetMonomials(copy)) };

	// eliminazione parentesi in più
	int ParenthesisBalance{};
	for (const auto& c : copy) {
		switch (c) {
		case L'(': ParenthesisBalance++;
			break;
		case L')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) break;
	}
	if (ParenthesisBalance == 0) pol = copy;

	// calcolo monomi delle parti
	auto fact{ FractPolynomial(pol) };
	tensor<int> null(Variables.size(), 0);
	tensor<polynomial<big>> Union;
	
	for (const auto& adder : fact) {
		polynomial<big> UnionElement(adder.size());
		tensor<long double> ExpPos, ExpVal;
		for (size_t i = 0; i < adder; ++i) {

			// esponente
			if (adder[i].at(0) == L'^') {
				int value{ adder[i].at(1) - L'0' };
				if (adder[i].size() > 2) value = 10 * value + adder[i].at(2) - L'0';
				ExpPos << i;
				ExpVal << value;
			}

			// fattore
			else UnionElement[i] =
				PolynomialMultiply<big>(GetMonomialsRedirector(adder[i]));
		}

		// aggiunta
		for (size_t i = 0; i < ExpPos; ++i)
			UnionElement[ExpPos[i]] = { { ExpVal[i], {-1} } };
		Union << UnionElement;
	}

	// aggiunta di spazio
	for (size_t i = 0; i < Union; ++i) for (size_t j = 0; j < Union[i]; ++j) {
		for (size_t k = 0; k < Union[i][j]; ++k)
			Union[i][j][k].exp(Variables.size(), 0);
		Union[i][j] = PolynomialSum(Union[i][j]);
	}

	// correzione numeratori
	size_t sizemax{};
	for (auto P : Union) if (P > sizemax) sizemax = P.size();
	for (auto& P : Union) {
		big NewLcm = LCM ^ int(sizemax - P.size());
		for (auto& mon : P[0]) mon.coefficient *= NewLcm;
	}

	// aggiustamento segni
	tensor<big> numbers;
	for (size_t i = 0; i < Union; ++i) {
		Union[i].open();

		// calcolo segno
		int sign{ 1 };
		for (size_t j = 0; j < Union[i]; ++j) {
			Union[i][j].SortByExponents();
			if (Union[i][j][0].coefficient < 0) {
				sign *= -1;
				for (size_t k = 0; k < Union[i][j]; ++k)
					Union[i][j][k].coefficient.invert();
			}
		}

		// calcolo coefficiente
		big Coeff = sign;
		for (ptrdiff_t j = Union[i].size() - 1; j >= 0; --j) if (Union[i][j] == 1)
		{
			bool IsACoefficient{ true };
			for (size_t k = 0; k < Variables.size(); ++k)
				if (Union[i][j][0].exp[k] != 0) IsACoefficient = false;
			if (IsACoefficient) {
				Coeff *= Union[i][j][0].coefficient;
				Union[i].erase(Union[i].begin() + j);
			}
		}

		// push coefficiente
		Union[i] >> factor<big>{ { Coeff, null } };
		numbers << Coeff;
	}
	auto gcd{ Gcd(numbers).fabs() };
	if (gcd == 0) ret polynomial<big>{ { { 0, null } } };
	if (gcd != 1) for (size_t i = 0; i < Union; ++i)
		Union[i][0][0].coefficient /= gcd;

	// ricerca fattori in comune
	auto ListCommonFactors{ Union[0] };
	--ListCommonFactors;
	for (ptrdiff_t i = ListCommonFactors.size() - 1; i >= 0; --i) {
		bool IsCommon{ true };
		for (size_t j = 1; j < Union; ++j) {
		
			bool common{ false };
			for (size_t k = 0; k < Union[j]; ++k)
				if (ListCommonFactors[i] == Union[j][k]) common = true;

			if (!common) {
				IsCommon = false;
				break;
			}
		}

		// rimozione fattore non in comune dalla lista
		if (!IsCommon) ListCommonFactors.erase(ListCommonFactors.begin() + i);

		// rimozione fattore in comune dall'insieme
		else for (size_t j = 0; j < Union; ++j)
			for (ptrdiff_t k = Union[j].size() - 1; k >= 0; --k)
				if (Union[j][k] == ListCommonFactors[i]) {
					Union[j].erase(Union[j].begin() + k);
					break;
				}
	}
	ListCommonFactors >> factor<big>{ { gcd, null } };
	
	// calcolo prodotti
	tensor<factor<big>> products;
	for (const auto& Adder : Union) products << PolynomialMultiply<big>(Adder);
	
	// calcolo somma dei prodotti
	factor<big> Sum;
	for (const auto& product : products) Sum += product;
	ListCommonFactors << PolynomialSum(Sum);

	// correzione termine polinomio
	if (ListCommonFactors.last() == factor<big>{ { 1, null } }) ListCommonFactors--;
	for (size_t i = 0; i < ListCommonFactors; ++i)
		if (ListCommonFactors[i] == 1) if (ListCommonFactors[i][0].coefficient < 0)
		{
			ListCommonFactors[i][0].coefficient.invert();
			ListCommonFactors[0][0].coefficient.invert();
		}

	// aggiustamento coefficiente
	if (ListCommonFactors[0] == factor<big>{ { 1, null } } and
		ListCommonFactors > 1)
		--ListCommonFactors;
	else if (ListCommonFactors[0] == factor<big>{ { -1, null } } and
		ListCommonFactors > 1)
	{
		--ListCommonFactors;
		for (size_t i = 0; i < ListCommonFactors[0]; ++i)
			ListCommonFactors[0][i].coefficient.invert();
	}
	if (ListCommonFactors.last() == factor<big>{ { 1, null } } and
		ListCommonFactors > 1)
		ListCommonFactors--;

	// moltiplicazioni coefficienti
	big GeneralCoeff = 1;
	for (ptrdiff_t i = ListCommonFactors.size() - 1; i >= 0; --i)
		if (ListCommonFactors[i] == 1 and ListCommonFactors[i][0].exp == null)
		{
			GeneralCoeff *= ListCommonFactors[i][0].coefficient;
			ListCommonFactors.erase(ListCommonFactors.begin() + i);
		}
	ListCommonFactors >> factor<big>{ { GeneralCoeff, null } };

	LCM ^= (int)sizemax;
	ListCommonFactors.close();
	ret ListCommonFactors;
}

// porta il polinomio in una forma più semplice per la traduzione
static polynomial<big> GetMonomialsAssister(wstring pol)
{
	for (ptrdiff_t index = pol.size() - 2; index > 0; --index)
		if (pol.at(index) == L'*' and
			pol.at(index - 1) != ')' and pol.at(index + 1) != '(')
		{

			// calcolo indici
			bool AssignedStart{ false }, AssignedEnd{ false };
			ptrdiff_t startIndex{}, endIndex = pol.size() - 1;
			int StartBalance{}, EndBalance{};
			for (ptrdiff_t i = index - 1; i >= 0; --i) {
				if (pol.at(i) == ')') StartBalance--;
				if (pol.at(i) == '(') StartBalance++;
				if (issign(pol.at(i)) or StartBalance == 1)
				{
					startIndex = i;
					AssignedStart = true;
					break;
				}
			}
			for (size_t i = index + 1; i < pol.size() - 1; ++i) {
				if (pol.at(i) == '(') EndBalance--;
				if (pol.at(i) == ')') EndBalance++;
				if (issign(pol.at(i)) or EndBalance == 1)
				{
					endIndex = i;
					AssignedEnd = true;
					break;
				}
			}

			// calcolo stringhe
			wstring start{ pol }, first{ pol }, Last{ pol }, end{ pol };
			if (AssignedEnd) end.erase(0, endIndex + (pol.at(endIndex) == L')'));
			else end.clear();
			if (AssignedStart)
				start.erase(startIndex + (pol.at(startIndex) != L'('));
			else start.clear();
			if (AssignedEnd) Last.erase(endIndex);
			Last.erase(0, index + 1);
			first.erase(index);
			if (AssignedStart) first.erase(0, startIndex + 1);

			pol = start + L'(' + first + L")(" + Last + L')' + end;
		}
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i)
		if (pol.at(i) == L'*') pol.erase(i, 1);

	// calcolo variabili
	Variables.clear();
	for (const auto& c : pol) if (isalpha(c)) {
		bool IsTheVariableSet{ false };
		for (const auto& Variable : Variables) if (Variable == c)
			IsTheVariableSet = true;
		if (!IsTheVariableSet) Variables += c;
	}
	if (Variables.empty()) Variables = L"x";

	// calcolo minimo comune multiplo
	LCM = 1;
	for (size_t i = 0; i < pol.size(); ++i) if (pol.at(i) == L'/') {

		// ritaglio stringa
		auto bigger{ pol };
		int J{ -1 };
		if (i < bigger.size() - 2) for (size_t j = i; j < bigger.size(); ++j) {
			auto ch{ bigger.at(j) };
			if (issign(ch) or ch == L'(' or ch == L')') {
				J = j;
				break;
			}
		}
		if (J >= 0) bigger.erase(J);
		bigger.erase(0, i + 1);

		// calcolo
		big second = bigger;
		LCM = (LCM * second).fabs() / Gcd(LCM, second);
	}

	ret GetMonomialsRedirector(pol);
}

template<typename T> T ObjectOperations
(wstring& errcode, tensor<T> list, tensor<wstring> ops, wstring disposition)
{
	// caso di disposizione non calcolata in precedenza
	if (disposition.empty()) {
		for (size_t i = 0; i < ops; ++i) disposition += ops[i] + L'\'';
		if (disposition.empty()) {
			errcode = L'_';
			ret T();
		}
		disposition.pop_back();
	}
	bool stay{ true };

	// segni di uguaglianza
	int occurrences{};
	for (const auto& ch : disposition) {
		if (ch == L'=') occurrences++;
		if (occurrences > 1) {
			errcode = L"Troppe uguaglianze";
			ret T();
		}
	}
	if (occurrences > 0) {
		auto position{ disposition.find(L'=') };
		disposition.erase(position, 1);
		disposition.insert(disposition.begin() + position, L'(');
		disposition.insert(disposition.begin() + position, L'-');
		disposition += L')';
	}

	// calcolo principale
	for (;;) {
		int Apostrophes{}, apostrophes{};
		T final;
		wstring part;
		if (disposition.find(L'(') == wstring::npos and
			disposition.find(L')') == wstring::npos) stay = false;

		// loop per trovare una regione senza parentesi
		bool change{ false };
		int balance{}, start{ -1 }, end = disposition.size();
		if (stay) for (size_t i = 0; i < disposition.size(); ++i) {

			// aggiornamento puntatori
			switch (disposition.at(i)) {
			case L'(':
				change = true;
				start = i;
				balance++;
				apostrophes = Apostrophes;
				break;
			case L')':
				if (balance == 1) end = i;
				if (balance == 0) {
					errcode = L"Le parentesi sono invertite";
					ret T();
				}
				balance--;
				break;
			case L'\'': Apostrophes++;
			}

			if (balance == 0 and change) {
				part = disposition.substr(start + 1, end - start - 1);
				break;
			}
		}
		else part = disposition;
		if (balance != 0) {
			errcode = L"Le parentesi sono sbilanciate";
			ret T();
		}
		if (start + 1 == end) {
			errcode = L"Manca un fattore";
			ret T();
		}

		// controllo estremi
		if (Last(part) != L'\'') {
			errcode = L"Manca un monomio alla fine di un fattore";
			ret T();
		}
		if (part.at(0) == L'*' or part.at(0) == L'/') {
			errcode = L"Manca un monomio all'inizio di un fattore";
			ret T();
		}
		if (part.at(0) == L'\'') part = L'+' + part;

		// controllo operatori consecutivi
		for (size_t i = 1; i < part.size(); ++i)
			if (part.at(i - 1) != L'\'' and part.at(i) != L'\'')
			{
				errcode = L"Manca un monomio al centro di un fattore";
				ret T();
			}

		// moltiplicazione
		int LocalApostrophes{ apostrophes - 1 };
		for (ptrdiff_t i = part.size() - 1; i >= 0; --i) switch (part.at(i))
		{
		case L'*': part.erase(i, 1);
			break;
		case L'\'': LocalApostrophes++;
		}

		// divisione
		auto local_apostrophes{ LocalApostrophes };
		for (ptrdiff_t i = part.size() - 1; i >= 0; --i) switch (part.at(i))
		{
		case L'f':
			part.erase(i, 1);
			list[local_apostrophes + 1] = list[local_apostrophes + 1].invert();
			if (isnan(list[local_apostrophes + 1])) {
				errcode = L"Divisione per zero";
				ret T();
			}
			break;
		case L'/':
			part.erase(i, 1);
			list[local_apostrophes + 1] = list[local_apostrophes + 1].invert();
			if (isnan(list[local_apostrophes + 1])) {
				errcode = L"Divisione per zero";
				ret T();
			}
			break;
		case L'\'': local_apostrophes--;
		}

		// sottrazione
		local_apostrophes = LocalApostrophes + 1;
		for (ptrdiff_t i = part.size() - 1; i >= 0; --i) switch (part.at(i))
		{
		case L'-': {
			part.at(i) = L'+';
			auto& obj{ list[local_apostrophes] };
			obj = T() - obj;
			break;
		}
		case L'\'': local_apostrophes--;
		}

		// addizione
		tensor<tensor<T>> AddAndMultiply{ tensor<T>{} };
		tensor<T> Add;
		auto index{ apostrophes };
		for (size_t i = 0; i < part.size(); ++i) {
			if (part.at(i) == L'\'') {
				AddAndMultiply.last() << list[index];
				index++;
				continue;
			}
			AddAndMultiply << tensor<T>{};
		}
		for (auto& Multiply : AddAndMultiply) {
			if (Multiply.empty()) continue;
			auto product{ Multiply[0] };
			for (size_t i = 1; i < Multiply; ++i) product *= Multiply[i];
			Add << product;
		}
		final = Add[0];
		for (size_t i = 1; i < Add; ++i) final += Add[i];

		// sostituzione
		if (disposition.find(L'(') != wstring::npos or
			disposition.find(L')') != wstring::npos)
		{
			disposition.erase(start, end - start + 1);
			disposition.insert(disposition.begin() + start, L'\'');
		}
		list.erase(
			(size_t)apostrophes, size_t(LocalApostrophes - apostrophes + 1)
		);
		list.insert(list.begin() + apostrophes, final);

		// termine
		if (!stay) {
			errcode.clear();
			ret final;
		}
	}
}

#pragma endregion

// funzioni utili per lavorare con i polinomi
#pragma region HandPolynomials

// calcola le posizioni delle variabili di un polinomio a più variabili
static tensor<tensor<long double>> FromPolynomialToPos(
	factor<> vect,
	int& StartIndex,
	tensor<int>& CorrectSizes,
	tensor<int>& VDirectorTerm,
	tensor<int>& VKnownTerm,
	tensor<tensor<int>>& VDirectorSeq,
	tensor<tensor<int>>& VKnownSeq
)
{
	vect.SortByExponents();
	tensor<int> null(Variables.size(), 0);

	// calcolo possibili dimensioni
	auto DirectorDegSequence{ vect[0].exp };
	auto KnownDegSequence{ vect.last().exp };
	StartIndex = 0;
	for (size_t i = 0; i < Variables.size(); ++i)
		if (DirectorDegSequence[i] > 0 and KnownDegSequence[i] > 0) ret {};
	for (ptrdiff_t i = Variables.size() - 1; i >= 0; --i)
		if (DirectorDegSequence[i] > 0 or KnownDegSequence[i] > 0) StartIndex = i;

	int Size{ Gcd(vect[0].exp + vect.last().exp) };
	auto listSizes{ DivisorCounter(Size) };

	// controllo degli esponenti
	for (const auto& size : listSizes) {
		bool keep{ false };
		if (size + 1 < vect) continue;

		// riduzione
		auto DirectorSeq{ DirectorDegSequence };
		auto KnownSeq{ KnownDegSequence };
		for (size_t i = 0; i < Variables.size(); ++i) {
			DirectorSeq[i] /= size;
			KnownSeq[i] /= size;
		}

		// controllo esponenti centrali
		for (size_t i = 1; i + 1 < vect; ++i) {
			double Dquot{ -1 }, Kquot{ -1 };

			for (size_t j = 0; j < Variables.size(); ++j) {
				double vexp = vect[i].exp[j];
				if (!DirectorSeq[j] and !KnownSeq[j] and vexp) ret {};
				bool primary = DirectorSeq[j];

				double quot =
					primary ? vexp / DirectorSeq[j] : vexp / KnownSeq[j];
				if (!integer(quot)) {
					keep = true;
					break;
				}

				if (primary) {
					if (Dquot == -1) Dquot = quot;
					else if (Dquot != quot) keep = true;
				}
				else {
					if (Kquot == -1) Kquot = quot;
					else if (Kquot != quot) keep = true;
				}
			}

			if (keep) break;
		}
		if (keep) continue;

		if (size > 1) CorrectSizes << size;
	}

	// iterazione per ogni dimensione tra quelle possibili
	tensor<tensor<long double>> result;
	for (const auto& CorrectSize : CorrectSizes) {

		// ridimensionamento esponenti
		auto DirectorSeq{ DirectorDegSequence };
		auto KnownSeq{ KnownDegSequence };
		for (size_t i = StartIndex; i < Variables.size(); ++i) {
			DirectorSeq[i] /= CorrectSize;
			KnownSeq[i] /= CorrectSize;
		}

		// controllo coefficienti
		int DirectorTerm = vect[0].coefficient;
		int KnownTerm = vect.last().coefficient;
		if (abs(DirectorTerm) >= GlobalMax or abs(KnownTerm) >= GlobalMax)
			continue;

		// assegnazione di una posizione ai coefficienti
		int KnVarPos{ -1 };
		tensor<long double> position(CorrectSize + 1, 0);
		for (size_t i = StartIndex; i < Variables.size(); ++i)
			if (KnownSeq[i] > 0) {
				KnVarPos = i;
				break;
			}
		bool skip{ false };
		for (size_t i = 0; i < vect; ++i) {
			int index;
			if (KnVarPos >= 0) index = vect[i].exp[KnVarPos] / KnownSeq[KnVarPos];
			else index = CorrectSize - vect[i].exp[StartIndex]
				/ DirectorSeq[StartIndex];
			if (index < 0) {
				skip = true;
				break;
			}
			position[index] = vect[i].coefficient;
		}
		if (skip) continue;

		result << position;
		VDirectorTerm << DirectorTerm;
		VKnownTerm << KnownTerm;
		VDirectorSeq << DirectorSeq;
		VKnownSeq << KnownSeq;
	}

	// ordinamento soluzioni
	for (size_t i = 0; i < result; ++i)
		for (size_t j = i + 1; j < result; ++j)
			if (result[i] < result[j])
			{
				swap(result[i], result[j]);
				swap(CorrectSizes[i], CorrectSizes[j]);
				swap(VDirectorTerm[i], VDirectorTerm[j]);
				swap(VKnownTerm[i], VKnownTerm[j]);
				swap(VDirectorSeq[i], VDirectorSeq[j]);
				swap(VKnownSeq[i], VKnownSeq[j]);
			}
	ret result;
}

// somma un fattore di un polinomio
template<typename T_int = long double>
static factor<T_int> PolynomialSum(factor<T_int> vect)
{

	// correzione esponenti dei numeri complessi
	int ImgUnitPos = Variables.find(L'i');
	if (ImgUnitPos != wstring::npos) for (auto& mon : vect) {
		mon.exp[ImgUnitPos] %= 4;
		if (mon.exp[ImgUnitPos] > 1) {
			mon.coefficient *= -1;
			mon.exp[ImgUnitPos] -= 2;
		}
	}

	// ricerca di monomi simili
	for (ptrdiff_t i = vect.size() - 1; i >= 0; --i)
		for (ptrdiff_t j = i - 1; j >= 0; --j)
			if (vect[i].exp[0] >= 0 and vect[j].exp[0] >= 0) {

				bool AreTheMonomialsSimiliar{ true };
				for (int k = 0; k < Variables.size(); ++k)
					if (vect[i].exp[k] != vect[j].exp[k])
						AreTheMonomialsSimiliar = 0;

				if (AreTheMonomialsSimiliar) {
					vect[i].coefficient += vect[j].coefficient;
					vect[j].coefficient = 0;
				}
			}

	// rimozione dei monomi simili
	for (ptrdiff_t i = vect.size() - 1; i >= 0; --i)
		if (vect[i].coefficient == 0) vect[i].exp.clear();
	auto it = remove(vect.begin(), vect.end(), monomial<T_int>{ 0, {} });
	vect.erase(it, vect.end());

	if (vect.empty()) ret factor<T_int>{ { 0, tensor<int>(Variables.size(), 0) } };
	ret vect;
}

// moltiplica un polinomio (inverso della scomposizione)
template<typename T_int = long double>
static factor<T_int> PolynomialMultiply(polynomial<T_int> Polynomial)
{

	// polinomio nullo
	bool Empty{ Polynomial.empty() };
	if (!Empty) for (const auto& term : Polynomial) if (term.empty()) {
		Empty = true;
		break;
	}
	if (Empty) ret { { 1, tensor<int>(Variables.size(), 0) } };
	Polynomial.open();

	while (Polynomial > 1) {
		factor<T_int> Temp;
		monomial<T_int> temp;

		for (auto A : Polynomial[0]) for (auto B : Polynomial[1]) {
			temp.coefficient = A.coefficient * B.coefficient;
			temp.exp.clear();
			for (size_t i = 0; i < Variables.size(); ++i)
				temp.exp << A.exp[i] + B.exp[i];
			Temp << temp;
		}
		--(--Polynomial);
		Polynomial >> Temp;
	}
	ret PolynomialSum(Polynomial[0]);
}

// esegue la divisione tra polinomi
static void PolynomialDivide
(
	FACTOR<> dividend, FACTOR<> divisor,
	FACTOR<>& quotient, FACTOR<>& rest
)
{

	// aggiustamento polinomi
	dividend.sort();
	divisor.sort();
	dividend.complete(dividend[0].degree);
	divisor.complete(divisor[0].degree);
	dividend.sort();
	divisor.sort();
	quotient.clear();

	// divisione
	while (dividend[0].degree >= divisor[0].degree) {

		auto divide{ divisor };
		int deg = dividend[0].degree, _deg = divisor[0].degree;
		long double rest_element{ dividend[0].coefficient };
		rest_element /= divisor[0].coefficient;
		CORRECTION_RATIO *= divisor[0].coefficient;

		for (size_t i = 0; i < divide; ++i) {
			divide[i].coefficient *= -rest_element;
			divide[i].degree += deg - _deg;
		}
		dividend = dividend - divide.neg();
		dividend.complete(deg);
		dividend.sort();
		quotient << MONOMIAL<>{ deg - _deg, rest_element };
	}
	rest = dividend;

	// amplificazione dei coefficienti
	for (size_t i = 0; i < quotient; ++i) quotient[i].coefficient *= CORRECTION_RATIO;
	for (size_t i = 0; i < rest; ++i) rest[i].coefficient *= CORRECTION_RATIO;
	int gcd{ abs(Gcd(quotient + rest)) };
	for (size_t i = 0; i < quotient; ++i) quotient[i].coefficient /= gcd;
	for (size_t i = 0; i < rest; ++i) rest[i].coefficient /= gcd;
}

#pragma endregion

// funzioni con le tecniche di scomposizione
#pragma region Techniques

// raccoglimento totale
static polynomial<> Total(factor<> vect)
{
	
	// filtro per tensori con più di un termine
	polynomial<> output;
	output << vect;
	if (vect <= 1) ret output;

	// calcolo grado minimo e riscrittura
	bool positive_min{ false };
	int GCD{ Gcd(vect) };
	tensor<int> exponents;
	for (size_t i = 0; i < Variables.size(); ++i) {
		int min{ vect[0].exp[i] };
		for (const auto& t : vect) if (t.exp[i] < min) min = t.exp[i];
		exponents << min;
		if (min > 0) positive_min = 1;
	}
	if (abs(GCD) != 1 or positive_min) {
		output.clear();
		output << factor<>{ { (long double)GCD, exponents } };
		for (size_t i = 0; i < vect; ++i) {
			vect[i].coefficient /= GCD;
			for (size_t j = 0; j < Variables.size(); ++j)
				vect[i].exp[j] -= exponents[j];
		}
	}

	// totale
	if (abs(GCD) != 1 or positive_min) {
		output.clear();
		output << factor<>{ { (long double)GCD, exponents } } << vect;
		ret output;
	}
	ret { vect };
}

// raccoglimento parziale
static polynomial<> Partial(factor<> vect)
{

	// filtro tensori a quattro termini
	polynomial<> outp;
	outp << vect;
	if (vect != 4) ret outp;
	tensor<int> null(Variables.size(), 0);

	// riassegnazione e dichiarazioni
	factor<> part_1{ vect[0], vect[1] }, part_2{ vect[2], vect[3] };
	auto Part1{ Total(part_1) };
	auto Part2{ Total(part_2) };
	if ((Part1.last() - Part2.last().neg()).empty()) {
		if (Part1 == 1) swap(Part1, Part2);
		Part2 >> factor<>{ { -1, null } };
		Part2[1] = Part2[1].neg();
	}
	part_1 = Part1.last();
	part_2 = Part2.last();
	if (part_1 != part_2) ret outp;
	outp.clear();

	// riordinamento del totale
	polynomial<> mon_1, mon_2;
	if (Part1 == 1) mon_1 << factor<>{ { 1, null } };
	else mon_1 << Part1[0];
	if (Part2 == 1) mon_2 << factor<>{ { 1, null } };
	else mon_2 << Part2[0];
	mon_1 << part_1;
	mon_2 << part_2;

	// riordinamento del parziale
	part_1.SortByExponents();
	part_2 = mon_1[0] - mon_2[0].neg();
	part_2.SortByExponents();
	outp << part_1 << part_2;

	ret outp;
}

// potenza di binomio
static polynomial<> Binomial(factor<> vect)
{
	
	// filtro per tensori con più di un termine
	polynomial<> outp;
	outp << vect;
	int exponent = vect.size() - 1, sign{ 1 };
	if (exponent <= 1) ret outp;
	bool reassigne{ false };
	vect.SortByDegree();

	// calcolo del monomio modificatore dell'esponente
	tensor<int> modifier(Variables.size(), 0);
	modifier[0] = -1;

	auto A{ vect[0] };
	auto B{ vect.last() };

	// controllo per evitare radici impossibili da eseguire nei reali
	if (exponent % 2 == 0 and (A.coefficient < 0 or B.coefficient < 0)) ret outp;

	// calcolo delle radici
	double Sq_A, Sq_B;
	if (A.coefficient > 0) Sq_A = pow(A.coefficient, 1.0 / exponent);
	else Sq_A = -pow(-A.coefficient, 1.0 / exponent);
	if (B.coefficient > 0) Sq_B = pow(B.coefficient, 1.0 / exponent);
	else Sq_B = -pow(-B.coefficient, 1.0 / exponent);

	// controllo sulle potenze
	if (!integer(Sq_A)) ret outp;
	if (!integer(Sq_B)) ret outp;
	for (size_t i = 0; i < Variables.size(); ++i) if (A.exp[i] % exponent != 0)
		ret outp;
	for (size_t i = 0; i < Variables.size(); ++i) if (B.exp[i] % exponent != 0)
		ret outp;
	auto Aexps{ A.exp };
	auto Bexps{ B.exp };
	for (size_t i = 0; i < Variables.size(); ++i) {
		Aexps[i] /= exponent;
		Bexps[i] /= exponent;
	}

	for (size_t i = 1; i < exponent; ++i) {

		// calcolo coefficiente
		for (size_t j = 0; j < Variables.size(); ++j)
			if (vect[i].exp[j] != Aexps[j] * (exponent - i) + Bexps[j] * i) ret outp;
		int coeff = BinomialCoeff(exponent, i);

		// caso con la sottrazione
		if (vect[i].coefficient ==
			-coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
			) {
			if (!reassigne) {
				sign = -1;
				reassigne = 1;
			}
			else if (sign == 1) ret outp;
		}

		// caso con l'addizione
		else if (vect[i].coefficient ==
			coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
			)
		{
			if (!reassigne) {
				sign = 1;
				reassigne = 1;
			}
			else if (sign == -1) ret outp;
		}

		// caso non accettato
		else ret outp;
	}

	// composizione della potenza di binomio
	outp.clear();
	outp << factor<>{ { (long double)exponent, modifier } };
	outp++;
	outp[1] << monomial<>{ Sq_A, Aexps } << monomial<>{ sign * Sq_B, Bexps };

	ret outp;
}

// trinomio speciale
static polynomial<> Trinomial(factor<> vect)
{

	// filtro per tensori di tre termini
	polynomial<> outp;
	outp << vect;
	if (vect != 3) ret outp;
	vect.SortByDegree();

	// calcolo termini ed esponenti
	int A, B, C;
	for (size_t i = 0; i < Variables.size(); ++i)
		if (vect[0].exp[i] % 2 == 1 or vect[2].exp[i] % 2 == 1) ret outp;

	auto Aexps{ vect[0].exp };
	auto Cexps{ vect[2].exp };
	for (size_t i = 0; i < Variables.size(); ++i) {
		if (2 * vect[1].exp[i] != vect[0].exp[i] + vect[2].exp[i])
			ret outp;
		Aexps[i] /= 2;
		Cexps[i] /= 2;
	}
	A = vect[0].coefficient;
	B = vect[1].coefficient;
	C = vect[2].coefficient;

	// calcolo delle radici
	double firstX, secondX, delta;
	delta = B * B - 4 * A * C;
	if (delta <= 0) ret outp;
	if (!integer(sqrt(delta))) ret outp;
	firstX = (-B - sqrt(delta)) / (2 * A);
	secondX = (-B + sqrt(delta)) / (2 * A);
	if (!integer(A * firstX * secondX)) ret outp;
	outp.clear();

	// calcolo dei coefficienti
	int I, J;
	for (I = 1; I <= abs(A); ++I) if (integer(firstX * I)) break;
	if (I == abs(A) + 1) I--;
	if (A < 0) I *= -1;
	for (J = 1; J <= abs(A); ++J) if (integer(secondX * J)) break;
	if (J == abs(A) + 1) J--;

	// composizione del trinomio scomposto
	outp = { {}, {} };
	outp[0] << monomial<>{ -I * firstX, Cexps };
	outp[0] << monomial<>{ (long double)I, Aexps };
	outp[1] << monomial<>{ -J * secondX, Cexps };
	outp[1] << monomial<>{ (long double)J, Aexps };
	outp[0].SortByExponents();
	outp[1].SortByExponents();

	ret outp;
}

// differenza di cubi (presto diventerà differenza di potenze)
static polynomial<> SquareDifference(factor<> vect)
{

	// filtro per tensori di due termini
	polynomial<> outp;
	outp << vect;
	if (vect != 2) ret outp;

	// controllo sui quadrati perfetti
	if (!vect[0].IsSquare()) ret outp;
	if (!vect[1].IsSquare()) ret outp;

	// riassegnazione se i segni non vanno bene
	bool Sign_A{ vect[0].coefficient > 0 };
	bool Sign_B{ vect[1].coefficient > 0 };
	if (Sign_A == Sign_B) ret outp;

	// calcolo esponenti
	auto Aexps{ vect[0].exp };
	auto Bexps{ vect[1].exp };
	for (size_t i = 0; i < Variables.size(); ++i) {
		Aexps[i] /= 2;
		Bexps[i] /= 2;
	}

	// composizione di somma e differenza
	outp = { {}, {} };
	outp[0] << monomial<>{ +sqrt(fabs(vect[1].coefficient)), Bexps };
	outp[0] << monomial<>{ +sqrt(fabs(vect[0].coefficient)), Aexps };
	outp[1] << monomial<>{ +sqrt(fabs(vect[1].coefficient)), Bexps };
	outp[1] << monomial<>{ -sqrt(fabs(vect[0].coefficient)), Aexps };
	if (Sign_A) {
		outp[1][0].coefficient *= -1;
		outp[1][1].coefficient *= -1;
	}

	ret outp;
}

// scomposizione con ruffini
static polynomial<> Ruffini(factor<> vect)
{

	// filtro per tensori con più di un termine
	polynomial<> output;
	output << vect;
	if (vect < 2) ret output;
	vect.SortByExponents();
	tensor<int> null(Variables.size(), 0);
	int StartIndex;
	tensor<int> CorrectSizes;
	tensor<int> VDirectorTerm;
	tensor<int> VKnownTerm;
	tensor<tensor<int>> VDirectorSeq;
	tensor<tensor<int>> VKnownSeq;
	auto ListPos{
		FromPolynomialToPos(
			vect,
			StartIndex,
			CorrectSizes,
			VDirectorTerm,
			VKnownTerm,
			VDirectorSeq,
			VKnownSeq
		) 
	};

	for (size_t i = 0; i < ListPos; ++i) {
		auto position{ ListPos[i] };
		auto DirectorTerm{ VDirectorTerm[i] };
		auto KnownTerm{ VKnownTerm[i] };
		auto DirectorSeq{ VDirectorSeq[i] };
		auto KnownSeq{ VKnownSeq[i] };
		auto CorrectSize{ CorrectSizes[i] };

		// calcolo divisori
		auto P{ DivisorCounter(abs(KnownTerm)) };
		auto Q{ DivisorCounter(abs(DirectorTerm)) };
		tensor<int> PossibleRoots;

		// teorema delle radici razionali
		for (auto p : P) for (auto q : Q) PossibleRoots.push_back(p / q);
		for (ptrdiff_t j = PossibleRoots.size() - 1; j >= 0; --j)
			for (ptrdiff_t k = j - 1; k >= 0 and j < PossibleRoots; --k)
				if (PossibleRoots[j] == PossibleRoots[k])
					PossibleRoots.erase(PossibleRoots.begin() + j);
		int SetRoot{}, Root;

		// calcolo della regola di ruffini sui coefficienti
		for (int n = 1; n < CorrectSize; ++n) {

			// regola di ruffini
			tensor<long double> temp;
			for (const auto& root : PossibleRoots) {
				Root = root;
				do {

					// divisione polinomio per binomio
					temp = position;
					for (size_t j = 1; j < position; ++j)
						temp[j] = Root * temp[j - 1] + temp[j];

					// caso con resto nullo
					if (temp.last() == 0) {
						temp--;
						SetRoot = Root;
						position = temp;
						break;
					}

					Root *= -1;
				} while (Root != root);
				if (SetRoot != 0) break;
			}

			// caso di zero trovato
			if (SetRoot != 0) {
				output.clear();
				output++;
				output[0] << monomial<>{ 1, DirectorSeq };
				output[0] << monomial<>{ -(long double)SetRoot, KnownSeq };
				output++;
				for (int j = 0; j < CorrectSize; ++j) {
					if (position[CorrectSize - 1 - j] == 0) continue;
					tensor<int> VariableExp(Variables.size(), 0);
					size_t index{ Variables.size() };
					if (DirectorSeq[StartIndex] == 0) swap(DirectorSeq, KnownSeq);
					for (size_t k = StartIndex; k < Variables.size(); ++k) {
						if (DirectorSeq[k] == 0) {
							index = k;
							break;
						}
						VariableExp[k] = j * DirectorSeq[k];
					}
					for (size_t k = index; k < Variables.size(); ++k)
						VariableExp[k] = (CorrectSize - 1 - j) * KnownSeq[k];
					output[1] << monomial<>{
						(long double)position[CorrectSize - j - 1], VariableExp
					};
				}
				output[1].SortByExponents();
				ret output;
			}
		}
	}

	ret { vect };
}

// completamento del quadrato
static polynomial<> CompleteTheSquare(factor<> vect)
{

	// filtro per tensori con tre termini
	polynomial<> outp;
	outp << vect;
	if (vect != 3) ret outp;
	vect.SortByDegree();
	auto A{ vect[0] };
	auto B{ vect[2] };

	// calcolo delle radici
	if (A.coefficient < 0 or B.coefficient < 0) ret outp;
	double Sq_A = sqrt(A.coefficient);
	double Sq_B = sqrt(B.coefficient);

	// controllo sui quadrati
	if (!A.IsSquare()) ret outp;
	if (!B.IsSquare()) ret outp;
	for (size_t i = 0; i < Variables.size(); ++i) if (A.exp[i] % 4 != 0) ret outp;
	
	// controllo sui gradi
	for (size_t i = 0; i < Variables.size(); ++i) {
		if (vect[1].exp[i] != A.exp[i] / 2 + B.exp[i] / 2) ret outp;
		if (!integer(A.exp[i] / 4 + B.exp[i] / 4)) ret outp;
	}

	// dichiarazioni
	monomial<> DiffSquare, Diffneg;
	for (size_t i = 0; i < Variables.size(); ++i)
		DiffSquare.exp << A.exp[i] / 4 + B.exp[i] / 4;
	int middleterm{ 2 * (int)Sq_A * (int)Sq_B }, sign;
	int CasePlus = middleterm - vect[1].coefficient;
	int CaseMinus = -middleterm - vect[1].coefficient;

	// calcolo del quadrato di differenza
	if (CasePlus > 0 and integer(sqrt(CasePlus))) {
		DiffSquare.coefficient = sqrt(CasePlus);
		sign = 1;
	}
	else if (CaseMinus > 0 and integer(sqrt(CaseMinus))) {
		DiffSquare.coefficient = sqrt(CaseMinus);
		sign = -1;
	}
	else ret outp;
	Diffneg.coefficient = -DiffSquare.coefficient;
	Diffneg.exp = DiffSquare.exp;

	// calcolo gradi finali
	for (size_t i = 0; i < Variables.size(); ++i) {
		A.exp[i] /= 2;
		B.exp[i] /= 2;
	}

	// composizione di somma e differenza
	outp << vect;
	outp[0].clear();
	outp[1].clear();

	outp[0] << monomial<>{ Sq_A, A.exp } << DiffSquare << monomial<>{ Sq_B, B.exp };
	outp[1] << monomial<>{ Sq_A, A.exp } << Diffneg << monomial<>{ Sq_B, B.exp };

	ret outp;
}

// quadrato di trinomio
static polynomial<> TrinomialSquare(factor<> vect)
{

	// filtro per tensori con 5 o 6 termini
	polynomial<> output;
	output << vect;
	if (vect != 5 and vect != 6) ret output;

	// push del monomio modificatore dell'esponente
	tensor<int> modifier(Variables.size(), 0);
	modifier[0] = -1;
	
	if (vect == 5) {
		vect.SortByDegree();

		// controllo coefficienti
		bool AB2, AC2, BC2;
		long double A{ sqrt(vect[0].coefficient) };
		if (!integer(A)) ret output;
		long double C{ sqrt(vect[4].coefficient) };
		if (!integer(C)) ret output;
		long double B{ (long double)vect[3].coefficient / (2 * C) };
		if (!integer(B)) ret output;
		if (fabs(B) != fabs((double)vect[1].coefficient / (2 * A))) ret output;

		// controllo esponenti
		for (size_t i = 0; i < Variables.size(); ++i) for (int j = 0; j < 5; ++j)
			if (vect[4 - j].exp[i] != j * vect[3].exp[i]) ret output;

		// calcolo segni
		AB2 = vect[1].coefficient < 0;
		BC2 = vect[3].coefficient < 0;
		if (fabs(vect[2].coefficient) == fabs(2 * A * C + B * B))
			AC2 = vect[2].coefficient - B * B < 0;
		else if (fabs(vect[2].coefficient) == fabs(2 * A * C - B * B))
			AC2 = vect[2].coefficient + B * B < 0;
		else ret output;
		if (AB2 + AC2 + BC2 > 1) {
			AB2 = !AB2;
			AC2 = !AC2;
			BC2 = !BC2;
		}

		// riassegnazione variabili
		A = A >= 0 ? A : -A;
		B = B >= 0 ? B : -B;
		C = C >= 0 ? C : -C;
		if (AB2) C = -C;
		if (AC2) B = -B;
		if (BC2) A = -A;

		// composizione del quadrato di trinomio
		output.clear();
		output << factor<>{ { 2, modifier } };
		output++;
		output[1] << monomial<>{ A, vect[2].exp };
		output[1] << monomial<>{ B, vect[3].exp };
		output[1] << monomial<>{ C, vect[4].exp };
	}
	else if (vect == 6) {

		// ricerca dei quadrati
		factor<> squares;
		for (int i = 0; i < 6; ++i) if (vect[i].IsSquare()) squares << vect[i];
		if (squares < 3) ret output;
		tensor<int> _pos{ 1, 2, 2 };
		int IndexAccesser{ 2 };

		// ricerca dei quadrati corretti
		monomial<> A, B, C;
		bool AB2{ true }, AC2{ true }, BC2{ true };
		while (IndexAccesser >= 0) {
			A = {};
			B = {};
			C = {};

			auto backup{ _pos };
			for (int i = IndexAccesser; i < 3; ++i) backup[i]++;
			if (backup.last() > squares) {
				IndexAccesser--;
				continue;
			}
			IndexAccesser = 2;
			_pos = backup;

			// // controllo quadrati
			factor<> NewSquares(3);
			for (int i = 0; i < 3; ++i) NewSquares[i] = squares[_pos[i] - 1];

			A = NewSquares[0].Root(2);
			B = NewSquares[1].Root(2);
			C = NewSquares[2].Root(2);

			monomial<> AB, AC, BC;
			AB.coefficient = 2 * A.coefficient * B.coefficient;
			AC.coefficient = 2 * A.coefficient * C.coefficient;
			BC.coefficient = 2 * B.coefficient * C.coefficient;

			for (size_t i = 0; i < Variables.size(); ++i) {
				AB.exp << A.exp[i] + B.exp[i];
				AC.exp << A.exp[i] + C.exp[i];
				BC.exp << B.exp[i] + C.exp[i];
			}

			monomial<> ABterm, ACterm, BCterm;
			for (const auto& v : vect) {

				if (v == AB) ABterm = v;
				if (v == AC) ACterm = v;
				if (v == BC) BCterm = v;

				auto v2{ v };
				v2.coefficient *= -1;

				if (v2 == AB) ABterm = v;
				if (v2 == AC) ACterm = v;
				if (v2 == BC) BCterm = v;
			}
			if (
				ABterm == monomial<>{} or
				ACterm == monomial<>{} or
				BCterm == monomial<>{}
				) continue;
			// //

			// calcolo segni
			AB2 = ABterm.coefficient >= 0;
			AC2 = ACterm.coefficient >= 0;
			BC2 = BCterm.coefficient >= 0;
			if (AB2 + AC2 + BC2 > 1) {
				AB2 = !AB2;
				AC2 = !AC2;
				BC2 = !BC2;
			}

			break;
		}

		// composizione del quadrato di trinomio
		if (BC2) A.coefficient *= -1;
		if (AC2) B.coefficient *= -1;
		if (AB2) C.coefficient *= -1;
		output.clear();
		output << factor<>{ { 2, modifier } };
		output++;
		output[1] << A << B << C;
	}

	ret output;
}

#pragma endregion

// funzioni utili per lavorare con le frazioni algebriche
#pragma region Algebric

// calcola il complementario di un fattore rispetto a un polinomio
static FACTOR<> Complementary(POLYNOMIAL<> Polynomial, FACTOR<> factor, int exp)
{

	// caso di eccezione
	if (Polynomial[0] == factor) --Polynomial;

	else for (ptrdiff_t i = Polynomial.size() - 1; i > 0 and i < Polynomial; --i)
		if (Polynomial[i] == factor) {

			// caso senza esponente
			if (Polynomial[i - 1][0].degree >= 0) {
				Polynomial.erase(Polynomial.begin() + i);
				break;
			}

			// casi con esponente
			if (Polynomial[i - 1][0].coefficient - exp > 1) {
				Polynomial[i - 1][0].coefficient -= exp;
				break;
			}
			if (Polynomial[i - 1][0].coefficient - exp < 1) {
				Polynomial.erase(Polynomial.begin() + i);
				Polynomial.erase(Polynomial.begin() + i - 1);
				break;
			}
			Polynomial.erase(Polynomial.begin() + i - 1);
			break;
		}

	ret V1converter(PolynomialMultiply, Polynomial);
}

// semplifica numeratore e denominatore in una frazione
static void Simplify(Fraction<>& fr, int& ncoeff, int& dcoeff)
{
	tensor<int> null(Variables.size(), 0);
	auto& num{ fr.num };
	auto& den{ fr.den };

	num.open();
	den.open();
	for (size_t i = 0; i < num; ++i) num[i].SortByExponents();
	for (size_t i = 0; i < den; ++i) den[i].SortByExponents();

	// semplificazione fattori
	int sign{ 1 };
	for (ptrdiff_t i = num.size() - 1; i >= 0; --i) {

		// caso coefficiente
		if (num[i] == 1 and num[i][0].exp == null) continue;

		for (ptrdiff_t j = den.size() - 1; j >= 0; --j) {
			if (i >= num or j >= den) continue;

			// caso coefficiente
			if (den[j] == 1 and den[j][0].exp == null) continue;

			// caso con polinomi uguali
			if (num[i] == den[j]) {
				num.erase(num.begin() + i);
				den.erase(den.begin() + j);
				continue;
			}

			// caso con polinomi opposti
			for (size_t k = 0; k < den[j]; ++k) den[j][k].coefficient *= -1;
			if (num[i] == den[j]) {
				num.erase(num.begin() + i);
				den.erase(den.begin() + j);
				sign = -1;
				continue;
			}
			else for (size_t k = 0; k < den[j]; ++k) den[j][k].coefficient *= -1;

			// caso di monomi
			if (num[i] == 1 and den[j] == 1)
				for (size_t k = 0; k < Variables.size(); ++k) {
					int GradeDelta{ abs(num[i][0].exp[k] - den[j][0].exp[k]) };
					if (num[i][0].exp[k] > den[j][0].exp[k]) {
						num[i][0].exp[k] = GradeDelta;
						den[j][0].exp[k] = 0;
					}
					else {
						num[i][0].exp[k] = 0;
						den[j][0].exp[k] = GradeDelta;
					}
				}
		}
	}

	// ricerca coefficenti
	int FindN{ -1 }, FindD{ -1 };
	for (size_t i = 0; i < num; ++i) if (num[i] == 1) {
		ncoeff = num[i][0].coefficient * sign;
		if (num[i][0].exp == null and num != 1 and num[0] != 1)
			num.erase(num.begin() + i);
		else FindN = i;
		break;
	}
	for (size_t i = 0; i < den; ++i) if (den[i] == 1) {
		dcoeff = den[i][0].coefficient;
		if (den[i][0].exp == null and den != 1 and den[0] != 1)
			den.erase(den.begin() + i);
		else FindD = i;
		break;
	}

	// semplificazione coefficienti
	int GCD = Gcd(abs(ncoeff), abs(dcoeff));
	ncoeff /= GCD;
	dcoeff /= GCD;
	if (FindN >= 0) num[FindN][0].coefficient = 1;
	if (FindD >= 0) den[FindD][0].coefficient = 1;
	ncoeff *= sign;

	// compressione polinomi
	num.close();
	den.close();
	for (size_t i = 0; i < num.size(); ++i) if (num[i] == factor<>{ { 1, null } })
		num.erase(num.begin() + i);
	for (size_t i = 0; i < den.size(); ++i) if (den[i] == factor<>{ { 1, null } })
		den.erase(den.begin() + i);
}

// stampa una frazione
static void PrintFraction
(int NC, int DC, int& LINE, bool WritePlus, Fraction<> fract)
{
	
	// aggiunta di spazio
	tensor<int> null(Variables.size(), 0);
	_GetCursorPos();
	auto start{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	_GetCursorPos();
	if (csbi.dwCursorPosition.Y >= start.Y)
		start.Y -= 10 - csbi.dwCursorPosition.Y + start.Y;
	SetConsoleCursorPosition(hConsole, start);
	
	// calcolo numeratore
	long double root{};
	int I{ 1 }, Root{};
	bool IsMinus{ false };
	wstring den_, num_;
	if (fract.num == 1) if (fract.num[0] == 1)
		if (fract.num[0][0].exp == null)
			root = fract.num[0][0].coefficient;

	// correzione numeratore
	bool Empty{ fract.num.empty() }, dontreset{ false };
	if (Empty) {
		fract.num = polynomial<>{ { { 1, null } } };
		dontreset = true;
	}
	else {
		Empty = true;
		for (const auto& term : fract.num) if (!term.empty()) {
			Empty = false;
			break;
		}
	}
	if (Empty and !dontreset) {
		NC = 0;
		fract.num = polynomial<>{ { { 0, null } } };
	}

	// correzione denominatore
	if (!(Empty = fract.den.empty())) {
		Empty = true;
		for (const auto& term : fract.den) if (!term.empty()) {
			Empty = false;
			break;
		}
	}
	if (Empty) fract.den = polynomial<>{ { { 1, null } } };

	// calcolo coefficienti e correzione
	if (root != 0) {
		for (;;) {
			if (integer(I * root)) break;
			I++;
		}
		Root = root * I;
		DC *= I;
		if (NC * Root < 0 and DC < 0) {
			NC = -NC;
			DC = -DC;
		}
		else if (NC * Root < 0) {
			NC = -NC;
			IsMinus = true;
		}
		else if (DC < 0) {
			DC = -DC;
			IsMinus = true;
		}
	}

	// aggiustamento denominatore
	bool HasACoefficient{ false };
	if (fract.den >= 1) if (fract.den[0] == 1)
		if (fract.den[0][0].exp == null) HasACoefficient = true;
	if (HasACoefficient) fract.den[0][0].coefficient *= CORRECTION_RATIO;
	else fract.den >> factor<>{ monomial<>{ CORRECTION_RATIO, null } };

	// calcolo GCD e segni
	int gcd = Gcd(NC, DC);
	NC /= gcd;
	DC /= gcd;
	int Gcd{ 1 };
	if (root == 0) Gcd =
		::Gcd((int)fract.num[0][0].coefficient, (int)fract.den[0][0].coefficient);
	else Gcd = ::Gcd(Root, fract.den[0][0].coefficient);
	fract.den[0][0].coefficient /= Gcd;
	if (root != 0) Root /= Gcd;
	else fract.num[0][0].coefficient /= Gcd;
	if (fract.den[0] == 1 and fract.den[0][0] == monomial<>{ 1, null })
		--fract.den;
	else if (fract.den[0][0] == monomial<>{ -1, null }) {
		--fract.den;
		if (root == 0) fract.num[0][0].coefficient *= -1;
		else Root *= -1;
	}
	if (root == 0)
		if (fract.num[0] == 1 and fract.num[0][0] == monomial<>{ 1, null })
			--fract.num;
	if (root != 0) num_ = to_wstring(NC * Root);

	// calcolo numeratore
	if (root == 0) {
		num_ = fract.num.str();

		if (num_ == L"0") num_.clear();
		else if (abs(NC) != 1 and (fract.num[0] > 1 and fract.num == 1))
			num_ = L'(' + num_ + L')';

		if (abs(NC) != 1) num_ = to_wstring(NC) + num_;
		if (num_.empty()) num_ = L"1";

		if (NC == -1 and
			(num_.find(L'+') == wstring::npos and num_.find(L'-') == wstring::npos)
			or num_.find(L'(') != wstring::npos) num_ = L'-' + num_;
		else if (NC == -1) num_ = L"-(" + num_ + L')';
	}

	// // calcolo denominatore
	den_.clear();
	auto tempden{ fract.den.str() };
	if (tempden != L"1") den_ = tempden;
	
	if (den_ == L"0") den_.clear();
	else if (abs(DC) != 1 and (fract.den[0] > 1 and fract.den == 1))
		den_ = L'(' + den_ + L')';

	if (abs(DC) != 1) den_ = to_wstring(DC) + den_;
	if (den_.empty()) den_ = L"1";

	if (DC == -1 and
		(den_.find(L'+') == wstring::npos and den_.find(L'-') == wstring::npos)
		and den_.find(L'(') != wstring::npos) den_ = L'-' + den_;
	else if (DC == -1) den_ = L"-(" + den_ + L')';
	// //

	// aggiustamento segni
	bool both{ true };
	if (num_.at(0) == L'-' and den_.at(0) == L'-' and
		fract.num == 1 and fract.den == 1)
		if (fract.num[0] == 1 and fract.den[0] == 1)
		{
			num_.erase(0, 1);
			den_.erase(0, 1);
			both = false;
		}
	if (num_.at(0) == L'-' and fract.num == 1 and both) if (fract.num[0] == 1)
	{
		num_.erase(0, 1);
		IsMinus = !IsMinus;
		both = false;
	}
	if (den_.at(0) == L'-' and fract.den == 1 and both) if (fract.den[0] == 1)
	{
		den_.erase(0, 1);
		IsMinus = !IsMinus;
	}
	if (NC == 0) {
		num_ = L"0";
		den_ = L"1";
	}

	// calcolo dati
	int sizemax = max(num_.size(), den_.size());
	int spacing = num_.size() - den_.size();
	spacing = abs(spacing) / 2;
	if (num_.size() > den_.size()) den_ = wstring(spacing, L' ') + den_;
	else num_ = wstring(spacing, L' ') + num_;

	// caso di fine riga
	if (LINE + spacing + WritePlus * 2 > csbi.dwSize.X) {
		LINE = 0;
		start.Y += 4;
		SetConsoleCursorPosition(hConsole, start);
	}

	// output segno
	if (WritePlus or IsMinus) {
		if (WritePlus) start.X++;
		start.Y++;
		SetConsoleCursorPosition(hConsole, start);
		IsMinus ? wcout << L'-' : wcout << L'+';
		start.X += 2;
		LINE += 2;
		start.Y--;
	}

	// output frazione
	SetConsoleCursorPosition(hConsole, start);
	wcout << num_;
	start.Y++;
	SetConsoleCursorPosition(hConsole, start);
	wcout << wstring(sizemax, L'-');
	start.Y++;
	SetConsoleCursorPosition(hConsole, start);
	wcout << den_;
	start.Y -= 2;
	start.X += sizemax;
	SetConsoleCursorPosition(hConsole, start);

	// aggiornamento linea
	LINE += sizemax + 1;
}

// stampa una frazione algebrica con la forma corretta
static void PrintFractionaryResult
(
	int NC, int DC, int& lines, Fraction<> Fract,

	POLYNOMIAL<> NScomp, POLYNOMIAL<> DScomp,

	bool HasMoreVariables, bool correct,

	tensor<double> roots, tensor<POLYNOMIAL<>> Denominators
)
{
	// inizio
	tensor<int> null(Variables.size(), 0);
	bool ShowPlus{ false };

	// caso generale, frazione scomposta
	Fraction<> Part;
	Part.num = HasMoreVariables ? Fract.num : ToXV(NScomp);
	Part.den = HasMoreVariables ? Fract.den : ToXV(DScomp);
	if (correct) {
		wcout << L"\n\n";
		for (size_t i = 0; i < Denominators; ++i) {
			PrintFraction(
				NC,
				DC,
				lines,
				ShowPlus,
				{ polynomial<>{ { { roots[i], null } } }, ToXV(Denominators[i]) }
			);
			ShowPlus = true;
		}
		wcout << L"\n\n";
		goto EndOfStatement;
	}

	// caso di frazione semplificata ma non scomposta
	if (!Part.den.empty()) {
		if (Part.den > 1 or Part.den[0] > 1 or Part.den[0][0].exp != null)
		{
			_GetCursorPos();
			csbi.dwCursorPosition.Y--;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			PrintFraction(
				NC,
				DC,
				lines,
				false,
				Part
			);
			wcout << L"\n\n";
			goto EndOfStatement;
		}
	}

	// caso di denominatore coefficiente
	if (abs(DC) != 1 and !Part.num.empty()) {
		_GetCursorPos();
		csbi.dwCursorPosition.Y--;
		SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		PrintFraction(
			NC,
			DC,
			lines,
			false,
			{ Part.num, { { monomial<>{ 1, null } } } }
		);
		wcout << L"\n\n";
	}

	// caso di frazione normale
	else if (abs(DC) != 1 and NScomp.empty()) {
		_GetCursorPos();
		csbi.dwCursorPosition.Y--;
		SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		PrintFraction(
			NC,
			DC,
			lines,
			false,
			{ { { { 1, null } } }, { { { 1, null } } } }
		);
		wcout << L"\n\n";
	}

	// caso costante
	else if (NScomp.empty()) {
		if (DC == -1) NC *= -1;
		wcout << L' ' << NC;
	}

	// caso fattore
	else if (NScomp == 1) {
		auto output = HasMoreVariables ?
			Fract.num[0].str() : NScomp[0].str();
		ElabExponents(output);
		if (NScomp[0] > 1 and NC != 1) output = L'(' + output + L')';
		if (abs(NC) != 1) output = to_wstring(NC) + output;
		if (NC * DC == -1) output = L'-' + output;
		wcout << L' ' << output;
	}

	// caso polinomio
	else wcout << L' ' << (HasMoreVariables ? Fract.num.str() : NScomp.str());

EndOfStatement:

	// reset cursore
	_GetCursorPos();
	auto cursorP{ csbi.dwCursorPosition };
	cursorP.X = lines;
	cursorP.Y--;
	SetConsoleCursorPosition(hConsole, cursorP);
}


#pragma endregion

// funzioni relative al calcolo delle soluzioni di una disequazione
#pragma region Disequations

// calcola una soluzione di un equazione con il metodo di newton-raphson
static void Approximator(tensor<long double>& Equation, long double& root)
{

	// traduzione
	FACTOR<> equation(Equation.size());
	for (ptrdiff_t i = Equation.size() - 1; i >= 0; --i) {
		equation[i].coefficient = Equation[i];
		equation[i].degree = Equation.size() - i - 1;
	}
	auto derivative{ equation.derivate() };

	// calcolo radice
	const double TOL{ 1e-06 };
	for (int i = 0; i < 100; ++i) {
		long double fx{}, dfx{};

		// calcolo parametri
		for (size_t j = 0; j < equation; ++j)
			fx += equation[j].coefficient * pow(root, equation[j].degree);
		for (size_t j = 0; j < derivative; ++j)
			dfx += derivative[j].coefficient * pow(root, derivative[j].degree);

		// calcolo nuovo punto
		if (dfx == 0) dfx += TOL;
		long double next = root - fx / dfx;
		if (fabs(next - root) < TOL) {
			root = next;
			break;
		}
		root = next;
	}

	// divisione del polinomio
	for (size_t i = 1; i < equation.size(); ++i) {
		equation[i].coefficient =
			root * equation[i - 1].coefficient + equation[i].coefficient;
		equation[i].degree--;
	}
	equation[0].degree--;
	equation--;
	
	for (size_t i = 0; i < equation; ++i) Equation[i] = equation[i].coefficient;
	Equation--;
}

// calcola gli zeri di un polinomio
static tensor<wstring> EquationSolver(factor<> Equation)
{
	// caso nullo
	tensor<int> null(Variables.size() , 0);
	if (Equation.empty()) ret {};
	tensor<wstring> answer;

	if (Equation == 1) {

		// caso esponente
		if (Equation[0].exp[0] == -1) ret {};
		
		// caso monomio
		for (size_t i = 0; i < Variables.size(); ++i) if (Equation[0].exp[i] != 0)
			answer << wstring(1, Variables.at(i)) + L" != 0";
		ret answer;
	}

	// calcolo della posizione
	int StartIndex;
	tensor<int> CorrectSizes;
	tensor<int> VDirectorTerm;
	tensor<int> VKnownTerm;
	tensor<tensor<int>> VDirectorSeq;
	tensor<tensor<int>> VKnownSeq;
	auto equation{
		FromPolynomialToPos(
			Equation,
			StartIndex,
			CorrectSizes,
			VDirectorTerm,
			VKnownTerm,
			VDirectorSeq,
			VKnownSeq
		)
	};

	// caso di sicurezza
	if (equation.empty() and Variables.size() == 1) {
		FACTOR<> eq{ To1V(Equation) };
		eq.sort();
		eq.complete(eq[0].degree + 1);
		tensor<long double> _eq;
		for (const auto& term : eq) _eq << term.coefficient;
		equation = { _eq };
		VDirectorSeq = { { 1 } };
		VKnownSeq = { { 0 } };
	}

	// risoluzione dell'equazione
	if (!equation.empty()) for (;;) {

		if (equation[0] == 2) break;

		// equazione di secondo grado
		if (equation[0] == 3) {
			long double A, B, C;
			A = equation[0][0];
			B = equation[0][1];
			C = equation[0][2];

			long double delta_4{ (B * B - 4 * A * C) / (4 * A * A) };
			long double half_root_sum{ -B / (2 * A) };
			wstring _push;

			// radici reali
			if (delta_4 >= 0) {
				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ to_wstring(half_root_sum + sqrt(delta_4));

				if (VKnownSeq[0] != null)
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;

				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ to_wstring(half_root_sum - sqrt(delta_4));

				if (VKnownSeq[0] != null)
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;
			}

			// radici complesse
			else {
				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ complex<double>(half_root_sum, sqrt(-delta_4)).str();
				if (VKnownSeq[0] != null)
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;

				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ complex<double>(half_root_sum, -sqrt(-delta_4)).str();
				if (VKnownSeq[0] != null)
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;
			}
			ret answer;
		}

		// metodo di newton-raphson
		long double root{};
		Approximator(equation[0], root);
		auto push{
			factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != " + to_wstring(root)
		};
		if (VKnownSeq[0] != null)
			push += factor<>{ { 1, VKnownSeq[0] } }.str();
		answer << push;
	}

	// caso binomio
	if (Equation == 2) {
		int gcd{ abs(Gcd(Equation)) };
		Equation[0].coefficient /= gcd;
		Equation[1].coefficient /= gcd;

		for (size_t i = 0; i < Variables.size(); ++i) {
			int min{ ::min(Equation[0].exp[i], Equation[1].exp[i]) };
			Equation[0].exp[i] -= min;
			Equation[1].exp[i] -= min;
		}
		Equation.SortByExponents();

		auto coeff{ Equation[0].coefficient };
		Equation[0].coefficient = 1;
		if (coeff < 0) coeff *= -1;
		else Equation[1].coefficient *= -1;

		wstring push{ factor<>{ Equation[0] }.str() + L" != " };
		push += factor<>{ Equation[1] }.str();
		if (coeff != 1) push += L" / " + to_wstring(coeff);
		ret { push };
	}

	// caso molto generico
	factor<> top, bottom;
	size_t Vpos{ Variables.find(L'x') };
	for (const auto& mon : Equation) if (mon.exp[Vpos] > 1)
		ret { Equation.str() + L"!= 0" };

	// caso con variabile e parametri
	for (auto mon : Equation) {
		if (mon.exp[Vpos] == 1) {
			mon.exp[Vpos] = 0;
			bottom << mon;
			continue;
		}
		mon.coefficient *= -1;
		top << mon;
	}

	// ricerca variabili
	tensor<bool> Used(Variables.size(), false);
	for (const auto& mon : Equation)
		for (size_t i = 0; i < Variables.size(); ++i) if (mon.exp[i] > 0)
			Used[i] = true;
		
	// calcolo stringhe
	auto D = bottom.empty() ? L"1" : bottom.str();
	auto DD{ D };
	if (D == L"-1") {
		D = L"1";
		for (auto& mon : top) mon.coefficient *= -1;
	}
	auto N = top.empty() ? L"1" : top.str();
	auto NN{ N };
	if (issign(NN.at(0))) NN.erase(0, 1);
	if (issign(DD.at(0))) DD.erase(0, 1);

	// concatenazione stringhe
	if (NN.find(L'+') != wstring::npos or NN.find(L'-') != wstring::npos)
		N = L'(' + N + L')';
	if (DD.find(L'+') != wstring::npos or DD.find(L'-') != wstring::npos)
		D = L'(' + D + L')';
	auto str{ N };

	// controllo denominatore
	if (D == L"-1") {
		if (str.at(0) == L'(') str.erase(0, 1);
		if (str.find(L'(') == wstring::npos) str.pop_back();
		else str = L'(' + str;
		str.at(0) == L'-' ? str.erase(0, 1) : str = L'-' + str;
	}
	if (D != L"1") str += L'/' + D;

	ret Used[Vpos] ?
		tensor<wstring>{ L"x != " + str } : tensor<wstring>{ str + L" != 0" };
}

// risolve un sistema non lineare con il metodo di newton-raphson
static tensor<tensor<long double>> SystemSolver(tensor<factor<>> functions)
{
	const double TOL{ 1e-06 };
	tensor<int> null(Variables.size(), 0);

	// calcolo del grado del sistema
	if (functions != Variables.size()) ret {};
	int degree{ 1 };
	for (const auto& function : functions) {
		int max{ function[0].degree() };
		for (size_t i = 1; i < function; ++i) {
			int deg{ function[i].degree() };
			if (max < deg) max = deg;
		}
		degree *= max;
	}

	// casi semplificati
	if (degree == 0) ret {};
	if (degree == 1) {
		tensor<tensor<long double>> solutions(1);

		// calcolo termini noti
		tensor<int> KnownTerms(Variables.size(), 0);
		for (size_t i = 0; i < functions; ++i)
			for (size_t j = 0; j < functions[i]; ++j)
				if (functions[i][j].exp == null)
					KnownTerms[i] = -functions[i][j].coefficient;

		// calcolo coefficienti interni
		Matrix<int> system(Variables.size(), tensor<int>(Variables.size(), 0));
		for (size_t i = 0; i < functions; ++i)
			for (size_t j = 0; j < functions[i]; ++j)
				for (size_t k = 0; k < Variables.size(); ++k)
					if (functions[i][j].exp[k] == 1)
						system[k][i] = functions[i][j].coefficient;

		// calcolo determinanti
		auto D{ system.det<long double>() };
		tensor<long double> dets;
		for (size_t i = 0; i < Variables.size(); ++i) {
			auto mx{ system };
			mx[i] = KnownTerms;
			dets << mx.det<long double>();
		}
		if (D == 0) {
			if (dets == tensor<long double>(dets.size(), 0)) ret { { nan("") } };
			ret { {} };
		}
		for (const auto& det : dets) solutions[0] << det / D;
		ret solutions;
	}
	
	// calcolo variabili iniziali
	tensor<Fraction<>> NewFunctions;
	for (const auto& funct : functions) NewFunctions << Fraction<>({ funct });
	tensor<tensor<long double>> solutions;
	tensor<long double> StarterPoint;
	for (size_t i = 0; i < Variables.size(); ++i)
		StarterPoint << pow(5, 1.0 / (i + 2));

	// calcolo di ogni coppia ordinata
	for (int i = 0; i < 100 and solutions < degree; ++i) {

		// calcolo dello jacobiano
		Matrix<Fraction<>> Jacobian(Variables.size());
		for (size_t j = 0; j < Variables.size(); ++j)
			for (size_t k = 0; k < Variables.size(); ++k)
				Jacobian[j] << NewFunctions[j].derivate(k);
		auto solution{ StarterPoint };

		for (int j = 0; j < 100; ++j) {
			
			// valutazione dello jacobiano nel punto
			Matrix<> JInvpoint(Variables.size());
			for (size_t k = 0; k < Variables.size(); ++k)
				for (size_t l = 0; l < Variables.size(); ++l)
					JInvpoint[k] << Jacobian[k][l](solution);

			// inversione
			auto determinant{ JInvpoint.det<long double>() };
			JInvpoint = determinant == 0 ?
				JInvpoint.invert(1e-03) : JInvpoint.invert(determinant);

			// aggiornamento punto
			tensor<long double> vect;
			for (size_t k = 0; k < Variables.size(); ++k)
				vect << NewFunctions[k](solution);
			tensor<long double> updater{ JInvpoint * vect };
			for (size_t k = 0; k < Variables.size(); ++k)
				solution[k] -= updater[k];

			// uscita
			long double norm{};
			for (size_t k = 0; k < Variables.size(); ++k)
				norm += updater[k] * updater[k];
			if (norm < TOL) break;
		}

		// aggiunta
		bool present{ false };
		for (auto& sol : solutions) {

			bool LocalPresent{ true };
			for (size_t j = 0; j < sol; ++j)
				if (fabs(sol[j] - solution[j]) > 100 * TOL)
				{
					LocalPresent = false;
					break;
				}
			if (LocalPresent) {
				present = true;
				break;
			}
		}
		if (!present) solutions << solution;

		// rimozione soluzione dalle funzioni
		factor<> remover;
		for (size_t j = 0; j < Variables.size(); ++j) {
			tensor<int> exponent(Variables.size(), 0);
			remover << monomial<>{ solution[j] * solution[j], exponent };
			exponent[j] = 1;
			remover << monomial<>{ -2 * solution[j], exponent };
			exponent[j] = 2;
			remover << monomial<>{ 1, exponent };
		}
		for (auto& newfunct : NewFunctions) newfunct.den[0] *= remover;
	}

	ret solutions;
}

// converte le soluzioni di un'equazione da stringa a numero
static tensor<long double> RootExtractor(polynomial<> vect)
{
	bool repeat{ false };
	tensor<long double> roots;
	for (const auto& fact : vect) {
		if (fact.empty()) continue;

		// modificatore
		if (fact[0].exp[0] < 0) {
			repeat = true;
			continue;
		}
		auto solutions{ EquationSolver(fact) };

		// molteplicità delle soluzioni
		if (fact == 1 and fact[0].exp[Variables.find(L'x')] == 2)
			solutions += solutions;

		// aggiunta delle radici del numeratore
		for (auto sol : solutions) if (sol.find(L'i') == wstring::npos)
		{
			sol.erase(0, 5);
			auto fden{ sol };

			if (sol.find(L'/') != wstring::npos) {
				while (fden.at(0) != L'/') fden.erase(0, 1);
				fden.erase(0, 1);
				while (Last(sol) != L'/') sol.pop_back();
				sol.pop_back();
			}
			else fden = L"1";

			auto root{ stold(sol) / stold(fden) };
			roots << root;
			if (repeat)	roots << root;
		}
		repeat = false;
	}

	ret roots;
}

// parte indipendente dal segno di una disequazione normale
static void FractDisequationMain(
	polynomial<> Num, polynomial<> Den,
	
	tensor<wstring>& Roots,
	tensor<bool>& ItsFromDenominator,

	bool& InitSign, bool& Invert
)
{
	// calcolo del segno dei coefficienti
	polynomial<> Un{ Num + Den };
	long double Coeff{ 1 };
	for (size_t i = 0; i < Un; ++i)
		if (Un[i] == 1 and Un[i][0].exp == tensor<int>{ 0 })
			Coeff *= Un[i][0].coefficient;
	Invert = Coeff < 0;

	// calcolo delle radici
	auto roots{ RootExtractor(Num) };
	ItsFromDenominator = tensor<bool>(roots.size(), false);
	roots += RootExtractor(Den);
	ItsFromDenominator += tensor<bool>(
		roots.size() - ItsFromDenominator.size(), true
	);
	for (ptrdiff_t i = roots.size() - 1; i >= 0; --i)
		if (roots[i] <= -2'147'483'647 or roots[i] >= 2'147'483'647)
			roots.erase(roots.begin() + i);

	// ordinamento delle radici
	for (size_t i = 0; i < roots; ++i) for (size_t j = i + 1; j < roots; ++j)
		if (roots[i] > roots[j])
		{
			swap(roots[i], roots[j]);
			swap(ItsFromDenominator[i], ItsFromDenominator[j]);
		}

	// calcolo segno
	InitSign = POS;
	for (auto& fact : Num) {
		if (fact.empty()) continue;
		fact.SortByExponents();
		if (fact[0].coefficient < 0) InitSign = !InitSign;
	}
	for (auto& fact : Den) {
		if (fact.empty()) continue;
		fact.SortByExponents();
		if (fact[0].coefficient < 0) InitSign = !InitSign;
	}

	for (const auto& root : roots) Roots << Handler(to_wstring(root));
}

// parte dipendente dal segno di una disequazione normale
static ConsoleStream GetAlgebricSolution(
	tensor<wstring> roots,
	tensor<bool> ItsFromDenominator,

	bool InitialSign,
	bool ExpectedSign,
	bool CanBeNull
)
{
	// correzione dei segni
	ConsoleStream text;
	bool condition{ ((InitialSign == (roots.size() % 2 == 0)) == ExpectedSign) };
	for (ptrdiff_t i = 0; i < roots.size() - 1; ++i) {
		bool SamePart{ int(i % 2) == condition };
		if (i >= roots) break;

		if (roots[i] == roots[i + 1]) {
			bool T0{ ItsFromDenominator[i] or !CanBeNull };
			bool T1{ ItsFromDenominator[i + 1] or !CanBeNull };

			// eliminazione zeri inutili
			if (
				(T0 and T1 and SamePart) or
				!(T0 or T1 or SamePart) or
				(!SamePart and (T0 xor T1))
				)
			{
				roots.erase(roots.begin() + i + 1);
				roots.erase(roots.begin() + i);
				ItsFromDenominator.erase(ItsFromDenominator.begin() + i + 1);
				ItsFromDenominator.erase(ItsFromDenominator.begin() + i);
				i--;
				continue;
			}

			// correzione segni discordanti
			if ((T0 xor T1) and SamePart)
			{
				ItsFromDenominator[i] = true;
				ItsFromDenominator[i] = false;
			}
		}
	}
	if (roots.empty()) ret InitialSign == ExpectedSign ?
		ConsoleStream{ Console(L"per ogni x appartenente a R", 11) } :
		ConsoleStream{ Console(L"per nessun x", 11) };

	// parte iniziale
	if (condition) {
		text = { Console(L"x") };
		CanBeNull and !ItsFromDenominator[0] ?
			text << Console(L" <= ") : text << Console(L" < ");
		text << Console(roots[0]);
		if (roots > 1) text << Console(L" V ", 8);
	}

	for (size_t i = condition; i < roots; i += 2) {

		// parte finale
		if (i + 1 == roots) {
			CanBeNull and !ItsFromDenominator[i] ?
				text << Console(L"x >= ") : text << Console(L"x > ");
			text << Console(roots[i]);
			break;
		}

		// parte centrale
		text << Console(roots[i]);
		CanBeNull and !ItsFromDenominator[i] ?
			text << Console(L" <= x") : text << Console(L" < x");
		CanBeNull and !ItsFromDenominator[i + 1] ?
			text << Console(L" <= ") : text << Console(L" < ");
		text << Console(roots[i + 1]);
		if (i + 2 < roots) text << Console(L" V ", 8);
	}

	for (auto& cons : text) ElabExponents(cons.Text);
	ret text;
}

// inizio di una disequazione parametrica
static bool ParamDisequationSetup(
	polynomial<>& Num, polynomial<>& Den, polynomial<>& Sum,

	tensor<bool>& FromDenominator,
	tensor<long double>& AdditionalRoots,
	factor<>& Parametric,

	tensor<factor<>>& tops,
	tensor<factor<>>& bottoms,

	bool& InitSign,
	bool& InvertSign
)
{
	auto Vpos{ Variables.find(L'x') };

	// calcolo polinomi in entrata
	for (auto& fact : Num) if (fact[0].exp[0] < 0 and fact[0].coefficient > 2)
		fact[0].coefficient = (int)fact[0].coefficient % 2;
	for (auto& fact : Den) if (fact[0].exp[0] < 0 and fact[0].coefficient > 2)
		fact[0].coefficient = (int)fact[0].coefficient % 2;
	Num.open();
	Den.open();
	Sum = Num + Den;
	for (auto& fact : Sum) for (const auto& mon : fact)
		if (mon.exp[Vpos] > 1) ret false;
	FromDenominator =
		tensor<bool>(Num.size(), false) + tensor<bool>(Den.size(), true);

	// calcolo segno iniziale
	InitSign = POS;
	for (auto& fact : Sum) {
		fact.SortByExponents();
		if (fact[0].coefficient < 0) InitSign = !InitSign;
	}

	// calcolo dei termini parametrici
	tensor<factor<>> Parametrics;
	for (ptrdiff_t i = Sum.size() - 1; i >= 0; --i) {
		bool IsACoefficient{ true };
		for (const auto& mon : Sum[i]) if (mon.exp[Vpos] != 0) {
			IsACoefficient = false;
			break;
		}
		if (IsACoefficient) {
			Parametrics << Sum[i];
			Sum.erase(Sum.begin() + i);
			FromDenominator.erase(FromDenominator.begin() + i);
			if (Sum.empty()) ret false;
		}
	}
	AdditionalRoots = RootExtractor(Parametrics);
	Parametric = PolynomialMultiply<long double>(Parametrics);

	// calcolo zeri dei fattori
	tops(Sum.size()), bottoms(Sum.size());
	for (size_t i = 0; i < Sum; ++i) {
		auto fact{ Sum[i] };

		// push
		for (auto mon : fact) {
			if (mon.exp[Vpos] == 1) {
				mon.exp[Vpos] = 0;
				bottoms[i] << mon;
				continue;
			}
			mon.coefficient *= -1;
			tops[i] << mon;
		}

		// gestione dei coefficienti
		if (tops[i].empty()) tops[i] = factor<>{ { 1, { 0, 0 } } };
		if (bottoms[i].empty()) bottoms[i] = factor<>{ { 1, { 0, 0 } } };
		if (fact == 1 and fact[0].exp == tensor<int>{ 0, 0 })
		{
			InvertSign =
				((tops[i][0].coefficient < 0) xor (bottoms[i][0].coefficient < 0));
			Sum.erase(Sum.begin() + i);
			tops.erase(tops.begin() + i);
			bottoms.erase(bottoms.begin() + i);
			i--;
		}
	}

	ret true;
}

// parte indipendente dal segno di una disequazione parametrica
static void ParamDisequationMain(
	polynomial<> Un,
	tensor<factor<>> tops,
	tensor<factor<>> bottoms,
	tensor<long double> AdditionalRoots,

	size_t& Unisize,
	tensor<tensor<factor<>>>& TableOfMains,
	tensor<long double>& RootSet,
	tensor<long double>& RootExamples,
	tensor<wstring>& vals
)
{
	// calcolo delle disequazioni principali
	Unisize = Un.size();
	tensor<tensor<factor<>>> FirstTable(
		bottoms.size(), tensor<factor<>>(bottoms.size())
	);
	TableOfMains = FirstTable;
	if (Unisize > 1) for (int first = 0; first < TableOfMains; ++first)
		for (int second = first + 1; second < TableOfMains; ++second)
			TableOfMains[first][second] =
				tops[first] * bottoms[second] - tops[second] * bottoms[first];
	if (FirstTable == TableOfMains) Unisize = 1;

	// calcolo radici
	RootSet = tensor<long double>{ RootExtractor(bottoms) };
	if (Unisize > 1) for (auto& F : TableOfMains) for (auto& S : F)
		RootSet += RootExtractor({ S });
	RootSet += AdditionalRoots;

	if (!RootSet.empty()) {

		// ordinamento radici
		long double RepeatedValue{ RootSet.last() };
		for (size_t i = 0; i < RootSet; ++i)
			for (size_t j = i + 1; j < RootSet; ++j)
				if (RootSet[i] > RootSet[j])
					swap(RootSet[i], RootSet[j]);

		// rimozione duplicati
		for (ptrdiff_t i = RootSet.size() - 2; i >= 0; --i) {
			if (RootSet[i] == RepeatedValue) {
				RootSet.erase(RootSet.begin() + i);
				continue;
			}
			RepeatedValue = RootSet[i];
		}

		// calcolo intervalli
		RootExamples << RootSet[0] - 1;
		for (ptrdiff_t i = 0; i < RootSet.size() - 1; ++i)
			RootExamples << (RootSet[i] + RootSet[i + 1]) / 2.0;
		RootExamples << RootSet.last() + 1;

	}
	else RootExamples = { 0 };

	// calcolo valori
	for (size_t i = 0; i < Un; ++i) {
		auto D = bottoms[i].empty() ? L"1" : bottoms[i].str();
		auto DD{ D };
		auto top{ tops[i] };
		if (D == L"-1") {
			D = L"1";
			for (auto& mon : top) mon.coefficient *= -1;
		}

		auto N = top.empty() ? L"1" : top.str();
		auto NN{ N };
		if (issign(NN.at(0))) NN.erase(0, 1);
		if (issign(DD.at(0))) DD.erase(0, 1);

		if (NN.find(L'+') != wstring::npos or NN.find(L'-') != wstring::npos)
			N = L'(' + N + L')';
		if (DD.find(L'+') != wstring::npos or DD.find(L'-') != wstring::npos)
			D = L'(' + D + L')';
		auto str{ N };
		if (D != L"1") str += L'/' + D;
		vals << str;
	}
}

// parte dipendente dal segno di una disequazione parametrica
static ConsoleStream GetParametricSolution(
	wchar_t parameter,
	size_t Unisize, size_t Vpos,
	bool InitialSign, bool ExpectedSign, bool CanBeNull,

	tensor<bool> TermsFromDenominator,
	polynomial<>& Num, polynomial<>& Den, factor<> Parametric,
	tensor<factor<>> tops, tensor<factor<>> bottoms,

	tensor<tensor<factor<>>> TableOfMains,
	tensor<long double> RootSet, tensor<long double> RootExamples,
	tensor<wstring> vals
)
{
	ConsoleStream text;

	// iterazione su ogni intervallo
	tensor<wstring> ParameterIntervals;
	tensor<ConsoleStream> UnknownIntervals;
	for (size_t index = 0; index < RootExamples; ++index) {
		auto interval{ RootExamples[index] };
		auto values{ vals };
		auto ItsFromDenominator{ TermsFromDenominator };
		ConsoleStream line;
		tensor<int> SumOfGEQValues(bottoms.size(), 0);

		// output intervallo iniziale
		if (index == 0) {
			ParameterIntervals << wstring(1, parameter);
			ParameterIntervals[0] += L" < " + Handler(to_wstring(RootSet[0]));
			UnknownIntervals << ConsoleStream{ Console(L"\n") };
			goto comparison;
		}

		// output intervallo finale
		if (index == RootSet) {
			ParameterIntervals << wstring(1, parameter);
			ParameterIntervals.last() +=
				L" > " + Handler(to_wstring(RootSet.last()));
			UnknownIntervals << ConsoleStream{ Console(L"\n") };
			goto comparison;
		}

		// output intervalli centrali
		ParameterIntervals << Handler(to_wstring(RootSet[index - 1]));
		CanBeNull and index - 1 < bottoms ?
			ParameterIntervals.last() += L" <= " :
			ParameterIntervals.last() += L" < ";
		ParameterIntervals.last() += wstring(1, parameter);
		CanBeNull and index < bottoms ?
			ParameterIntervals.last() += L" <= " :
			ParameterIntervals.last() += L" < ";
		ParameterIntervals.last() += Handler(to_wstring(RootSet[index]));
		UnknownIntervals << ConsoleStream{ Console(L"\n") };

	comparison:
		if (Unisize == 1) goto add_line;

		// calcolo dei segni
		for (size_t first = 0; first < SumOfGEQValues; ++first)
			for (size_t second = first + 1; second < SumOfGEQValues; ++second)
			{
				bool value{
					(TableOfMains[first][second](interval, 1 - Vpos, true))
						==
					(
						bottoms[first](interval, 1 - Vpos, true)
						==
						bottoms[second](interval, 1 - Vpos, true)
					)
				};

				SumOfGEQValues[first] += value;
				SumOfGEQValues[second] += !value;
			}

		// controllo legalità dei confronti
		for (size_t i = 0; i < SumOfGEQValues; ++i)
			for (size_t j = i + 1; j < SumOfGEQValues; ++j)
				if (SumOfGEQValues[i] == SumOfGEQValues[j])
					line = { Console(L"  ->  ", 8), Console(L"impossibile", 11) };

		// confronto valori
		for (size_t i = 0; i < SumOfGEQValues; ++i)
			for (size_t j = i + 1; j < SumOfGEQValues; ++j)
				if (SumOfGEQValues[i] > SumOfGEQValues[j])
				{
					swap(SumOfGEQValues[i], SumOfGEQValues[j]);
					swap(values[i], values[j]);
					swap(ItsFromDenominator[i], ItsFromDenominator[j]);
				}

		// output intervallo della variabile
	add_line:
		line = ConsoleStream{ Console(L"  ->  ", 8) } + GetAlgebricSolution(
			values,
			ItsFromDenominator,
			InitialSign,
			ExpectedSign == Parametric(interval, 1 - Vpos, true),
			CanBeNull
		);
		UnknownIntervals.last() = line + UnknownIntervals.last();
		if (index == RootSet) break;

		// valori speciali
		ParameterIntervals << wstring(1, parameter) + L" = ";
		ParameterIntervals.last() += Handler(to_wstring(RootSet[index]));
		auto numerator{ Num };
		auto denominator{ Den };
		for (auto& fact : numerator) fact = fact(RootSet[index], 1 - Vpos, 1);
		for (auto& fact : denominator) fact = fact(RootSet[index], 1 - Vpos, 1);

		// modifiche alla lista di variabili
		if (Vpos == 1) {
			for (auto& fact : numerator) for (auto& mon : fact)
				mon.exp[0] = mon.exp[1];
			for (auto& fact : denominator) for (auto& mon : fact)
				mon.exp[0] = mon.exp[1];
		}
		auto save{ Variables };
		Variables = L"x";

		// aggiunta dei casi particolari
		UnknownIntervals << ConsoleStream{ Console(L"  ->  ", 8) };
		if (numerator.empty()) numerator = polynomial<>{ { { 0, { 0 } } } };
		if (denominator.empty()) denominator = polynomial<>{ { { 0, { 0 } } } };
		UnknownIntervals.last() += DisequationSolutionPrinter(
			numerator,
			denominator,
			1 << (
				2 * (ExpectedSign xor Parametric(RootSet[index], 1 - Vpos, true))
				+ CanBeNull
				),
			false,
			false
		) + ConsoleStream{ Console(L"\n") };
		Variables = save;
	}

	// riorganizzazione del risultato finale
	size_t sizemax{ ParameterIntervals[0].size() };
	for (size_t i = 1; i < ParameterIntervals; ++i)
		if (sizemax < ParameterIntervals[i].size())
			sizemax = ParameterIntervals[i].size();
	for (auto& word : ParameterIntervals) if (word.size() < sizemax)
		word += wstring(sizemax - word.size(), L' ');
	for (size_t i = 0; i < ParameterIntervals; ++i) {
		text << Console(ParameterIntervals[i]);
		for (size_t j = 0; j < UnknownIntervals[i]; ++j)
			text << UnknownIntervals[i][j];
	}

	for (auto& cons : text) ElabExponents(cons.Text);
	ret text;
}

// risolve una disequazione fratta con un parametro
static ConsoleStream DisequationSolutionPrinter(
	polynomial<> Num,
	polynomial<> Den,
	int behaviour,
	bool ChangeSign,
	bool PrintCondition
)
{
	// controlli iniziali
	auto Vpos{ Variables.find(L'x') };
	if (Variables.size() > 2 or Vpos == wstring::npos) ret {};

	// calcolo frasi
	if (Num.empty() and Den.empty()) ret {};
	WORD wAttribute{ 6 };
	wstring expr = Variables == L"x" ?
		L"F(x)" : L"F(x, " + wstring(1, Variables.at(1 - Vpos)) + L")";
	expr = L"SE  " + expr;
	ConsoleStream dir{
		Console(expr + L" < 0   ALLORA", wAttribute),
		Console(expr + L" <= 0  ALLORA", wAttribute),
		Console(expr + L" > 0   ALLORA", wAttribute),
		Console(expr + L" >= 0  ALLORA", wAttribute)
	};

	// disequazione normale
	if (Variables == L"x") {
		
		// calcolo principale
		tensor<wstring> roots;
		tensor<bool> ItsFromTheDenominator;
		bool InitialSign, InvertTheSign;
		FractDisequationMain(
			Num,
			Den,
			roots,
			ItsFromTheDenominator,
			InitialSign,
			InvertTheSign
		);

		// output
		ConsoleStream Output;
		for (int i = 0; i < 4; ++i) if ((behaviour | (1 << i)) == behaviour) {
			bool positive = i / 2;
			if (PrintCondition) Output << dir[i] << Console(L"\n\n");

			Output += GetAlgebricSolution(
				roots,
				ItsFromTheDenominator,
				InitialSign,
				(positive == InvertTheSign) xor ChangeSign,
				i % 2 == 1
			);

			if (PrintCondition) Output << Console(L"\n\n");
		}

		if (PrintCondition) {
			Output--;
			Output << Console(L"\n----------");
		}
		ret Output;
	}
	// disequazione parametrica

	// parte principale
	wchar_t parameter{ Variables.at(1 - Vpos) };
	polynomial<> Un;
	tensor<bool> TermsFromDenominator;
	tensor<long double> AdditionalRoots;
	factor<> Parametric;
	tensor<factor<>> tops, bottoms;
	bool InitialSign, InvertSign{ true };
	if (
		!ParamDisequationSetup(
			Num,
			Den,
			Un,
			TermsFromDenominator,
			AdditionalRoots,
			Parametric,
			tops,
			bottoms,
			InitialSign,
			InvertSign
		)
	) ret {};

	// caso di un fattore
	if (Un == 1 and Parametric == factor<>{ { 1, { 0, 0 } } }) {
		ConsoleStream Output;
		tensor<wstring> vals{ EquationSolver(Un[0]) };
		if (vals == 1) if (isalpha(vals[0].at(0)) and isalpha(vals[0].at(1))) {
			if (vals[0].find(L'/') == wstring::npos) vals[0] += L'/';
			vals[0] += parameter;
		}
		for (auto& val : vals) val.erase(0, 5);

		// output
		for (int i = 0; i < 4; ++i) if ((behaviour | (1 << i)) == behaviour) {
			bool positive = i / 2;
			if (PrintCondition) Output << dir[i] << Console(L"\n\n");

			Output += GetAlgebricSolution(
				vals,
				tensor<bool>(vals.size(), TermsFromDenominator[0]),
				InitialSign,
				(positive == InvertSign) xor ChangeSign,
				i % 2 == 1
			);

			if (PrintCondition) Output << Console(L"\n\n");
		}

		if (PrintCondition) {
			Output--;
			Output << Console(L"\n----------");
		}
		ret Output;
	}

	// calcolo dei dati indipendenti dai segni
	size_t Unisize;
	tensor<tensor<factor<>>> TableOfMains;
	tensor<long double> RootSet, RootExamples;
	tensor<wstring> vals;
	ParamDisequationMain(
		Un,
		tops,
		bottoms,
		AdditionalRoots,
		Unisize,
		TableOfMains,
		RootSet,
		RootExamples,
		vals
	);
	
	// output
	ConsoleStream Output;
	for (int i = 0; i < 4; ++i) if ((behaviour | (1 << i)) == behaviour) {
		bool positive = i / 2;
		if (PrintCondition) Output << dir[i] << Console(L"\n\n");

		Output += (
			RootSet.empty() ?

			// nessuno zero trovato
			GetAlgebricSolution(
				vals,
				TermsFromDenominator,
				InitialSign,
				(positive xor InvertSign) xor ChangeSign,
				i % 2 == 1
			) + ConsoleStream{ Console(L"\n") } :
			
			// caso comune
			GetParametricSolution(
				parameter,
				Unisize,
				Vpos,
				InitialSign,
				(positive xor InvertSign) xor ChangeSign,
				i % 2 == 1,
				TermsFromDenominator,
				Num,
				Den,
				Parametric,
				tops,
				bottoms,
				TableOfMains,
				RootSet,
				RootExamples,
				vals
			)
		);

		if (PrintCondition) Output << Console(L"\n");
	}

	if (PrintCondition) {
		Output--;
		Output << Console(L"\n----------");
	}
	ret Output;
}

#pragma endregion

// funzioni programma
#pragma region Programs

// programma per convertire un codice in un numero
static void CodeToNumber(switchcase& argc)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// istruzioni
	wstring to_evaluate, ToEvaluate, message;
	bool ShowErrors{ true }, NecessaryBoundary{ true };
	SetConsoleTextAttribute(hConsole, 14);
	wcout << L"Il PROGRAMMA traduce una stringa di codice\n\n";
	SetConsoleTextAttribute(hConsole, 12);

	wcout << L"Il codice non deve avere errori o verranno segnalati\n";
	wcout << L"Il codice deve essere compreso tra <>\n";
	wcout << L"Se sono presenti piu' caratteri '<', '>',\n";
	wcout << L"verranno considerati solo quelli che compaiono prima\n";
	wcout << L"Unici caratteri non numerici ammessi: '(', ')', '+', '.' \n\n";

	SetConsoleTextAttribute(hConsole, 9);
	wcout << L"Si indichino le cifre incognite con caratteri '_'\n";
	wcout << L"Aggiungendo '$' come primo carattere\n";
	wcout << L"oppure '\\' o '/' senza <> non vengono mostrati gli errori\n\n";
	ResetAttribute();

	for (;;)
	{
		do {
			message.clear();

			// input e controllo
			wcout << L"Inserire una stringa (f = fine input)\n";
			wcout << L"per fermare il calcolo premere s\\S\n";
			getline(wcin, ToEvaluate);
			if (ToEvaluate == L"f") {
				argc = NotAssigned;
				ret;
			}
			argc = ConvertWStringToEnum(ToEvaluate);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(ToEvaluate.c_str());
				ret;
			}
			if (ToEvaluate == L".") {
				argc = Random;
				ret;
			}

			// ammissione errori
			if (!ToEvaluate.empty()) {
				NecessaryBoundary =
					ToEvaluate.at(0) != L'\\' and ToEvaluate.at(0) != L'/';
				ShowErrors = ToEvaluate.at(0) != L'$' and NecessaryBoundary;
				if (!NecessaryBoundary) ToEvaluate.erase(0, 1);
			}

			// individuazione degli errori
			to_evaluate = ToEvaluate;
			if (NecessaryBoundary) message = UpdateString(ToEvaluate);
			if (message.empty()) message = NumberCodeSyntax(ToEvaluate);

			// output errori
			if (message.size() > 1) {
				lock_guard<mutex> lock(CoutMutex);
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"ERR[404]: " << message << L'\n';
				ResetAttribute();
			}

		} while (message.size() > 1);

		// eliminazione spazi
		for (ptrdiff_t space = ToEvaluate.size() - 1; space >= 0; --space)
			if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
				ToEvaluate.erase(space, 1);

		// reset globali
		{
			lock_guard<mutex> lock(mtx);
			GlobalInterr = false;
			interrupted = false;
			computing = true;
		}
		Cv.notify_all();
		HIDECURSOR;

		// dichiarazione ed esecuzione dei thread
		thread ComputationThread([=]() {
			LongComputation(to_evaluate, message, ShowErrors, NecessaryBoundary);
			}
		);
		thread InputThread(UserInputThread);
		unique_lock<mutex> lock(CoutMutex);
		Cv.wait(lock, [] { ret !GlobalInterr; });
		if (ComputationThread.joinable()) ComputationThread.join();
		if (InputThread.joinable()) InputThread.join();

		// se il calcolo viene interrotto
		if (GlobalInterr) {
			SetConsoleTextAttribute(hConsole, 14);
			wcout << L"\nFine del calcolo\n\n";
			ResetAttribute();
		}
		SetConsoleCursorInfo(hConsole, &cursor);
	}
}

// programma per convertire un numero in un codice basato sull'espansione in serie
tensor<tensor<wstring>> Map(17);
static wstring ExpandNumber(
	switchcase& argc,
	big Number,		/*  attivato se bisogna codificare ricorsivamente un numero  */
	int Base,		/*  base della codifica                                      */
	bool access		/*  stabilisce se è possibile accedere a determinate parti   */
)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// istruzioni
	bool code{ true };
	wstring ToEvaluate;
	bool RetAccess{ false };
	if (access)
	{
		SetConsoleTextAttribute(hConsole, 14);
		wcout << L"Il PROGRAMMA calcola la codifica in serie di un numero\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		wcout << L"Per codificare un numero inserire solo caratteri numerici\n";
		wcout << L"Il numero deve essere compreso tra 1 e 10^50 - 1\n";
		wcout << L"Per decodificare una stringa, aggiungere <> e ricordarsi\n";
		wcout << L"di aggiungere la base di decodifica rispettiva all'inizio\n";
		wcout << L"Se non si aggiunge la base, la decodifica verrà effettuata per\n";
		wcout << L"tutte le basi da 2 a 16\n";
		ResetAttribute();
	}

	for (;;)
	{
		if (!RetAccess) code = true;
		if (access)
		{
		input:

			// input
			SetConsoleTextAttribute(hConsole, 11);
			wcout << L"\nInserire un numero o una stringa (f = fine input)\n";
			ResetAttribute();
			getline(wcin, ToEvaluate);
			for (ptrdiff_t i = ToEvaluate.size() - 1; i >= 0; --i)
				if (ToEvaluate.at(i) == L' ' or ToEvaluate.at(i) == L'\t')
					ToEvaluate.erase(i, 1);

			// casi particolari
			if (ToEvaluate == L"f") {
				argc = NotAssigned;
				ret L"";
			}
			argc = ConvertWStringToEnum(ToEvaluate);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(ToEvaluate.c_str());
				ret L"";
			}
			if (ToEvaluate == L".") {
				argc = Random;
				ret L"";
			}

			// modifiche e validazione
			if (regex_search(ToEvaluate, wregex(L"<>"))) goto input;
			if (ToEvaluate.size() > 2 and (
					ToEvaluate.find(L'<') != wstring::npos and
					ToEvaluate.find(L'>') != wstring::npos
				))
			{
				code = false;

				// calcolo base
				Base = 2;
				if (Last(ToEvaluate) != L'>') goto input;
				int pos = ToEvaluate.find(L'<');
				switch (pos) {
				case 0: Base = -1;
					break;
				case 1:
					if (!isdigit(ToEvaluate.at(0))) goto input;
					Base = ToEvaluate.at(0) - L'0';
					break;
				case 2:
					if (!isdigit(ToEvaluate.at(0)) or
						!isdigit(ToEvaluate.at(1))) goto input;
					Base = (ToEvaluate.at(0) - L'0') * 10 +
						ToEvaluate.at(1) - L'0';
					break;
				default: goto input;
				}
				if ((Base < 2 or Base > 16) and Base >= 0) goto input;

				// estrazione stringa
				ToEvaluate.erase(0, pos + 1);
				ToEvaluate.pop_back();
				if (ToEvaluate.find(L'<') != wstring::npos and
					ToEvaluate.find(L'>') != wstring::npos) goto input;

				// controllo caratteri non ammessi
				if (regex_search(ToEvaluate, wregex(L"[^\\(\\)+\\d]")))
					goto input;

				// controllo sui segni
				if (ToEvaluate.at(0) == L'+' or Last(ToEvaluate) == L'+')
					goto input;
				for (size_t i = 1; i < ToEvaluate.size(); ++i)
					if (ToEvaluate.at(i - 1) == L'+' and ToEvaluate.at(i) == L'+')
						goto input;

				// controllo sulle parentesi
				int Parenthesis{};
				for (const auto& ch : ToEvaluate) {
					switch (ch) {
					case L'(': Parenthesis++;
						break;
					case L')': Parenthesis--;
						break;
					}
					if (Parenthesis < 0 or Parenthesis > 5) goto input;
				}

				// controllo riguardante segni e parentesi
				if (regex_search(ToEvaluate, wregex(L"\\)\\("))) goto input;
				if (regex_search(ToEvaluate, wregex(L"\\(\\)"))) goto input;
				for (size_t i = 1; i < ToEvaluate.size() - 1; ++i)
					if (ToEvaluate.at(i) == L'+' and (
						ToEvaluate.at(i - 1) == L'(' or
						ToEvaluate.at(i + 1) == L')')
						) goto input;
					
				// controllo lunghezza numeri
				if (ToEvaluate.size() >= 2)
					if (
						isdigit(Last(ToEvaluate)) and
						isdigit(ToEvaluate.at(ToEvaluate.size() - 2))
						) goto input;
				if (regex_search(ToEvaluate, wregex(L"\\d\\d[^\\(]")))
					goto input;
			}
			if (ToEvaluate.size() > 50 and code) goto input;

			// calcolo numero e controllo aggiuntivo
			if (code) {
				if (regex_search(ToEvaluate, wregex(L"\\D"))) goto input;
				Number = ToEvaluate;
			}
			if (Number == 0) goto input;

			// setup della decodifica di debug
			if (!code and Base == -1) {
				access = false;
				RetAccess = true;
				Base = 1;
			}
		}
		if (RetAccess) Base++;
		if (Base == 17) {
			access = true;
			RetAccess = false;
			Base = 2;
			continue;
		}

		// codifica
		if (code) for (int base = 2; base <= 16; ++base) {
			if (!access and base != Base) continue;

			wstring output;
			big number = Number;

			// calcolo logaritmo e coefficienti
			tensor<int> coefficients;
			for (int i = 0;; ++i) {
				if (number < base) break;
				big quotient = number / base;
				coefficients << (number - quotient * base).Number<int>();
				number = quotient;
			}
			coefficients << number.Number<int>();
			Map[base](max(Map[base].size(), coefficients.size()), L"");
			Map[base][0] = L"0";

			// calcolo esponenti
			for (ptrdiff_t i = coefficients.size() - 1; i >= 0; --i)
				if (coefficients[i] > 0)
				{
				
					wstring partial{ L"+" };
					bool recursion{ coefficients[i] > 1 };
					if (recursion) partial += to_wstring(coefficients[i]);
					if (Map[base][i].empty())
						Map[base][i] = ExpandNumber(argc, i, base, false);

					if (!recursion) recursion =
						Map[base][i].find(L'+') != wstring::npos or
						Map[base][i].find(L'(') != wstring::npos;
					if (recursion) partial += L'(' + Map[base][i] + L')';
					else partial += to_wstring(stoi(Map[base][i]) + 1);

					output += partial;
				}
			if (output.at(0) == L'+') output.erase(0, 1);
			if (!access) ret output;

			// output
			SetConsoleTextAttribute(hConsole, 6);
			wcout << L"Espansione in base " << base << L": ";
			ResetAttribute();
			wcout << L'<' << output << L">\n";
		}

		// decodifica
		else {
			auto toevaluate{ ToEvaluate };

			// calcolo delle tetrazioni
			tensor<big> tetration{ 0, 1, Base };
			big Last = Base;
			for (;;) {
				if (Last * log2(Base) >= 256) break;
				Last = big(Base) ^ Last;
				tetration << Last;
			}

			// sostituzione cifre pure
			for (ptrdiff_t i = toevaluate.size() - 1; i >= 0; --i)
				if (isdigit(toevaluate.at(i))) {

					// controlli
					if (i != (int)toevaluate.size() - 1)
						if (toevaluate.at(i + 1) == L'(') continue;
					int dim = toevaluate.at(i) - L'0';
					if (dim < 2) continue;
					if (dim >= tetration) goto overflow;

					// suddivisione e sostituzione
					auto first{ toevaluate };
					auto second{ toevaluate };
					first.erase(i);
					second.erase(0, i + 1);
					toevaluate = toevaluate.substr(0, i)
						+ tetration[dim].str()
						+ toevaluate.substr(i + 1, toevaluate.size() - 1);
				}

			// iterazione principale
			while (toevaluate.find(L'(') != wstring::npos)
				for (ptrdiff_t i = toevaluate.size() - 1; i >= 0; --i)
					if (toevaluate.at(i) == L'(')
					{

						// estrazione
						size_t j = i;
						for (; j < toevaluate.size(); ++j)
							if (toevaluate.at(j) == L')') break;
						auto part{ toevaluate };
						part.erase(j);
						part.erase(0, i + 1);

						// somma
						tensor<big> add;
						for (ptrdiff_t k = part.size() - 1; k >= 0; --k)
							if (part.at(k) == L'+') {
								auto NewPart{ part };
								part.erase(k);
								NewPart.erase(0, k + 1);
								add << NewPart;
							}
						add << part;
						big sum = 0;
						for (const auto& num : add) sum += num;

						// calcolo coefficiente
						int coefficient{ 1 }, size{};
						if (i > 0) if (isdigit(toevaluate.at(i - 1))) {
							coefficient = toevaluate.at(i - 1) - L'0';
							size = 1;
						}
						if (i > 1) if (
							isdigit(toevaluate.at(i - 1)) and
							isdigit(toevaluate.at(i - 2))
							)
						{
							coefficient = coefficient * 10 + 
								toevaluate.at(i - 1) - L'0';
							size = 2;
						}

						// calcolo risultato parziale
						if (sum * log2(Base) >= 256) goto overflow;
						big result = (big(Base) ^ sum) * coefficient;

						// ricomposizione
						auto first{ toevaluate };
						auto second{ toevaluate };
						first.erase(i - size);
						second.erase(0, j + 1);
						toevaluate = toevaluate.substr(0, i - size)
							+ result.str()
							+ toevaluate.substr(j + 1, toevaluate.size() - 1);
					}

			// ultima somma
			tensor<big> add;
			for (ptrdiff_t j = toevaluate.size() - 1; j >= 0; --j)
				if (toevaluate.at(j) == L'+') {
					auto part{ toevaluate };
					toevaluate.erase(j);
					part.erase(0, j + 1);
					add << part;
				}
			add << toevaluate;
			big LastSum = 0;
			for (const auto& num : add) LastSum += num;

			// output finale
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"base: " << Base << L", la decodifica è: ";
			wcout << LastSum << L'\n';
			ResetAttribute();
		}
		continue;

		// input troppo grande
	overflow:
		if (!RetAccess) {
			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"input out of range\a\n";
			ResetAttribute();
		}
		continue;
	}

	argc = NotAssigned;
	ret L"";
}

// programma per il calcolo
static void Repeater(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input)
)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	wstring n_{ to_wstring(GlobalMax) }, Input;
	ptrdiff_t input;
	NumberData result;
	SetConsoleTextAttribute(hConsole, 14);
	wcout << message << L"\n\n";
	ResetAttribute();

	for (;;)
	{
		// input e controllo
		SetConsoleTextAttribute(hConsole, 14);
		wstring txt{
			L"Inserire un numero tra 2 e " + n_ + L" (1 = fine input)\n"
		};
		ResetAttribute();
		Input = GetUserNum(txt, 1, GlobalMax, true);
		if (!Input.empty()) {
			if (Input == L".") {
				argc = Random;
				ret;
			}
			argc = ConvertWStringToEnum(Input);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(Input.c_str());
				ret;
			}
			input = stoull(Input);
		}

		// generatore casuale in caso di input vuoto
		else {
			random_device rng;
			mt19937 gen(rng());
			uniform_int_distribution<size_t> dis(2, GlobalMax);
			input = dis(gen);
		}

		// calcolo e stampa dei risultati
		if (input == 1) break;
		result = CPU(input);
		result.printf();
	}

	argc = NotAssigned;
	ret;
}

// programma per il debug
static void Loop(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input),
	bool select
)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	wstring n_{ to_wstring(GlobalMax) }, Input, txt;
	NumberDataTensor data;
	ptrdiff_t LowerBound, UpperBound, datalenght;
	bool Return;

	// input estremi
	wcout << L"debug::\n\n";
	SetConsoleTextAttribute(hConsole, 14);
	wcout << message << '\n';
	SetDebug(message, argc, Return, LowerBound, UpperBound, datalenght);
	if (Return) ret;

	// input instruzioni
	wstring instr;
	if (select) {
		PRINTN = false;
		items = { 0, 0, 0, 0 };
		SetConsoleTextAttribute(hConsole, 9);
		wcout << L"Inserisci la stringa di istruzioni, il tipo è $_/_ #_/_\n";
		wcout << L"per indicare i rapporti somma cifre con numero";
		wcout << L" e prodotto cifre con numero\n";
		ResetAttribute();

		bool exit{ false };
		do {
			wcout << L"\nInserire la stringa\n";
			instr = GetLine(Expressions);
			if (instr == L".") {
				argc = Random;
				ret;
			}

			// rimozione spazi
			for (ptrdiff_t i = instr.size() - 1; i >= 0; --i)
				if (instr.at(i) == L' ' or instr.at(i) == L'\t') instr.erase(i, 1);

			// prima suddivisione
			wstring sum_instr{ instr }, prod_instr{ instr };
			int posP{}, posS{};
			if (instr.empty()) {
				items = { 0, 0, 0, 0 };
				break;
			}
			posS = instr.find(L'$');
			posP = instr.find(L'#');
			if (posS == wstring::npos) sum_instr.clear();
			if (posP == wstring::npos) prod_instr.clear();
			if (sum_instr.empty()) prod_instr.erase(0, posP + 1);
			else if (prod_instr.empty()) sum_instr.erase(0, posS + 1);
			else if (posS < posP) {
				prod_instr.erase(0, posP + 1);
				sum_instr.erase(posP);
				sum_instr.erase(0, posS + 1);
			}
			else {
				sum_instr.erase(0, posS + 1);
				prod_instr.erase(posS);
				prod_instr.erase(0, posP + 1);
			}

			// // seconde suddivisioni
			int pos_p{}, pos_s{};
			if (!sum_instr.empty()) pos_s = sum_instr.find(L'/');
			if (!prod_instr.empty()) pos_p = prod_instr.find(L'/');
			if (pos_s == wstring::npos or pos_p == wstring::npos) continue;

			wstring np, dp, ns, ds;
			bool Continue{ false };
			if (!prod_instr.empty()) {
				np = prod_instr;
				dp = prod_instr;
				np.erase(pos_p);
				dp.erase(0, pos_p + 1);
				for (const auto& c : np) if (!isdigit(c)) Continue = true;
				for (const auto& c : dp) if (!isdigit(c)) Continue = true;
				if (Continue) continue;
				items.digitProductRatioNum = stoi(np);
				items.digitProductRatioDen = stoi(dp);
				exit = true;
			}

			if (!sum_instr.empty()) {
				ns = sum_instr;
				ds = sum_instr;
				ns.erase(pos_s);
				ds.erase(0, pos_s + 1);
				for (const auto& c : ns) if (!isdigit(c)) Continue = true;
				for (const auto& c : ds) if (!isdigit(c)) Continue = true;
				if (Continue) continue;
				items.digitSumRatioNum = stoi(ns);
				items.digitSumRatioDen = stoi(ds);
				exit = true;
			}
			// //

			if (!exit) wcout << L'\a';
		} while (!exit);
	}

	// calcolo e parallelizzazione
	system("cls");
	_GetCursorPos();
	const int Barwidth{ csbi.dwSize.X - 11 };
	HIDECURSOR;

	if (datalenght >= 1'000) {
		int iter{};
		atomic<long double> Progress{};
		DECLARE_TIME_POINT(begin);
		parallel_for(ptrdiff_t(LowerBound), UpperBound, 
			[&](ptrdiff_t set) {

				auto data_element{ CPU(set) };
				mtx.lock();
				data << data_element;
				if (iter % 200 == 0) {

					// stampa della barra di avanzamento
					DECLARE_TIME_POINT(stop);
					SetConsoleTextAttribute(hConsole, 112);
					Progress = (long double)data.size() / datalenght;
					ProgressBar(Progress, Barwidth);

					// calcolo del tempo rimanente
					
					int time = 1'000 *
						static_cast<double>(stop.QuadPart - begin.QuadPart)
						/ (ProgramFrequency.QuadPart);
					ResetAttribute();
					long double time_rem{ (time / Progress) * (1 - Progress) };
					long double time_seconds{ (long double)time_rem / 1'000 };

					// calcolo cifre decimali
					wostringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					wcout << L"\nTempo rimanente: " << stream.str();
					wcout << L" [secondi] ";
				}

				iter++;
				mtx.unlock();
			}
		);
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		wcout << wstring(Barwidth + 11, L'\\') << L'\n';

		// multithreading
		thread t1([&data]() {
			data.HeapSort();
			lock_guard<mutex> lock(mtx);
			IsDone = true;
			cv.notify_one();
			}
		);
		thread t2(CS_CenterPrinter);
		if (t2.joinable()) t2.join();
		if (t1.joinable()) t1.join();
		system("cls");

		// stampa risultati
		SetConsoleCursorInfo(hConsole, &cursor);
		data.printf();
		DECLARE_TIME_POINT(end);
		wcout << L"\nTempo di calcolo = ";
		wcout << 1'000 * static_cast<double>(end.QuadPart - begin.QuadPart)
			/ (ProgramFrequency.QuadPart);
		wcout << L"[ms]\n\n";
	}

	// caso con intervallo di dimensioni minori
	else {
		SetConsoleCursorInfo(hConsole, &cursor);
		DECLARE_TIME_POINT(begin);
		for (ptrdiff_t set = LowerBound; set < UpperBound; ++set)
			data << NumberData{ CPU(set) };
		data.printf();
		wcout << L"\nTempo di calcolo = ";
		DECLARE_TIME_POINT(end);
		wcout << 1'000 * static_cast<double>(end.QuadPart - begin.QuadPart)
			/ (ProgramFrequency.QuadPart);
		wcout << L"[ms]\n\n\n";
	}

	// termine
	PRINTN = true;
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	wcout << L"Premi un tasto per continuare\t\t";
	argc = _getch() == L'.' ? Random : NotAssigned;
	ret;
}

// programma per risolvere sistemi non lineari oppure parametrici lineari
static void SystemSolverGeneral(switchcase& argc)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));
	SetConsoleTextAttribute(hConsole, 14);

	// istruzioni
	wcout << L"Il PROGRAMMA risolve i sistemi in generale\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"Premere CTRL + ALT per aggiungere una frazione algebrica\n";
	wcout << L"Premere SHIFT + INVIO per aggiungere una nuova equazione\n";
	wcout << L"Premere INVIO per confermare\n\n";
	wcout << L"Per attivare gli esponenti in forma di apice ";
	wcout << L"scrivere noboolalpha\n";
	wcout << L"Per disattivare gli esponenti sottoforma di apice ";
	wcout << L"scrivere boolalpha\n";
	ResetAttribute();

	bool startover{ true };
	tensor<wstring> VariablesDisposition;
	tensor<Fraction<>> Fractions;
	for (;;)
	{
		while (GetAsyncKeyState(VK_SHIFT) & 0x8000 or
			GetAsyncKeyState(VK_RETURN) & 0x8000);

		// input equazioni
		if (!RunMonitor) goto RETURN;
		if (startover) {
			Variables = L"x";
			wcout << L"\nInserisci un sistema di equazioni\n\n";
		}
		startover = false;
		wstring err;
		int data;
		Fraction<> it{ GetFractionAdvanced(err, data) };
		VariablesDisposition << Variables;

		// messaggi di boolalpha
		if ((data | CHANGEDVALUE) != data and data > 0)
			wcout << (data % 2 ? L"boolalpha\n" : L"noboolalpha\n");

		// messaggio di errore
		if (it == Fraction<>{} and !err.empty()) {

			// uscita
			argc = ConvertWStringToEnum(err);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(err.c_str());
				goto RETURN;
			}

			// termine programma
			if (err == L"_") {
				argc = Random;
				goto RETURN;
			}

			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"\n\n" << err << L"!!\n";
			ResetAttribute();

			Fractions.clear();
			startover = true;
			continue;
		}

		// ultima operazione di input
		Fractions << it;
		if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) and Fractions < 5) continue;
		bool Continue{ false };

		// riempimento buchi nelle disposizioni
		wstring complete;
		for (auto& disp : VariablesDisposition) for (const auto& ch : disp)
			if (complete.find(ch) == wstring::npos) complete += ch;
		for (auto& disp : VariablesDisposition) for (const auto& ch : complete)
			if (disp.find(ch) == wstring::npos) disp += ch;
		
		// allocazione di memoria in più
		for (auto& fraction : Fractions) {
			for (auto& fact : fraction.num) for (auto& mon : fact)
				mon.exp(complete.size());
			for (auto& fact : fraction.den) for (auto& mon : fact)
				mon.exp(complete.size());
		}

		// ridisposizione
		tensor<int> ExpNull(complete.size(), 0);
		for (size_t i = 0; i < 2 * Fractions.size(); ++i) {
			if (VariablesDisposition[i / 2] == complete) continue;

			// preparazione polinomi
			auto& old = i % 2 ? Fractions[i / 2].den : Fractions[i / 2].num;
			polynomial<> correct(old.size());
			for (size_t j = 0; j < correct; ++j) for (const auto& mono : old[j])
				correct[j] << monomial<>{ mono.coefficient, ExpNull };

			// correzione esponenti
			for (size_t j = 0; j < VariablesDisposition[i / 2].size(); ++j) {
				auto pos{ complete.find(VariablesDisposition[i / 2].at(j)) };
				if (pos == wstring::npos) continue;
				for (size_t k = 0; k < correct; ++k)
					for (size_t l = 0; l < correct[k]; ++l)
						correct[k][l].exp[pos] = old[k][l].exp[j];
			}

			old = correct;
		}

		// numero di variabili eccessivo
		VariablesDisposition.clear();
		if (Variables.size() > Fractions.size() + 1) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"Troppe variabili!!\a\n";
			ResetAttribute();

			Fractions.clear();
			startover = true;
			continue;
		}

		// traduzione secondaria
		polynomial<> equations;
		for (const auto& eq : Fractions) equations << eq.num[0];
		for (auto& equation : equations) for (auto& mono : equation)
			mono.exp(Variables.size(), 0);

		// una sola equazione in una variabile
		if (Variables.size() == Fractions and Fractions == 1) {

			// estrazione radici
			charVariable = Variables.at(0);
			Variables = L"x";
			auto solutions{ RootExtractor(equations) };
			Variables = wstring(1, charVariable);
			
			// rimozione doppi
			for (ptrdiff_t i = solutions.size() - 1; i >= 0; --i)
				for (ptrdiff_t j = i - 1; j >= 0; --j)
					if (solutions[i] == solutions[j])
						solutions.erase(solutions.begin() + i);

			// rimozione delle singolarità
			for (ptrdiff_t i = solutions.size() - 1; i >= 0; --i)
				for (const auto& fract : Fractions)
					if (fabs(fract.den[0]({ solutions[i] })) < 1e-05)
						solutions.erase(solutions.begin() + i);

			// output
			SetConsoleTextAttribute(hConsole, 11);
			wcout << L"Le soluzioni sono " << solutions << L'\n';
			ResetAttribute();

			Fractions.clear();
			equations.clear();
			startover = true;
			continue;
		}

		// numero di variabili minore-uguale al numero di equazioni
		if (Variables.size() <= equations) {
			
			// calcolo soluzioni
			auto solutions{ SystemSolver(tensor<factor<>>(
				equations.begin(),
				equations.begin() + Variables.size()
			)) };
			SetConsoleTextAttribute(hConsole, 11);

			// sistema indeterminato
			if (isnan(solutions[0][0])) {
				wcout << L"Il sistema è indeterminato\a\n";
				ResetAttribute();

				Fractions.clear();
				equations.clear();
				startover = true;
				continue;
			}
			
			// rimozione delle singolarità
			for (ptrdiff_t i = solutions.size() - 1; i >= 0; --i) {
				if (solutions[i].empty()) continue;

				for (const auto& fract : Fractions)
					if (fract.den[0](solutions[i]) < 1e-05)
						solutions.erase(solutions.begin() + i);
			}

			// errore
			if (solutions.empty()) {
				wcout << L"Non sono state trovate soluzioni utilizzando";
				wcout << L" i metodi standard\n";
				ResetAttribute();

				Fractions.clear();
				equations.clear();
				startover = true;
				continue;
			}

			// sistema impossibile
			if (solutions[0].empty()) {
				wcout << L"Il sistema è impossibile\a\n";
				ResetAttribute();

				Fractions.clear();
				equations.clear();
				startover = true;
				continue;
			}

			// selezione
			for (ptrdiff_t i = solutions.size() - 1; i >= 0; --i)
				for (size_t j = Variables.size(); j < equations; ++j)
					if (fabs(equations[j](solutions[i])) > 1e-05)
					{
						solutions.erase(solutions.begin() + i);
						break;
					}
			
			// output soluzioni
			if (solutions.empty()) {
				wcout << L"Il sistema è impossibile\a\n";
				ResetAttribute();

				Fractions.clear();
				equations.clear();
				startover = true;
				continue;
			}
			wcout << L"Soluzioni del sistema: \n";
			for (const auto& sol : solutions) {
				wcout << L"{\n";
				for (size_t i = 0; i < Variables.size(); ++i) {
					wcout << L"    " << Variables.at(i);
					wcout << L" = " << sol[i] << L'\n';
				}
				wcout << L"}\n";
			}
			ResetAttribute();

			Fractions.clear();
			equations.clear();
			startover = true;
			continue;
		}
		// sistema parametrico

		// priorità delle variabili
		int pIndex{ -1 };
		wstring VarOrder;
		tensor<int> VariablePos;
		const wstring VariablePriority{ L"xyzuvtsabcd" };
		for (const auto& var : VariablePriority) {
			auto pos{ Variables.find(var) };
			if (pos != wstring::npos) {
				VarOrder += var;
				VariablePos << pos;
			}
		}
		ptrdiff_t ParameterIndex = VarOrder.size() - 1;

		// controllo linearità e calcolo parametro
		for (; ParameterIndex >= 0; --ParameterIndex) {
			for (const auto& eq : equations) {
				for (size_t i = 0; i < eq; ++i) {
					int deg{};
					for (size_t j = 0; j < VarOrder.size(); ++j) {
						if (j == ParameterIndex) continue;
						deg += eq[i].exp[VariablePos[j]];
					}
					if (deg > 1) {
						Continue = true;
						break;
					}
				}
				if (Continue) break;
			}
			if (Continue) {
				Continue = false;
				continue;
			}
			pIndex = VariablePos[ParameterIndex];
			charVariable = Variables.at(pIndex);
			break;
		}
		if (pIndex < 0) {

			Fractions.clear();
			equations.clear();
			startover = true;
			continue;
		}

		// calcolo termini noti
		size_t Vsize{ Variables.size() }, I{};
		tensor<int> null(Vsize, 0);
		tensor<factor<>> KnownTerms(Vsize);
		for (size_t i = 0; i < equations;) {
			if (I == pIndex) {
				I++;
				continue;
			}
			for (size_t j = 0; j < equations[i]; ++j) {
				auto exps{ equations[i][j].exp };
				exps[pIndex] = 0;
				if (exps == null) {
					auto mon{ equations[i][j] };
					mon.coefficient *= -1;
					KnownTerms[I] << mon;
				}
			}
			i++;
			I++;
		}

		// calcolo coefficienti interni
		I = 0;
		bool Break{ false };
		Matrix<factor<>> system(Vsize, tensor<factor<>>(Vsize));
		for (size_t i = 0; i < equations;) {
			for (size_t j = 0; j < equations[i]; ++j) {
				for (size_t k = 0; k < Vsize; ++k) {
					if (I == pIndex) {
						I++;
						Break = true;
						break;
					}
					if (k == pIndex) continue;

					auto mon{ equations[i][j] };
					mon.exp[k] = 0;
					if (equations[i][j].exp[k] != 0) system[k][I] << mon;
				}
				if (Break) break;
			}
			if (Break) {
				Break = false;
				continue;
			}
			I++;
			i++;
		}

		// aggiustamento dimensione
		KnownTerms.erase(KnownTerms.begin() + pIndex);
		system.erase(system.begin() + pIndex);
		for (auto& eq : system) eq.erase(eq.begin() + pIndex);
		tensor<Fraction<>> solve;
		tensor<polynomial<>> dets;

		// calcolo soluzione
		auto D{ DecompPolynomial(usefree, system.det()) };
		auto ProblematicPoints{ RootExtractor(D) };
		tensor<long double> Zeros;
		for (size_t i = 0; i < Vsize - 1; ++i) {
			
			// calcolo soluzioni del sistema lineare
			auto mx{ system };
			mx[i] = KnownTerms;
			dets << DecompPolynomial(usefree, mx.det());
			
			// calcolo zeri
			auto NewZeros{ RootExtractor(dets.last()) };
			for (const auto& zero : NewZeros) {
				
				Continue = false;
				for (const auto& OtherZero : Zeros)
					if (fabs(OtherZero - zero) < 1e-05)
					{
						Continue = true;
						break;
					}

				if (Continue) continue;
				Zeros << zero;
			}
		}
		if (D.empty()) {
			SetConsoleTextAttribute(hConsole, 11);
			
			// sistema indeterminato
			if (dets == tensor<polynomial<>>(dets.size())) {
				wcout << L"Il sistema è indeterminato\a\n";
				ResetAttribute();

				Fractions.clear();
				equations.clear();
				startover = true;
				continue;
			}

			// sistema impossibile
			wcout << L"Il sistema è impossibile\a\n";
			ResetAttribute();
			Fractions.clear();
			equations.clear();
			startover = true;
			continue;
		}
		for (const auto& det : dets) solve << Fraction<>{ det, D };
		wcout << L'\n';

		// output
		int line{};
		bool skipped{ false };
		for (size_t i = 0; i < Vsize; ++i) {
			if (i == pIndex) {
				skipped = true;
				continue;
			}

			// scomposizione numeratore e denominatore
			int ncoeff{ 1 }, dcoeff{ 1 };
			auto& resolution{ solve[i - skipped] };
			Simplify(resolution, ncoeff, dcoeff);
			auto NScomp{ To1V(resolution.num) };
			auto DScomp{ To1V(resolution.den) };
			NScomp.close();
			DScomp.close();
			for (size_t j = 0; j < NScomp; ++j) NScomp[j].sort();
			for (size_t j = 0; j < DScomp; ++j) DScomp[j].sort();

			// output
			SetConsoleTextAttribute(hConsole, 11);
			wcout << Variables.at(i) << L" = ";
			PrintFractionaryResult(
				ncoeff,
				dcoeff,
				line,
				resolution,
				NScomp,
				DScomp,
				resolution.num != ToXV(NScomp) or resolution.den != ToXV(DScomp)
			);
			wcout << L"\n\n";

			if (i != Vsize - 1) wcout << L'\n';
		}
		
		// output punti problematici
		bool starting{ true };
		SetConsoleTextAttribute(hConsole, 6);
		for (const auto& p : ProblematicPoints) {

			Continue = false;
			for (const auto& zero : Zeros) if (fabs(p - zero) < 1e-05) {

				// indeterminato
				if (starting) {
					starting = false;
					wcout << L'\n';
				}
				wcout << L"SE " << charVariable << L" = " << Handler(to_wstring(p));
				wcout << L" ALLORA il sistema è indeterminato\n\n";

				Continue = true;
			}
			if (Continue) continue;

			// impossibile
			if (starting) {
				starting = false;
				wcout << L'\n';
			}
			wcout << L"SE " << charVariable << L" = " << Handler(to_wstring(p));
			wcout << L" ALLORA il sistema è impossibile\n\n";
		}

		ResetAttribute();
		Fractions.clear();
		equations.clear();
		startover = true;
	}

	// invio del segnale per terminare i thread
	argc = NotAssigned;
RETURN:
	{
		lock_guard<mutex> lk(MonitorMTX);
		RunMonitor = false;
	}
	MonitorCV.notify_all();
}

// programma per scomporre i polinomi
template<typename Type = wstring>
static polynomial<> DecompPolynomial(switchcase& argc, Type Polynomial)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));
	SetConsoleTextAttribute(hConsole, 14);

	// variabili
	wstring pol;
	polynomial<> HT;
	bool empty{ true }, Xout{ false }, input{ Polynomial == Type() };
	const constexpr bool CheckSafe{ is_same_v<Type, wstring> };

	// istruzioni
	if constexpr (CheckSafe) if (input)
	{
		wcout << L"Il PROGRAMMA scompone i polinomi e ne disegna il grafico\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		wcout << L"Per attivare gli esponenti in forma di apice ";
		wcout << L"scrivere noboolalpha\n";
		wcout << L"Per disattivare gli esponenti sottoforma di apice ";
		wcout << L"scrivere boolalpha\n\n";
		wcout << L"Per disegnare il grafico aggiungere '\\' all'inizio\n";
		wcout << L"è possibile eseguire addizioni, sottrazioni, moltiplicazioni\n";
		wcout << L"e potenze con polinomi molto grandi\n\n";
		wcout << L"Nel grafico è possibile premere il tasto X per eliminare\n";
		wcout << L"la funzione oppure il tasto D per calcolare la sua derivata\n\n";
		SetConsoleTextAttribute(hConsole, 4);
		wcout << L"Attenzione! il programma deduce i polinomi con le parentesi,\n";
		wcout << L"Per calcolarne il valore aggiungere alla fine +1-1\n";
		wcout << L"Per le potenze di numeri includere il numero tra parentesi\n\n";
		ResetAttribute();
	}

	do {
		bool draw{ false };
		if (!RunMonitor) goto RETURN;
		if constexpr (CheckSafe) if (input)
		{
			empty = true;
			Xout = false;
			wstring Message;
			do {
				_GetCursorPos();
				draw = false;
				bool wrong{ true };

				// input
				ResetAttribute();
				wcout << L"Inserisci un polinomio in una o più variabili";
				wcout << L" (0 = fine input)\n";
				do {
					Polynomial = GetLine(Polynomials);
					wcout << L'\n';
				} while (Polynomial.empty());
				if (Polynomial.at(0) == L'\\') {
					Polynomial.erase(0, 1);
					draw = true;
				}

				// caso di ridirezionamento
				if (Polynomial == L".") {
					argc = Random;
					HT = {};
					goto RETURN;
				}
				argc = ConvertWStringToEnum(Polynomial);
				ReassigneEnum(argc);
				if (argc != NotAssigned) {
					system("cls");
					SetConsoleTitle(Polynomial.c_str());
					HT = {};
					goto RETURN;
				}

				// esponenti con gli apici
				if (Polynomial == L"noboolalpha")
				{
					BOOLALPHA = true;
					wrong = false;
				}
				if (Polynomial == L"boolalpha")
				{
					BOOLALPHA = false;
					wrong = false;
				}
				if (!wrong) wcout << Polynomial << L'\n';

				// rimozione spazi
				for (ptrdiff_t i = Polynomial.size() - 1; i >= 0; --i)
					if (Polynomial.at(i) == L' ' or Polynomial.at(i) == L'\t')
						Polynomial.erase(i, 1);

				// controllo
				Message = Polynomial.empty() ? L"il polinomio è vuoto"
					: PolynomialSyntaxDirector(Polynomial);
				if (!Message.empty() and wrong) {
					SetConsoleTextAttribute(hConsole, 12);
					wcout << Message << L"!!\n\a";
					ResetAttribute();
				}

			} while (!Message.empty());
			if (Polynomial == L"0") break;
		}

		polynomial<> BackT, Back_T{ HT };
		polynomial<big> bigHT;
		tensor<int> null, Null;
		ptrdiff_t Coeff{ 1 };
		int size;
		if constexpr (CheckSafe)
		{

			// traduzione dell'input utente
			bigHT = GetMonomialsAssister(Polynomial);

			// semplificazione numeratore denominatore
			tensor<big> ListOfCoefficients;
			for (auto fact : bigHT) for (auto mon : fact) if (mon.exp[0] >= 0)
				ListOfCoefficients << mon.coefficient;
			big G{ Gcd(ListOfCoefficients + tensor<big>{ LCM }).fabs() };
			for (auto& fact : bigHT) for (auto& mon : fact) if (mon.exp[0] >= 0)
				mon.coefficient /= G;
			LCM /= G;

			if (input) charVariable = Variables.at(0);
			HT = FromBigToDefault(bigHT);

			// se il polinomio troppo grande
			if (HT >= 1) if (HT[0] >= 1) if (HT[0][0].exp[0] == -2) {
				if (input) {
					SetConsoleTextAttribute(hConsole, 2);
					wcout << L"Questo è il polinomio: " << bigHT << L'\n';
					SetConsoleTextAttribute(hConsole, 64);
					wcout << L"Il polinomio è troppo grande.";
					ResetAttribute();
					wcout << L'\n';
					continue;
				}
				else ret {};
			}

			// se sono presenti dei coefficienti complessi
			if (Variables.find(L'i') != wstring::npos) {
				if (!input) ret {};

				SetConsoleTextAttribute(hConsole, 2);
				wcout << L"Questo è il polinomio: ";
				wcout << PolynomialMultiply<big>(bigHT).str() << L'\n';

				SetConsoleTextAttribute(hConsole, 64);
				wcout << L"Il polinomio contiene dei numeri complessi.";
				ResetAttribute();
				wcout << L'\n';
				continue;
			}
		}

		// separazione dei template
		else if constexpr (is_same_v<Type, factor<>>) HT = { Polynomial };
		else if constexpr (is_same_v<Type, polynomial<>>) HT = Polynomial;
		wstring _polynomial;
		if constexpr (CheckSafe) _polynomial = Polynomial;

		// risultato della somma
		Null(Variables.size(), 0);
		null(Variables.size(), 0);
		null[0] = -1;
		for (const auto& poly_data : HT) if (poly_data.empty()) {
			_polynomial = L"0";
			break;
		}
		if (HT.empty()) _polynomial = L"0";
		else if (_polynomial != L"0") _polynomial = HT.str();
		if (input) {
			SetConsoleTextAttribute(hConsole, 2);
			if (_polynomial.empty()) _polynomial = L"0";
			wcout << L"Questo è il polinomio: " << _polynomial << L'\n';
		}

		// caso nullo
		size = HT.size();
		if (_polynomial == L"0") {
			if (input) {
				ResetAttribute();
				wcout << "Il polinomio non è scomponibile\n";
			}
			goto EndOfDecomposition;
		}

		// raccoglimento totale
		Back_T = HT;
		HT.clear(); 
		for (const auto& polydata : Back_T) HT += Total(polydata);
		for (ptrdiff_t i = HT.size() - 1; i >= 0; --i)
			if (HT[i] == 1) if (HT[i][0].exp == Null)
			{
				Coeff *= HT[i][0].coefficient;
				HT.erase(HT.begin() + i);
				if (Coeff >= 2'147'483'647 or Coeff <= -2'147'483'647) {
					if (!input) ret {};

					SetConsoleTextAttribute(hConsole, 2);
					wcout << L"Questo è il polinomio: " << bigHT << L'\n';
					SetConsoleTextAttribute(hConsole, 64);
					wcout << L"Il polinomio è troppo grande.";

					ResetAttribute();
					wcout << L'\n';
					continue;
				}
			}

		// aggiunta del coefficiente corretto
		if (HT.empty()) HT = polynomial<>{ { {
			(long double)Coeff, Null
		} } };
		else if (abs(Coeff) != 1) HT >> factor<>{ {
			(long double)Coeff, Null
		} };
		else if (Coeff == -1) for (auto& mon : HT[0]) mon.coefficient *= -1;

		// output raccoglimento totale
		HT.close();
		_polynomial = HT.str();
		if (HT != size and CheckSafe and input) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"Raccoglimento totale: " << _polynomial << L'\n';
			empty = false;
		}

		do {

			// raccoglimento parziale
			Back_T = HT;
			pol = _polynomial;
			auto polydata{ HT.last() };
			polydata.SortByDegree();
			HT--;
			HT += Partial(polydata);
			HT.close();
			_polynomial = HT.str();
			if (Back_T % HT and !Xout and CheckSafe and input) {
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"Raccoglimento parziale: " << _polynomial << L'\n';
				empty = false;
			}

			// potenza di binomio
			HT.close();
			Back_T = HT;
			HT.clear();
			for (const auto& a : Back_T) HT += Binomial(a);
			HT.close();
			_polynomial = HT.str();
			if (Back_T % HT and !Xout and CheckSafe and input) {
				SetConsoleTextAttribute(hConsole, 3);
				wcout << L"Potenza di binomio scomposta: ";
				wcout << _polynomial << L'\n';
				empty = false;
			}

			// trinomio speciale
			Back_T = HT;
			HT.clear();
			for (const auto& a : Back_T) HT += Trinomial(a);
			HT.close();
			_polynomial = HT.str();
			if (Back_T % HT and !Xout and CheckSafe and input) {
				SetConsoleTextAttribute(hConsole, 9);
				wcout << L"Trinomio speciale scomposto: ";
				wcout << _polynomial << L'\n';
				empty = false;
			}

			// differenza di quadrati
			Back_T = HT;
			HT.clear();
			int extend{ 1 };
			for (const auto& a : Back_T) {
				if (a[0].exp[0] < 0) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = SquareDifference(a);
				for (const auto& b : BackT) {
					if (extend > 1) HT << factor<>{ { (long double)extend, null } };
					HT << b;
				}
				extend = 1;
			}
			HT.close();
			_polynomial = HT.str();

			// somma per differenza
			if (Back_T % HT and !Xout and CheckSafe and input) {
				SetConsoleTextAttribute(hConsole, 5);
				wcout << L"Differenza di quadrati scomposta: ";
				wcout << _polynomial << L'\n';
				empty = false;
			}

			// scomposizione con ruffini
			for (auto& poldata : HT) poldata.SortByExponents();
			pol = HT.str();
			Back_T = HT;
			HT.clear();
			extend = 1;
			for (const auto& a : Back_T) {
				if (a[0].exp[0] < 0) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = Ruffini(a);
				if (!a.empty() and BackT.empty()) {
					Xout = true;
					break;
				}
				for (const auto& b : BackT) {
					if (extend > 1) HT << factor<>{ { (long double)extend, null } };
					HT << b;
				}
				extend = 1;
			}

			// ruffini
			HT.close();
			_polynomial = HT.str();
			if (Back_T % HT and !Xout and CheckSafe and input) {
				SetConsoleTextAttribute(hConsole, 6);
				wcout << L"Applicazione della regola di ruffini: ";
				wcout << _polynomial << L'\n';
				empty = false;
			}
		} while (_polynomial != pol);

		// completamento del quadrato
		Back_T = HT;
		HT.clear();
		for (const auto& a : Back_T) HT += CompleteTheSquare(a);
		HT.close();
		_polynomial = HT.str();
		if (Back_T % HT and !Xout and CheckSafe and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"Completamento del quadrato: " << _polynomial;
			ResetAttribute();
			wcout << L'\n';
			empty = false;
		}

		// quadrato del trinomio
		Back_T = HT;
		HT.clear();
		for (const auto& a : Back_T) HT += TrinomialSquare(a);
		
		HT.close();
		_polynomial = HT.str();
		if (Back_T % HT and !Xout and CheckSafe and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"Quadrato di trinomio scomposto: " << _polynomial;
			ResetAttribute();
			wcout << L'\n';
			empty = false;
		}

		// caso vuoto
		if (empty and !Xout and CheckSafe and input) {
			ResetAttribute();
			wcout << L"Il polinomio non è scomponibile con i metodi standard\n";
		}

		// caso impossibile
		if (Xout and CheckSafe and input) {
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"\aX_OUT_OF_RANGE";
			ResetAttribute();
			wcout << L'\n';
		}

		// grafico del polinomio
		if (CheckSafe and input and draw) switch (Variables.size()) {
		case 1:
			if (CreateGraph(
				{ { PolynomialMultiply(HT) }, { { { 1, Null } } } }
			)) while (CreateGraph());
			break;
		case 2: Project3DGraph(
			{ { PolynomialMultiply(HT) }, { { { 1, { Null } } } } }
			 );
			break;
		}

	EndOfDecomposition: if (!(CheckSafe and input)) break;

	} while (CheckSafe and input);

	// invio del segnale per terminare i thread
	argc = NotAssigned;
RETURN:
	if (CheckSafe and input) {
		{
			lock_guard<mutex> lk(MonitorMTX);
			RunMonitor = false;
		}
		MonitorCV.notify_all();
	}

	ret HT;
}

// programma per scomporre le frazioni algebriche
static void DecompFraction(switchcase& argc)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// istruzioni
	SetConsoleTextAttribute(hConsole, 14);
	wcout << L"Il PROGRAMMA scompone, semplifica, esegue lo studio del segno\n";
	wcout << L"e disegna il grafico delle frazioni algebriche\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"Nel grafico è possibile premere il tasto X per eliminare\n";
	wcout << L"la funzione oppure il tasto D per calcolare la sua derivata\n\n";
	wcout << L"Per attivare gli esponenti in forma di apice ";
	wcout << L"scrivere noboolalpha\n";
	wcout << L"Per disattivare gli esponenti sottoforma di apice ";
	wcout << L"scrivere boolalpha\n";
	wcout << L"Per disegnare il grafico aggiungere '\\' all'inizio\n";
	ResetAttribute();

	for (;;)
	{
	insert:
		bool skip{ false }, draw{ false };
		while (GetAsyncKeyState(VK_SHIFT) & 0x8000 or
			GetAsyncKeyState(VK_RETURN) & 0x8000);

		// input frazione
		if (!RunMonitor) goto RETURN;
		ResetAttribute();
		Variables = L"x";
		wcout << L"\nInserisci una frazione algebrica (0 = fine input)\n\n";
		wstring err;
		int data;
		Fraction<> it{ GetFractionAdvanced(err, data) };

		// controllo dati aggiuntivi
		if ((data | CHANGEDVALUE) == data)
			wcout << (data % 2 ? L"boolalpha\n" : L"noboolalpha\n");
		if ((data | GRAPHED) == data) draw = true;

		// messaggio di errore
		if (it == Fraction<>{} and !err.empty()) {

			// uscita
			argc = ConvertWStringToEnum(err);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(err.c_str());
				goto RETURN;
			}

			// termine programma
			if (err == L"_") {
				argc = Random;
				goto RETURN;
			}

			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"\n\n" << err << L"!!\n";
			ResetAttribute();
			continue;
		}

		// uscita
		if (!it.num.empty()) if (!it.num[0].empty())
			if (it.num[0][0].coefficient == 0) break;

		// scomposizione polinomi
		CORRECTION_RATIO = 1;
		Fraction<> fraction;
		fraction.num = DecompPolynomial(usefree, it.num);

		// denominatori aggiuntivi
		big DenMultiplier = LCM;
		auto savx{ Variables };
		fraction.den = DecompPolynomial(usefree, it.den);
		big NumMultiplier = LCM, GCD{ Gcd(NumMultiplier, DenMultiplier) };
		NumMultiplier /= GCD;
		DenMultiplier /= GCD;
		auto nummultiplier{ NumMultiplier.Number<long double>() };
		auto denmultiplier{ DenMultiplier.Number<long double>() };
		
		if (!(fraction.num and fraction.den) or
			isnan(nummultiplier) or isnan(denmultiplier))
		{
			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"Input overflow: prova a inserire valori più piccoli\n";
			wcout << L" e non dei numeri complessi!!\a";
			ResetAttribute();
			wcout << L'\n';
			goto insert;
		}

		// aggiunta di spazio nella memoria
		auto oldV{ Variables };
		for (const auto& ch : Variables) if (savx.find(ch) == wstring::npos)
			savx += ch;
		Variables = savx;
		for (auto& fac : fraction.num) for (auto& mon : fac)
			mon.exp(Variables.size(), 0);
		for (auto& fac : fraction.den) for (auto& mon : fac)
			mon.exp(Variables.size(), 0);
		auto temp{ fraction.den };
		for (size_t i = 0; i < fraction.den; ++i)
			for (size_t j = 0; j < temp[i]; ++j) if (temp[i][j].exp[0] >= 0)
				for (size_t k = 0; k < Variables.size(); ++k)
				{
					auto pos{ oldV.find(Variables.at(k)) };
					temp[i][j].exp[k] = pos != wstring::npos ?
						fraction.den[i][j].exp[pos] : 0;
				}
		fraction.den = temp;
		
		// backup
		auto Backup{ fraction };
		int NCOEFF{ 1 }, DCOEFF{ 1 };
		tensor<int> null(Variables.size(), 0);

		// semplificazione fattori
		Simplify(fraction, NCOEFF, DCOEFF);
		NCOEFF *= nummultiplier;
		DCOEFF *= denmultiplier;
		LCM = 1;

		// aggiornamento dati globali
		auto test{ fraction.num };
		if (!(fraction.num or fraction.den)) charVariable = L'x';
		else if (fraction.num.empty()) test = fraction.den;
		if (fraction.num or fraction.den)
			for (size_t i = 0; i < Variables.size(); ++i)
				if (test[0][0].exp[i] != 0) charVariable = Variables.at(i);

		// correzione fattori
		auto NScomp{ To1V(fraction.num) };
		auto DScomp{ To1V(fraction.den) };
		NScomp.close();
		DScomp.close();
		for (size_t i = 0; i < NScomp; ++i) NScomp[i].sort();
		for (size_t i = 0; i < DScomp; ++i) DScomp[i].sort();

		if (DScomp <= 1) skip = true;
		if (!skip) for (auto a : DScomp) for (auto b : a)
			if (a != 1 and b.degree > 1) skip = true;

		// caso con più variabili
		bool IsAModifier{ false }, HasMoreVariables{ false };
		tensor<POLYNOMIAL<>> denominators;
		POLYNOMIAL<> complementaries;
		size_t index{}, size{};
		int Det{ 1 };
		Matrix<int> Matrix;
		tensor<int> results;
		tensor<double> roots;
		FACTOR<> Quotient;
		FACTOR<> Rest;
		if (fraction.num != ToXV(NScomp) or fraction.den != ToXV(DScomp)) {
			skip = true;
			HasMoreVariables = true;
			goto PrintStatement;
		}

		// calcolo denominatori
		if (!skip) for (size_t i = 0; i < DScomp; ++i) {
			if (DScomp[i][0].degree == -1) {
				IsAModifier = true;
				continue;
			}

			// caso con le potenze
			if (IsAModifier)
				for (ptrdiff_t j = DScomp[i - 1][0].coefficient; j > 0; --j)
				{
					denominators++;
					if (j > 1)
						denominators[index] << FACTOR<>{ { -1, (long double)j } };
					denominators[index] << DScomp[i];
					index++;
					complementaries << Complementary(DScomp, DScomp[i], j);
				}
			
			// caso con le potenze della variabile
			else if (DScomp[i] == 1)
				for (ptrdiff_t j = DScomp[i][0].degree; j > 0; --j)
				{
					denominators++;
					denominators[index] << FACTOR<>{ { (int)j, 1 } };
					index++;
					auto NewScomp{ DScomp };
					NewScomp.erase(NewScomp.begin() + i);
					NewScomp.insert(NewScomp.begin() + i, { { 1, 1 } });
					NewScomp.insert(NewScomp.begin() + i, {
						{ -1, (long double)DScomp[i][0].degree }
						});
					complementaries << Complementary(NewScomp, NewScomp[i + 1], j);
				}

			// caso senza potenze
			else {
				denominators++;
				denominators[index] << DScomp[i];
				index++;
				complementaries << Complementary(DScomp, DScomp[i], 1);
			}
			IsAModifier = false;
		}
		if (!skip) for (size_t i = 0; i < complementaries; ++i)
			complementaries[i].complete(complementaries.size());

		// inizializzazione matrice
		if (!skip) {
			size = complementaries.size();
			Matrix(size);
			for (size_t i = 0; i < complementaries; ++i)
				for (size_t j = 0; j < complementaries; ++j)
					Matrix[i] << complementaries[i][j].coefficient;
		}

		// calcolo determinanti
		if (!skip) {

			// divisione polinomi
			PolynomialDivide(
				V1converter(PolynomialMultiply, NScomp),
				V1converter(PolynomialMultiply, DScomp),
				Quotient,
				Rest
			);
			Rest.complete(complementaries.size() - 1);
			Rest.sort();

			for (const auto& R : Rest) results << R.coefficient;
			while (results.size() < complementaries.size()) results >> 0;
			Det = Matrix.det();
		}
		if (!skip) for (size_t i = 0; i < results; ++i) {
			::Matrix<int> MX{ Matrix };
			MX[i] = results;
			roots << (double)MX.det() / Det;
		}

		// eliminazione degli zeri
		for (ptrdiff_t i = denominators.size() - 1; i >= 0; --i) 
			if (roots[i] == 0) {
				denominators.erase(denominators.begin() + i);
				roots.erase(roots.begin() + i);
			}
		if (roots.empty()) skip = true;

	PrintStatement:

		// calcolo condizioni di esistenza
		SetConsoleTextAttribute(hConsole, 11);
		wcout << L"C.E.: ";
		SetConsoleTextAttribute(hConsole, 10);
		tensor<wstring> C_E_;
		bool HasBeenPrinted{ false };

		// push condizioni di esistenza
		COORD cursorPos;
		for (const auto& d : Backup.den) {
			auto Ctemp_{ EquationSolver(d) };
			for (const auto& i : Ctemp_) C_E_ << i;
		}
		for (ptrdiff_t i = C_E_.size() - 1; i >= 0; --i)
			for (ptrdiff_t j = i - 1; j >= 0; --j)
				if (C_E_[i] == C_E_[j]) C_E_.erase(C_E_.begin() + i);

		// output condizioni di esistenza
		for (auto I : C_E_) {
			wcout << Handler(I) << L"; ";
			HasBeenPrinted = true;
		}
		if (!HasBeenPrinted) wcout << L"\r      \r";
		_GetCursorPos();
		cursorPos = csbi.dwCursorPosition;
		if (!HasBeenPrinted) {
			cursorPos.X = 0;
			cursorPos.Y--;
			SetConsoleCursorPosition(hConsole, cursorPos);
		}
		else wcout << L'\n';

		// output del segno della frazione
		auto DiseqSol{
			DisequationSolutionPrinter(
				fraction.num, fraction.den, 15, NCOEFF < 0 or DCOEFF < 0
			)
		};
		if (!DiseqSol.empty()) wcout << L'\n' << DiseqSol << L'\n';

		// output frazioni
		SetConsoleTextAttribute(hConsole, 10);
		wcout << L"\nLa scomposizione è: ";
		SetConsoleTextAttribute(hConsole, 12);
		int lines{};
		PrintFractionaryResult(
			NCOEFF,
			DCOEFF,
			lines,
			fraction,
			NScomp,
			DScomp,
			HasMoreVariables,
			!skip,
			roots,
			denominators
		);

		// output polinomio di resto
		if (!skip) for (const auto& a : Quotient) {
			auto rest{ POLYNOMIAL<>{ { a } } };
			if (a.coefficient == 0) continue;

			// output normale
			if (integer(a.coefficient / CORRECTION_RATIO)) {
				rest[0][0].coefficient /= CORRECTION_RATIO;
				auto pol{ rest.str() };
				ElabExponents(pol);
				bool IsMinus{ false };

				// correzione segno
				if (pol.at(0) == L'-') {
					pol.erase(0, 1);
					IsMinus = true;
				}
				if (pol.size() >= 2) if (pol.at(0) == '(' and Last(pol) == ')')
				{
					pol.pop_back();
					pol.erase(0, 1);
				}
				if (pol.at(0) == L'-') {
					pol.erase(0, 1);
					IsMinus = true;
				}
				else if (pol.at(0) == L'+') pol.erase(0, 1);

				IsMinus ? wcout << L'-' : wcout << L'+';
				wcout << L' ' << pol << L' ';
				lines += 2 + pol.size();
			}

			// frazione
			else {

				// arretramento cursore
				_GetCursorPos();
				COORD dwCursorPos{ csbi.dwCursorPosition };
				dwCursorPos.Y--;
				SetConsoleCursorPosition(hConsole, dwCursorPos);

				// output frazione
				PrintFraction(
					1,
					1,
					lines,
					true,
					{ { { { a.coefficient, null } } }, { { { 1, null } } } }
				);

				// avanzamento cursore
				_GetCursorPos();
				dwCursorPos = csbi.dwCursorPosition;
				dwCursorPos.Y++;
				SetConsoleCursorPosition(hConsole, dwCursorPos);

				// output potenza della variabile
				wstring power;
				if (a.degree > 0) power += charVariable;
				if (a.degree > 1) {
					power += L'^' + to_wstring(a.degree);
					ElabExponents(power);
				}
				wcout << L' ' << power << L' ';
			}
		}
		wcout << L"\n\n";

		// grafico
		if (draw) switch (Variables.size()) {
		case 1:
			if (CreateGraph(Backup.extend())) while (CreateGraph());
			break;
		case 2: Project3DGraph(Backup.extend());
			break;
		}
	}

	argc = NotAssigned;
RETURN:
	// invio del segnale per terminare i thread
	{
		lock_guard<mutex> lk(MonitorMTX);
		RunMonitor = false;
	}
	MonitorCV.notify_all();
}

// programma per decomporre le matrici
static void DecompMatrices(switchcase& argc)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// istruzioni
	SetConsoleTextAttribute(hConsole, 14);
	wcout << L"Il PROGRAMMA scompone le matrici\n";
	wcout << L"e calcola determiante, autovalori e autovettori\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"Sono ammesse solo matrici quadrate da 2x2 a 7x7\n";
	wcout << L"Utilizza CTRL + ALT per inserire una matrice\n";
	wcout << L"Utilizza CTRL + ALT + BACKSPACE per azzerare la matrice\n";
	wcout << L"Premi r per copiare la penultima riga (azzera il determinante)\n";
	wcout << L"Premi z per riempire la matrice con numeri casuali\n\n";
	ResetAttribute();
	Matrix<> matrix, Mx;

	for (;;)
	{

		// input
		ResetAttribute();
		wcout << L"Inserisci una matrice\n\n";
		for (;;) {
			wstring err;
			if (matrix.input(err)) break;
			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 4);
			wcout << err << L"!!\n\n";
			ResetAttribute();
		}
		size_t size{ matrix.size() };
		if (size == 0) {
			argc = Random;
			goto RETURN;
		}
		if (matrix == Matrix<>(size, tensor<long double>(size, 0))) break;
		Mx = matrix;

		// output matrice risultato
		SetConsoleTextAttribute(hConsole, 2);
		wcout << L"\nQuesta è la matrice: \n\n";
		matrix.output({ 0, -2 }, __NULL__, 2);
		wcout << L'\n';
		ResetAttribute();

		// calcolo matrice di permutazione
		auto Id{ Matrix<>(size, tensor<long double>(size, 0)) };
		for (size_t i = 0; i < size; ++i) Id[i][i] = 1;
		auto permutator{ Id };
		for (size_t i = 0; i + 1 < size; ++i) {

			int max = Mx[size - 1][i], IndexofMax = size - 1;
			for (ptrdiff_t j = size - 2; j >= i; --j) {
				if (j < 0) break;
				if (Mx[j][i] > max) {
					max = Mx[j][i];
					IndexofMax = j;
				}
			}

			if (IndexofMax != i) {
				swap(Mx[IndexofMax], Mx[i]);
				swap(permutator[IndexofMax], permutator[i]);
			}
		}

		// trasposizione della matrice di permutazione
		auto NewPermutator{ Matrix<>(size) };
		for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j)
			NewPermutator[i] << permutator[j][i];
		permutator = NewPermutator;

		// calcolo elementi
		auto lower{ Id };
		auto upper{ Mx };
		bool Break{ false };
		for (size_t i = 0; i + 1 < size; ++i) {
			
			for (size_t j = i + 1; j < size; ++j) {
				
				if (upper[i][i] == 0) {
					Break = true;
					break;
				}
				lower[j][i] = upper[j][i] / upper[i][i];

				for (size_t k = 0; k < size; ++k)
					upper[j][k] -= lower[j][i] * upper[i][k];
			}
			if (Break) break;
		}

		// decomposizione PLU
		if (!Break) {
			wcout << L"Decomposizione PLU:\n";
			permutator.DisplayWith(lower, upper);
		}

		// algoritmo di givens
		Mx = matrix;
		auto ortogonal{ Id };
		Break = false;
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = i + 1; j < size; ++j) if (Mx[j][i] != 0) {

				long double norm{ hypot(Mx[j][i], Mx[j - 1][i]) };
				if (norm == 0) {
					Break = true;
					break;
				}
				long double cosine{ Mx[j - 1][i] / norm }, sine{ Mx[j][i] / norm };

				auto givens{ Id };
				givens[i][i] = cosine;
				givens[i][j] = sine;
				givens[j][i] = -sine;
				givens[j][j] = cosine;

				Mx = givens * Mx;
				ortogonal *= givens;
			}
			if (Break) break;
		}

		// decomposizione QR
		if (!Break) {
			wcout << L"Decomposizione QR:\n";
			ortogonal.DisplayWith(Mx);
		}

		// decomposizione di cholesky
		Mx = matrix;
		lower = Id;
		Break = false;
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j <= i; ++j) {
				double sum{};

				// elementi sulla diagonale
				if (i == j) {
					for (size_t k = 0; k < i; ++k) sum += lower[i][k] * lower[i][k];
					lower[i][i] = sqrt(Mx[i][i] - sum);
				}

				// controllo risultati corretti
				if (lower[i][i] == 0 or isnan(lower[i][i])) {
					Break = true;
					break;
				}

				// elementi sotto alla diagonale
				if (i != j) {
					for (size_t k = 0; k < i; ++k) sum += lower[i][k] * lower[j][k];
					lower[i][j] = (Mx[i][j] - sum) / lower[j][j];
				}

			}
			if (Break) break;
		}
		auto lowerT{ Matrix<>(size) };
		if (!Break) for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size; ++j) lowerT[i] << lower[j][i];

		// output decomposizione
		if (!Break) {
			wcout << L"Decomposizione di cholesky:\n";
			lower.DisplayWith(lowerT);
		}

		// calcolo autovalori
		Mx = matrix;
		auto MxT{ Id };
		for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j)
			MxT[i][j] = Mx[j][i];
		auto Mx_MxT{ Mx * MxT };
		auto MxT_Mx{ MxT * Mx };
		auto EigenV{ Mx_MxT.EigenValues() };

		// calcolo matrici U, V e sigma
		auto sigma{ Id };
		Break = EigenV.size() != size;
		Matrix<> U, V;
		if (!Break) {
			for (size_t i = 0; i < size; ++i) sigma[i][i] = sqrt(EigenV[i]);
			U = Mx_MxT.EigenVectors(EigenV);
			V = MxT_Mx.EigenVectors();
			if (V.empty()) Break = true;
			else {
				auto NewV{ Id };
				for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j)
					NewV[i][j] = V[j][i];
				V = NewV;
			}
		}

		// decomposizione a valori singolari
		if (!Break) {
			wcout << L"Decomposizione a valori singolari:\n";
			U.DisplayWith(sigma, V);
		}

		// output dati della matrice
		auto maindet{ matrix.det() };
		wcout << L"Determinante: " << maindet << L'\n';
		auto eigenvalues{ matrix.EigenValues() };
		wcout << L"Autovalori reali: " << eigenvalues << L'\n';
		auto eigenvectors{ matrix.EigenVectors(eigenvalues) };
		if (eigenvectors == size) {
			wcout << L"Autovettori reali: \n";
			for (auto vector : eigenvectors) wcout << vector << L'\n';
			wcout << L'\n';
		}

		// risoluzione sistema lineare
		if (maindet == 0) {

			// calcolo nuovo determinante
			wstring varlist{ L"xyzwuv" };
			tensor<double> solutionList;
			auto NewMatrix{ matrix };
			for (auto& row : NewMatrix) row--;
			NewMatrix--;
			auto newdet{ NewMatrix.det() };
			if (newdet == 0) continue;

			// calcolo soluzioni
			for (size_t i = 0; i < size - 1; ++i) {
				Mx = NewMatrix;
				for (size_t j = 0; j < size - 1; ++j)
					Mx[j][i] = matrix[j].last();
				solutionList << Mx.det() / newdet;
			}

			// output risultati
			wcout << L"Soluzioni del sistema lineare: \n";
			for (size_t i = 0; i < size - 1; ++i)
				wcout << varlist[i] << L" = " << solutionList[i] << L'\n';
			wcout << L'\n';
		}
	}
	
	// invio del segnale per terminare i thread
	argc = NotAssigned;
RETURN:
	{
		lock_guard<mutex> lk(MonitorMTX);
		RunMonitor = false;
	}
	MonitorCV.notify_all();
}

#pragma endregion

#pragma endregion

// file natvis                                54  righe
// tensor.cpp                                 806 righe
/// totale righe non presenti in questo file: 860

// fine del codice -----------------------------------------------------------------

/*	LAVORO DA FARE
	
	debug systemsolver
	debug generale
	
	ottimizzazione generica O(n^2) --> O(n*log(n))
	
	aggiunta valori sui tratti degli assi e frecce
	
	upgrade generico del grafico
	
	polinomi a coefficienti complessi
	
LAVORO MOLTO DIFFICILE
	
	operazioni ricorsive polinomiali infinite
	radicali e operazioni con i radicali

	trasparenza e linee tratteggiate
	effetti per il colore
	calcolo sulla GPU
*/