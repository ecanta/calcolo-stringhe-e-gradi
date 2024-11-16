#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <vcruntime.h>

#define ret return

#ifndef  __TENSOR__
#define __TENSOR__

#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)
#define FRIEND_BOOL_OPERATOR \
template<typename U, typename = _STD enable_if_t<_STD is_integral_v<U>>> \
friend bool operator

namespace std_tensor
{

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
			if (capacity > new_capacity) ret;
			T* new_data = new T[new_capacity];
			if (data != nullptr) {
				for (size_t i = 0; i < count; ++i) new_data[i] = _STD move(data[i]);
				delete[] data;
			}
			data = new_data;
			capacity = new_capacity;
		}

	public:

		// costruttori e distruttori
		tensor() : data(nullptr), capacity(0), count(0)
		{
			resize(10);
		}
		tensor(const tensor& other) : data(nullptr), capacity(0), count(0)
		{
			resize(other.count + 10);
			count = other.count;
			for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
		}
		tensor(tensor&& other) noexcept :
			data(other.data),
			capacity(other.capacity),
			count(other.count)
		{
			other.data = nullptr;
			other.count = other.capacity = 0;
		}
		tensor(_STD initializer_list<T> init) : tensor()
		{
			for (const T& value : init) push_back(value);
		}
		tensor(size_t size, const T& initial_value)
			: data(nullptr), capacity(0), count(0)
		{
			resize(size + 10);
			count = size;
			_STD fill(data, data + count, initial_value);
		}
		tensor(size_t size) : data(nullptr), capacity(0), count(0)
		{
			resize(size + 10);
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
				resize(other.count + 10);
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
				other.count = other.capacity = 0;
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
			if (index >= count) throw _STD out_of_range("Index out of range!");
			ret data[index];
		}
		inline const T& at(size_t index) const
		{
			if (index >= count) throw _STD out_of_range("Index out of range!");
			ret data[index];
		}
		inline T& last()
		{
			if (count == 0) throw _STD out_of_range("Tensor is empty!");
			ret data[count - 1];
		}
		inline const T& last() const
		{
			if (count == 0) throw _STD out_of_range("Tensor is empty!");
			ret data[count - 1];
		}

		// metodi di taglio
		inline void clear()
		{
			count = 0;
		}
		tensor erase(size_t pos)
		{
			if (pos >= count) throw _STD out_of_range("Index out of range!");
			count = pos;
			ret *this;
		}
		tensor erase(size_t pos, size_t n)
		{
			if (pos >= count) throw _STD out_of_range("Index out of range");
			n = _STD min(n, count - pos);
			for (size_t i = pos; i < count - n; ++i)
				data[i] = _STD move(data[i + n]);
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
			if (count == 0) throw _STD out_of_range("Tensor is empty");
			count--;
		}
		void push_front(const T& value)
		{
			if (count == capacity) resize(capacity * 2);
			for (size_t i = count; i > 0; --i) data[i] = _STD move(data[i - 1]);
			data[0] = value;
			count++;
		}
		void pop_front()
		{
			if (count == 0) throw _STD out_of_range("Tensor is empty");
			for (size_t i = 0; i < count - 1; ++i) data[i] = _STD move(data[i + 1]);
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
			auto temp{ *this };
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
			auto temp{ *this };
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
		_NODISCARD tensor operator+(const T value) const
		{
			auto result{ *this };
			result.push_back(value);
			ret result;
		}
		_NODISCARD tensor operator+(const tensor other) const
		{
			auto result{ *this };
			result += other;
			ret result;
		}
		tensor& operator+=(const tensor other)
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
		FRIEND_BOOL_OPERATOR == (const tensor & t, U n)
		{
			ret t.count == static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR != (const tensor & t, U n)
		{
			ret t.count != static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR < (const tensor& t, U n)
		{
			ret t.count < static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR <= (const tensor & t, U n)
		{
			ret t.count <= static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR > (const tensor& t, U n)
		{
			ret t.count > static_cast<size_t>(n);
		}
		FRIEND_BOOL_OPERATOR >= (const tensor & t, U n)
		{
			ret t.count >= static_cast<size_t>(n);
		}

		// operatori di confronto a sinistra con un intero
		FRIEND_BOOL_OPERATOR == (U n, const tensor & t)
		{
			ret static_cast<size_t>(n) == t.count;
		}
		FRIEND_BOOL_OPERATOR != (U n, const tensor & t)
		{
			ret static_cast<size_t>(n) != t.count;
		}
		FRIEND_BOOL_OPERATOR < (U n, const tensor& t)
		{
			ret static_cast<size_t>(n) < t.count;
		}
		FRIEND_BOOL_OPERATOR <= (U n, const tensor & t)
		{
			ret static_cast<size_t>(n) <= t.count;
		}
		FRIEND_BOOL_OPERATOR > (U n, const tensor& t)
		{
			ret static_cast<size_t>(n) > t.count;
		}
		FRIEND_BOOL_OPERATOR >= (U n, const tensor & t)
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
			  using value_type = T;
			  using reference = T&;
			  using pointer = T*;
			  using difference_type = ptrdiff_t;
			  using iterator_category = _STD forward_iterator_tag;

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
				  if (index < value.index)
					  throw _STD out_of_range("Index out of range");
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
				  ret&data[index];
			  }
			  const T* operator->() const
			  {
				  ret&data[index];
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
			if (it == end()) throw _STD out_of_range("Iterator out of range");
			size_t pos{ it - begin() };
			for (size_t i = pos; i < count - 1; ++i)
				data[i] = _STD move(data[i + 1]);
			count--;
		}
		void erase(iterator first, iterator last)
		{
			if (first == last) ret;
			size_t start{ first - begin() };
			size_t end{ last - begin() };

			if (start >= count or end > count or start > end)
				throw _STD out_of_range("Invalid iterator range");

			size_t distance = end - start;
			for (size_t i = start; i < count - distance; ++i)
				data[i] = _STD move(data[i + distance]);

			count -= distance;
		}
		void insert(iterator pos, const T& value)
		{
			size_t index = pos - begin();
			if (count == capacity) resize(capacity * 2);

			for (size_t i = count; i > index; --i) data[i] = _STD move(data[i - 1]);

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

		virtual _NODISCARD _STD wstring str(int size = Variables.size())
		{
			_STD wostringstream result;
			_STD wstring outp;
			result << _STD fixed;

			// bool
			if constexpr (_STD is_same_v<T, bool>) for (const auto& element : *this)
			{
				result << element ? L"1" : L"0";
				result << L", ";
			}

			// carattere
			else if constexpr (_STD is_same_v<T, wchar_t>) {
				for (const auto& element : *this) result << element;
				result << L", ";
			}

			// numeri decimali
			else if constexpr (_STD is_same_v<T, double>)
				for (const auto& element : *this)
				{
					if (integer(element)) result << _STD setprecision(0);
					result << element << L", ";
					if (integer(element)) result << _STD setprecision(6);
				}

			// dati generici
			else if constexpr (_STD is_integral_v<T>
				or _STD is_same_v<T, _STD wstring>)
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

		tensor_t() {}
		tensor_t(
			tensor<bool> is_prime_param,
			tensor<ptrdiff_t> list_primes_param
		) :
			is_prime(_STD move(is_prime_param)),
			list_primes(_STD move(list_primes_param))
		{}
		tensor_t(const tensor_t& other)
			: is_prime(other.is_prime), list_primes(other.list_primes)
		{}
		tensor_t(tensor_t&& other) noexcept
			: is_prime(_STD move(other.is_prime)),
			list_primes(_STD move(other.list_primes))
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
#endif