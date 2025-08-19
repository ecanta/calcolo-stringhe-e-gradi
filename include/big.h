#pragma once

// definizioni di macro
#define POS false
#define NEG true

// inclusioni
#include "../include/complex.h"
#include "../include/tensor.h"
using namespace std;

// blocco del preprocessore attivo
using _TENSOR tensor;
#ifndef __BIG__
#define __BIG__

// algoritmo di cooley-tukey per la trasformata di fourier veloce
extern tensor<complex<long double>> Omega;
void FFT(tensor<complex<long double>>& List, bool inverse = false);

// numeri grandi con precisione di long double
class big
{
	// dati
private:
	tensor<int> Integer;
	bool sign;
	long double decimal;

	// funzioni minori
	void construct(ptrdiff_t param);
	bool compare(const big& A, const big& B) const;

	// addizione e sottrazione
	big Add(const big& __This, const big& __Val, bool changesign) const;
	big Sub(const big& __This, const big& __Val, bool changesign) const;
	big AlgebricOperation1(const big& A, const big& B, bool Sign) const;

	// moltiplicazione
	big FFT_Multiplication(const big& value) const;

	// conversione
public:
	template<typename t> t Number();

	// costruttori
	big();
	big(int param);
	big(ptrdiff_t param);
	big(double param);
	big(long double param);
	big(tensor<int> Big);
	big(wstring wstr);

	// confronto primario e assegnazione
	big& operator=(const big& other);
	inline bool operator==(const big& other) const;
	inline bool operator!=(const big& other) const;

	// confronto secondario
	bool operator<(const big& other) const;
	inline bool operator<=(const big& other) const;
	inline bool operator>=(const big& other) const;
	inline bool operator>(const big& other) const;

	// addizione
	big operator+(const big& value) const;
	inline big& operator+=(const big& value);
	inline big& operator++();
	inline big operator++(int);

	// sottrazione
	big operator-(const big& value) const;
	inline big& operator-=(const big& value);
	inline big& operator--();
	inline big operator--(int);

	// shifting
	big operator<<(int shift) const;
	inline big& operator<<=(int shift);
	big operator>>(int shift) const;
	inline big& operator>>=(int shift);

	// moltiplicazione
	big operator*(const big& value) const;
	inline big& operator*=(const big& value);

	// divisione intera
	big operator/(const big& value) const;
	inline big& operator/=(const big& value);

	// modulo
	big operator%(const big& value) const;
	inline big& operator%=(const big& value);

	// potenza
	big operator^(const big& exp) const;
	inline big& operator^=(const big& exp);

	// metodi matematici
	inline size_t Size() const;
	inline bool intg() const;
	inline big fabs() const;
	inline big floor();
	inline big ceil();
	inline big round();
	inline big invert();
	inline int log(int base);

	// output
	wostringstream c_str(int precision) const;
	inline wstring str() const;
};
wostream& operator<<(wostream& os, const big& obj);

#pragma region big

inline bool big::operator==(const big& other) const
{
	ret sign == other.sign and Integer == other.Integer
		and decimal == other.decimal;
}
inline bool big::operator!=(const big& other) const
{
	ret !(*this == other);
}

inline bool big::operator<=(const big& other) const
{
	ret *this < other or *this == other;
}
inline bool big::operator>=(const big& other) const
{
	ret !(*this < other);
}
inline bool big::operator>(const big& other) const
{
	ret !(*this == other or *this < other);
}

inline big& big::operator+=(const big& value)
{
	*this = *this + value;
	ret *this;
}
inline big& big::operator++()
{
	*this = *this + 1;
	ret *this;
}
inline big big::operator++(int)
{
	auto temp{ *this };
	*this = *this + 1;
	ret temp;
}

inline big& big::operator-=(const big& value)
{
	*this = *this - value;
	ret *this;
}
inline big& big::operator--()
{
	*this = *this - 1;
	ret *this;
}
inline big big::operator--(int)
{
	auto temp{ *this };
	*this = *this - 1;
	ret temp;
}

inline big& big::operator*=(const big& value)
{
	*this = *this * value;
	ret *this;
}
inline big& big::operator/=(const big& value)
{
	*this = *this / value;
	ret* this;
}
inline big& big::operator%=(const big& value)
{
	*this = *this % value;
	ret *this;
}
inline big& big::operator^=(const big& exp)
{
	*this = *this ^ exp;
	ret *this;
}

inline size_t big::Size() const
{
	ret Integer.size();
}
inline bool big::intg() const
{
	ret decimal == 0;
}
inline big big::fabs() const
{
	big other = *this;
	other.sign = POS;
	ret other;
}
inline big big::floor()
{
	decimal = 0;
	ret *this;
}
inline big big::ceil()
{
	bool integ = decimal == 0;
	decimal = 0;
	if (integ)
	{
		(*this)++;
	}
	ret *this;
}
inline big big::round()
{
	*this += _STD round(decimal);
	decimal = 0;
	ret *this;
}
inline big big::invert()
{
	sign = !sign;
	ret *this;
}
inline int big::log(int base)
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

inline wstring big::str() const
{
	ret c_str(6).str();
}

// conversione
template<typename t> t big::Number()
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

#pragma endregion

big pow(big x, int y);
big abs(big x);

#endif // __BIG__
