#define NO_DISCARD_CONST_EXPR _NODISCARD _CONSTEXPR20
#ifndef TENSOR_IMPL_H
#define TENSOR_IMPL_H

#include "tensor.h"
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

template <class T>
void tensor<T>::resize(size_t new_capacity) {
	if (new_capacity < capacity) return;
	T* new_data = new(std::nothrow) T[new_capacity];
	if (data != nullptr) {
		for (size_t i = 0; i < count; ++i) new_data[i] = std::move(data[i]);
		delete[] data;
	}
	data = new_data;
	capacity = new_capacity;
}

template <class T>
tensor<T>::tensor() : data(nullptr), capacity(0), count(0)
{
	resize(10);
}

template <class T>
tensor<T>::tensor(const tensor& other) : data(nullptr), capacity(0), count(0)
{
	resize(other.count);
	count = other.count;
	for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
}

template <class T>
tensor<T>::tensor(tensor&& other) noexcept :
	data(other.data),
	capacity(other.capacity),
	count(other.count)
{
	other.data = nullptr;
	other.capacity = 0;
	other.count = 0;
}

template <class T>
tensor<T>::tensor(std::initializer_list<T> init) : tensor()
{
	for (const T& value : init) push_back(value);
}

template <class T>
tensor<T>::tensor(size_t size, const T& initial_value)
	: data(nullptr), capacity(0), count(0)
{
	resize(size);
	count = size;
	std::fill(data, data + count, initial_value);
}

template <class T>
tensor<T>::tensor(size_t size) : data(nullptr), capacity(0), count(0)
{
	resize(size);
	count = size;
}

template <class T>
tensor<T>::~tensor()
{
	delete[] data;
}

template <class T>
tensor<T>& tensor<T>::operator=(const tensor& other)
{
	if (this != &other) {
		resize(other.count);
		for (size_t i = 0; i < other.count; ++i) data[i] = other.data[i];
		count = other.count;
	}
	return *this;
}

template <class T>
tensor<T>& tensor<T>::operator=(tensor&& other) noexcept
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

template<class T>
void tensor<T>::assign(tensor<T> other)
{
	*this = other;
}

template<class T>
size_t tensor<T>::size() const
{
	return count;
}

template<class T>
size_t tensor<T>::get_capacity() const
{
	return capacity;
}

template<class T>
bool tensor<T>::empty() const
{
	return count == 0;
}

template<class T>
T& tensor<T>::at(size_t index)
{
	if (index >= count) throw std::out_of_range("Index out of range");
	return data[index];
}

template<class T>
const T& tensor<T>::at(size_t index) const
{
	if (index >= count) throw std::out_of_range("Index out of range");
	return data[index];
}

template<class T>
T& tensor<T>::last()
{
	return data[count - 1];
}

template<class T>
const T& tensor<T>::last() const
{
	return data[count - 1];
}

template<class T>
void tensor<T>::clear()
{
	count = 0;
}

template<class T>
void tensor<T>::erase(size_t pos)
{
	if (pos >= count) throw std::out_of_range("Index out of range");
	for (size_t i = pos; i < count - 1; ++i) data[i] = move(data[i + 1]);
	count--;
}

template<class T>
void tensor<T>::erase(size_t pos, size_t n)
{
	if (pos >= count) throw std::out_of_range("Index out of range");
	n = std::min(n, count - pos);
	for (size_t i = pos; i < count - n; ++i) data[i] = move(data[i + n]);
	count -= n;
}

template<class T>
NO_DISCARD_CONST_EXPR T& tensor<T>::operator[](size_t index)
{
	return at(index);
}

template<class T>
NO_DISCARD_CONST_EXPR const T& tensor<T>::operator[](size_t index) const
{
	return at(index);
}

template<class T>
void tensor<T>::push_back(const T& value)
{
	if (count == capacity) resize(capacity * 2 + 1);
	data[count++] = value;
}

template<class T>
void tensor<T>::pop_back()
{
	if (count == 0) throw std::out_of_range("tensor is empty");
	count--;
}

template<class T>
void tensor<T>::push_front(const T& value)
{
	if (count == capacity) resize(capacity * 2);
	for (size_t i = count; i > 0; --i) data[i] = std::move(data[i - 1]);
	data[0] = value;
	count++;
}

template<class T>
void tensor<T>::pop_front()
{
	if (count == 0) throw std::out_of_range("tensor is empty");
	for (size_t i = 0; i < count - 1; ++i) data[i] = std::move(data[i + 1]);
	count--;
}

template<class T>
tensor<T>& tensor<T>::operator++()
{
	push_front(T());
	return *this;
}

template<class T>
tensor<T> tensor<T>::operator++(int)
{
	tensor temp = *this;
	push_back(T());
	return temp;
}

template<class T>
tensor<T>& tensor<T>::operator--()
{
	pop_front();
	return *this;
}

template<class T>
tensor<T> tensor<T>::operator--(int)
{
	tensor temp = *this;
	pop_back();
	return temp;
}

template<class T>
tensor<T>& tensor<T>::operator-=(size_t n)
{
	count = n > count ? 0 : count - n;
	return *this;
}

template<class T>
tensor<T>& tensor<T>::operator()(size_t n)
{
	if (n >= count) resize(n * 2);
	count = n;
	return *this;
}

template<class T>
tensor<T>& tensor<T>::operator()(size_t n, const T& value)
{
	if (n >= count) resize(n * 2);
	for (int i = count; i < n; ++i) data[i] = value;
	count = n;
	return *this;
}

template<class T>
constexpr void tensor<T>::operator<<(const T& value)
{
	push_back(value);
}

template<class T>
constexpr void tensor<T>::operator>>(const T& value)
{
	push_front(value);
}

template<class T>
_NODISCARD bool tensor<T>::operator==(const tensor& other) const
{
	if (count != other.count) return false;
	for (size_t i = 0; i < count; ++i) if (data[i] != other.data[i])
		return false;
	return true;
}

template<class T>
_NODISCARD bool tensor<T>::operator!=(const tensor& other) const
{
	return !(*this == other);
}

template<class T>
_NODISCARD tensor<T> tensor<T>::operator+(const tensor& other) const
{
	tensor result = *this;
	result += other;
	return result;
}

template<class T>
tensor<T>& tensor<T>::operator+=(const tensor& other)
{
	for (size_t i = 0; i < other.count; ++i) push_back(other.data[i]);
	return *this;
}

template<class T>
_NODISCARD bool tensor<T>::operator<(const tensor& other) const
{
	return count < other.count;
}

template<class T>
_NODISCARD bool tensor<T>::operator<=(const tensor& other) const
{
	return count <= other.count;
}

template<class T>
_NODISCARD bool tensor<T>::operator>(const tensor& other) const
{
	return count > other.count;
}

template<class T>
_NODISCARD bool tensor<T>::operator>=(const tensor& other) const
{
	return count >= other.count;
}


template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator==(const tensor<T>& t, U n) {
	return t.count == static_cast<size_t>(n);
}

template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator!=(const tensor<T>& t, U n) {
	return t.count != static_cast<size_t>(n);
}

template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator<(const tensor<T>& t, U n) {
	return t.count < static_cast<size_t>(n);
}

template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator<=(const tensor<T>& t, U n) {
	return t.count <= static_cast<size_t>(n);
}

template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator>(const tensor<T>& t, U n) {
	return t.count > static_cast<size_t>(n);
}

template <class T, typename U,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator>=(const tensor<T>& t, U n) {
	return t.count >= static_cast<size_t>(n);
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator==(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) == t.count;
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator!=(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) != t.count;
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator<(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) < t.count;
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator<=(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) <= t.count;
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator>(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) > t.count;
}

template <typename U, class T,
	typename = std::enable_if_t<std::is_integral_v<U>>>
bool operator>=(U n, const tensor<T>& t) {
	return static_cast<size_t>(n) >= t.count;
}

template<class T>
_NODISCARD bool tensor<T>::operator&&(const tensor& other) const
{
	return !this->empty() and !other.empty();
}

template<class T>
_NODISCARD bool tensor<T>::operator||(const tensor& other) const
{
	return !this->empty() or !other.empty();
}

template<class T>
_NODISCARD bool tensor<T>::operator%(const tensor& other) const
{
	return this->empty() != other.empty();
}

template<class T>
tensor<T>::iterator::iterator(T* data, size_t index) : data(data), index(index) {}

template<class T>
typename tensor<T>::iterator& tensor<T>::iterator::operator++()
{
	index++;
	return *this;
}

template<class T>
typename tensor<T>::iterator tensor<T>::iterator::operator++(int)
{
	iterator temp = *this;
	index++;
	return temp;
}

template<class T>
typename tensor<T>::iterator& tensor<T>::iterator::operator--()
{
	index--;
	return *this;
}

template<class T>
typename tensor<T>::iterator tensor<T>::iterator::operator--(int)
{
	iterator temp = *this;
	index--;
	return temp;
}

template<class T>
typename tensor<T>::iterator tensor<T>::iterator::operator+(size_t n) const
{
	return iterator(data, index + n);
}

template<class T>
typename tensor<T>::iterator& tensor<T>::iterator::operator+=(size_t n)
{
	index += n;
	return *this;
}

template<class T>
typename tensor<T>::iterator tensor<T>::iterator::operator-(size_t n) const
{
	return iterator(data, index - n);
}

template<class T>
typename tensor<T>::iterator& tensor<T>::iterator::operator-=(size_t n)
{
	index -= n;
	return *this;
}

template<class T>
size_t tensor<T>::iterator::operator+(iterator value) const
{
	return index + value.index;
}

template<class T>
size_t tensor<T>::iterator::operator-(iterator value) const
{
	if (index == value.index) return 0;
	if (index < value.index) throw std::out_of_range("Index out of range");
	return index - value.index;
}

template<class T>
T& tensor<T>::iterator::operator*()
{
	return data[index];
}

template<class T>
const T& tensor<T>::iterator::operator*() const
{
	return data[index];
}

template<class T>
T* tensor<T>::iterator::operator->()
{
	return &data[index];
}

template<class T>
const T* tensor<T>::iterator::operator->() const
{
	return &data[index];
}

template<class T>
bool tensor<T>::iterator::operator==(const iterator& other) const
{
	return index == other.index;
}

template<class T>
bool tensor<T>::iterator::operator!=(const iterator& other) const
{
	return index != other.index;
}

template<class T>
bool tensor<T>::iterator::operator<(const iterator& other) const
{
	return index < other.index;
}

template<class T>
bool tensor<T>::iterator::operator<=(const iterator& other) const
{
	return index <= other.index;
}

template<class T>
bool tensor<T>::iterator::operator>(const iterator& other) const
{
	return index > other.index;
}

template<class T>
bool tensor<T>::iterator::operator>=(const iterator& other) const
{
	return index >= other.index;
}

template<class T>
tensor<T>::iterator tensor<T>::begin()
{
	return iterator(data, 0);
}

template<class T>
tensor<T>::iterator tensor<T>::end()
{
	return iterator(data, count);
}

template<class T>
void tensor<T>::erase(iterator it)
{
	if (it == end()) throw std::out_of_range("Iterator out of range");
	size_t pos{ it - begin() };
	for (size_t i = pos; i < count - 1; ++i) data[i] = std::move(data[i + 1]);
	count--;
}

template<class T>
void tensor<T>::erase(iterator first, iterator last)
{
	if (first == last) return;
	size_t start{ first - begin() };
	size_t end{ last - begin() };

	if (start >= count or end > count or start > end)
		throw std::out_of_range("Invalid iterator range");

	size_t distance = end - start;
	for (size_t i = start; i < count - distance; ++i)
		data[i] = std::move(data[i + distance]);

	count -= distance;
}

template<class T>
void tensor<T>::insert(iterator pos, const T& value)
{
	size_t index = pos - begin();
	if (count == capacity) resize(capacity * 2);

	for (size_t i = count; i > index; --i) data[i] = std::move(data[i - 1]);

	data[index] = value;
	count++;
}

template<class T>
void tensor<T>::remove(const T& value)
{
	size_t write{};
	for (size_t read = 0; read < count; ++read) if (data[read] != value)
	{
		if (write != read) data[write] = move(data[read]);
		write++;
	}
	count = write;
}

template<class T>
_NODISCARD std::wstring tensor<T>::str()
{
	std::wostringstream result;
	std::wstring outp;

	// bool
	if constexpr (std::is_same_v<T, bool>) for (const auto& element : *this) {
		result << element ? L"1" : L"0";
		result << L", ";
	}

	// carattere
	else if constexpr (std::is_same_v<T, wchar_t>) {
		for (const auto& element : *this) result << element;
		result << L", ";
	}

	// dato integrale
	else if constexpr (std::is_integral_v<T>)
		for (const auto& element : *this) result << std::to_wstring(element) << L", ";

	// stringhe
	else if constexpr (std::is_same_v<T, std::wstring>)
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

#endif // TENSOR_IMPL_H