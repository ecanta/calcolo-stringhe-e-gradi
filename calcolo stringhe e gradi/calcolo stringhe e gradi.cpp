// inizio del codice
#pragma region Files

// pragma
#pragma once

// pragma warning
#pragma	warning (disable : 4101) // variabile locale senza riferimenti
#pragma	warning (disable : 4244) // conversione, possibile perdita di dati
#pragma	warning (disable : 4267) // conversione, possibile perdita di dati
#pragma	warning (disable : 4551) // chiamata di funzione senza elenco di argomenti
#pragma	warning (disable : 4715) // non tutti i percorsi restituiscono un valore
#pragma	warning (disable : 6001) // utilizzo di memoria non inizializzata
#pragma	warning (disable : 28182) // dereferenziazione del puntatore null

// messaggi
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")

// Descrizione programma ::
	/*                                                          |
	*  Strings ZP[0.8.6].cpp: il programma calcola singola e\o  |
	*  doppia scomposizione di alcuni interi in una stringa o   |
	*  il contrario, i numeri primi, cifre e divisori, scompone |
	*  anche i polinomi, le frazioni algebriche e le matrici    |
	*///                                                        |

	// macro
#define and &&
#define or ||
#define xor !=
#define POS false
#define NEG true
#define BUGS
#define DEBUG
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define NO_DISCARD_CONST_EXPR _NODISCARD _CONSTEXPR20
#define integer(x) (_STD fabs(x - _STD round(x)) < 1e-9)
#define issign(x) (x == L'+' or x == L'-')
#define V1converter(func, param) To1V(func(ToXV(param)))
#define VXconverter(func, param) ToXV(func(To1V(param)))

// inclusioni
#include <algorithm>
#include <atomic>
#include <chrono> // per le misurazioni di tempo
#include <cmath> // per i calcoli
#include <condition_variable> // per il multithreading
#include <conio.h> // per l'input avanzato
#include <iomanip>
#include <iostream> // per l'output
#include <io.h> // per unicode
#include <initializer_list> // per le classi template
#include <iterator>
#include <locale> // per unicode
#include <memory>
#include <new> // per nothrow
#include <ppl.h> // per la parallelizzazione
#include <queue>
#include <random> // per i generatori casuali
#include <regex> // per la convalidazione
#include <sstream>
#include <stdexcept> // per le eccezioni
#include <string> // per le stringhe e i metodi
#include <thread> // per il multithreading
#include <type_traits>
#include <unordered_map> // per la conFversione degli enum
#include <utility>
#include <Windows.h> // per hConsole e la posizione del cursore

// namespace globali
using namespace std;
using namespace chrono;
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
ptrdiff_t GlobalMax(pow(10, 10));
const ptrdiff_t GLOBAL_CAP(1e10);
bool BOOLALPHA(true);
bool PRINTN(true);
double CORRECTION_RATIO{ 1.0 };

// variabili globali e atomiche
atomic<bool> GlobalInterr(false);
atomic<bool> interrupted(false);
atomic<bool> computing(false);
atomic<bool> IsDone(false);
condition_variable cv, Cv;
mutex CoutMutex, mtx;
COORD Min{ 25, 15 };

// strutture locali
struct compost {
	int factors;
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

	operator COORD() const {
		COORD result;
		result.X = static_cast<SHORT>(X);
		result.Y = static_cast<SHORT>(Y);
		return result;
	}
};

// enum e mappe
enum switchcase
{
	DoSimpleCode,
	DoComplexCode,
	DoSimpleFactor,
	DoComplexFactor,
	DoCodeFactor,
	DoAll,
	DebugSimpleCode,
	DebugComplexCode,
	DebugSimpleFactor,
	DebugComplexFactor,
	DebugCodeFactor,
	DebugAll,
	DebugDigits,
	DebugDigitsAndCode,
	DebugDigitsAndFactor,
	DebugComplete,
	ConvertCodeInverse,
	FactorPolynomial,
	FactorFraction,
	FactorMatrix,
	Random,
	NotAssigned
};
unordered_map<wstring, switchcase> stringToEnumMap{
	{L"cc" , switchcase::DoSimpleCode        },
	{L"ccc", switchcase::DoComplexCode       },
	{L"cf" , switchcase::DoSimpleFactor      },
	{L"cff", switchcase::DoComplexFactor     },
	{L"ccf", switchcase::DoCodeFactor        },
	{L"ct" , switchcase::DoAll               },
	{L"dc" , switchcase::DebugSimpleCode     },
	{L"dcc", switchcase::DebugComplexCode    },
	{L"df" , switchcase::DebugSimpleFactor   },
	{L"dff", switchcase::DebugComplexFactor  },
	{L"dcf", switchcase::DebugCodeFactor     },
	{L"dt" , switchcase::DebugAll            },
	{L"dr" , switchcase::DebugDigits         },
	{L"drc", switchcase::DebugDigitsAndCode  },
	{L"drf", switchcase::DebugDigitsAndFactor},
	{L"drt", switchcase::DebugComplete       },
	{L"ctn", switchcase::ConvertCodeInverse  },
	{L"pol", switchcase::FactorPolynomial    },
	{L"alg", switchcase::FactorFraction      },
	{L"mtx", switchcase::FactorMatrix        },
	{L"rnd", switchcase::Random              }
};
unordered_map<switchcase, wstring> enumToStringMap{
	{switchcase::DoSimpleCode        , L"cc" },
	{switchcase::DoComplexCode       , L"ccc"},
	{switchcase::DoSimpleFactor      , L"cf" },
	{switchcase::DoComplexFactor     , L"cff"},
	{switchcase::DoCodeFactor        , L"ccf"},
	{switchcase::DoAll               , L"ct" },
	{switchcase::DebugSimpleCode     , L"dc" },
	{switchcase::DebugComplexCode    , L"dcc"},
	{switchcase::DebugSimpleFactor   , L"df" },
	{switchcase::DebugComplexFactor  , L"dff"},
	{switchcase::DebugCodeFactor     , L"dcf"},
	{switchcase::DebugAll            , L"dt" },
	{switchcase::DebugDigits         , L"dr" },
	{switchcase::DebugDigitsAndCode  , L"drc"},
	{switchcase::DebugDigitsAndFactor, L"drf"},
	{switchcase::DebugComplete       , L"drt"},
	{switchcase::ConvertCodeInverse  , L"ctn"},
	{switchcase::FactorPolynomial    , L"pol"},
	{switchcase::FactorFraction      , L"alg"},
	{switchcase::FactorMatrix        , L"mtx"},
	{switchcase::Random              , L"rnd"}
};
unordered_map<wstring, wstring> ConvertFromSuperScript{
	{L"⁰", L"0"},
	{L"¹", L"1"},
	{L"²", L"2"},
	{L"³", L"3"},
	{L"⁴", L"4"},
	{L"⁵", L"5"},
	{L"⁶", L"6"},
	{L"⁷", L"7"},
	{L"⁸", L"8"},
	{L"9", L"9"},
};

#pragma endregion
#pragma region Classes

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
		if (new_capacity < capacity) return;
		T* new_data = new(nothrow) T[new_capacity];
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
		return *this;
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
		return *this;
	}
	void assign(tensor<T> other)
	{
		*this = other;
	}

	// metodi di base
	size_t size() const
	{
		return count;
	}
	size_t get_capacity() const
	{
		return capacity;
	}
	bool empty() const
	{
		return count == 0;
	}

	// metodi di accesso agli elementi
	T& at(size_t index)
	{
		if (index >= count) throw out_of_range("Index out of range");
		return data[index];
	}
	const T& at(size_t index) const
	{
		if (index >= count) throw out_of_range("Index out of range");
		return data[index];
	}
	T& last()
	{
		return data[count - 1];
	}
	const T& last() const
	{
		return data[count - 1];
	}

	// metodi di taglio
	void clear()
	{
		count = 0;
	}
	void erase(size_t pos)
	{
		if (pos >= count) throw out_of_range("Index out of range");
		count = pos;
	}
	void erase(size_t pos, size_t n)
	{
		if (pos >= count) throw out_of_range("Index out of range");
		n = min(n, count - pos);
		for (size_t i = pos; i < count - n; ++i) data[i] = move(data[i + n]);
		count -= n;
	}

	// operatori di accesso agli elementi
	NO_DISCARD_CONST_EXPR T& operator[](size_t index)
	{
		return at(index);
	}
	NO_DISCARD_CONST_EXPR const T& operator[](size_t index) const
	{
		return at(index);
	}

	// operatori di modifica degli elementi e della dimensione
	void push_back(const T& value)
	{
		if (count == capacity) resize(capacity * 2 + 1);
		data[count++] = value;
	}
	void pop_back()
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
	tensor<T>& operator++()
	{
		push_front(T());
		return *this;
	}
	tensor<T> operator++(int)
	{
		tensor temp = *this;
		push_back(T());
		return temp;
	}
	tensor<T>& operator--()
	{
		pop_front();
		return *this;
	}
	tensor<T> operator--(int)
	{
		tensor temp = *this;
		pop_back();
		return temp;
	}
	tensor& operator-=(size_t n)
	{
		count = n > count ? 0 : count - n;
		return *this;
	}

	// operatori push
	tensor& operator()(size_t n)
	{
		if (n >= count) resize(n * 2);
		count = n;
		return *this;
	}
	tensor& operator()(size_t n, const T& value)
	{
		if (n >= count) resize(n * 2);
		for (int i = count; i < n; ++i) data[i] = value;
		count = n;
		return *this;
	}
	constexpr tensor& operator<<(const T& value)
	{
		push_back(value);
		return *this;
	}
	constexpr tensor& operator>>(const T& value)
	{
		push_front(value);
		return *this;
	}

	// operatori di uguaglianza
	_NODISCARD bool operator==(const tensor& other) const
	{
		if (count != other.count) return false;
		for (size_t i = 0; i < count; ++i) if (data[i] != other.data[i])
			return false;
		return true;
	}
	NO_DISCARD_CONST_EXPR bool operator!=(const tensor& other) const
	{
		return !(*this == other);
	}

	// operatori di concatenazione
	_NODISCARD tensor operator+(const tensor& other) const
	{
		tensor result = *this;
		result += other;
		return result;
	}
	tensor& operator+=(const tensor& other)
	{
		for (size_t i = 0; i < other.count; ++i) push_back(other.data[i]);
		return *this;
	}

	// operatori di confronto tra tensori
	NO_DISCARD_CONST_EXPR bool operator<(const tensor& other) const
	{
		return count < other.count;
	}
	NO_DISCARD_CONST_EXPR bool operator<=(const tensor& other) const
	{
		return count <= other.count;
	}
	NO_DISCARD_CONST_EXPR bool operator>(const tensor& other) const
	{
		return count > other.count;
	}
	NO_DISCARD_CONST_EXPR bool operator>=(const tensor& other) const
	{
		return count >= other.count;
	}

	// operatori di confronto a destra con un intero
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator==(const tensor& t, U n)
	{
		return t.count == static_cast<size_t>(n);
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator!=(const tensor& t, U n)
	{
		return t.count != static_cast<size_t>(n);
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator<(const tensor& t, U n)
	{
		return t.count < static_cast<size_t>(n);
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator<=(const tensor& t, U n)
	{
		return t.count <= static_cast<size_t>(n);
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator>(const tensor& t, U n)
	{
		return t.count > static_cast<size_t>(n);
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator>=(const tensor& t, U n)
	{
		return t.count >= static_cast<size_t>(n);
	}

	// operatori di confronto a sinistra con un intero
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator==(U n, const tensor& t)
	{
		return static_cast<size_t>(n) == t.count;
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator!=(U n, const tensor& t)
	{
		return static_cast<size_t>(n) != t.count;
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator<(U n, const tensor& t)
	{
		return static_cast<size_t>(n) < t.count;
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator<=(U n, const tensor& t)
	{
		return static_cast<size_t>(n) <= t.count;
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator>(U n, const tensor& t)
	{
		return static_cast<size_t>(n) > t.count;
	}
	template<typename U, typename = enable_if_t<is_integral_v<U>>>
	friend bool operator>=(U n, const tensor& t)
	{
		return static_cast<size_t>(n) >= t.count;
	}

	// operatori logici
	NO_DISCARD_CONST_EXPR bool operator&&(const tensor& other) const
	{
		return !this->empty() and !other.empty();
	}
	NO_DISCARD_CONST_EXPR bool operator||(const tensor& other) const
	{
		return !this->empty() or !other.empty();
	}
	NO_DISCARD_CONST_EXPR bool operator%(const tensor& other) const
	{
		return this->size() xor other.size();
	}

	// iteratori
	class iterator
	{
	private: T* data;

	public: size_t index;
		using iterator_category = forward_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(T* data, size_t index) : data(data), index(index) {}

		iterator& operator++()
		{
			index++; 
			return *this; 
		}
		iterator operator++(int)
		{ 
			iterator temp = *this;
			index++; 
			return temp; 
		}
		iterator& operator--()
		{
			index--;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;
			index--;
			return temp;
		}

		iterator operator+(size_t n) const
		{
			return iterator(data, index + n);
		}
		iterator& operator+=(size_t n)
		{
			index += n;
			return *this;
		}
		iterator operator-(size_t n) const
		{
			return iterator(data, index - n);
		}
		iterator& operator-=(size_t n)
		{
			index -= n;
			return *this;
		}

		size_t operator+(iterator value) const
		{
			return index + value.index;
		}
		size_t operator-(iterator value) const
		{
			if (index == value.index) return 0;
			if (index < value.index) throw out_of_range("Index out of range");
			return index - value.index;
		}

		T& operator*()
		{
			return data[index];
		}
		const T& operator*() const
		{
			return data[index];
		}
		T* operator->()
		{
			return &data[index];
		}
		const T* operator->() const
		{
			return &data[index];
		}

		bool operator==(const iterator& other) const
		{
			return index == other.index;
		}
		bool operator!=(const iterator& other) const
		{
			return index != other.index;
		}
		bool operator<(const iterator& other) const
		{
			return index < other.index;
		}
		bool operator<=(const iterator& other) const
		{
			return index <= other.index;
		}
		bool operator>(const iterator& other) const
		{
			return index > other.index;
		}
		bool operator>=(const iterator& other) const
		{
			return index >= other.index;
		}
	};
	iterator begin()
	{
		return iterator(data, 0);
	}
	iterator end()
	{
		return iterator(data, count);
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
		if (first == last) return;
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

		// dato integrale
		else if constexpr (is_integral_v<T>)
			for (const auto& element : *this) result << to_wstring(element) << L", ";

		// stringhe
		else if constexpr (is_same_v<T, wstring>)
			for (const auto& element : *this) result << element << L", ";

		// niente
		else return L"";

		// fine
		outp = result.str();
		if (outp.size() >= 2) {
			outp.pop_back();
			outp.pop_back();
		}
		return L'{' + outp + L'}';
	}
};

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
		for (int i = str.size() - 1; i >= 0; --i) {
			int element = str.at(i) - '0';
			if (element != 0) Do = true;
			if (Do) Integer << element;
		}
	}

public:

	long double Number()
	{
		ptrdiff_t val{};

		// calcolo parte intera
		for (int i = 0; i < Integer; ++i) {
			val += Integer[i] * pow(10, Integer.size() - i - 1);
			if (val <= -2'147'483'647 or val >= 2'147'483'647) return nan("");
		}
		long double res = val;
		
		// parte decimale e segno
		res += decimal;
		if (sign == NEG) res *= -1;
		return res;
	}

	// costruttori
	big() : sign(POS), Integer(), decimal(0) {}
	big(int param) : sign(param < 0), Integer(), decimal(0)
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
	big(tensor<int> dig) : sign(POS), Integer(dig), decimal(0) {}

	// confronto primario e assegnazione
	big& operator=(const big& other)
	{
		sign = other.sign;
		Integer = other.Integer;
		decimal = other.decimal;
		return *this;
	}
	bool operator==(const big& other) const
	{
		return sign == other.sign and Integer == other.Integer
			and decimal == other.decimal;
	}
	bool operator!=(const big& other) const
	{
		return !(*this == other);
	}

	// confronto secondario
	bool operator<(const big& other) const
	{
		auto integ{ Integer };
		auto oth_integ{ other.Integer };

		if (sign and !other.sign) return true;
		if (!sign and other.sign) return false;

		while (integ[0] == 0) {
			if (integ <= 1) break;
			--integ;
		}
		while (oth_integ[0] == 0) {
			if (oth_integ <= 1) break;
			--oth_integ;
		}

		if (integ % oth_integ) return integ < oth_integ xor sign;
		for (int i = 0; i < integ; ++i) if (integ[i] != oth_integ[i])
				return integ[i] < oth_integ[i] xor sign;

		return decimal < other.decimal xor sign;
	}
	bool operator<=(const big& other) const
	{
		return *this < other or *this == other;
	}
	bool operator>=(const big& other) const
	{
		return !(*this < other);
	}
	bool operator>(const big& other) const
	{
		return !(*this == other or *this < other);
	}

	// addizione
	big operator+(const big& value) const
	{
		big Val = value;
		big This = *this;
		bool carry{ false };

		// segni
		if (!This.sign and Val.sign) {
			Val.sign = POS;
			return This - Val;
		}
		if (This.sign and !Val.sign) {
			This.sign = POS;
			return Val - This;
		}
		if (Val.sign and This.sign) Val.sign = POS;

		// ridimensionamento
		if (This.Integer < Val.Integer) swap(This, Val);
		while (Val.Integer < This.Integer) Val.Integer >> 0;

		// somma
		This.decimal += Val.decimal;
		carry = This.decimal >= 10;
		if (carry) This.decimal--;
		for (int i = This.Integer.size() - 1; i >= 0; --i) {
			int sum = This.Integer[i] + Val.Integer[i] + carry;
			carry = sum >= 10;
			This.Integer[i] = sum % 10;
		}
		if (carry) This.Integer >> 1;

		return This;
	}
	big& operator+=(const big& value)
	{
		*this = *this + value;
		return *this;
	}
	big& operator++()
	{
		*this = *this + 1;
		return *this;
	}
	big& operator++(int)
	{
		*this = *this + 1;
		return *this;
	}

	// sottrazione
	big operator-(const big& value) const
	{
		big Val = value;
		big This = *this;
		bool carry{ false }, neg{ false };

		// segni
		if (!This.sign and Val.sign) {
			Val.sign = POS;
			return This + Val;
		}
		if (This.sign and !Val.sign) {
			Val.sign = NEG;
			return Val + This;
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

		for (int i = This.Integer.size() - 1; i >= 0; --i) {
			int diff = This.Integer[i] - Val.Integer[i] - carry;
			carry = diff < 0;
			This.Integer[i] = (diff + 10) % 10;
		}

		while (This.Integer[0] == 0) {
			if (This.Integer <= 1) break;
			--This.Integer;
		}
		return This;
	}
	big& operator-=(const big& value)
	{
		*this = *this - value;
		return *this;
	}
	big& operator--()
	{
		*this = *this - 1;
		return *this;
	}
	big& operator--(int)
	{
		*this = *this - 1;
		return *this;
	}

	// moltiplicazione
	big operator*(const big& value) const
	{
		if (*this == 0 or value == 0) return 0;
		big Val = value;
		big This = *this;
		Val.shift();
		This.shift();
		int decprecision = Val.Integer.size() - value.Integer.size()
			+ This.Integer.size() - Integer.size();
		This.sign = POS;
		Val.sign = POS;

		// moltiplicazione
		tensor<big> add;
		for (int a = 0; a < Val.Integer.size(); ++a) {

			int factor{ Val.Integer.at(a) };
			if (factor == 0) continue;
			int carry{}, prod{};

			auto _Number{ This.Integer };
			for (int i = _Number.size() - 1; i >= 0; --i) {
				prod = (_Number.at(i)) * factor + carry;
				carry = prod / 10;
				_Number.at(i) = prod % 10;
			}
			if (carry != 0) _Number >> carry;
			for (int i = Val.Integer.size() - a - 2; i >= 0; --i) _Number << 0;
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
		for (int i = 0; i < decdigits; ++i)
			dec += decdigits[i] * pow(10, decdigits.size() - i - 1);
		This.decimal = dec / pow(10, decprecision);

		This.sign = sign xor value.sign;
		return This;
	}
	big& operator*=(const big& value)
	{
		*this = *this * value;
		return *this;
	}

	// divisione intera
	big operator/(const big& value) const
	{
		if (value == 0) throw invalid_argument("Division by zero!");

		big This = *this;
		big result, current;
		result.Integer.clear();
		result.sign = This.sign != value.sign;

		// divisione lunga
		for (int i = 0; i < This.Integer; ++i)
		{
			// correzione
			int quotient = 0;
			current.Integer << This.Integer[i];
			while (current.Integer > 1 and current.Integer[0] == 0) --current.Integer;

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
		return result;
	}
	big& operator/=(const big& value)
	{
		*this = *this / value;
		return *this;
	}

	// modulo
	big operator%(const big& value) const
	{
		if (value == 0) throw invalid_argument("Modulo by zero!");

		// segni
		big This = *this;
		big Val = value;
		This.sign = POS;
		Val.sign = POS;

		// calcolo
		while (This >= Val) {
			big temp = Val;
			big factor = 1;

			while (temp * 10 <= This) {
				factor *= 10;
				temp *= 10;
			}
			This -= temp;
		}

		return This;
	}
	big& operator%=(const big& value)
	{
		*this = *this % value;
		return *this;
	}

	// metodi matematici
	bool intg() const
	{
		return decimal == 0;
	}
	big fabs() const
	{
		big other = *this;
		other.sign = POS;
		return other;
	}
	big floor()
	{
		decimal = 0;
		return *this;
	}
	big ceil()
	{
		bool integ = decimal == 0;
		decimal = 0;
		if (integ) (*this)++;
		return *this;
	}
	big round()
	{
		*this += _STD round(decimal);
		decimal = 0;
		return *this;
	}
	big invert()
	{
		sign = !sign;
		return *this;
	}

	// output
	wostringstream c_str(int precision)
	{
		wostringstream oss, result;
		if (sign) wcout << L'-';
		for (auto intg : Integer) result << intg;
		oss << setprecision(precision) << decimal;
		auto str{ oss.str() };
		str.erase(0, 1);
		if (!str.empty()) result << L'.' << str;
		return result;
	}
};

// numeri complessi
class complex
{
public:

	// dati
	double RealPart;
	double ImaginaryPart;
	double norm() const
	{
		return sqrt(RealPart * RealPart + ImaginaryPart * ImaginaryPart);
	}

	// costruttori
	complex() : RealPart(0), ImaginaryPart(0) {}
	complex(double real) : RealPart(real), ImaginaryPart(0) {}
	complex(double real, double imag) : RealPart(real), ImaginaryPart(imag) {}

	// metodi matematici
	complex conjugate() const
	{
		return complex(RealPart, -ImaginaryPart);
	}
	complex opposite() const
	{
		return complex(-RealPart, -ImaginaryPart);
	}

	// addizione
	complex operator+(complex value) const
	{
		return complex(
			RealPart + value.RealPart,
			ImaginaryPart + value.ImaginaryPart
		);
	}
	complex& operator+=(complex value)
	{
		*this = *this + value;
		return *this;
	}
	complex& operator++()
	{
		*this = *this + 1;
		return *this;
	}
	complex& operator++(int)
	{
		*this = *this + 1;
		return *this;
	}

	// sottrazione
	complex operator-(complex value) const
	{
		return complex(
			RealPart - value.RealPart,
			ImaginaryPart - value.ImaginaryPart
		);
	}
	complex& operator-=(complex value)
	{
		*this = *this - value;
		return *this;
	}
	complex& operator--()
	{
		*this = *this - 1;
		return *this;
	}
	complex& operator--(int)
	{
		*this = *this - 1;
		return *this;
	}

	// moltiplicazione e divisione
	complex operator*(complex value) const
	{
		double a{ RealPart };
		double b{ ImaginaryPart };
		double c{ value.RealPart };
		double d{ value.ImaginaryPart };

		return complex(
			a * c - b * d,
			b * c + a * d
		);
	}
	complex& operator*=(complex value)
	{
		*this = *this * value;
		return *this;
	}
	complex operator/(complex value) const
	{
		double a{ RealPart };
		double b{ ImaginaryPart };
		double c{ value.RealPart };
		double d{ value.ImaginaryPart };

		return complex(
			(a * c + b * d) / (c * c + d * d),
			(b * c - a * d) / (c * c + d * d)
		);
	}
	complex operator/=(complex value)
	{
		*this = *this / value;
		return *this;
	}

	// output
	wstring c_str() const
	{
		wostringstream output;
		output << setprecision(10) << L'(' << RealPart << L' ';
		ImaginaryPart > 0 ? output << L'+' : output << L'-';
		output << L" i" << fabs(ImaginaryPart) << L')';
		return output.str();
	}
};

// monomi
wstring Variables;
template<typename T_int = long double>struct MONOMIAL {
	int degree;
	T_int coefficient;
	bool operator == (const MONOMIAL& other) const
	{
		return coefficient == other.coefficient and
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
		return coefficient == other.coefficient and exp == other.exp;
	}
	int degree()
	{
		int sum{};
		for (size_t i = 0; i < exp.size(); ++i) sum += exp[i];
		return sum;
	}
	bool IsSquare()
	{
		if (!integer(sqrt(fabs(this->coefficient)))) return false;
		for (size_t i = 0; i < exp.size(); ++i)
			if (exp[i] % 2 == 1) return false;
		return true;
	}
	monomial Root(int order)
	{
		monomial result;

		result.coefficient = pow(this->coefficient, 1.0 / order);
		for (size_t i = 0; i < exp.size(); ++i)
			result.exp.push_back(exp[i] / order);

		return result;
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
					Monomial += data.coefficient.fabs().c_str(0).str();
			}

			// aggiunta variabili ed esponenti
			for (int i = 0; i < Variables.size(); ++i) if (data.exp[i] != 0) {
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

		return polynomial;
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
		for (int i = this->size() - 1; i > 0; --i)
			for (int j = 1; j < (*this)[i - 1].degree - (*this)[i].degree; ++j)
				this->insert(this->begin() + i, { (*this)[i - 1].degree - j, 0 });

		// riempimento buchi agli estremi
		if (this->empty()) for (int i = 0; i < s; ++i) this->push_back({ i, 0 });
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
		for (auto Monomial : *this) {
			monomial<T_int> element;
			element.coefficient = Monomial.coefficient;
			element.exp(Variables.size(), 0);
			element.exp[_FirstPos] = Monomial.degree;
			traduction << element;
		}
		return traduction.str(1);
	}
};
static factor<> ToXV(FACTOR<> vect)
{
	factor<> output;
	int _FirstPos = Variables.find(charVariable);
	for (auto Monomial : vect) {
		monomial<> element;
		element.coefficient = Monomial.coefficient;
		element.exp(Variables.size(), 0);
		element.exp[_FirstPos] = Monomial.degree;
		output << element;
	}
	return output;
}
static FACTOR<> To1V(factor<> vect)
{
	FACTOR<> output;
	int _FirstPos = Variables.find(charVariable);
	for (auto Monomial : vect) {
		MONOMIAL<> element{ 0, 0 };
		element.coefficient = Monomial.coefficient;
		if (_FirstPos != wstring::npos) element.degree = Monomial.exp[_FirstPos];
		output << element;
	}
	return output;
}

// polinomi completi
static void ElabExponents(wstring& str);
template<typename T_int = long double>class polynomial : public tensor<factor<T_int>>
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
		for (int i = 0; i < this->size(); ++i) if ((*this)[i][0].exp[0] == -1)
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
		if (!this->empty()) for (int i = 0; i < this->size(); ++i)
			for (int j = this->size() - 1; j > i; --j)
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
							for (int k = 0; k < this->size(); ++k)
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
		wstring output, exp;
		bool IsAModifier{ false };
		for (auto T : *this) {

			// caso di monomio modificatore
			if (!T[0].exp.empty()) if (T[0].exp[0] < 0) {
				if constexpr (is_same_v<T_int, long double>)
					exp = to_wstring((int)T[0].coefficient);
				else if constexpr (is_same_v<T_int, big>)
					exp = T[0].coefficient.c_str(0).str();
				IsAModifier = true;
				continue;
			}
			auto xout{ T.str(size) };

			// caso con elevamento a potenza
			if (IsAModifier) {
				xout = L"(" + xout + L")^" + exp;
				IsAModifier = false;
			}

			// caso comune
			else if (T > 1) xout = L"(" + xout + L")";

			output += xout;
		}

		// caso nullo
		if (output.empty()) return L"0";

		if (BOOLALPHA) ElabExponents(output);
		return output;
	}
};
template<typename T_int = long double>class POLYNOMIAL : public tensor<FACTOR<T_int>>
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
		for (int i = 0; i < this->size(); ++i) NewClass << ToXV((*this)[i]);
		NewClass.open();
		this->clear();
		for (int i = 0; i < NewClass.size(); ++i)
			this->push_back(To1V(NewClass[i]));
	}
	void close()
	{
		polynomial<T_int> NewClass;
		for (int i = 0; i < this->size(); ++i)
			NewClass.push_back(ToXV((*this)[i]));
		NewClass.close();
		this->clear();
		for (int i = 0; i < NewClass.size(); ++i)
			this->push_back(To1V(NewClass[i]));
	}

	_NODISCARD wstring str(int size = Variables.size()) override
	{
		polynomial<T_int> traduction;
		for (auto vector : *this) traduction << ToXV(vector);
		return traduction.str(1);
	}
};

static polynomial<> ToXV(POLYNOMIAL<> vect)
{
	polynomial<> output;
	for (auto vector : vect) output << ToXV(vector);
	return output;
}
static POLYNOMIAL<> To1V(polynomial<> vect)
{
	POLYNOMIAL<> output;
	for (auto vector : vect) output << To1V(vector);
	return output;
}

static polynomial<> FromBigToDefault(polynomial<big> BigPolynomial)
{
	polynomial<> traduction;
	for (auto fact : BigPolynomial) {
		factor<> element;
		for (auto mon : fact) {
			monomial<> unity;
			unity.coefficient = mon.coefficient.Number();

			if (isnan(unity.coefficient)) return
				polynomial<>({ factor<>({ monomial<>({
					1,
					tensor<int>(1, -2)
				}) }) });

			unity.exp = mon.exp;
			element << unity;
		}
		traduction << element;
	}
	return traduction;
}

// estensioni di tensor
class tensor_t
{
public:
	tensor<bool> is_prime;
	tensor<int> list_primes;

	tensor_t(){}	
	tensor_t(
		tensor<bool> is_prime_param, 
		tensor<int> list_primes_param
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
		return *this;
	}
};
tensor_t PrimeNumbers;

// altre classi
class NumberData
{
public:
	int number{};
	wstring code;
	int degree{};
	wstring expression;
	tensor<int> sequence;
	divisor div;
	digitRatio digit;

	NumberData() = default;
	NumberData(
		int num,
		const wstring& c,
		int deg,
		const wstring& expr,
		const tensor<int>& seq,
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
		}

		// stampa dati cifre
		else if (number >= 10) {

			// stampa numero
			if (
				digit.digitSumRatioNum == 0 and
				digit.digitProductRatioNum == 0
				) return;
			wcout << L"numero " << number << L":\n";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"in esadecimale è " << hex << uppercase;
			wcout << number << L'\n' << dec << nouppercase;
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
			for (int i = 0; i < sequence.size() - 1; ++i) wcout << sequence[i] << L", ";
			wcout << sequence.last() << L")\n";
		}

		if (!expression.empty()) {

			// se il numero è primo
			if (PrimeNumbers.is_prime[number]) {
				SetConsoleTextAttribute(hConsole, 240);
				wcout << L"il numero è primo";
				SetConsoleTextAttribute(hConsole, 15);
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
		SetConsoleTextAttribute(hConsole, 15);
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
		for (int i = n / 2 - 1; i >= 0; --i) heapify(n, i);
		for (int i = n - 1; i > 0; --i) {
			iter_swap(this->begin(), this->begin() + i);
			heapify(i, 0);
		}
	}
};
class TestInputReader
{
private: _STD queue<wchar_t> buffer;
public:
	void enqueue(wchar_t c)
	{
		buffer.push(c);
	}
	wchar_t read()
	{
		if (buffer.size() == 0) buffer.push(_getwch());
		auto front{ buffer.front() };
		buffer.pop();
		return front;
	}
};
TestInputReader ObjectGetCh;

// oggetti
struct Console {
	wstring Text;
	int Attribute{ 15 };
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
	L"pol",
	L"alg",
	L"mtx",
	L"rnd"
};

#pragma endregion
#pragma region Declarations

static size_t Factorial(size_t n);
static size_t BinomialCoeff(size_t n, size_t k);
static int Gcd(int A, int B);
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
static void ProgressBar(double ratio, double barWidth);
static long double WaitingScreen(auto begin, auto end);
static void PrintGraph(FACTOR<> funct, const coord position);
static wstring CTSuperScript(wchar_t input);
static wstring CFSuperScript(wstring script);
static void DeduceFromExponents(wstring& str);
static void GetFraction(wstring& numerator, wstring& denominator);
static wstring GetLine(bool ShowSuggestions, int sizemax);
static wstring GetUserNum
(wstring txt, int low, ptrdiff_t high, bool ShowSuggestions);
static void SetDebug(wstring message, switchcase& opt, bool& Return,
	ptrdiff_t& LowerBound, ptrdiff_t& UpperBound, ptrdiff_t& datalenght
);
static bool Prime(ptrdiff_t number);
static void UserInputThread();
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
static wstring PolynomialSyntaxDirector(wstring pol);
static wstring PolynomialSyntax(wstring pol);
static wstring UpdateString(wstring& ToEvaluate);
static wstring NumberCodeSyntax(wstring ToEvaluate);
static size_t NumberConverter(size_t root, wstring M);
static size_t StringConverter(wstring ToEvaluate);
static void CodeConverter
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static void LongComputation
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static polynomial<big> GetMonomialsAssister(wstring pol);
static polynomial<big> GetMonomialsDirector(wstring pol, bool changx = true);
static factor<big> GetMonomials(wstring pol);
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
static tensor<tensor<double>> MatrixMultiply(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
);
template<typename T> static T Determinant(tensor<tensor<T>> mx);
FACTOR<> PolynomialMatrixDeterminant(tensor<tensor<FACTOR<>>> PolynomialMatrix);
static tensor<double> EigenValues
(tensor<tensor<double>> mx, bool determinant = false);
static void CodeToNumber(switchcase& argc);
static void Repeater(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input)
);
static void Loop(
	switchcase& argc,
	wstring message,
	NumberData CPU(ptrdiff_t input),
	bool select
);
static polynomial<> DecompPolynomial(switchcase& argc, wstring polynomial);
static void DecompFraction(switchcase& argc);
static void DecompMatrices(switchcase& argc);

#pragma endregion

// programma principale
int main()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	wcout.imbue(locale(""));
	
	Beep(1000, 50);
	Beep(1000, 50);

	// dichiarazione stringhe
	wstring simpledeg{ L"il PROGRAMMA calcola solo la codifica di un intero" };
	wstring simplefact{ L"il PROGRAMMA calcola solo la fattorizzazione di un intero" };
	wstring def_sct{ L"il PROGRAMMA calcola solo codifica e fattorizzazione" };
	wstring desimpledeg{ L"il PROGRAMMA calcola solo la codifica di una serie" };
	wstring desimplefact{ L"il PROGRAMMA calcola solo la fattorizzazione di una serie" };
	wstring defact_message{ L"il PROGRAMMA calcola la fattorizzazione di una serie" };
	defact_message.append(L"\ne numero, somma e prodotto dei divisori");
	wstring deg_message{ L"il PROGRAMMA calcola codice, sequenza e grado di una serie" };
	wstring fact_message{ L"il PROGRAMMA calcola la fattorizzazione di un intero" };
	fact_message.append(L"\ne numero, somma e prodotto dei divisori");
	wstring message{ L"il PROGRAMMA calcola codice, sequenza e grado di un intero" };
	wstring AllMessage{ L"il PROGRAMMA calcola \"tutti\" i dati di alcuni interi" };
	wstring de_digit{ L"il PROGRAMMA ricerca numeri con particolari" };
	de_digit.append(L" occorrenze di somma e prodotto cifre");
	wstring deg_digit{ L"il PROGRAMMA calcola cifre, codice, sequenza e grado" };
	wstring fact_digit{ L"il PROGRAMMA calcola cifre, fattorizzazione, e divisori" };
	wstring defact_digit{ L"il PROGRAMMA calcola tutti i dati, cifre comprese" };
	wstring vel, text;
	switchcase option;

	bool start{ true };
	bool LockPrimeNumbersInput{ false };
	ptrdiff_t global{ 1 };
	long double ComputationTime;
	size_t Timer{ 2'400'000'000 };
	while (true)
	{
		if (!LockPrimeNumbersInput) {
			Start:
			while (true) {
				system("cls");
				SetConsoleTitle(L"schermata START");
				
				// // output
				SetConsoleTextAttribute(hConsole, 2);
				wcout << L"~~~~~.";
#ifndef BUGS
				wcout << L"~~";
#endif
				wcout << L"[> CALCOLO-STRINGHE-E-GRADI V";
#ifndef BUGS
				wcout << L' ';
#endif
				wcout << L"0.8.6 ";
#ifdef BUGS
				wcout << L"BETA ";
#endif
				wcout << L"<]";
#ifndef BUGS
				wcout << L"~~";
#endif
				wcout << L".~~~~~\n";
				wcout << L"*****.*****.*****.[> CALCOLATRICE <].*****.*****.*****\n\n";

				SetConsoleTextAttribute(hConsole, 10);
				wcout << L"Scegliere il limite per la ricerca dei numeri primi\n";
				wcout << L"Un limite più alto comporta un tempo di attesa più lungo\n";
				wcout << L"inserire un numero tra compreso 10 milioni e 10 miliardi\n\n";

				SetConsoleTextAttribute(hConsole, 2);
				wcout << L"*****.*****.*****.*****.******.*****.*****.*****.*****\n\n";
				SetConsoleTextAttribute(hConsole, 9);
				wcout << L"per bloccare l'input inserire 0\n";
				// //

				// inserimento punti
				wstring Timer_t{ to_wstring(Timer) };
				for (int i = Timer_t.size() - 3; i > 0; i -= 3)
					Timer_t.insert(Timer_t.begin() + i, L'.');

				// input controllato
				text = L"ESEMPIO: " + Timer_t + L" = ~1 minuto di attesa\n";
				wstring G{ GetUserNum(text, 0, GLOBAL_CAP, false) };
				if (G == L".") goto End;
				if (G.empty()) G = L"0";
				if (ConvertWStringToEnum(G) != NotAssigned) continue;

				// casi 0 e 1
				global = stoi(G);
				if (global == 1) continue;
				if (global < 10'000'000) {
					if (!start and global == 0) LockPrimeNumbersInput = true;
					else global = 10'000'000;
					break;
				}
				if (global < 10'000'000) global = 10'000'000;
				break;
			};
			SetConsoleTextAttribute(hConsole, 15);

			// output del tempo
			if (global != 0 or start) {
				steady_clock::time_point begin{ steady_clock::now() };
				GlobalMax = global;
#ifndef DEBUG
				SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
				PrimeNCalculator(GlobalMax + 1'000);

				steady_clock::time_point end{ steady_clock::now() };
				ComputationTime = WaitingScreen(begin, end);
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorInfo(hConsole, &cursor);
				start = false;
			}
			if (GlobalMax > 9'000 and global > 1) {
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
		SetConsoleTextAttribute(hConsole, 15);
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
			case L'.': goto End;
			default: vel += L' ';
			}
		}

		// caso input non assegnato correttamente
		option = ConvertWStringToEnum(vel);
		if (option == NotAssigned) {

			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"NON CORRETTO !!\a";
			SetConsoleTextAttribute(hConsole, 15);

		option_choice:

			wcout << L"\nscegli opzioni:: (...)\n";
			vel = GetLine(true, 10);
			goto assigne;
		}

		wcout << L"\n\n";
		ReassigneEnum(option);
		auto wtitle{ ConvertEnumToWString(option) };

		// cambio titolo
		system("cls");
		SetConsoleTitle(wtitle.c_str());

		// scelta funzioni e opzioni
		do {
			Beep(500, 200);
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
				Loop(option, desimpledeg, ExecuteSimpledeg, false);
				break;
			case DebugComplexCode:
				Loop(option, deg_message, ExecuteDegree, false);
				break;
			case DebugSimpleFactor:
				Loop(option, desimplefact, ExecuteSimpleFact, false);
				break;
			case DebugComplexFactor:
				Loop(option, defact_message, ExecuteFactor, false);
				break;
			case DebugCodeFactor:
				Loop(option, def_sct, ExecuteSimpleDF, false);
				break;
			case DebugAll:
				Loop(option, AllMessage, ExecuteDegFactor, false);
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
			case ConvertCodeInverse:
				CodeToNumber(option);
				break;
			case FactorPolynomial:
				DecompPolynomial(option, L"");
				break;
			case FactorFraction:
				DecompFraction(option);
				break;
			case FactorMatrix:
				DecompMatrices(option);
				break;
			}
			if (option == Random) goto End;

		} while (option != NotAssigned);
	}

	// fine del programma
End:
	system("cls");
	SetConsoleTextAttribute(hConsole, 4);
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	return 0;
}

#pragma region Functions

// funzioni matematiche
#pragma region Math

// fattoriale x! = x*(x-1)*...*2*1
static size_t Factorial(size_t n)
{
	if (n <= 1) return 1;
	return n * Factorial(n - 1);
}

// coefficiente binomiale: (n k) = n! / (k! (n-k)!)
static size_t BinomialCoeff(size_t n, size_t k)
{
	long double coeff{ 1.0 };

	// limite di sicurezza per prevenire crash
	if (n <= 20) coeff = Factorial(n) / (Factorial(k) * Factorial(n - k));
	else for (int j = 1; j <= n - k; ++j) coeff *= (k + j) / j;

	return (size_t)coeff;
}

// massimo comune divisore tra due interi
static int Gcd(int A, int B)
{
	if (A < B) swap(A, B);
	while (B != 0) {
		int temp = B;
		B = A % B;
		A = temp;
	}
	return A;
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
	return A;
}

// massimo comune divisore tra più termini
template<typename T>static int Gcd(tensor<T> terms)
{
	int gcd{};
	if (terms.empty()) return 0;

	// tensore di interi
	if constexpr (is_same_v<T, int>) {
		if (terms == 1) return terms[0];
		gcd = terms[0];
		for (auto term : terms) {
			gcd = Gcd(gcd, term);
			if (gcd == 1) break;
		}
	}

	// fattore
	else if constexpr (is_same_v<T, MONOMIAL<>> or is_same_v<T, monomial<>>)
	{
		if (terms == 1) return terms[0].coefficient;
		gcd = terms[0].coefficient;
		for (auto term : terms) {
			gcd = Gcd(gcd, term.coefficient);
			if (gcd == 1) break;
		}
	}

	return gcd;
}

// massimo comune divisore tra numeri molto grandi
static big Gcd(tensor<big> terms)
{
	if (terms == 1) return terms[0];
	auto gcd{ terms[0] };
	for (auto term : terms) {
		gcd = Gcd(gcd, term);
		if (gcd == 1) break;
	}
	return gcd;
}

// potenza sugli interi (per precisione)
static ptrdiff_t intpow(ptrdiff_t base, int exp)
{
	ptrdiff_t power{ 1 };
	auto NewExp{ exp };
	auto NewBase{ base };
	if (base < 0) NewBase *= -1;
	while (NewExp > 0) {
		power *= NewBase;
		if (power < 0) return -1;
		NewExp--;
	}
	if (exp % 2 == 1 and base < 0) return -power;
	return power;
}

#pragma endregion

// funzioni per gestrire l'enum
#pragma region EnumMod

// da enum a stringa
static wstring ConvertEnumToWString(switchcase Enum)
{
	auto it = enumToStringMap.find(Enum);
	if (it != enumToStringMap.end()) return it->second;
}

// da stringa a enum
static switchcase ConvertWStringToEnum(wstring str)
{
	auto it = stringToEnumMap.find(str);
	if (it != stringToEnumMap.end()) return it->second;
	else {
		stringToEnumMap.insert({ str , NotAssigned });
		it = stringToEnumMap.find(str);
		return it->second;
	}
}

// riassegna l'opzione casuale dell'enum
static void ReassigneEnum(switchcase& option)
{
	if (option != Random) return;
	random_device rng;
	mt19937 gen(rng());
	uniform_int_distribution<> dis(0, 20);
	switch (dis(gen)) {
	case 0:
		option = DoSimpleCode;
		break;
	case 1:
		option = DoComplexCode;
		break;
	case 2:
		option = DoSimpleFactor;
		break;
	case 3:
		option = DoComplexFactor;
		break;
	case 4:
		option = DoCodeFactor;
		break;
	case 5:
		option = DebugCodeFactor;
		break;
	case 6:
		option = DoAll;
		break;
	case 7:
		option = DebugSimpleCode;
		break;
	case 8:
		option = DebugComplexCode;
		break;
	case 9:
		option = DebugSimpleFactor;
		break;
	case 10:
		option = DebugComplexFactor;
		break;
	case 11:
		option = DebugComplexFactor;
		break;
	case 12:
		option = DebugAll;
		break;
	case 13:
		option = DebugDigits;
		break;
	case 14:
		option = DebugDigitsAndCode;
		break;
	case 15:
		option = DebugDigitsAndCode;
		break;
	case 16:
		option = DebugDigitsAndFactor;
		break;
	case 17:
		option = ConvertCodeInverse;
		break;
	case 18:
		option = FactorPolynomial;
		break;
	case 19:
		option = FactorFraction;
		break;
	case 20:
		option = FactorMatrix;
		break;
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
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD consoleSize = intpow(2 * Dimensions.X + 1, 2);
	DWORD written;
	COORD coord;

	coord.X = WinCenter.X - Dimensions.X;
	coord.Y = WinCenter.Y - Dimensions.Y;

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
	SetConsoleTextAttribute(hConsole, 15);

	COORD coord;
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

	for (double rad = 0; rad < 2 * M_PI; rad += theta) {
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
			index *= (double)prints.size() / (2 * radius);
			wcout << prints[index];
		}
	}
}

// stampa il cerchio
static void DrawFrame
(int arc, double __i, int centerX, int centerY, double DIM)
{
	COORD coord;
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
		int colour;

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
		for (int j = 0; j < spectrum; ++j) if (DisGen == j) colour = spectrum[j];

		// stampa
		SetConsoleTextAttribute(hConsole, colour);
		wcout << dis(gen);
	}
}

// gestisce la stampa del poligono e del cerchio
static void DrawCircleSquare(COORD CircleCenter)
{
	
	// calcolo variabili
	COORD cursor{ 0, CircleCenter.Y };
	cursor.Y -= Min.Y;
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
			SetConsoleCursorPosition
			(hConsole, cursor);
			return;
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

	COORD origin;
	origin.X = WindowLenght + shift.X + pos.X;
	origin.Y = WindowWidth + shift.Y + pos.Y;
	SetConsoleTextAttribute(hConsole, 15);

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
		for (int i = 0; i < funct; ++i)
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
	SetConsoleTextAttribute(hConsole, 15);

	// scrittura estremi asse y
	SetConsoleCursorPosition(hConsole, { (short)(2 * WindowLenght + 3), 0 });
	wcout << wstring(13, ' ');
	SetConsoleCursorPosition(hConsole, { (short)(2 * WindowLenght + 3), 0 });
	wcout << (WindowWidth + shift.Y) * DIM / zoom;
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght + 3), (short)(2 * WindowWidth + 2)}
	);
	wcout << wstring(13, ' ');
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght + 3), (short)(2 * WindowWidth + 2) }
	);

	wcout << (shift.Y - 2 - WindowWidth) * DIM / zoom;

	// scrittura estremi asse x
	SetConsoleCursorPosition(hConsole, { 0, (short)(2 * WindowWidth + 3) });
	wcout << wstring(13, ' ');
	SetConsoleCursorPosition(hConsole, { 0, (short)(2 * WindowWidth + 3) });
	wcout << (-WindowLenght - shift.X) / zoom;
	SetConsoleCursorPosition(
		hConsole,
		{ (short)(2 * WindowLenght), (short)(2 * WindowWidth + 3) }
	);
	wcout << wstring(13, ' ');
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
static void CS_CenterPrinter()
{

	// assegnazione delle coordinate del centro
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD WinCenter;
	if (csbi.dwSize.X / 2 < Min.X) WinCenter.X = Min.X;
	else WinCenter.X = csbi.dwSize.X / 2;
	if (csbi.dwSize.Y / 2 < Min.Y) WinCenter.Y = Min.Y + 1;
	else WinCenter.Y = csbi.dwSize.Y / 2 + 1;

	// animazione
	DrawCircleSquare(WinCenter);

}

// stampa poligono e cerchio in un angolo della finestra
static void CS_CornerPrinter()
{

	// lettura coordinate
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	wcout << wstring(csbi.dwSize.Y - 1, L'\n');

	// animazione
	SetConsoleCursorPosition(hConsole, { 0, 0 });
	DrawCircleSquare(Min);

}

// stampa una barra di avanzamento
static void ProgressBar(double ratio, double barWidth)
{
	if (barWidth <= 10) return;

	// necessario per poter scrivere messaggi 
	// sotto alla barra di progresso
	SetConsoleCursorPosition(hConsole, { 0, 1 });

	// stampa della barra principale
	wcout << L"[[";
	int pos{ (int)(barWidth * ratio) };
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) wcout << L'=';
		else i == pos ? wcout << L'>' : wcout << L' ';
	}

	// calcolo della percentuale
	ratio *= 100.0;
	wstringstream stream;
	stream << fixed << setprecision(1) << ratio;
	wcout << L"]] " << stream.str() << L"%\r";
}

// stampa il tempo del calcolo
static long double WaitingScreen(auto begin, auto end)
{
	system("cls");

	// calcolo dati
	long double delta = duration_cast<microseconds> (end - begin).count();
	long double ExceptDelta = duration_cast<nanoseconds> (end - begin).count();
	wstringstream output;
	output << fixed << setprecision(1) << L"tempo di calcolo numeri primi = ";

	// calcolo output
	if (delta <= 10'000)
	{
		output << ExceptDelta / 1'000;
		output << L" microsecondi\n\n";
	}
	else if (delta <= 10'000'000)
	{
		output << delta / 1'000;
		output << L" millisecondi\n\n";
	}
	else if (delta <= 600'000'000)
	{
		output << delta / 1'000'000;
		output << L" secondi\n\n";
	}
	else
	{
		output << delta / 60'000'000;
		output << L" minuti\n\n";
	}
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	SetConsoleTextAttribute(hConsole, 6);

	// output
	COORD Cursor;
	Cursor.X = (csbi.dwSize.X - output.str().size()) / 2 - 1;
	Cursor.Y = csbi.dwSize.Y / 2 - 1;
	SetConsoleCursorPosition(hConsole, Cursor);
	wcout << output.str();
	sleep_for(seconds(1));

	return ExceptDelta;
}

// crea una finestra con dei comandi per ridimensionare il grafico
static void PrintGraph(FACTOR<> funct, const coord position)
{

	// variabili
	bool Break{ false };
	double zoom{ 1 };
	coord shift{ 0, 0 };
	const short lenght{ 40 };
	const short width{ 12 };
#ifndef DEBUG
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
	
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
	
	while (true) {

		// grafico
		DrawGraphFrame(funct, shift, position, zoom, lenght, width);
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
				SetConsoleCursorPosition(
					hConsole,
					{ 0, (short)(position.Y + width * 2 + 4) }
				);
				return;
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

		ClearArea(
			{ (short)(lenght + position.X + 1), (short)(width + position.Y + 1) },
			{ lenght, width }
		);
		if (Break) break;
	}

	SetConsoleCursorInfo(hConsole, &cursor);
}

#pragma endregion

// funzioni per gestire gli esponenti
#pragma region SuperScript

// converte da numero ad apice
static wstring CTSuperScript(wchar_t input)
{
	switch (input) {
	case L'0': return L"⁰";
		break;
	case L'1': return L"¹";
		break;
	case L'2': return L"²";
		break;
	case L'3': return L"³";
		break;
	case L'4': return L"⁴";
		break;
	case L'5': return L"⁵";
		break;
	case L'6': return L"⁶";
		break;
	case L'7': return L"⁷";
		break;
	case L'8': return L"⁸";
		break;
	case L'9': return L"9";
		break;
	}
	return wstring(1, input);
}

// converte da apice a numero
static wstring CFSuperScript(wstring script)
{
	wstring output;
	for (auto ch : script) {
		auto it = ConvertFromSuperScript.find(script);
		if (it != ConvertFromSuperScript.end()) output += it->second;
		else output += wstring(1, ch);
	}
	return output;
}

// cambia una stringa da formato numeri a formato esponenti
static void ElabExponents(wstring& str)
{
	int J{ 1 };
	bool dobreak{ false };
	for (int I = 0; I < str.size(); ++I) {
		int pointer{ I + 1 };
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
	for (int i = str.size() - 1; i >= 0; --i) {
		auto script{ wstring(1, str.at(i)) };
		auto unscript{ CFSuperScript(script) };
		if (unscript != script) {
			str.erase(i, 1);
			str.insert(str.begin() + i, unscript.at(0));
			str.insert(str.begin() + i, L'^');
		}
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

	int sizevel, diff{};
	numerator.clear();
	denominator.clear();
	wstring vel, command{ L"rnd" }, Num, Den;
	bool script{ true }, arrow{ false }, Continue{ false };
	bool IsTheCursorAtStart{ true };

	// aggiunta di spazio
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto START{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if (csbi.dwCursorPosition.Y >= START.Y)
		START.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
	SetConsoleCursorPosition(hConsole, START);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto start{ csbi.dwCursorPosition };
	while (true) if (_kbhit) {

		char c = _getch();
		GetConsoleScreenBufferInfo(hConsole, &csbi);
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
#ifndef DEBUG
			SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
			SetConsoleCursorPosition(hConsole, start);
			for (int a = 0; a < 4; ++a) wcout << S << L'\n';
			SetConsoleCursorInfo(hConsole, &cursor);
			return;

			// L'\r' termina l'input
		case L'\r':
			start.Y += 4;
			SetConsoleCursorPosition(hConsole, start);
			if (denominator.empty()) denominator = L"1";
			return;

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
			for (auto ch : copy)
				if (CFSuperScript(wstring(1, ch)) != wstring(1, ch))
					new_diff--;

			// aggiunta carattere
			if (!arrow) {
				if (new_diff < 0) new_diff = 0;
				auto first{ vel };
				auto last{ vel };
				first.erase(new_diff);
				last.erase(0, new_diff);
				first += c;
				vel = first + last;

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

				// ctrl + canc cancella lacseconda parte della stringa
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
		if (Num.size() > 0) for (auto comma : commands) {
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
#ifndef DEBUG
		SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
		if (Num.size() > Den.size()) {
			SetConsoleCursorPosition(hConsole, start);
			wcout << S;
			if (!script) {
				SetConsoleTextAttribute(hConsole, 6);
				wcout << command << L'\r';
				SetConsoleTextAttribute(hConsole, 15);
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
				SetConsoleTextAttribute(hConsole, 15);
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
}

// inputa un polinomio
static wstring GetLine(bool ShowSuggestions, int sizemax)
{
	int diff{};
	wstring vel, E_Vel, command{ L"rnd" };
	bool script{ true }, arrow{ false }, Continue{ false };
	while (true) if (_kbhit()) {
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
		case L'.': return L".";

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
			for (auto ch : copy)
				if (CFSuperScript(wstring(1, ch)) != wstring(1, ch))
					new_diff--;

			// aggiunta carattere
			if (!arrow) {
				if (new_diff < 0) new_diff = 0;
				auto first{ vel };
				auto last{ vel };
				first.erase(new_diff);
				last.erase(0, new_diff);
				first += c;
				vel = first + last;
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
		if (vel.size() > sizemax) {
			vel.clear();
			E_Vel.clear();
			Velpart.clear();
			diff = 0;
			wcout << L'\r' << wstring(sizemax, L' ');
		}
		script = true;
#ifndef DEBUG
		SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
		if (ShowSuggestions and !vel.empty())

			// ricerca suggerimento giusto
			for (auto comma : commands) {
				command = comma;
				auto back{ command };
				if (back.size() == vel.size()) continue;
				if (back.size() > vel.size()) back.erase(vel.size());
				if (back == E_Vel) {
					SetConsoleTextAttribute(hConsole, 6);
					wcout << L'\r' << wstring(sizemax, ' ');
					wcout << L'\r' << command;
					SetConsoleTextAttribute(hConsole, 15);

					wcout << L'\r' << E_Vel << L'\r' << Velpart;
					script = false;
					break;
				}
			}
		if (script) {
			wcout << L'\r' << wstring(sizemax, L' ');
			wcout << L'\r' << E_Vel << L'\r' << Velpart;
		}
		SetConsoleCursorInfo(hConsole, &cursor);
	}
	return vel;
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
		bool error{ true };
		bool ReturnFalse{ false };
		wcout << txt;
		check = GetLine(ShowSuggestions, 10);
		wcout << L'\n';
		if (check == L"." or check.empty()) return check;
		option = ConvertWStringToEnum(check);
		ReassigneEnum(option);
		if (option != NotAssigned) return ConvertEnumToWString(option);

		// controllo
		wregex CheckDigits(L"\\D");
		if (regex_search(check, CheckDigits)) UserNum = 0;
		else UserNum = stoull(check);

		if (UserNum < low or UserNum > high) wcout << L'\a';
	} while (UserNum < low or UserNum > high);
	return to_wstring(UserNum);
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
	SetConsoleTextAttribute(hConsole, 15);
	txt = L"inserisci il valore di inizio della ricerca\n";
	do Input = GetUserNum(txt, 1, GlobalMax, true);
	while (Input.empty());
	if (Input == L".") {
		opt = Random;
		Return = true;
		return;
	}
	opt = ConvertWStringToEnum(Input);
	ReassigneEnum(opt);
	if (opt != NotAssigned) {
		system("cls");
		SetConsoleTitle(Input.c_str());
		Return = true;
		return;
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
		return;
	}
	UpperBound = stoull(Input) + 1;

	if (UpperBound < LowerBound) swap(LowerBound, UpperBound);
	datalenght = UpperBound - LowerBound;
}

#pragma endregion

// alcune funzioni
#pragma region Primitive

// calcola se un numero è primo
static bool Prime(ptrdiff_t number)
{
	if (number <= 1) return false;
	if (number <= 3) return true;
	if (number < GlobalMax) return PrimeNumbers.is_prime[number];
	if (number % 2 == 0 or number % 3 == 0) return false;
	for (int i = 5; i * i <= number; i += 6)
		if (number % i == 0 or number % (i + 2) == 0) return true;
	return true;
}

// gestisce il secondo thread del code to number (non va)
static void UserInputThread()
{
	while (computing) {

		// controllo
		wchar_t choice{ ObjectGetCh.read() };
		if (choice == L'S' or choice == L's') {
			GlobalInterr = true;
			interrupted = true;
			return;
		}

		// riduzione uso della CPU
		sleep_for(milliseconds(100));
	}
}

// calcola i numeri primi con il crivello di eratostene
static void PrimeNCalculator(ptrdiff_t max, ptrdiff_t min)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const int BARWIDTH{ csbi.dwSize.X - 11 };

	// calcolo tensori
	tensor<int> primes{ PrimeNumbers.list_primes };
	tensor<bool> is_prime(max + 1, true);
	if (PrimeNumbers.is_prime.empty()) PrimeNumbers.is_prime = is_prime;
	else {
		is_prime = PrimeNumbers.is_prime;
		is_prime(max + 1);
	}
	int SPEED{ 50 };
	const double COEFF{ 0.3 };
	const int SQUARE{ (int)sqrt(max) + 2 };
	int iter{};
	bool PrintProgressBar = min == 0;
	if (PrintProgressBar) {
		system("cls");
		SetConsoleTextAttribute(hConsole, 4);
		wstring warning{
			L"ATTENIONE: il tempo rimanente non è accurato all'inizio"
		};
		if (BARWIDTH + 11 > warning.size()) wcout << warning;
	}

	auto begin{ steady_clock::now() };
	SetConsoleTextAttribute(hConsole, 15);
	for (int p = 2; p < SQUARE; ++p) {

		// calcolo numeri primi
		if (is_prime[p]) for (int i = min - min % p + p; i <= max; i += p)
			if (i >= p * p) is_prime[i] = 0;

		// stampa barra di avanzamento
		if (iter % SPEED == 0 and PrintProgressBar) {
			auto stop{ steady_clock::now() };

			// stampa della barra di avanzamento
			long double progress{ (long double)p / SQUARE };
			if (progress > 0.5) SPEED = 15;
			if (progress > 1) progress = 1;
			ProgressBar(progress, BARWIDTH);

			// calcolo tempo rimanente
			int time = duration_cast<milliseconds> (stop - begin).count();
			long double time_rem{ (time / progress) * (1 - progress) };
			long double time_seconds{ (long double)time_rem / 1'000 };

			// calcolo cifre decimali
			wstringstream stream;
			stream << fixed << setprecision(1) << time_seconds;
			wcout << L"\ntempo rimanente: " << stream.str() << L" [secondi]  ";
			if (SPEED < 75) SPEED += 5;
		}
		iter++;
	}

	// rimozione barra di avanzamento
	if (PrintProgressBar) {
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		wcout << wstring(BARWIDTH + 11, L'\\') << L"\n\n\r";
		wcout << wstring(BARWIDTH + 11, L' ') << L"attendere\r";
	}

	// multithreading
	if (PrintProgressBar) {
		thread t1([&]() {
			for (ptrdiff_t p = 2; p < max + 1; ++p) if (is_prime[p]) primes << p;
			lock_guard<mutex> lock(mtx);
			IsDone = true;
			cv.notify_one();
			}
		);
		thread t2(CS_CenterPrinter);
		t1.join();
		t2.join();
	}

	// push numeri primi
	else for (ptrdiff_t p = 2; p < max + 1; ++p) if (is_prime[p]) primes << p;
	PrimeNumbers = { is_prime, primes };
}

#pragma endregion

// funzioni di scomposizione di base
#pragma region Operators

// scompone un numero nei suoi fattori sottoforma di struttura
static tensor<compost> DecomposeNumber(ptrdiff_t input)
{

	// correzione intervallo di PrimeNumbers
	if (input > PrimeNumbers.list_primes.last())	
		PrimeNCalculator(input + 1'000, PrimeNumbers.is_prime.size() - 1);

	// scomposizione
	int index{};
	tensor<compost> output(12, compost{ 0, 1 });
	for (int i = 0; intpow(PrimeNumbers.list_primes[i], 2) <= input; ++i)
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

	return output;
}

// divide una scomposizione singola
static tensor<int> DecomposeStrings(wstring Terminal)
{
	int pass{};
	int CiphresElement;
	tensor<int> ciphres;
	for (int i = 0; i < Terminal.size(); ++i) {

		// salta se pass è vero
		while (pass != 0) {
			i++;
			pass--;
		}

		// eccezioni
		if (i >= Terminal.size()) return ciphres;
		if (i == Terminal.size() - 1) CiphresElement = Terminal.at(i) - L'0';

		// caso di seconda eccezione
		else if (i > Terminal.size() - 3) {
			if (Terminal.at(i + 1) == L'0') {
				CiphresElement = 10 * (Terminal.at(i) - L'0');
				pass = 1;
			}
			else CiphresElement = Terminal.at(i) - L'0';
		}

		// caso con L'.'
		else if (Terminal.at(i) == L'.') {
			CiphresElement = 10 * (Terminal.at(i + 1) - L'0')
				+ (Terminal.at(i + 2) - L'0');
			pass = 2;
		}

		// caso con gli zeri
		else {
			if (Terminal.at(i + 1) == L'0') {
				CiphresElement = 10 * (Terminal.at(i) - L'0');
				pass = 1;
			}

			// caso comune
			else CiphresElement = Terminal.at(i) - L'0';
		}

		// aggiunta
		ciphres << CiphresElement;
	}

	return ciphres;
}

// divide una scomposizione doppia
static tensor<wstring> Fractioner(wstring str)
{
	tensor<wstring> monomials;
	wstring temp;
	auto backup{ str };
	int ParenthesisBalance{}, Parenthesis{}, find{};
	for (auto ch : backup) {
		if (ch == L'(') ParenthesisBalance++;

		// solo in caso di bilancio tra le parentesi e carattere L'+'
		if (ParenthesisBalance == 0 and ch == L'+') {
			temp = str;
			for (int finder = 0; finder < temp.size(); ++finder) {

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

	return monomials;
}

// scompone un polinomio nelle sue parti (non fattori)
static tensor<tensor<wstring>> FractPolynomial(wstring pol)
{

	// controllo estremi
	while (issign(pol.at(pol.size() - 1))) pol.erase(pol.size() - 1);
	if (!issign(pol.at(0))) pol = L'+' + pol;

	// suddivisione in parti
	tensor<wstring> adders;
	int Parenthesis{};
	for (int i = pol.size() - 1; i >= 0; --i) {

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
	for (int i = 0; i < adders; ++i) {

		auto adder{ adders[i] };
		for (int j = adders[i].size() - 1; j >= 0;) {

			auto FactorPart{ adder };
			int Parenthesis{ adders[i].at(j) != L')' }, J{ j };
			for (int k = FactorPart.size() - 1; k >= 0; --k) {

				switch (FactorPart.at(k)) {
				case L'(': Parenthesis++;
					break;
				case L')': Parenthesis--;
					break;
				}

				if (Parenthesis == 0) {
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
	for (int i = 0; i < factors; ++i) for (int j = factors[i].size() - 1; j >= 0; --j)
		if (factors[i][j].empty()) factors[i].erase(factors[i].begin() + j);
	for (int i = factors.size() - 1; i >= 0; --i)
		if (factors[i].empty()) factors.erase(factors.begin() + i);

	return factors;
}

#pragma endregion

// funzioni avanzate di scomposizione
#pragma region Calc

// esegue la scomposizione doppia
static wstring Cript(ptrdiff_t input)
{

	auto expfactors{ DecomposeNumber(input) };
	while (expfactors.last().factors == 0) expfactors--;
	wstring OutputString, ExpVerify, ExpString, PrimeExp_String;
	int prime_exp, sizestring, presence;
	ptrdiff_t WhatFactor;
	bool repeat;
	wstring result;

	// itera sui fattori primi
	for (
		int FactorIndexAccesser = 0;
		FactorIndexAccesser < expfactors;
		++FactorIndexAccesser
		)
	{
		repeat = false;
		presence = 0;

		// esponente
		ExpVerify = to_wstring(expfactors[FactorIndexAccesser].exp);
		WhatFactor = expfactors[FactorIndexAccesser].factors;
		wstring start{ L"(" };
		wstring end{ L")" };

		// se l'esponente ha una cifra ed è maggiore di 1,
		if (expfactors[FactorIndexAccesser].exp != 1 and
			expfactors[FactorIndexAccesser].exp < 11)
		{
			end.append(ExpVerify);
			presence = 1;
		}

		// se l'esponente ha due cifre,
		else if (expfactors[FactorIndexAccesser].exp > 10) {
			end.append(L".");
			end.append(ExpVerify);
			presence = 2;
		}

		// si esclude il caso di un esponente a tre cifre
		auto WhatFactorString{ to_wstring(WhatFactor) };
		OutputString = start + WhatFactorString + end;

		do {
			// caso con argomento primo
			while (Prime(WhatFactor)) {

				// riduzione dell'argomento
				ptrdiff_t position{ -1 };
				for (int a = 1; ; ++a) if (PrimeNumbers.list_primes[a - 1] == WhatFactor)
				{
					position = a;
					break;
				}

				WhatFactor = position;
				WhatFactorString = to_wstring(WhatFactor);
				OutputString.erase(0, OutputString.find(L')'));
				OutputString = start + WhatFactorString + OutputString;

				// temporanea eliminazione dell'esponente normale
				switch (presence) {
				case 1:
					ExpString = wstring(1, OutputString.at(OutputString.size() - 1));
					OutputString.erase(OutputString.size() - 1);
					break;
				case 2:
					ExpString = L'.' + OutputString.at(OutputString.size() - 2)
						+ OutputString.at(OutputString.size() - 1);
					OutputString.erase(OutputString.size() - 3);
					break;
				}

				// aggiunta dell'esponente primo
				if (repeat) {
					PrimeExp_String = wstring(1, OutputString.at(OutputString.size() - 1));
					OutputString.erase(OutputString.size() - 1);
					prime_exp = stoi(PrimeExp_String);
					prime_exp++;
					PrimeExp_String = to_wstring(prime_exp);
					if (prime_exp > 10) PrimeExp_String = L'.' + PrimeExp_String;
					OutputString.append(PrimeExp_String);
				}

				// riaggiunta dell'esponente normale
				else OutputString.append(L"1");
				if (presence > 0) OutputString.append(ExpString);
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
	int position[12], j{};
	for (int i = 0; i < (result.size() - 2); ++i)
		if ((result.at(i) == L'(') and (result.at(i + 1) == L'1')
			and (result.at(i + 2) == L')'))
		{
			position[j] = i;
			j++;
		}
	for (int k = j - 1; k >= 0; --k) result.erase(position[k], 3);

	// eliminazione parentesi in più
	int l{};
	sizestring = result.size();
	if (sizestring > 4) {
		for (int m = 0; m < (result.size() - 3); ++m)
			if ((result.at(m) == L'(') and (result.at(m + 3) == L')'))
			{
				position[l] = m;
				l++;
			}
		for (int m = l - 1; m >= 0; --m) {
			result.erase(position[m] + 3, 1);
			result.erase(position[m], 1);
		}
	}

	return result;
}

// esegue la scomposizione singola
static wstring FactNumber(ptrdiff_t input)
{
	auto expfactors{ DecomposeNumber(input) };
	while (expfactors.last().factors == 0) expfactors--;

	// unione dei monomi
	wstring output;
	for (int i = 0; i < expfactors; ++i) {
		output += to_wstring(expfactors[i].factors);
		if (expfactors[i].exp != 1) output += L'^' + to_wstring(expfactors[i].exp);
		output += L" * ";
	}

	// rimozione della fine
	output.erase(output.size() - 3);

	return output;
}

// calcola il valore aritmetico di un'espressione
static int ExeStrings(wstring input)
{
	int output{};
	int location{};
	bool presence{ true };
	int values[12];
	for (int i = 0; i < input.size(); ++i) if (input.at(i) == L'.') input.erase(i, 1);
	tensor<wstring> parts{ Fractioner(input) };

	for (int i = 0; i < parts; ++i)
	{
		// caso con le parentesi
		if (parts[i].at(0) == L'(') {

			// acquisizione dati
			for (int j = parts[i].size() - 1; j >= 0; --j)
				if ((presence) and (parts[i].at(j) == L')')) {
					presence = false;
					location = j;
				}

			// calcolo risultato
			auto temp{ parts[i] };
			temp.erase(location);
			temp.erase(0, 1);
			parts[i].erase(0, location + 1);
			values[i] = ExeStrings(temp) * (stoi(parts[i]));
		}

		// caso senza parentesi
		else values[i] = stoi(parts[i]);
		presence = true;
	}

	// somma dei monomi
	for (int end = 0; end < parts.size(); ++end) output += values[end];

	return output;
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
	for (int i = factor.size() - 1; i >= 0; --i) if (factor.at(i) == L'*')
	{
		auto backup{ factor };
		backup.erase(0, i + 2);
		if (backup.at(backup.size() - 1) == L' ') backup.erase(backup.size() - 1);
		parts << backup;
		factor.erase(i);
	}

	// eccezione
	if (factor.at(factor.size() - 1) == L' ') factor.erase(factor.size() - 1);
	parts << factor;

	// ricavo della scomposizione
	for (int i = 0; i < parts.size(); ++i) {
		ptrdiff_t value{};
		int exp{ 1 };
		ExpPresence = false;
		for (int j = 1; j < parts[i].size(); ++j)
			if (parts[i].at(j) == L'^') {
				auto first{ parts[i] };
				auto second{ parts[i] };
				first.erase(j);
				second.erase(0, j + 1);
				value = stoi(first);
				exp = stoi(second);
				ExpPresence = true;
			}
		if (!ExpPresence) value = stoi(parts[i]);
		values << value;
		exponents << exp;
	}

	// calcolo del numero dei divisori
	for (int i = 0; i < parts; ++i) output.DivNumber *= exponents[i] + 1;

	// calcolo del numero risultato e della sua somma dei divisori
	ptrdiff_t x{ 1 };
	for (int i = 0; i < parts; ++i) {
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

	return output;
}

// calcola i dati riguardanti le cifre di un numero
static digitRatio DigitRationalizer(ptrdiff_t inpt)
{

	// calcolo somma e prodotto cifre
	digitRatio output;
	int digit_sum{}, digit_product{ 1 };
	auto input{ to_string(inpt) };
	for (int i = 0; i < input.size(); ++i) {
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
	return output;
}

// elenca i divisori di un numero
static tensor<int> DivisorCounter(int num)
{

	// creazione dei tensori con i principali fattori
	tensor<int> vec;
	tensor<compost> expfact{ DecomposeNumber(num) };
	while (expfact.last().factors == 0) expfact--;

	tensor<tensor<int>> MainDiv;
	for (int i = 0; i < expfact; ++i) {
		MainDiv++;
		int EFelement{ 1 };
		for (int j = 0; j <= expfact[i].exp; ++j) {
			MainDiv[i] << EFelement;
			EFelement *= expfact[i].factors;
		}
	}

	// prodotto cartesiano
	tensor<int> temp;
	for (int i = MainDiv.size() - 1; i > 0; --i) {
		for (auto a : MainDiv[i]) for (auto b : MainDiv[i - 1]) temp << a * b;
		MainDiv[i - 1] = temp;
		MainDiv--;
	}

	return MainDiv[0];
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
	return output;
}

// calcola codice, grado e sequenza
static NumberData ExecuteDegree(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	int counter{};
	int copy = input;

	// iterazione per ottenere grado e sequenza
	do {
		output.sequence << copy;
		copy = ExeStrings(Cript(copy));
		counter++;
		if (copy < 4) output.degree = counter + copy;
	} while (copy != 1);

	output.sequence << 1;
	copy = input;
	return output;
}

// calcola la fattorizzazione
static NumberData ExecuteSimpleFact(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.expression = FactNumber(input);
	return output;
}

// calcola fattorizzazione e divisori
static NumberData ExecuteFactor(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.expression = FactNumber(input);
	divisor D{ DivisorCalculator(output.expression) };
	output.div = D;
	return output;
}

// calcola fattorizzazione e codice
static NumberData ExecuteSimpleDF(ptrdiff_t input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	output.expression = FactNumber(input);
	return output;
}

// calcola le cifre (beta)
static NumberData ExecuteDigit(ptrdiff_t input)
{
	NumberData output;
	digitRatio D{ DigitRationalizer(input) };
	output.number = input;
	output.digit = D;
	return output;
}

// calcola codice, grado, sequenza, fattorizzazione e divisori
static NumberData ExecuteDegFactor(ptrdiff_t input)
{
	NumberData A{ ExecuteDegree(input) };
	NumberData B{ ExecuteFactor(input) };
	A.expression = B.expression;
	A.div = B.div;
	return A;
}

// calcola codice, grado, sequenza e cifre
static NumberData ExecuteDegDigit(ptrdiff_t input)
{
	NumberData B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0)
		return B;
	NumberData A{ ExecuteDegree(input) };
	A.digit = B.digit;
	return A;
}

// calcola fattorizzazione, divisori e cifre
static NumberData ExecuteFactDigit(ptrdiff_t input)
{
	NumberData B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0)
		return B;
	NumberData A{ ExecuteFactor(input) };
	A.digit = B.digit;
	return A;
}

// calcola codice, grado, sequenza, fattorizzazione, divisori e cifre
static NumberData ExecuteAll(ptrdiff_t input)
{
	NumberData C{ ExecuteDigit(input) };
	if (C.digit.digitSumRatioNum == 0 and
		C.digit.digitProductRatioNum == 0)
		return C;
	NumberData A{ ExecuteDegree(input) };
	NumberData B{ ExecuteFactor(input) };
	A.expression = B.expression;
	A.div = B.div;
	A.digit = C.digit;
	return A;
}

#pragma endregion

// funzioni per validare un input utente
#pragma region Convalid

// gestisce la convalidazione di un polinomio con le parentesi
static wstring PolynomialSyntaxDirector(wstring pol)
{
	
	// controllo asterischi
	if (pol.at(0) == L'*' or pol.at(pol.size() - 1) == L'*')
		return L"manca un termine";
	for (int i = pol.size() - 2; i > 0; --i) if (pol.at(i) == L'*') {
		if (pol.at(i - 1) == '(' or pol.at(i + 1) == ')')
			return L"un asterisco non può essere racchiuso tra parentesi";
		if (pol.at(i - 1) == ')' or pol.at(i + 1) == '(') {
			pol.erase(i, 1);
			continue;
		}
		if (!isalnum(pol.at(i - 1)) or !isalnum(pol.at(i + 1)))
			return L"asterisco nel punto sbagliato";
		pol.erase(i, 1);
	}

	// caso vuoto
	for (int i = 0; i < (int)pol.size() - 2; ++i)
		if (pol.at(i) == L'(' and pol.at(i + 1) == L')')
			return L"il polinomio non può essere void";
	if (pol.empty()) return L"il polinomio non può essere void";

	// senza parentesi
	auto copy{ pol };
	if (copy.size() >= 2) {
		if (copy.at(0) == L'(') copy.erase(0, 1);
		if (copy.at(copy.size() - 1) == L')') copy.erase(copy.size() - 1);
	}
	if (copy.find(L'(') == wstring::npos and copy.find(L')') == wstring::npos)
		return PolynomialSyntax(copy);

	// controllo bilancio parentesi
	bool balanced{ false };
balance:
	int ParenthesisBalance{};
	for (auto c : copy) {
		switch (c) {
		case L'(': ParenthesisBalance++;
			break;
		case L')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) {
			if (!balanced) break;
			return L"le parentesi sono invertite";
		}
	}
	if (ParenthesisBalance == 0) pol = copy;
	else if (!balanced) {
		balanced = true;
		copy = pol;
		goto balance;
	}
	else return L"le parentesi sono sbilanciate";

	// rimozione spazi
	for (int i = pol.size() - 1; i >= 0; --i)
		if (pol.at(i) == L' ' or pol.at(i) == L'\t') pol.erase(i, 1);

	// controllo caratteri non ammessi
	for (auto c : pol)
		if (!isalnum(c) and !issign(c) and c != L'(' and c != L')' and c != L'^')
			return L"il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	bool error{ true };
	for (auto c : pol) if (!issign(c)) error = false;
	if (error) return L"non è presente alcun monomio";
	for (int i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1))) return L"manca un monomio";
	if (pol.at(0) == L'^') return L"manca la base rispetto al relativo esponente";

	// controllo di ogni parte
	auto fact = FractPolynomial(pol);
	for (auto adder : fact) if (adder > 10) return L"il polinomio è troppo grande";
	for (auto adder : fact) for (auto element : adder) {
		if (PolynomialSyntaxDirector(element).empty()) continue;

		bool exp{ element.size() > 1 and element.size() < 4 };
		if (exp) if (element.at(0) == L'^')
			for (int i = 1; i < element.size(); ++i) if (!isdigit(element.at(i)))
				return L"gli esponenti devono essere costanti";
	}

	return L"";
}

// convalida un polinomio senza parentesi
static wstring PolynomialSyntax(wstring pol)
{

	// caso vuoto
	if (pol.empty()) return L"il polinomio non può essere void";

	// controllo caratteri ammessi
	for (auto c : pol) if (!isalnum(c) and c != L'^' and c != L' ' and !issign(c))
		return L"il polinomio presenta dei caratteri non ammessi";

	// controllo segni
	for (int i = 1; i < pol.size(); ++i)
		if (issign(pol.at(i)) and issign(pol.at(i - 1)))
			return L"manca un monomio";
	if (!issign(pol.at(0))) pol = L'+' + pol;
	if (issign(pol.at(pol.size() - 1)))
		return L"manca un monomio";

	// controllo esponenti in forma di numero
	for (int i = 0; i < pol.size() - 1; ++i)
		if (pol.at(i) == L'^' and !isdigit(pol.at(i + 1)))
			return L"gli esponenti devono essere costanti";

	// suddivisione in parti
	tensor <wstring> parts;
	for (int i = pol.size() - 1; i >= 0; --i)
		if (issign(pol.at(i))) {
			auto part{ pol };
			part.erase(0, i + 1);
			pol.erase(i);
			parts << part;
		}

	for (auto part : parts) {

		// cancellamento coefficiente
		while (isdigit(part.at(0))) {
			part.erase(0, 1);
			if (part.empty()) break;
		}
		if (part.empty()) continue;

		// controllo estremi
		if (part.at(0) == L'^' or part.at(part.size() - 1) == L'^')
			return L"manca la base rispetto al relativo esponente";

		// controllo variabili ripetute
		for (int i = 0; i < part.size(); ++i)
			for (int j = i + 1; j < part.size(); ++j)
				if (isalpha(part.at(i)) and part.at(i) == part.at(j))
					return L"non è possibile ripetere le variabili nello stesso monomio";

		// controllo limite esponenti
		for (int i = 0; i < part.size() - 1; ++i) if (isdigit(part.at(i)))
			for (int j = i; j < part.size(); ++j) {
				if (j >= part.size()) break;
				if (!isdigit(part.at(j))) break;
				if (j - i >= 2) return L"gli esponenti sono troppo grandi";
			}

		// controllo coefficienti corretti
		for (int i = 1; i < part.size(); ++i) if (
			isdigit(part.at(i)) and
			!isdigit(part.at(i - 1)) and
			part.at(i - 1) != L'^'
			)
			return L"il coefficiente deve precedere il monomio";
	}

	return L"";
}

// aggiorna una stringa di codice
static wstring UpdateString(wstring& ToEvaluate)
{
	// controllo sulle doppie parentesi
	int BoundaryBalance{};
	for (auto c : ToEvaluate) {
		switch (c) {
		case L'<': BoundaryBalance++;
			break;
		case L'>': BoundaryBalance--;
			break;
		}
		if (BoundaryBalance > 1 or BoundaryBalance < 0)
			return L"le parentesi di delimitazione non possono essere doppie";
	}

	// suddivisione della stringa in pezzi
	tensor<wstring> pieces;
	bool start{ true };
	for (int i = ToEvaluate.size() - 1; i >= 0; --i) {

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
		if (piece.at(0) == L'<' and piece.at(piece.size() - 1) == L'>') {
			piece.erase(piece.size() - 1);
			piece.erase(0, 1);
		}
		if (piece.find(L'<') != wstring::npos or piece.find(L'>') != wstring::npos)
			return L"le parentesi di delimitazione sono al contrario";
	}

	// creazione nuova stringa
	ToEvaluate.clear();
	for (auto piece : pieces) {
		if (piece.empty()) continue;
		if (piece.at(0) == L'<') {
			piece.erase(piece.size() - 1);
			piece.erase(0, 1);
			ToEvaluate = piece + ToEvaluate;
		}
		else {
			for (int i = piece.size() - 1; i >= 0; --i)
				if (!isdigit(piece.at(i))) piece.erase(i, 1);
			if (piece.empty()) continue;
			int number = stoi(piece);
			if (number > GlobalMax or number <= 0) return L"XRANGE";
			ToEvaluate = Cript(number) + ToEvaluate;
		}
	}
	return L"";
}

// convalida una stringa di codice
static wstring NumberCodeSyntax(wstring ToEvaluate)
{
	if (ToEvaluate == L"f") return L"";
	tensor<wstring> mono;
	wstring CharsAllowed{ L"0123456789+(_)." };
	bool LocError{ true };
	int ParenthesisBalance{}, count{};

	// eliminazione degli spazi e dei tab
	for (int space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
			ToEvaluate.erase(space, 1);

	// ricerca del bilancio tra le parentesi
	for (int i = 0; i < ToEvaluate.size(); ++i) {
		switch (ToEvaluate.at(i)) {
		case '(': ParenthesisBalance++;
			break;
		case ')': ParenthesisBalance--;
			break;
		}
		if (ParenthesisBalance < 0) return L"le parentesi sono invertite";
	}
	if (ParenthesisBalance != 0) return L"le parentesi sono sbilanciate";

	// se la stringa è vuota
	if (ToEvaluate.empty()) return L"la stringa è vuota";

	// se la stringa contiene caratteri non ammessi
	wregex unallowed_chars(L"[^\\d+()._]");
	if (regex_search(ToEvaluate, unallowed_chars))
		return L"sono presenti dei caratteri non ammessi";

	// controllo sugli estremi
	if (ToEvaluate.at(0) == L'+') return L"manca un monomio a inizio stringa";
	if (ToEvaluate.at(0) == L'0') return L"un monomio non può essere null";
	if (ToEvaluate.at(0) == L')') return L"le parentesi sono al contrario";
	if (ToEvaluate.at(ToEvaluate.size() - 1) == L'+')
		return L"manca un monomio alla fine della stringa";

	// controllo sulla non consecutività dei L'+'
	wregex no_monomial_(L"\\+{2,}");
	if (regex_search(ToEvaluate, no_monomial_))
		return L"manca un monomio al centro della stringa";

	// controlli sugli zeri
	wregex cons_null_digits(L"0{2,}");
	if (regex_search(ToEvaluate, cons_null_digits))
		return L"le cifre null non possono essere consecutive";
	wregex excep_no_digits(L"\\.");
	wregex no_digits(L"[_\\d]\\.[_1-9][_\\d]");
	if (regex_search(ToEvaluate, excep_no_digits))
		if (!regex_search(ToEvaluate, no_digits))
			return L"esponente a due cifre impostato in modo errato";
	wregex s_null_digits(L"[\\r\\D]0");
	if (regex_search(ToEvaluate, s_null_digits))
		return L"un monomio non può essere null";

	mono = Fractioner(ToEvaluate);

	// per ogni monomio
	for (int indexof = 0; indexof < mono; ++indexof) {
		int stackfinder{ -1 }, stickfinder{ -1 }, FindIndex{ -1 };
		bool stop{ false }, pass{ false };
		int res{};
		tensor<int> min_ciphres, max_ciphres;
		tensor<int> ciphr_min, ciphr_max;
		wstring min, max;
		auto stack{ mono[indexof] };

		// per ogni secondo monomio
		for (int second = 1; second < mono; ++second) {
			if (indexof != second) {
				if (mono[indexof] == mono[second]) return L"1";
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
						for (int l = 0; l < ciphr_min; ++l) {
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
					for (int l = 0; l < ciphr_min; ++l) {
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
					return L"2";
			}
		}

		// // controlli sugli oggetti adiacenti alle parentesi
		for (int i = stack.size() - 1; i >= 0; --i) if (stack.at(i) == ')') {
			FindIndex = i;
			break;
		}
		if (stack.at(stack.size() - 1) == L')')
			return L"manca l'esponente di fianco a una parentesi";
		if (stack.at(stack.size() - 1) == L'(')
			return L"le parentesi sono al contrario";
		if (stack.at(0) == L'(') {

			// controllo sulla necessità delle parentesi
			LocError = true;
			for (int checkplus = 1; checkplus < FindIndex; ++checkplus)
				if (stack.at(checkplus) == L'+') LocError = false;
			if (LocError) return L"ci sono troppe parentesi";

			stack.erase(0, 1);
			stack.erase(FindIndex - 1);
			auto message{ NumberCodeSyntax(stack) };
			if (!message.empty()) return message;
		}
		else if (mono[indexof].at(0) == L')') return L"le parentesi sono al contrario";
		else for (int check = 1; check < mono[indexof].size(); ++check) {
			if (mono[indexof].at(check) == L'(')
				return L"l'esponente non può precedere una parentesi";
			if (mono[indexof].at(check) == L')')
				return L"l'esponente non può precedere una parentesi";
		}
		// //
	}

	return L"";
}

#pragma endregion

// funzioni per convertire da codice a numero
#pragma region Converters

// calcola il valore di un singolo elemento del codice
static size_t NumberConverter(size_t root, wstring M)
{
	bool WhichWay{ true }, XOutOfRange{ false };
	bool UselessExponent{ false }, pass{ false };
	bool XSubscriptOutOfRange{ false };
	int size = PrimeNumbers.list_primes.size(), nums;
	auto ciphres{ DecomposeStrings(M) };

	// per ogni cifra
	for (int iter = 0; iter < ciphres; ++iter) {

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
	if (XSubscriptOutOfRange) return -3;
	if (UselessExponent) return -2;
	if (XOutOfRange) return -1;

	return root;
}

// calcola il valore del codice di codice
static size_t StringConverter(wstring ToEvaluate)
{
	size_t integer{ 1 };
	auto mono{ Fractioner(ToEvaluate) };
	int sizeP = PrimeNumbers.list_primes.size();

	// per ogni monomio
	for (int indexof = 0; indexof < mono; ++indexof) {

		// calcolo indice
		auto M{ mono[indexof] };
		int FindIndex;
		for (int i = M.size() - 1; i >= 0; --i) if (M.at(i) == ')') {
			FindIndex = i;
			break;
		}
		ptrdiff_t root;
		bool WhichWay{ false };

		if (M.at(0) != L'(') root = NumberConverter(1, M);
		else {

			// calcolo valori
			auto first{ M };
			auto second{ M };
			second.erase(0, FindIndex + 1);
			first.erase(FindIndex);
			first.erase(0, 1);
			root = NumberConverter(StringConverter(first), second);

		}
		if (root < 0) return root; // eccezione
		else integer *= root; // caso comune
	}

	return integer;
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
	if (ToEvaluate == L"f") return;

	for (int space = ToEvaluate.size() - 1; space >= 0; --space)
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
	tensor<int> pos;
	for (int i = 0; i < ToEvaluate.size(); ++i) if (ToEvaluate.at(i) == L'_') {
		pos << i;
		counter++;
	}

	// caso di stringa univoca
	lock_guard<mutex> lock(CoutMutex);
	if (counter == 0) {
		CodeConverter(ToEvaluate, message, ShowErrors, NecBoundary);
		for (auto Console : ConsoleText) {
			SetConsoleTextAttribute(hConsole, Console.Attribute);
			wcout << Console.Text;
			SetConsoleTextAttribute(hConsole, 15);
		}
		ConsoleText.clear();
	}

	// caso di stringa ripetuta
	else for (int i = 0; i < intpow(10, counter); ++i) {

		// passa variabili per indirizzo
		thread t1([&]() {

			auto j{ to_wstring(i) };
			backup = ToEvaluate;
			int ZerosCount = counter - j.size();
			for (int k = 0; k < ZerosCount; ++k) j = L"0" + j;
			for (int k = 0; k < j.size(); ++k)
				backup.replace(pos[k], 1, wstring(1, j.at(k)));
			if (NecBoundary) UpdateString(backup);
			message = NumberCodeSyntax(backup);

			// eventuale stampa degli errori
			lock_guard<mutex> lock(mtx);
			if (message.size() > 1 and ShowErrors) {

				auto text{ L"codice <" + backup + L"> :\n" };
				ConsoleText << Console{ text , 11 };

				text = L"ERR[404]: " + message + L"\n";
				ConsoleText << Console{ text , 4 };
			}
			else CodeConverter(backup, message, ShowErrors, false);
			if (interrupted) return;

			IsDone = true;
			cv.notify_one();

			}
		);
		thread t2(CS_CornerPrinter);
		t1.join();
		t2.join();

		for (auto a : ConsoleText) {
			SetConsoleTextAttribute(hConsole, a.Attribute);
			wcout << a.Text;
			SetConsoleTextAttribute(hConsole, 15);
		}
		ConsoleText.clear();
	}
	computing = false;
	Cv.notify_one();
}

#pragma endregion

// funzioni necessarie per tradurre i polinomi in strutture
#pragma region Translate

// modifica gli asterischi trasformandoli in parentesi
// e poi traduce il polinomio in una struttura
static polynomial<big> GetMonomialsAssister(wstring pol)
{
	for (int index = pol.size() - 2; index > 0; --index)
		if (pol.at(index) == L'*' and
			pol.at(index - 1) != ')' and pol.at(index + 1) != '(')
		{

			// calcolo indici
			bool AssignedStart{ false }, AssignedEnd{ false };
			int startIndex{}, endIndex = pol.size() - 1;
			int StartBalance{}, EndBalance{};
			for (int i = index - 1; i >= 0; --i) {
				if (pol.at(i) == ')') StartBalance--;
				if (pol.at(i) == '(') StartBalance++;
				if (issign(pol.at(i)) or StartBalance == 1)
				{
					startIndex = i;
					AssignedStart = true;
					break;
				}
			}
			for (int i = index + 1; i < pol.size() - 1; ++i) {
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
			if (AssignedStart) start.erase(startIndex + (pol.at(startIndex) != L'('));
			else start.clear();
			if (AssignedEnd) last.erase(endIndex);
			last.erase(0, index + 1);
			first.erase(index);
			if (AssignedStart) first.erase(0, startIndex + 1);

			pol = start + L'(' + first + L")(" + last + L')' + end;
		}
	for (int i = pol.size() - 1; i >= 0; --i) if (pol.at(i) == L'*') pol.erase(i, 1);
	return GetMonomialsDirector(pol);
}

// gestisce la traduzione di un polinomio con le parentesi
static polynomial<big> GetMonomialsDirector(wstring pol, bool changx)
{

	// calcolo variabili
	if (changx) {
		Variables.clear();
		for (auto c : pol) if (isalpha(c)) {
			bool IsTheVariableSet{ false };
			for (auto Variable : Variables) if (Variable == c)
				IsTheVariableSet = true;
			if (!IsTheVariableSet) Variables += c;
		}
		if (Variables.empty()) Variables = L"x";
	}

	// caso senza parentesi
	auto copy{ pol };
	if (copy.size() >= 2) {
		if (copy.at(0) == L'(') copy.erase(0, 1);
		if (copy.at(copy.size() - 1) == L')') copy.erase(copy.size() - 1);
	}
	if (copy.find(L'(') == wstring::npos and copy.find(L')') == wstring::npos)
		return polynomial<big>({ PolynomialSum(GetMonomials(copy)) });

	// eliminazione parentesi in più
	int ParenthesisBalance{};
	for (auto c : copy) {
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
	auto fact = FractPolynomial(pol);
	tensor<int> null(Variables.size(), 0);

	tensor<polynomial<big>> Union;
	tensor<long double> ExpPos, ExpVal;
	for (auto adder : fact) {
		polynomial<big> UnionElement(adder.size());
		for (int i = 0; i < adder; ++i) {

			// esponente
			if (adder[i].at(0) == L'^') {
				int value{ adder[i].at(1) - L'0' };
				if (adder[i].size() > 2)
					value = 10 * value + adder[i].at(2) - L'0';
				ExpPos << i;
				ExpVal << value;
			}

			// fattore
			else UnionElement[i] =
				PolynomialMultiply<big>(GetMonomialsDirector(adder[i], false));
		}

		// aggiunta
		for (int i = 0; i < ExpPos; ++i)
			UnionElement[ExpPos[i]] = { { ExpVal[i], {-1} } };
		Union << UnionElement;
	}

	// aggiunta di spazio
	for (int i = 0; i < Union; ++i) for (int j = 0; j < Union[i]; ++j) {
		for (int k = 0; k < Union[i][j]; ++k) Union[i][j][k].exp(Variables.size(), 0);
		Union[i][j] = PolynomialSum(Union[i][j]);
	}

	// aggiustamento segni
	tensor<big> numbers;
	for (int i = 0; i < Union; ++i) {
		Union[i].open();

		// calcolo segno
		int sign{ 1 };
		for (int j = 0; j < Union[i]; ++j) {
			Union[i][j].SortByExponents();
			if (Union[i][j][0].coefficient < 0) {
				sign *= -1;
				for (int k = 0; k < Union[i][j]; ++k)
					Union[i][j][k].coefficient.invert();
			}
		}

		// calcolo coefficiente
		big Coeff( sign );
		for (int j = Union[i].size() - 1; j >= 0; --j) if (Union[i][j] == 1)
		{
			bool IsACoefficient{ true };
			for (int k = 0; k < Variables.size(); ++k)
				if (Union[i][j][0].exp[k] != 0) IsACoefficient = false;
			if (IsACoefficient) {
				Coeff *= Union[i][j][0].coefficient;
				Union[i].erase(Union[i].begin() + j);
			}
		}

		// push coefficiente
		Union[i] >> factor<big>({ monomial<big>({Coeff, null}) });
		numbers << Coeff;
	}
	auto gcd{ Gcd(numbers) };
	if (gcd == -1)
		for (int i = 0; i < Union; ++i) Union[i][0][0].coefficient.invert();
	else if (gcd != 1)
		for (int i = 0; i < Union; ++i) Union[i][0][0].coefficient /= gcd;

	// ricerca fattori in comune
	auto ListCommonFactors{ Union[0] };
	--ListCommonFactors;
	for (int i = ListCommonFactors.size() - 1; i >= 0; --i) {
		bool IsCommon{ true };
		for (int j = 1; j < Union; ++j) {
		
			bool common{ false };
			for (int k = 0; k < Union[j]; ++k)
				if (ListCommonFactors[i] == Union[j][k]) common = true;

			if (!common) {
				IsCommon = false;
				break;
			}
		}

		if (!IsCommon) ListCommonFactors.erase(ListCommonFactors.begin() + i);
	}

	// rimozione fattori in comune
	for (int i = 0; i < Union; ++i)
		for (int k = 0; k < ListCommonFactors; ++k)
			for (int j = Union[i].size() - 1; j >= 0; --j)
				if (Union[i][j] == ListCommonFactors[k]) {
					Union[i].erase(Union[i].begin() + j);
					break;
				}
	ListCommonFactors >> factor<big>{ monomial<big>{ gcd, null } };
	
	// calcolo prodotti
	tensor<factor<big>> products;
	for (auto Adder : Union) products << PolynomialMultiply<big>(Adder);
	
	// calcolo somma dei prodotti
	factor<big> Sum;
	for (auto product : products) Sum += product;
	ListCommonFactors << PolynomialSum(Sum);

	// correzione termine polinomio
	if (ListCommonFactors.last() == factor<big>({ monomial<big>({1, null}) }))
		ListCommonFactors--;
	for (int i = 0; i < ListCommonFactors; ++i)
		if (ListCommonFactors[i] == 1) if (ListCommonFactors[i][0].coefficient < 0)
		{
			ListCommonFactors[i][0].coefficient.invert();
			ListCommonFactors[0][0].coefficient.invert();
		}

	// aggiustamento coefficiente
	if (ListCommonFactors[0] == factor<big>{ {1, null} } and ListCommonFactors > 1)
		--ListCommonFactors;
	else if (ListCommonFactors[0] == factor<big>{ {-1, null} } and
		ListCommonFactors > 1)
	{
		--ListCommonFactors;
		for (int i = 0; i < ListCommonFactors[0]; ++i)
			ListCommonFactors[0][i].coefficient.invert();
	}

	ListCommonFactors.close();
	return ListCommonFactors;
}

// traduce un polinomio senza parentesi
static factor<big> GetMonomials(wstring pol)
{
	factor<big> out;
	if (pol.empty()) return {};
	if (!issign(pol.at(0))) pol = L'+' + pol;
	for (int i = pol.size() - 1; i >= 0; --i) if (issign(pol.at(i))) {
		auto part{ pol };
		pol.erase(i);
		part.erase(0, i);

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
		for (int i = 0; i < coeff.size(); ++i) {
			Coeff += coeff.at(i) - '0';
			if (i < coeff.size() - 1) Coeff *= 10;
		}
		if (coeff.empty()) Coeff = 1;
		if (mono.coefficient == -1) Coeff.invert();
		mono.coefficient = Coeff;
		if (part.empty()) {
			out << mono;
			continue;
		}

		// calcolo gradi
		for (int j = 0; j < part.size(); ++j) if (isalpha(part.at(j))) {

			// calcolo posizione
			int VariableIndex;
			for (int k = 0; k < Variables.size(); ++k)
				if (Variables.at(k) == part.at(j)) {
					VariableIndex = k;
					break;
				}

			// calcolo grado
			int degree{ 1 };
			if (j < (int)part.size() - 2)
				if (part.at(j + 1) == L'^' and isdigit(part.at(j + 2))) {
					degree = part.at(j + 2) - L'0';
					if (j < (int)part.size() - 3) if (isdigit(part.at(j + 3)))
						degree = 10 * degree + part.at(j + 3) - L'0';
				}
			mono.exp[VariableIndex] = degree;
		}
		out << mono;
	}

	return out;
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
	for (int i = 0; i < Variables.size(); ++i)
		if (DirectorDegSequence[i] > 0 and KnownDegSequence[i] > 0) return {};
	for (int i = Variables.size() - 1; i >= 0; --i)
		if (DirectorDegSequence[i] > 0 or KnownDegSequence[i] > 0) StartIndex = i;

	int Size{ Gcd(vect[0].exp + vect.last().exp) };
	auto listSizes{ DivisorCounter(Size) };

	// controllo degli esponenti
	for (auto size : listSizes) {
		bool keep{ false };
		if (size + 1 < vect) continue;

		// riduzione
		auto DirectorSeq{ DirectorDegSequence };
		auto KnownSeq{ KnownDegSequence };
		for (int i = 0; i < Variables.size(); ++i) {
			DirectorSeq[i] /= size;
			KnownSeq[i] /= size;
		}

		// controllo esponenti centrali
		for (int i = 1; i + 1 < vect; ++i) {
			int FirstDiv{ -1 }, SecondDiv{ -1 };

			for (int j = 0; j < Variables.size(); ++j) {
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
	for (auto CorrectSize : CorrectSizes) {

		// ridimensionamento esponenti
		auto DirectorSeq{ DirectorDegSequence };
		auto KnownSeq{ KnownDegSequence };
		for (int i = StartIndex; i < Variables.size(); ++i) {
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
		for (int i = StartIndex; i < Variables.size(); ++i)
			if (KnownSeq[i] > 0) {
				KnVarPos = i;
				break;
			}
		bool skip{ false };
		for (int i = 0; i < vect; ++i) {
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
	return result;
}

// somma un fattore di un polinomio
template<typename T_int = long double>
static factor<T_int> PolynomialSum(factor<T_int> vect)
{

	// ricerca di monomi simili
	for (int i = vect.size() - 1; i >= 0; --i) for (int j = i - 1; j >= 0; --j)
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
	for (int i = vect.size() - 1; i >= 0; --i)
		if (vect[i].coefficient == 0) vect[i].exp.clear();

	// rimozione
	auto it = remove(vect.begin(), vect.end(), monomial<T_int>{ 0, {} });
	vect.erase(it, vect.end());

	return vect;
}

// moltiplica un polinomio (inverso della scomposizione)
template<typename T_int = long double>
static factor<T_int> PolynomialMultiply(polynomial<T_int> Polynomial)
{
	if (Polynomial.empty()) return { {1, tensor(Variables.size(), 0)} };
	Polynomial.open();
	while (Polynomial > 1) {

		monomial<T_int> temp;
		factor<T_int> Temp;
		for (auto A : Polynomial[0])
			for (auto B : Polynomial[1]) {
				temp.coefficient = A.coefficient * B.coefficient;
				temp.exp.clear();
				for (int i = 0; i < Variables.size(); ++i)
					temp.exp << A.exp[i] + B.exp[i];
				Temp << temp;
			}
		--(--Polynomial);
		Polynomial >> Temp;
	}
	return PolynomialSum(Polynomial[0]);
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
		int deg = dividend[0].degree;
		int _deg = divisor[0].degree;
		long double rest_element{ dividend[0].coefficient };
		rest_element /= divisor[0].coefficient;
		CORRECTION_RATIO *= divisor[0].coefficient;

		for (int i = 0; i < divide; ++i) {
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
	for (int i = 0; i < quotient; ++i) quotient[i].coefficient *= CORRECTION_RATIO;
	for (int i = 0; i < rest; ++i) rest[i].coefficient *= CORRECTION_RATIO;
	int gcd{ abs(Gcd(quotient + rest)) };
	for (int i = 0; i < quotient; ++i) quotient[i].coefficient /= gcd;
	for (int i = 0; i < rest; ++i) rest[i].coefficient /= gcd;
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
	if (vect <= 1) return output;

	// calcolo grado minimo e riscrittura
	bool positive_min{ false };
	int GCD{ Gcd(vect) };
	tensor<int> exponents;
	for (int i = 0; i < Variables.size(); ++i) {
		int min{ vect[0].exp[i] };
		for (auto t : vect) if (t.exp[i] < min) min = t.exp[i];
		exponents << min;
		if (min > 0) positive_min = 1;
	}
	if (abs(GCD) != 1 or positive_min) {
		output.clear();
		output << factor<>{ {(long double)GCD, exponents} };
		for (int i = 0; i < vect; ++i) {
			vect[i].coefficient /= GCD;
			for (int j = 0; j < Variables.size(); ++j) vect[i].exp[j] -= exponents[j];
		}
	}

	// totale
	if (abs(GCD) != 1 or positive_min) {
		output.clear();
		output << factor<>{ {(long double)GCD, exponents} } << vect;
		return output;
	}
	return { vect };
}

// raccoglimento parziale
static polynomial<> Partial(factor<> vect)
{

	// filtro tensori a quattro termini
	polynomial<> outp;
	outp << vect;
	if (vect != 4) return outp;
	tensor<int> null(Variables.size(), 0);

	// riassegnazione e dichiarazioni
	factor<> part_1{ vect[0], vect[1] };
	factor<> part_2{ vect[2], vect[3] };
	auto Part1{ Total(part_1) };
	auto Part2{ Total(part_2) };
	if (PolynomialSum<long double>(Part1.last() + Part2.last()).empty()) {
		if (Part1 == 1) swap(Part1, Part2);
		Part2 >> factor<>{ { -1, null } };
		for (int i = 0; i < Part2[1]; ++i) Part2[1][i].coefficient *= -1;
	}
	part_1 = Part1.last();
	part_2 = Part2.last();
	if (part_1 != part_2) return outp;
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

	return outp;
}

// potenza di binomio
static polynomial<> Binomial(factor<> vect)
{
	
	// filtro per tensori con più di un termine
	polynomial<> outp;
	outp << vect;
	int exponent = vect.size() - 1, sign{ 1 };
	if (exponent <= 1) return outp;
	bool reassigne{ false };
	vect.SortByDegree();

	// calcolo del monomio modificatore dell'esponente
	tensor<int> modifier(Variables.size(), 0);
	modifier[0] = -1;

	auto A{ vect[0] };
	auto B{ vect.last() };

	// controllo per evitare radici impossibili da eseguire nei reali
	if (exponent % 2 == 0 and (A.coefficient < 0 or B.coefficient < 0)) return outp;

	// calcolo delle radici
	double Sq_A, Sq_B;
	if (A.coefficient > 0) Sq_A = pow(A.coefficient, 1.0 / exponent);
	else Sq_A = -pow(-A.coefficient, 1.0 / exponent);
	if (B.coefficient > 0) Sq_B = pow(B.coefficient, 1.0 / exponent);
	else Sq_B = -pow(-B.coefficient, 1.0 / exponent);

	// controllo sulle potenze
	if (!integer(Sq_A)) return outp;
	if (!integer(Sq_B)) return outp;
	for (int i = 0; i < Variables.size(); ++i) if (A.exp[i] % exponent != 0)
		return outp;
	for (int i = 0; i < Variables.size(); ++i) if (B.exp[i] % exponent != 0)
		return outp;
	auto Aexps{ A.exp };
	auto Bexps{ B.exp };
	for (int i = 0; i < Variables.size(); ++i) {
		Aexps[i] /= exponent;
		Bexps[i] /= exponent;
	}

	for (int i = 1; i < exponent; ++i) {

		// calcolo coefficiente
		for (int j = 0; j < Variables.size(); ++j)
			if (vect[i].exp[j] != Aexps[j] * (exponent - i) + Bexps[j] * i) return outp;
		int coeff = BinomialCoeff(exponent, i);

		// caso con la sottrazione
		if (vect[i].coefficient ==
			-coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
			) {
			if (!reassigne) {
				sign = -1;
				reassigne = 1;
			}
			else if (sign == 1) return outp;
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
			else if (sign == -1) return outp;
		}

		// caso non accettato
		else return outp;
	}

	// composizione della potenza di binomio
	outp.clear();
	outp << factor<>{ {(long double)exponent, modifier} };
	outp++;
	outp[1] << monomial<>{ Sq_A, Aexps } << monomial<>{ sign * Sq_B, Bexps };

	return outp;
}

// trinomio speciale
static polynomial<> Trinomial(factor<> vect)
{

	// filtro per tensori di tre termini
	polynomial<> outp;
	outp << vect;
	if (vect != 3) return outp;
	vect.SortByDegree();

	// calcolo termini ed esponenti
	int A, B, C;
	for (int i = 0; i < Variables.size(); ++i)
		if (vect[0].exp[i] % 2 == 1 or vect[2].exp[i] % 2 == 1) return outp;

	auto Aexps{ vect[0].exp };
	auto Cexps{ vect[2].exp };
	for (int i = 0; i < Variables.size(); ++i) {
		if (2 * vect[1].exp[i] != vect[0].exp[i] + vect[2].exp[i])
			return outp;
		Aexps[i] /= 2;
		Cexps[i] /= 2;
	}
	A = vect[0].coefficient;
	B = vect[1].coefficient;
	C = vect[2].coefficient;

	// calcolo delle radici
	double firstX, secondX, delta;
	delta = B * B - 4 * A * C;
	if (delta <= 0) return outp;
	if (!integer(sqrt(delta))) return outp;
	firstX = (-B - sqrt(delta)) / (2 * A);
	secondX = (-B + sqrt(delta)) / (2 * A);
	if (!integer(A * firstX * secondX)) return outp;
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

	return outp;
}

// differenza di cubi (presto diventerà differenza di potenze)
static polynomial<> SquareDifference(factor<> vect)
{

	// filtro per tensori di due termini
	polynomial<> outp;
	outp << vect;
	if (vect != 2) return outp;

	// controllo sui quadrati perfetti
	if (!vect[0].IsSquare()) return outp;
	if (!vect[1].IsSquare()) return outp;

	// riassegnazione se i segni non vanno bene
	bool Sign_A{ vect[0].coefficient > 0 };
	bool Sign_B{ vect[1].coefficient > 0 };
	if (Sign_A == Sign_B) return outp;

	// calcolo esponenti
	auto Aexps{ vect[0].exp };
	auto Bexps{ vect[1].exp };
	for (int i = 0; i < Variables.size(); ++i) {
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

	return outp;
}

// scomposizione con ruffini
static polynomial<> Ruffini(factor<> vect)
{

	// filtro per tensori con più di un termine
	polynomial<> output;
	output << vect;
	if (vect < 2) return output;
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

	for (int i = 0; i < ListPos; ++i) {
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
		int SetRoot{};
		int Root;

		// calcolo della regola di ruffini sui coefficienti
		bool assigne{ true };
		for (int n = 1; n < CorrectSize; ++n) {

			// regola di ruffini
			tensor<long double> temp;
			for (auto root : PossibleRoots) {
				Root = root;
				do {

					// divisione polinomio per binomio
					temp = position;
					for (int i = 1; i < position; ++i)
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
					int index = Variables.size();
					if (DirectorSeq[StartIndex] == 0) swap(DirectorSeq, KnownSeq);
					for (int j = StartIndex; j < Variables.size(); ++j) {
						if (DirectorSeq[j] == 0) {
							index = j;
							break;
						}
						VariableExp[j] = i * DirectorSeq[j];
					}
					for (int j = index; j < Variables.size(); ++j)
						VariableExp[j] = (CorrectSize - 1 - i) * KnownSeq[j];
					output[1] << monomial<>{
						(long double)position[CorrectSize - i - 1], VariableExp
					};
				}
				output[1].SortByExponents();
				return output;
			}
		}
	}

	return { vect };
}

// completamento del quadrato
static polynomial<> CompleteTheSquare(factor<> vect)
{

	// filtro per tensori con tre termini
	polynomial<> output;
	output << vect;
	if (vect != 3) return output;
	vect.SortByDegree();
	auto A{ vect[0] };
	auto B{ vect[2] };

	// calcolo delle radici
	if (A.coefficient < 0 or B.coefficient < 0) return output;
	double Sq_A = sqrt(A.coefficient);
	double Sq_B = sqrt(B.coefficient);

	// controllo sui quadrati
	if (!A.IsSquare()) return output;
	if (!B.IsSquare()) return output;
	for (int i = 0; i < Variables.size(); ++i) if (A.exp[i] % 4 != 0) return output;
	
	// controllo sui gradi
	for (int i = 0; i < Variables.size(); ++i) {
		if (vect[1].exp[i] != A.exp[i] / 2 + B.exp[i] / 2) return output;
		if (!integer(A.exp[i] / 4 + B.exp[i] / 4)) return output;
	}

	// dichiarazioni
	monomial<> DiffSquare, Diffneg;
	for (int i = 0; i < Variables.size(); ++i)
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
	else return output;
	Diffneg.coefficient = -DiffSquare.coefficient;
	Diffneg.exp = DiffSquare.exp;

	// calcolo gradi finali
	for (int i = 0; i < Variables.size(); ++i) {
		A.exp[i] /= 2;
		B.exp[i] /= 2;
	}

	// composizione di somma e differenza
	output << vect;
	output[0].clear();
	output[1].clear();

	output[0] << monomial<>{ Sq_A, A.exp } << DiffSquare << monomial<>{ Sq_B, B.exp };
	output[1] << monomial<>{ Sq_A, A.exp } << Diffneg << monomial<>{ Sq_B, B.exp };

	return output;
}

// quadrato di trinomio
static polynomial<> TrinomialSquare(factor<> vect)
{

	// filtro per tensori con 5 o 6 termini
	polynomial<> output;
	output << vect;
	if (vect != 5 and vect != 6) return output;

	// push del monomio modificatore dell'esponente
	tensor<int> modifier(Variables.size(), 0);
	modifier[0] = -1;
	
	if (vect == 5) {
		vect.SortByDegree();

		// controllo coefficienti
		bool AB2, AC2, BC2;
		long double A{ sqrt(vect[0].coefficient) };
		if (!integer(A)) return output;
		long double C{ sqrt(vect[4].coefficient)};
		if (!integer(C)) return output;
		long double B{ (long double)vect[3].coefficient / (2 * C) };
		if (!integer(B)) return output;
		if (fabs(B) != fabs((double)vect[1].coefficient / (2 * A))) return output;

		// controllo esponenti
		for (int i = 0; i < Variables.size(); ++i) for (int j = 0; j < 5; ++j)
			if (vect[4 - j].exp[i] != j * vect[3].exp[i]) return output;

		// calcolo segni
		AB2 = vect[1].coefficient < 0;
		BC2 = vect[3].coefficient < 0;
		if (fabs(vect[2].coefficient) == fabs(2 * A * C + B * B))
			AC2 = vect[2].coefficient - B * B < 0;
		else if (fabs(vect[2].coefficient) == fabs(2 * A * C - B * B))
			AC2 = vect[2].coefficient + B * B < 0;
		else return output;
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
		if (squares < 3) return output;
		tensor<int> _pos{1, 2, 2};
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

			for (int i = 0; i < Variables.size(); ++i) {
				AB.exp << A.exp[i] + B.exp[i];
				AC.exp << A.exp[i] + C.exp[i];
				BC.exp << B.exp[i] + C.exp[i];
			}

			monomial<> ABterm, ACterm, BCterm;
			for (auto v : vect) {

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

	return output;
}

#pragma endregion

// funzioni utili per lavorare con le frazioni algebriche
#pragma region Algebric

// calcola il complementario di un fattore rispetto a un polinomio
static FACTOR<> Complementary(POLYNOMIAL<> Polynomial, FACTOR<> factor, int exp)
{

	// caso di eccezione
	if (Polynomial[0] == factor) --Polynomial;

	else for (int i = Polynomial.size() - 1; i > 0; --i)
		if (Polynomial[i] == factor) {

			// caso senza esponente
			if (Polynomial[i - 1][0].degree != -1) {
				Polynomial.erase(Polynomial.begin() + i);
				break;
			}

			// casi con esponente
			else if (Polynomial[i - 1][0].coefficient - exp > 1)
				Polynomial[i - 1][0].coefficient -= exp;
			else if (Polynomial[i - 1][0].coefficient - exp < 1) {
				Polynomial.erase(Polynomial.begin() + i);
				Polynomial.erase(Polynomial.begin() + i - 1);
			}
			else Polynomial.erase(Polynomial.begin() + i - 1);

		}

	return V1converter(PolynomialMultiply, Polynomial);
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
	for (int i = 0; i < num; ++i) num[i].SortByExponents();
	for (int i = 0; i < den; ++i) den[i].SortByExponents();

	// semplificazione fattori
	int sign{ 1 };
	for (int i = num.size() - 1; i >= 0; --i) {

		// caso coefficiente
		if (num[i] == 1 and num[i][0].exp == null) continue;

		for (int j = den.size() - 1; j >= 0; --j) {
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
			for (int k = 0; k < den[j]; ++k) den[j][k].coefficient *= -1;
			if (num[i] == den[j]) {
				num.erase(num.begin() + i);
				den.erase(den.begin() + j);
				sign = -1;
				continue;
			}
			else for (int k = 0; k < den[j]; ++k) den[j][k].coefficient *= -1;

			// caso di monomi
			if (num[i] == 1 and den[j] == 1)
				for (int k = 0; k < Variables.size(); ++k) {
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
	for (int i = 0; i < num; ++i) if (num[i] == 1) {
		ncoeff = num[i][0].coefficient * sign;
		if (num[i][0].exp == null and num != 1 and num[0] != 1)
			num.erase(num.begin() + i);
		else FindN = i;
		break;
	}
	for (int i = 0; i < den; ++i) if (den[i] == 1) {
		dcoeff = den[i][0].coefficient;
		if (den[i][0].exp == null and den != 1 and den[0] != 1)
			den.erase(den.begin() + i);
		else FindD = i;
		break;
	}

	// semplificazione coefficienti
	int GCD{ Gcd(abs(ncoeff), abs(dcoeff)) };
	ncoeff /= GCD;
	dcoeff /= GCD;
	if (FindN >= 0) num[FindN][0].coefficient = 1;
	if (FindD >= 0) den[FindD][0].coefficient = 1;
	ncoeff *= sign;

	// compressione polinomi
	num.close();
	den.close();

	for (int i = 0; i < num.size(); ++i) if (num[i] == factor<>({ monomial<>({1, null}) }))
		num.erase(num.begin() + i);
	for (int i = 0; i < den.size(); ++i) if (den[i] == factor<>({ monomial<>({1, null}) }))
		den.erase(den.begin() + i);
}

// calcola una soluzione di un equazione con il metodo di newton-raphson
static void Approximator(tensor<long double>& Equation, long double& root)
{

	// traduzione
	FACTOR<> equation(Equation.size());
	for (int i = Equation.size() - 1; i >= 0; --i) {
		equation[i].coefficient = Equation[i];
		equation[i].degree = Equation.size() - i - 1;
	}

	// calcolo derivata
	auto derivative{ equation };
	for (int j = 0; j < derivative; ++j) {
		derivative[j].coefficient *= derivative[j].degree;
		derivative[j].degree--;
	}
	derivative--;

	// calcolo radice
	int size = equation.size();
	const double TOL = 0.000001;
	for (int i = 0; i < 100; ++i) {
		long double fx{}, dfx{};

		// calcolo parametri
		for (int j = 0; j < equation; ++j)
			fx += equation[j].coefficient * pow(root, equation[j].degree);
		for (int j = 0; j < derivative; ++j)
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
	for (int i = 1; i < equation.size(); ++i) {
		equation[i].coefficient =
			root * equation[i - 1].coefficient + equation[i].coefficient;
		equation[i].degree--;
	}
	equation[0].degree--;
	equation--;
	
	for (int i = 0; i < equation; ++i) Equation[i] = equation[i].coefficient;
	Equation--;
}

// calcola gli zeri di un polinomio
static tensor<wstring> EquationSolver(factor<> Equation)
{
	// caso nullo
	if (Equation.empty()) return {};
	tensor<wstring> answer;

	if (Equation == 1) {

		// caso esponente
		if (Equation[0].exp[0] == -1) return {};
		
		// caso monomio
		for (int i = 0; i < Variables.size(); ++i) if (Equation[0].exp[i] != 0)
			answer << wstring(1, Variables.at(i)) + L" != 0";
	}

	// caso binomio
	if (Equation == 2) {
		int gcd{ Gcd(Equation) };
		Equation[0].coefficient /= gcd;
		Equation[1].coefficient /= gcd;

		for (int i = 0; i < Variables.size(); ++i) {
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
		answer << push;
	}
	if (Equation <= 2) return answer;

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

	if (equation.size() > 0) while (true) {

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
				_push = factor<>({ monomial<>({ 1, VDirectorSeq[0] }) }).str() + L" != "
					+ to_wstring(half_root_sum + sqrt(delta_4));
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>({ monomial<>({ 1, VKnownSeq[0] }) }).str();
				answer << _push;

				_push = factor<>({ monomial<>({ 1, VDirectorSeq[0] }) }).str() + L" != "
					+ to_wstring(half_root_sum - sqrt(delta_4));
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>({ monomial<>({ 1, VKnownSeq[0] }) }).str();
				answer << _push;
			}

			// radici complesse
			else {
				_push = factor<>({ monomial<>({ 1, VDirectorSeq[0] }) }).str() + L" != "
					+ complex(half_root_sum, sqrt(-delta_4)).c_str();
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>({ monomial<>({ 1, VKnownSeq[0] }) }).str();
				answer << _push;

				_push = factor<>({ monomial<>({ 1, VDirectorSeq[0] }) }).str() + L" != "
					+ complex(half_root_sum, -sqrt(-delta_4)).c_str();
				if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
					_push += factor<>({ monomial<>({ 1, VKnownSeq[0] }) }).str();
				answer << _push;
			}
			return answer;
		}

		// metodo di Newton-Raphson
		long double root{};
		Approximator(equation[0], root);
		auto push{
			factor<>({ monomial<>({ 1, VDirectorSeq[0] }) }).str()
			+ L" != " + to_wstring(root)
		};
		if (VKnownSeq[0] != tensor<int>(Variables.size(), 0))
			push += factor<>({ monomial<>({ 1, VKnownSeq[0] }) }).str();
		answer << push;
	}
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
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto start{ csbi.dwCursorPosition };
	wcout << wstring(10, L'\n');
	GetConsoleScreenBufferInfo(hConsole, &csbi);
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
	if (numerator.empty()) numerator = polynomial<>(
		{ factor<>({ monomial<>({1, null}) }) }
	);

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
	else denominator >> factor<>{ monomial<>{CORRECTION_RATIO, null} };

	// calcolo GCD e segni
	int gcd{ Gcd(NC, DC) };
	NC /= gcd;
	DC /= gcd;
	int Gcd{ 1 };
	if (root == 0) Gcd = ::Gcd(numerator[0][0].coefficient, denominator[0][0].coefficient);
	else Gcd = ::Gcd(Root, denominator[0][0].coefficient);
	denominator[0][0].coefficient /= Gcd;
	if (root != 0) Root /= Gcd;
	else numerator[0][0].coefficient /= Gcd;
	if (denominator[0][0] == monomial<>{1, null}) --denominator;
	else if (denominator[0][0] == monomial<>{-1, null}) {
		--denominator;
		if (root == 0) numerator[0][0].coefficient *= -1;
		else Root *= -1;
	}
	if (root == 0) if (numerator[0][0] == monomial<>{1, null}) --numerator;
	if (root != 0) num_ = to_wstring(NC * Root);

	// calcolo numeratore
	if (root == 0) {
		num_ = numerator.str();
		if (numerator == 1 and NC == 1 and num_.size() >= 2)
			if (num_.at(0) == L'(' and num_.at(num_.size() - 1) == L')')
			{
				num_.erase(num_.size() - 1);
				num_.erase(0, 1);
			}
		if (num_ == L"0") num_.clear();
		if (abs(NC) != 1) num_ = to_wstring(NC) + num_;
		if (num_.empty()) num_ = L"1";
		if (NC == -1) num_ = L'-' + num_;
	}

	// calcolo denominatore
	den_.clear();
	auto tempden{ denominator.str() };
	if (tempden != L"1") den_ = tempden;
	if (denominator == 1 and DC == 1 and den_.size() >= 2)
		if (den_.at(0) == L'(' and den_.at(den_.size() - 1) == L')')
		{
			den_.erase(den_.size() - 1);
			den_.erase(0, 1);
		}
	if (den_ == L"0") den_.clear();
	if (abs(DC) != 1) den_ = to_wstring(DC) + den_;
	if (den_.empty()) den_ = L"1";
	if (DC == -1) den_ = L'-' + den_;

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
	int size = Matrix.size();
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto begin{ csbi.dwCursorPosition };
	wcout << wstring(2 * size + 1, L'\n');
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if (csbi.dwCursorPosition.Y >= begin.Y)
		begin.Y -= 2 * size + 1 - csbi.dwCursorPosition.Y + begin.Y;
	SetConsoleCursorPosition(hConsole, begin);
	csbi.dwCursorPosition = begin;

	// calcolo stringhe e trasposizione matrice stringhe
	tensor<tensor<wstring>> StrMatrix(size), StrDenominators(size);
	for (int i = 0; i < size; ++i) for (int j = 0; j < Matrix[i]; ++j) {
		double element{ Matrix[j][i] };

		// elemento intero
		if (SelectedElement.X != -1 or integer(element)) {
			StrDenominators[i] << L"";
			StrMatrix[i] << to_wstring((int)element);
			continue;
		}

		// elemento decimale
		int I{ -1 };
		for (int i = 2; i < 1'000; ++i) {
			if (integer(i * element)) {
				I = i;
				break;
			}
			i++;
		}
		if (I == -1) {

			// elemento sottoforma di numero decimale
			StrMatrix[i] << to_wstring(element);
			StrDenominators[i] << L"";
		}
		else {

			// elemento sottoforma di frazione
			StrMatrix[i] << to_wstring((int)(element * I));
			StrDenominators[i] << to_wstring(I);
		}
	}

	// correzione lunghezza stringhe
	int sum{};
	for (int i = 0; i < size; ++i) {
		auto column{ StrMatrix[i] };
		auto denom{ StrDenominators[i] };
		int maxlenght{ 3 };

		// calcolo della lunghezza massima e correzione
		for (auto& num : column) if (num.size() > maxlenght) maxlenght = num.size();
		for (auto& den : denom) if (den.size() > maxlenght) maxlenght = den.size();
		for (auto& num : column) if (num.size() < maxlenght)
			num += wstring(maxlenght - num.size(), L' ');
		for (auto& den : denom) if (den.size() < maxlenght)
			den += wstring(maxlenght - den.size(), L' ');

		StrMatrix[i] = column;
		StrDenominators[i] = denom;
		sum += maxlenght;
	}
	sum += size * 2;

	// calcolo delle righe con e senza frazioni
	tensor<bool> HaveTheyFractions(size, false);
	for (int i = 0; i < size; ++i) for (int j = 0; j < size; ++j)
		if (StrDenominators[j][i].at(0) != L' ') {
			HaveTheyFractions[i] = true;
			break;
		}
	int index{}, row{};

	// iterazione e stampa matrice
	int line{};
	for (int i = 0; index <= 2 * size; ++i) {

		// inizio e fine matrice
		if (index == 2 * size) line = i;
		if (index == 0 or index == 2 * size) {
			wcout << L'+' << wstring(sum + 1, L'-') << L'+';
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			index++;
			continue;
		}
		wcout << L"| ";

		// calcolo linea di frazione e indice
		if (index % 2 == 0) {
			wcout << wstring(sum, L' ') << L'|';
			index++;
			csbi.dwCursorPosition.Y++;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			continue;
		}
		if (HaveTheyFractions[(index - 1) / 2]) row++;
		if (row == 4) row = 1;

		// output elemento (la matrice delle stringhe è trasposta)
		for (int j = 0; j < size; ++j) {

			// evindenziazione cursore
			if (j == SelectedElement.X and (index - 1) / 2 == SelectedElement.Y)
				SetConsoleTextAttribute(hConsole, 12);

			// caso senza frazioni
			if (
				!HaveTheyFractions[(index - 1) / 2] or
				(row == 2 and StrDenominators[j][(index - 1) / 2].at(0) == L' ')
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
				if (StrDenominators[j][(index - 1) / 2].at(0) == L' ')
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
				if (StrDenominators[j][(index - 1) / 2].at(0) == L' ')
					wcout << wstring(
						StrMatrix[j][(index - 1) / 2].size() + 1, L' '
					);
				else wcout << StrDenominators[j][(index - 1) / 2] << L' ';
				break;
			}

			SetConsoleTextAttribute(hConsole, 15);
			wcout << L' ';
		}
		if (row == 0 or row == 3) index++;

		// fine riga
		wcout << L'|';
		csbi.dwCursorPosition.Y++;
		SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
	}

	// riposizionamento cursore
	if (SelectedElement.Y == -2) {
		line = max(line, (int)SelectedElement.X);
		begin.Y += line + 1;
	}
	if (SelectedElement.X == -1) begin.X += sum + 3;
	SetConsoleCursorPosition(hConsole, begin);

	return line;
}

// inputa una matrice
static tensor<tensor<double>> InputMatrix()
{

	// calcolo posizione cursore
#ifndef DEBUG
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif

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
	while (true) if (_kbhit()) {
		char c = tolower(_getch());

		// casi speciali
		if (c == -32) {
			arrow = true;
			continue;
		}
		if (c <= 0) continue;
		if (arrow) {
			switch (c) {
			case 'h': c = 'w';
				break;
			case 'p': c = 's';
				break;
			case 'm': c = 'd';
				break;
			case 'k': c = 'a';
				break;
			}
			arrow = false;
		}

		// // scelta carattere
		int size;

		// casi che non modificano la matrice
		switch (c) {

			// wasd per cambiare l'elemento da modificare
		case 'w': IndexAccesser.Y = (IndexAccesser.Y - 1) % TheMatrix.size();
			break;
		case 's': IndexAccesser.Y = (IndexAccesser.Y + 1) % TheMatrix.size();
			break;
		case 'a': IndexAccesser.X = (IndexAccesser.X - 1) % TheMatrix.size();
			break;
		case 'd': IndexAccesser.X = (IndexAccesser.X + 1) % TheMatrix.size();
			break;
		}

		MatrixAtIndex = to_wstring(
			(int)TheMatrix[IndexAccesser.Y][IndexAccesser.X]
		);

		// casi che modificano la matrice
		switch (c) {

			// '\b' cancella un carattere
		case '\b':
			if (MatrixAtIndex == L"0" and Signs[IndexAccesser.Y][IndexAccesser.X]) {
				Signs[IndexAccesser.Y][IndexAccesser.X] = POS;
				break;
			}
			if (MatrixAtIndex.size() == 1) {
				MatrixAtIndex = L"0";
				break;
			}
			MatrixAtIndex.erase(MatrixAtIndex.size() - 1);
			break;

			// ctrl + '\b' cancella tutto
		case 127:
			MatrixAtIndex = L"0";
			Signs[IndexAccesser.Y][IndexAccesser.X] = POS;
			break;

			// '+' aumenta la dimensione
		case '>': if (TheMatrix.size() > 6) break;
			size = TheMatrix.size() + 1;
			TheMatrix(size);
			Signs(size);
			for (int i = 0; i < size; ++i) {
				TheMatrix[i](size, 0);
				Signs[i](size, POS);
			}
			break;

			// '-' riduce la dimensione
		case '<': if (TheMatrix.size() <= 2) break;
			TheMatrix--;
			for (auto& row : TheMatrix) row--;
			IndexAccesser.X %= TheMatrix.size();
			IndexAccesser.Y %= TheMatrix.size();
			break;

			// '\r' invia la matrice
		case '\r':
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			csbi.dwCursorPosition.Y += 2 * TheMatrix.size() + 1;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			SetConsoleCursorInfo(hConsole, &cursor);
			return TheMatrix;

			// '.' termina il programma
		case '.':
			SetConsoleCursorInfo(hConsole, &cursor);
			return {};

		default:

			// aggiunta di carattere numerico o segno
			if (isdigit(c) or (c == L'-' and MatrixAtIndex == L"0")
				and !Signs[IndexAccesser.Y][IndexAccesser.X])
			{
				if (Signs[IndexAccesser.Y][IndexAccesser.X]
					and MatrixAtIndex.at(0) != L'-')
					MatrixAtIndex = L'-' + MatrixAtIndex;
				if (c == L'-') Signs[IndexAccesser.Y][IndexAccesser.X] = NEG;
				if (MatrixAtIndex.size() > 4 + (MatrixAtIndex.at(0) == L'-')) break;
				if (MatrixAtIndex == L"0") MatrixAtIndex = L"";
				MatrixAtIndex += c;
			}
		}
		// //

		// stampa
		TheMatrix[IndexAccesser.Y][IndexAccesser.X] =
			MatrixAtIndex == L"-" ? 0 : stoi(MatrixAtIndex);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		auto CursorPos{ csbi.dwCursorPosition };
		ClearArea(
			{ (short)(CursorPos.X + 30), (short)(CursorPos.Y + 8) }, { 30, 8 }
		);
		OutputMatrix(TheMatrix, IndexAccesser);
	}
	SetConsoleCursorInfo(hConsole, &cursor);
}

// moltiplica due matrici
static tensor<tensor<double>> MatrixMultiply(
	tensor<tensor<double>> A,
	tensor<tensor<double>> B
)
{
	if (A % B) return {};
	int size = A.size();
	tensor<tensor<double>> C(size);

	for (int i = 0; i < size; ++i) for (int j = 0; j < size; ++j) {
		double scalar_prod{};
		for (int k = 0; k < size; ++k) scalar_prod += A[i][k] * B[k][j];
		C[i] << scalar_prod;
	}
	
	return C;
}

// calcola il determinante di una matrice con il teorema di laplace
template<typename T> static T Determinant(tensor<tensor<T>> mx)
{
	T det{};
	int s = mx.size();

	// casi speciali
	if (s == 1) return mx[0][0];
	if (s == 2) return mx[0][0] * mx[1][1] - mx[0][1] * mx[1][0];

	// caso generale
	for (int i = 0; i < s; ++i) {

		tensor<tensor<T>> MX(s - 1);
		for (int I = 0; I < s - 1; ++I) for (int J = 0; J < s; ++J)
		{
			if (i == J) continue;
			MX[I] << mx[I + 1][J];
		}
		
		det += intpow(-1, i) * mx[0][i] * Determinant(MX);
	}
	return det;
}

// calcola il determinante di una matrice di polinomi
FACTOR<> PolynomialMatrixDeterminant(tensor<tensor<FACTOR<>>> PolynomialMatrix)
{

	FACTOR<> det;
	int s = PolynomialMatrix.size();

	// casi speciali del calcolo del determinante
	if (s == 1) return PolynomialMatrix[0][0];
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
		return To1V(PolynomialSum<long double>(addend1 + addend2));
	}

	// caso generale del calcolo del determinante
	for (int i = 0; i < s; ++i) {

		tensor<tensor<FACTOR<>>> MX(s - 1);
		for (int I = 0; I < s - 1; ++I) for (int J = 0; J < s; ++J)
		{
			if (i == J) continue;
			MX[I] << PolynomialMatrix[I + 1][J];
		}

		auto adder{
			PolynomialMultiply<long double>({
				ToXV(PolynomialMatrix[0][i]),
				ToXV(PolynomialMatrixDeterminant(MX))
				})
		};
		for (auto& mon : adder) mon.coefficient *= -1;
		det = To1V(PolynomialSum<long double>(ToXV(det) + adder));
	}

	return det;
};

// calcola gli autovalori di una matrice
static tensor<double> EigenValues(tensor<tensor<double>> mx, bool determinant)
{

	// inizializzazione
	int s = mx.size();
	auto PolynomialMatrix{ tensor<tensor<FACTOR<>>>(s, tensor<FACTOR<>>(s)) };
	for (int i = 0; i < s; ++i) for (int j = 0; j < s; ++j)
		PolynomialMatrix[i][j] << MONOMIAL<>{ 0, (long double)mx[i][j] };
	for (int i = 0; i < s; ++i) PolynomialMatrix[i][i] >> MONOMIAL<>{ 1, -1 };
	
	// calcolo autovalori
	tensor<double> eigenvalues;
	auto EigenStrings{
		EquationSolver(
			ToXV(PolynomialMatrixDeterminant(PolynomialMatrix))
		)
	};
	for (auto str : EigenStrings) {
		str.erase(0, str.find(L'=') + 1);
		if (str.find(L'i') == wstring::npos) eigenvalues << stod(str);
	}
	return eigenvalues;
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

	// scelta
	wstring to_evaluate, ToEvaluate, message;
	bool ShowErrors{ true }, NecessaryBoundary{ true };
	SetConsoleTextAttribute(hConsole, 14);
	wcout << L"il PROGRAMMA traduce una stringa di codice\n\n";
	SetConsoleTextAttribute(hConsole, 12);

	wcout << L"il codice non deve avere errori o saranno segnalati\n";
	wcout << L"il codice deve essere compreso tra <>\n";
	wcout << L"se sono presenti piu' caratteri '<', '>',\n";
	wcout << L"verranno considerati solo quelli che compaiono prima\n";
	wcout << L"unici caratteri non numerici ammessi: '(', ')', '+', '.' \n\n";

	SetConsoleTextAttribute(hConsole, 9);
	wcout << L"si indichino le cifre incognite con caratteri '_'\n";
	wcout << L"aggiungendo '$' come primo carattere\n";
	wcout << L"oppure '\\' o '/' senza <> non vengono mostrati gli errori\n\n";
	SetConsoleTextAttribute(hConsole, 15);

	while (true)
	{
		do {
			message.clear();

			// input e controllo
			wcout << L"inserire una stringa (f = fine input)\n";
			wcout << L"per fermare il calcolo premere s\\S\n";
			getline(wcin, ToEvaluate);
			argc = ConvertWStringToEnum(ToEvaluate);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(ToEvaluate.c_str());
				return;
			}
			if (ToEvaluate == L".") {
				argc = Random;
				return;
			}

			// ammissione errori
			if (!ToEvaluate.empty()) {
				NecessaryBoundary = ToEvaluate.at(0) != L'\\' and ToEvaluate.at(0) != L'/';
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
				SetConsoleTextAttribute(hConsole, 15);
			}

		} while (message.size() > 1);

		// caso di fine input
		if (ToEvaluate == L"f") {
			argc = NotAssigned;
			return;
		}

		// eliminazione spazi
		for (int space = ToEvaluate.size() - 1; space >= 0; --space)
			if (ToEvaluate.at(space) == L' ' or ToEvaluate.at(space) == L'\t')
				ToEvaluate.erase(space, 1);

		GlobalInterr = false;
		computing = true;
		interrupted = false;

		ObjectGetCh.enqueue(L' ');
#ifndef DEBUG
		SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif

		// dichiarazione dei thread
		thread ComputationThread([=]() {
			LongComputation(to_evaluate, message, ShowErrors, NecessaryBoundary);
			}
		);
		thread InputThread(UserInputThread);

		unique_lock<mutex> lock(CoutMutex);
		Cv.wait(lock, [] { return !computing; });

		if (ComputationThread.joinable()) ComputationThread.join();
		interrupted = true;
		if (InputThread.joinable()) InputThread.join();

		// se il calcolo viene interrotto
		if (GlobalInterr) {
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"CALCOLO INTERROTTO!!!";
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"\n\n";
		}
		SetConsoleCursorInfo(hConsole, &cursor);
	}
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
	SetConsoleTextAttribute(hConsole, 15);

	while (true)
	{
		// input e controllo
		SetConsoleTextAttribute(hConsole, 14);
		wstring txt{
			L"inserire un numero tra 2 e " + n_ + L" (1 = fine input)\n"
		};
		SetConsoleTextAttribute(hConsole, 15);
		Input = GetUserNum(txt, 1, GlobalMax, true);
		if (!Input.empty()) {
			if (Input == L".") {
				argc = Random;
				return;
			}
			argc = ConvertWStringToEnum(Input);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(Input.c_str());
				return;
			}
			input = stoull(Input);
		}

		// generatore casuale in caso di input vuoto
		else {
			random_device rng;
			mt19937 gen(rng());
			uniform_int_distribution<> dis(2, GlobalMax);
			input = dis(gen);
		}

		// calcolo e stampa dei risultati
		if (input == 1) break;
		result = CPU(input);
		result.printf();
	}

	argc = NotAssigned;
	return;
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
	ptrdiff_t input, LowerBound, UpperBound, datalenght;
	bool Return;

	// input estremi
	wcout << L"debug::\n\n";
	SetConsoleTextAttribute(hConsole, 14);
	wcout << message << '\n';
	SetDebug(message, argc, Return, LowerBound, UpperBound, datalenght);
	if (Return) return;

	// input instruzioni
	wstring instr;
	if (select) {
		PRINTN = false;
		items = { 0, 0, 0, 0 };
		SetConsoleTextAttribute(hConsole, 9);
		wcout << L"inserisci la stringa di istruzioni, il tipo è $_/_ #_/_\n";
		wcout << L"per indicare i rapporti somma cifre con numero";
		wcout << L" e prodotto cifre con numero\n";
		SetConsoleTextAttribute(hConsole, 15);

		bool exit{ false };
		do {
			wcout << L"\ninserire la stringa\n";
			instr = GetLine(true, 20);
			if (instr == L".") {
				argc = Random;
				return;
			}

			// rimozione spazi
			for (int i = instr.size() - 1; i >= 0; --i)
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
				for (auto c : np) if (!isdigit(c)) Continue = true;
				for (auto c : dp) if (!isdigit(c)) Continue = true;
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
				for (auto c : ns) if (!isdigit(c)) Continue = true;
				for (auto c : ds) if (!isdigit(c)) Continue = true;
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
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const int Barwidth{ csbi.dwSize.X - 11 };
#ifndef DEBUG
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#endif
	if (datalenght >= 1000) {
		int iter{};
		atomic<long double> Progress{};
		auto begin{ steady_clock::now() };
		parallel_for(ptrdiff_t(LowerBound), UpperBound, 
			[&](ptrdiff_t set) {

				auto data_element{ CPU(set) };
				mtx.lock();
				data << data_element;
				if (iter % 200 == 0) {

					// stampa della barra di avanzamento
					auto stop{ steady_clock::now() };
					SetConsoleTextAttribute(hConsole, 112);
					Progress = (long double)data.size() / datalenght;
					ProgressBar(Progress, Barwidth);

					// calcolo del tempo rimanente
					int time = duration_cast <milliseconds> (stop - begin).count();
					SetConsoleTextAttribute(hConsole, 15);
					long double time_rem{ (time / Progress) * (1 - Progress) };
					long double time_seconds{ (long double)time_rem / 1000 };

					// calcolo cifre decimali
					wstringstream stream;
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
		t2.join();
		t1.join();
		system("cls");

		// stampa risultati
		SetConsoleCursorInfo(hConsole, &cursor);
		data.printf();
		auto end{ steady_clock::now() };
		wcout << L"\ntempo di calcolo = ";
		wcout << duration_cast<milliseconds> (end - begin).count();
		wcout << L"[ms]\n\n";
	}

	// caso con intervallo di dimensioni minori
	else {
		SetConsoleCursorInfo(hConsole, &cursor);
		auto begin{ steady_clock::now() };
		for (ptrdiff_t set = LowerBound; set < UpperBound; ++set)
			data << NumberData{ CPU(set) };
		data.printf();
		wcout << L"\ntempo di calcolo = ";
		auto end{ steady_clock::now() };
		wcout << duration_cast<milliseconds> (end - begin).count();
		wcout << L"[ms]\n\n\n";
	}

	// termine
	wchar_t null;
	PRINTN = true;
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	wcout << L"premi un tasto per continuare\t\t";
	do null = _getwch();
	while ((null > 64 and null < 91) or null < 32);
	argc = null == L'.' ? Random : NotAssigned;
	return;
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
		wcout << L"il PROGRAMMA scompone i polinomi\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		wcout << L"per attivare gli esponenti in forma di apice ";
		wcout << L"scrivere noboolalpha\n";
		wcout << L"per disattivare gli esponenti sottoforma di apice ";
		wcout << L"scrivere boolalpha\n\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	do {
		if (input)
		{
			empty = true;
			Xout = false;
			wstring Message;
			do {
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				bool wrong{ true };

				// input
				SetConsoleTextAttribute(hConsole, 15);
				wcout << L"inserisci un polinomio in una o più variabili";
				wcout << L" (0 = fine input)\n";
				do {
					Polynomial = GetLine(true, csbi.dwSize.X);
					wcout << L'\n';
				} while (Polynomial.empty());
				if (Polynomial == L".") {
					argc = Random;
					return {};
				}
				argc = ConvertWStringToEnum(Polynomial);
				ReassigneEnum(argc);
				if (argc != NotAssigned) {
					system("cls");
					SetConsoleTitle(Polynomial.c_str());
					return {};
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
				for (int i = Polynomial.size() - 1; i >= 0; --i)
					if (Polynomial.at(i) == L' ' or Polynomial.at(i) == L'\t')
						Polynomial.erase(i, 1);

				// controllo
				Message = PolynomialSyntaxDirector(Polynomial);
				if (!Message.empty() and wrong) {
					SetConsoleTextAttribute(hConsole, 12);
					wcout << Message << L"!!\n\a";
					SetConsoleTextAttribute(hConsole, 15);
				}

			} while (!Message.empty());
			if (Polynomial == L"0") break;
		}

		// somma
		polynomial<> BackT, Back_T{ HT };
		tensor<int> null;
		int size;
		auto bigHT{ GetMonomialsAssister(Polynomial) };
		if (input) charVariable = Variables.at(0);
		HT = FromBigToDefault(bigHT);
		if (HT >= 1) if (HT[0] >= 1) if (HT[0][0].exp[0] == -2) {
			if (input) {
				SetConsoleTextAttribute(hConsole, 2);
				wcout << L"questo è il polinomio: " << bigHT.str() << L'\n';
				SetConsoleTextAttribute(hConsole, 64);
				wcout << L"il polinomio è troppo grande.";
				SetConsoleTextAttribute(hConsole, 15);
				wcout << L'\n';
				goto EndOfDecomposition;
			}
			else return {};
		}

		null(Variables.size());
		null[0] = -1;
		if (HT == polynomial<>{ factor<>{} }) Polynomial = L"0";
		else if (HT == 1) Polynomial = HT[0].str();
		else Polynomial = HT.str();
		if (BOOLALPHA) ElabExponents(Polynomial);

		// risultato della somma
		if (input) {
			SetConsoleTextAttribute(hConsole, 2);
			if (Polynomial.empty()) Polynomial = L"0";
			wcout << L"questo è il polinomio: " << Polynomial << L'\n';
		}

		// caso nullo
		size = HT.size();
		if (Polynomial == L"0") {
			SetConsoleTextAttribute(hConsole, 15);
			wcout << "il polinomio non è scomponibile\n";
			goto EndOfDecomposition;
		}

		// raccoglimento totale
		Back_T = HT;
		HT.clear();
		for (auto polydata : Back_T) HT += Total(polydata);
		Polynomial = HT.str();
		if (HT != size and input) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"raccoglimento totale: " << Polynomial << L'\n';
			empty = false;
		}
		do {

			// raccoglimento parziale
			pol = Polynomial;
			auto polydata{ HT.last() };
			HT--;
			HT += Partial(polydata);
			HT.close();
			Polynomial = HT.str();
			if (Back_T % HT and Polynomial != pol and input) {
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"raccoglimento parziale: " << Polynomial << L'\n';
				empty = false;
			}

			// potenza di binomio
			HT.close();
			Back_T = HT;
			HT.clear();
			for (auto a : Back_T) HT += Binomial(a);
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
			for (auto a : Back_T) HT += Trinomial(a);
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
			for (auto a : Back_T) {
				if (a[0].exp[0] < 0) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = SquareDifference(a);
				for (auto b : BackT) {
					if (extend > 1) HT << factor<>{ {(long double)extend, null} };
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
			for (auto a : Back_T) {
				if (a[0].exp[0] < 0) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = Ruffini(a);
				if (!a.empty() and BackT.empty()) {
					Xout = true;
					break;
				}
				for (auto b : BackT) {
					if (extend > 1) HT << factor<>{ {(long double)extend, null} };
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
		for (auto a : Back_T) HT += CompleteTheSquare(a);
		HT.close();
		Polynomial = HT.str();
		if (Back_T % HT and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"completamento del quadrato: " << Polynomial;
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L'\n';
			empty = false;
		}

		// quadrato del trinomio
		Back_T = HT;
		HT.clear();
		for (auto a : Back_T) HT += TrinomialSquare(a);
		
		HT.close();
		Polynomial = HT.str();
		if (Back_T % HT and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 79);
			wcout << L"quadrato di trinomio scomposto: " << Polynomial;
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L'\n';
			empty = false;
		}

		// caso vuoto
		if (empty and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"il polinomio non è scomponibile";
			wcout << L" con i metodi standard\n";
		}

		// caso impossibile
		if (Xout and input) {
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"X_OUT_OF_RANGE";
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L'\n';
		}

		if (input) {

			// controllo dimensione console
			if (Variables.size() != 1) continue;
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			if (csbi.dwSize.X <= 94 or csbi.dwSize.Y <= 26) continue;

			// aggiunta di spazio
			wcout << wstring(csbi.dwSize.Y - 1, L'\n');
			SetConsoleCursorPosition(hConsole, { 0, 0 });
			PrintGraph(To1V(PolynomialMultiply(HT)), { 0, 0 });
		}

	EndOfDecomposition: if (!input) break;

	} while (input);

	argc = NotAssigned;
	return HT;
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
	wcout << L"il PROGRAMMA scompone le frazioni algebriche\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"per attivare gli esponenti in forma di apice ";
	wcout << L"scrivere noboolalpha\n";
	wcout << L"per disattivare gli esponenti sottoforma di apice ";
	wcout << L"scrivere boolalpha\n";
	SetConsoleTextAttribute(hConsole, 15);

	while (true)
	{
		// input della frazione algebrica
		wstring numerator, denominator;
		bool No1{ false }, No2{ false }, skip{ false };
	insert:
		do {

			// input
			SetConsoleTextAttribute(hConsole, 15);
			bool wrong{ true };
			wcout << L"\ninserisci una frazione algebrica (0 = fine input)\n\n";
			GetFraction(numerator, denominator);
			if (numerator.empty()) numerator = L"0";
			if (denominator.empty()) denominator = L"1";

			if (numerator == L".") {
				argc = Random;
				return;
			}
			argc = ConvertWStringToEnum(numerator);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				SetConsoleTitle(numerator.c_str());
				return;
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
				SetConsoleTextAttribute(hConsole, 15);
			}

			// denominatore nullo
			if (!No1 and !No2) if (GetMonomialsAssister(denominator)
				== polynomial<big>{ factor<big>{} })
			{
				No2 = true;
				SetConsoleTextAttribute(hConsole, 4);
				wcout << L"il denominatore non può essere nullo\n\a";
				SetConsoleTextAttribute(hConsole, 15);
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
		auto savx{ Variables };
		auto D_{ DecompPolynomial(use, denominator) };
		
		if (!(N_ and D_)) {
			wcout << L'\n';
			SetConsoleTextAttribute(hConsole, 64);
			wcout << L"input overflow: prova a inserire valori più piccoli";
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L'\n';
			goto insert;
		}

		// aggiunta di spazio nella memoria
		auto oldV{ Variables };
		for (auto ch : Variables) if (savx.find(ch) == wstring::npos) savx += ch;
		Variables = savx;
		for (auto& fac : N_) for (auto& mon : fac) mon.exp(Variables.size(), 0);
		for (auto& fac : D_) for (auto& mon : fac) mon.exp(Variables.size(), 0);
		auto temp(D_);
		for (int i = 0; i < D_; ++i) for (int j = 0; j < temp[i]; ++j)
			for (int k = 0; k < Variables.size(); ++k)
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

		// aggiornamento dati globali
		auto test{ N_ };
		if (N_.empty() and D_.empty()) charVariable = L'x';
		else if (N_.empty()) test = D_;
		if (!(N_.empty() and D_.empty())) for (int i = 0; i < Variables.size(); ++i)
			if (test[0][0].exp[i] != 0) charVariable = Variables.at(i);

		// correzione fattori
		auto NScomp{ To1V(N_) };
		auto DScomp{ To1V(D_) };
		NScomp.close();
		DScomp.close();
		for (int i = 0; i < NScomp; ++i) NScomp[i].sort();
		for (int i = 0; i < DScomp; ++i) DScomp[i].sort();
		if (DScomp <= 1) skip = true;
		if (!skip) for (auto a : DScomp) for (auto b : a)
			if (a != 1 and b.degree > 1) skip = true;

		// caso con più variabili
		bool IsAModifier{ false }, HasMoreVariables{ false };
		tensor<POLYNOMIAL<>> denominators;
		POLYNOMIAL<> complementaries;
		int index{}, size{}, Det;
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
		if (!skip) for (int i = 0; i < DScomp; ++i) {
			if (DScomp[i][0].degree == -1) {
				IsAModifier = true;
				continue;
			}

			// caso con le potenze
			if (IsAModifier) for (int j = DScomp[i - 1][0].coefficient; j > 0; --j)
			{
				denominators++;
				if (j > 1) denominators[index] << FACTOR<>{ {-1, (long double)j} };
				denominators[index] << DScomp[i];
				index++;
				complementaries << Complementary(DScomp, DScomp[i], j);
			}
			
			// caso con le potenze della variabile
			else if (DScomp[i] == 1) for (int j = DScomp[i][0].degree; j > 0; --j)
			{
				denominators++;
				denominators[index] << FACTOR<>{ {j, 1} };
				index++;
				auto NewScomp{ DScomp };
				NewScomp.erase(NewScomp.begin() + i);
				NewScomp.insert(NewScomp.begin() + i, { {1, 1} });
				NewScomp.insert(NewScomp.begin() + i, {
					{-1, (long double)DScomp[i][0].degree}
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
		if (!skip) for (int i = 0; i < complementaries; ++i)
			complementaries[i].complete(complementaries.size());

		// inizializzazione matrice
		if (!skip) {
			size = complementaries.size();
			Matrix(size);
			for (int i = 0; i < complementaries; ++i)
				for (int j = 0; j < complementaries; ++j)
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

			for (auto R : Rest) results << R.coefficient;
			while (results.size() < complementaries.size()) results >> 0;
			Det = Determinant(Matrix);
		}
		if (!skip) for (int i = 0; i < results; ++i) {
			tensor<tensor<int>> MX{ Matrix };
			MX[i] = results;
			roots << (double)Determinant(MX) / Det;
		}

		// eliminazione degli zeri
		for (int i = denominators.size() - 1; i >= 0; --i) 
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
		for (auto d : DenBackup) {
			auto Ctemp_{ EquationSolver(d) };
			for (auto i : Ctemp_) C_E_ << i;
		}

		// output condizioni di esistenza
		for (auto I : C_E_) {
			
			// eliminazione cifre decimali nulle
			if (I.find(L'.') != wstring::npos or I.find(L',') != wstring::npos)
			while (I.at(I.size() - 1) == L'0') I.erase(I.size() - 1);
			if (I.at(I.size() - 1) == L',' or I.at(I.size() - 1) == L'.')
				I.erase(I.size() - 1);

			// stampa
			if (BOOLALPHA) ElabExponents(I);
			wcout << I << L"; ";
			HasBeenPrinted = true;

		}
		if (!HasBeenPrinted) wcout << L"\r      \r";
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		cursorPos = csbi.dwCursorPosition;
		if (!HasBeenPrinted) {
			cursorPos.X = 0;
			cursorPos.Y--;
			SetConsoleCursorPosition(hConsole, cursorPos);
		}
		else wcout << L'\n';

		// output frazioni
		SetConsoleTextAttribute(hConsole, 10);
		wcout << L"\nla scomposizione è: ";
		SetConsoleTextAttribute(hConsole, 12);
		bool ShowPlus{ false };
		int lines{};

		// caso generale, frazione scomposta
		if (!skip) {
			wcout << L"\n\n";
			for (int i = 0; i < denominators; ++i) {
				PrintFraction(
					NCOEFF,
					DCOEFF,
					lines,
					ShowPlus,
					{ { { roots[i], tensor<int>(Variables.size(), 0) }}},
					ToXV(denominators[i])
				);
				ShowPlus = true;
			}
			wcout << L"\n\n";
		}

		else {

			// caso di frazione semplificata ma non scomposta
			bool NewPrint{ false };
			polynomial<> TopPart = HasMoreVariables ? N_ : ToXV(NScomp);
			polynomial<> BottomPart = HasMoreVariables ? D_ : ToXV(DScomp);
			if (!BottomPart.empty()) {
				if (BottomPart > 1 or BottomPart[0] > 1 or
					BottomPart[0][0].exp != tensor<int>(Variables.size(), 0))
				{
					GetConsoleScreenBufferInfo(hConsole, &csbi);
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
				GetConsoleScreenBufferInfo(hConsole, &csbi);
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
				GetConsoleScreenBufferInfo(hConsole, &csbi);
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
				
		}

		// reset cursore
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		auto cursorP{ csbi.dwCursorPosition };
		cursorP.X = lines;
		cursorP.Y--;
		SetConsoleCursorPosition(hConsole, cursorP);

		// output polinomio di resto
		if (!skip) for (auto a : Quotient) {
			auto rest{ POLYNOMIAL<>({ FACTOR<>({a}) }) };
			if (a.coefficient == 0) continue;

			// output normale
			if (integer(a.coefficient / CORRECTION_RATIO)) {
				rest[0][0].coefficient /= CORRECTION_RATIO;
				auto pol{ rest.str() };
				bool IsMinus{ false };

				// correzione segno
				if (pol.at(0) == L'-') {
					pol.erase(0, 1);
					IsMinus = true;
				}
				if (pol.size() >= 2)
					if (pol.at(0) == '(' and pol.at(pol.size() - 1) == ')')
					{
						pol.erase(pol.size() - 1);
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
				GetConsoleScreenBufferInfo(hConsole, &csbi);
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
				GetConsoleScreenBufferInfo(hConsole, &csbi);
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
	}

	argc = NotAssigned;
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
	wcout << L"il PROGRAMMA scompone le matrici\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	wcout << L"sono ammesse solo matrici quadrate da 2x2 a 7x7\n\n";
	SetConsoleTextAttribute(hConsole, 15);
	tensor<tensor<double>> matrix, Mx;

	while (true)
	{
		// input
		SetConsoleTextAttribute(hConsole, 15);
		wcout << L"inserisci una matrice, usa wasd per cambiare elemento\n";
		matrix = InputMatrix();
		if (matrix.empty()) {
			argc = Random;
			return;
		}
		if (matrix == tensor<tensor<double>>(Mx.size(), tensor<double>(Mx.size(), 0)))
			break;
		wcout << L'\n';
		Mx = matrix;

		// calcolo matrice di permutazione
		auto Id{ tensor<tensor<double>>(Mx.size(), tensor<double>(Mx.size(), 0)) };
		for (int i = 0; i < Mx; ++i) Id[i][i] = 1;
		auto permutator{ Id };
		for (int i = 0; i + 1 < Mx; ++i) {

			int max = Mx[Mx.size() - 1][i], IndexofMax = Mx.size() - 1;
			for (int j = Mx.size() - 2; j >= i; --j) if (Mx[j][i] > max) {
				max = Mx[j][i];
				IndexofMax = j;
			}

			if (IndexofMax != i) {
				swap(Mx[IndexofMax], Mx[i]);
				swap(permutator[IndexofMax], permutator[i]);
			}

		}

		// trasposizione della matrice di permutazione
		auto NewPermutator{ tensor<tensor<double>>(permutator.size(), 0) };
		for (int i = 0; i < Mx; ++i) for (int j = 0; j < Mx; ++j)
			NewPermutator[i] << permutator[j][i];
		permutator = NewPermutator;

		// calcolo elementi
		auto lower{ Id };
		auto upper{ Mx };
		bool Break{ false };
		for (int i = 0; i + 1 < Mx; ++i) {
			
			for (int j = i + 1; j < Mx; ++j) {
				
				if (upper[i][i] == 0) {
					Break = true;
					break;
				}
				lower[j][i] = upper[j][i] / upper[i][i];

				for (int k = 0; k < Mx; ++k)
					upper[j][k] -= lower[j][i] * upper[i][k];
			}
			if (Break) break;
		}

		// decomposizione PLU
		if (!Break) {
			wcout << L"decomposizione PLU:\n";
			int line{ OutputMatrix(permutator) };
			line = max(line, OutputMatrix(lower));
			OutputMatrix(upper, { (short)line, -2 });
			wcout << L'\n';
		}

		// algoritmo di givens
		Mx = matrix;
		auto ortogonal{ Id };
		Break = false;
		for (int i = 0; i < Mx; ++i) {
			for (int j = i + 1; j < Mx; ++j) if (Mx[j][i] != 0) {

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
			OutputMatrix(Mx, { (short)OutputMatrix(ortogonal), -2 });
			wcout << L'\n';
		}

		// decomposizione di cholesky
		Mx = matrix;
		lower = Id;
		Break = false;
		for (int i = 0; i < Mx; ++i) {
			for (int j = 0; j <= i; ++j) {
				double sum{};

				// elementi sulla diagonale
				if (i == j) {
					for (int k = 0; k < i; ++k) sum += lower[i][k] * lower[i][k];
					lower[i][i] = sqrt(Mx[i][i] - sum);
				}

				// controllo risultati corretti
				if (lower[i][i] == 0 or isnan(lower[i][i])) {
					Break = true;
					break;
				}

				// elementi sotto alla diagonale
				if (i != j) {
					for (int k = 0; k < i; ++k) sum += lower[i][k] * lower[j][k];
					lower[i][j] = (Mx[i][j] - sum) / lower[j][j];
				}

			}
			if (Break) break;
		}
		auto lowerT{ tensor<tensor<double>>(Mx.size()) };
		if (!Break) for (int i = 0; i < Mx; ++i)
			for (int j = 0; j < Mx; ++j) lowerT[i] << lower[j][i];

		// output decomposizione
		if (!Break) {
			wcout << L"decomposizione di cholesky:\n";
			OutputMatrix(lowerT, { (short)OutputMatrix(lower), -2 });
			wcout << L'\n';
		}

		// decomposizione a valori singolari


	}

	argc = NotAssigned;
}

#pragma endregion

#pragma endregion

// file natvis 56 righe
// fine del codice

/*

impegni programma:
	
	aggiungere i tipi rimanenti di decomposizione matrici (22-23/08)

	aggiungere dei thread per il controllo della dimensione della console (24-25/08)
	
	refactor foreach loop e for auto& loop (26/08)

	fare un grande debug (26/08)

*/