// inizio del codice
#pragma region Files

// pragma
#pragma once
#pragma optimize("", on)

// pragma warning
#pragma warning(disable : 4101)
#pragma warning(disable : 4244)
#pragma warning(disable : 4247)
#pragma warning(disable : 4267)
#pragma warning(disable : 4551)
#pragma warning(disable : 4715)
#pragma warning(disable : 6001)
#pragma warning(disable : 6385)
#pragma warning(disable : 6386)
#pragma warning(disable : 28182)
#pragma warning(disable : 28193)

// messaggi
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")
#pragma message("COMPILAZIONE IN CORSO")

// Descrizione programma ::
	/*                                                          |
	*  Strings ZP[5.9].cpp: il programma calcola singola e\o    |
	*  doppia scomposizione di alcuni interi in una stringa o   |
	*  il contrario, i numeri primi, cifre e divisori, scompone |
	*  anche i polinomi e le frazioni algebriche                |
	*///                                                        |

	// macro
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
#define NO_DISCARD_CONST_EXPR _NODISCARD _CONSTEXPR20
#define integer(x) (floor(x) == ceil(x))
#define issign(x) (x == '+' or x == '-')

// inclusioni
#include <algorithm>
#include <atomic>
#include <chrono> // per le misurazioni di tempo
#include <cmath> // per i calcoli
#include <condition_variable> // per il multithreading
#include <conio.h> // per l'input avanzato
#include <deque>
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
#include <unordered_map> // per la conversione degli enum
#include <utility>
#include <Windows.h> // per hConsole e la posizione del cursore

// namespace globali
using namespace std;
using namespace chrono;
using Concurrency::parallel_for, this_thread::sleep_for;

#pragma endregion
#pragma region Globals

// oggetti windows
auto hConsole{
	GetStdHandle(STD_OUTPUT_HANDLE)
};
CONSOLE_CURSOR_INFO cursorInfo{ 10, FALSE };
CONSOLE_CURSOR_INFO cursor{ 10, TRUE };
CONSOLE_SCREEN_BUFFER_INFO csbi;

// funzioni e variabili globali
static char charVariable('x');
long long GlobalMax(pow(10, 10));
const long long GLOBAL_CAP(pow(10, 10));
bool BOOLALPHA(true);
bool PRINTN(true);

// monomi
struct MONOMIAL {
	int degree;
	int coefficient;
	bool operator == (const MONOMIAL& other) const
	{
		return coefficient == other.coefficient and
			degree == other.degree;
	}
};
struct REAL_MONOMIAL {
	long double degree;
	long double coefficient;
	bool operator == (const REAL_MONOMIAL& other) const
	{
		return coefficient == other.coefficient and
			degree == other.degree;
	}
};

// variabili globali e atomiche
atomic<bool> GlobalInterr(false);
atomic<bool> interrupted(false);
atomic<bool> computing(false);
atomic<bool> is_done(false);
condition_variable cv, Cv;
mutex CoutMutex, mtx;
COORD Min{ 25, 15 };

// strutture locali
struct compost {
	int factors;
	int exp;
};
struct divisor {
	long long DivNumber{ 1 };
	long long DivSum{ 1 };
	long long DivProduct{ 1 };
	string Div_pr{};
};
struct digitRatio {
	int digitSumRatioNum{};
	int digitSumRatioDen{};
	int digitProductRatioNum{};
	int digitProductRatioDen{};
};
digitRatio items;

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
	{L"⁹", L"9"},
};

#pragma endregion
#pragma region Classes

// per tensor
string Variables{};
static void ElabExponents(wstring& str);
template<class T> class tensor
{
private:
	T* data;
	size_t capacity{ 10 };
	size_t count{ 10 };

	void resize(size_t new_capacity)
	{
		if (new_capacity == 0 or new_capacity < capacity) return;
		T* new_data = new(nothrow) T[new_capacity];
		if (!new_data) throw bad_alloc();
		if (data != nullptr) {
			for (size_t i = 0; i < count; ++i) new_data[i] = move(data[i]);
			delete[] data;
		}
		data = new_data;
		capacity = new_capacity;
	}
	void heapify(int n, int i)
	{
		int largest{ i };
		int left{ 2 * i + 1 };
		int right{ 2 * i + 2 };
		if (left < n and (*this)[(left).number] > (*this)[(largest).number])
			largest = left;
		if (right < n and (*this)[(right).number] > (*this)[(largest).number])
			largest = right;
		if (largest != i) {
			iter_swap(this->begin() + i, this->begin() + largest);
			heapify(n, largest);
		}
	}

public:
	tensor()
		: data(nullptr), capacity(0), count(0)
	{
		resize(10);
	}
	tensor(const tensor& other)
		: data(nullptr), capacity(0), count(0)
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
		_STD fill(data, data + count, initial_value);
		count = size;
	}
	~tensor()
	{
		delete[] data;
	}

	tensor& operator=(const tensor& other)
	{
		if (this != &other) {
			resize(other.count);
			for (size_t i = 0; i < other.count; ++i)
				data[i] = other.data[i];
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

	void clear()
	{
		count = 0;
	}
	void erase(size_t pos)
	{
		if (pos >= count) throw out_of_range("Index out of range");
		for (size_t i = pos; i < count - 1; ++i) data[i] = move(data[i + 1]);
		count--;
	}
	void erase(size_t pos, size_t n)
	{
		if (pos >= count) throw out_of_range("Index out of range");
		n = min(n, count - pos);
		for (size_t i = pos; i < count - n; ++i) data[i] = move(data[i + n]);
		count -= n;
	}

	NO_DISCARD_CONST_EXPR T& operator[](size_t index)
	{
		return at(index);
	}
	NO_DISCARD_CONST_EXPR const T& operator[](size_t index) const
	{
		return at(index);
	}

	void push_back(const T& value)
	{
		if (count == capacity) resize(capacity == 0 ? 1 : capacity * 2);
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

	tensor& operator++()
	{
		push_front(T());
		return *this;
	}
	tensor operator++(int)
	{
		tensor temp = *this;
		push_back(T());
		return temp;
	}
	tensor& operator--()
	{
		pop_front();
		return *this;
	}
	tensor operator--(int)
	{
		tensor temp = *this;
		pop_back();
		return temp;
	}

	_NODISCARD bool operator==(const tensor& other) const
	{
		if (count != other.count) return false;
		for (size_t i = 0; i < count; ++i) if (data[i] != other.data[i])
			return false;
		return true;
	}
	_NODISCARD bool operator!=(const tensor& other) const
	{
		return !(*this == other);
	}

	_NODISCARD tensor operator+(const T& value) const
	{
		tensor result = *this;
		result += value;
		return result;
	}
	tensor& operator+=(const T& value)
	{
		push_back(value);
		return *this;
	}
	tensor& operator-=(size_t n)
	{
		count = (n > count) ? 0 : count - n;
		return *this;
	}

	_NODISCARD bool operator<(const tensor& other) const
	{
		return count < other.count;
	}
	_NODISCARD bool operator<=(const tensor& other) const
	{
		return count <= other.count;
	}
	_NODISCARD bool operator>(const tensor& other) const
	{
		return count > other.count;
	}
	_NODISCARD bool operator>=(const tensor& other) const
	{
		return count >= other.count;
	}

	_NODISCARD bool operator&&(const tensor& other) const
	{
		return !this->empty() and !other.empty();
	}
	_NODISCARD bool operator||(const tensor& other) const
	{
		return !this->empty() or !other.empty();
	}
	_NODISCARD bool operator%(const tensor& other) const
	{
		return this->empty() != other.empty();
	}

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

	void sort()
	{
		for (size_t i = 0; i < this->size(); ++i)
			for (size_t j = i + 1; j < this->size(); ++j)
				if (this->at(i).degree < this->at(j).degree)
					swap(this->at(i), this->at(j));
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

	void open()
	{
		for (int i = 0; i < this->size(); ++i) if ((*this)[i][0].degree == -1)
		{
			int repeat{ (*this)[i][0].coefficient };
			this->erase(this->begin() + i);
			auto push{ (*this)[i] };
			for (int j = 0; j < repeat - 1; ++j) this->push_front(push);
		}
	}
	void close()
	{
		tensor<MONOMIAL> CommonFactor;
		for (int i = 0; i < this->size(); ++i)
			for (int j = this->size() - 1; j > i; --j)
				if ((*this)[i] == (*this)[j] and (*this)[i][0].degree != -1)
				{
					CommonFactor = (*this)[i];
					if (i > 0) {

						// caso con esponente
						if ((*this)[i - 1].size() == 1 and 
							(*this)[i - 1][0].degree == -1)
						{
							(*this)[i - 1][0].coefficient++;
							this->erase(this->begin() + j);
						}

						// caso senza esponente
						else {
							int setK = 0;
							this->insert(this->begin(), { {-1, 2} });
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
						int setK = 0;
						this->push_front({ {-1, 2} });
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
	}
	void fill(int s)
	{
		// riempimento buchi
		for (int i = this->size() - 1; i > 0; --i)
			for (int j = 1; j < (*this)[i - 1].degree - (*this)[i].degree; ++j)
				this->insert(this->begin() + i, { (*this)[i - 1].degree - j, 0 });

		// riempimento buchi agli estremi
		if (this->size() == 0)
			for (int i = 0; i < s; ++i) this->push_back({ i, 0 });
		if (this->size() < s)
		{
			while ((*this)[0].degree < s - 1)
				this->insert(this->begin(), { (*this)[0].degree + 1, 0 });
			
			while ((*this)[this->size() - 1].degree > 0)
				this->push_back({ (*this)[this->size() - 1].degree - 1, 0 });
		}
	}

	_NODISCARD wstring str()
	{
		wostringstream result{};
		wstring outp{};

		// bool
		if constexpr (is_same_v<T, bool>)
			for (const auto& element : *this) 
				result << element ? L"1" : L"0" << L", ";
			
		// carattere
		else if constexpr (is_same_v<T, char>) {
			for (const auto& element : *this) result << element;
			result << L", ";
		}

		// dato integrale
		else if constexpr (is_integral_v<T>)
			for (const auto& element : *this)
				result << to_wstring(element) << L", ";

		// stringhe
		else if constexpr (is_same_v<T, wstring>)
			for (const auto& element : *this) result << element << L", ";

		// fattore di un polinomio
		else if constexpr (is_same_v<T, MONOMIAL> or is_same_v<T, REAL_MONOMIAL>)
		{
			wstring xout;
			for (const auto& element : *this) {
				xout = L"";

				// caso con coefficiente sottinteso
				if (element.coefficient != 1 and element.coefficient != -1)
					xout = to_wstring(element.coefficient);

				// caso con grado non nullo
				if (element.degree != 0) {
					xout.append(wstring(1, charVariable));
					if (element.degree != 1)
						xout += L'^' + to_wstring(element.degree);
				}
				else xout = to_wstring(element.coefficient);

				// aggiunta del segno
				if (element.coefficient < 0 and xout.at(0) != '-')
					xout = L'-' + xout;
				else if (element.coefficient > 0) xout = L'+' + xout;

				// aggiunta
				result << xout;
			}
			outp = result.str();
			if (outp.at(0) == '+') outp.erase(0, 1);
			return outp;
		}

		// polinomio scomposto
		else if constexpr (is_same_v<T, tensor<MONOMIAL>>)
		{
			bool set_modifier{ false };
			wstring exp;
			for (auto T : *this) {

				// caso di monomio modificatore
				if (T[0].degree == -1) {
					exp = to_wstring(T[0].coefficient);
					set_modifier = true;
					continue;
				}
				wstring xout = T.str();

				// caso con elevamento a potenza
				if (set_modifier) {
					xout = L'(' + xout + L")^" + exp;
					set_modifier = false;
				}

				// caso di parentesi necessarie
				else if (T.size() > 1) xout = L'(' + xout + L')';
				result << xout;
			}
			outp = result.str();

			// caso nullo
			if (outp.empty()) return L"0";

			// fine
			if (BOOLALPHA) ElabExponents(outp);
			return outp;
		}

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

// estensioni di tensor
class tensor_t
{
public:
	tensor<bool> is_prime;
	tensor<int> list_primes;

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
tensor_t PrimeNumbers{
	{},
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}
};

// classi
class NumberData
{
public:
	int number{};
	wstring code{};
	int degree{};
	wstring expression{};
	tensor<int> sequence{};
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
		wcout.imbue(locale(""));

		// stampa numero
		if (PRINTN) {
			cout << "numero " << number << ":\n";
			SetConsoleTextAttribute(hConsole, 2);
			cout << "in esadecimale è " << hex << uppercase;
			cout << number << "\n" << dec << nouppercase;
		}

		// stampa dati cifre
		else if (number >= 10) {

			// stampa numero
			if (
				digit.digitSumRatioNum == 0 and
				digit.digitProductRatioNum == 0
				) return;
			cout << "numero " << number << ":\n";
			SetConsoleTextAttribute(hConsole, 2);
			cout << "in esadecimale è " << hex << uppercase;
			cout << number << "\n" << dec << nouppercase;
			SetConsoleTextAttribute(hConsole, 13);

			// stampa somma cifre
			if (digit.digitSumRatioNum != 0) {
				wcout << L"la somma delle cifre è ";
				cout << '(' << digit.digitSumRatioNum;
				cout << '/' << digit.digitSumRatioDen;
				cout << ")x\n";
			}

			// stampa prodotto cifre
			if (digit.digitProductRatioNum != 0) {
				wcout << L"il prodotto delle cifre è ";
				if (digit.digitProductRatioDen != 1)
					cout << '(';
				cout << digit.digitProductRatioNum;
				if (digit.digitProductRatioDen != 1) {
					cout << '/';
					cout << digit.digitProductRatioDen;
					cout << ')';
				}
				cout << "x\n";
			}
		}

		// stampa stringa
		if (!code.empty()) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << L"il codice è <" << code << ">\n";
		}

		// stampa grado e sequenza
		if (degree != 0) {
			SetConsoleTextAttribute(hConsole, 4);
			wcout << L"il grado è " << degree << '\n';
			SetConsoleTextAttribute(hConsole, 3);
			wcout << L"la sequenza del grado è :\n(";
			for (int i = 0; i < sequence.size() - 1; ++i)
				cout << sequence[i] << ", ";
			cout << sequence[sequence.size() - 1] << ")\n";
		}

		if (!expression.empty()) {

			// se il numero è primo
			if (PrimeNumbers.is_prime[number]) {
				SetConsoleTextAttribute(hConsole, 240);
				wcout << L"il numero è primo";
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
			}

			// altrimenti stampa scomposizione
			else {
				SetConsoleTextAttribute(hConsole, 11);
				wcout << L"la fattorizzazione è ";
				wcout << expression << '\n';
				if (div.DivNumber != 1) {
					SetConsoleTextAttribute(hConsole, 8);

					// stampa numero divisori
					wcout << L"il numero dei divisori è ";
					cout << div.DivNumber << '\n';

					// stampa somma divisori
					wcout << L"la somma dei divisori è ";
					cout << div.DivSum << '\n';

					// stampa prodotto divisori
					wcout << "il prodotto dei divisori è ";
					if (div.DivProduct != 1)
						cout << div.DivProduct << '\n';
					else cout << div.Div_pr << '\n';
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
private: _STD queue<char> buffer;
public:
	void enqueue(char c)
	{
		buffer.push(c);
	}
	char read()
	{
		if (buffer.size() == 0) buffer.push(_getch());
		auto front{ buffer.front() };
		buffer.pop();
		return front;
	}
};
TestInputReader ObjectGetCh;

// oggetti
struct Console {
	wstring Text;
	int Attribute;
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
	L"rnd"
};

#pragma endregion
#pragma region Declarations

static size_t Factorial(size_t n);
static int Gcd(int A, int B);
static int Gcd(tensor<int> terms);
static int Gcd(tensor<MONOMIAL> terms);
static long long intpow(long long base, int exp);
static wstring ConvertEnumToWString(switchcase Enum);
static switchcase ConvertWStringToEnum(wstring str);
static void ReassigneEnum(switchcase& option);
static void ClearArea(COORD win_center);
static void PrintPFrame
(double deg, int sides, double radius, COORD win_center);
static void DrawFrame
(int arc, double __i, int centerX, int centerY, double DIM);
static void DrawCircleSquare(COORD circle_center);
static void CS_CenterPrinter();
static void CS_CornerPrinter();
static void ProgressBar(double ratio, double barWidth);
static long double WaitingScreen(auto begin, auto end);
static wstring CTSuperScript(char input);
static wstring CFSuperScript(wstring script);
static void DeduceFromExponents(wstring& str);
static void GetFraction(wstring& numerator, wstring& denominator);
static wstring GetLine(bool ShowSuggestions, int sizemax);
static wstring GetUserNum
(wstring txt, int low, long long high, bool ShowSuggestions);
static void SetDebug(string message, switchcase& opt, bool& do_return,
	long long& lower_bound, long long& upper_bound, long long& datalenght
);
static bool Prime(long long number);
static void UserInputThread();
static tensor_t PrimeNCalculator(long long N, bool USE_pro_bar);
static tensor<compost> DecomposeNumber(long long input);
static tensor<wstring> Fractioner(wstring polinomial);
static tensor<int> DecomposeStrings(wstring Terminal);
static wstring Cript(long long input);
static wstring FactNumber(long long input);
static int ExeStrings(wstring input);
static divisor DivisorCalculator(wstring factor);
static digitRatio DigitRationalizer(long long inpt);
static tensor<int> DivisorCounter(int num);
static NumberData ExecuteSimpledeg(long long input);
static NumberData ExecuteDegree(long long input);
static NumberData ExecuteSimpleFact(long long input);
static NumberData ExecuteFactor(long long input);
static NumberData ExecuteSimpleDF(long long input);
static NumberData ExecuteDigit(long long input);
static NumberData ExecuteDegFactor(long long input);
static NumberData ExecuteDegDigit(long long input);
static NumberData ExecuteFactDigit(long long input);
static NumberData ExecuteAll(long long input);
static bool Syntax(wstring polynomial);
static wstring UpdateString(wstring& ToEvaluate);
static wstring SyntaxValidator(wstring ToEvaluate);
static size_t NumberConverter(size_t root, wstring M);
static size_t StringConverter(wstring ToEvaluate);
static void CodeConverter
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static void LongComputation
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary);
static tensor<MONOMIAL> GetMonomials(wstring polynomial);
static tensor<MONOMIAL> PolynomialSum(tensor<MONOMIAL> inp);
static tensor<MONOMIAL> PolynomialMultiply
(tensor<tensor<MONOMIAL>> Polynomial);
static void PolynomialDivide
(
	tensor<MONOMIAL> dividend,
	tensor<MONOMIAL> divisor,
	tensor<MONOMIAL>& quotient,
	tensor<MONOMIAL>& rest
);
static tensor<tensor<MONOMIAL>> Total(tensor<MONOMIAL> inp);
static tensor<tensor<MONOMIAL>> Partial(tensor<MONOMIAL> inpt);
static tensor<tensor<MONOMIAL>> Binomial(tensor<MONOMIAL> InpT);
static tensor<tensor<MONOMIAL>> Trinomial(tensor<MONOMIAL> InpT);
static tensor<tensor<MONOMIAL>> SquareDifference(tensor<MONOMIAL> InpT);
static tensor<tensor<MONOMIAL>> Ruffini(tensor<MONOMIAL> vect);
static tensor<tensor<MONOMIAL>> CompleteTheSquare(tensor<MONOMIAL> vect);
static tensor<tensor<MONOMIAL>> TrinomialSquare(tensor<MONOMIAL> vect);
static tensor<MONOMIAL> Complementary
(tensor<tensor <MONOMIAL>> Polynomial, tensor<MONOMIAL> factor, int exp);
static void Simplify(
	tensor<tensor<MONOMIAL>>& num,
	tensor<tensor<MONOMIAL>>& den,
	int& ncoeff, int& dcoeff);
static int Determinant(tensor<tensor<int>> mx);
static void Approximator
(tensor<REAL_MONOMIAL>& equation, long double& root);
static tensor<long double> ExistenceConditions
(tensor<REAL_MONOMIAL> equation);
template<typename TN, typename TD> static void PrintFraction
(
	int NC, int DC, int& LINE, bool WritePlus,
	tensor<tensor<TN>> numerator,
	tensor<tensor<TD>> denominator
);
static void CodeToNumber(switchcase& argc);
static void Repeater(
	switchcase& argc,
	string message,
	NumberData CPU(long long input)
);
static void Loop(
	switchcase& argc,
	string message,
	NumberData CPU(long long input),
	bool select
);
static tensor<tensor<MONOMIAL>> DecompPolynomial
(switchcase& argc, wstring polynomial);
static void DecompFraction(switchcase& argc);

#pragma endregion

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));

	Beep(1000, 50);
	Beep(1000, 50);

	// dichiarazione stringhe
	string simpledeg{ "il PROGRAMMA calcola solo la codifica di un intero" };
	string simplefact{ "il PROGRAMMA calcola solo la fattorizzazione di un intero" };
	string def_sct{ "il PROGRAMMA calcola solo codifica e fattorizzazione" };
	string desimpledeg{ "il PROGRAMMA calcola solo la codifica di una serie" };
	string desimplefact{ "il PROGRAMMA calcola solo la fattorizzazione di una serie" };
	string defact_message{ "il PROGRAMMA calcola la fattorizzazione di una serie" };
	defact_message.append("\ne numero, somma e prodotto dei divisori");
	string deg_message{ "il PROGRAMMA calcola codice, sequenza e grado di una serie" };
	string fact_message{ "il PROGRAMMA calcola la fattorizzazione di un intero" };
	fact_message.append("\ne numero, somma e prodotto dei divisori");
	string message{ "il PROGRAMMA calcola codice, sequenza e grado di un intero" };
	string AllMessage{ "il PROGRAMMA calcola \"tutti\" i dati di alcuni interi" };
	string de_digit{ "il PROGRAMMA ricerca numeri con particolari" };
	de_digit.append(" occorrenze di somma e prodotto cifre");
	string deg_digit{ "il PROGRAMMA calcola cifre, codice, sequenza e grado" };
	string fact_digit{ "il PROGRAMMA calcola cifre, fattorizzazione, e divisori" };
	string defact_digit{ "il PROGRAMMA calcola tutti i dati, cifre comprese" };
	wstring vel{};
	wstring text;
	switchcase option;

	bool start{ true };
	bool lock_prime_input{ false };
	long long global{ 1 };
	long double ComputationTime;
	size_t Timer{ 100'000'000 };
	while (true)
	{
		bool stop{ false };
		bool skip{ true };
		bool redo{ false };

		if (!lock_prime_input) {
			do {
				redo = false;
				system("cls");
				SetConsoleTitle(TEXT("START"));

				// // output
				SetConsoleTextAttribute(hConsole, 2);
				cout << "*****.*****.*****.*****.******.*****.*****.*****.*****\n\n";
				cout << "*****.*****.*****.[> CALCOLATRICE <].*****.*****.*****\n\n";

				SetConsoleTextAttribute(hConsole, 10);
				cout << "Scegliere il limite per la ricerca dei numeri primi\n";
				cout << "Un limite più alto comporta un tempo di attesa più lungo\n";
				cout << "inserire un numero tra 2 e 10.000.000.000\n\n";

				SetConsoleTextAttribute(hConsole, 2);
				cout << "*****.*****.*****.*****.******.*****.*****.*****.*****\n\n";
				SetConsoleTextAttribute(hConsole, 9);
				// //

				// inserimento punti
				wstring Timer_t{ to_wstring(Timer) };
				for (int i = Timer_t.size() - 3; i > 0; i -= 3)
					Timer_t.insert(Timer_t.begin() + i, '.');

				// input controllato
				text = L"ESEMPIO: " + Timer_t + L" = ~1 minuto di attesa\n";
				wstring G{ GetUserNum(text, 0, GLOBAL_CAP, false) };
				if (ConvertWStringToEnum(G) != NotAssigned) redo = true;
				else if (G.empty()) redo = true;

				// termine programma
				else if (G == L".") goto End;

				// casi 0 e 1
				else global = stoi(G);
				if (global == 1) redo = true;
				if (global == 0) {
					lock_prime_input = true;
					if (start) redo = true;
				}
			} while (redo);
			SetConsoleTextAttribute(hConsole, 15);

			// output del tempo
			if (global != 0 or start) {
				steady_clock::time_point begin{ steady_clock::now() };
				GlobalMax = global;
				SetConsoleCursorInfo(hConsole, &cursorInfo);
				PrimeNumbers = PrimeNCalculator(GlobalMax + 1'000, true);

				steady_clock::time_point end{ steady_clock::now() };
				ComputationTime = WaitingScreen(begin, end);
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorInfo(hConsole, &cursor);
				start = false;
			}
			if (GlobalMax > 9'000 && global > 1) {
				ComputationTime /= 1'000'000;
				Timer = (GlobalMax + 1'000) * 60'000 / ComputationTime;
			}
		}

		// titolo e audio
		system("cls");
		SetConsoleTitle(TEXT("switchcase scegli le opzioni"));
		Beep(750, 300);

		// scelta
		cout << "scegliere la modalità di calcolo::\n";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "se stringa di un carattere:\n";
		cout << "\t'0' = blocca input numeri primi ~[~sempre]\n";
		cout << "\t'1' = sblocca input numeri primi\n";
		cout << "\t'.' = fine programma [sempre]\n";
		SetConsoleTextAttribute(hConsole, 9);
		cout << "altrimenti:\n";
		cout << "\t\"rnd\" = casuale\n";
		cout << "\t\"ctn\" = da codice a numero\n";
		cout << "\t\"pol\" = scomposizione polinomi\n";
		cout << "\t\"alg\" = scomposizione frazioni algebriche\n";
		SetConsoleTextAttribute(hConsole, 11);
		cout << "oppure:\n";
		cout << "primi caratteri:\n";
		cout << "\t'c' = calcolo\n";
		cout << "\t'd' = debug\n";
		cout << "\t\"dr\" = debug ristretto\n";
		SetConsoleTextAttribute(hConsole, 14);
		cout << "caratteri seguenti:\n";
		cout << "\t'c' = solo codifica\n";
		cout << "\t'f' = scomposizione in fattori primi\n";
		cout << "\t\"cc\" = codifica, sequenza e grado\n";
		cout << "\t\"ff\" = fattoizzazione e dati dei divisori\n";
		cout << "\t\"cf\" = codifica e fattorizzazione\n";
		cout << "\t't' = tutti i dati\n";
		SetConsoleTextAttribute(hConsole, 6);
		cout << "solo per il debug ristretto:\n";
		cout << "\t'' = solo dati sulle cifre dei numeri\n";
		cout << "\t'c' = cifre, codifica, sequenza e grado\n";
		cout << "\t'f' = fattorizzazione, cifre e divisori\n";
		cout << "\t't' = tutti i dati compresi quelli sulle cifre\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << "selezionando più operazioni, il tempo di calcolo aumenta\n";

		vel = GetLine(true, 10);
		option = ConvertWStringToEnum(vel);
		bool lock{ false };
		do {

			// gestione input numeri primi
			lock = false;
			if (vel.size() == 1) {
				skip = false;
				switch (vel.at(0)) {
				case '0':
					lock = false;
					lock_prime_input = true;
					cout << "\ninput numeri primi bloccato\n";
					break;
				case '1':
					lock = true;
					lock_prime_input = false;
					cout << "\ninput numeri primi sbloccato\n";
					break;
				case '.': goto End;
					break;
				default: vel += ' ';
				}
			}

			// caso input non assegnato correttamente
			if (option == NotAssigned) do {
				skip = false;
				if (vel.size() == 1) stop = vel.at(0) != '0' and vel.at(0) != '1';
				else {
					option = ConvertWStringToEnum(vel);
					stop = option == NotAssigned;
					skip = option != NotAssigned;
				}
				if (stop) {
					cout << "\n\n";
					SetConsoleTextAttribute(hConsole, 64);
					cout << "NON CORRETTO !!\a";
					SetConsoleTextAttribute(hConsole, 15);
					cout << "\nscegli opzioni:: (...)\n";
					vel = GetLine(true, 10);
				}
			} while (stop);
			if (stop or lock) {
				cout << "\nscegli opzioni:: (...)\n";
				vel = GetLine(true, 10);
				stop = false;
			}
		} while (!skip);
		cout << "\n\n";
		ReassigneEnum(option);
		auto wtitle{ ConvertEnumToWString(option) };

		// cambio titolo
		system("cls");
		auto title{ wtitle.c_str() };
		SetConsoleTitle(title);

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

#pragma region Math

static size_t Factorial(size_t n)
{
	if (n <= 1) return 1;
	return n * Factorial(n - 1);
}
static int Gcd(int A, int B)
{
	if (A < B) swap(A, B);
	while (B != 0) {
		int quotient = A / B;
		int rest = A % B;
		if (rest == 0) return B;
		A = quotient;
		B = rest;
		if (A < B) swap(A, B);
	}
	return A;
}
static int Gcd(tensor<int> terms)
{
	if (terms.size() == 0) return 0;
	if (terms.size() == 1) return terms[0];
	int GCD{ terms[0] };
	for (int i = 1; i < terms.size(); ++i) {
		GCD = Gcd(GCD, terms[i]);
		if (GCD == 1) break;
	}
	return GCD;
}
static int Gcd(tensor<MONOMIAL> terms)
{
	if (terms.size() == 0) return 0;
	if (terms.size() == 1) return terms[0].coefficient;
	int GCD{ terms[0].coefficient };
	for (int i = 1; i < terms.size(); ++i) {
		GCD = Gcd(GCD, terms[i].coefficient);
		if (GCD == 1) break;
	}
	return GCD;
}
static long long intpow(long long base, int exp)
{
	long long power{ 1 };
	auto new_exp{ exp };
	if (base < 0) base *= -1;
	while (new_exp > 0) {
		power *= base;
		if (power < 0) return -1;
		new_exp--;
	}
	if (exp % 2 == 1) return -power;
	return power;
}

#pragma endregion
#pragma region EnumMod

static wstring ConvertEnumToWString(switchcase Enum)
{
	auto it = enumToStringMap.find(Enum);
	if (it != enumToStringMap.end()) return it->second;
}
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
static void ReassigneEnum(switchcase& option)
{
	if (option != Random) return;
	random_device rng;
	mt19937 gen(rng());
	uniform_int_distribution<> dis(0, 19);
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
	}
}

#pragma endregion
#pragma region BasicPrints

int RotAngle{ 270 }, PolygDegree{}, PolygonSides{ 4 };
int CircleCenterX, CircleCenterY, CircleRotDegreeAngle{};
bool DecreaseAngle{ true }, DecreaseWidth{ true };
double DWidth{ 1.9 };

const tensor<int> spectrum{ 9, 9, 9, 11, 11, 3, 3, 12, 4 };

static void ClearArea(COORD win_center)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD consoleSize = intpow(2 * Min.X + 1, 2);
	DWORD written;
	COORD coord;

	coord.X = win_center.X - Min.X;
	coord.Y = win_center.Y - Min.Y;

	for (int y = win_center.Y; y <= win_center.Y + 2 * Min.Y; ++y) {
		coord.Y = y - Min.Y;
		FillConsoleOutputCharacter
		(hConsole, ' ', 2 * Min.X + 1, coord, &written);
	}
}
static void PrintPFrame
(double deg, int sides, double radius, COORD win_center)
{
	SetConsoleTextAttribute(hConsole, 15);

	COORD coord;
	const double DIM{ 1.9 };
	const int centerX{ win_center.X };
	const int centerY{ win_center.Y };
	long double setX, setY;
	long double theta{ 2 * M_PI / sides };

	// calcolo apotema e lato con la goniometria e le formule
	long double sidelenght{ sqrt(2 * pow(radius, 2) * (1 - cos(theta))) };
	long double apotem{ sqrt(pow(radius, 2) - pow(sidelenght / 2, 2)) };

	// stringa dei caratteri per l'illuminazione del poligono
	string prints{ "@$#/*!+=~;:-,." };

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
			cout << prints[index];
		}
	}
}
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
		for (int j = 0; j < spectrum.size(); ++j) if (DisGen == j)
			colour = spectrum[j];

		// stampa
		SetConsoleTextAttribute(hConsole, colour);
		cout << dis(gen);
	}
}
static void DrawCircleSquare(COORD circle_center)
{

	// calcolo variabili
	COORD cursor{ 0, circle_center.Y };
	cursor.Y -= Min.Y;
	const double SPEED{ 50 };
	const double GAP{ 0.05 };
	const int const_x{ circle_center.X };
	const int const_y{ circle_center.Y };
	const double R2{ 5 };
	bool Skip_skipping{ true };

	for (CircleRotDegreeAngle;
		CircleRotDegreeAngle % 2 < 2;
		CircleRotDegreeAngle += 7)
	{
		// termine funzione
		if (is_done.load() and !Skip_skipping) {
			ClearArea(circle_center);
			SetConsoleCursorPosition
			(hConsole, cursor);
			return;
		}
		Skip_skipping = false;

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
		PrintPFrame(PolygDegree * M_PI / 180, PolygonSides, 10, circle_center);
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
		ClearArea(circle_center);
	}
}

#pragma endregion
#pragma region Print

static void CS_CenterPrinter()
{

	// assegnazione delle coordinate del centro
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD win_center;
	if (csbi.dwSize.X / 2 < Min.X) win_center.X = Min.X;
	else win_center.X = csbi.dwSize.X / 2;
	if (csbi.dwSize.Y / 2 < Min.Y) win_center.Y = Min.Y + 1;
	else win_center.Y = csbi.dwSize.Y / 2 + 1;

	// animazione
	DrawCircleSquare(win_center);

}
static void CS_CornerPrinter()
{

	// lettura coordinate
	auto win_center{ Min };
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	for (int i = 1; i < csbi.dwSize.Y; ++i) cout << '\n';

	// animazione
	SetConsoleCursorPosition(hConsole, { 0, 0 });
	DrawCircleSquare(Min);

}
static void ProgressBar(double ratio, double barWidth)
{
	if (barWidth <= 10) return;

	// necessario per poter scrivere messaggi 
	// sotto alla barra di progresso
	SetConsoleCursorPosition(hConsole, { 0, 0 });

	// stampa della barra principale
	cout << "[[";
	int pos{ (int)(barWidth * ratio) };
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) cout << "=";
		else i == pos ? cout << ">" : cout << " ";
	}

	// calcolo della percentuale
	ratio *= 100.0;
	stringstream stream;
	stream << fixed << setprecision(1) << ratio;
	cout << "]] " << stream.str() << "%\r";
}
static long double WaitingScreen(auto begin, auto end)
{
	system("cls");

	// calcolo dati
	long double delta = duration_cast <microseconds> (end - begin).count();
	long double exception_delta = duration_cast <nanoseconds> (end - begin).count();
	stringstream output;
	output << fixed << setprecision(1) << "tempo di calcolo numeri primi = ";

	// calcolo output
	if (delta <= 10'000)
	{
		output << exception_delta / 1'000;
		output << " microsecondi\n\n";
	}
	else if (delta <= 10'000'000)
	{
		output << delta / 1'000;
		output << " millisecondi\n\n";
	}
	else if (delta <= 600'000'000)
	{
		output << delta / 1'000'000;
		output << " secondi\n\n";
	}
	else
	{
		output << delta / 60'000'000;
		output << " minuti\n\n";
	}
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	SetConsoleTextAttribute(hConsole, 6);

	// output
	COORD Cursor;
	Cursor.X = (csbi.dwSize.X - output.str().size()) / 2 - 1;
	Cursor.Y = csbi.dwSize.Y / 2 - 1;
	SetConsoleCursorPosition(hConsole, Cursor);
	cout << output.str();
	sleep_for(seconds(1));

	return exception_delta;
}

#pragma endregion
#pragma region SuperScript

static wstring CTSuperScript(char input)
{
	switch (input) {
	case '0': return L"⁰";
		break;
	case '1': return L"¹";
		break;
	case '2': return L"²";
		break;
	case '3': return L"³";
		break;
	case '4': return L"⁴";
		break;
	case '5': return L"⁵";
		break;
	case '6': return L"⁶";
		break;
	case '7': return L"⁷";
		break;
	case '8': return L"⁸";
		break;
	case '9': return L"⁹";
		break;
	}
	return wstring(1, input);
}
static wstring CFSuperScript(wstring script)
{
	wstring output{};
	for (int i = 0; i < script.size(); ++i) {
		auto digit{ wstring(1, script.at(i)) };
		auto it = ConvertFromSuperScript.find(script);
		if (it != ConvertFromSuperScript.end())
			output += it->second;
		else output += digit;
	}
	return output;
}
static void ElabExponents(wstring& str)
{
	int J{ 1 };
	bool dobreak{ false };
	for (int I = 0; I < str.size(); ++I) {
		int pointer{ I + 1 };
		if (str.at(I) == '^' and I != str.size() - 1) {
			while (isdigit(str.at(pointer)))
			{
				// scelta carattere
				dobreak = false;
				wstring replacer;
				if (str.at(pointer) == '0') {
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
static void DeduceFromExponents(wstring& str)
{
	for (int i = str.size() - 1; i >= 0; --i) {
		auto script{ wstring(1, str.at(i)) };
		auto unscript{ CFSuperScript(script) };
		if (unscript != script) {
			str.erase(i, 1);
			str.insert(str.begin() + i, unscript.at(0));
			str.insert(str.begin() + i, '^');
		}
	}
}

#pragma endregion
#pragma region Input

static void GetFraction(wstring& numerator, wstring& denominator)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));

	int sizevel, diff{};
	numerator = L"";
	denominator = L"";
	wstring vel, command{ L"rnd" }, Num{}, Den{};
	bool script{ true }, arrow{ false }, cursor_at_start{ true };

	// aggiunta di spazio
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto START{ csbi.dwCursorPosition };
	cout << string(10, '\n');
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if (csbi.dwCursorPosition.Y >= START.Y)
		START.Y -= 10 - csbi.dwCursorPosition.Y + START.Y;
	SetConsoleCursorPosition(hConsole, START);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto start{ csbi.dwCursorPosition };
	while (true) if (_kbhit) {

		char c = _getch();
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		auto S{ wstring(csbi.dwSize.X, ' ') + L'\r' };

		bool cond{
			c == '\b' or c == '\t' or c == '\r' or
			c == 'K' or c == 'M' or c > 31 or c == -109
		};
		if (c == -32) arrow = true;
		auto testN{ Num };
		auto testD{ Den };

		if (cond) switch (c) {

			// '.' termina il programma
		case '.':
			numerator = L".";
			SetConsoleCursorInfo(hConsole, &cursorInfo);
			SetConsoleCursorPosition(hConsole, start);
			for (int a = 0; a < 4; ++a) wcout << S << '\n';
			SetConsoleCursorInfo(hConsole, &cursor);
			return;

			// '\r' termina l'input
		case '\r':
			start.Y += 4;
			SetConsoleCursorPosition(hConsole, start);
			if (denominator == L"") denominator = L"1";
			return;

			// '\b' cancella indietro
		case '\b': vel = cursor_at_start ? Num : Den;

			if (vel.size() > 1 and vel.size() - diff > 0)
				vel.erase(vel.size() - 1 - diff, 1);
			else if (vel.size() == 1 and diff == 0) vel = L"";

			if (cursor_at_start) Num = vel;
			else Den = vel;
			break;

			// tab per scegliere il suggerimento
		case '\t': numerator = command;
			break;

			// ctrl + '\b' cancella la prima parte della stringa
		case 127: vel = cursor_at_start ? Num : Den;

			vel.erase(0, vel.size() - diff);
			if (cursor_at_start) Num = vel;
			else Den = vel;
			break;

		default: vel = cursor_at_start ? numerator : denominator;
			
			// aggiunta carattere
			if (!arrow) {
				auto first{ vel };
				auto last{ vel };
				if ((int)vel.size() - diff < 0) diff = vel.size();
				first.erase(vel.size() - diff);
				last.erase(0, vel.size() - diff);
				first += c;
				vel = first + last;

				if (cursor_at_start) numerator = vel;
				else denominator = vel;
				break;
			}
			
			// frecce
			vel = cursor_at_start ? Num : Den;
			sizevel = vel.size();
			switch (c) {
			case 'K': if (diff < sizevel) diff++;
				break;
			case 'M': if (diff > 0) diff--;
				break;

				// canc cancella in avanti
			case 'S':
				if (diff <= 0) break;
				vel.erase(vel.size() - diff, 1);
				diff--;
				break;

				// ctrl + canc cancella la
				// seconda parte della stringa
			case -109:
				vel.erase(vel.size() - diff);
				diff = 0;
				break;

			case 's': diff = sizevel;
				break;
			case 't': diff = 0;
				break;
			}
			if (arrow) arrow = false;
			if (cursor_at_start) Num = vel;
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
		SetConsoleCursorInfo(hConsole, &cursorInfo);
		if (Num.size() > Den.size()) {
			SetConsoleCursorPosition(hConsole, start);
			wcout << S;
			if (!script) {
				SetConsoleTextAttribute(hConsole, 6);
				wcout << command << '\r';
				SetConsoleTextAttribute(hConsole, 15);
			}
			wcout << Num << '\n';
			wcout << S << wstring(Num.size(), '-') << '\n';
			wcout << S << wstring(spaces, ' ') << Den;
		}
		else {
			SetConsoleCursorPosition(hConsole, start);
			wcout << S;
			if (!script) {
				SetConsoleTextAttribute(hConsole, 6);
				wcout << wstring(spaces, ' ');
				wcout << command << '\r';
				SetConsoleTextAttribute(hConsole, 15);
			}
			wcout << wstring(spaces, ' ') << Num << '\n';
			wcout << S << wstring(Den.size(), '-') << '\n';
			wcout << S << Den;
		}

		// reset riga
		if (c == 'H') cursor_at_start = true;
		else if (c == 'P') cursor_at_start = false;

		// reset cursore
		COORD startPos{ start };
		if (cursor_at_start) {
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
static wstring GetLine(bool ShowSuggestions, int sizemax)
{
	int diff{};
	wstring vel{}, E_Vel{}, command{ L"rnd" };
	bool script{ true }, arrow{ false };
	while (true) if (_kbhit()) {
		char c = _getch();
		if (c == '\r') break;
		auto Test{ E_Vel };

		// ignora alcuni caratteri
		bool cond{
			c == '\b' or c == '\t' or
			c == 'K' or c == 'M' or
			c > 31 or c == -109
		};
		if (c == -32) arrow = true;

		if (cond) switch (c) {

			// '.' termina il programma
		case '.': return L".";

			// '\b' cancella indietro
		case '\b':
			if (E_Vel.size() > 1 and E_Vel.size() - diff > 0)
				E_Vel.erase(E_Vel.size() - 1 - diff, 1);
			else if (E_Vel.size() == 1 and diff == 0) E_Vel = L"";
			break;

			// tab per scegliere il suggerimento
		case '\t':
			if (ShowSuggestions) vel = command;
			break;

			// ctrl + '\b' cancella la prima parte della stringa
		case 127: E_Vel.erase(0, E_Vel.size() - diff);
			break;

		default:

			// calcolo differenza in più
			auto copy{ vel };
			copy.erase(0, vel.size() - diff - 1);
			int cursor_position{ (int)vel.size() - diff };
			for (int i = 0; i < (int)copy.size() - 1; ++i)
				if (copy.at(i) == '^' and isdigit(copy.at(i + 1)))
					cursor_position--;

			// aggiunta carattere
			if (!arrow) {
				if (cursor_position < 0) cursor_position = 0;
				auto first{ vel };
				auto last{ vel };
				first.erase(cursor_position);
				last.erase(0, cursor_position);
				first += c;
				vel = first + last;
				break;
			}

			// frecce
			switch (c) {
			case 'K': if (diff < E_Vel.size()) diff++;
				break;
			case 'M': if (diff > 0) diff--;
				break;

				// canc cancella in avanti
			case 'S':
				if (diff <= 0) break;
				E_Vel.erase(E_Vel.size() - diff, 1);
				diff--;
				break;

				// ctrl + canc cancella la
				// seconda parte della stringa
			case -109:
				E_Vel.erase(E_Vel.size() - diff);
				diff = 0;
				break;

			case 's': diff = E_Vel.size();
				break;
			case 't': diff = 0;
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
		if (Velpart.size() - diff >= 0)
			Velpart.erase(Velpart.size() - diff);
		else Velpart = L"";

		// stampa dei caratteri immessi
		if (vel.size() > sizemax) {
			vel = L"";
			E_Vel = L"";
			Velpart = L"";
			diff = 0;
			wcout << '\r' << wstring(sizemax, ' ');
		}
		script = true;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
		if (ShowSuggestions and vel.size() > 0)

			// ricerca suggerimento giusto
			for (auto comma : commands) {
				command = comma;
				auto back{ command };
				if (back.size() == vel.size()) continue;
				if (back.size() > vel.size()) back.erase(vel.size());
				if (back == E_Vel) {
					SetConsoleTextAttribute(hConsole, 6);
					wcout << '\r' << wstring(sizemax, ' ');
					wcout << '\r' << command;
					SetConsoleTextAttribute(hConsole, 15);

					wcout << '\r' << E_Vel << '\r' << Velpart;
					script = false;
					break;
				}
			}
		if (script) {
			wcout << '\r' << wstring(sizemax, ' ');
			wcout << '\r' << E_Vel << '\r' << Velpart;
		}
		SetConsoleCursorInfo(hConsole, &cursor);
	}
	return vel;
}
static wstring GetUserNum
(wstring txt, int low, long long high, bool ShowSuggestions)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	switchcase option;
	long long user_num;
	wstring check;
	do {

		// input
		bool error{ true };
		bool general_error{ false };
		wcout << txt;
		check = GetLine(ShowSuggestions, 10);
		cout << '\n';
		if (check == L"." or check.empty()) return check;
		option = ConvertWStringToEnum(check);
		ReassigneEnum(option);
		if (option != NotAssigned)
			return ConvertEnumToWString(option);

		// controllo
		wregex CheckDigits(L"\\D");
		if (regex_search(check, CheckDigits)) user_num = 0;
		else user_num = stoull(check);

		if (user_num < low or user_num > high) cout << '\a';
	} while (user_num < low or user_num > high);
	return to_wstring(user_num);
}
static void SetDebug(string message, switchcase& opt, bool& do_return,
	long long& lower_bound, long long& upper_bound, long long& datalenght
)
{
	wstring n_{ to_wstring(GlobalMax) }, Input, txt;
	do_return = false;
	wcout << "gli estremi dell'intervallo devono essere compresi";
	wcout << " tra 1 e " << n_ << "\n\n";

	// input e controllo valore iniziale
	SetConsoleTextAttribute(hConsole, 15);
	txt = L"inserisci il valore di inizio della ricerca\n";
	do Input = GetUserNum(txt, 1, GlobalMax, true);
	while (Input.empty());
	if (Input == L".") {
		opt = Random;
		do_return = true;
		return;
	}
	opt = ConvertWStringToEnum(Input);
	ReassigneEnum(opt);
	if (opt != NotAssigned) {
		system("cls");
		auto title{ Input.c_str() };
		SetConsoleTitle(title);
		do_return = true;
		return;
	}
	lower_bound = stoull(Input) + 1;

	// input e controllo valore finale
	txt = L"inserisci il valore finale della ricerca\n";
	do Input = GetUserNum(txt, 1, GlobalMax, true);
	while (Input.empty());
	if (Input == L".") {
		opt = Random;
		do_return = true;
	}
	opt = ConvertWStringToEnum(Input);
	ReassigneEnum(opt);
	if (opt != NotAssigned) {
		system("cls");
		auto title{ Input.c_str() };
		SetConsoleTitle(title);
		do_return = true;
		return;
	}
	upper_bound = stoull(Input) + 1;

	if (upper_bound < lower_bound) swap(lower_bound, upper_bound);
	datalenght = upper_bound - lower_bound;
}

#pragma endregion
#pragma region Primitive

static bool Prime(long long number)
{
	bool is_prime{ true };
	if (number <= 1) return false;
	if (number <= 3) return true;
	if (number < GlobalMax) return PrimeNumbers.is_prime[number];
	if (number % 2 == 0 or number % 3 == 0) return false;
	for (int i = 5; i * i <= number; i += 6)
		if (number % i == 0 or number % (i + 2) == 0) return true;
	return true;
}
static void UserInputThread()
{
	while (computing) {

		// controllo
		char choice{ ObjectGetCh.read() };
		if (choice == 'S' or choice == 's') {
			GlobalInterr = true;
			interrupted = true;
			return;
		}

		// riduzione uso della CPU
		sleep_for(milliseconds(100));
	}
}
static tensor_t PrimeNCalculator(long long N, bool USE_pro_bar)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const int BARWIDTH{ csbi.dwSize.X - 11 };
	if (N < 100'000) USE_pro_bar = false;

	tensor<bool> is_prime(N + 1, true);
	tensor<int> primes;
	int SPEED{ 50 };
	const double COEFF{ 0.3 };
	const int SQUARE{ (int)sqrt(N) + 2 };
	int iter{};
	if (USE_pro_bar) system("cls");

	auto begin{ steady_clock::now() };
	SetConsoleTextAttribute(hConsole, 15);
	for (int p = 2; p < SQUARE; ++p) {

		// calcolo numeri primi
		if (is_prime[p]) for (int i = p * p; i <= N; i += p) is_prime[i] = 0;

		// stampa barra di avanzamento
		if (iter % SPEED == 0 and USE_pro_bar) {
			auto stop{ steady_clock::now() };

			// stampa della barra di avanzamento
			long double progress{ (long double)p / SQUARE };
			if (progress > 0.5) SPEED = 15;
			if (progress > 1) progress = 1;
			ProgressBar(progress, BARWIDTH);

			// calcolo tempo rimanente
			int time = duration_cast <milliseconds> (stop - begin).count();
			long double time_rem{ (time / progress) * (1 - progress) };
			long double time_seconds{ (long double)time_rem / 1'000 };

			// calcolo cifre decimali
			stringstream stream;
			stream << fixed << setprecision(1) << time_seconds;
			cout << "\ntempo rimanente: " << stream.str() << " [secondi]  ";
			if (SPEED < 75) SPEED += 5;
		}
		iter++;
	}

	// rimozione barra di avanzamento
	if (USE_pro_bar) {
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		cout << string(BARWIDTH + 11, '\\') << "\n\nattendere\r";
	}

	// multithreading
	if (USE_pro_bar) {
		thread t1([&]() {
			for (long long p = 2; p < N + 1; ++p)
				if (is_prime[p]) primes.push_back(p);
			lock_guard <mutex> lock(mtx);
			is_done = true;
			cv.notify_one();
			}
		);
		thread t2(CS_CenterPrinter);
		t1.join();
		t2.join();
	}

	else for (long long p = 2; p < N + 1; ++p)
		if (is_prime[p]) primes.push_back(p);
	return tensor_t{ move(is_prime), move(primes) };
}

#pragma endregion
#pragma region Operators

static tensor<compost> DecomposeNumber(long long input)
{

	// correzione intervallo di PrimeNumbers
	if (input > PrimeNumbers.list_primes[PrimeNumbers.list_primes.size() - 1])
	{
		auto PrimeN{ PrimeNCalculator(input, false) };

		// riassegnazione
		for (int i = PrimeNumbers.list_primes.size();
			i < PrimeN.list_primes.size(); ++i) {
			mtx.lock();
			PrimeNumbers.list_primes.push_back(PrimeN.list_primes[i]);
			mtx.unlock();
		}
	}
	int size{};
	int product{ 1 };

	// calcolo limite di approssimazione
	do {
		product *= PrimeNumbers.list_primes[size];
		size++;
	} while (product < GlobalMax);
	tensor<compost> output;
	compost output_element{ 0, 1 };
	for (int i = 0; i < size; ++i) output.push_back(output_element);
	int index{};

	// scomposizione
	for (int i = 0; intpow(PrimeNumbers.list_primes[i], 2) <= input; ++i)
	{
		if (input != 1) {
			if (input % PrimeNumbers.list_primes[i] == 0) {

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
		}
	}
	// eccezione
	if (output[index].factors == input) output[index].exp++;
	else output[index].factors = input;

	return output;
}
static tensor<wstring> Fractioner(wstring polinomial)
{
	tensor<wstring> monomials;
	auto backup{ polinomial };
	wstring temp;
	int parenthesis_balance{};
	int p_balance{};
	int find{};
	for (int i = 0; i < backup.size(); ++i) {
		if (backup.at(i) == '(') parenthesis_balance++;

		// solo in caso di bilancio tra le parentesi e carattere '+'
		if (parenthesis_balance == 0 and backup.at(i) == '+') {
			temp = polinomial;
			for (int finder = 0; finder < temp.size(); ++finder) {

				// scomposizione in monomi
				if (find == 0) {
					if (temp.at(finder) == '(') p_balance++;
					if ((p_balance == 0) and (temp.at(finder) == '+'))
						find = finder;
					if (temp.at(finder) == ')') p_balance--;
				}
			}

			// aggiunta dei monomi alla lista
			temp.erase(find);
			monomials.push_back(temp);
			polinomial.erase(0, find + 1);
			find = 0;
		}
		if (backup.at(i) == ')') parenthesis_balance--;
	}
	monomials.push_back(polinomial);

	return monomials;
}
static tensor<int> DecomposeStrings(wstring Terminal)
{
	int pass{};
	int ciphres_element;
	tensor<int> ciphres;
	for (int i = 0; i < Terminal.size(); ++i) {

		// salta se pass è vero
		while (pass != 0) {
			i++;
			pass--;
		}

		// eccezioni
		if (i >= Terminal.size()) return ciphres;
		if (i == Terminal.size() - 1)
			ciphres_element = Terminal.at(i) - '0';

		// caso di seconda eccezione
		else if (i > Terminal.size() - 3) {
			if (Terminal.at(i + 1) == '0') {
				ciphres_element = 10 * (Terminal.at(i) - '0');
				pass = 1;
			}
			else ciphres_element = Terminal.at(i) - '0';
		}

		// caso con '.'
		else if (Terminal.at(i) == '.') {
			ciphres_element = 10 * (Terminal.at(i + 1) - '0')
				+ (Terminal.at(i + 2) - '0');
			pass = 2;
		}

		// caso con gli zeri
		else {
			if (Terminal.at(i + 1) == '0') {
				ciphres_element = 10 * (Terminal.at(i) - '0');
				pass = 1;
			}

			// caso comune
			else ciphres_element = Terminal.at(i) - '0';
		}

		// aggiunta
		ciphres.push_back(ciphres_element);
	}

	return ciphres;
}

#pragma endregion
#pragma region Calc

static wstring Cript(long long input)
{
	int size{};
	int product{ 1 };

	// calcolo del limite di approssimazione
	do {
		product *= PrimeNumbers.list_primes[size];
		size++;
	} while (product < GlobalMax);

	tensor<compost> expfactors{ DecomposeNumber(input) };
	while (expfactors[expfactors.size() - 1].factors == 0)
		expfactors.pop_back();
	wstring the_string, exp_verify, exp_string, prime_exp_string;
	int prime_exp, sizestring, presence;
	long long analyse;
	bool repeat;
	wstring* monomials{ new(nothrow) wstring[size] };

	// per ogni fattore primo
	for (
		int what_factor = 0;
		what_factor < expfactors.size();
		++what_factor
		)
	{
		repeat = false;
		presence = 0;

		// esponente
		exp_verify = to_wstring(expfactors[what_factor].exp);
		analyse = expfactors[what_factor].factors;
		wstring part_of1{ L"(" };
		wstring part_of2{ L")" };

		// se l'esponente ha una cifra ed è maggiore di 1,
		if (expfactors[what_factor].exp != 1 and
			expfactors[what_factor].exp < 11)
		{
			part_of2.append(exp_verify);
			presence = 1;
		}

		// se l'esponente ha due cifre,
		else if (expfactors[what_factor].exp > 10) {
			part_of2.append(L".");
			part_of2.append(exp_verify);
			presence = 2;
		}

		// si esclude il caso di un esponente a tre cifre
		auto analyse_string{ to_wstring(analyse) };
		the_string = part_of1 + analyse_string + part_of2;

		do {
			// caso con argomento primo
			while (Prime(analyse)) {

				// riduzione dell'argomento
				long long position{ -1 };
				int a{ 1 };
				do {
					if (PrimeNumbers.list_primes[a - 1] == analyse)
						position = a;
					a++;
				} while (position < 0);
				analyse = position;
				analyse_string = to_wstring(analyse);
				the_string.erase(0, the_string.find(')'));
				the_string = part_of1 + analyse_string + the_string;

				// temporanea eliminazione dell'esponente normale
				switch (presence) {
				case 1:
					exp_string = wstring(1, the_string.at(the_string.size() - 1));
					the_string.erase(the_string.size() - 1);
					break;
				case 2:
					exp_string = L'.' + wstring(1, the_string.at(the_string.size() - 2))
						+ wstring(1, the_string.at(the_string.size() - 1));
					the_string.erase(the_string.size() - 3);
					break;
				}

				// aggiunta dell'esponente primo
				if (repeat) {
					prime_exp_string = wstring(1, the_string.at(the_string.size() - 1));
					the_string.erase(the_string.size() - 1);
					prime_exp = stoi(prime_exp_string);
					prime_exp++;
					prime_exp_string = to_wstring(prime_exp);
					if (prime_exp > 10) prime_exp_string = L'.' + prime_exp_string;
					the_string.append(prime_exp_string);
				}

				// riaggiunta dell'esponente normale
				else the_string.append(L"1");
				if (presence > 0) the_string.append(exp_string);
				repeat = true;
			}
			// caso con argomento composto
			if (analyse != 1 and !Prime(analyse)) {
				analyse_string = Cript(analyse);
				the_string.erase(0, the_string.find(')'));
				the_string = part_of1 + analyse_string + the_string;
				analyse = 1;
			}

		} while (analyse != 1);
		monomials[what_factor] = the_string;
	}

	// unione dei monomi
	the_string = L"";
	for (int i = 0; i < expfactors.size(); ++i)
		the_string = the_string + L"+" + monomials[i];
	the_string.erase(0, 1);

	// rimozione basi
	int* position{ new(nothrow) int[size] };
	int j{};
	for (int i = 0; i < (the_string.size() - 2); ++i)
		if ((the_string.at(i) == '(') and (the_string.at(i + 1) == '1')
			and (the_string.at(i + 2) == ')'))
		{
			position[j] = i;
			j++;
		}
	for (int k = j - 1; k >= 0; --k) the_string.erase(position[k], 3);

	// eliminazione parentesi in più
	int l{};
	sizestring = the_string.size();
	if (sizestring > 4) {
		for (int m = 0; m < (the_string.size() - 3); ++m)
			if ((the_string.at(m) == '(') and (the_string.at(m + 3) == ')'))
			{
				position[l] = m;
				l++;
			}
		for (int m = l - 1; m >= 0; --m) {
			the_string.erase(position[m] + 3, 1);
			the_string.erase(position[m], 1);
		}
	}
	delete[] position;

	return the_string;
}
static wstring FactNumber(long long input)
{
	tensor<compost> expfactors{ DecomposeNumber(input) };
	while (expfactors[expfactors.size() - 1].factors == 0)
		expfactors.pop_back();

	// unione dei monomi
	wstring output{};
	for (int i = 0; i < expfactors.size(); ++i) {
		if (expfactors[i].exp != 1) {
			output += to_wstring(expfactors[i].factors);
			output += L'^' + to_wstring(expfactors[i].exp);
			output += L" * ";
		}
		else output += to_wstring(expfactors[i].factors) + L" * ";
	}

	// rimozione della fine
	output.erase(output.size() - 3);

	return output;
}
static int ExeStrings(wstring input)
{
	int size{};
	int product{ 1 };

	// calcolo del limite di approssimazione
	do {
		product *= PrimeNumbers.list_primes[size];
		size++;
	} while (product < GlobalMax);

	int output{};
	int location{};
	bool presence{ true };
	int* values{ new(nothrow) int[size] };
	for (int i = 0; i < input.size(); ++i)
		if (input.at(i) == '.') input.erase(i, 1);
	tensor<wstring> monomials{ Fractioner(input) };

	for (int i = 0; i < monomials.size(); ++i)
	{
		// caso con le parentesi
		if (monomials[i].at(0) == '(') {

			// acquisizione dati
			for (int j = monomials[i].size() - 1; j >= 0; --j)
				if ((presence) and (monomials[i].at(j) == ')')) {
					presence = false;
					location = j;
				}

			// calcolo risultato
			auto temp{ monomials[i] };
			temp.erase(location);
			temp.erase(0, 1);
			monomials[i].erase(0, location + 1);
			values[i] = ExeStrings(temp) * (stoi(monomials[i]));
		}

		// caso senza parentesi
		else values[i] = stoi(monomials[i]);
		presence = true;
	}

	// somma dei monomi
	for (int end = 0; end < monomials.size(); ++end) output += values[end];

	delete[] values;
	return output;
}

static divisor DivisorCalculator(wstring factor)
{
	divisor output{ 1, 1, 1, "" };
	tensor<wstring> monomials;
	tensor<long long> values;
	tensor<int> exponents;
	bool pow_presence{ false };

	// scompozizione in monomi
	for (int i = factor.size() - 1; i >= 0; --i) if (factor.at(i) == '*')
	{
		auto backup{ factor };
		backup.erase(0, i + 2);
		if (backup.at(backup.size() - 1) == ' ')
			backup.erase(backup.size() - 1);
		monomials.push_back(backup);
		factor.erase(i);
	}

	// eccezione
	if (factor.at(factor.size() - 1) == ' ') factor.erase(factor.size() - 1);
	monomials.push_back(factor);

	// ricavo della scomposizione
	for (int i = 0; i < monomials.size(); ++i) {
		long long value{ -1 };
		int exp{ -1 };
		pow_presence = false;
		for (int j = 1; j < monomials[i].size(); ++j)
			if (monomials[i].at(j) == '^') {
				auto first{ monomials[i] };
				auto second{ monomials[i] };
				first.erase(j);
				second.erase(0, j + 1);
				value = stoi(first);
				exp = stoi(second);
				pow_presence = true;
			}
		if (value == -1 and !pow_presence) value = monomials[i].size();
		if (exp == -1 and !pow_presence) exp = 1;
		values.push_back(value);
		exponents.push_back(exp);
	}

	// calcolo del numero dei divisori
	for (int i = 0; i < monomials.size(); ++i)
		output.DivNumber *= exponents[i] + 1;

	// calcolo del numero risultato
	// e della sua somma dei divisori
	long long x{ 1 };
	for (int i = 0; i < monomials.size(); ++i) {
		long long num = -1 + intpow(values[i], exponents[i] + 1);
		long long den{ values[i] - 1 };
		if (den != 0) output.DivSum *= (num / den);
		x *= intpow(values[i], exponents[i]);
	}

	// eccezione
	if (output.DivSum < 0) output.DivSum = -1;

	// calcolo del prodotto dei divisori
	if (output.DivNumber > 0) {
		double out{ (double)output.DivNumber / 2 };
		long long y;
		if (integer(out)) y = intpow(x, out);
		else y = intpow(x, out) * sqrt(x);
		if (y > 0) output.DivProduct = y;

		// caso di overflow
		else if (output.DivNumber % 2 == 0)
			output.Div_pr = to_string(x) + "^" + to_string((long long)out);

		// caso di un quadrato perfetto pari
		else {
			output.Div_pr = to_string((long long)sqrt(x));
			output.Div_pr += "^" + to_string((long long)(out * 2));
		}
	}

	// eccezione
	else {
		output.DivNumber = -1;
		output.DivProduct = -1;
	}

	return output;
}
static digitRatio DigitRationalizer(long long inpt)
{

	// calcolo somma e prodotto cifre
	digitRatio output;
	int digit_sum{}, digit_product{ 1 };
	auto input{ to_string(inpt) };
	for (int i = 0; i < input.size(); ++i) {
		digit_sum += input.at(i) - '0';
		digit_product *= input.at(i) - '0';
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
static tensor<int> DivisorCounter(int num)
{

	// creazione dei vettori con i principali fattori
	tensor<int> vec;
	tensor<compost> expfact{ DecomposeNumber(num) };
	while (expfact[expfact.size() - 1].factors == 0) expfact.pop_back();

	tensor<tensor<int>> MainDiv;
	for (int i = 0; i < expfact.size(); ++i) {
		MainDiv.push_back({});
		int EFelement{ 1 };
		for (int j = 0; j <= expfact[i].exp; ++j) {
			MainDiv[i].push_back(EFelement);
			EFelement *= expfact[i].factors;
		}
	}

	// prodotto cartesiano
	tensor<int> temp;
	for (int i = MainDiv.size() - 1; i > 0; --i) {
		for (auto a : MainDiv[i]) for (auto b : MainDiv[i - 1])
			temp.push_back(a * b);
		MainDiv[i - 1] = temp;
		MainDiv.pop_back();
	}

	return MainDiv[0];
}

#pragma endregion
#pragma region Execute

static NumberData ExecuteSimpledeg(long long input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	return output;
}
static NumberData ExecuteDegree(long long input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	int counter{};
	int copy = input;

	// iterazione per ottenere grado e sequenza
	do {
		output.sequence.push_back(copy);
		copy = ExeStrings(Cript(copy));
		counter++;
		if (copy < 4) output.degree = counter + copy;
	} while (copy != 1);

	output.sequence.push_back(1);
	copy = input;
	return output;
}
static NumberData ExecuteSimpleFact(long long input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	output.expression = FactNumber(input);
	return output;
}
static NumberData ExecuteFactor(long long input)
{
	NumberData output;
	output.number = input;
	output.expression = FactNumber(input);
	divisor D{ DivisorCalculator(output.expression) };
	output.div = D;
	return output;
}
static NumberData ExecuteSimpleDF(long long input)
{
	NumberData output;
	output.number = input;
	output.code = Cript(input);
	output.expression = FactNumber(input);
	return output;
}
static NumberData ExecuteDigit(long long input)
{
	NumberData output;
	digitRatio D{ DigitRationalizer(input) };
	output.number = input;
	output.digit = D;
	return output;
}
static NumberData ExecuteDegFactor(long long input)
{
	NumberData A{ ExecuteDegree(input) };
	NumberData B{ ExecuteFactor(input) };
	A.expression = B.expression;
	A.div = B.div;
	return A;
}
static NumberData ExecuteDegDigit(long long input)
{
	NumberData B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0)
		return B;
	NumberData A{ ExecuteDegree(input) };
	A.digit = B.digit;
	return A;
}
static NumberData ExecuteFactDigit(long long input)
{
	NumberData B{ ExecuteDigit(input) };
	if (B.digit.digitSumRatioNum == 0 and
		B.digit.digitProductRatioNum == 0)
		return B;
	NumberData A{ ExecuteFactor(input) };
	A.digit = B.digit;
	return A;
}
static NumberData ExecuteAll(long long input)
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
#pragma region Convalid

static bool Syntax(wstring polynomial)
{
	if (polynomial.empty()) return false;
	if (polynomial == L"0") return true;
	bool error;
	bool assigne{ false };
	string charsAllowed{ "0123456789+-^" };

	// controllo caratteri
	for (auto a : polynomial) {
		error = true;
		for (auto b : charsAllowed) if (a == b) error = false;
		if (error) {
			if (assigne) return false;
			charVariable = a;
			charsAllowed += charVariable;
			assigne = true;
			if (charVariable < 97 or charVariable > 122) return false;
		}
	}

	// controllo successione caratteri
	string sequence{ "123456789+-" };
	sequence += charVariable;
	bool is_an_exponent{ false };
	int i{};
	for (auto a : polynomial) {
		error = true;
		for (auto b : sequence) if (a == b) error = false;
		if (error) return false;

		// riassegnazione dei caratteri ammessi
		if (a == charVariable) sequence = "+-^";
		else switch (a) {
		case '+':
			sequence = "123456789";
			sequence += charVariable;
			if (is_an_exponent) is_an_exponent = false;
			i = 0;
			break;
		case '-':
			sequence = "123456789";
			sequence += charVariable;
			if (is_an_exponent) is_an_exponent = false;
			i = 0;
			break;
		case '^':
			sequence = "123456789";
			is_an_exponent = true;
			break;
		default:
			sequence = "0123456789+-";
			if (is_an_exponent) i++;
			else sequence += charVariable;
			if (i > 2) return false;
		}
	}

	// controllo al termine
	char end = polynomial.at(polynomial.size() - 1);
	if (end == '+' or end == '-' or end == '^') return false;

	return true;
}
static wstring UpdateString(wstring& ToEvaluate)
{
	// controllo sulle doppie parentesi
	int boundary_balance{};
	for (auto c : ToEvaluate) {
		switch (c) {
		case '<': boundary_balance++;
			break;
		case '>': boundary_balance--;
			break;
		}
		if (boundary_balance > 1 or boundary_balance < 0)
			return L"DOUBLE_BOUNDARIES";
	}

	// suddivisione della stringa in pezzi
	tensor<wstring> pieces{};
	bool start{ true };
	for (int i = ToEvaluate.size() - 1; i >= 0; --i) {

		wstring piece{ ToEvaluate };
		if (ToEvaluate.at(i) == '>') {
			piece.erase(0, i + 1);
			if (i + 1 < ToEvaluate.size()) ToEvaluate.erase(i + 1);
			if (start) start = false;
		}
		else if (ToEvaluate.at(i) == '<' and !start) {
			piece.erase(0, i);
			ToEvaluate.erase(i);
		}
		else continue;
		pieces.push_back(piece);
	}
	if (!ToEvaluate.empty()) pieces.push_back(ToEvaluate);

	// controllo parentesi
	for (auto piece : pieces) {
		if (piece.empty()) continue;
		if (piece.at(0) == '<' and piece.at(piece.size() - 1) == '>')
		{
			piece.erase(piece.size() - 1);
			piece.erase(0, 1);
		}
		if (piece.find('<') != wstring::npos or
			piece.find('>') != wstring::npos)
			return L"INVERTED_BRACKETS";
	}

	// creazione nuova stringa
	ToEvaluate = L"";
	for (auto piece : pieces) {
		if (piece.empty()) continue;
		if (piece.at(0) == '<') {
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
static wstring SyntaxValidator(wstring ToEvaluate)
{
	if (ToEvaluate == L"f") return L"";
	tensor<wstring> mono;
	string charsAllowed{ "0123456789+(_)." };
	bool local_error{ true };
	int stable{};
	int parenthesis_balance{}, count{};

	// eliminazione degli spazi e dei tab
	for (int space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == ' ' or ToEvaluate.at(space) == '\t')
			ToEvaluate.erase(space, 1);

	// ricerca del bilancio tra le parentesi
	for (int i = 0; i < ToEvaluate.size(); ++i) {
		if (ToEvaluate.at(i) == '(') {
			parenthesis_balance++;
			stable++;
		}
		if (ToEvaluate.at(i) == ')') parenthesis_balance--;
	}
	if (parenthesis_balance != 0) return L"UNBALANCED_BRACKETS";

	// se la stringa è vuota
	if (ToEvaluate.empty()) return L"EMPTY_IMPUT";

	// se la stringa contiene caratteri non ammessi
	wregex unallowed_chars(L"[^\\d+()._]");
	if (regex_search(ToEvaluate, unallowed_chars))
		return L"UNALLOWED_CHARACTERS";

	// controllo sugli estremi
	if (ToEvaluate.at(0) == '+') return L"NO_START_STRING";
	if (ToEvaluate.at(0) == '0') return L"NULL_DIGIT";
	if (ToEvaluate.at(0) == ')') return L"INVERTED_BRACKETS";
	if (ToEvaluate.at(ToEvaluate.size() - 1) == '+') return L"NO_END_STRING";

	// controllo sulla non consecutività dei '+'
	wregex no_monomial_(L"\\+{2,}");
	if (regex_search(ToEvaluate, no_monomial_)) return L"MISSING_MONOMIAL";

	// controlli sugli zeri
	wregex cons_null_digits(L"0{2,}");
	if (regex_search(ToEvaluate, cons_null_digits))
		return L"CONSECUTIVE_NULL_DIGITS";
	wregex excep_no_digits(L"\\.");
	wregex no_digits(L"[_\\d]\\.[_1-9][_\\d]");
	if (regex_search(ToEvaluate, excep_no_digits))
		if (!regex_search(ToEvaluate, no_digits)) return L"MISSING_DIGITS";
	wregex s_null_digits(L"[\\r\\D]0");
	if (regex_search(ToEvaluate, s_null_digits)) return L"NULL_DIGITS";

	mono = Fractioner(ToEvaluate);

	// per ogni monomio
	for (int monomial = 0; monomial < mono.size(); ++monomial) {
		int stackfinder{ -1 }, stickfinder{ -1 }, finder{ -1 };
		bool stop{ false }, pass{ false };
		int res{};
		tensor<int> min_ciphres, max_ciphres;
		tensor<int> ciphr_min, ciphr_max;
		wstring min, max;
		auto stack{ mono[monomial] };

		// per ogni secondo monomio
		for (int second = 1; second < mono.size(); ++second) {
			if (monomial != second) {
				if (mono[monomial] == mono[second]) return L"1";
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
				if (stack.at(0) == '(' or stick.at(0) == ')') {

					// ricerca delle parentesi
					stackfinder = stack.find(')');
					stickfinder = stick.find(')');
					if (stackfinder == wstring::npos) stackfinder = -1;
					if (stickfinder == wstring::npos) stickfinder = -1;

					// caso con solo un monomio dotato di parentesi
					if (stackfinder * stickfinder < 0) {
						if (stackfinder > 0) finder = stackfinder;
						else finder = stickfinder;
					}

					// caso con i monomi corrispondenti
					else if (stickfinder == stackfinder) {
						finder = stackfinder;
						for (int l = 0; l <= finder + 1; ++l)
							if (l < min.size())
								if (stick.at(l) != stack.at(l)) stop = true;
						auto min_backup{ min };
						auto max_backup{ max };
						min_backup.erase(0, finder + 2);
						max_backup.erase(0, finder + 2);
						min_ciphres = DecomposeStrings(min_backup);
						max_ciphres = DecomposeStrings(max_backup);
						if (min_ciphres.size() < max_ciphres.size()) {
							ciphr_min = min_ciphres;
							ciphr_max = max_ciphres;
						}
						else {
							ciphr_min = max_ciphres;
							ciphr_max = min_ciphres;
						}
						for (int l = 0; l < ciphr_min.size(); ++l) {
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
					if (min_ciphres.size() < max_ciphres.size()) {
						ciphr_min = min_ciphres;
						ciphr_max = max_ciphres;
					}
					else {
						ciphr_min = max_ciphres;
						ciphr_max = min_ciphres;
					}

					// conta delle ripetizioni
					for (int l = 0; l < ciphr_min.size(); ++l) {
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
					ciphr_max.size() - res <= 1 and
					ciphr_min.size() - res <= 1
					)
					return L"2";
			}
		}

		// // controlli sugli oggetti adiacenti alle parentesi
		finder = stack.find(')');
		if (stack.at(stack.size() - 1) == ')') return L"MISSING_OBJECT";
		if (stack.at(stack.size() - 1) == '(') return L"INVERTED_BRACKETS";
		if (stack.at(0) == '(') {
			local_error = true;

			// controllo sulla necessità delle parentesi
			for (int checkplus = 1; checkplus < finder; ++checkplus)
				if (stack.at(checkplus) == '+') local_error = false;
			if (local_error) return L"USELESS_BRACKETS";

			stack.erase(0, 1);
			stack.erase(finder);
			auto message{ SyntaxValidator(stack) };
			if (!message.empty()) return message;
		}
		else if (mono[monomial].at(0) == ')') return L"INVERTED_BRACKETS";
		else for (int check = 1; check < mono[monomial].size(); ++check) {
			if (mono[monomial].at(check) == '(') return L"WRONG_OBJECT";
			if (mono[monomial].at(check) == ')') return L"WRONG_OBJECT";
		}
		// //
	}

	return L"";
}

#pragma endregion
#pragma region Converters

static size_t NumberConverter(size_t root, wstring M)
{
	bool WhichWay{ true }, XOutOfRange{ false };
	bool UselessExponent{ false }, pass{ false };
	bool XSubscriptOutOfRange{ false };
	int sizeP = PrimeNumbers.list_primes.size(), nums;
	tensor<int> ciphres{ DecomposeStrings(M) };

	// per ogni cifra
	for (int iter = 0; iter < ciphres.size(); ++iter) {

		WhichWay = !WhichWay;
		nums = ciphres[iter];

		// caso esponente
		if (!XOutOfRange and WhichWay) {
			UselessExponent = nums == 1;
			root = intpow(root, nums);
		}

		// caso esponente primo
		else do {
			if (!XOutOfRange and root < sizeP) {
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
static size_t StringConverter(wstring ToEvaluate)
{
	size_t integer{ 1 };
	wstring backup, back;
	tensor<wstring> mono{ Fractioner(ToEvaluate) };
	int sizeP = PrimeNumbers.list_primes.size();
	int finder{ -1 };

	// per ogni monomio
	for (int monomial = 0; monomial < mono.size(); ++monomial) {
		auto M{ mono[monomial] };
		long long root;
		bool WhichWay{ false };
		if (M.at(0) != '(') root = NumberConverter(1, M);
		else {

			// calcolo preciso
			back = M;
			backup = M;
			backup.erase(0, M.find(')'));
			back.erase(M.find(')') - 1);
			back.erase(0, 1);
			root = StringConverter(back);
			root = NumberConverter(root, backup);
		}
		if (root < 0) return root; // eccezione
		else integer *= root; // caso comune
	}

	return integer;
}
static void CodeConverter
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	long long number;
	if (ToEvaluate == L"f") return;

	for (int space = ToEvaluate.size() - 1; space >= 0; --space)
		if (ToEvaluate.at(space) == ' ' or ToEvaluate.at(space) == '\t')
			ToEvaluate.erase(space, 1);
	if (NecBoundary) UpdateString(ToEvaluate);
	number = StringConverter(ToEvaluate);

	// caso normale
	if (ShowErrors or number > 0) {
		auto text{ L"codice <" + ToEvaluate + L"> :\n" };
		ConsoleText.push_back({ text , 11 });
	}

	// caso con overflow interno
	if (number < -2 and ShowErrors) {
		auto text{ L"ERR[413]: X_SUBSCRIPT_OUT_OF_RANGE\n" };
		ConsoleText.push_back({ text , 12 });
	}

	// caso di comune overflow
	if (number == -1 and ShowErrors) {
		auto text{ L"ERR[413]: X_OUT_OF_RANGE\n" };
		ConsoleText.push_back({ text , 12 });
	}

	// caso errato per esponente inutile
	if (number == -2 and ShowErrors) {
		auto text{ L"ERR[413]: USELESS_EXPONENT\n" };
		ConsoleText.push_back({ text , 6 });
	}

	// caso errato con correzione
	if (!message.empty() and ShowErrors and number > 0) {

		wstring text{
			message == L"1" ?
			L"ERR[400]: EQUAL_MONOMIALS\n" :
			L"ERR[400]: SIMILIAR_MONOMIALS\n"
		};
		ConsoleText.push_back({ text , 15 });

		if (number < GlobalMax)
			text = L"codice corretto: <" + Cript(number) + L">\n";
		else text = L"codice corretto non disponibile\n";

		ConsoleText.push_back({ text , 2 });
	}

	// caso con errori nascosti per scelta utente
	if (number > 0) {
		auto text{ L"il numero corrispondente e' " };
		ConsoleText.push_back({ text , 15 });
		ConsoleText.push_back({ to_wstring(number) + L'\n' , 4 });
	}
}
static void LongComputation
(wstring ToEvaluate, wstring message, bool ShowErrors, bool NecBoundary)
{
	computing = true;
	interrupted = false;

	// conta dei caratteri '_' e archivio della posizione
	auto backup{ ToEvaluate };
	int counter{};
	tensor<int> pos;
	for (int i = 0; i < ToEvaluate.size(); ++i)
		if (ToEvaluate.at(i) == '_') {
			pos.push_back(i);
			counter++;
		}

	// caso di stringa univoca
	lock_guard <mutex> lock(CoutMutex);
	if (counter == 0) {
		CodeConverter(ToEvaluate, message, ShowErrors, NecBoundary);
		for (auto a : ConsoleText) {
			SetConsoleTextAttribute(hConsole, a.Attribute);
			wcout << a.Text;
			SetConsoleTextAttribute(hConsole, 15);
		}
		ConsoleText = {};
	}

	// caso di stringa ripetuta
	else for (int i = 0; i < intpow(10, counter); ++i) {

		// passa variabili per indirizzo
		thread t1([&]() {

			auto j{ to_string(i) };
			backup = ToEvaluate;
			int zero_counter = counter - j.size();
			for (int k = 0; k < zero_counter; ++k) j = "0" + j;
			for (int k = 0; k < j.size(); ++k)
				backup.replace(pos[k], 1, wstring(1, j.at(k)));
			if (NecBoundary) UpdateString(backup);
			message = SyntaxValidator(backup);

			// eventuale stampa degli errori
			lock_guard<mutex> lock(mtx);
			if (message.size() > 1 and ShowErrors) {

				auto text{ L"codice <" + backup + L"> :\n" };
				ConsoleText.push_back({ text , 11 });

				text = L"ERR[404]: " + message + L"\n";
				ConsoleText.push_back({ text , 4 });
			}
			else CodeConverter(backup, message, ShowErrors, false);
			if (interrupted) return;

			is_done = true;
			cv.notify_one();
			});
		thread t2(CS_CornerPrinter);
		t1.join();
		t2.join();

		for (auto a : ConsoleText) {
			SetConsoleTextAttribute(hConsole, a.Attribute);
			wcout << a.Text;
			SetConsoleTextAttribute(hConsole, 15);
		}
		ConsoleText = {};
	}
	computing = false;
	Cv.notify_one();
}

#pragma endregion
#pragma region HandPolynomials

static tensor<MONOMIAL> GetMonomials(wstring polynomial)
{
	tensor<MONOMIAL> output;
	MONOMIAL output_element;

	for (int i = polynomial.size() - 1; i >= 0; --i)
		if (polynomial.at(i) == '+' or
			polynomial.at(i) == '-' or
			i == 0)
		{
			wstring mono{ polynomial };
			wstring coeff{};
			mono.erase(0, i);
			int var_pos{ -1 };

			// calcolo del segno
			int sign{ 1 };
			if (mono.at(0) == '-') sign = -1;
			if (mono.at(0) == '+' or mono.at(0) == '-') mono.erase(0, 1);

			// se il coefficiente è sottinteso
			if (mono.at(0) == charVariable) {
				output_element.coefficient = 1;
				var_pos = 0;
			}

			// caso con il coefficiente
			else {
				for (int j = 0; j < mono.size(); ++j) {
					if (mono.at(j) == charVariable) {
						var_pos = j;
						break;
					}
					coeff += wstring(1, mono.at(j));
				}
				if (coeff == mono) output_element.degree = 0;
				output_element.coefficient = stoi(coeff);
			}

			// caso di grado non nullo
			if (coeff != mono) {
				if (mono == wstring(1, charVariable))
					output_element.degree = 1;
				else if (mono.size() > var_pos + 1)
					if (mono.at(var_pos + 1) == '^') {
						mono.erase(0, var_pos + 2);
						output_element.degree = stoi(mono);
					}
					else output_element.degree = 1;
				else output_element.degree = 1;
			}

			// aggiunta
			output_element.coefficient *= sign;
			output.push_back(output_element);
			polynomial.erase(i);
		}

	return output;
}
static tensor<MONOMIAL> PolynomialSum(tensor<MONOMIAL> inp)
{
	// ricerca di monomi simili
	for (int i = inp.size() - 1; i >= 0; --i)
		for (int j = i - 1; j >= 0; --j)	
			if (inp[i].degree >= 0 and inp[j].degree >= 0)
				if(inp[i].degree == inp[j].degree) {
					inp[i].coefficient += inp[j].coefficient;
					inp[j].coefficient = 0;
				}
		
	// marcamento dei monomi simili
	for (int i = inp.size() - 1; i >= 0; --i)
		if (inp[i].coefficient == 0) inp[i].degree = -1;
	
	// rimozione
	auto it = remove_if(
		inp.begin(), 
		inp.end(), 
		[](const MONOMIAL& m) {
			return m.degree == -1;
		}
	);
	if (it != inp.end()) inp.erase(it, inp.end());

	return inp;
}
static tensor<MONOMIAL> PolynomialMultiply
(tensor<tensor<MONOMIAL>> Polynomial)
{
	if (Polynomial.size() == 0) return { {0, 1} };
	Polynomial.open();
	while (Polynomial.size() > 1) {

		MONOMIAL temp;
		tensor<MONOMIAL> Temp;
		for (auto A : Polynomial[0])
			for (auto B : Polynomial[1]) {
				temp.coefficient = A.coefficient * B.coefficient;
				temp.degree = A.degree + B.degree;
				Temp.push_back(temp);
			}
		Polynomial.pop_front();
		Polynomial.pop_front();
		Polynomial.push_front(Temp);
	}
	return PolynomialSum(Polynomial[0]);
}
static void PolynomialDivide
(
	tensor<MONOMIAL> dividend,
	tensor<MONOMIAL> divisor,
	tensor<MONOMIAL>& quotient,
	tensor<MONOMIAL>& rest
)
{

	// aggiustamento polinomi
	dividend.sort();
	divisor. sort();
	dividend.fill(dividend[0].degree);
	divisor. fill(divisor[0].degree);
	dividend.sort();
	divisor. sort();
	quotient = {};

	// divisione
	while (dividend[0].degree >= divisor[0].degree) {

		auto divide{ divisor };
		int deg{ dividend[0].degree };
		int _deg{ divisor[0].degree };
		int rest_element{ dividend[0].coefficient };
		rest_element /= divisor[0].coefficient;
		for (int i = 0; i < divide.size(); ++i) {
			divide[i].coefficient *= -rest_element;
			divide[i].degree += deg - _deg;
		}
		for (int i = 0; i < dividend.size(); ++i)
			divide.insert(divide.begin() + i, dividend[i]);
		dividend = PolynomialSum(divide);
		dividend.fill(deg);
		dividend.sort();
		quotient.push_back({ deg - _deg, rest_element });
	}
	rest = dividend;
}

#pragma endregion
#pragma region Techniques

static tensor<tensor<MONOMIAL>> Total(tensor<MONOMIAL> inp)
{
	tensor<tensor<MONOMIAL>> output;
	output.push_back(inp);
	int min;
	if (inp.size() <= 1) return output;
	min = inp[0].degree;

	// calcolo grado minimo e riscrittura
	int GCD{ Gcd(inp) };
	for (auto t : inp) if (t.degree < min) min = t.degree;
	if (fabs(GCD) != 1 or min > 0) {
		output = {};
		output.push_back({ {min, GCD} });
		for (int i = 0; i < inp.size(); ++i) {
			inp[i].coefficient /= GCD;
			inp[i].degree -= min;
		}
	}

	// totale
	if (fabs(GCD) != 1 or min > 0) {
		output = {};
		output.push_back({ {min, GCD} });
		output.push_back(inp);
		return output;
	}
	return { inp };
}
static tensor<tensor<MONOMIAL>> Partial(tensor<MONOMIAL> inpt)
{

	// filtro vettori a quattro termini
	tensor<tensor<MONOMIAL>> outp;
	outp.push_back(inpt);
	if (inpt.size() != 4) return outp;
	inpt.sort();

	// riassegnazione e dichiarazioni
	tensor<MONOMIAL> part_1{ inpt[0], inpt[1] };
	tensor<MONOMIAL> part_2{ inpt[2], inpt[3] };
	auto Part1{ Total(part_1) };
	auto Part2{ Total(part_2) };
	auto part_3{ Part1[Part1.size() - 1] };
	for (auto a : Part2[Part2.size() - 1]) part_3.push_back(a);
	if (PolynomialSum(part_3).size() == 0) {
		if (Part1.size() == 1) swap(Part1, Part2);
		Part2.push_front({ { 0, -1 } });
		for (int i = 0; i < Part2[1].size(); ++i)
			Part2[1][i].coefficient *= -1;
	}
	part_1 = Part1[Part1.size() - 1];
	part_2 = Part2[Part2.size() - 1];
	if (part_1 != part_2) return outp;
	outp = {};

	// riordinamento del totale
	tensor<tensor<MONOMIAL>> mon_1;
	tensor<tensor<MONOMIAL>> mon_2;
	if (Part1.size() == 1) mon_1.push_back({ MONOMIAL{ 0, 1 } });
	else mon_1.push_back(Part1[0]);
	if (Part2.size() == 1) mon_2.push_back({ MONOMIAL{ 0, 1 } });
	else mon_2.push_back(Part2[0]);
	mon_1.push_back(part_1);
	mon_2.push_back(part_2);

	// riordinamento del parziale
	outp.push_back(part_1);
	part_2 = mon_1[0];
	for (auto a : mon_2[0]) part_2.push_back(a);
	part_2 = PolynomialSum(part_2);

	outp.push_back(part_2);
	return outp;
}
static tensor<tensor<MONOMIAL>> Binomial(tensor<MONOMIAL> InpT)
{

	// filtro per vettori con più di un termine
	tensor<tensor<MONOMIAL>> outp;
	outp.push_back(InpT);
	int exponent = InpT.size() - 1, sign{ 1 };
	if (exponent <= 1) return outp;
	bool reassigne{ false };
	InpT.sort();

	auto A{ InpT[0] };
	auto B{ InpT[InpT.size() - 1] };

	// controllo per evitare radici impossibili da eseguire nei reali
	if (exponent % 2 == 0 and (A.coefficient < 0 or B.coefficient < 0))
		return outp;

	// calcolo delle radici
	double Sq_A, Sq_B;
	if (A.coefficient > 0) Sq_A = pow(A.coefficient, 1.0 / exponent);
	else Sq_A = -pow(-A.coefficient, 1.0 / exponent);
	if (B.coefficient > 0) Sq_B = pow(B.coefficient, 1.0 / exponent);
	else Sq_B = -pow(-B.coefficient, 1.0 / exponent);

	// controllo sulle potenze
	if (!integer(Sq_A)) return outp;
	if (!integer(Sq_A)) return outp;
	if (A.degree % exponent != 0) return outp;
	if (B.degree % exponent != 0) return outp;
	int Adeg{ A.degree / exponent };
	int Bdeg{ B.degree / exponent };

	for (int i = 1; i < exponent; ++i) {

		// calcolo coefficiente
		if (InpT[i].degree != Adeg * (exponent - i) + Bdeg * i)
			return outp;
		int coeff = Factorial(exponent) / (Factorial(i) * Factorial(exponent - i));

		// caso con la sottrazione
		if (InpT[i].coefficient ==
			-coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
			)
		{
			if (!reassigne) {
				sign = -1;
				reassigne = true;
			}
			else if (sign == 1) return outp;
		}

		// caso con l'addizione
		else if (InpT[i].coefficient ==
			coeff * (int)pow(Sq_A, exponent - i) * (int)pow(Sq_B, i)
			)
		{
			if (!reassigne) {
				sign = 1;
				reassigne = true;
			}
			else if (sign == -1) return outp;
		}

		// caso non accettato
		else return outp;
	}

	// composizione della potenza di binomio
	outp = {};
	outp.push_back({ {-1, exponent} });
	outp.push_back(InpT);
	outp[1] = {};
	outp[1].push_back({ A.degree / exponent, (int)Sq_A });
	outp[1].push_back({ B.degree / exponent, sign * (int)Sq_B });

	return outp;
}
static tensor<tensor<MONOMIAL>> Trinomial(tensor<MONOMIAL> InpT)
{

	// filtro per vettori di tre termini
	tensor<tensor<MONOMIAL>> outp;
	outp.push_back(InpT);
	if (InpT.size() != 3) return outp;

	// calcolo termini ed esponente
	tensor<MONOMIAL> terms;
	int A, B, C;
	for (int i = 0; i < InpT.size(); ++i) {
		if (InpT[i].degree != 0) terms.push_back(InpT[i]);
		else C = InpT[i].coefficient;
	}
	if (terms[0].degree > terms[1].degree)
		swap(terms[0], terms[1]);
	double exp = terms[1].degree / (terms[0].degree * 2);
	if (!integer(exp)) return outp;
	A = terms[1].coefficient;
	B = terms[0].coefficient;

	// calcolo delle radici
	double firstX, secondX, delta;
	delta = B * B - 4 * A * C;
	if (delta <= 0) return outp;
	if (!integer(sqrt(delta))) return outp;
	firstX = (-B - sqrt(delta)) / (2 * A);
	secondX = (-B + sqrt(delta)) / (2 * A);
	if (!integer(A * firstX * secondX)) return outp;
	outp = {};

	// calcolo dei coefficienti
	int I, J;
	for (I = 1; I <= fabs(A); ++I) if (integer(firstX * I)) break;
	if (I == fabs(A) + 1) I--;
	if (A < 0) I = -I;
	for (J = 1; J <= fabs(A); ++J) if (integer(secondX * J)) break;
	if (J == fabs(A) + 1) J--;

	// composizione del trinomio scomposto
	outp = { {}, {} };
	outp[0].push_back(MONOMIAL{ (int)exp, I });
	outp[0].push_back(MONOMIAL{ 0, (int)(-I * firstX) });
	outp[1].push_back(MONOMIAL{ (int)exp, J });
	outp[1].push_back(MONOMIAL{ 0, (int)(-J * secondX) });

	return outp;
}
static tensor<tensor<MONOMIAL>> SquareDifference(tensor<MONOMIAL> InpT)
{

	// filtro per vettori di due termini
	tensor<tensor<MONOMIAL>> outp;
	outp.push_back(InpT);
	if (InpT.size() != 2) return outp;

	// controllo sui quadrati perfetti
	if (InpT[0].degree % 2 == 1) return outp;
	if (InpT[1].degree % 2 == 1) return outp;

	// riassegnazione se i segni non vanno bene
	bool Sign_A{ InpT[0].coefficient > 0 };
	bool Sign_B{ InpT[1].coefficient > 0 };
	if (Sign_A == Sign_B) return outp;

	// calcolo radici
	double Sq_A{ sqrt(fabs(InpT[0].coefficient)) };
	double Sq_B{ sqrt(fabs(InpT[1].coefficient)) };
	if (!integer(Sq_A)) return outp;
	if (!integer(Sq_B)) return outp;

	// composizione di somma e differenza
	outp = { {}, {} };
	outp[0].push_back(MONOMIAL{ InpT[1].degree / 2, +(int)Sq_B });
	outp[0].push_back(MONOMIAL{ InpT[0].degree / 2, +(int)Sq_A });
	outp[1].push_back(MONOMIAL{ InpT[1].degree / 2, +(int)Sq_B });
	outp[1].push_back(MONOMIAL{ InpT[0].degree / 2, -(int)Sq_A });
	if (Sign_A) {
		outp[1][0].coefficient *= -1;
		outp[1][1].coefficient *= -1;
	}

	return outp;
}
static tensor<tensor<MONOMIAL>> Ruffini(tensor<MONOMIAL> vect)
{

	// filtro per vettori con più di un termine
	tensor<tensor<MONOMIAL>> VECT;
	VECT.push_back(vect);
	if (vect.size() < 2) return VECT;
	if (vect.size() == 2 and (vect[0].degree == 1 or vect[1].degree == 1))
		return VECT;
	vect.sort();

	int DirectorTerm{ vect[0].coefficient };
	int size{ vect[0].degree };
	int KnownTerm{ vect[vect.size() - 1].coefficient };
	if (fabs(DirectorTerm) >= GlobalMax or fabs(KnownTerm) >= GlobalMax)
		return {};

	// calcolo divisori
	tensor<int> P{ DivisorCounter(fabs(KnownTerm)) };
	tensor<int> Q{ DivisorCounter(fabs(DirectorTerm)) };
	tensor<int> PossibleRoots;

	// teorema delle radici razionali
	for (auto p : P) for (auto q : Q) PossibleRoots.push_back(p / q);
	int SetRoot{};
	int Root;

	tensor<MONOMIAL> Try;
	bool assigne{ true };
	for (int n = 1; n < size; ++n) {

		// riduzione del polinomio
		Try = vect;
		assigne = true;
		for (int m = 0; m < Try.size(); ++m) {
			long double a{ (double)Try[m].degree / n };
			if (!integer(a)) {
				assigne = false;
				break;
			}
			Try[m].degree = a;
		}
		if (assigne) vect = Try;

		// eventuale aggiunta dei coefficienti nulli	
		for (int i = 1; i < vect.size(); ++i)
			for (int j = 1; j < vect[i - 1].degree - vect[i].degree; ++j)
				vect.insert(vect.begin() + i, { vect[i - 1].degree - j, 0 });

		// regola di ruffini
		tensor<MONOMIAL> temp;
		for (auto root : PossibleRoots) {
			Root = root;
			do {

				// divisione polinomio per binomio
				temp = vect;
				for (int i = 1; i < vect.size(); ++i) {
					temp[i].coefficient = Root * temp[i - 1].coefficient
						+ temp[i].coefficient;
					temp[i].degree--;
				}

				// caso con resto nullo
				if (temp[temp.size() - 1].coefficient == 0) {
					temp[0].degree--;
					temp.pop_back();
					SetRoot = Root;
					vect = temp;
					break;
				}

				Root = -Root;
			} while (Root != root);
			if (SetRoot != 0) break;
		}
		vect = PolynomialSum(vect);

		// caso di polinomio scomposto
		if (SetRoot != 0) {
			for (int i = 0; i < vect.size(); ++i) vect[i].degree *= n;
			VECT = {};
			VECT.push_back({ {n, 1}, {0, -SetRoot} });
			VECT.push_back(vect);
			break;
		}

		// ripristino polinomio
		if (assigne) for (int i = 0; i < vect.size(); ++i) vect[i].degree *= n;
	}

	return VECT;
}
static tensor<tensor<MONOMIAL>> CompleteTheSquare(tensor<MONOMIAL> vect)
{

	// filtro per vettori con tre termini
	tensor<tensor<MONOMIAL>> Vect;
	Vect.push_back(vect);
	if (vect.size() != 3) return Vect;
	vect.sort();
	auto A{ vect[0] };
	auto B{ vect[2] };

	// calcolo delle radici
	if (A.coefficient < 0 or B.coefficient < 0) return Vect;
	double Sq_A{ sqrt(A.coefficient) };
	double Sq_B{ sqrt(B.coefficient) };

	// controllo sulle potenze
	if (!integer(Sq_A)) return Vect;
	if (!integer(Sq_B)) return Vect;

	// controllo sui gradi
	if (A.degree % 2 == 1 or A.degree / 2 == 1) return Vect;
	if (B.degree % 2 == 1 or B.degree / 2 == 1) return Vect;
	if (vect[1].degree != A.degree / 2 + B.degree / 2) return Vect;
	if (!integer(A.degree / 4 + B.degree / 4)) return Vect;

	// calcolo quadrato di differenza
	MONOMIAL DiffSquare, Diffneg;
	DiffSquare.degree = A.degree / 4 + B.degree / 4;
	int middleterm{ 2 * (int)Sq_A * (int)Sq_B }, sign;
	int CasePlus{ middleterm - vect[1].coefficient };
	int CaseMinus{ -middleterm - vect[1].coefficient };
	if (CasePlus < 0) return Vect;
	if (integer(sqrt(CasePlus))) {
		DiffSquare.coefficient = sqrt(CasePlus);
		sign = 1;
	}
	else if (integer(sqrt(-CaseMinus))) {
		DiffSquare.coefficient = sqrt(-CaseMinus);
		sign = -1;
	}
	else return Vect;
	Diffneg.coefficient = -DiffSquare.coefficient;
	Diffneg.degree = DiffSquare.degree;

	// composizione di somma e differenza
	Vect.push_back(vect);
	Vect[0] = {};
	Vect[1] = {};

	Vect[0].push_back({ A.degree / 2 , (int)Sq_A });
	Vect[0].push_back({ B.degree / 2 , (int)Sq_B });
	Vect[0].push_back(DiffSquare);
	Vect[1].push_back({ A.degree / 2 , (int)Sq_A });
	Vect[1].push_back({ B.degree / 2 , (int)Sq_B });
	Vect[1].push_back(Diffneg);

	return Vect;
}
static tensor<tensor<MONOMIAL>> TrinomialSquare(tensor<MONOMIAL> vect)
{
	// filtro per vettori con 5 o 6 termini
	tensor<tensor<MONOMIAL>> output;
	output.push_back(vect);
	vect.sort();
	if (vect.size() != 5 and vect.size() != 6) return output;

	// calcolo coefficienti
	double A{ sqrt(vect[0].coefficient) };
	if (!integer(A)) return output;
	double C{ sqrt(vect[vect.size() - 1].coefficient) };
	if (!integer(C)) return output;
	double B{ (double)vect[vect.size() - 2].coefficient / (2 * C) };
	if (!integer(B)) return output;
	if (fabs(B) != (double)vect[1].coefficient / (2 * A)) return output;
	double middle_deg = vect[vect.size() - 2].degree, director_deg;

	// caso generico
	bool AB2, AC2, BC2;
	if (vect.size() == 6) {

		// controllo gradi
		bool direct_double_middle;
		director_deg = (double)vect[0].degree / 2;
		if (!integer(director_deg)) return output;
		if (vect[1].degree != middle_deg + director_deg) return output;
		if (vect[2].degree == 2 * middle_deg and
			vect[3].degree == director_deg)
			direct_double_middle = false;
		else if (
			vect[3].degree == 2 * middle_deg and
			vect[2].degree == director_deg
			)
			direct_double_middle = true;
		else return output;

		// verifica coefficienti centrali
		if (direct_double_middle) {
			if (fabs(vect[2].coefficient) != fabs(2 * A * C)) return output;
			if (vect[3].coefficient != B * B) return output;
		}
		else {
			if (fabs(vect[3].coefficient) != fabs(2 * A * C)) return output;
			if (vect[2].coefficient != B * B) return output;
		}
		AC2 = vect[3 - direct_double_middle].coefficient >= 0;
	}

	// caso specifico
	else if (vect.size() == 5) {

		// verifica
		for (int i = 0; i <= 2; ++i)
			if (vect[i].degree != (4 - i) * vect[3].degree) return output;
		if (fabs(vect[2].coefficient) == fabs(2 * A * C + B * B))
			AC2 = vect[2].coefficient - B * B >= 0;
		else if (fabs(vect[2].coefficient) == fabs(2 * A * C - B * B))
			AC2 = vect[2].coefficient + B * B >= 0;
		else return output;
		director_deg = 2 * middle_deg;
	}
	AB2 = vect[1].coefficient >= 0;
	BC2 = vect[vect.size() - 2].coefficient >= 0;
	int sign_number = AB2 + AC2 + BC2;

	if (sign_number % 2 == 1) return output;
	A = A >= 0 ? A : -A;
	B = B >= 0 ? B : -B;
	C = C >= 0 ? C : -C;
	if (AB2) C = -C;
	else if (AC2) B = -B;
	else if (BC2) C = -C;

	// composizione del quadrato di trinomio
	output = { {}, {} };
	output[0].push_back({ -1, 2 });
	output[1].push_back({ (int)director_deg, (int)A });
	output[1].push_back({ (int)middle_deg, (int)B });
	output[1].push_back({ 0, (int)C });
	return output;
}

#pragma endregion
#pragma region Algebraic

static tensor<MONOMIAL> Complementary
(tensor<tensor<MONOMIAL>> Polynomial, tensor<MONOMIAL> factor, int exp)
{

	// caso di eccezione
	if (Polynomial[0] == factor) Polynomial.pop_front();

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

	return PolynomialMultiply(Polynomial);
}

static void Simplify(
	tensor<tensor<MONOMIAL>>& num,
	tensor<tensor<MONOMIAL>>& den,
	int& ncoeff, int& dcoeff)
{
	num.open();
	den.open();
	for (int i = 0; i < num.size(); ++i) num[i].sort();
	for (int i = 0; i < den.size(); ++i) den[i].sort();

	// semplificazione fattori
	int sign{ 1 };
	for (int i = num.size() - 1; i >= 0; --i) {

		// caso coefficiente
		if (num[i].size() == 1 and num[i][0].degree == 0) continue;

		for (int j = den.size() - 1; j >= 0; --j) {
			if (i >= num.size() or j >= den.size()) continue;

			// caso coefficiente
			if (den[j].size() == 1 and den[j][0].degree == 0) continue;

			// caso con polinomi uguali
			if (num[i] == den[j]) {
				num.erase(num.begin() + i);
				den.erase(den.begin() + j);
				continue;
			}

			// caso con polinomi opposti
			for (int k = 0; k < den[j].size(); ++k) den[j][k].coefficient *= -1;
			if (num[i] == den[j]) {
				num.erase(num.begin() + i);
				den.erase(den.begin() + j);
				sign = -1;
				continue;
			}
			else for (int k = 0; k < den[j].size(); ++k) den[j][k].coefficient *= -1;

			// caso di potenze
			if (num[i].size() == 1 and den[j].size() == 1) {
				int grade_difference = fabs(num[i][0].degree - den[j][0].degree);
				if (num[i][0].degree > den[j][0].degree) {
					num[i][0].degree = grade_difference;
					den[j][0].degree = 0;
				}
				else {
					num[i][0].degree = 0;
					den[j][0].degree = grade_difference;
				}
			}
		}
	}

	// ricerca coefficenti
	int FindN{ -1 }, FindD{ -1 };
	for (int i = 0; i < num.size(); ++i)
		if (num[i].size() == 1) {
			ncoeff = num[i][0].coefficient * sign;
			if (num[i][0].degree == 0 and
				den.size() != 1 and
				den[0].size() != 1)
				num.erase(num.begin() + i);
			else FindN = i;
			break;
		}
	for (int i = 0; i < den.size(); ++i)
		if (den[i].size() == 1) {
			dcoeff = den[i][0].coefficient;
			if (den[i][0].degree == 0 and 
				den.size() != 1 and 
				den[0].size() != 1)
				den.erase(den.begin() + i);
			else FindD = i;
			break;
		}

	// semplificazione coefficienti
	int GCD{ Gcd(fabs(ncoeff), fabs(dcoeff)) };
	ncoeff /= GCD;
	dcoeff /= GCD;
	if (FindN >= 0) num[FindN][0].coefficient = 1;
	if (FindD >= 0) den[FindD][0].coefficient = 1;
	if (num.size() > 0) for (int i = 0; i < num[0].size(); ++i)
		num[0][i].coefficient *= sign;
	else if (den.size() > 0) for (int i = 0; i < den[0].size(); ++i)
		den[0][i].coefficient *= sign;
	else ncoeff *= sign;

	// compressione polinomi
	num.close();
	den.close();
}

static int Determinant(tensor<tensor<int>> mx)
{
	int det{};
	int s = mx.size();

	// casi speciali
	if (s == 1) return mx[0][0];
	if (s == 2) return mx[0][0] * mx[1][1] - mx[0][1] * mx[1][0];

	// caso generale
	for (int i = 0; i < s; ++i) {

		tensor<tensor<int>> MX;
		for (int a = 0; a < s - 1; ++a) MX.push_back({});
		for (int I = 0; I < s - 1; ++I) for (int J = 0; J < s; ++J)
		{
			if (i == J) continue;
			MX[I].push_back(mx[I + 1][J]);
		}
		
		det += intpow(-1, i) * mx[0][i] * Determinant(MX);
	}
	return det;
}

static void Approximator
(tensor<REAL_MONOMIAL>& equation, long double& root)
{

	// calcolo derivata
	auto derivative{ equation };
	for (int j = 0; j < derivative.size(); ++j) {
		derivative[j].coefficient *= derivative[j].degree;
		derivative[j].degree--;
	}
	derivative.pop_back();

	// calcolo radice
	int size = equation.size();
	const double TOL = 0.000001;
	for (int i = 0; i < 100; ++i) {
		long double fx{}, dfx{};

		// calcolo parametri
		for (int j = 0; j < equation.size(); ++j)
			fx += equation[j].coefficient *
			pow(root, equation[j].degree);
		for (int j = 0; j < derivative.size(); ++j)
			dfx += derivative[j].coefficient *
			pow(root, derivative[j].degree);

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
			root * equation[i - 1].coefficient
			+ equation[i].coefficient;
		equation[i].degree--;
	}
	equation[0].degree--;
	equation.pop_back();
}

static tensor<long double> ExistenceConditions
(tensor<REAL_MONOMIAL> equation)
{

	// casi illegali
	if (equation.size() == 0) return {};
	if (equation[0].degree < 0) return {};

	if (equation.size() == 1) {
		if (equation[0].degree == 0) return {};
		return { 0 };
	}

	// completamento dei termini
	equation.sort();
	for (int i = equation.size() - 1; i > 0; --i) {
		int limit = equation[i - 1].degree - equation[i].degree;
		for (int j = 1; j < limit; ++j)
			equation.insert
			(equation.begin() + i, { equation[i - 1].degree - j, 0 });
	}

	tensor<long double> answer;
	long double A, B, C;
	long double delta;
	while (true) switch (equation.size()) {

		// caso coefficiente
	case 1: return answer;

		// caso di primo grado
	case 2:
		answer.push_back((long double)
			-equation[1].coefficient /
			+equation[0].coefficient
		);
		return answer;

		// caso di secondo grado
	case 3:
		A = equation[0].coefficient;
		B = equation[1].coefficient;
		C = equation[2].coefficient;

		delta = sqrt(B * B - 4 * A * C);
		answer.push_back((-B + delta) / (2 * A));
		answer.push_back((-B - delta) / (2 * A));
		return answer;

		// metodo di newton-raphson
	default:

		long double root{};
		Approximator(equation, root);
		answer.push_back(root);
	}
}

template<typename TN, typename TD> static void PrintFraction
(
	int NC, int DC, int& LINE, bool WritePlus,
	tensor<tensor<TN>> numerator,
	tensor<tensor<TD>> denominator
)
{

	// aggiunta di spazio
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto start{ csbi.dwCursorPosition };
	for (int i = 0; i < 10; ++i) cout << '\n';
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if (csbi.dwCursorPosition.Y > start.Y)
		start.Y -= 10 - csbi.dwCursorPosition.Y + start.Y;
	SetConsoleCursorPosition(hConsole, start);

	// calcolo numeratore
	double root{};
	int I{ 1 }, Root;
	bool is_minus{ false };
	wstring den_, num_;
	if (numerator.size() == 1) if (numerator[0].size() == 1)
		if (numerator[0][0].degree == 0)
			root = numerator[0][0].coefficient;

	// traduzione numeratore
	tensor<tensor<MONOMIAL>> Numerator{};
	for (auto d : numerator) {
		tensor<MONOMIAL> TEMP;
		for (auto t : d) {
			MONOMIAL TEMP_;
			TEMP_.coefficient = t.coefficient;
			TEMP_.degree = t.degree;
			TEMP.push_back(TEMP_);
		}
		Numerator.push_back(TEMP);
	}

	// calcolo coefficienti
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
			is_minus = true;
		}
		else if (DC < 0) {
			DC = -DC;
			is_minus = true;
		}

		num_ = to_wstring(NC * Root);
	}

	// calcolo numeratore
	else {
		num_ = Numerator.str();
		if (numerator.size() == 1 and NC == 1 and num_.size() >= 2)
		{
			num_.erase(num_.size() - 1);
			num_.erase(0, 1);
		}
		if (num_ == L"0") num_ = L"";
		if (NC != 1) num_ = to_wstring(NC) + num_;
		if (num_ == L"") num_ = L"1";
	}

	// calcolo denominatore
	den_ = L"";
	auto tempden{ denominator.str() };
	if (tempden != L"1") den_ = tempden;
	if (denominator.size() == 1 and DC == 1 and den_.size() >= 2)
	{
		den_.erase(den_.size() - 1);
		den_.erase(0, 1);
	}
	if (DC != 1) den_ = to_wstring(DC) + den_;

	// calcolo dati
	int sizemax = max(num_.size(), den_.size());
	int spacing = num_.size() - den_.size();
	spacing = fabs(spacing) / 2;
	if (num_.size() > den_.size()) den_ = wstring(spacing, ' ') + den_;
	else num_ = wstring(spacing, ' ') + num_;

	// caso di fine riga
	if (LINE + spacing + WritePlus * 2 > csbi.dwSize.X) {
		LINE = 0;
		start.Y += 4;
		SetConsoleCursorPosition(hConsole, start);
	}

	// output segno
	if (WritePlus or is_minus) {
		if (WritePlus) start.X++;
		start.Y++;
		SetConsoleCursorPosition(hConsole, start);
		is_minus ? cout << '-' : cout << '+';
		start.X += 2;
		LINE += 2;
		start.Y--;
	}

	// output frazione
	SetConsoleCursorPosition(hConsole, start);
	wcout << num_;
	start.Y++;
	SetConsoleCursorPosition(hConsole, start);
	wcout << wstring(sizemax, '-');
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
#pragma region Programs

static void CodeToNumber(switchcase& argc)
{

	// scelta
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	wstring to_evaluate, ToEvaluate, message;
	bool ShowErrors{ true }, NecessaryBoundary{ true };
	SetConsoleTextAttribute(hConsole, 14);
	cout << "il PROGRAMMA traduce una stringa di codice\n\n";
	SetConsoleTextAttribute(hConsole, 12);

	cout << "il codice non deve avere errori o saranno segnalati\n";
	cout << "il codice deve essere compreso tra <>\n";
	cout << "se sono presenti piu' caratteri '<', '>',\n";
	cout << "verranno considerati solo quelli che compaiono prima\n";
	cout << "unici caratteri non numerici ammessi: '(', ')', '+', '.' \n\n";

	SetConsoleTextAttribute(hConsole, 9);
	cout << "si indichino le cifre incognite con caratteri '_'\n";
	cout << "aggiungendo '$' come primo carattere\n";
	cout << "oppure '\\' o '/' senza <> non vengono mostrati gli errori\n\n";
	SetConsoleTextAttribute(hConsole, 15);

	while (true) {
		do {
			message = L"";

			// input e controllo
			cout << "inserire una stringa (f = fine input)\n";
			cout << "per fermare il calcolo premere s\\S\n";
			getline(wcin, ToEvaluate);
			argc = ConvertWStringToEnum(ToEvaluate);
			ReassigneEnum(argc);
			if (argc != NotAssigned) {
				system("cls");
				auto title{ ToEvaluate.c_str() };
				SetConsoleTitle(title);
				return;
			}
			if (ToEvaluate == L".") {
				argc = Random;
				return;
			}

			// ammissione errori
			if (!ToEvaluate.empty()) {
				NecessaryBoundary = ToEvaluate.at(0) != '\\' and ToEvaluate.at(0) != '/';
				ShowErrors = ToEvaluate.at(0) != '$' and NecessaryBoundary;
				if (!NecessaryBoundary) ToEvaluate.erase(0, 1);
			}

			// individuazione degli errori
			to_evaluate = ToEvaluate;
			if (NecessaryBoundary) message = UpdateString(ToEvaluate);
			if (message.empty()) message = SyntaxValidator(ToEvaluate);

			// output errori
			if (message.size() > 1) {
				lock_guard<mutex> lock(CoutMutex);
				SetConsoleTextAttribute(hConsole, 4);
				wcout << "ERR[404]: " << message << '\n';
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
			if (ToEvaluate.at(space) == ' ' or ToEvaluate.at(space) == '\t')
				ToEvaluate.erase(space, 1);

		GlobalInterr = false;
		computing = true;
		interrupted = false;

		ObjectGetCh.enqueue(' ');
		SetConsoleCursorInfo(hConsole, &cursorInfo);

		// dichiarazione dei thread
		thread ComputationThread([=]() {
			LongComputation(to_evaluate, message, ShowErrors, NecessaryBoundary);
			});
		thread InputThread(UserInputThread);

		unique_lock<mutex> lock(CoutMutex);
		Cv.wait(lock, [] { return !computing; });

		if (ComputationThread.joinable()) ComputationThread.join();
		interrupted = true;
		if (InputThread.joinable()) InputThread.join();

		// se il calcolo viene interrotto
		if (GlobalInterr) {
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
			SetConsoleTextAttribute(hConsole, 64);
			cout << "CALCOLO INTERROTTO!!!";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "\n\n";
		}
		SetConsoleCursorInfo(hConsole, &cursor);
	}
}

static void Repeater(
	switchcase& argc,
	string message,
	NumberData CPU(long long input)
)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	wstring n_{ to_wstring(GlobalMax) }, Input;
	long long input;
	NumberData result;
	SetConsoleTextAttribute(hConsole, 14);
	cout << message << "\n\n";
	SetConsoleTextAttribute(hConsole, 15);
	do {

		// input e controllo
		SetConsoleTextAttribute(hConsole, 14);
		wstring txt{
			L"inserire un numero tra 2 e " +
			n_ + L" (1 = fine input)\n"
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
				auto title{ Input.c_str() };
				SetConsoleTitle(title);
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
		if (input != 1) {
			result = CPU(input);
			result.printf();
		}

	} while (input != 1);

	argc = NotAssigned;
	return;
}
static void Loop(
	switchcase& argc,
	string message,
	NumberData CPU(long long input),
	bool select
)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	wstring n_{ to_wstring(GlobalMax) }, Input, txt;
	NumberDataTensor data;
	long long input, lower_bound, upper_bound, datalenght;
	bool do_return;

	// input estremi
	cout << "debug::\n\n";
	SetConsoleTextAttribute(hConsole, 14);
	cout << message << '\n';
	SetDebug
	(message, argc, do_return, lower_bound, upper_bound, datalenght);
	if (do_return) return;

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
			cout << "\ninserire la stringa\n";
			instr = GetLine(true, 20);
			if (instr == L".") {
				argc = Random;
				return;
			}

			// rimozione spazi
			for (int i = instr.size() - 1; i >= 0; --i)
				if (instr.at(i) == ' ' or instr.at(i) == '\t') instr.erase(i, 1);

			// prima suddivisione
			wstring sum_instr{ instr }, prod_instr{ instr };
			bool do_divide_sum{ true }, do_divide_prod{ true };
			int posP{}, posS{};
			if (instr.empty()) {
				items = { 0, 0, 0, 0 };
				break;
			}
			posS = instr.find('$');
			posP = instr.find('#');
			if (posS == wstring::npos) sum_instr = L"";
			if (posP == wstring::npos) prod_instr = L"";
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
			if (!sum_instr.empty()) pos_s = sum_instr.find('/');
			if (!prod_instr.empty()) pos_p = prod_instr.find('/');
			if (pos_s == wstring::npos or pos_p == wstring::npos) continue;

			wstring np, dp, ns, ds;
			bool do_continue{ false };
			if (!prod_instr.empty()) {
				np = prod_instr;
				dp = prod_instr;
				np.erase(pos_p);
				dp.erase(0, pos_p + 1);
				for (char c : np) if (!isdigit(c)) do_continue = true;
				for (char c : dp) if (!isdigit(c)) do_continue = true;
				if (do_continue) continue;
				items.digitProductRatioNum = stoi(np);
				items.digitProductRatioDen = stoi(dp);
				exit = true;
			}

			if (!sum_instr.empty()) {
				ns = sum_instr;
				ds = sum_instr;
				ns.erase(pos_s);
				ds.erase(0, pos_s + 1);
				for (char c : ns) if (!isdigit(c)) do_continue = true;
				for (char c : ds) if (!isdigit(c)) do_continue = true;
				if (do_continue) continue;
				items.digitSumRatioNum = stoi(ns);
				items.digitSumRatioDen = stoi(ds);
				exit = true;
			}
			// //

			if (!exit) cout << '\a';
		} while (!exit);
	}

	// calcolo e parallelizzazione
	system("cls");
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const int Barwidth{ csbi.dwSize.X - 11 };
	SetConsoleCursorInfo(hConsole, &cursorInfo);
	if (datalenght >= 1000) {
		int iter{};
		atomic<long double> Progress{};
		auto begin{ steady_clock::now() };
		parallel_for(long long(lower_bound), upper_bound, 
			[&](long long set) {

				auto data_element{ CPU(set) };
				mtx.lock();
				data.push_back(data_element);
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
					stringstream stream;
					stream << fixed << setprecision(1) << time_seconds;
					cout << "\ntempo rimanente: " << stream.str() << " [secondi] ";
				}
				iter++;
				mtx.unlock();

			}
		);
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		cout << string(Barwidth + 11, '\\') << '\n';

		// multithreading
		thread t1([&data]() {
			data.HeapSort();
			lock_guard<mutex> lock(mtx);
			is_done = true;
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
		cout << "\ntempo di calcolo = ";
		cout << duration_cast <milliseconds> (end - begin).count();
		cout << "[ms]\n\n";
	}

	// caso con intervallo di dimensioni minori
	else {
		SetConsoleCursorInfo(hConsole, &cursor);
		auto begin{ steady_clock::now() };
		for (long long set = lower_bound; set < upper_bound; ++set)
			data.push_back({ CPU(set) });
		data.printf();
		auto end{ steady_clock::now() };
		cout << "\ntempo di calcolo = ";
		cout << duration_cast <milliseconds> (end - begin).count();
		cout << "[ms]\n\n\n";
	}

	// termine
	char null;
	PRINTN = true;
	Beep(750, 100);
	Beep(650, 75);
	Beep(550, 50);
	cout << "premi un tasto per continuare\t\t";
	do null = _getch();
	while ((null > 64 and null < 91) or null < 32);
	argc = null == '.' ? Random : NotAssigned;
	return;
}

static tensor<tensor<MONOMIAL>> DecompPolynomial
(switchcase& argc, wstring polynomial)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));
	SetConsoleTextAttribute(hConsole, 14);

	// variabili
	tensor<MONOMIAL> polydata, pdata;
	wstring pol, POL;
	bool empty{ true }, Xout{ false };
	bool input = polynomial.empty();
	tensor<tensor<MONOMIAL>> HT;

	// istruzioni
	if (input)
	{
		cout << "il PROGRAMMA scompone i polinomi\n\n";
		SetConsoleTextAttribute(hConsole, 12);
		cout << "per attivare gli esponenti in forma di apice, \n";
		cout << "scrivere $%ralpha, $%d_alpha o $%%alfa\n";
		cout << "per disattivare gli esponenti sottoforma di apice: \n";
		cout << "scrivere $boolalpha, $bool_alpha o $b_alfa\n\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	do {
		if (input)
		{
			empty = true;
			Xout = false;
			bool No{ false };
			do {
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				bool wrong{ true };

				// input
				SetConsoleTextAttribute(hConsole, 15);
				cout << "inserisci un polinomio in una variabile";
				cout << " (0 = fine input)\n";
				do {
					polynomial = GetLine(true, csbi.dwSize.X);
					cout << '\n';
				} while (polynomial.empty());
				if (polynomial == L".") {
					argc = Random;
					return {};
				}
				argc = ConvertWStringToEnum(polynomial);
				ReassigneEnum(argc);
				if (argc != NotAssigned) {
					system("cls");
					auto title{ polynomial.c_str() };
					SetConsoleTitle(title);
					return {};
				}

				// esponenti con gli apici
				if (
					polynomial == L"$%ralpha" or
					polynomial == L"$%d_alpha" or
					polynomial == L"$%%alfa"
					)
				{
					BOOLALPHA = true;
					wrong = false;
				}
				if (
					polynomial == L"$boolalpha" or
					polynomial == L"$bool_alpha" or
					polynomial == L"$b_alfa"
					)
				{
					BOOLALPHA = false;
					wrong = false;
				}
				if (!wrong) wcout << polynomial << '\n';

				// rimozione spazi
				for (int i = polynomial.size() - 1; i >= 0; --i)
					if (polynomial.at(i) == ' ' or polynomial.at(i) == '\t')
						polynomial.erase(i, 1);

				// controllo
				No = !Syntax(polynomial);
				if (No and wrong) {
					SetConsoleTextAttribute(hConsole, 15);
					wcout << "quello non è un polinomio in una variabile\n\a";
				}

			} while (No);
			if (polynomial == L"0") break;
		}

		// somma
		polydata = GetMonomials(polynomial);
		pdata = PolynomialSum(polydata);

		// risultato della somma
		polynomial = pdata.str();
		if (BOOLALPHA) ElabExponents(polynomial);
		if (polydata.size() != pdata.size() and input) {
			SetConsoleTextAttribute(hConsole, 2);
			if (polynomial.empty()) polynomial = L"0";
			wcout << "qualche calcolo dopo: " << polynomial << '\n';
			empty = false;
		}

		// raccoglimento totale
		polydata = pdata;
		tensor<tensor<MONOMIAL>> BackT;
		tensor<tensor<MONOMIAL>> Back_T;
		HT = Total(polydata);
		polynomial = HT.str();
		if (HT.size() != 1 and input) {
			SetConsoleTextAttribute(hConsole, 12);
			wcout << "raccoglimento totale: " << polynomial << '\n';
			empty = false;
		}
		do {

			// raccoglimento parziale
			polydata = HT[HT.size() - 1];
			HT.pop_back();
			BackT = Partial(polydata);
			for (auto a : BackT) HT.push_back(a);
			pol = HT.str();
			if (pol != polynomial and input) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 4);
				wcout << "raccoglimento parziale: " << polynomial << '\n';
				empty = false;
			}

			// potenza di binomio
			HT.close();
			Back_T = HT;
			HT = {};
			for (auto a : Back_T) {
				BackT = Binomial(a);
				for (auto b : BackT) HT.push_back(b);
			}
			HT.close();
			pol = HT.str();
			if (pol != polynomial and !Xout and input) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 3);
				wcout << "potenza di binomio scomposta: ";
				wcout << polynomial << '\n';
				empty = false;
			}

			// trinomio speciale
			Back_T = HT;
			HT = {};
			for (auto a : Back_T) {
				BackT = Trinomial(a);
				for (auto b : BackT) HT.push_back(b);
			}
			HT.close();
			pol = HT.str();
			if (pol != polynomial and !Xout and input) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "trinomio speciale scomposto: ";
				wcout << polynomial << '\n';
				empty = false;
			}

			// differenza di quadrati
			Back_T = HT;
			HT = {};
			int extend{ 1 };
			for (auto a : Back_T) {
				if (a[0].degree == -1) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = SquareDifference(a);
				for (auto b : BackT) {
					if (extend > 1) HT.push_back({ {-1, extend} });
					HT.push_back(b);
				}
				extend = 1;
			}
			HT.close();
			pol = HT.str();

			// somma per differenza
			if (pol != polynomial and !Xout and input) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 5);
				wcout << "differenza di quadrati scomposta: ";
				wcout << polynomial << '\n';
				empty = false;
			}

			// scomposizione con ruffini
			POL = HT.str();
			Back_T = HT;
			HT = {};
			extend = 1;
			for (auto a : Back_T) {
				if (a[0].degree == -1) {
					extend = a[0].coefficient;
					continue;
				}
				BackT = Ruffini(a);
				if (a.size() > 0 and BackT.size() == 0) {
					Xout = true;
					break;
				}
				for (auto b : BackT) {
					if (extend > 1) HT.push_back({ {-1, extend} });
					HT.push_back(b);
				}
			}

			// ruffini
			HT.close();
			pol = HT.str();
			if (pol != polynomial and !Xout and input) {
				polynomial = pol;
				SetConsoleTextAttribute(hConsole, 6);
				wcout << "applicazione della regola di ruffini: ";
				wcout << polynomial << '\n';
				empty = false;
			}
		} while (pol != POL);

		// completamento del quadrato
		Back_T = HT;
		HT = {};
		for (auto a : Back_T) {
			BackT = CompleteTheSquare(a);
			for (auto b : BackT) HT.push_back(b);
		}
		HT.close();
		pol = HT.str();
		if (pol != polynomial and !Xout and input) {
			polynomial = pol;
			SetConsoleTextAttribute(hConsole, 79);
			wcout << "completamento del quadrato: " << polynomial;
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
			empty = false;
		}

		// quadrato del trinomio
		Back_T = HT;
		HT = {};
		for (auto a : Back_T) {
			BackT = TrinomialSquare(a);
			for (auto b : BackT) HT.push_back(b);
		}
		HT.close();
		pol = HT.str();
		if (pol != polynomial and !Xout and input) {
			polynomial = pol;
			SetConsoleTextAttribute(hConsole, 79);
			wcout << "quadrato di trinomio scomposto: " << polynomial;
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
			empty = false;
		}

		// caso vuoto
		if (empty and !Xout and input) {
			SetConsoleTextAttribute(hConsole, 15);
			wcout << "il polinomio non è scomponibile";
			wcout << " con i metodi standard\n";
		}

		// caso impossibile
		if (Xout and input) {
			SetConsoleTextAttribute(hConsole, 64);
			cout << "X_OUT_OF_RANGE";
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
		}
	} while (input);

	argc = NotAssigned;
	return HT;
}
static void DecompFraction(switchcase& argc)
{
	setlocale(LC_ALL, "");
	SetConsoleOutputCP(CP_UTF8);
	wcout.imbue(locale(""));

	// istruzioni
	SetConsoleTextAttribute(hConsole, 14);
	cout << "il PROGRAMMA scompone le frazioni algebriche\n\n";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "per attivare gli esponenti in forma di apice, \n";
	cout << "scrivere $%ralpha, $%d_alpha o $%%alfa\n";
	cout << "per disattivare gli esponenti sottoforma di apice: \n";
	cout << "scrivere $boolalpha, $bool_alpha o $b_alfa\n";
	SetConsoleTextAttribute(hConsole, 15);

	while (true)
	{
		// input della frazione algebrica
		wstring numerator, denominator;
		bool No1{ false }, No2{ false }, No3{ false }, skip{ false };
		do {

			// input
			SetConsoleTextAttribute(hConsole, 15);
			bool wrong{ true };
			cout << "\ninserisci una frazione algebrica";
			cout << " (0 = fine input)\n\n";
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
				auto title{ numerator.c_str() };
				SetConsoleTitle(title);
				return;
			}

			// esponenti con gli apici
			if (
				numerator == L"$%ralpha" or
				numerator == L"$%d_alpha" or
				numerator == L"$%%alfa"
				)
			{
				BOOLALPHA = true;
				wrong = false;
			}
			if (
				numerator == L"$boolalpha" or
				numerator == L"$bool_alpha" or
				numerator == L"$b_alfa"
				)
			{
				BOOLALPHA = false;
				wrong = false;
			}
			if (!wrong) wcout << numerator << '\n';

			// controllo
			No1 = !Syntax(numerator);
			No2 = !Syntax(denominator) or denominator == L"0";
			No3 = denominator.at(0) == '+' or denominator.at(0) == '-' ?
				!Syntax(numerator + denominator) :
				!Syntax(numerator + L'+' + denominator);

			if (numerator == L"0") break;
			if ((No1 or No2 or No3) and wrong) {
				SetConsoleTextAttribute(hConsole, 4);
				wcout << "quella non è una frazione algebrica\n\a";
				SetConsoleTextAttribute(hConsole, 15);
			}

			if (!No1 and !No2 and !No3)
				if (PolynomialSum(GetMonomials(denominator)).size() == 0)
				{
					No2 = true;
					SetConsoleTextAttribute(hConsole, 4);
					wcout << "il denominatore non può essere nullo\n\a";
					SetConsoleTextAttribute(hConsole, 15);
				}
		} while (No1 or No2 or No3);
		if (numerator == L"0") break;

		// semplificazione fattori e backup
		switchcase use;
		auto NScomp{ DecompPolynomial(use, numerator) };
		auto DScomp{ DecompPolynomial(use, denominator) };
		for (int i = 0; i < DScomp.size(); ++i) DScomp[i].sort();
		for (int i = 0; i < NScomp.size(); ++i) NScomp[i].sort();
		auto DenBackup{ DScomp };
		auto NumBackup{ NScomp };
		DScomp.close();
		NScomp.close();
		int NCOEFF{ 1 }, DCOEFF{ 1 };
		Simplify(NScomp, DScomp, NCOEFF, DCOEFF);
		if (DScomp.size() <= 1) skip = true;
		if (!skip) for (auto a : DScomp) for (auto b : a)
			if (a.size() != 1 and b.degree > 1) skip = true;

		// calcolo denominatori
		bool is_modifier{ false };
		tensor<tensor<tensor<MONOMIAL>>> denominators;
		tensor<tensor<MONOMIAL>> complementaries;
		int index{};
		if (!skip) for (int i = 0; i < DScomp.size(); ++i) {
			if (DScomp[i][0].degree == -1) {
				is_modifier = true;
				continue;
			}

			// caso con le potenze
			if (is_modifier)
				for (int j = DScomp[i - 1][0].coefficient; j > 0; --j)
				{
					denominators.push_back({});
					if (j > 1) denominators[index].push_back({ {-1, j} });
					denominators[index].push_back(DScomp[i]);
					index++;
					complementaries.push_back(
						Complementary(DScomp, DScomp[i], j)
					);
				}
			else if (DScomp[i].size() == 1)

				// caso con le potenze della variabile
				for (int j = DScomp[i][0].degree; j > 0; --j)
				{
					denominators.push_back({});
					denominators[index].push_back({ {j, 1} });
					index++;
					auto NewScomp{ DScomp };
					NewScomp.erase(NewScomp.begin() + i);
					NewScomp.insert(NewScomp.begin() + i, { {1, 1} });
					NewScomp.insert(NewScomp.begin() + i, {
						{-1, DScomp[i][0].degree} }
						);
					complementaries.push_back(
						Complementary(NewScomp, NewScomp[i + 1], j)
					);
				}

			// caso senza potenze
			else {
				denominators.push_back({});
				denominators[index].push_back(DScomp[i]);
				index++;
				complementaries.push_back(
					Complementary(DScomp, DScomp[i], 1)
				);
			}
			is_modifier = false;
		}
		if (!skip) for (int i = 0; i < complementaries.size(); ++i)
			complementaries[i].fill(complementaries.size());

		// inizializzazione matrice
		tensor<tensor<int>> Matrix;
		if (!skip) for (int i = 0; i < complementaries.size(); ++i)
			Matrix.push_back({});
		if (!skip) for (int i = 0; i < complementaries.size(); ++i)
			for (int j = 0; j < complementaries.size(); ++j)
				Matrix[i].push_back(complementaries[i][j].coefficient);

		// calcolo determinanti
		tensor<int> results;
		tensor<double> roots;
		int Det;
		tensor<MONOMIAL> Quotient;
		tensor<MONOMIAL> Rest;
		if (!skip) {

			// divisione polinomi
			PolynomialDivide(
				PolynomialMultiply(NScomp),
				PolynomialMultiply(DScomp),
				Quotient,
				Rest
			);
			Rest.fill(complementaries.size() - 1);
			Rest.sort();

			for (auto R : Rest) results.push_back(R.coefficient);
			Det = Determinant(Matrix);
		}
		if (!skip) for (int i = 0; i < results.size(); ++i) {
			tensor<tensor<int>> MX{ Matrix };
			MX[i] = results;
			roots.push_back((double)Determinant(MX) / Det);
		}

		// eliminazione degli zeri
		for (int i = denominators.size() - 1; i >= 0; --i) 
			if (roots[i] == 0) {
				denominators.erase(denominators.begin() + i);
				roots.erase(roots.begin() + i);
			}
		if (roots.size() == 0) skip = true;

		// calcolo condizioni di esistenza
		SetConsoleTextAttribute(hConsole, 11);
		wcout << L"C.E.: ";
		SetConsoleTextAttribute(hConsole, 10);
		tensor<long double> C_E_;
		bool has_been_printed{ false };
		int Idx{};
		tensor<tensor<REAL_MONOMIAL>> DBCKP;
		for (auto D : DenBackup) {
			DBCKP.push_back({});
			for (auto M : D) DBCKP[Idx].push_back
			(
				REAL_MONOMIAL{
					(long double)M.degree,
					(long double)M.coefficient
				}
			);
			Idx++;
		}

		// output condizioni di esistenza
		COORD cursorPos;
		for (auto d : DBCKP) {
			auto CEtemp{ ExistenceConditions(d) };
			for (auto i : CEtemp) if (!isnan(i)) C_E_.push_back(i);
		}
		for (auto i : C_E_) {
			wcout << charVariable << L" != ";

			stringstream stream;
			stream << fixed << setprecision(5) << i;
			string I = stream.str();
			while (
				(I.at(I.size() - 1) == '0' or
					I.at(I.size() - 1) == '.') and
				I.size() > 1
				) I.erase(I.size() - 1);

			cout << I << "; ";
			has_been_printed = true;
		}
		if (!has_been_printed) wcout << "\r      \r";
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		cursorPos = csbi.dwCursorPosition;
		if (!has_been_printed) {
			cursorPos.X = 0;
			cursorPos.Y--;
			SetConsoleCursorPosition(hConsole, cursorPos);
		}
		else cout << '\n';

		// calcolo casi
		bool print{
			(
				// il denominatore è cambiato e
				DenBackup != DScomp
				and

				// non è un coefficiente oppure è 0 o 1
				(
					DenBackup.size() > 1
					or
					DenBackup[0].size() > 1
					or
					DenBackup[0][0].degree > 0
					or
					DenBackup[0][0].coefficient == 0
					or
					DenBackup[0][0].coefficient == 1
				)
			)
			// oppure
			or
			(
				// il numeratore è cambiato ma
				NumBackup != NScomp
				and

				// non è un coefficiente
				(
					NumBackup.size() > 1
					or
					NumBackup[0].size() > 1
					or
					NumBackup[0][0].degree > 0
				)
			)
			or
			(
				// frazione semplificata

				NScomp == tensor<tensor<MONOMIAL>>({
					tensor<MONOMIAL>({
						MONOMIAL(0, 1)
					})
				})
				and
				NScomp == DScomp
				and
				NCOEFF != NumBackup[0][0].coefficient
				and
				DCOEFF != DenBackup[0][0].coefficient
			)
			or
			(
				// denominatore assente

				DScomp == tensor<tensor<MONOMIAL>>({
					tensor<MONOMIAL>({
						MONOMIAL(0, 1)
					})
				})
				and
				DenBackup == DScomp
				and
				DCOEFF == 1
			)
		};
		
		// output frazioni
		if (!skip or print) {
			SetConsoleTextAttribute(hConsole, 10);
			wcout << L"\nla scomposizione è: ";
			SetConsoleTextAttribute(hConsole, 12);
		}
		bool ShowPlus{ false };
		int lines{};

		// caso generale, frazione scomposta
		if (!skip) {
			cout << "\n\n";
			for (int i = 0; i < denominators.size(); ++i) {
				PrintFraction<REAL_MONOMIAL, MONOMIAL>(
					NCOEFF,
					DCOEFF,
					lines,
					ShowPlus,
					{ { { 0, roots[i] } } },
					denominators[i]
				);
				ShowPlus = true;
			}
			cout << "\n\n";
		}

		else if (print) {

			// caso di frazione semplificata ma non scomposta
			bool new_print{ false };
			if (DScomp.size() > 0) {
				if (DScomp.size() > 1 or DScomp[0].size() > 1
					or DScomp[0][0].degree > 0)
				{
					GetConsoleScreenBufferInfo(hConsole, &csbi);
					csbi.dwCursorPosition.Y--;
					SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
					PrintFraction<MONOMIAL, MONOMIAL>(
						NCOEFF,
						DCOEFF,
						lines,
						false,
						NScomp,
						DScomp
					);
					cout << "\n\n";
				}
				else new_print = true;
			}
			else new_print = true;

			// caso di denominatore coefficiente
			if (DCOEFF != 1 and NScomp.size() != 0 and new_print) {
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				csbi.dwCursorPosition.Y--;
				SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
				PrintFraction<MONOMIAL, MONOMIAL>(
					NCOEFF,
					DCOEFF,
					lines,
					false,
					NScomp,
					{ { MONOMIAL{ 0, 1 } } }
				);
				cout << "\n\n";
			}

			// caso di frazione normale
			else if (DCOEFF != 1 and NScomp.size() == 0 and new_print) {
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				csbi.dwCursorPosition.Y--;
				SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
				PrintFraction<MONOMIAL, MONOMIAL>(
					NCOEFF,
					DCOEFF,
					lines,
					false,
					{ { MONOMIAL{ 0, 1 } } },
					{ { MONOMIAL{ 0, 1 } } }
				);
				cout << "\n\n";
			}

			// caso di unità
			else if (NScomp.size() == 0) cout << ' ' << NCOEFF;

			// caso costante o fattore
			else if (NScomp.size() == 1 and new_print) {
				auto output = NScomp[0].str();
				if (BOOLALPHA) ElabExponents(output);
				if (output == L"1") {
					wcout << ' ' << NCOEFF << "\n\n";
					continue;
				}
				if (NScomp[0].size() > 1 and NCOEFF != 1)
					output = L'(' + output + L')';
				if (NCOEFF != 1) output = to_wstring(NCOEFF) + output;
				wcout << ' ' << output;
			}

			// caso polinomio
			else if (new_print) wcout << ' ' << NScomp.str();
		}

		// caso non scomponibile
		else {

			// messaggio di errore
			SetConsoleTextAttribute(hConsole, 64);
			cout << "NON E' POSSIBILE SCOMPORRE!!\a";
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
			continue;
		}

		// reset cursore
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		auto cursorP{ csbi.dwCursorPosition };
		cursorP.X = lines;
		cursorP.Y--;
		SetConsoleCursorPosition(hConsole, cursorP);

		// output polinomio di resto
		if (!skip) for (auto a : Quotient) {
			tensor T = { {a} };
			auto pol{ T.str() };
			bool is_minus{ false };
			if (pol.at(0) == '-') {
				pol.erase(0, 1);
				is_minus = true;
			}
			if (pol.size() >= 2) {
				pol.erase(pol.size() - 1);
				pol.erase(0, 1);
			}
			if (pol.at(0) == '-') {
				pol.erase(0, 1);
				is_minus = true;
			}
			else if (pol.at(0) == '+') pol.erase(0, 1);
			is_minus ? cout << "- " : cout << "+ ";
			wcout << pol << ' ';
		}
		cout << "\n\n";

	}

	argc = NotAssigned;
	return;
}

#pragma endregion

#pragma endregion
/*
impegni:

	cambiare le dichiarazioni delle funzioni aggiungendo alcuni valori di default
	utilizzare i nuovi operatori
	fare il debug
	cambiare i puntatori in array[11] (non in tensor)
	scrivere le ultime funzioni (sono 3)
	aggiungere le nuove funzioni per i polinomi a due variabili
	aggiungere un paio di costruttori a tensor e utilizzarli
	altro debug

fine impegni (circa)
*/
// fine del codice