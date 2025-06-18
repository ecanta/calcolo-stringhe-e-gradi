#pragma once

// definizioni di macro
#define ret return
#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)

// inclusioni
#include <cmath>
#include <compare>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>
using namespace std;

// blocco del preprocessore attivo
#ifndef __COMPLEX__
#define __COMPLEX__

template<typename T> T Sqrt(T val)
{
	if constexpr (is_integral_v<T>)
	{
		ret static_cast<T>(sqrt(static_cast<double>(val)));
	}
	else if constexpr (is_floating_point_v<T>)
	{
		ret sqrt(val);
	}
	else
	{
		throw invalid_argument("Unsupported type!");
	}
}
template<typename Ty>class complex
{
public:

	// dati
	Ty RealPart;
	Ty ImaginaryPart;
	Ty norm() const;

	// confronto
	partial_ordering operator<=>(const complex& other) const;
	bool real() const;

	// costruttori
	complex();
	complex(Ty real);
	complex(Ty real, Ty imag);

	// metodi matematici
	inline complex conjugate() const;
	inline complex opposite() const;

	// addizione
	complex operator+(complex value) const;
	inline complex& operator+=(complex value);
	inline complex& operator++();
	inline complex operator++(int);

	// sottrazione
	complex operator-(complex value) const;
	inline complex& operator-=(complex value);
	inline complex& operator--();
	inline complex operator--(int);

	// moltiplicazione e divisione
	complex operator*(complex value) const;
	inline complex& operator*=(complex value);
	complex operator/(complex value) const;
	inline complex operator/=(complex value);

	// output
	_NODISCARD wstring str() const;
};

#pragma region complex

template<typename Ty> Ty complex<Ty>::norm() const
{
	ret Sqrt(RealPart * RealPart + ImaginaryPart * ImaginaryPart);
}

// confronto
template<typename Ty>
partial_ordering complex<Ty>::operator<=>(const complex& other) const
{
	ret norm() <=> other.norm();
}
template<typename Ty> bool complex<Ty>::real() const
{
	ret ImaginaryPart == 0;
}

// costruttori
template<typename Ty> complex<Ty>::complex() : RealPart(0), ImaginaryPart(0) {}
template<typename Ty> complex<Ty>::complex(Ty real)
	: RealPart(real), ImaginaryPart(0)
{}
template<typename Ty> complex<Ty>::complex(Ty real, Ty imag)
	: RealPart(real), ImaginaryPart(imag)
{}

// metodi matematici
template<typename Ty> inline complex<Ty> complex<Ty>::conjugate() const
{
	ret complex(RealPart, -ImaginaryPart);
}
template<typename Ty> inline complex<Ty> complex<Ty>::opposite() const
{
	ret complex(-RealPart, -ImaginaryPart);
}

// addizione
template<typename Ty> complex<Ty> complex<Ty>::operator+(complex value) const
{
	ret complex(
		RealPart + value.RealPart,
		ImaginaryPart + value.ImaginaryPart
	);
}
template<typename Ty> inline complex<Ty>& complex<Ty>::operator+=(complex value)
{
	*this = *this + value;
	ret *this;
}
template<typename Ty> inline complex<Ty>& complex<Ty>::operator++()
{
	*this = *this + 1;
	ret *this;
}
template<typename Ty> inline complex<Ty> complex<Ty>::operator++(int)
{
	auto temp{ *this };
	*this = *this + 1;
	ret temp;
}

// sottrazione
template<typename Ty> complex<Ty> complex<Ty>::operator-(complex value) const
{
	ret complex(
		RealPart - value.RealPart,
		ImaginaryPart - value.ImaginaryPart
	);
}
template<typename Ty> inline complex<Ty>& complex<Ty>::operator-=(complex value)
{
	*this = *this - value;
	ret *this;
}
template<typename Ty> inline complex<Ty>& complex<Ty>::operator--()
{
	*this = *this - 1;
	ret *this;
}
template<typename Ty> inline complex<Ty> complex<Ty>::operator--(int)
{
	auto temp{ *this };
	*this = *this - 1;
	ret temp;
}

// moltiplicazione e divisione
template<typename Ty> complex<Ty> complex<Ty>::operator*(complex value) const
{
	Ty a{ RealPart }, b{ ImaginaryPart };
	Ty c{ value.RealPart }, d{ value.ImaginaryPart };

	ret complex(
		a * c - b * d,
		b * c + a * d
	);
}
template<typename Ty> inline complex<Ty>& complex<Ty>::operator*=(complex value)
{
	*this = *this * value;
	ret *this;
}
template<typename Ty> complex<Ty> complex<Ty>::operator/(complex value) const
{
	Ty a{ RealPart }, b{ ImaginaryPart };
	Ty c{ value.RealPart }, d{ value.ImaginaryPart };

	ret complex(
		(a * c + b * d) / (c * c + d * d),
		(b * c - a * d) / (c * c + d * d)
	);
}
template<typename Ty> inline complex<Ty> complex<Ty>::operator/=(complex value)
{
	*this = *this / value;
	ret *this;
}

// output
template<typename Ty> wstring complex<Ty>::str() const
{
	wostringstream output;
	if (ImaginaryPart != 0)
	{
		output << setprecision(10) << L'(';
	}
	output << RealPart;
	if (ImaginaryPart != 0)
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
template<typename Ty> wostream& operator<<(wostream& os, const complex<Ty>& obj)
{
	os << obj.str();
	ret os;
}

#pragma endregion

template<typename Ty> static complex<Ty> InitExponentialForm(Ty radius, Ty angle)
{
	ret complex<Ty>(radius * cos(angle), radius * sin(angle));
}

#endif // __COMPLEX__
