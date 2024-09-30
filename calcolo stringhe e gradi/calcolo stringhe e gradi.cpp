// inizio del codice
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

// macro di rinominazione
#define POS false
#define NEG true
#define ret return
#define FRIEND_BOOL_OPERATOR \
template<typename U, typename = enable_if_t<is_integral_v<U>>> friend bool operator

// funzioni macro
#define _GetCursorPos() GetConsoleScreenBufferInfo(hConsole, &csbi)
#define ResetAttribute() SetConsoleTextAttribute(hConsole, 15)
#define V1converter(func, param) To1V(func(ToXV(param)))
#define VXconverter(func, param) ToXV(func(To1V(param)))
#define DECLARE_TIME_POINT(x) LARGE_INTEGER x; QueryPerformanceCounter(&(x))

// funzioni macro importanti
#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)
#define issign(x)  (x == L'+' || x == L'-')
#define Last(x)    (x).at((x).size() - 1)
#define _SQ(x)     x * x

// pragma warning
#ifndef BUGS
#pragma	warning (disable : 4244) // conversione, possibile perdita di dati
#pragma	warning (disable : 4267) // conversione, possibile perdita di dati
#pragma warning (disable : 4348) // ridefinizione di un parametro predefinito
#pragma	warning (disable : 4715) // non tutti i percorsi restituiscono un valore
#pragma	warning (disable : 6001) // utilizzo di memoria non inizializzata
#pragma	warning (disable : 28182) // dereferenziazione del puntatore null
#endif

// messaggi
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")

#ifdef BUGS
RUIN UNOPT
#else
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

// namespace globali
using namespace std;
using namespace _STD chrono;
using Concurrency::parallel_for, this_thread::sleep_for;

#pragma endregion
#pragma region Globals

// oggetti windows
void* hConsole{
	GetStdHandle(STD_OUTPUT_HANDLE)
};
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
struct compost {
	ptrdiff_t factors;
	int exp;
};
struct divisor {
	ptrdiff_t DivNumber{ 1 };
	ptrdiff_t DivSum{ 1 };
	ptrdiff_t DivProduct{ 1 };
	wstring Div_pr;
};
struct digitRatio {
	int digitSumRatioNum{};
	int digitSumRatioDen{};
	int digitProductRatioNum{};
	int digitProductRatioDen{};
};
digitRatio items;
struct coord {
	double X;
	double Y;
	
	coord() : X(0), Y(0) {}
	coord(double _x, double _y) : X(_x), Y(_y) {}
	coord(COORD _coord) : X(_coord.X), Y(_coord.Y) {}

	operator COORD() const
	{
		ret {
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
	FactorPolynomial    ,
	FactorFraction      ,
	FactorMatrix        ,
	Random              ,
	NotAssigned
};
unordered_map<wstring, switchcase> stringToEnumMap{
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
	{ L"pol", switchcase::FactorPolynomial     },
	{ L"alg", switchcase::FactorFraction       },
	{ L"mtx", switchcase::FactorMatrix         },
	{ L"rnd", switchcase::Random               }
};
unordered_map<switchcase, wstring> enumToStringMap{
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
	{ switchcase::FactorPolynomial    , L"pol" },
	{ switchcase::FactorFraction      , L"alg" },
	{ switchcase::FactorMatrix        , L"mtx" },
	{ switchcase::Random              , L"rnd" }
};
unordered_map<wstring, wstring> ConvertFromSuperScript{
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

namespace std_tensor
{
	wstring Variables;

	// tensor, una variante ottimizzata di ::std::vector
	template<class T>class tensor
	{
	protected:

		// dati
		T* data;
		size_t capacity{ 10 };
		size_t count{ 10 };
	
		// metodi privati
		void resize(size_t new_capacity)
		{
			if (new_capacity < capacity) ret;
			T* new_data = new T[new_capacity];
			if (data != nullptr) {
				for (size_t i = 0; i < count; ++i) new_data[i] = move(data[i]);
				delete[] data;
			}
			data = new_data;
			capacity = new_capacity;
		}

	public:

		// costruttori e distruttori
		tensor(): data(nullptr), capacity(0), count(0)
		{
			resize(10);
		}
		tensor(const tensor& other): data(nullptr), capacity(0), count(0)
		{
			resize(other.count);
			count = other.count;
			for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
		}
		tensor(tensor&& other) noexcept:
			data(other.data),
			capacity(other.capacity),
			count(other.count)
		{
			other.data = nullptr;
			other.capacity = 0;
			other.count = 0;
		}
		tensor(initializer_list<T> init) : tensor()
		{
			for (const T& value : init) push_back(value);
		}
		tensor(size_t size, const T& initial_value)
			: data(nullptr), capacity(0), count(0)
		{
			resize(size);
			count = size;
			fill(data, data + count, initial_value);
		}
		tensor(size_t size) : data(nullptr), capacity(0), count(0)
		{
			resize(size);
			count = size;
		}
		~tensor()
		{
			delete[] data;
		}

		// assegnazione
		tensor& operator=(const tensor& other)
		{
			if (this != &other) {
				resize(other.count);
				for (size_t i = 0; i < other.count; ++i) data[i] = other.data[i];
				count = other.count;
			}
			ret *this;
		}
		tensor& operator=(tensor&& other) noexcept
		{
			if (this != &other) {
				delete[] data;
				data = other.data;
				capacity = other.capacity;
				count = other.count;
				other.data = nullptr;
				other.capacity = 0;
				other.count = 0;
			}
			ret *this;
		}
		inline void assign(tensor<T> other)
		{
			*this = other;
		}

		// metodi di base
		inline size_t size() const
		{
			ret count;
		}
		inline size_t get_capacity() const
		{
			ret capacity;
		}
		inline bool empty() const
		{
			ret count == 0;
		}

		// metodi di accesso agli elementi
		inline T& at(size_t index)
		{
			if (index >= count) throw out_of_range("Index out of range");
			ret data[index];
		}
		inline const T& at(size_t index) const
		{
			if (index >= count) throw out_of_range("Index out of range");
			ret data[index];
		}
		inline T& last()
		{
			ret data[count - 1];
		}
		inline const T& last() const
		{
			ret data[count - 1];
		}

		// metodi di taglio
		inline void clear()
		{
			count = 0;
		}
		tensor erase(size_t pos)
		{
			if (pos >= count) throw out_of_range("Index out of range");
			count = pos;
			ret *this;
		}
		tensor erase(size_t pos, size_t n)
		{
			if (pos >= count) throw out_of_range("Index out of range");
			n = min(n, count - pos);
			for (size_t i = pos; i < count - n; ++i) data[i] = move(data[i + n]);
			count -= n;
			ret *this;
		}

		// operatori di accesso agli elementi
		_NODISCARD inline T& operator[](size_t index)
		{
			ret at(index);
		}
		_NODISCARD inline const T& operator[](size_t index) const
		{
			ret at(index);
		}
	
		// operatori di modifica degli elementi e della dimensione
		inline void push_back(const T& value)
		{
			if (count == capacity) resize(capacity * 2 + 1);
			data[count++] = value;
		}
		inline void pop_back()
		{
			if (count == 0) throw out_of_range("tensor is empty");
			count--;
		}
		void push_front(const T& value)
		{
			if (count == capacity) resize(capacity * 2);
			for (size_t i = count; i > 0; --i) data[i] = move(data[i - 1]);
			data[0] = value;
			count++;
		}
		void pop_front()
		{
			if (count == 0) throw out_of_range("tensor is empty");
			for (size_t i = 0; i < count - 1; ++i) data[i] = move(data[i + 1]);
			count--;
		}

		// operatori di modifica della dimensione
		inline tensor<T>& operator++()
		{
			push_front(T());
			ret *this;
		}
		inline tensor<T> operator++(int)
		{
			tensor temp = *this;
			push_back(T());
			ret temp;
		}
		inline tensor<T>& operator--()
		{
			pop_front();
			ret *this;
		}
		inline tensor<T> operator--(int)
		{
			tensor temp = *this;
			pop_back();
			ret temp;
		}
		inline tensor& operator-=(size_t n)
		{
			count = n > count ? 0 : count - n;
			ret *this;
		}

		// operatori push
		tensor& operator()(size_t n)
		{
			if (n >= count) resize(n * 2);
			count = n;
			ret *this;
		}
		tensor& operator()(size_t n, const T& value)
		{
			if (n >= count) resize(n * 2);
			for (size_t i = count; i < n; ++i) data[i] = value;
			count = n;
			ret *this;
		}
		inline tensor& operator<<(const T& value)
		{
			push_back(value);
			ret *this;
		}
		inline tensor& operator>>(const T& value)
		{
			push_front(value);
			ret *this;
		}

		// operatori di uguaglianza
		_NODISCARD bool operator==(const tensor& other) const
		{
			if (count != other.count) ret false;
			for (size_t i = 0; i < count; ++i) if (data[i] != other.data[i])
				ret false;
			ret true;
		}
		_NODISCARD inline bool operator!=(const tensor& other) const
		{
			ret !(*this == other);
		}

		// operatori di concatenazione
		_NODISCARD tensor operator+(const tensor& other) const
		{
			tensor result = *this;
			result += other;
			ret result;
		}
		tensor& operator+=(const tensor& other)
		{
			for (size_t i = 0; i < other.count; ++i) push_back(other.data[i]);
			ret *this;
		}

		// operatori di confronto tra tensori
		_NODISCARD inline bool operator<(const tensor& other) const
		{
			ret count < other.count;
		}
		_NODISCARD inline bool operator<=(const tensor& other) const
		{
			ret count <= other.count;
		}
		_NODISCARD inline bool operator>(const tensor& other) const
		{
			ret count > other.count;
		}
		_NODISCARD inline bool operator>=(const tensor& other) const
		{
			ret count >= other.count;
		}

		// operatori di confronto a destra con un intero
		FRIEND_BOOL_OPERATOR==(const tensor& t, U n)
		{
			ret t.count == static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR!=(const tensor& t, U n)
		{
			ret t.count != static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR<(const tensor& t, U n)
		{
			ret t.count < static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR<=(const tensor& t, U n)
		{
			ret t.count <= static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR>(const tensor& t, U n)
		{
			ret t.count > static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR>=(const tensor& t, U n)
		{
			ret t.count >= static_cast<size_t>(n);
		}

		// operatori di confronto a sinistra con un intero
		FRIEND_BOOL_OPERATOR==(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) == t.count;
		}
		FRIEND_BOOL_OPERATOR!=(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) != t.count;
		}
		FRIEND_BOOL_OPERATOR<(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) < t.count;
		}
		FRIEND_BOOL_OPERATOR<=(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) <= t.count;
		}
		FRIEND_BOOL_OPERATOR>(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) > t.count;
		}
		FRIEND_BOOL_OPERATOR>=(U n, const tensor& t)
		{
			ret static_cast<size_t>(n) >= t.count;
		}

		// operatori logici
		_NODISCARD inline bool operator&&(const tensor& other) const
		{
			ret !this->empty() and !other.empty();
		}
		_NODISCARD inline bool operator||(const tensor& other) const
		{
			ret !this->empty() or !other.empty();
		}
		_NODISCARD inline bool operator%(const tensor& other) const
		{
			ret this->size() xor other.size();
		}

		// iteratori
		class iterator
		{
		private: T* data;

		public: size_t index;
			using value_type        = T;
			using reference         = T&;
			using pointer           = T*;
			using difference_type   = ptrdiff_t;
			using iterator_category = forward_iterator_tag;

			iterator(T* data, size_t index) : data(data), index(index) {}

			iterator& operator++()
			{
				index++; 
				ret *this;
			}
			iterator operator++(int)
			{ 
				iterator temp = *this;
				index++; 
				ret temp;
			}
			iterator& operator--()
			{
				index--;
				ret *this;
			}
			iterator operator--(int)
			{
				iterator temp = *this;
				index--;
				ret temp;
			}

			iterator operator+(size_t n) const
			{
				ret iterator(data, index + n);
			}
			iterator& operator+=(size_t n)
			{
				index += n;
				ret *this;
			}
			iterator operator-(size_t n) const
			{
				ret iterator(data, index - n);
			}
			iterator& operator-=(size_t n)
			{
				index -= n;
				ret *this;
			}

			size_t operator+(iterator value) const
			{
				ret index + value.index;
			}
			size_t operator-(iterator value) const
			{
				if (index == value.index) ret 0;
				if (index < value.index) throw out_of_range("Index out of range");
				ret index - value.index;
			}

			T& operator*()
			{
				ret data[index];
			}
			const T& operator*() const
			{
				ret data[index];
			}
			T* operator->()
			{
				ret &data[index];
			}
			const T* operator->() const
			{
				ret &data[index];
			}

			bool operator==(const iterator& other) const
			{
				ret index == other.index;
			}
			bool operator!=(const iterator& other) const
			{
				ret index != other.index;
			}
			bool operator<(const iterator& other) const
			{
				ret index < other.index;
			}
			bool operator<=(const iterator& other) const
			{
				ret index <= other.index;
			}
			bool operator>(const iterator& other) const
			{
				ret index > other.index;
			}
			bool operator>=(const iterator& other) const
			{
				ret index >= other.index;
			}
		};
		iterator begin()
		{
			ret iterator(data, 0);
		}
		iterator end()
		{
			ret iterator(data, count);
		}
		tensor(iterator first, iterator last) : data(nullptr), capacity(0), count(0)
		{
			size_t n = last - first;
			if (n > count) resize(n);
			count = n;

			for (size_t i = 0; i < n; ++i, ++first) data[i] = *first;
		}

		// metodi con gli operatori
		void erase(iterator it)
		{
			if (it == end()) throw out_of_range("Iterator out of range");
			size_t pos{ it - begin() };
			for (size_t i = pos; i < count - 1; ++i) data[i] = move(data[i + 1]);
			count--;
		}
		void erase(iterator first, iterator last)
		{
			if (first == last) ret;
			size_t start{ first - begin() };
			size_t end{ last - begin() };

			if (start >= count or end > count or start > end)
				throw out_of_range("Invalid iterator range");

			size_t distance = end - start;
			for (size_t i = start; i < count - distance; ++i)
				data[i] = move(data[i + distance]);

			count -= distance;
		}
		void insert(iterator pos, const T& value)
		{
			size_t index = pos - begin();
			if (count == capacity) resize(capacity * 2);

			for (size_t i = count; i > index; --i) data[i] = move(data[i - 1]);

			data[index] = value;
			count++;
		}
		void remove(const T& value)
		{
			size_t write{};
			for (size_t read = 0; read < count; ++read) if (data[read] != value)
			{
				if (write != read) data[write] = move(data[read]);
				write++;
			}
			count = write;
		}

		virtual _NODISCARD wstring str(int size = Variables.size())
		{
			wostringstream result;
			wstring outp;
			result << fixed;

			// bool
			if constexpr (is_same_v<T, bool>) for (const auto& element : *this) {
				result << element ? L"1" : L"0";
				result << L", ";
			}

			// carattere
			else if constexpr (is_same_v<T, wchar_t>) {
				for (const auto& element : *this) result << element;
				result << L", ";
			}

			// numeri decimali
			else if constexpr (is_same_v<T, double>) for (const auto& element : *this)
			{
				if (integer(element)) result << setprecision(0);
				result << element << L", ";
				if (integer(element)) result << setprecision(6);
			}

			// dati generici
			else if constexpr (is_integral_v<T> or is_same_v<T, wstring>)
				for (const auto& element : *this) result << element << L", ";

			// niente
			else ret L"";

			// fine
			outp = result.str();
			if (outp.size() >= 2) {
				outp.pop_back();
				outp.pop_back();
			}
			ret L'{' + outp + L'}';
		}
	};

	// estensioni di tensor
	class tensor_t
	{
	public:
		tensor<bool> is_prime;
		tensor<ptrdiff_t> list_primes;

		tensor_t(){}	
		tensor_t(
			tensor<bool> is_prime_param, 
			tensor<ptrdiff_t> list_primes_param
		): 
			is_prime(move(is_prime_param)), 
			list_primes(move(list_primes_param))
		{}
		tensor_t(const tensor_t& other)
			: is_prime(other.is_prime), list_primes(other.list_primes)
		{}
		tensor_t(tensor_t&& other) noexcept
			: is_prime(move(other.is_prime)),
			list_primes(move(other.list_primes))
		{}

		tensor_t& operator=(const tensor_t& other)
		{
			if (this != &other) {
				is_prime = other.is_prime;
				list_primes = other.list_primes;
			}
			ret *this;
		}
	};

};
#define _TENSOR ::std_tensor::
using _TENSOR Variables, _TENSOR tensor, _TENSOR tensor_t;

// numeri grandi con precisione di long double
class big
{
	// dati
private: tensor<int> Integer;
	bool sign;
	long double decimal;

	void shift()
	{
		wstring str;
		wostringstream oss;
		oss << fixed << setprecision(25) << decimal;
		str = oss.str();
		str.erase(0, 2);
		bool Do{ false };
		for (ptrdiff_t i = str.size() - 1; i >= 0; --i) {
			int element = str.at(i) - '0';
			if (element != 0) Do = true;
			if (Do) Integer << element;
		}
	}

	big Multiply(const big& value) const
	{
		if ((value.Integer[0] == 0 and value.decimal == 0) or
			(Integer[0] == 0 and decimal == 0)) ret 0;
		big Val = value, This = *this;
		Val.shift();
		This.shift();
		int decprecision = Val.Integer.size() - value.Integer.size()
			+ This.Integer.size() - Integer.size();
		This.sign = POS;
		Val.sign = POS;

		// moltiplicazione
		tensor<big> add;
		for (size_t a = 0; a < Val.Integer.size(); ++a) {

			int factor{ Val.Integer.at(a) };
			if (factor == 0) continue;
			int carry{}, prod{};

			auto _Number{ This.Integer };
			for (ptrdiff_t i = _Number.size() - 1; i >= 0; --i) {
				prod = (_Number.at(i)) * factor + carry;
				carry = prod / 10;
				_Number.at(i) = prod % 10;
			}
			if (carry != 0) _Number >> carry;
			for (ptrdiff_t i = Val.Integer.size() - a - 2; i >= 0; --i)
				_Number << 0;
			add << big(_Number);
		}

		// somma
		This.Integer.clear();
		for (auto big : add) This += big;

		// cifre decimali
		int dec{};
		auto decdigits{ This.Integer };
		while (decdigits.size() - decprecision < 0) decdigits >> 0;
		This.Integer = decdigits;
		if (decprecision > 0) This.Integer.erase(decdigits.size() - decprecision);
		decdigits.erase(0, decdigits.size() - decprecision);
		for (size_t i = 0; i < decdigits; ++i)
			dec += decdigits[i] * pow(10, decdigits.size() - i - 1);
		This.decimal = dec / pow(10, decprecision);

		This.sign = sign xor value.sign;
		ret This;
	}

public:

	long double Number()
	{
		ptrdiff_t val{};

		// calcolo parte intera
		for (size_t i = 0; i < Integer; ++i) {
			val += Integer[i] * pow(10, Integer.size() - i - 1);
			if (val <= -2'147'483'647 or val >= 2'147'483'647) ret nan("");
		}
		long double res = val;
		
		// parte decimale e segno
		res += decimal;
		if (sign == NEG) res *= -1;
		ret res;
	}

	// costruttori
	big() : sign(POS), Integer(), decimal(0) {}
	big(int param) : sign(param < 0), Integer(), decimal(0)
	{
		wstring Param{ to_wstring(param) };
		if (Param.at(0) == L'-') Param.erase(0, 1);
		for (auto ch : Param) Integer << ch - '0';
	}
	big(ptrdiff_t param) : sign(param < 0), Integer(), decimal(0)
	{
		wstring Param{ to_wstring(param) };
		if (Param.at(0) == L'-') Param.erase(0, 1);
		for (auto ch : Param) Integer << ch - '0';
	}
	big(double param) : sign(param < 0), Integer(0), decimal(0)
	{
		int intParam = param;
		wstring Param{ to_wstring(intParam) };
		if (Param.at(0) == L'-') Param.erase(0, 1);
		for (auto ch : Param) Integer << ch - '0';
		decimal = _STD fabs(param) - _STD fabs(intParam);
	}
	big(long double param) : sign(param < 0), Integer(0), decimal(0)
	{
		int intParam = param;
		wstring Param{ to_wstring(intParam) };
		if (Param.at(0) == L'-') Param.erase(0, 1);
		for (auto ch : Param) Integer << ch - '0';
		decimal = _STD fabs(param) - _STD fabs(intParam);
	}
	big(tensor<int> Big) : sign(POS), Integer(Big), decimal(0) {}
	big(wstring wstr) : sign(POS), Integer(0), decimal(0)
	{
		tensor<int> Big;
		for (auto c : wstr) if (isdigit(c)) Integer << c - '0';
	}

	// confronto primario e assegnazione
	big& operator=(const big& other)
	{
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
		auto integ{ Integer };
		auto oth_integ{ other.Integer };

		if (sign and !other.sign) ret true;
		if (!sign and other.sign) ret false;

		while (integ[0] == 0) {
			if (integ <= 1) break;
			--integ;
		}
		while (oth_integ[0] == 0) {
			if (oth_integ <= 1) break;
			--oth_integ;
		}

		if (integ % oth_integ) ret integ < oth_integ xor sign;
		for (size_t i = 0; i < integ; ++i) if (integ[i] != oth_integ[i])
			ret integ[i] < oth_integ[i] xor sign;

		ret decimal < other.decimal xor sign;
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
		big Val = value, This = *this;
		bool carry{ false };

		// segni
		if (!This.sign and Val.sign) {
			Val.sign = POS;
			ret This - Val;
		}
		if (This.sign and !Val.sign) {
			This.sign = POS;
			ret Val - This;
		}
		if (Val.sign and This.sign) Val.sign = POS;

		// ridimensionamento
		if (This.Integer < Val.Integer) swap(This, Val);
		while (Val.Integer < This.Integer) Val.Integer >> 0;

		// somma
		This.decimal += Val.decimal;
		carry = This.decimal >= 10;
		if (carry) This.decimal--;
		for (ptrdiff_t i = This.Integer.size() - 1; i >= 0; --i) {
			int sum = This.Integer[i] + Val.Integer[i] + carry;
			carry = sum >= 10;
			This.Integer[i] = sum % 10;
		}
		if (carry) This.Integer >> 1;

		ret This;
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
		ret* this;
	}

	// sottrazione
	big operator-(const big& value) const
	{
		big Val = value, This = *this;
		bool carry{ false };

		// segni
		if (!This.sign and Val.sign) {
			Val.sign = POS;
			ret This + Val;
		}
		if (This.sign and !Val.sign) {
			Val.sign = NEG;
			ret Val + This;
		}
		if (Val.sign and This.sign) Val.sign = POS;

		// ridimensionamento
		while (This.Integer > Val.Integer) Val.Integer >> 0;
		while (Val.Integer > This.Integer) This.Integer >> 0;
		if (This < Val) {
			swap(This, Val);
			This.sign = !This.sign;
		}

		This.decimal -= Val.decimal;
		carry = This.decimal < 0;
		if (carry) This.decimal++;

		for (ptrdiff_t i = This.Integer.size() - 1; i >= 0; --i) {
			int diff = This.Integer[i] - Val.Integer[i] - carry;
			carry = diff < 0;
			This.Integer[i] = (diff + 10) % 10;
		}

		while (This.Integer[0] == 0) {
			if (This.Integer <= 1) break;
			--This.Integer;
		}
		ret This;
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
		for (size_t i = 0; i < shift; ++i) result.Integer << 0;
		ret result;
	}
	inline big& operator<<=(int shift)
	{
		*this = *this << shift;
		ret *this;
	}
	big operator*(const big& value) const
	{
		if (Integer.size() <= 2 or value.Integer.size() <= 2) ret Multiply(value);
		int m = max(Integer.size(), value.Integer.size());
		int m2 = _STD ceil((double)min(Integer.size(), value.Integer.size()) / 2);

		// suddivisione
		auto Int{ Integer }, valInt{ value.Integer };
		big high1 = tensor<int>(Int.begin(), Int.begin() + m2);
		big low1 = tensor<int>(Int.begin() + m2, Int.end());
		big high2 = tensor<int>(valInt.begin(), valInt.begin() + m2);
		big low2 = tensor<int>(valInt.begin() + m2, valInt.end());

		// ricorsione
		big z1 = (low1 + high1) * (low2 + high2);
		big z0 = low1 * low2, z2 = high1 * high2;

		ret (z2 << (2 * (m - m2))) + ((z1 - z2 - z0) << (m - m2)) + z0;
	}
	inline big& operator*=(const big& value)
	{
		*this = *this * value;
		ret *this;
	}

	// divisione intera
	big operator/(const big& value) const
	{
		if (value == 0) throw invalid_argument("Division by zero!");

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
				--current.Integer;

			// divisione
			while (current >= value.fabs()) {
				current -= value.fabs();
				quotient++;
			}
			result.Integer << quotient;
		}

		// ridimensionamento
		while (result.Integer > 1 and result.Integer[0] == 0) --result.Integer;
		result.decimal = 0;
		ret result;
	}
	inline big& operator/=(const big& value)
	{
		*this = *this / value;
		ret *this;
	}

	// modulo
	big operator%(const big& value) const
	{
		if (value == 0) throw invalid_argument("Modulo by zero!");

		// segni
		big This = *this, Val = value;
		This.sign = POS;
		Val.sign = POS;

		// calcolo
		while (This >= Val) {
			big temp = Val, factor = 1;

			while ((temp << 1) <= This) {
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
		if (*this < 0) NewBase.invert();
		while (--NewExp > 0) {
			power *= NewBase;
			if (power < 0) ret -1;
		}
		if (exp % 2 == 1 and *this < 0) power.invert();
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
		if (integ) (*this)++;
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
		for (int i = 0;; ++i) {
			if (*this < base) ret i;
			*this /= base;
		}
	}

	// output
	wostringstream c_str(int precision) const
	{
		wostringstream oss, result;
		if (sign) wcout << L'-';
		for (size_t i = 0; i < Integer; ++i) result << Integer[i];
		oss << setprecision(precision) << decimal;
		auto str{ oss.str() };
		str.erase(0, 1);
		if (!str.empty()) result << L'.' << str;
		ret result;
	}
	inline wstring str() const
	{
		ret c_str(0).str();
	}
	friend wostream& operator<<(wostream& os, const big& Big)
	{
		os << Big.str();
		return os;
	}
};
big LCM(1);

// numeri complessi
class complex
{
public:

	// dati
	double RealPart;
	double ImaginaryPart;
	double norm() const
	{
		ret sqrt(RealPart * RealPart + ImaginaryPart * ImaginaryPart);
	}

	// costruttori
	complex() : RealPart(0), ImaginaryPart(0) {}
	complex(double real) : RealPart(real), ImaginaryPart(0) {}
	complex(double real, double imag) : RealPart(real), ImaginaryPart(imag) {}

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
		double a{ RealPart };
		double b{ ImaginaryPart };
		double c{ value.RealPart };
		double d{ value.ImaginaryPart };

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
		double a{ RealPart };
		double b{ ImaginaryPart };
		double c{ value.RealPart };
		double d{ value.ImaginaryPart };

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
	wstring c_str() const
	{
		wostringstream output;
		output << setprecision(10) << L'(' << RealPart << L' ';
		ImaginaryPart > 0 ? output << L'+' : output << L'-';
		output << L" i" << fabs(ImaginaryPart) << L')';
		ret output.str();
	}
};

// monomi
template<typename T_int = long double>struct MONOMIAL {
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
	int degree()
	{
		int sum{};
		for (size_t i = 0; i < exp; ++i) sum += exp[i];
		ret sum;
	}
	bool IsSquare()
	{
		if (!integer(sqrt(fabs(this->coefficient)))) ret false;
		for (size_t i = 0; i < exp; ++i) if (exp[i] % 2 == 1) ret false;
		ret true;
	}
	monomial Root(int order)
	{
		monomial result;

		result.coefficient = pow(this->coefficient, 1.0 / order);
		for (size_t i = 0; i < exp; ++i) result.exp << (exp[i] / order);

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
		for (const auto& value : vect) this->push_back(value);
	}

	void SortByDegree()
	{
		for (size_t i = 0; i < this->size(); ++i)
			for (size_t j = i + 1; j < this->size(); ++j)
				if (this->at(i).degree() < this->at(j).degree())
					swap(this->at(i), this->at(j));
	}
	void SortByExponents()
	{
		for (size_t i = 0; i < this->size(); ++i)
			for (size_t j = i + 1; j < this->size(); ++j) {
				bool swap{ false };
				for (size_t k = 0; k < Variables.size(); ++k) {
					if (this->at(i).exp[k] > this->at(j).exp[k]) break;
					if (this->at(i).exp[k] == this->at(j).exp[k]) continue;
					swap = true;
					break;
				}
				if (swap) ::swap(this->at(i), this->at(j));
			}
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		wstring polynomial;
		tensor<int> null(size, 0);
		for (auto data : *this) {

			// caso nullo
			if (data.coefficient == 0) continue;

			// aggiunta coefficiente
			wstring Monomial;
			Monomial = data.coefficient > 0 ? L'+' : L'-';
			if ((data.coefficient != 1 and data.coefficient != -1)
				or data.exp == null)
			{
				if constexpr (is_same_v<T_int, long double>)
					Monomial += to_wstring((int)fabs(data.coefficient));
				else if constexpr (is_same_v<T_int, big>)
					Monomial += data.coefficient.fabs().str();
			}

			// aggiunta variabili ed esponenti
			for (size_t i = 0; i < Variables.size(); ++i) if (data.exp[i] != 0) {
				Monomial += size == Variables.size() ?
					Variables.at(i) : Variables.at(Variables.find(charVariable));
				if (data.exp[i] > 1) {
					Monomial += L'^';
					Monomial += to_wstring((int)data.exp[i]);
				}
			}

			polynomial += Monomial;
		}
		if (polynomial.at(0) == L'+') polynomial.erase(0, 1);

		ret polynomial;
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
		for (const auto& value : vect) this->push_back(value);
	}

	void sort()
	{
		for (size_t i = 0; i < this->size(); ++i)
			for (size_t j = i + 1; j < this->size(); ++j)
				if (this->at(i).degree < this->at(j).degree)
					swap(this->at(i), this->at(j));
	}
	void complete(int s)
	{
		// riempimento buchi
		for (ptrdiff_t i = this->size() - 1; i > 0; --i)
			for (int j = 1; j < (*this)[i - 1].degree - (*this)[i].degree; ++j)
				this->insert(this->begin() + i, { (*this)[i - 1].degree - j, 0 });

		// riempimento buchi agli estremi
		if (this->empty()) for (size_t i = 0; i < s; ++i)
			this->push_back({ (int)i, 0 });
		if (this->size() < s)
		{
			while ((*this)[0].degree < s - 1)
				this->insert(this->begin(), { (*this)[0].degree + 1, 0 });

			while ((*this)[this->size() - 1].degree > 0)
				this->push_back({ (*this)[this->size() - 1].degree - 1, 0 });
		}
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		factor<T_int> traduction;
		int _FirstPos = Variables.find(charVariable);
		for (const auto& Monomial : *this) {
			monomial<T_int> element;
			element.coefficient = Monomial.coefficient;
			element.exp(Variables.size(), 0);
			element.exp[_FirstPos] = Monomial.degree;
			traduction << element;
		}
		ret traduction.str(1);
	}
};
static factor<> ToXV(FACTOR<> vect)
{
	factor<> output;
	int _FirstPos = Variables.find(charVariable);
	for (const auto& Monomial : vect) {
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
	for (const auto& Monomial : vect) {
		MONOMIAL<> element{ 0, 0 };
		element.coefficient = Monomial.coefficient;
		if (_FirstPos != wstring::npos) element.degree = Monomial.exp[_FirstPos];
		output << element;
	}
	ret output;
}

// polinomi completi
static void ElabExponents(wstring& str);
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
		for (const auto& value : vect) push_back(value);
	}

	void open()
	{
		for (size_t i = 0; i < this->count; ++i) if ((*this)[i][0].exp[0] == -1)
		{
			auto repeat = (*this)[i][0].coefficient;
			this->erase(this->begin() + i);
			auto push{ (*this)[i] };
			for (big j = 0; j < repeat - 1; ++j) this->push_front(push);
		}
	}
	void close()
	{
		tensor<int> modifier(Variables.size());
		modifier[0] = -1;
		factor<T_int> CommonFactor;
		if (this->count != 0) for (size_t i = 0; i < this->count; ++i)
			for (ptrdiff_t j = this->count - 1; j > i; --j)
				if ((*this)[i] == (*this)[j] and (*this)[i][0].exp[0] >= 0)
				{
					CommonFactor = (*this)[i];
					if (i > 0) {

						// caso con esponente
						if ((*this)[i - 1].size() == 1 and
							(*this)[i - 1][0].exp[0] < 0)
						{
							(*this)[i - 1][0].coefficient++;
							this->erase(this->begin() + j);
						}

						// caso senza esponente
						else {
							int setK = 0;
							this->insert(this->begin() + i, { {2, modifier} });
							this->erase(this->begin() + j);
							for (size_t k = 0; k < this->size(); ++k)
								if ((*this)[k] == CommonFactor) {
									setK = k;
									break;
								}
							if ((*this)[i + 1] != CommonFactor)
								swap((*this)[i + 1], (*this)[setK]);
						}
					}

					// caso di eccezione
					else {
						this->push_front({ {2, modifier} });
						this->erase(this->begin() + j + 1);
					}
				}
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		if (this->count == 0) ret L"0";

		wstring output, exp, coeffstr{ L"1" };
		bool IsAModifier{ false };
		for (auto T : *this) {

			// caso di monomio modificatore
			if (!T[0].exp.empty()) if (T[0].exp[0] < 0) {
				if constexpr (is_same_v<T_int, long double>)
					exp = to_wstring((int)T[0].coefficient);
				else if constexpr (is_same_v<T_int, big>)
					exp = T[0].coefficient.str();
				IsAModifier = true;
				continue;
			}
			auto xout{ T.str(size) };

			// caso con elevamento a potenza
			if (IsAModifier) {
				xout = L"(" + xout + L")^" + exp;
				IsAModifier = false;
				output += xout;
				continue;
			}

			// caso coefficiente
			if (T == 1) {
				coeffstr = xout;
				continue;
			}

			// caso comune
			else if ((int)this->size() - (coeffstr != L"1") > 1)
				xout = L"(" + xout + L")";
			output += xout;
		}
		
		// aggiunta del denominatore
		if (!output.empty()) output = L'[' + output + L']';
		else if (LCM != 1) output.clear();
		else {
			ElabExponents(coeffstr);
			ret coeffstr;
		}
		if (LCM.fabs() != 1 or coeffstr != L"1") {

			// polinomio piccolo
			if constexpr (is_same_v<T_int, long double>) {
				if (LCM.fabs() != 1) output = L'/' + LCM.str() + L']' + output;
				output = coeffstr + output;
				if (LCM.fabs() != 1) output = L'[' + output;
			}

			// polinomio grande
			else if constexpr (is_same_v<T_int, big>) {
				if (!output.empty()) output += L'/';
				output = output + L'[' + LCM.str() + L']';
			}
		}
		if (LCM < 0) output = L'-' + output;

		// eliminazioni parentesi quadre se non sono necessarie
		else if (output.at(0) == L'[' and Last(output) == L']') {
			output.erase(0, 1);
			output.pop_back();
			if (output.find(L'[') != wstring::npos and
				output.find(L']') != wstring::npos) output = L'[' + output + L']';
		}

		if (BOOLALPHA) ElabExponents(output);
		ret output;
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
		for (const auto& value : vect) push_back(value);
	}

	void open()
	{
		polynomial<T_int> NewClass;
		for (size_t i = 0; i < this->count; ++i) NewClass << ToXV((*this)[i]);
		NewClass.open();
		this->clear();
		for (size_t i = 0; i < NewClass; ++i) this->push_back(To1V(NewClass[i]));
	}
	void close()
	{
		polynomial<T_int> NewClass;
		for (size_t i = 0; i < this->count; ++i) NewClass.push_back(ToXV((*this)[i]));
		NewClass.close();
		this->clear();
		for (size_t i = 0; i < NewClass; ++i) this->push_back(To1V(NewClass[i]));
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		polynomial<T_int> traduction;
		for (const auto& vector : *this) traduction << ToXV(vector);
		ret traduction.str(1);
	}
};

static polynomial<> ToXV(POLYNOMIAL<> vect)
{
	polynomial<> output;
	for (const auto& vector : vect) output << ToXV(vector);
	ret output;
}
static POLYNOMIAL<> To1V(polynomial<> vect)
{
	POLYNOMIAL<> output;
	for (const auto& vector : vect) output << To1V(vector);
	ret output;
}
static polynomial<> FromBigToDefault(polynomial<big> BigPolynomial)
{
	polynomial<> traduction;
	for (auto fact : BigPolynomial) {
		factor<> element;
		for (auto mon : fact) {
			monomial<> unity;
			unity.coefficient = mon.coefficient.Number();

			if (isnan(unity.coefficient))
				ret polynomial<>{ { { 1, tensor<int>(1, -2) } } };
			unity.exp = mon.exp;
			element << unity;
		}
		traduction << element;
	}
	ret traduction;
}

tensor_t PrimeNumbers;
_STD map<int, wstring> CalculatedData;

// altre classi
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
		if (PRINTN) {
			wcout << L"numero " << number << L":\n";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"in esadecimale è " << hex << uppercase;
			wcout << number << L'\n' << dec << nouppercase;
			if (number - 1 < PrimeNumbers.list_primes) {
				wcout << L"Numero Primo #" << number << L" = ";
				wcout << PrimeNumbers.list_primes[number - 1] << L'\n';
			}
		}

		// stampa dati cifre
		else if (number >= 10) {

			// stampa numero
			if (
				digit.digitSumRatioNum == 0 and
				digit.digitProductRatioNum == 0
				) ret;
			wcout << L"numero " << number << L":\n";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"in esadecimale è " << hex << uppercase;
			wcout << number << L'\n' << dec << nouppercase;
			if (number - 1 < PrimeNumbers.list_primes) {
				wcout << L"Numero Primo #" << number << L" = ";
				wcout << PrimeNumbers.list_primes[number - 1] << L'\n';
			}
			SetConsoleTextAttribute(hConsole, 13);

			// stampa somma cifre
			if (digit.digitSumRatioNum != 0) {
				wcout << L"la somma delle cifre è ";
				wcout << L'(' << digit.digitSumRatioNum;
				wcout << L'/' << digit.digitSumRatioDen;
				wcout << L")x\n";
			}

			// stampa prodotto cifre
			if (digit.digitProductRatioNum != 0) {
				wcout << L"il prodotto delle cifre è ";
				if (digit.digitProductRatioDen != 1) wcout << L'(';
				wcout << digit.digitProductRatioNum;
				if (digit.digitProductRatioDen != 1) {
					wcout << L'/';
					wcout << digit.digitProductRatioDen;
					wcout << L')';
				}
				wcout << L"x\n";
			}
		}

		// stampa stringa
		if (!code.empty()) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"il codice è <" << code << L">\n";
		}

		// stampa grado e sequenza
		if (degree != 0) {
			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"il grado è " << degree << L'\n';
			SetConsoleTextAttribute(hConsole, 3);
			wcout << L"la sequenza del grado è :\n(";
			for (size_t i = 0; i < sequence.size() - 1; ++i)
				wcout << sequence[i] << L", ";
			wcout << sequence.last() << L")\n";
		}

		if (!expression.empty()) {

			// se il numero è primo
			if (PrimeNumbers.is_prime[number]) {
				SetConsoleTextAttribute(hConsole, 240);
				wcout << L"il numero è primo";
				ResetAttribute();
				wcout << L'\n';
			}

			// altrimenti stampa scomposizione
			else {
				SetConsoleTextAttribute(hConsole, 11);
				wcout << L"la fattorizzazione è ";
				wcout << expression << L'\n';
				if (div.DivNumber != 1) {
					SetConsoleTextAttribute(hConsole, 8);

					// stampa numero divisori
					wcout << L"il numero dei divisori è ";
					wcout << div.DivNumber << L'\n';

					// stampa somma divisori
					wcout << L"la somma dei divisori è ";
					wcout << div.DivSum << L'\n';

					// stampa prodotto divisori
					wcout << L"il prodotto dei divisori è ";
					if (div.DivProduct != 1) wcout << div.DivProduct << L'\n';
					else wcout << div.Div_pr << L'\n';
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
			largest = left;
		if (right < n and this->at(right).number > this->at(largest).number)
			largest = right;
		if (largest != i) {
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
		for (auto& data : *this) data.printf();
	}
	void HeapSort()
	{
		int n = this->size();
		for (ptrdiff_t i = n / 2 - 1; i >= 0; --i) heapify(n, i);
		for (ptrdiff_t i = n - 1; i > 0; --i) {
			iter_swap(this->begin(), this->begin() + i);
			heapify(i, 0);
		}
	}
};

// oggetti
struct Console {
	wstring Text;
	WORD Attribute{ 15 };
	void print() const
	{
		SetConsoleTextAttribute(hConsole, Attribute);
		wcout << Text;
		ResetAttribute();
	}
};
tensor<Console> ConsoleText;
tensor<wstring> commands{
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
	L"dr",
	L"drc",
	L"drf",
	L"drt",
	L"ctn",
	L"cod",
	L"pol",
	L"alg",
	L"mtx",
	L"rnd"
};

#pragma endregion
#pragma region Declarations

static wstring Handler(wstring test);
static size_t Factorial(size_t n);
static size_t BinomialCoeff(size_t n, size_t k);
static ptrdiff_t Gcd(ptrdiff_t A, ptrdiff_t B);
template<typename T> static int Gcd(tensor<T> terms);
static ptrdiff_t intpow(ptrdiff_t base, int exp);
static wstring ConvertEnumToWString(switchcase Enum);
static switchcase ConvertWStringToEnum(wstring str);
static void ReassigneEnum(switchcase& option);
static void ClearArea(COORD WinCenter, COORD Dimensions);
static void PrintPFrame
(double deg, int sides, double radius, COORD WinCenter);
static void DrawFrame
(int arc, double __i, int centerX, int centerY, double DIM);
static void DrawCircleSquare(COORD CircleCenter);
static void DrawGraphFrame(
	FACTOR<> funct, coord shift, const COORD pos, double zoom,
	const short WindowLenght, const short WindowWidth
);
static void CS_CenterPrinter();
static void CS_CornerPrinter();
static void ProgressBar(long double ratio, double barWidth);
static long double WaitingScreen(auto begin, auto end);
static void PrintGraph(FACTOR<> funct, const coord position);
static wstring CTSuperScript(wchar_t input);
static wstring CFSuperScript(wstring script);
static void DeduceFromExponents(wstring& str);
static void GetFraction(wstring& numerator, wstring& denominator);
static wstring GetLine(bool ShowSuggestions = true, int sizemax = -1);
static wstring GetUserNum
(wstring txt, int low, ptrdiff_t high, bool ShowSuggestions);
static void SetDebug(wstring message, switchcase& opt, bool& Return,
	ptrdiff_t& LowerBound, ptrdiff_t& UpperBound, ptrdiff_t& datalenght
);
static void SendCtrlPlusMinus(bool plus);
static void MonitorConsoleSize(COORD min, atomic_bool& runMonitor);
static void UserInputThread();
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
template<typename T_int = long double>
static factor<T_int> PolynomialSum(factor<T_int> vect);
template<typename T_int = long double>
static factor<T_int> PolynomialMultiply(polynomial<T_int> Polynomial);
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
static void Simplify(
	polynomial<>& num, polynomial<>& den,
	int& ncoeff, int& dcoeff
);
static void Approximator(tensor<long double>& Equation, long double& root);
static tensor<wstring> EquationSolver(factor<> equation);
static wstring DisequationSolver
(polynomial<> Num, polynomial<> Den, bool ExpectedSign, bool CanBeNull = false);
static void PrintFraction
(
	int NC, int DC, int& LINE, bool WritePlus,
	polynomial<> numerator, polynomial<> denominator
);
static int OutputMatrix(
	tensor<tensor<double>> Matrix,
	COORD SelectedElement = { -1, -1 }
);
static tensor<tensor<double>> InputMatrix();
static void DisplayMatrices(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
);
static void DisplayMatrices(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B,
	tensor<tensor<double>> C
);
static tensor<tensor<double>> MatrixMultiply(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
);
template<typename T> static T Determinant(tensor<tensor<T>> mx);
FACTOR<> PolynomialMatrixDeterminant(tensor<tensor<FACTOR<>>> PolynomialMatrix);
static tensor<double> EigenValues(tensor<tensor<double>> mx);
static tensor<tensor<double>> EigenVectors
(tensor<tensor<double>> mx, tensor<double> EigenV = {});
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
static polynomial<> DecompPolynomial(switchcase& argc, wstring polynomial);
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
	
	// avvio
	QueryPerformanceFrequency(&ProgramFrequency);
	Beep(1'000, 50);
	Beep(1'000, 50);

	// // dichiarazione stringhe
	wstring simpledeg{ L"il PROGRAMMA calcola solo la codifica di un intero" };

	wstring simplefact{ L"il PROGRAMMA calcola solo la fattorizzazione di un intero" };

	wstring def_sct{ L"il PROGRAMMA calcola solo codifica e fattorizzazione" };

	wstring desimpledeg{ L"il PROGRAMMA calcola solo la codifica di una serie" };

	wstring desimplefact{ L"il PROGRAMMA calcola solo la fattorizzazione di una serie" };

	wstring defact_message{ L"il PROGRAMMA calcola la fattorizzazione di una serie" };
	defact_message += L"\ne numero, somma e prodotto dei divisori";

	wstring deg_message{ L"il PROGRAMMA calcola codice, sequenza e grado di una serie" };

	wstring fact_message{ L"il PROGRAMMA calcola la fattorizzazione di un intero" };
	fact_message += L"\ne numero, somma e prodotto dei divisori";

	wstring message{ L"il PROGRAMMA calcola codice, sequenza e grado di un intero" };

	wstring AllMessage{ L"il PROGRAMMA calcola \"tutti\" i dati di alcuni interi" };

	wstring de_digit{ L"il PROGRAMMA ricerca numeri con particolari" };
	de_digit += L" occorrenze di somma e prodotto cifre";

	wstring deg_digit{ L"il PROGRAMMA calcola cifre, codice, sequenza e grado" };

	wstring fact_digit{ L"il PROGRAMMA calcola cifre, fattorizzazione, e divisori" };

	wstring defact_digit{ L"il PROGRAMMA calcola tutti i dati, cifre comprese" };

	wstring vel;
	switchcase option;
	// //

	bool start{ true };
	bool LockPrimeNumbersInput{ false };
	ptrdiff_t global{ 1 };
	long double ComputationTime;
	size_t Timer{ 6'500'000'000 };
	while (true)
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
			wcout << L"0.9.8 ";
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
			wcout << L"inserire un numero tra compreso 10 milioni e 50 miliardi\n\n";

			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"*****.*****.*****.*****.******.*****.*****.*****.*****\n\n";
			SetConsoleTextAttribute(hConsole, 9);
			wcout << L"per bloccare l'input inserire 0\n";
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

			// casi 0 e 1
			else global = stoull(G);
			if (global < 10'000'000) {
				if (!start and global == 0) LockPrimeNumbersInput = true;
				if (start) global = 10'000'000;
				else global = 0;
			}
			ResetAttribute();

			// output del tempo e calcolo primi
			auto OldGlobalMax{ GlobalMax };
			if (global != 0) {
				DECLARE_TIME_POINT(begin);
				GlobalMax = global;
#ifndef BUGS
				SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS
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
		wcout << L"scegliere la modalità di calcolo::\n";
		SetConsoleTextAttribute(hConsole, 4);
		wcout << L"se stringa di un carattere:\n";
		wcout << L"\t'0' = blocca input numeri primi ~[~sempre]\n";
		wcout << L"\t'1' = sblocca input numeri primi\n";
		wcout << L"\t'x' = TORNA ALLA SCHERMATA START\n";
		wcout << L"\t'.' = fine programma [sempre]\n";
		SetConsoleTextAttribute(hConsole, 9);
		wcout << L"altrimenti:\n";
		wcout << L"\t\"rnd\" = casuale\n";
		wcout << L"\t\"ctn\" = da codice a numero\n";
		wcout << L"\t\"cod\" = da numero a espansione in serie e viceversa\n";
		wcout << L"\t\"pol\" = scomposizione polinomi\n";
		wcout << L"\t\"alg\" = scomposizione frazioni algebriche\n";
		wcout << L"\t\"mtx\" = scomposizione matrici\n";
		SetConsoleTextAttribute(hConsole, 11);
		wcout << L"oppure:\n";
		wcout << L"primi caratteri:\n";
		wcout << L"\t'c' = calcolo\n";
		wcout << L"\t'd' = debug\n";
		wcout << L"\t\"dr\" = debug ristretto\n";
		SetConsoleTextAttribute(hConsole, 14);
		wcout << L"caratteri seguenti:\n";
		wcout << L"\t'c' = solo codifica\n";
		wcout << L"\t'f' = scomposizione in fattori primi\n";
		wcout << L"\t\"cc\" = codifica, sequenza e grado\n";
		wcout << L"\t\"ff\" = fattoizzazione e dati dei divisori\n";
		wcout << L"\t\"cf\" = codifica e fattorizzazione\n";
		wcout << L"\t't' = tutti i dati\n";
		SetConsoleTextAttribute(hConsole, 6);
		wcout << L"solo per il debug ristretto:\n";
		wcout << L"\t'' = solo dati sulle cifre dei numeri\n";
		wcout << L"\t'c' = cifre, codifica, sequenza e grado\n";
		wcout << L"\t'f' = fattorizzazione, cifre e divisori\n";
		wcout << L"\t't' = tutti i dati compresi quelli sulle cifre\n";
		ResetAttribute();
		wcout << L"selezionando più operazioni, il tempo di calcolo aumenta\n";

		vel = GetLine(true, 10);
		option = ConvertWStringToEnum(vel);
		
		// gestione input numeri primi
		assigne:
		if (vel.size() == 1) {
			switch (vel.at(0)) {
			case L'0':
				LockPrimeNumbersInput = true;
				wcout << L"\ninput numeri primi bloccato";
				goto option_choice;
			case L'1':
				LockPrimeNumbersInput = false;
				wcout << L"\ninput numeri primi sbloccato";
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

			wcout << L"\nscegli opzioni:: (...)\n";
			vel = GetLine(true, 10);
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
			COORD MinLenght{ 50, 20 };

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

			case FactorPolynomial: Threading = true;
				calculator = thread(DecompPolynomial, ref(option), L"");
				monitor = thread(MonitorConsoleSize, MinLenght, ref(RunMonitor));
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
		\n\n   sei sicuro di voler terminare il programma?\
		\n\n   [riprova] per tornare all'inizio del programma\
		\n\n",
		L"Microsoft Visual C++ Runtime Library",
		MB_ABORTRETRYIGNORE | MB_ICONWARNING
	);

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

static wstring Handler(wstring test)
{
	if (test.find(L'.') != wstring::npos or test.find(L',') != wstring::npos)
		while (Last(test) == L'0') test.pop_back();
	if (Last(test) == L',' or Last(test) == L'.') test.pop_back();
	if (BOOLALPHA) ElabExponents(test);
	return test;
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

	ret (size_t)coeff;
}

// massimo comune divisore tra due interi
static ptrdiff_t Gcd(ptrdiff_t  A, ptrdiff_t  B)
{
	if (A < B) swap(A, B);
	while (B != 0) {
		int temp = B;
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
static wstring ConvertEnumToWString(switchcase Enum)
{
	auto it = enumToStringMap.find(Enum);
	if (it != enumToStringMap.end()) ret it->second;
}

// da stringa a enum
static switchcase ConvertWStringToEnum(wstring str)
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
	case 19: option = FactorPolynomial;
		ret;
	case 20: option = FactorFraction;
		ret;
	case 21: option = FactorMatrix;
		ret;
	}
}

#pragma endregion

// funzioni necessarie per disegnare
#pragma region BasicPrints

int RotAngle{ 270 }, PolygDegree{}, PolygonSides{ 4 };
int CircleCenterX, CircleCenterY, CircleRotDegreeAngle{};
bool DecreaseAngle{ true }, DecreaseWidth{ true };
double DWidth{ 1.9 };

const tensor<int> spectrum{ 9, 9, 9, 11, 11, 3, 3, 12, 4 };

// cancella un'area rettangolare di spazio
static void ClearArea(COORD WinCenter, COORD Dimensions)
{
	_GetCursorPos();
	DWORD written;
	COORD coord{
		(short)(WinCenter.X - Dimensions.X),
		(short)(WinCenter.Y - Dimensions.Y)
	};

	for (int y = WinCenter.Y; y <= WinCenter.Y + 2 * Dimensions.Y; ++y) {
		coord.Y = y - Dimensions.Y;
		FillConsoleOutputCharacter
		(hConsole, L' ', 2 * Dimensions.X + 1, coord, &written);
	}
}

// stampa il poligono
static void PrintPFrame
(double deg, int sides, double radius, COORD WinCenter)
{
	ResetAttribute();

	COORD coord{};
	const double DIM{ 1.9 };
	const int centerX{ WinCenter.X };
	const int centerY{ WinCenter.Y };
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
		WORD colour{ 15 };

		// generatore casuale numeri
		random_device rng;
		mt19937 gen(rng());
		uniform_int_distribution<> dis(0, 9);
		random_device Random;

		// generatore casuale colori
		mt19937 Gen(Random());
		uniform_int_distribution<> Dis(0, spectrum.size() - 1);
		int DisGen{ Dis(Gen) };

		// assegnazione colori
		for (size_t j = 0; j < spectrum; ++j) if (DisGen == j) colour = spectrum[j];

		// stampa
		SetConsoleTextAttribute(hConsole, colour);
		wcout << dis(gen);
	}
}

// gestisce la stampa del poligono e del cerchio
static void DrawCircleSquare(COORD CircleCenter)
{
	
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

// stampa il grafico di un polinomio
static void DrawGraphFrame(
	FACTOR<> funct, coord shift, const COORD pos, double zoom,
	const short WindowLenght, const short WindowWidth
)
{
	const double DIM{ 1.9 };

	COORD origin{
		WindowLenght + shift.X + pos.X,
		WindowWidth + shift.Y + pos.Y
	};
	ResetAttribute();

	// asse x
	if (origin.Y > pos.Y and origin.Y <= 2 * WindowWidth + pos.Y + 1) {
		SetConsoleCursorPosition(hConsole, { (short)(pos.X + 1), origin.Y });
		wcout << wstring(2 * WindowLenght + 1, L'-');
	}
	else origin.Y = -1;

	// asse y
	if (origin.X > pos.X and origin.X <= 2 * WindowLenght + pos.X + 1)
		for (short i = 1; i <= 2 * WindowWidth + 1; ++i)
		{
			SetConsoleCursorPosition(hConsole, { origin.X, (short)(pos.Y + i) });
			wcout << L'|';
		}
	else origin.X = -1;

	// origine degli assi
	if (origin.X != -1 and origin.Y != -1) {
		SetConsoleCursorPosition(hConsole, origin);
		wcout << L'+';
	}

	// output funzione
	SetConsoleTextAttribute(hConsole, 4);
	for (
		double x = (-WindowLenght - shift.X) / zoom;
		x <= (WindowLenght - shift.X) / zoom + 1;
		x += 1 / zoom
		)
	{
		// calcolo valori
		double fx{};
		for (size_t i = 0; i < funct; ++i)
			fx -= funct[i].coefficient * pow(x, funct[i].degree);
		fx /= DIM;

		// calcolo valori con traslazione e zoom
		short X{ (short)(x * zoom + shift.X + WindowLenght + pos.X) };
		short Y{ (short)(fx * zoom + shift.Y + WindowWidth + pos.Y) };
		
		// output punto
		if (Y > pos.Y and Y <= 2 * WindowWidth + pos.Y + 1 and
			X > pos.X and X <= 2 * WindowLenght + pos.X + 1)
		{
			SetConsoleCursorPosition(hConsole, { X, Y });
			wcout << L'*';
		}
	}
	ResetAttribute();

	// scrittura estremi asse y
	SetConsoleCursorPosition(hConsole, { (short)(2 * WindowLenght + 3), 0 });
	wcout << wstring(13, L' ');
	SetConsoleCursorPosition(hConsole, { (short)(2 * WindowLenght + 3), 0 });
	wcout << (WindowWidth + shift.Y) * DIM / zoom;
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght + 3), (short)(2 * WindowWidth + 2) }
	);
	wcout << wstring(13, L' ');
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght + 3), (short)(2 * WindowWidth + 2) }
	);

	wcout << (shift.Y - 2 - WindowWidth) * DIM / zoom;

	// scrittura estremi asse x
	SetConsoleCursorPosition(hConsole, { 0, (short)(2 * WindowWidth + 3) });
	wcout << wstring(13, L' ');
	SetConsoleCursorPosition(hConsole, { 0, (short)(2 * WindowWidth + 3) });
	wcout << (-WindowLenght - shift.X) / zoom;
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght), (short)(2 * WindowWidth + 3) }
	);
	wcout << wstring(13, L' ');
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght), (short)(2 * WindowWidth + 3) }
	);
	wcout << (WindowLenght + 2 - shift.X) / zoom;
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
		(csbi.dwSize.X - output.str().size()) / 2 - 1,
		csbi.dwSize.Y / 2 - 1
	};
	SetConsoleCursorPosition(hConsole, Cursor);
	wcout << output.str();
	sleep_for(seconds(1));

	ResetAttribute();
	ret delta * 1'000'000;
}

// crea una finestra con dei comandi per ridimensionare il grafico
static void PrintGraph(FACTOR<> funct, const coord position)
{

	// variabili
	double zoom{ 1 };
	coord shift{ 0, 0 };
	const short lenght{ 40 };
	const short width{ 12 };
#ifndef BUGS
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS

	// // output margini finestra
	SetConsoleTextAttribute(hConsole, 11);

	// linee orizzontali
	SetConsoleCursorPosition(hConsole, position);
	wcout << wstring(2 * lenght + 3, L'-');
	SetConsoleCursorPosition(
		hConsole,
		{ (short)position.X, (short)(2 * width + position.Y + 2) }
	);
	wcout << wstring(2 * lenght + 3, L'-');

	// linee verticali
	for (short i = 0; i <= 2 * width + 2; ++i)
	{
		SetConsoleCursorPosition(
			hConsole,
			{ (short)position.X, (short)(i + position.Y) }
		);
		wcout << L'|';
		SetConsoleCursorPosition(
			hConsole,
			{ (short)(2 * lenght + position.X + 2), (short)(i + position.Y) }
		);
		wcout << L'|';
	}
	// //
	DrawGraphFrame(funct, shift, position, zoom, lenght, width);

	while (true) {
		if (_kbhit()) {
			char move;

			// elaborazione input mosse
			do {
				move = tolower(_getch());
				switch (move) {
				case 'a': shift.X++;
					break;
				case 'd': shift.X--;
					break;
				case 'w': shift.Y++;
					break;
				case 's': shift.Y--;
					break;
				case 'r':
					shift = { 0, 0 };
					zoom = 1;
					break;
				case '+': zoom *= 1.3;
					break;
				case '-': zoom /= 1.3;
					break;
				case '\r':
					SetConsoleCursorInfo(hConsole, &cursor);
					SetConsoleCursorPosition(
						hConsole,
						{ 0, (short)(position.Y + width * 2 + 4) }
					);
					ret;
				}
			} while (
				move != 'a' and
				move != 'd' and
				move != 's' and
				move != 'w' and
				move != 'r' and
				move != '\r' and
				!issign(move)
				);

			// grafico
			ClearArea(
				{ (short)(lenght + position.X + 1), (short)(width + position.Y + 1) },
				{ lenght, width }
			);
			DrawGraphFrame(funct, shift, position, zoom, lenght, width);

		}
		if (!RunMonitor) {
			SetConsoleCursorPosition(
				hConsole,
				{ 0, (short)(position.Y + width * 2 + 4) }
			);
			ret;
		}
	}
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
static void ElabExponents(wstring& str)
{
	int J{ 1 };
	bool dobreak{ false };
	for (size_t I = 0; I < str.size(); ++I) {
		auto pointer{ I + 1 };
		if (str.at(I) == L'^' and I != str.size() - 1) {
			while (isdigit(str.at(pointer)))
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
}

// calcola la stringa originaria da quella con gli esponenti
static void DeduceFromExponents(wstring& str)
{
	for (ptrdiff_t i = str.size() - 1; i >= 0; --i) {
		auto script{ wstring(1, str.at(i)) };
		auto unscript{ CFSuperScript(script) };
		if (unscript != script)
			str.replace(i, i + 1, L"^" + unscript.at(0));
	}
}

#pragma endregion

// funzioni di input utente
#pragma region Input

// inputa una frazione algebrica
static void GetFraction(wstring& numerator, wstring& denominator)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	int diff{};
	size_t sizevel;
	numerator.clear();
	denominator.clear();
	wstring vel, command{ L"rnd" }, Num, Den;
	bool script{ true }, arrow{ false }, Continue{ false };
	bool IsTheCursorAtStart{ true };

	// aggiunta di spazio
	_GetCursorPos();
	auto START{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	_GetCursorPos();
	if (csbi.dwCursorPosition.Y >= START.Y)
		START.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
	SetConsoleCursorPosition(hConsole, START);

	_GetCursorPos();
	auto start{ csbi.dwCursorPosition };
	while (true) {
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
			auto S{ wstring(csbi.dwSize.X, L' ') + L'\r' };

			bool cond{
				c == L'\b' or c == L'\t' or c == L'\r' or c == L' '
				or c == L'K' or c == L'M' or c > 31 or c == -109
			};
			if (c == -32) arrow = true;
			if (c == 0) {
				Continue = true;
				continue;
			}
			if (Continue) {
				Continue = false;
				continue;
			}
			auto testN{ Num };
			auto testD{ Den };

			if (cond) switch (c) {

				// L'.' termina il programma
			case L'.':
				numerator = L".";
	#ifndef BUGS
				SetConsoleCursorInfo(hConsole, &cursorInfo);
	#endif // BUGS
				SetConsoleCursorPosition(hConsole, start);
				for (int a = 0; a < 4; ++a) wcout << S << L'\n';
				SetConsoleCursorInfo(hConsole, &cursor);
				ret;

				// L'\r' termina l'input
			case L'\r':
				start.Y += 4;
				SetConsoleCursorPosition(hConsole, start);
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
					auto first{ vel };
					auto second{ vel };
					first.erase(new_diff);
					second.erase(0, new_diff);
					first += c;
					vel = vel.substr(0, new_diff) + wstring(1, c)
						+ vel.substr(new_diff, vel.size() - 1);

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

			// ricerca suggerimento giusto
			int spaces = fabs(((int)Num.size() - (int)Den.size()) / 2);
			script = true;
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
	#ifndef BUGS
			SetConsoleCursorInfo(hConsole, &cursorInfo);
	#endif // BUGS
			if (Num.size() > Den.size()) {
				SetConsoleCursorPosition(hConsole, start);
				wcout << S;
				if (!script) {
					SetConsoleTextAttribute(hConsole, 6);
					wcout << command << L'\r';
					ResetAttribute();
				}
				wcout << Num << L'\n';
				wcout << S << wstring(Num.size(), L'-') << L'\n';
				wcout << S << wstring(spaces, L' ') << Den;
			}
			else {
				SetConsoleCursorPosition(hConsole, start);
				wcout << S;
				if (!script) {
					SetConsoleTextAttribute(hConsole, 6);
					wcout << wstring(spaces, L' ');
					wcout << command << L'\r';
					ResetAttribute();
				}
				wcout << wstring(spaces, L' ') << Num << L'\n';
				wcout << S << wstring(Den.size(), L'-') << L'\n';
				wcout << S << Den;
			}

			// reset riga
			if (c == L'H') IsTheCursorAtStart = true;
			else if (c == L'P') IsTheCursorAtStart = false;

			// reset cursore
			COORD startPos{ start };
			if (IsTheCursorAtStart) {
				startPos.X += Num.size();
				if (diff < Num.size()) startPos.X -= diff;
				else startPos.X = 0;
				if (Num.size() < Den.size()) startPos.X += spaces;
			}
			else {
				startPos.X += Den.size();
				if (diff < Den.size()) startPos.X -= diff;
				else startPos.X = 0;
				if (Num.size() > Den.size()) startPos.X += spaces;
				startPos.Y += 2;
			}
			SetConsoleCursorPosition(hConsole, startPos);
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		if (!RunMonitor) {
			numerator = L"0";
			denominator = L"";
			ret;
		}
	}
}

// inputa un polinomio
static wstring GetLine(bool ShowSuggestions, int sizemax)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// variabili
	int diff{}, maxsize{ sizemax };
	wstring vel, E_Vel, command{ L"rnd" };
	bool script{ true }, arrow{ false }, Continue{ false };

	while (true) {
		if (_kbhit()) {

			// controllo della dimensione della console
			if (sizemax == -1) {
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
			}

			char c = _getch();
			if (c != -32 and c != -109 and c < 0) continue;

			if (c == L'\r') break;
			auto Test{ E_Vel };

			// ignora alcuni caratteri
			bool cond{
				c == L'\b' or c == L'\t' or c == L'K' or
				c == L'M' or c == L' ' or c > 31 or c == -109
			};
			if (c == -32) arrow = true;
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
						+ vel.substr(new_diff, vel.size() - 1);
					break;
				}

				// frecce
				switch (c) {
				case L'K': if (diff < E_Vel.size()) diff++;
					break;
				case L'M': if (diff > 0) diff--;
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

			// stampa dei caratteri immessi
			if (vel.size() > maxsize) {
				vel.clear();
				E_Vel.clear();
				Velpart.clear();
				diff = 0;
				wcout << L'\r' << wstring(maxsize, L' ');
			}
			script = true;
#ifndef BUGS
			SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS
			if (ShowSuggestions and !vel.empty())

				// ricerca suggerimento giusto
				for (const auto& comma : commands) {
					command = comma;
					auto back{ command };
					if (back.size() == vel.size()) continue;
					if (back.size() > vel.size()) back.erase(vel.size());
					if (back == E_Vel) {
						SetConsoleTextAttribute(hConsole, 6);
						wcout << L'\r' << wstring(maxsize, ' ');
						wcout << L'\r' << command;
						ResetAttribute();

						wcout << L'\r' << E_Vel << L'\r' << Velpart;
						script = false;
						break;
					}
				}
			if (script) {
				wcout << L'\r' << wstring(maxsize, L' ');
				wcout << L'\r' << E_Vel << L'\r' << Velpart;
			}
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		if (!RunMonitor) ret L"0";
	}
	ret vel;
}

// inputa un numero dati valore minimo e valore massimo
static wstring GetUserNum
(wstring txt, int low, ptrdiff_t high, bool ShowSuggestions)
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
		check = GetLine(ShowSuggestions, 14);
		wcout << L'\n';
		for (ptrdiff_t i = check.size() - 1; i >= 0; --i) if (check.at(i) == L'\'')
			check.erase(i, 1);
		if (check == L"." or check.empty()) ret check;
		option = ConvertWStringToEnum(check);
		ReassigneEnum(option);
		if (option != NotAssigned) ret ConvertEnumToWString(option);

		// controllo
		if (regex_search(check, wregex(L"\\D"))) UserNum = 0;
		else UserNum = stoull(check);

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
	wcout << L"gli estremi dell'intervallo devono essere compresi";
	wcout << L" tra 1 e " << n_ << L"\n\n";

	// input e controllo valore iniziale
	ResetAttribute();
	txt = L"inserisci il valore di inizio della ricerca\n";
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
	txt = L"inserisci il valore finale della ricerca\n";
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
		L"ATTENIONE: il tempo rimanente non è accurato all'inizio"
	};
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
			wcout << L"\ntempo rimanente: " << stream.str() << L" [secondi]  ";
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
				while (true) {
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
	if (pol.empty()) ret L"il polinomio non può essere void";

	// controllo caratteri ammessi
	for (const auto& c : pol)
		if (!isalnum(c) and !issign(c) and c != L'^' and c != L' ' and c != L'/')
			ret L"il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	for (size_t i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1)))
			ret L"manca un monomio";
	if (!issign(pol.at(0))) pol = L'+' + pol;
	if (issign(Last(pol))) ret L"manca un monomio";

	// controllo esponenti in forma di numero
	for (size_t i = 0; i < pol.size() - 1; ++i)
		if (pol.at(i) == L'^' and !isdigit(pol.at(i + 1)))
			ret L"gli esponenti devono essere costanti";

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
			ret L"è possibile eseguire massimo una divisione per monomio";

		// controllo del denominatore
		if (part.find(L'/') != wstring::npos) {
			if (part.at(0) == L'/') ret L"manca un numeratore";
			if (Last(part) == L'/') ret L"manca un denominatore";
			if (!isdigit(Last(part))) ret L"denominatore non valido";
			while (isdigit(Last(part))) {
				if (part.empty()) break;
				part.pop_back();
				if (Last(part) == L'/') {
					part.pop_back();
					break;
				}
				if (!isdigit(Last(part))) ret L"denominatore non valido";
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
			ret L"manca la base rispetto al relativo esponente";

		// controllo variabili ripetute
		for (size_t i = 0; i < part.size(); ++i)
			for (size_t j = i + 1; j < part.size(); ++j)
				if (isalpha(part.at(i)) and part.at(i) == part.at(j))
					ret L"non è possibile ripetere le variabili nello stesso monomio";

		// controllo limite esponenti
		for (size_t i = 0; i < part.size() - 1; ++i) if (isdigit(part.at(i)))
			for (size_t j = i; j < part.size(); ++j) {
				if (j >= part.size()) break;
				if (!isdigit(part.at(j))) break;
				if (j - i >= 2) ret L"gli esponenti sono troppo grandi";
			}

		// controllo coefficienti corretti
		for (size_t i = 1; i < part.size(); ++i) if (
			isdigit(part.at(i)) and
			!isdigit(part.at(i - 1)) and
			part.at(i - 1) != L'^'
			)
			ret L"il coefficiente deve precedere il monomio";
	}

	ret L"";
}

// gestisce la convalidazione di un polinomio con le parentesi
static wstring PolynomialSyntaxDirector(wstring pol)
{
	
	// controllo asterischi
	if (pol.at(0) == L'*' or Last(pol) == L'*')
		ret L"manca un termine";
	for (ptrdiff_t i = pol.size() - 2; i > 0; --i) if (pol.at(i) == L'*') {
		if (pol.at(i - 1) == '(' or pol.at(i + 1) == ')')
			ret L"un asterisco non può essere racchiuso tra parentesi";
		if (pol.at(i - 1) == ')' or pol.at(i + 1) == '(') {
			pol.erase(i, 1);
			continue;
		}
		if (!isalnum(pol.at(i - 1)) or !isalnum(pol.at(i + 1)))
			ret L"asterisco nel punto sbagliato";
		pol.erase(i, 1);
	}

	// caso vuoto
	for (ptrdiff_t i = 0; i < (ptrdiff_t)pol.size() - 2; ++i)
		if (pol.at(i) == L'(' and pol.at(i + 1) == L')')
			ret L"il polinomio non può essere void";
	if (pol.empty()) ret L"il polinomio non può essere void";

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
			ret L"le parentesi sono invertite";
		}
		if (ParenthesisBalance >= 100) ret L"ci sono troppe parentesi";
	}
	if (ParenthesisBalance == 0) pol = copy;
	else if (!balanced) {
		balanced = true;
		copy = pol;
		goto balance;
	}
	else ret L"le parentesi sono sbilanciate";

	// rimozione spazi
	for (ptrdiff_t i = pol.size() - 1; i >= 0; --i)
		if (pol.at(i) == L' ' or pol.at(i) == L'\t') pol.erase(i, 1);

	// controllo caratteri non ammessi
	for (const auto& c : pol)
		if (!isalnum(c) and !issign(c)
			and c != L'(' and c != L')' and c != L'^' and c != L'/'
			)
			ret L"il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	bool error{ true };
	for (const auto& c : pol) if (!issign(c)) error = false;
	if (error) ret L"non è presente alcun monomio";
	for (size_t i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1))) ret L"manca un monomio";
	if (pol.at(0) == L'^') ret L"manca la base rispetto al relativo esponente";

	// controllo di ogni parte
	auto fact = FractPolynomial(pol);
	for (const auto& adder : fact) if (adder > 10)
		ret L"il polinomio è troppo grande";
	for (auto adder : fact) for (auto element : adder) {
		if (PolynomialSyntaxDirector(element).empty()) continue;

		bool exp{ element.size() > 1 and element.size() < 4 };
		if (exp) if (element.at(0) == L'^')
			for (size_t i = 1; i < element.size(); ++i) if (!isdigit(element.at(i)))
				ret L"gli esponenti devono essere costanti";
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
			ret L"le parentesi di delimitazione non possono essere doppie";
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
			ret L"le parentesi di delimitazione sono al contrario";
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
	wstring CharsAllowed{ L"0123456789+(_)." };
	bool LocError{ true };
	int ParenthesisBalance{}, count{};

	// eliminazione degli spazi e dei tab
	for (ptrdiff_t space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
			ToEvaluate.erase(space, 1);

	// ricerca del bilancio tra le parentesi
	for (size_t i = 0; i < ToEvaluate.size(); ++i) {
		switch (ToEvaluate.at(i)) {
		case '(': ParenthesisBalance++;
			break;
		case ')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) ret L"le parentesi sono invertite";
		if (ParenthesisBalance >= 100) ret L"ci sono troppe parentesi";
	}
	if (ParenthesisBalance != 0) ret L"le parentesi sono sbilanciate";
	
	// se la stringa è vuota
	if (ToEvaluate.empty()) ret L"la stringa è vuota";

	// se la stringa contiene caratteri non ammessi
	if (regex_search(ToEvaluate, wregex(L"[^\\d+()._]")))
		ret L"sono presenti dei caratteri non ammessi";

	// controllo sugli estremi
	if (ToEvaluate.at(0) == L'+') ret L"manca un monomio a inizio stringa";
	if (ToEvaluate.at(0) == L'0') ret L"un monomio non può essere null";
	if (ToEvaluate.at(0) == L')') ret L"le parentesi sono al contrario";
	if (Last(ToEvaluate) == L'+') ret L"manca un monomio alla fine della stringa";

	// controllo sulla non consecutività dei L'+'
	if (regex_search(ToEvaluate, wregex((L"\\+{2,}"))))
		ret L"manca un monomio al centro della stringa";

	// controlli sugli zeri
	if (regex_search(ToEvaluate, wregex(L"0{2,}")))
		ret L"le cifre null non possono essere consecutive";
	if (regex_search(ToEvaluate, wregex(L"\\.")))
		if (!regex_search(ToEvaluate, wregex(L"[_\\d]\\.[_1-9][_\\d]")))
			ret L"esponente a due cifre impostato in modo errato";
	if (regex_search(ToEvaluate, wregex(L"[\\r\\D]0")))
		ret L"un monomio non può essere null";

	mono = Fractioner(ToEvaluate);

	// per ogni monomio
	for (size_t indexof = 0; indexof < mono; ++indexof) {
		ptrdiff_t stackfinder{ -1 }, stickfinder{ -1 }, FindIndex{ -1 };
		bool stop{ false }, pass{ false };
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
		if (Last(stack) == L')') ret L"manca l'esponente di fianco a una parentesi";
		if (Last(stack) == L'(') ret L"le parentesi sono al contrario";
		if (stack.at(0) == L'(') {

			// controllo sulla necessità delle parentesi
			LocError = true;
			for (ptrdiff_t checkplus = 1; checkplus < FindIndex; ++checkplus)
				if (stack.at(checkplus) == L'+') LocError = false;
			if (LocError) ret L"ci sono troppe parentesi";

			stack.erase(0, 1);
			stack.erase(FindIndex - 1);
			auto message{ NumberCodeSyntax(stack) };
			if (!message.empty()) ret message;
		}
		else if (mono[indexof].at(0) == L')') ret L"le parentesi sono al contrario";
		else for (size_t check = 1; check < mono[indexof].size(); ++check) {
			if (mono[indexof].at(check) == L'(')
				ret L"l'esponente non può precedere una parentesi";
			if (mono[indexof].at(check) == L')')
				ret L"l'esponente non può precedere una parentesi";
		}
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
	bool UselessExponent{ false }, pass{ false };
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
	int sizeP = PrimeNumbers.list_primes.size();

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
		bool WhichWay{ false };

		if (M.at(0) != L'(') root = NumberConverter(1, M);
		
		// calcolo valori
		else root = NumberConverter(
			StringConverter(M.substr(1, FindIndex)),
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
		for (auto& text : ConsoleText) text.print();
		ConsoleText.clear();
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

		// output errori
		for (auto& text : ConsoleText) text.print();
		ConsoleText.clear();

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
		for (size_t i = 0; i < coeff.size(); ++i) {
			Coeff += coeff.at(i) - '0';
			if (i < coeff.size() - 1) Coeff *= 10;
		}
		if (coeff.empty()) Coeff = 1;
		if (mono.coefficient == -1) Coeff.invert();
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
			wstring start{ pol }, first{ pol }, last{ pol }, end{ pol };
			if (AssignedEnd) end.erase(0, endIndex + (pol.at(endIndex) == L')'));
			else end.clear();
			if (AssignedStart)
				start.erase(startIndex + (pol.at(startIndex) != L'('));
			else start.clear();
			if (AssignedEnd) last.erase(endIndex);
			last.erase(0, index + 1);
			first.erase(index);
			if (AssignedStart) first.erase(0, startIndex + 1);

			pol = start + L'(' + first + L")(" + last + L')' + end;
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
			int FirstDiv{ -1 }, SecondDiv{ -1 };

			for (size_t j = 0; j < Variables.size(); ++j) {
				int FD{ -1 }, SD{ -1 };

				if (DirectorSeq[j] > 0) FD = vect[i].exp[j] / DirectorSeq[j];
				if (KnownSeq[j] > 0) SD = vect[i].exp[j] / KnownSeq[j];

				if (FirstDiv == -1) FirstDiv = FD;
				else if (FirstDiv != FD and FD != -1) {
					keep = true;
					break;
				}

				if (SecondDiv == -1) SecondDiv = SD;
				else if (SecondDiv != SD and SD != -1) {
					keep = true;
					break;
				}
			}
			if (keep) break;
			if (FirstDiv == -1) FirstDiv = 0;
			if (SecondDiv == -1) SecondDiv = 0;

			if (FirstDiv + SecondDiv != size and KnownSeq != null)
			{
				keep = true;
				break;
			}
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
			else index = CorrectSize - vect[i].exp[StartIndex] / DirectorSeq[StartIndex];
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
	// marcamento dei monomi simili
	for (ptrdiff_t i = vect.size() - 1; i >= 0; --i)
		if (vect[i].coefficient == 0) vect[i].exp.clear();

	// rimozione
	auto it = remove(vect.begin(), vect.end(), monomial<T_int>{ 0, {} });
	vect.erase(it, vect.end());

	ret vect;
}

// moltiplica un polinomio (inverso della scomposizione)
template<typename T_int = long double>
static factor<T_int> PolynomialMultiply(polynomial<T_int> Polynomial)
{
	if (Polynomial.empty()) ret { {1, tensor(Variables.size(), 0)} };
	Polynomial.open();
	while (Polynomial > 1) {

		monomial<T_int> temp;
		factor<T_int> Temp;
		for (auto A : Polynomial[0])
			for (auto B : Polynomial[1]) {
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
		dividend = V1converter(PolynomialSum, dividend + divide);
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
		output << factor<>{ {(long double)GCD, exponents} };
		for (size_t i = 0; i < vect; ++i) {
			vect[i].coefficient /= GCD;
			for (size_t j = 0; j < Variables.size(); ++j)
				vect[i].exp[j] -= exponents[j];
		}
	}

	// totale
	if (abs(GCD) != 1 or positive_min) {
		output.clear();
		output << factor<>{ {(long double)GCD, exponents} } << vect;
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
	factor<> part_1{ vect[0], vect[1] };
	factor<> part_2{ vect[2], vect[3] };
	auto Part1{ Total(part_1) };
	auto Part2{ Total(part_2) };
	if (PolynomialSum<long double>(Part1.last() + Part2.last()).empty()) {
		if (Part1 == 1) swap(Part1, Part2);
		Part2 >> factor<>{ { -1, null } };
		for (size_t i = 0; i < Part2[1]; ++i) Part2[1][i].coefficient *= -1;
	}
	part_1 = Part1.last();
	part_2 = Part2.last();
	if (part_1 != part_2) ret outp;
	outp.clear();

	// riordinamento del totale
	polynomial<> mon_1;
	polynomial<> mon_2;
	if (Part1 == 1) mon_1 << factor<>{ monomial<>{1, null} };
	else mon_1 << Part1[0];
	if (Part2 == 1) mon_2 << factor<>{ monomial<>{1, null} };
	else mon_2 << Part2[0];
	mon_1 << part_1;
	mon_2 << part_2;

	// riordinamento del parziale
	part_1.SortByExponents();
	part_2 = PolynomialSum<long double>(mon_1[0] + mon_2[0]);
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
	outp << factor<>{ {(long double)exponent, modifier} };
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
	outp[0] << monomial<>{ -I * firstX, Cexps } << monomial<>{ (long double)I, Aexps };
	outp[1] << monomial<>{ -J * secondX, Cexps } << monomial<>{ (long double)J, Aexps };
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
		int SetRoot{}, Root;

		// calcolo della regola di ruffini sui coefficienti
		bool assigne{ true };
		for (int n = 1; n < CorrectSize; ++n) {

			// regola di ruffini
			tensor<long double> temp;
			for (const auto& root : PossibleRoots) {
				Root = root;
				do {

					// divisione polinomio per binomio
					temp = position;
					for (size_t i = 1; i < position; ++i)
						temp[i] = Root * temp[i - 1] + temp[i];

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
				for (int i = 0; i < CorrectSize; ++i) {
					if (position[CorrectSize - 1 - i] == 0) continue;
					tensor<int> VariableExp(Variables.size(), 0);
					size_t index{ Variables.size() };
					if (DirectorSeq[StartIndex] == 0) swap(DirectorSeq, KnownSeq);
					for (size_t j = StartIndex; j < Variables.size(); ++j) {
						if (DirectorSeq[j] == 0) {
							index = j;
							break;
						}
						VariableExp[j] = i * DirectorSeq[j];
					}
					for (size_t j = index; j < Variables.size(); ++j)
						VariableExp[j] = (CorrectSize - 1 - i) * KnownSeq[j];
					output[1] << monomial<>{
						(long double)position[CorrectSize - i - 1], VariableExp
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
	polynomial<> output;
	output << vect;
	if (vect != 3) ret output;
	vect.SortByDegree();
	auto A{ vect[0] };
	auto B{ vect[2] };

	// calcolo delle radici
	if (A.coefficient < 0 or B.coefficient < 0) ret output;
	double Sq_A = sqrt(A.coefficient);
	double Sq_B = sqrt(B.coefficient);

	// controllo sui quadrati
	if (!A.IsSquare()) ret output;
	if (!B.IsSquare()) ret output;
	for (size_t i = 0; i < Variables.size(); ++i) if (A.exp[i] % 4 != 0) ret output;
	
	// controllo sui gradi
	for (size_t i = 0; i < Variables.size(); ++i) {
		if (vect[1].exp[i] != A.exp[i] / 2 + B.exp[i] / 2) ret output;
		if (!integer(A.exp[i] / 4 + B.exp[i] / 4)) ret output;
	}

	// dichiarazioni
	monomial<> DiffSquare, Diffneg;
	for (size_t i = 0; i < Variables.size(); ++i)
		DiffSquare.exp << A.exp[i] / 4 + B.exp[i] / 4;
	int middleterm{ 2 * (int)Sq_A * (int)Sq_B }, sign;
	int CasePlus  =  middleterm - vect[1].coefficient;
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
	else ret output;
	Diffneg.coefficient = -DiffSquare.coefficient;
	Diffneg.exp = DiffSquare.exp;

	// calcolo gradi finali
	for (size_t i = 0; i < Variables.size(); ++i) {
		A.exp[i] /= 2;
		B.exp[i] /= 2;
	}

	// composizione di somma e differenza
	output << vect;
	output[0].clear();
	output[1].clear();

	output[0] << monomial<>{ Sq_A, A.exp } << DiffSquare << monomial<>{ Sq_B, B.exp };
	output[1] << monomial<>{ Sq_A, A.exp } << Diffneg << monomial<>{ Sq_B, B.exp };

	ret output;
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
		long double C{ sqrt(vect[4].coefficient)};
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
		bool AB2, AC2, BC2;
		bool start{ true };
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
			if (ABterm == monomial<>{} or ACterm == monomial<>{} or BCterm == monomial<>{})
				continue;
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
static void Simplify(
	polynomial<>& num, polynomial<>& den,
	int& ncoeff, int& dcoeff
)
{
	tensor<int> null(Variables.size(), 0);

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
	for (size_t i = 0; i < num.size(); ++i) if (num[i] == factor<>{ {1, null} })
		num.erase(num.begin() + i);
	for (size_t i = 0; i < den.size(); ++i) if (den[i] == factor<>{ {1, null} })
		den.erase(den.begin() + i);
}

// calcola una soluzione di un equazione con il metodo di newton-raphson
static void Approximator(tensor<long double>& Equation, long double& root)
{

	// traduzione
	FACTOR<> equation(Equation.size());
	for (ptrdiff_t i = Equation.size() - 1; i >= 0; --i) {
		equation[i].coefficient = Equation[i];
		equation[i].degree = Equation.size() - i - 1;
	}

	// calcolo derivata
	auto derivative{ equation };
	for (size_t j = 0; j < derivative; ++j)
		derivative[j].coefficient *= derivative[j].degree--;
	derivative--;

	// calcolo radice
	const double TOL = 0.000001;
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

	// risoluzione dell'equazione
	if (!equation.empty()) while (true) {

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

				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;

				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ to_wstring(half_root_sum - sqrt(delta_4));

				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;
			}

			// radici complesse
			else {
				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ complex(half_root_sum, sqrt(-delta_4)).c_str();
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;

				_push = factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != "
					+ complex(half_root_sum, -sqrt(-delta_4)).c_str();
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>{ { 1, VKnownSeq[0] } }.str();
				answer << _push;
			}
			ret answer;
		}

		// metodo di Newton-Raphson
		long double root{};
		Approximator(equation[0], root);
		auto push{
			factor<>{ { 1, VDirectorSeq[0] } }.str() + L" != " + to_wstring(root)
		};
		if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
			push += factor<>{ { 1, VKnownSeq[0] } }.str();
		answer << push;
	}

	// caso binomio
	if (Equation == 2) {
		int gcd{ Gcd(Equation) };
		Equation[0].coefficient /= gcd;
		Equation[1].coefficient /= gcd;

		for (size_t i = 0; i < Variables.size(); ++i) {
			int min{ ::min(Equation[0].exp[i], Equation[1].exp[i]) };
			Equation[0].exp[i] -= min;
			Equation[1].exp[i] -= min;
		}
		
		int coeff = Equation[0].coefficient;
		Equation[0].coefficient = 1;
		if (coeff < 0) coeff *= -1;
		else Equation[1].coefficient *= -1;

		wstring push{ factor<>{ Equation[0] }.str() + L" != " };
		push += factor<>{ Equation[1] }.str();
		if (coeff != 1) push += L" / " + to_wstring(coeff);
		ret { push };
	}
}

// calcola i valori di x sui quali la frazione algebrica ha un certo segno
static wstring DisequationSolver
(polynomial<> Num, polynomial<> Den, bool ExpectedSign, bool CanBeNull)
{

	// casi illegali
	if (Variables != L"x" or Num.empty() or Den.empty()) return L"";
	
	// calcolo delle radici
	bool repeat{ false };
	tensor<long double> roots;
	tensor<bool> ItsFromDenominator;
	for (const auto& fact : Num) {
		if (fact[0].exp[0] < 0) {
			repeat = true;
			continue;
		}
		auto solutions{ EquationSolver(fact) };

		// aggiunta delle radici del numeratore
		for (auto sol : solutions) if (sol.find(L'i') == wstring::npos)
		{
			sol.erase(0, 5);
			roots << stold(sol);
			ItsFromDenominator << false;
			if (repeat) {
				roots << stold(sol);
				ItsFromDenominator << false;
			}
		}
		repeat = false;
	}
	repeat = false;
	for (const auto& fact : Den) {
		if (fact[0].exp[0] < 0) {
			repeat = true;
			continue;
		}
		auto solutions{ EquationSolver(fact) };

		// aggiunta delle radici del denominatore
		for (auto sol : solutions) if (sol.find(L'i') == wstring::npos)
		{
			sol.erase(0, 5);
			roots << stold(sol);
			ItsFromDenominator << true;
			if (repeat) {
				roots << stold(sol);
				ItsFromDenominator << true;
			}
		}
		repeat = false;
	}
	
	// ordinamento delle radici
	for (size_t i = 0; i < roots; ++i) for (size_t j = i + 1; j < roots; ++j)
		if (roots[i] > roots[j])
		{
			swap(roots[i], roots[j]);
			swap(ItsFromDenominator[i], ItsFromDenominator[j]);
		}

	// calcolo segno
	bool InitialSign{ POS };
	for (auto& fact : Num) {
		fact.SortByExponents();
		if (fact[0].exp[0] < 0) InitialSign = !InitialSign;
	}
	for (auto& fact : Den) {
		fact.SortByExponents();
		if (fact[0].exp[0] < 0) InitialSign = !InitialSign;
	}

	// // costruzione risultato
	wstring output;
	bool condition{ ((InitialSign == (roots.size() % 2 == 0)) == ExpectedSign) };

	// parte iniziale
	if (condition) {
		output = L"x";
		CanBeNull and !ItsFromDenominator[0] ? output += L" <= " : output += L" < ";
		output += Handler(to_wstring(roots[0]));
		if (roots > 1) output += L" V ";
	}

	for (size_t i = condition; i < roots; i += 2) {

		// parte finale
		if (i + 1 == roots) {
			CanBeNull and !ItsFromDenominator[i] ?
				output += L"x >= " : output += L"x > ";
			output += Handler(to_wstring(roots[i]));
			break;
		}

		// parte centrale
		output += Handler(to_wstring(roots[i]));
		CanBeNull and !ItsFromDenominator[i] ?
			output += L" <= x" : output += L" < x";
		CanBeNull and !ItsFromDenominator[i + 1] ?
			output += L" <= " : output += L" < ";
		output += Handler(to_wstring(roots[i + 1]));
		if (i + 2 < roots) output += L" V ";
	}
	// //

	return output;
}

// stampa una frazione
static void PrintFraction
(
	int NC, int DC, int& LINE, bool WritePlus,
	polynomial<> numerator, polynomial<> denominator
)
{

	// aggiunta di spazio
	tensor<int> null(Variables.size(), 0);
	_GetCursorPos();
	auto start{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	_GetCursorPos();
	if (csbi.dwCursorPosition.Y > start.Y)
		start.Y -= 10 - csbi.dwCursorPosition.Y + start.Y;
	SetConsoleCursorPosition(hConsole, start);

	// calcolo numeratore
	long double root{};
	int I{ 1 }, Root;
	bool IsMinus{ false };
	wstring den_, num_;
	if (numerator == 1) if (numerator[0] == 1)
		if (numerator[0][0].exp == null)
			root = numerator[0][0].coefficient;
	if (numerator.empty()) numerator = polynomial<> { { { 1, null } } };

	// calcolo coefficienti e correzione
	if (root != 0) {
		while (true) {
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
	if (denominator >= 1) if (denominator[0] == 1)
		if (denominator[0][0].exp == null) HasACoefficient = true;
	if (HasACoefficient) denominator[0][0].coefficient *= CORRECTION_RATIO;
	else denominator >> factor<>{ monomial<>{ CORRECTION_RATIO, null } };

	// calcolo GCD e segni
	int gcd = Gcd(NC, DC);
	NC /= gcd;
	DC /= gcd;
	int Gcd{ 1 };
	if (root == 0) Gcd =
		::Gcd((int)numerator[0][0].coefficient, (int)denominator[0][0].coefficient);
	else Gcd = ::Gcd(Root, denominator[0][0].coefficient);
	denominator[0][0].coefficient /= Gcd;
	if (root != 0) Root /= Gcd;
	else numerator[0][0].coefficient /= Gcd;
	if (denominator[0][0] == monomial<>{ 1, null }) --denominator;
	else if (denominator[0][0] == monomial<>{ -1, null }) {
		--denominator;
		if (root == 0) numerator[0][0].coefficient *= -1;
		else Root *= -1;
	}
	if (root == 0) if (numerator[0][0] == monomial<>{ 1, null }) --numerator;
	if (root != 0) num_ = to_wstring(NC * Root);

	// calcolo numeratore
	if (root == 0) {
		num_ = numerator.str();

		if (num_ == L"0") num_.clear();
		else if (abs(NC) != 1 or numerator > 1) num_ = L'(' + num_ + L')';

		if (abs(NC) != 1) num_ = to_wstring(NC) + num_;
		if (num_.empty()) num_ = L"1";
		if (NC == -1) num_ = L'-' + num_;
	}

	// // calcolo denominatore
	den_.clear();
	auto tempden{ denominator.str() };
	if (tempden != L"1") den_ = tempden;
	
	if (den_ == L"0") den_.clear();
	else if (abs(DC) != 1 or denominator > 1) den_ = L'(' + den_ + L')';

	if (abs(DC) != 1) den_ = to_wstring(DC) + den_;
	if (den_.empty()) den_ = L"1";
	if (DC == -1) den_ = L'-' + den_;
	// //

	// aggiustamento segni
	bool both{ true };
	if (num_.at(0) == L'-' and den_.at(0) == L'-' and
		numerator == 1 and denominator == 1)
		if (numerator[0] == 1 and denominator[0] == 1)
		{
			num_.erase(0, 1);
			den_.erase(0, 1);
			both = false;
		}
	if (num_.at(0) == L'-' and numerator == 1 and both) if (numerator[0] == 1)
	{
		num_.erase(0, 1);
		IsMinus = !IsMinus;
		both = false;
	}
	if (den_.at(0) == L'-' and denominator == 1 and both) if (denominator[0] == 1)
	{
		den_.erase(0, 1);
		IsMinus = !IsMinus;
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

#pragma endregion

// funzioni relative alle matrici
#pragma region matrices

// stampa una matrice quadrata e restituisce la posizione del cursore
static int OutputMatrix(
	tensor<tensor<double>> Matrix,
	COORD SelectedElement
)
{
	
	// aggiunta di spazio
	_GetCursorPos();
	auto size{ Matrix.size() };
	auto begin{ csbi.dwCursorPosition };
	wcout << wstring(4 * size + 1, L'\n');
	_GetCursorPos();
	if (csbi.dwCursorPosition.Y >= begin.Y)
		begin.Y -= 4 * size + 1 - csbi.dwCursorPosition.Y + begin.Y;
	SetConsoleCursorPosition(hConsole, begin);
	csbi.dwCursorPosition = begin;

	// calcolo stringhe e trasposizione matrice stringhe
	tensor<tensor<wstring>> StrMatrix(size), StrDenominators(size);
	for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < Matrix[i]; ++j)
	{
		double element{ Matrix[j][i] };

		// elemento intero
		if (SelectedElement.Y >= 0 or integer(element)) {
			StrDenominators[i] << L"";
			StrMatrix[i] << to_wstring((int)element);
			continue;
		}

		// elemento decimale
		int I{ -1 };
		for (int i = 2; i < 1'000; ++i) if (integer(i * element)) {
			I = i;
			break;
		}
		if (I == -1) {

			// elemento sottoforma di numero decimale
			StrMatrix[i] << to_wstring(element);
			StrDenominators[i] << L"";
		}
		else {

			// elemento sottoforma di frazione
			StrMatrix[i] << to_wstring(int(element * I));
			StrDenominators[i] << to_wstring(I);
		}
	}

	// correzione lunghezza stringhe
	int sum{};
	for (size_t i = 0; i < size; ++i) {
		auto column{ StrMatrix[i] };
		auto denom{ StrDenominators[i] };
		int maxlenght{ 3 };

		// calcolo della lunghezza massima e correzione
		for (auto& num : column) if (num.size() > maxlenght) maxlenght = num.size();
		for (auto& den : denom) if (den.size() > maxlenght) maxlenght = den.size();
		for (auto& num : column) if (num.size() < maxlenght) {
			int TotalLenght = maxlenght - num.size();
			num = wstring(TotalLenght / 2, L' ') +
				num + wstring(TotalLenght - TotalLenght / 2, L' ');
		}
		for (auto& den : denom) if (den.size() < maxlenght) {
			int TotalLenght = maxlenght - den.size();
			den = wstring(TotalLenght / 2, L' ') +
				den + wstring(TotalLenght - TotalLenght / 2, L' ');
		}

		StrMatrix[i] = column;
		StrDenominators[i] = denom;
		sum += maxlenght;
	}
	sum += size * 2;

	// calcolo delle righe con e senza frazioni
	tensor<bool> HaveTheyFractions(size, false);
	for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j)
		if (StrDenominators[j][i].at(
			(StrDenominators[j][i].size() - 1) / 2) != L' '
			)
		{
			HaveTheyFractions[i] = true;
			break;
		}
	int row{};
	size_t index{};

	// iterazione e stampa matrice
	int line{};
	for (size_t i = 0; index <= 2 * size; ++i) {

		// inizio e fine matrice
		if (index == 2 * size) line = i;
		if (index == 0 or index == 2 * size) {
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
		if (index % 2 == 0) {
			wcout << wstring(sum, L' ') << L'|';
			index++;
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(
				hConsole, { begin.X, csbi.dwCursorPosition.Y }
			);
			continue;
		}
		if (HaveTheyFractions[(index - 1) / 2]) row++;
		if (row == 4) row = 1;

		// output elemento (la matrice delle stringhe è trasposta)
		for (size_t j = 0; j < size; ++j) {

			// evindenziazione cursore
			if (j == SelectedElement.X and (index - 1) / 2 == SelectedElement.Y)
				SetConsoleTextAttribute(hConsole, 12);

			// caso senza frazioni
			auto TempDenominator{ StrDenominators[j][(index - 1) / 2] };
			if (
				!HaveTheyFractions[(index - 1) / 2] or
				(row == 2 and TempDenominator.at(
					(TempDenominator.size() - 1) / 2) == L' ')
				)
			{
				wcout << StrMatrix[j][(index - 1) / 2];
				if (j == SelectedElement.X and (index - 1) / 2 == SelectedElement.Y)
				{
					SetConsoleTextAttribute(hConsole, 4);
					wcout << L'.';
				}
				else wcout << L' ';
			}

			// caso con almeno una frazione nella riga
			else switch (row) {

				// numeratori
			case 1:
				if (TempDenominator.at((TempDenominator.size() - 1) / 2) == L' ')
					wcout << wstring(
						StrMatrix[j][(index - 1) / 2].size() + 1, L' '
					);
				else wcout << StrMatrix[j][(index - 1) / 2] << L' ';
				break;

				// linee di frazione e numeri
			case 2:
				wcout << wstring(StrMatrix[j][(index - 1) / 2].size(), L'-');
				wcout << L' ';
				break;
				
				// denominatori non nulli
			case 3:
				if (TempDenominator.at((TempDenominator.size() - 1) / 2) == L' ')
					wcout << wstring(
						StrMatrix[j][(index - 1) / 2].size() + 1, L' '
					);
				else wcout << StrDenominators[j][(index - 1) / 2] << L' ';
				break;
			}

			ResetAttribute();
			wcout << L' ';
		}
		if (row == 0 or row == 3) index++;

		// fine riga
		wcout << L'|';
		csbi.dwCursorPosition.Y++;
		SetConsoleCursorPosition(hConsole, { begin.X, csbi.dwCursorPosition.Y });
	}

	// riposizionamento cursore
	if (SelectedElement.Y == -2) {
		line = max(line, (int)SelectedElement.X);
		begin.Y += line + 1;
	}
	if (SelectedElement.X == -1) begin.X += sum + 3;
	SetConsoleCursorPosition(hConsole, begin);

	ret line;
}

// inputa una matrice
static tensor<tensor<double>> InputMatrix()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));

	// calcolo posizione cursore
#ifndef BUGS
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS

	// inizializzazione
	tensor<tensor<bool>> Signs(2);
	tensor<tensor<double>> TheMatrix(2);
	Signs[0](2, POS);
	Signs[1](2, POS);
	TheMatrix[0](2, 0);
	TheMatrix[1](2, 0);
	OutputMatrix(TheMatrix, { 0, 0 });
	COORD IndexAccesser{};

	bool arrow{ false };
	wstring MatrixAtIndex;
	while (true) {
		if (_kbhit()) {
			char c = tolower(_getch());

			// casi speciali
			if (c == -32) {
				arrow = true;
				continue;
			}
			if (c <= 0) continue;
			if (arrow) {
				switch (c) {
				case L'h': c = L'w';
					break;
				case L'p': c = L's';
					break;
				case L'm': c = L'd';
					break;
				case L'k': c = L'a';
					break;
				}
				arrow = false;
			}

			// // scelta carattere
			size_t size;

			// casi che non modificano la matrice
			switch (c) {

				// wasd per cambiare l'elemento da modificare
			case L'w': IndexAccesser.Y = (IndexAccesser.Y - 1) % TheMatrix.size();
				break;
			case L's': IndexAccesser.Y = (IndexAccesser.Y + 1) % TheMatrix.size();
				break;
			case L'a': IndexAccesser.X = (IndexAccesser.X - 1) % TheMatrix.size();
				break;
			case L'd': IndexAccesser.X = (IndexAccesser.X + 1) % TheMatrix.size();
				break;
			}

			MatrixAtIndex = to_wstring(
				(int)TheMatrix[IndexAccesser.Y][IndexAccesser.X]
			);

			// casi che modificano la matrice
			switch (c) {

				// L'r' azzera il determinante
			case L'r':
				TheMatrix.last() = TheMatrix[TheMatrix.size() - 2];
				MatrixAtIndex = to_wstring(
					(int)TheMatrix[IndexAccesser.Y][IndexAccesser.X]
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
				if (MatrixAtIndex.size() == 1) {
					MatrixAtIndex = L"0";
					break;
				}
				MatrixAtIndex.pop_back();
				break;

				// ctrl + L'\b' cancella tutto
			case 127:
				MatrixAtIndex = L"0";
				Signs[IndexAccesser.Y][IndexAccesser.X] = POS;
				break;

				// L'+' aumenta la dimensione
			case L'>': if (TheMatrix.size() > 6) break;
				size = TheMatrix.size() + 1;
				TheMatrix(size);
				Signs(size);
				for (size_t i = 0; i < size; ++i) {
					TheMatrix[i](size, 0);
					Signs[i](size, POS);
				}
				break;

				// L'-' riduce la dimensione
			case L'<': if (TheMatrix.size() <= 2) break;
				TheMatrix--;
				for (auto& row : TheMatrix) row--;
				IndexAccesser.X %= TheMatrix.size();
				IndexAccesser.Y %= TheMatrix.size();
				break;

				// L'\r' invia la matrice
			case L'\r':
				_GetCursorPos();
				csbi.dwCursorPosition.Y += 2 * TheMatrix.size() + 1;
				SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
				SetConsoleCursorInfo(hConsole, &cursor);
				ret TheMatrix;

				// L'.' termina il programma
			case L'.':
				SetConsoleCursorInfo(hConsole, &cursor);
				ret {};

			default:

				// aggiunta di carattere numerico o segno
				if (isdigit(c) or (c == L'-' and MatrixAtIndex == L"0")
					and !Signs[IndexAccesser.Y][IndexAccesser.X])
				{
					if (Signs[IndexAccesser.Y][IndexAccesser.X]
						and MatrixAtIndex.at(0) != L'-')
						MatrixAtIndex = L'-' + MatrixAtIndex;
					if (c == L'-') Signs[IndexAccesser.Y][IndexAccesser.X] = NEG;
					if (MatrixAtIndex.size() > 4 + (MatrixAtIndex.at(0) == L'-'))
						break;
					if (MatrixAtIndex == L"0") MatrixAtIndex = L"";
					MatrixAtIndex += c;
				}
			}
			// //

			// stampa
			TheMatrix[IndexAccesser.Y][IndexAccesser.X] =
				MatrixAtIndex == L"-" ? 0 : stoi(MatrixAtIndex);
			_GetCursorPos();
			auto CursorPos{ csbi.dwCursorPosition };
			ClearArea(
				{ (short)(CursorPos.X + 30), (short)(CursorPos.Y + 8) }, { 30, 8 }
			);
			OutputMatrix(TheMatrix, IndexAccesser);
			SetConsoleCursorInfo(hConsole, &cursor);
		}
		if (!RunMonitor) {
			_GetCursorPos();
			csbi.dwCursorPosition.Y += 2 * TheMatrix.size() + 1;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			SetConsoleCursorInfo(hConsole, &cursor);
			ret tensor<tensor<double>>(
				TheMatrix.size(), tensor<double>(TheMatrix.size(), 0)
			);
		}
	}
}

// scrive due matrici
static void DisplayMatrices(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
)
{
	_GetCursorPos();

	// console ristretta
	if (csbi.dwSize.X <= 22 * A.size() + 2) {
		OutputMatrix(A, { 0, -2 });
		OutputMatrix(B, { 0, -2 });
		wcout << L'\n';
		ret;
	}

	// console di dimensioni corrette
	OutputMatrix(B, { (short)OutputMatrix(A), -2 });
	wcout << L'\n';
}

// scrive tre matrici
static void DisplayMatrices(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B,
	tensor<tensor<double>> C
)
{
	_GetCursorPos();

	// console ristretta
	if (csbi.dwSize.X <= 33 * A.size() + 3) {
		OutputMatrix(A, { 0, -2 });
		OutputMatrix(B, { 0, -2 });
		OutputMatrix(C, { 0, -2 });
		wcout << L'\n';
		ret;
	}

	// console di dimensioni corrette
	int line{ OutputMatrix(A) };
	line = max(line, OutputMatrix(B));
	OutputMatrix(C, { (short)line, -2 });
	wcout << L'\n';
}

// moltiplica due matrici
static tensor<tensor<double>> MatrixMultiply(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
)
{
	if (A % B) ret {};
	size_t size{ A.size() };
	tensor<tensor<double>> C(size);

	for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j) {
		double scalar_prod{};
		for (size_t k = 0; k < size; ++k) scalar_prod += A[i][k] * B[k][j];
		C[i] << scalar_prod;
	}
	
	ret C;
}

// calcola il determinante di una matrice con il teorema di laplace
template<typename T> static T Determinant(tensor<tensor<T>> mx)
{
	T det{};
	size_t s{ mx.size() };

	// casi speciali
	if (s == 1) ret mx[0][0];
	if (s == 2) ret mx[0][0] * mx[1][1] - mx[0][1] * mx[1][0];

	// caso generale
	for (size_t i = 0; i < s; ++i) {

		tensor<tensor<T>> MX(s - 1);
		for (size_t I = 0; I < s - 1; ++I) for (size_t J = 0; J < s; ++J)
		{
			if (i == J) continue;
			MX[I] << mx[I + 1][J];
		}
		
		det += intpow(-1, i) * mx[0][i] * Determinant(MX);
	}
	ret det;
}

// calcola il determinante di una matrice di polinomi
FACTOR<> PolynomialMatrixDeterminant(tensor<tensor<FACTOR<>>> PolynomialMatrix)
{

	FACTOR<> det;
	int s = PolynomialMatrix.size();

	// casi speciali del calcolo del determinante
	if (s == 1) ret PolynomialMatrix[0][0];
	if (s == 2) {
		auto addend1{
			PolynomialMultiply(
				{ ToXV(PolynomialMatrix[0][0]), ToXV(PolynomialMatrix[1][1]) }
			)
		};
		auto addend2{
			PolynomialMultiply(
				{ ToXV(PolynomialMatrix[0][1]), ToXV(PolynomialMatrix[1][0]) }
			)
		};
		for (auto& mon : addend2) mon.coefficient *= -1;
		ret To1V(PolynomialSum<long double>(addend1 + addend2));
	}

	// caso generale del calcolo del determinante
	for (size_t i = 0; i < s; ++i) {

		tensor<tensor<FACTOR<>>> MX(s - 1);
		for (size_t I = 0; I < s - 1; ++I) for (size_t J = 0; J < s; ++J)
		{
			if (i == J) continue;
			MX[I] << PolynomialMatrix[I + 1][J];
		}

		auto MiddleDet{ ToXV(PolynomialMatrixDeterminant(MX)) };
		if (MiddleDet != 0) {
			auto adder{
				PolynomialMultiply<long double>({
					ToXV(PolynomialMatrix[0][i]),
					MiddleDet
					})
			};
			for (auto& mon : adder) mon.coefficient *= -1;
			det = To1V(PolynomialSum<long double>(ToXV(det) + adder));
		}
	}

	ret det;
};

// calcola gli autovalori di una matrice
static tensor<double> EigenValues(tensor<tensor<double>> mx)
{

	// inizializzazione
	size_t s{ mx.size() };
	auto PolynomialMatrix{ tensor<tensor<FACTOR<>>>(s, tensor<FACTOR<>>(s)) };
	for (size_t i = 0; i < s; ++i) for (size_t j = 0; j < s; ++j)
		PolynomialMatrix[i][j] << MONOMIAL<>{ 0, (long double)mx[i][j] };
	for (size_t i = 0; i < s; ++i) PolynomialMatrix[i][i] >> MONOMIAL<>{ 1, -1 };
	
	// calcolo autovalori
	tensor<double> eigenvalues;
	charVariable = L'x';
	Variables = L"x";
	auto EigenStrings{
		EquationSolver(
			ToXV(PolynomialMatrixDeterminant(PolynomialMatrix))
		)
	};
	for (auto str : EigenStrings) {
		str.erase(0, str.find(L'=') + 1);
		if (str.find(L'i') == wstring::npos) eigenvalues << stod(str);
	}

	// ordinamento in ordine decrescente
	for (size_t i = 0; i < eigenvalues; ++i)
		for (size_t j = i + 1; j < eigenvalues; ++j)
			if (eigenvalues[i] < eigenvalues[j])
				swap(eigenvalues[i], eigenvalues[j]);

	ret eigenvalues;
}

// calcola gli autovettori di una matrice
static tensor<tensor<double>> EigenVectors
(tensor<tensor<double>> mx, tensor<double> EigenV)
{
	size_t size{ mx.size() };
	if (EigenV.empty()) EigenV = EigenValues(mx);
	if (EigenV.size() != size) ret {};
	tensor<double> result;
	tensor<tensor<double>> eigenvectors(size);

	// risoluzione sistemi lineari
	for (size_t i = 0; i < size; ++i) {

		// sottrazione autovalore e rimozione fine
		auto NewMx{ mx };
		for (size_t j = 0; j < size; ++j) NewMx[j][j] -= EigenV[i];
		for (size_t j = 0; j < size - 1; ++j) result << -NewMx[j].last();
		NewMx--;
		for (size_t j = 0; j < size - 1; ++j) NewMx[j]--;
		auto Det{ Determinant(NewMx) };

		// calcolo soluzioni e determinanti
		for (size_t j = 0; j < size - 1; ++j) {
			auto NewMatrix{ NewMx };
			for (size_t k = 0; k < size - 1; ++k) NewMatrix[k][k] = result[k];
			eigenvectors[i] << Determinant(NewMatrix) / Det;
		}
		eigenvectors[i] << 1;

		// normalizzazione autovettori
		double norm{};
		for (size_t j = 0; j < size; ++j)
			norm += eigenvectors[i][j] * eigenvectors[i][j];
		norm = sqrt(norm);
		if (isnan(norm)) ret {};
		for (size_t j = 0; j < size; ++j) eigenvectors[i][j] /= norm;
	}

	ret eigenvectors;
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
	wcout << L"il PROGRAMMA traduce una stringa di codice\n\n";
	SetConsoleTextAttribute(hConsole, 12);

	wcout << L"il codice non deve avere errori o verranno segnalati\n";
	wcout << L"il codice deve essere compreso tra <>\n";
	wcout << L"se sono presenti piu' caratteri '<', '>',\n";
	wcout << L"verranno considerati solo quelli che compaiono prima\n";
	wcout << L"unici caratteri non numerici ammessi: '(', ')', '+', '.' \n\n";

	SetConsoleTextAttribute(hConsole, 9);
	wcout << L"si indichino le cifre incognite con caratteri '_'\n";
	wcout << L"aggiungendo '$' come primo carattere\n";
	wcout << L"oppure '\\' o '/' senza <> non vengono mostrati gli errori\n\n";
	ResetAttribute();

	while (true)
	{
		do {
			message.clear();

			// input e controllo
			wcout << L"inserire una stringa (f = fine input)\n";
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

#ifndef BUGS
		SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS

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
			wcout << L"\nfine del calcolo\n\n";
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
		wcout << L"il PROGRAMMA calcola la codifica in serie di un numero\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		wcout << L"per codificare un numero inserire solo caratteri numerici\n";
		wcout << L"il numero deve essere compreso tra 1 e 10^50 - 1\n";
		wcout << L"per decodificare una stringa, aggiungere <> e ricordarsi\n";
		wcout << L"di aggiungere la base di decodifica rispettiva all'inizio\n";
		wcout << L"se non si aggiunge la base, la decodifica verrà effettuata per\n";
		wcout << L"tutte le basi da 2 a 16\n";
		ResetAttribute();
	}

	while (true)
	{
		if (!RetAccess) code = true;
		if (access)
		{
		input:

			// input
			SetConsoleTextAttribute(hConsole, 11);
			wcout << L"\ninserire un numero o una stringa (f = fine input)\n";
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
				coefficients << (number - quotient * base).Number();
				number = quotient;
			}
			coefficients << number.Number();
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
			wcout << L"espansione in base " << base << L": ";
			ResetAttribute();
			wcout << L'<' << output << L">\n";
		}

		// decodifica
		else {
			auto toevaluate{ ToEvaluate };

			// calcolo delle tetrazioni
			tensor<big> tetration{ 0, 1, Base };
			big last = Base;
			while (true) {
				if (last * log2(Base) >= 256) break;
				last = big(Base) ^ last;
				tetration << last;
			}

			// sostituzione cifre pure
			for (ptrdiff_t i = toevaluate.size() - 1; i >= 0; --i)
				if (isdigit(toevaluate.at(i))) {

					// controlli
					if (i != toevaluate.size() - 1)
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
						for (ptrdiff_t j = part.size() - 1; j >= 0; --j)
							if (part.at(j) == L'+') {
								auto NewPart{ part };
								part.erase(j);
								NewPart.erase(0, j + 1);
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
			wcout << L"input out of range\n";
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

	while (true)
	{
		// input e controllo
		SetConsoleTextAttribute(hConsole, 14);
		wstring txt{
			L"inserire un numero tra 2 e " + n_ + L" (1 = fine input)\n"
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
	ptrdiff_t input{}, LowerBound, UpperBound, datalenght;
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
		wcout << L"inserisci la stringa di istruzioni, il tipo è $_/_ #_/_\n";
		wcout << L"per indicare i rapporti somma cifre con numero";
		wcout << L" e prodotto cifre con numero\n";
		ResetAttribute();

		bool exit{ false };
		do {
			wcout << L"\ninserire la stringa\n";
			instr = GetLine(true, 20);
			if (instr == L".") {
				argc = Random;
				ret;
			}

			// rimozione spazi
			for (ptrdiff_t i = instr.size() - 1; i >= 0; --i)
				if (instr.at(i) == L' ' or instr.at(i) == L'\t') instr.erase(i, 1);

			// prima suddivisione
			wstring sum_instr{ instr }, prod_instr{ instr };
			bool do_divide_sum{ true }, do_divide_prod{ true };
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
#ifndef BUGS
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif // BUGS
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
					wcout << L"\ntempo rimanente: " << stream.str() << L" [secondi] ";
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
		wcout << L"\ntempo di calcolo = ";
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
		wcout << L"\ntempo di calcolo = ";
		DECLARE_TIME_POINT(end);
		wcout << 1'000 * static_cast<double>(end.QuadPart - begin.QuadPart)
			/ (ProgramFrequency.QuadPart);
		wcout << L"[ms]\n\n\n";
	}

	// termine
	wchar_t null{};
	PRINTN = true;
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	wcout << L"premi un tasto per continuare\t\t";
	argc = _getch() == L'.' ? Random : NotAssigned;
	ret;
}

// programma per scomporre i polinomi
static polynomial<> DecompPolynomial(switchcase& argc, wstring Polynomial)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));
	SetConsoleTextAttribute(hConsole, 14);

	// variabili
	wstring pol;
	polynomial<> HT;
	bool empty{ true }, Xout{ false }, input { Polynomial.empty() };

	// istruzioni
	if (input)
	{
		wcout << L"il PROGRAMMA scompone e disegna il grafico dei polinomi\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		wcout << L"per attivare gli esponenti in forma di apice ";
		wcout << L"scrivere noboolalpha\n";
		wcout << L"per disattivare gli esponenti sottoforma di apice ";
		wcout << L"scrivere boolalpha\n\n";
		wcout << L"per disegnare il grafico aggiungere '\\' all'inizio\n";
		wcout << L"è possibile eseguire addizioni, sottrazioni, moltiplicazioni\n";
		wcout << L"e potenze con polinomi molto grandi\n\n";
		SetConsoleTextAttribute(hConsole, 4);
		wcout << L"attenzione! il programma deduce i polinomi con le parentesi,\n";
		wcout << L"per calcolarne il valore aggiungere alla fine +1-1\n";
		wcout << L"per le potenze di numeri includere il numero tra parentesi\n\n";
		ResetAttribute();
	}

	do {
		bool draw{ false };
		if (!RunMonitor) goto RETURN;
		if (input)
		{
			empty = true;
			Xout = false;
			wstring Message;
			do {
				_GetCursorPos();
				bool wrong{ true };

				// input
				ResetAttribute();
				wcout << L"inserisci un polinomio in una o più variabili";
				wcout << L" (0 = fine input)\n";
				do {
					Polynomial = GetLine();
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
				if (Polynomial == L"noboolalpha") {
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
				Message = PolynomialSyntaxDirector(Polynomial);
				if (!Message.empty() and wrong) {
					SetConsoleTextAttribute(hConsole, 12);
					wcout << Message << L"!!\n\a";
					ResetAttribute();
				}

			} while (!Message.empty());
			if (Polynomial == L"0") break;
		}

		// traduzione dell'input utente
		polynomial<> BackT, Back_T{ HT };
		tensor<int> null;
		int size;
		auto bigHT{ GetMonomialsAssister(Polynomial) };

		// semplificazione numeratore denominatore
		tensor<big> ListOfCoefficients;
		for (auto fact : bigHT) for (auto mon : fact) if (mon.exp[0] >= 0)
			ListOfCoefficients << mon.coefficient;
		big G{ Gcd(ListOfCoefficients + tensor<big>{ LCM }) };
		for (auto& fact : bigHT) for (auto& mon : fact) if (mon.exp[0] >= 0)
			mon.coefficient /= G;
		LCM /= G;

		if (input) charVariable = Variables.at(0);
		HT = FromBigToDefault(bigHT);

		// se il polinomio troppo grande
		ptrdiff_t Coeff{ 1 }; 
		if (HT >= 1) if (HT[0] >= 1) if (HT[0][0].exp[0] == -2) {
			if (input) {
			overflow:
				SetConsoleTextAttribute(hConsole, 2);
				wcout << L"questo è il polinomio: " << bigHT.str() << L'\n';
				SetConsoleTextAttribute(hConsole, 64);
				wcout << L"il polinomio è troppo grande.";
				ResetAttribute();
				wcout << L'\n';
				goto EndOfDecomposition;
			}
			else ret{};
		}

		// se sono presenti dei coefficienti complessi
		if (Variables.find(L'i') != wstring::npos) {
			if (!input) ret{};

			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"questo è il polinomio: " << bigHT.str() << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"il polinomio contiene dei numeri complessi.";
			ResetAttribute();
			wcout << L'\n';
			goto EndOfDecomposition;
		}

		// risultato della somma
		null(Variables.size());
		null[0] = -1;
		if (HT.empty()) Polynomial = L"0";
		else Polynomial = HT.str();
		if (input) {
			SetConsoleTextAttribute(hConsole, 2);
			if (Polynomial.empty()) Polynomial = L"0";
			wcout << L"questo è il polinomio: " << Polynomial << L'\n';
		}

		// caso nullo
		size = HT.size();
		if (Polynomial == L"0") {
			ResetAttribute();
			wcout << "il polinomio non è scomponibile\n";
			goto EndOfDecomposition;
		}

		// raccoglimento totale
		Back_T = HT;
		HT.clear();
		for (const auto& polydata : Back_T) HT += Total(polydata);
		for (ptrdiff_t i = HT.size() - 1; i >= 0; --i)
			if (HT[i] == 1) if (HT[i][0].exp == tensor<int>(Variables.size(), 0))
			{
				Coeff *= HT[i][0].coefficient;
				HT.erase(HT.begin() + i);
				if (Coeff >= 2'147'483'647 or Coeff <= -2'147'483'647) {
					if (!input) ret{};
					goto overflow;
				}
			}

		// aggiunta del coefficiente corretto
		if (abs(Coeff) != 1) HT >> factor<>{ {
			(long double)Coeff, tensor<int>(Variables.size(), 0)
		} };
		else if (Coeff == -1) for (auto& mon : HT[0]) mon.coefficient *= -1;
		if (HT.empty()) HT = polynomial<>{ { {
			(long double)Coeff, tensor<int>(Variables.size(), 0)
		} } };

		// output raccoglimento totale
		HT.close();
		Polynomial = HT.str();
		if (HT != size and input) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"raccoglimento totale: " << Polynomial << L'\n';
			empty = false;
		}

		do {

			// raccoglimento parziale
			Back_T = HT;
			pol = Polynomial;
			auto polydata{ HT.last() };
			polydata.SortByDegree();
			HT--;
			HT += Partial(polydata);
			HT.close();
			Polynomial = HT.str();
			if (Back_T % HT and !Xout and input) {
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"raccoglimento parziale: " << Polynomial << L'\n';
				empty = false;
			}

			// potenza di binomio
			HT.close();
			Back_T = HT;
			HT.clear();
			for (const auto& a : Back_T) HT += Binomial(a);
			HT.close();
			Polynomial = HT.str();
			if (Back_T % HT and !Xout and input) {
				SetConsoleTextAttribute(hConsole, 3);
				wcout << L"potenza di binomio scomposta: ";
				wcout << Polynomial << L'\n';
				empty = false;
			}

			// trinomio speciale
			Back_T = HT;
			HT.clear();
			for (const auto& a : Back_T) HT += Trinomial(a);
			HT.close();
			Polynomial = HT.str();
			if (Back_T % HT and !Xout and input) {
				SetConsoleTextAttribute(hConsole, 9);
				wcout << L"trinomio speciale scomposto: ";
				wcout << Polynomial << L'\n';
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
			Polynomial = HT.str();

			// somma per differenza
			if (Back_T % HT and !Xout and input) {
				SetConsoleTextAttribute(hConsole, 5);
				wcout << L"differenza di quadrati scomposta: ";
				wcout << Polynomial << L'\n';
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
			Polynomial = HT.str();
			if (Back_T % HT and !Xout and input) {
				SetConsoleTextAttribute(hConsole, 6);
				wcout << L"applicazione della regola di ruffini: ";
				wcout << Polynomial << L'\n';
				empty = false;
			}
		} while (Polynomial != pol);

		// completamento del quadrato
		Back_T = HT;
		HT.clear();
		for (const auto& a : Back_T) HT += CompleteTheSquare(a);
		HT.close();
		Polynomial = HT.str();
		if (Back_T % HT and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"completamento del quadrato: " << Polynomial;
			ResetAttribute();
			wcout << L'\n';
			empty = false;
		}

		// quadrato del trinomio
		Back_T = HT;
		HT.clear();
		for (const auto& a : Back_T) HT += TrinomialSquare(a);
		
		HT.close();
		Polynomial = HT.str();
		if (Back_T % HT and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"quadrato di trinomio scomposto: " << Polynomial;
			ResetAttribute();
			wcout << L'\n';
			empty = false;
		}

		// caso vuoto
		if (empty and !Xout and input) {
			ResetAttribute();
			wcout << L"il polinomio non è scomponibile";
			wcout << L" con i metodi standard\n";
		}

		// caso impossibile
		if (Xout and input) {
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"X_OUT_OF_RANGE";
			ResetAttribute();
			wcout << L'\n';
		}

		if (input and draw) {

			// controllo dimensione console
			if (Variables.size() != 1) continue;
			_GetCursorPos();
			if (csbi.dwSize.X <= 94 or csbi.dwSize.Y <= 26) continue;

			// aggiunta di spazio
			wcout << wstring(csbi.dwSize.Y - 1, L'\n');
			SetConsoleCursorPosition(hConsole, { 0, 0 });
			PrintGraph(To1V(PolynomialMultiply(HT)), { 0, 0 });
		}

	EndOfDecomposition: if (!input) break;

	} while (input);

	// invio del segnale per terminare i thread
	argc = NotAssigned;
RETURN:
	if (input) {
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
	wcout << L"il PROGRAMMA scompone e semplifica le frazioni algebriche\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"per attivare gli esponenti in forma di apice ";
	wcout << L"scrivere noboolalpha\n";
	wcout << L"per disattivare gli esponenti sottoforma di apice ";
	wcout << L"scrivere boolalpha\n";
	ResetAttribute();

	while (true)
	{
		// input della frazione algebrica
		wstring numerator, denominator;
		bool No1{ false }, No2{ false }, skip{ false };
	insert:
		do {

			// input
			ResetAttribute();
			bool wrong{ true };
			wcout << L"\ninserisci una frazione algebrica (0 = fine input)\n\n";
			GetFraction(numerator, denominator);
			if (numerator.empty()) numerator = L"0";
			if (denominator.empty()) denominator = L"1";

			if (numerator == L".") {
				argc = Random;
				goto RETURN;
			}
			argc = ConvertWStringToEnum(numerator);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(numerator.c_str());
				goto RETURN;
			}

			// esponenti con gli apici
			if (numerator == L"noboolalpha") {
				BOOLALPHA = true;
				wrong = false;
			}
			if (numerator == L"boolalpha") {
				BOOLALPHA = false;
				wrong = false;
			}
			if (!wrong) wcout << numerator << L'\n';

			// controllo
			No1 = !PolynomialSyntaxDirector(numerator).empty();
			No2 = !PolynomialSyntaxDirector(denominator).empty()
				or denominator == L"0";
			bool IsTheVariableSet{ false };

			// messaggi di errore
			if (numerator == L"0") break;
			if ((No1 or No2) and wrong) {
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"quella non è una frazione algebrica\n\a";
				ResetAttribute();
			}

			// denominatore nullo
			if (!No1 and !No2) if (GetMonomialsAssister(denominator)
				== polynomial<big>{ factor<big>{} })
			{
				No2 = true;
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"il denominatore non può essere nullo\n\a";
				ResetAttribute();
			}

			// numeratore nullo
			if (!No1 and !No2 and numerator != L"0")
				if (GetMonomialsAssister(numerator)
					== polynomial<big>{ factor<big>{} }) numerator = L"0";

		} while (No1 or No2);
		if (numerator == L"0") break;

		// scomposizione polinomi
		switchcase use;
		CORRECTION_RATIO = 1;
		auto N_{ DecompPolynomial(use, numerator) };
		big DenMultiplier = LCM;
		auto savx{ Variables };
		auto D_{ DecompPolynomial(use, denominator) };
		big NumMultiplier = LCM;
		big GCD{ Gcd(NumMultiplier, DenMultiplier) };
		NumMultiplier /= GCD;
		DenMultiplier /= GCD;
		auto nummultiplier{ NumMultiplier.Number() };
		auto denmultiplier{ DenMultiplier.Number() };
		
		if (!(N_ and D_) or isnan(nummultiplier) or isnan(denmultiplier)) {
			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"input overflow: prova a inserire valori più piccoli";
			ResetAttribute();
			wcout << L'\n';
			goto insert;
		}

		// aggiunta di spazio nella memoria
		auto oldV{ Variables };
		for (const auto& ch : Variables) if (savx.find(ch) == wstring::npos)
			savx += ch;
		Variables = savx;
		for (auto& fac : N_) for (auto& mon : fac) mon.exp(Variables.size(), 0);
		for (auto& fac : D_) for (auto& mon : fac) mon.exp(Variables.size(), 0);
		auto temp(D_);
		for (size_t i = 0; i < D_; ++i) for (size_t j = 0; j < temp[i]; ++j)
			for (size_t k = 0; k < Variables.size(); ++k)
				temp[i][j].exp[k] = oldV.find(Variables.at(k)) != wstring::npos ?
				D_[i][j].exp[oldV.find(Variables.at(k))] : 0;
		D_ = temp;
		
		// backup
		auto NumBackup{ N_ };
		auto DenBackup{ D_ };
		int NCOEFF{ 1 }, DCOEFF{ 1 };
		bool _Nchangx{ false }, _Dchangx{ false };

		// semplificazione fattori
		Simplify(N_, D_, NCOEFF, DCOEFF);
		if (N_ != NumBackup) _Nchangx = true;
		if (D_ != DenBackup) _Dchangx = true;
		NCOEFF *= nummultiplier;
		DCOEFF *= denmultiplier;
		LCM = 1;

		// aggiornamento dati globali
		auto test{ N_ };
		if (!(N_ or D_)) charVariable = L'x';
		else if (N_.empty()) test = D_;
		if (N_ or D_) for (size_t i = 0; i < Variables.size(); ++i)
			if (test[0][0].exp[i] != 0) charVariable = Variables.at(i);

		// correzione fattori
		auto NScomp{ To1V(N_) };
		auto DScomp{ To1V(D_) };
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
		int Det;
		tensor<tensor<int>> Matrix;
		tensor<int> results;
		tensor<double> roots;
		FACTOR<> Quotient;
		FACTOR<> Rest;
		if (N_ != ToXV(NScomp) or D_ != ToXV(DScomp)) {
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
			Det = Determinant(Matrix);
		}
		if (!skip) for (size_t i = 0; i < results; ++i) {
			tensor<tensor<int>> MX{ Matrix };
			MX[i] = results;
			roots << (double)Determinant(MX) / Det;
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
		int Idx{};

		// push condizioni di esistenza
		COORD cursorPos;
		for (const auto& d : DenBackup) {
			auto Ctemp_{ EquationSolver(d) };
			for (const auto& i : Ctemp_) C_E_ << i;
		}

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
		auto DiseqSol{ DisequationSolver(N_, D_, POS, true) };
		if (!DiseqSol.empty()) {
			SetConsoleTextAttribute(hConsole, 11);
			wcout << L"\nA(x) >= 0  ->  " << DiseqSol << L'\n';
		}

		// output frazioni
		SetConsoleTextAttribute(hConsole, 10);
		wcout << L"\nla scomposizione è: ";
		SetConsoleTextAttribute(hConsole, 12);
		bool ShowPlus{ false };
		int lines{};

		// caso generale, frazione scomposta
		polynomial<> TopPart = HasMoreVariables ? N_ : ToXV(NScomp);
		polynomial<> BottomPart = HasMoreVariables ? D_ : ToXV(DScomp);
		bool NewPrint{ false };
		if (!skip) {
			wcout << L"\n\n";
			for (size_t i = 0; i < denominators; ++i) {
				PrintFraction(
					NCOEFF,
					DCOEFF,
					lines,
					ShowPlus,
					{ { { roots[i], tensor<int>(Variables.size(), 0) } } },
					ToXV(denominators[i])
				);
				ShowPlus = true;
			}
			wcout << L"\n\n";
			goto EndOfStatement;
		}

		// caso di frazione semplificata ma non scomposta
		if (!BottomPart.empty()) {
			if (BottomPart > 1 or BottomPart[0] > 1 or
				BottomPart[0][0].exp != tensor<int>(Variables.size(), 0))
			{
				_GetCursorPos();
				csbi.dwCursorPosition.Y--;
				SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
				PrintFraction(
					NCOEFF,
					DCOEFF,
					lines,
					false,
					TopPart,
					BottomPart
				);
				wcout << L"\n\n";
			}
			else NewPrint = true;
		}
		else NewPrint = true;

		// caso di denominatore coefficiente
		if (abs(DCOEFF) != 1 and !TopPart.empty() and NewPrint) {
			_GetCursorPos();
			csbi.dwCursorPosition.Y--;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			PrintFraction(
				NCOEFF,
				DCOEFF,
				lines,
				false,
				TopPart,
				{ { monomial<>{ 1, tensor<int>(Variables.size(), 0) } } }
			);
			wcout << L"\n\n";
		}

		// caso di frazione normale
		else if (abs(DCOEFF) != 1 and NScomp.empty() and NewPrint) {
			_GetCursorPos();
			csbi.dwCursorPosition.Y--;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			PrintFraction(
				NCOEFF,
				DCOEFF,
				lines,
				false,
				{ { monomial<>{ 1, tensor<int>(Variables.size(), 0) } } },
				{ { monomial<>{ 1, tensor<int>(Variables.size(), 0) } } }
			);
			wcout << L"\n\n";
		}

		// caso costante
		else if (NScomp.empty() and NewPrint) {
			if (DCOEFF == -1) NCOEFF *= -1;
			wcout << L' ' << NCOEFF;
		}

		// caso fattore
		else if (NScomp == 1 and NewPrint) {
			auto output = HasMoreVariables ? N_[0].str() : NScomp[0].str();
			if (BOOLALPHA) ElabExponents(output);
			if (NScomp[0] > 1 and NCOEFF != 1) output = L'(' + output + L')';
			if (abs(NCOEFF) != 1) output = to_wstring(NCOEFF) + output;
			if (NCOEFF * DCOEFF == -1) output = L'-' + output;
			wcout << L' ' << output;
		}

		// caso polinomio
		else if (NewPrint) {
			wcout << L' ';
			HasMoreVariables ? wcout << N_.str() : wcout << NScomp.str();
		}

	EndOfStatement:

		// reset cursore
		_GetCursorPos();
		auto cursorP{ csbi.dwCursorPosition };
		cursorP.X = lines;
		cursorP.Y--;
		SetConsoleCursorPosition(hConsole, cursorP);

		// output polinomio di resto
		if (!skip) for (const auto& a : Quotient) {
			auto rest{ POLYNOMIAL<>{ { a } } };
			if (a.coefficient == 0) continue;

			// output normale
			if (integer(a.coefficient / CORRECTION_RATIO)) {
				rest[0][0].coefficient /= CORRECTION_RATIO;
				auto pol{ rest.str() };
				if (BOOLALPHA) ElabExponents(pol);
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
					{ { monomial<>{
						a.coefficient,
						tensor<int>(Variables.size(), 0) 
					} } },
					{ { monomial<>{1, tensor<int>(Variables.size(), 0)} } }
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
					if (BOOLALPHA) ElabExponents(power);
				}
				wcout << L' ' << power << L' ';
			}
		}
		wcout << L"\n\n";
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
	wcout << L"il PROGRAMMA scompone le matrici\n";
	wcout << L"e calcola determiante, autovalori e autovettori\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"sono ammesse solo matrici quadrate da 2x2 a 7x7\n";
	wcout << L"premi r per copiare la penultima riga (azzera il determinante)\n\n";
	ResetAttribute();
	tensor<tensor<double>> matrix, Mx;

	while (true)
	{
		// input
		ResetAttribute();
		wcout << L"inserisci una matrice, usa wasd per cambiare elemento\n";
		matrix = InputMatrix();
		size_t size{ matrix.size() };
		if (size == 0) {
			argc = Random;
			goto RETURN;
		}
		if (matrix == tensor<tensor<double>>(size, tensor<double>(size, 0)))
			break;
		wcout << L'\n';
		Mx = matrix;

		// calcolo matrice di permutazione
		auto Id{ tensor<tensor<double>>(size, tensor<double>(size, 0)) };
		for (size_t i = 0; i < size; ++i) Id[i][i] = 1;
		auto permutator{ Id };
		for (size_t i = 0; i + 1 < size; ++i) {

			int max = Mx[size - 1][i], IndexofMax = size - 1;
			for (ptrdiff_t j = size - 2; j >= i; --j) if (Mx[j][i] > max) {
				max = Mx[j][i];
				IndexofMax = j;
			}

			if (IndexofMax != i) {
				swap(Mx[IndexofMax], Mx[i]);
				swap(permutator[IndexofMax], permutator[i]);
			}
		}

		// trasposizione della matrice di permutazione
		auto NewPermutator{ tensor<tensor<double>>(size) };
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
			wcout << L"decomposizione PLU:\n";
			DisplayMatrices(permutator, lower, upper);
		}

		// algoritmo di givens
		Mx = matrix;
		auto ortogonal{ Id };
		Break = false;
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = i + 1; j < size; ++j) if (Mx[j][i] != 0) {

				double norm{ hypot(Mx[j][i], Mx[j - 1][i]) };
				if (norm == 0) {
					Break = true;
					break;
				}
				double cosine{ Mx[j - 1][i] / norm }, sine{ Mx[j][i] / norm };

				auto givens{ Id };
				givens[i][i] = cosine;
				givens[i][j] = sine;
				givens[j][i] = -sine;
				givens[j][j] = cosine;

				Mx = MatrixMultiply(givens, Mx);
				ortogonal = MatrixMultiply(ortogonal, givens);
			}
			if (Break) break;
		}

		// decomposizione QR
		if (!Break) {
			wcout << L"decomposizione QR:\n";
			DisplayMatrices(ortogonal, Mx);
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
		auto lowerT{ tensor<tensor<double>>(size) };
		if (!Break) for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size; ++j) lowerT[i] << lower[j][i];

		// output decomposizione
		if (!Break) {
			wcout << L"decomposizione di cholesky:\n";
			DisplayMatrices(lower, lowerT);
		}

		// calcolo autovalori
		Mx = matrix;
		auto MxT{ Id };
		for (size_t i = 0; i < size; ++i) for (size_t j = 0; j < size; ++j)
			MxT[i][j] = Mx[j][i];
		auto Mx_MxT{ MatrixMultiply(Mx, MxT) };
		auto MxT_Mx{ MatrixMultiply(MxT, Mx) };
		auto EigenV{ EigenValues(Mx_MxT) };

		// calcolo matrici U, V e sigma
		auto sigma{ Id };
		Break = EigenV.size() != size;
		tensor<tensor<double>> U, V;
		if (!Break) {
			for (size_t i = 0; i < size; ++i) sigma[i][i] = sqrt(EigenV[i]);
			U = EigenVectors(Mx_MxT, EigenV);
			V = EigenVectors(MxT_Mx);
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
			wcout << L"decomposizione a valori singolari:\n";
			DisplayMatrices(U, sigma, V);
		}

		// output dati della matrice
		auto maindet{ Determinant(matrix) };
		wcout << L"Determinante: " << maindet << L'\n';
		auto eigenvalues{ EigenValues(matrix) };
		wcout << L"Autovalori reali: " << eigenvalues.str() << L'\n';
		auto eigenvectors{ EigenVectors(matrix, eigenvalues) };
		if (eigenvectors == size) {
			wcout << L"Autovettori reali: \n";
			for (auto vector : eigenvectors) wcout << vector.str() << L'\n';
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
			auto newdet{ Determinant(NewMatrix) };
			if (newdet == 0) continue;

			// calcolo soluzioni
			for (size_t i = 0; i < size - 1; ++i) {
				Mx = NewMatrix;
				for (size_t j = 0; j < size - 1; ++j)
					Mx[j][i] = matrix[j][matrix.size() - 1];
				solutionList << Determinant(Mx) / newdet;
			}

			// output risultati
			wcout << L"soluzioni del sistema lineare: \n";
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

// file natvis 54 righe
// fine del codice