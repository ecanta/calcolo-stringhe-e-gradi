#define NO_DISCARD_CONST_EXPR _NODISCARD _CONSTEXPR20
#ifndef TENSOR_H
#define TENSOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

template<class T>class tensor
{
protected:

    // dati
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
    tensor(std::initializer_list<T> init);
    tensor(size_t size, const T& initial_value);
    tensor(size_t size);
    ~tensor();

    // assegnazione
    tensor& operator=(const tensor& other);
    tensor& operator=(tensor&& other) noexcept;
    void assign(tensor<T> other);

    // metodi di base
    size_t size() const;
    size_t get_capacity() const;
    bool empty() const;

    // metodi di accesso agli elementi
    virtual T& at(size_t index);
    virtual const T& at(size_t index) const;
    virtual T& last();
    virtual const T& last() const;

    // metodi di taglio
    void clear();
    void erase(size_t pos);
    void erase(size_t pos, size_t n);

    // operatori di accesso agli elementi
    NO_DISCARD_CONST_EXPR T& operator[](size_t index);
    NO_DISCARD_CONST_EXPR const T& operator[](size_t index) const;

    // operatori di modifica degli elementi e della dimensione
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();

    // operatori di modifica della dimensione
    tensor& operator++();
    tensor operator++(int);
    tensor& operator--();
    tensor operator--(int);
    tensor& operator-=(size_t n);

    // operatori push
    tensor& operator()(size_t n);
    tensor& operator()(size_t n, const T& value);
    constexpr void operator<<(const T& value);
    constexpr void operator>>(const T& value);

    // operatori di uguaglianza
    _NODISCARD bool operator==(const tensor& other) const;
    _NODISCARD bool operator!=(const tensor& other) const;

    // operatori di concatenazione
    _NODISCARD tensor operator+(const tensor& other) const;
    tensor& operator+=(const tensor& other);

    // operatori di confronto tra tensori
    _NODISCARD bool operator<(const tensor& other) const;
    _NODISCARD bool operator<=(const tensor& other) const;
    _NODISCARD bool operator>(const tensor& other) const;
    _NODISCARD bool operator>=(const tensor& other) const;

    // operatori di confronto a destra con un intero
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator==(const tensor& t, U n);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator!=(const tensor& t, U n);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator<(const tensor& t, U n);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator<=(const tensor& t, U n);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator>(const tensor& t, U n);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator>=(const tensor& t, U n);

    // operatori di confronto a sinistra con un intero
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator==(U n, const tensor& t);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator!=(U n, const tensor& t);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator<(U n, const tensor& t);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator<=(U n, const tensor& t);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator>(U n, const tensor& t);
    template<typename U, typename = std::enable_if_t<std::is_integral_v<U>>>
    friend bool operator>=(U n, const tensor& t);

    // operatori logici
    _NODISCARD bool operator&&(const tensor& other) const;
    _NODISCARD bool operator||(const tensor& other) const;
    _NODISCARD bool operator%(const tensor& other) const;

    // iteratori
    class iterator {
    private: T* data;
    public: size_t index;
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

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

    // metodi con gli iteratori
    void erase(iterator it);
    void erase(iterator first, iterator last);
    void insert(iterator pos, const T& value);
    void remove(const T& value);

    virtual _NODISCARD std::wstring str();
};

#include "tensor_impl.h"
#endif // TENSOR_H