#pragma once

// definizioni di macro
#define ret return
#define POS false
#define NEG true
#define _USE_MATH_DEFINES
#define integer(x) (::std::fabs(x - ::std::round(x)) < 1e-9)

// inclusioni
#include <cmath>
#include "../include/big.h"
#include "../include/complex.h"
#include "../include/tensor.h"
using namespace std;
using _TENSOR tensor;

tensor<complex<long double>> Omega;
void FFT(tensor<complex<long double>>&List, bool inverse)
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

	// algoritmo del bit reversal
	for (size_t ind = 0; ind < N; ++ind)
	{
		size_t rev = 0, x = ind;
		for (size_t i = 0; (1ull << i) < N; ++i)
		{
			rev = (rev << 1) | (x & 1);
			x >>= 1;
		}
		if (rev > ind)
		{
			swap(List[ind], List[rev]);
		}
	}

	// calcolo FFT
	for (size_t Size = 2; Size <= N; Size <<= 1)
	{
		auto OmegaStep = 2 * Omega.size() / Size;

		for (size_t i = 0; i < N; i += Size)
		{
			// calcolo dati
			for (size_t j = 0; j < Size / 2; ++j)
			{
				auto k{ i + j };
				auto product = (
					inverse ?
					Omega[OmegaStep * j].conjugate() : Omega[OmegaStep * j]
					) * List[k + Size / 2];

				Helper[k] = List[k] + product;
				Helper[k + Size / 2] = List[k] - product;
			}

			// trasferimento dati
			for (size_t j = 0; j < Size; ++j)
			{
				auto k{ i + j };
				List[k] = Helper[k];
			}
		}
	}
}

#pragma region big

// funzioni minori
void big::construct(ptrdiff_t param)
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
bool big::compare(const big& A, const big& B) const
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
big big::Add(const big& __This, const big& __Val, bool changesign) const
{
	big This = __This, Val = __Val;
	if (changesign)
	{
		This.sign = !This.sign;
	}
	bool carry;

	// ridimensionamento
	if (This.Integer < Val.Integer)
	{
		swap(This.Integer, Val.Integer);
		swap(This.decimal, Val.decimal);
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
big big::Sub(const big& __This, const big& __Val, bool changesign) const
{
	big This = __This, Val = __Val;
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
big big::AlgebricOperation1(const big& A, const big& B, bool Sign) const
{
	// addendo nullo
	if (B == 0)
	{
		ret A;
	}
	if (A == 0)
	{
		auto result{ B };
		result.sign = Sign xor B.sign;
		ret result;
	}

	// addizione tra valori assoluti
	if (!(A.sign xor B.sign xor Sign))
	{
		ret Add(A, B, false);
	}

	// zero
	if (A.Integer == B.Integer and A.decimal == B.decimal)
	{
		ret 0;
	}

	// sottrazione tra valori assoluti
	ret compare(A, B) ? Sub(B, A, Sign) : Sub(A, B, false);
}

// moltiplicazione
big big::FFT_Multiplication(const big& value) const
{
	// calcolo tensori dei decimali
	tensor<int> decA, decB;
	auto decimalA{ decimal };
	auto decimalB{ value.decimal };
	while (decimalA != 0)
	{
		decimalA *= 10;
		decA << decimalA;
		decimalA -= decA.last();
	}
	while (decimalB != 0)
	{
		decimalB *= 10;
		decB << decimalB;
		decimalB -= decB.last();
	}

	// calcolo variabili importanti
	auto DA{ decA.size() };
	auto DB{ decB.size() };
	auto sizeA{ Integer.size() };
	auto sizeB{ value.Integer.size() };
	auto sumA{ sizeA + DA };
	auto sumB{ sizeB + DB };
	auto sizeT{ sumA + sumB };

	// calcolo dimensione
	size_t N{ 1 };
	while (N < sizeT)
	{
		N <<= 1;
	}

	// aggiunta parte decimale
	tensor<complex<long double>> A(N), B(N);
	for (size_t i = 0; i < DA; ++i)
	{
		A[i] = complex<long double>(decA[DA - i - 1]);
	}
	for (size_t i = 0; i < DB; ++i)
	{
		B[i] = complex<long double>(decB[DB - i - 1]);
	}

	// preparazione tensori
	for (size_t i = DA; i < sumA; ++i)
	{
		A[i] = complex<long double>(Integer[sumA - i - 1]);
	}
	for (size_t i = DB; i < sumB; ++i)
	{
		B[i] = complex<long double>(value.Integer[sumB - i - 1]);
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
		ptrdiff_t cur = _STD round(A[i].RealPart) + carry;
		carry = (cur += 10 * (cur < 0)) / 10;
		result.Integer[N - i - 1] = cur % 10;
	}

	// calcolo parte decimale
	auto& Int{ result.Integer };
	auto& Dec{ result.decimal };
	size_t decprecision{ DA + DB };
	if (decprecision != 0)
	{
		for (ptrdiff_t i = 1; i <= decprecision; ++i)
		{
			Dec = (Dec + Int[N - i]) / 10;
		}
		Int.erase(N - decprecision);
	}

	// rimozione zeri inutili
	auto it{ Int.begin() };
	auto rend{ Int.end() };
	while (*it == 0 and it != rend)
	{
		++it;
	}
	Int.erase(Int.begin(), it);

	// tensore vuoto
	if (Int.empty())
	{
		Int = { 0 };
	}

	// calcolo segno
	result.sign = sign xor value.sign;
	ret result;
}

// costruttori
big::big() : sign(POS), Integer({ 0 }), decimal(0) {}
big::big(int param) : sign(param < 0), Integer(0), decimal(0)
{
	construct(abs(param));
}
big::big(ptrdiff_t param) : sign(param < 0), Integer(0), decimal(0)
{
	construct(abs(param));
}
big::big(double param) : sign(param < 0), Integer(0), decimal(0)
{
	param = _STD fabs(param);
	auto Intpart{ static_cast<ptrdiff_t>(param) };
	decimal = param - Intpart;
	construct(Intpart);
}
big::big(long double param) : sign(param < 0), Integer(0), decimal(0)
{
	param = _STD fabs(param);
	auto Intpart{ static_cast<ptrdiff_t>(param) };
	decimal = param - Intpart;
	construct(Intpart);
}
big::big(tensor<int> Big) : sign(POS), Integer(Big), decimal(0)
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
big::big(wstring wstr) : sign(POS), Integer(0), decimal(0)
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
big& big::operator=(const big& other)
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

// confronto secondario
bool big::operator<(const big& other) const	
{
	ret (sign xor other.sign) ? sign : (compare(*this, other) xor sign);
}

// addizione
big big::operator+(const big& value) const
{
	ret AlgebricOperation1(*this, value, POS);
}

// sottrazione
big big::operator-(const big& value) const
{
	ret AlgebricOperation1(*this, value, NEG);
}

// shifting
big big::operator<<(int shift) const
{
	big result = *this;
	for (ptrdiff_t i = 0; i < shift; ++i)
	{
		result.decimal *= 10;
		result.Integer << result.decimal;
		result.decimal -= result.Integer.last();
	}
	ret result;
}
big& big::operator<<=(int shift)
{
	for (ptrdiff_t i = 0; i < shift; ++i)
	{
		decimal *= 10;
		Integer << decimal;
		decimal -= Integer.last();
	}
	ret *this;
}
big big::operator>>(int shift) const
{
	big result = *this;
	for (ptrdiff_t i = 0; i < shift; ++i)
	{
		result.decimal += Integer.last();
		result.decimal /= 10;
	}
	shift >= result.Integer.size() ?
		result.Integer = { 0 } : result.Integer -= shift;
	ret result;
}
big& big::operator>>=(int shift)
{
	for (ptrdiff_t i = 0; i < shift; ++i)
	{
		decimal += Integer.last();
		decimal /= 10;
	}
	shift >= Integer.size() ? Integer = { 0 } : Integer -= shift;
	ret *this;
}

// moltiplicazione
big big::operator*(const big& value) const
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
	ret FFT_Multiplication(value);
}

// divisione intera
big big::operator/(const big& value) const
{
	if (value == 0)
	{
		throw invalid_argument("Division by zero!");
	}
	if (value == 1)
	{
		ret *this;
	}
	if (value == *this)
	{
		ret 1;
	}

	// metodo di newton-raphson
	big result, old, New = 1;
	for (;;)
	{
		bool FirstIter{ true };
		old = result = New;
		do
		{
			if (!FirstIter)
			{
				result >>= 1;
			}

			New = result * 2 - value * result * result;
			FirstIter = false;
		} while (New.sign or New == 0);

		if ((New - old).fabs() < 1e-15)
		{
			break;
		}
	}

	// rimozione zeri inutili
	auto it{ result.Integer.begin() };
	auto rend{ result.Integer.end() };
	while (*it == 0 and it != rend)
	{
		++it;
	}
	result.Integer.erase(result.Integer.begin(), it);

	// tensore vuoto
	if (result.Integer.empty())
	{
		result.Integer = { 0 };
	}
	result.sign = sign xor value.sign;

	// arrotondamento
	auto output = value.Integer > 10 ? result : (*this) * result;
	if (integer(output.decimal))
	{
		output.decimal = _STD round(output.decimal);
		if (output.decimal == 1)
		{
			output.decimal = 0;
			output++;
		}
	}
	for (ptrdiff_t i = output.Integer.size() - 1; i > 0; --i)
	{
		if (output.Integer[i] < 10)
		{
			break;
		}
		output.Integer[i] = 0;
		output.Integer[i - 1]++;
	}
	if (output.Integer[0] == 10)
	{
		output.Integer[0] = 0;
		output.Integer >> 1;
	}

	ret output;
}

// modulo
big big::operator%(const big& value) const
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

// potenza
big big::operator^(const big& exp) const
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

// output
wostringstream big::c_str(int precision) const
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
		result << str;
	}
	ret result;
}
wostream& operator<<(wostream& os, const big& obj)
{
	os << obj.str();
	ret os;
}

#pragma endregion

big pow(big x, int y)
{
	ret x ^ y;
}
