#pragma once

// definizioni di macro
#define ret return

// inclusioni
#include "../include/tensor.h"
using namespace std;

namespace std_tensor
{
#pragma region tensor_t

	tensor_t::tensor_t() {}

	tensor_t::tensor_t(
		tensor<bool> is_prime_param,
		tensor<ptrdiff_t> list_primes_param
	) :
		is_prime(move(is_prime_param)),
		list_primes(move(list_primes_param))
	{}

	tensor_t::tensor_t(const tensor_t& other)
		: is_prime(other.is_prime), list_primes(other.list_primes)
	{}

	tensor_t::tensor_t(tensor_t&& other) noexcept
		: is_prime(move(other.is_prime)),
		list_primes(move(other.list_primes))
	{}

	tensor_t& tensor_t::operator=(const tensor_t& other)
	{
		if (this != &other)
		{
			is_prime = other.is_prime;
			list_primes = other.list_primes;
		}
		ret *this;
	}

#pragma endregion
}
