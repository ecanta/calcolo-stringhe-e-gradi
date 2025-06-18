#pragma once

// definizioni di macro
#define ret return
#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)

// inclusioni
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <vcruntime.h>
using namespace std;

#ifndef __TENSOR__
#define __TENSOR__

static wstring Outputer(wstring test)
{
	if (test.find(L'.') != wstring::npos or
		test.find(L',') != wstring::npos)
	{
		while (test.at(test.size() - 1) == L'0')
		{
			test.pop_back();
		}
	}
	if (test.at(test.size() - 1) == L',' or test.at(test.size() - 1) == L'.')
	{
		test.pop_back();
	}
	ret test;
}

namespace std_tensor
{
	// metafunzioni necessarie
	template<class T, class = void> struct has_const_str : false_type {};
	template<class T>
	struct has_const_str<T, void_t<decltype(declval<const T>().str())>>
		: true_type
	{};

	// tensor, una variante ottimizzata di ::std::vector
	template<class T>class tensor
	{
		// dati
	protected:
		T* data;
		size_t capacity{ 10 };
		size_t count{ 10 };

		// metodi privati
		void resize(size_t new_capacity);

	public:
		// costruttori e distruttori
		tensor();
		tensor(const tensor& other);
		tensor(tensor&& other) noexcept;
		tensor(initializer_list<T> init);
		tensor(size_t size, const T& initial_value);
		tensor(size_t size);
		~tensor();

		// assegnazione
		tensor& operator=(const tensor& other);
		tensor& operator=(tensor&& other) noexcept;
		inline void assign(tensor<T> other);

		// metodi di base
		inline T* Data() const;
		inline size_t size() const;
		inline size_t get_capacity() const;
		inline bool empty() const;

		// metodi di accesso agli elementi
		inline T& at(size_t index);
		inline const T& at(size_t index) const;
		inline T& last();
		inline const T& last() const;

		// metodi di taglio
		inline void clear();
		tensor erase(size_t pos);
		tensor erase(size_t pos, size_t n);

		// operatori di accesso agli elementi
		_NODISCARD inline T& operator[](size_t index);
		_NODISCARD inline const T& operator[](size_t index) const;

		// operatori di modifica degli elementi e della dimensione
		inline void push_back(const T& value);
		inline void pop_back();
		void push_front(const T& value);
		void pop_front();

		// operatori di modifica della dimensione
		inline tensor<T>& operator++();
		inline tensor<T>& operator++(int);
		inline tensor<T>& operator--();
		inline tensor<T>& operator--(int);
		inline tensor& operator-=(size_t n);

		// operatori push
		tensor& operator()(size_t n);
		tensor& operator()(size_t n, const T& value);
		inline tensor& operator<<(const T& value);
		inline tensor& operator>>(const T& value);

		// operatori di uguaglianza
		_NODISCARD bool operator==(const tensor& other) const;
		_NODISCARD inline bool operator!=(const tensor& other) const;

		// operatori di concatenazione
		_NODISCARD tensor operator+(const T value) const;
		_NODISCARD tensor operator+(const tensor other) const;
		tensor& operator+=(const tensor other);

		// operatori di confronto tra tensori
		_NODISCARD virtual inline bool operator<(const tensor& other) const;
		_NODISCARD virtual inline bool operator<=(const tensor& other) const;
		_NODISCARD virtual inline bool operator>(const tensor& other) const;
		_NODISCARD virtual inline bool operator>=(const tensor& other) const;

		// // operatori di confronto a destra con un intero
		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator==(U n) const;

		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator!=(U n) const;

		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator<(U n) const;

		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator<=(U n) const;

		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator>(U n) const;

		template<typename U>
		typename enable_if<is_arithmetic<U>::value, bool>::type
			operator>=(U n) const;
		// //

		// operatori logici
		_NODISCARD inline bool operator&&(const tensor& other) const;
		_NODISCARD inline bool operator||(const tensor& other) const;
		_NODISCARD inline bool operator%(const tensor& other) const;

		// iteratori
		class iterator
		{
		private: T* data;

		public:
			size_t index;
			using value_type = T;
			using reference = T&;
			using pointer = T*;
			using difference_type = ptrdiff_t;
			using iterator_category = forward_iterator_tag;

			iterator(T* data, size_t index);

			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);

			iterator operator+(size_t n) const;
			iterator& operator+=(size_t n);
			iterator operator-(size_t n) const;
			iterator& operator-=(size_t n);

			size_t operator+(iterator value) const;
			size_t operator-(iterator value) const;

			T& operator*();
			const T& operator*() const;
			T* operator->();
			const T* operator->() const;

			bool operator==(const iterator& other) const;
			bool operator!=(const iterator& other) const;
			bool operator<(const iterator& other) const;
			bool operator<=(const iterator& other) const;
			bool operator>(const iterator& other) const;
			bool operator>=(const iterator& other) const;
		};

		iterator begin();
		iterator end();
		tensor(iterator first, iterator last);

		// metodi con gli operatori
		void erase(iterator it);
		void erase(iterator first, iterator last);
		void insert(iterator pos, const T& value);
		void insert(iterator pos, size_t amount, const T& value);
		void remove(const T& value);

		virtual _NODISCARD wstring str() const;
	};

	// // operatori di confronto a sinistra con un intero
	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator==(U n, const tensor<T>& t);

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator!=(U n, const tensor<T>& t);

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator<(U n, const tensor<T>& t);

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator<=(U n, const tensor<T>& t);

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator>(U n, const tensor<T>& t);

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator>=(U n, const tensor<T>& t);
	// //

	// estensioni di tensor
	class tensor_t
	{
	public:
		tensor<bool> is_prime;
		tensor<ptrdiff_t> list_primes;

		tensor_t();
		tensor_t(tensor<bool> is_prime_param, tensor<ptrdiff_t> list_primes_param);
		tensor_t(const tensor_t& other);
		tensor_t(tensor_t&& other) noexcept;

		tensor_t& operator=(const tensor_t& other);
	};

#pragma region tensor
	
	template<class T> void tensor<T>::resize(size_t new_capacity)
	{
		if (capacity > new_capacity)
		{
			ret;
		}

		T* new_data = new T[new_capacity];
		if (data != nullptr)
		{
			for (size_t i = 0; i < count; ++i)
			{
				new_data[i] = move(data[i]);
			}
			delete[] data;
		}

		data = new_data;
		capacity = new_capacity;
	}

	template<class T> tensor<T>::tensor() : data(nullptr), capacity(0), count(0)
	{
		resize(10);
	}

	template<class T> tensor<T>::tensor(const tensor& other)
		: data(nullptr), capacity(0), count(0)
	{
		resize(other.count + 10);
		count = other.count;
		for (size_t i = 0; i < count; ++i)
		{
			data[i] = other.data[i];
		}
	}

	template<class T> tensor<T>::tensor(tensor&& other) noexcept :
		data(other.data),
		capacity(other.capacity),
		count(other.count)
	{
		other.data = nullptr;
		other.count = other.capacity = 0;
	}

	template<class T> tensor<T>::tensor(initializer_list<T> init) : tensor()
	{
		for (const T& value : init)
		{
			push_back(value);
		}
	}

	template<class T> tensor<T>::tensor(size_t size, const T& initial_value)
		: data(nullptr), capacity(0), count(0)
	{
		resize(size + 10);
		count = size;
		 fill(data, data + count, initial_value);
	}

	template<class T> tensor<T>::tensor(size_t size)
		: data(nullptr), capacity(0), count(0)
	{
		resize(size + 10);
		count = size;
	}

	template<class T> tensor<T>::~tensor()
	{
		delete[] data;
	}

	template<class T> tensor<T>& tensor<T>::operator=(const tensor& other)
	{
		if (this != &other)
		{
			resize(other.count + 10);
			for (size_t i = 0; i < other.count; ++i)
			{
				data[i] = other.data[i];
			}
			count = other.count;
		}
		ret *this;
	}

	template<class T> tensor<T>& tensor<T>::operator=(tensor&& other) noexcept
	{
		if (this != &other)
		{
			delete[] data;
			data = other.data;
			capacity = other.capacity;
			count = other.count;
			other.data = nullptr;
			other.count = other.capacity = 0;
		}
		ret *this;
	}

	template<class T> inline void tensor<T>::assign(tensor other)
	{
		*this = other;
	}

	template<class T> inline T* tensor<T>::Data() const
	{
		ret data;
	}

	template<class T> inline size_t tensor<T>::size() const
	{
		ret count;
	}

	template<class T> inline size_t tensor<T>::get_capacity() const
	{
		ret capacity;
	}

	template<class T> inline bool tensor<T>::empty() const
	{
		ret count == 0;
	}

	template<class T> inline T& tensor<T>::at(size_t index)
	{
		if (index >= count)
		{
			throw out_of_range("Index out of range!");
		}
		ret data[index];
	}

	template<class T> inline const T& tensor<T>::at(size_t index) const
	{
		if (index >= count)
		{
			throw out_of_range("Index out of range!");
		}
		ret data[index];
	}

	template<class T> inline T& tensor<T>::last()
	{
		if (count == 0)
		{
			throw out_of_range("Tensor is empty!");
		}
		ret data[count - 1];
	}

	template<class T> inline const T& tensor<T>::last() const
	{
		if (count == 0)
		{
			throw out_of_range("Tensor is empty!");
		}
		ret data[count - 1];
	}

	template<class T> inline void tensor<T>::clear()
	{
		count = 0;
	}

	template<class T> tensor<T> tensor<T>::erase(size_t pos)
	{
		if (pos >= count)
		{
			throw out_of_range("Index out of range!");
		}
		count = pos;
		ret *this;
	}

	template<class T> tensor<T> tensor<T>::erase(size_t pos, size_t n)
	{
		if (pos >= count)
		{
			throw out_of_range("Index out of range");
		}
		n = min(n, count - pos);
		for (size_t i = pos; i < count - n; ++i)
		{
			data[i] = move(data[i + n]);
		}
		count -= n;
		ret *this;
	}

	template<class T> _NODISCARD inline T& tensor<T>::operator[](size_t index)
	{
		ret at(index);
	}

	template<class T>
	_NODISCARD inline const T& tensor<T>::operator[](size_t index) const
	{
		ret at(index);
	}

	template<class T> inline void tensor<T>::push_back(const T& value)
	{
		if (count == capacity)
		{
			resize(capacity * 2 + 1);
		}
		data[count++] = value;
	}

	template<class T> inline void tensor<T>::pop_back()
	{
		if (count == 0)
		{
			throw out_of_range("Tensor is empty");
		}
		count--;
	}

	template<class T> void tensor<T>::push_front(const T& value)
	{
		if (count == capacity)
		{
			resize(capacity * 2);
		}
		for (size_t i = count; i > 0; --i)
		{
			data[i] = move(data[i - 1]);
		}
		data[0] = value;
		count++;
	}

	template<class T> void tensor<T>::pop_front()
	{
		if (count == 0)
		{
			throw out_of_range("Tensor is empty");
		}
		for (size_t i = 0; i < count - 1; ++i)
		{
			data[i] = move(data[i + 1]);
		}
		count--;
	}

	template<class T> inline tensor<T>& tensor<T>::operator++()
	{
		push_front(T());
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator++(int)
	{
		push_back(T());
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator--()
	{
		pop_front();
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator--(int)
	{
		pop_back();
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator-=(size_t n)
	{
		count = n > count ? 0 : count - n;
		ret *this;
	}

	template<class T> tensor<T>& tensor<T>::operator()(size_t n)
	{
		if (n >= count)
		{
			resize(n * 2);
		}
		count = n;
		ret *this;
	}

	template<class T> tensor<T>& tensor<T>::operator()(size_t n, const T& value)
	{
		if (n >= count)
		{
			resize(n * 2);
		}
		for (size_t i = count; i < n; ++i)
		{
			data[i] = value;
		}
		count = n;
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator<<(const T& value)
	{
		push_back(value);
		ret *this;
	}

	template<class T> inline tensor<T>& tensor<T>::operator>>(const T& value)
	{
		push_front(value);
		ret *this;
	}

	template<class T>
	_NODISCARD bool tensor<T>::operator==(const tensor& other) const
	{
		if (count != other.count)
		{
			ret false;
		}
		for (size_t i = 0; i < count; ++i)
		{
			if (data[i] != other.data[i])
			{
				ret false;
			}
		}
		ret true;
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator!=(const tensor& other) const
	{
		ret !(*this == other);
	}

	template<class T> _NODISCARD tensor<T> tensor<T>::operator+(const T value) const
	{
		auto result{ *this };
		result.push_back(value);
		ret result;
	}

	template<class T>
	_NODISCARD tensor<T> tensor<T>::operator+(const tensor other) const
	{
		auto result{ *this };
		result += other;
		ret result;
	}

	template<class T> tensor<T>& tensor<T>::operator+=(const tensor other)
	{
		for (size_t i = 0; i < other.count; ++i)
		{
			push_back(other.data[i]);
		}
		ret *this;
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator<(const tensor& other) const
	{
		ret count < other.count;
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator<=(const tensor& other) const
	{
		ret count <= other.count;
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator>(const tensor& other) const
	{
		ret count > other.count;
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator>=(const tensor& other) const
	{
		ret count >= other.count;
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator==(U n) const
	{
		ret count == static_cast<size_t>(n);
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator!=(U n) const
	{
		ret count != static_cast<size_t>(n);
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator<(U n) const
	{
		ret count < static_cast<size_t>(n);
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator<=(U n) const
	{
		ret count <= static_cast<size_t>(n);
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator>(U n) const
	{
		ret count > static_cast<size_t>(n);
	}

	template<class T>
	template<typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		tensor<T>::operator>=(U n) const
	{
		ret count >= static_cast<size_t>(n);
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator==(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) == t.size();
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator!=(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) != t.size();
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator<(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) < t.size();
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator<=(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) <= t.size();
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator>(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) > t.size();
	}

	template<class T, typename U>
	typename enable_if<is_arithmetic<U>::value, bool>::type
		operator>=(U n, const tensor<T>& t)
	{
		ret static_cast<size_t>(n) >= t.size();
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator&&(const tensor& other) const
	{
		ret !this->empty() and !other.empty();
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator||(const tensor& other) const
	{
		ret !this->empty() or !other.empty();
	}

	template<class T>
	_NODISCARD inline bool tensor<T>::operator%(const tensor& other) const
	{
		ret this->size() xor other.size();
	}

	template<class T> tensor<T>::iterator::iterator(T* data, size_t index)
		: data(data), index(index)
	{}

	template<class T>
	typename tensor<T>::iterator& tensor<T>::iterator::operator++()
	{
		index++;
		ret *this;
	}

	template<class T>
	typename tensor<T>::iterator tensor<T>::iterator::operator++(int)
	{
		auto temp{ *this };
		index++;
		ret temp;
	}

	template<class T>
	typename tensor<T>::iterator& tensor<T>::iterator::operator--()
	{
		index--;
		ret *this;
	}

	template<class T>
	typename tensor<T>::iterator tensor<T>::iterator::operator--(int)
	{
		auto temp{ *this };
		index--;
		ret temp;
	}

	template<class T>
	typename tensor<T>::iterator tensor<T>::iterator::operator+(size_t n) const
	{
		ret iterator(data, index + n);
	}

	template<class T>
	typename tensor<T>::iterator& tensor<T>::iterator::operator+=(size_t n)
	{
		index += n;
		ret *this;
	}

	template<class T>
	typename tensor<T>::iterator tensor<T>::iterator::operator-(size_t n) const
	{
		ret iterator(data, index - n);
	}

	template<class T>
	typename tensor<T>::iterator& tensor<T>::iterator::operator-=(size_t n)
	{
		index -= n;
		ret *this;
	}

	template<class T> size_t tensor<T>::iterator::operator+(iterator value) const
	{
		ret index + value.index;
	}

	template<class T> size_t tensor<T>::iterator::operator-(iterator value) const
	{
		if (index == value.index)
		{
			ret 0;
		}
		if (index < value.index)
		{
			throw out_of_range("Index out of range");
		}
		ret index - value.index;
	}

	template<class T> T& tensor<T>::iterator::operator*()
	{
		ret data[index];
	}

	template<class T> const T& tensor<T>::iterator::operator*() const
	{
		ret data[index];
	}

	template<class T> T* tensor<T>::iterator::operator->()
	{
		ret &data[index];
	}

	template<class T> const T* tensor<T>::iterator::operator->() const
	{
		ret &data[index];
	}

	template<class T>
	bool tensor<T>::iterator::operator==(const iterator& other) const
	{
		ret index == other.index;
	}

	template<class T>
	bool tensor<T>::iterator::operator!=(const iterator& other) const
	{
		ret index != other.index;
	}

	template<class T>
	bool tensor<T>::iterator::operator<(const iterator& other) const
	{
		ret index < other.index;
	}

	template<class T>
	bool tensor<T>::iterator::operator<=(const iterator& other) const
	{
		ret index <= other.index;
	}

	template<class T>
	bool tensor<T>::iterator::operator>(const iterator& other) const
	{
		ret index > other.index;
	}

	template<class T>
	bool tensor<T>::iterator::operator>=(const iterator& other) const
	{
		ret index >= other.index;
	}

	template<class T> typename tensor<T>::iterator tensor<T>::begin()
	{
		ret iterator(data, 0);
	}

	template<class T> typename tensor<T>::iterator tensor<T>::end()
	{
		ret iterator(data, count);
	}

	template<class T> tensor<T>::tensor(iterator first, iterator last)
		: data(nullptr), capacity(0), count(0)
	{
		size_t n = last - first;
		if (n > count)
		{
			resize(n);
		}
		count = n;

		for (size_t i = 0; i < n; ++i, ++first)
		{
			data[i] = *first;
		}
	}

	template<class T> void tensor<T>::erase(iterator it)
	{
		if (it == end())
		{
			throw out_of_range("Iterator out of range");
		}
		size_t pos{ it - begin() };
		for (size_t i = pos; i < count - 1; ++i)
		{
			data[i] = move(data[i + 1]);
		}
		count--;
	}

	template<class T> void tensor<T>::erase(iterator first, iterator last)
	{
		if (first == last)
		{
			ret;
		}
		size_t start{ first - begin() }, end{ last - begin() };

		if (start >= count or end > count or start > end)
		{
			throw out_of_range("Invalid iterator range");
		}

		size_t distance = end - start;
		for (size_t i = start; i < count - distance; ++i)
		{
			data[i] = move(data[i + distance]);
		}

		count -= distance;
	}

	template<class T> void tensor<T>::insert(iterator pos, const T& value)
	{
		size_t index = pos - begin();
		if (count == capacity)
		{
			resize(capacity * 2);
		}
		for (size_t i = count; i > index; --i)
		{
			data[i] = move(data[i - 1]);
		}
		data[index] = value;
		count++;
	}

	template<class T>
	void tensor<T>::insert(iterator pos, size_t amount, const T& value)
	{
		if (amount == 0)
		{
			ret;
		}

		size_t index = pos - begin();
		if (count + amount >= capacity)
		{
			resize((count + amount) * 2);
		}

		for (ptrdiff_t i = count - 1; i >= (ptrdiff_t)index; --i)
		{
			data[i + amount] = move(data[i]);
		}
		for (size_t i = 0; i < amount; ++i)
		{
			data[index + i] = value;
		}
		count += amount;
	}

	template<class T> void tensor<T>::remove(const T& value)
	{
		size_t write{};
		for (size_t read = 0; read < count; ++read)
		{
			if (data[read] != value)
			{
				if (write != read) data[write] = move(data[read]);
				{
					write++;
				}
			}
		}
		count = write;
	}

	template<class T> _NODISCARD wstring tensor<T>::str() const
	{
		wostringstream result;
		wstring outp;
		result << fixed;

		// bool
		if constexpr (is_same_v<T, bool>)
		{
			for (size_t i = 0; i < count; ++i)
			{
				result << (*this)[i] ? L"1" : L"0";
				result << L", ";
			}
		}

		// carattere
		else if constexpr (is_same_v<T, wchar_t>)
		{
			for (size_t i = 0; i < count; ++i)
			{
				result << (*this)[i];
			}
			result << L", ";
		}

		// numeri decimali
		else if constexpr (is_same_v<T, double> or is_same_v<T, long double>)
		{
			for (size_t i = 0; i < count; ++i)
			{
				wostringstream temp;
				if (integer((*this)[i]))
				{
					temp << setprecision(0);
				}
				temp << (*this)[i];
				result << Outputer(temp.str()) << L", ";
			}
		}

		// dati generici
		else if constexpr (is_integral_v<T> or is_same_v<T, wstring>)
		{
			for (size_t i = 0; i < count; ++i)
			{
				result << (*this)[i] << L", ";
			}
		}

		// qualcosa
		else if constexpr (has_const_str<T>::value)
		{
			for (size_t i = 0; i < count; ++i)
			{
				result << (*this)[i].str() << L", ";
			}
		}

		// niente
		else
		{
			ret L"";
		}

		// fine
		outp = result.str();
		if (outp.size() >= 2)
		{
			outp.pop_back();
			outp.pop_back();
		}
		ret L"{ " + outp + L" }";
	}

	template<class T>
	wostream& operator<<(wostream& os, const tensor<T>& obj)
	{
		os << obj.str();
		ret os;
	}

#pragma endregion
}

#define _TENSOR ::std_tensor::
#endif // __TENSOR__
