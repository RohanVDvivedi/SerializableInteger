#include<large_uint.h>

#include<cutlery_math.h>

int compare_large_uint(large_uint a, large_uint b)
{
	int res = 0;
	for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0 && res == 0;)
	{
		i--;
		res = compare_numbers(a.limbs[i], b.limbs[i]);
	}
	return res;
}

int are_equal_large_uint(large_uint a, large_uint b)
{
	return compare_large_uint(a, b) == 0;
}

// carry_in must be 0 or 1 only
static uint64_t add_large_uint_overflow_unsafe_with_carry(large_uint* res, large_uint a, large_uint b, uint64_t carry)
{
	carry = !!carry;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
	{
		uint64_t carry_in = carry;
		res->limbs[i] = a.limbs[i] + b.limbs[i] + carry_in;
		carry = will_unsigned_sum_overflow(uint64_t, a.limbs[i], b.limbs[i]) || will_unsigned_sum_overflow(uint64_t, a.limbs[i] + b.limbs[i], carry_in);
	}
	return carry;
}

uint64_t add_large_uint_overflow_unsafe(large_uint* res, large_uint a, large_uint b)
{
	return add_large_uint_overflow_unsafe_with_carry(res, a, b, 0);
}

int add_large_uint(large_uint* res, large_uint a, large_uint b, large_uint max_limit)
{
	large_uint res_temp;
	if(add_large_uint_overflow_unsafe(&res_temp, a, b)) // carry out implies overflow
		return 0;

	// if max_limit is not 0, i.e. max_limit exists, and res_temp >= max_limit, then fail
	if(compare_large_uint(max_limit, LARGE_UINT_MIN) != 0 && compare_large_uint(res_temp, max_limit) >= 0)
		return 0;

	(*res) = res_temp;
	return 1;
}

static large_uint bitwise_not(large_uint a)
{
	large_uint res;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		res.limbs[i] = ~a.limbs[i];
	return res;
}

uint64_t sub_large_uint_underflow_unsafe(large_uint* res, large_uint a, large_uint b)
{
	large_uint not_b = bitwise_not(b);
	return add_large_uint_overflow_unsafe_with_carry(res, a, not_b, 1);
}

int sub_large_uint(large_uint* res, large_uint a, large_uint b)
{
	// can not subtract if a < b
	if(compare_large_uint(a, b) < 0)
		return 0;

	sub_large_uint_underflow_unsafe(res, a, b);
	return 1;
}

int set_bit_in_large_uint(large_uint* res, uint32_t bit_index)
{
	if(bit_index >= LARGE_UINT_MAX_BYTES * CHAR_BIT)
		return 0;
	res->limbs[bit_index / (sizeof(uint64_t) * CHAR_BIT)] |= (((uint64_t)1) << (bit_index % (sizeof(uint64_t) * CHAR_BIT)));
	return 1;
}

#include<serial_int.h>

void serialize_large_uint(void* bytes, uint32_t bytes_size, large_uint l)
{
	bytes_size = min(bytes_size, LARGE_UINT_MAX_BYTES);

	uint32_t limb_index = 0;
	while(bytes_size > 0)
	{
		uint32_t bytes_to_write = min(sizeof(uint64_t), bytes_size);

		serialize_uint64(bytes, bytes_to_write, l.limbs[limb_index++]);

		bytes_size -= bytes_to_write;
		bytes += bytes_to_write;
	}
}

large_uint deserialize_large_uint(const char* bytes, uint32_t bytes_size)
{
	large_uint res = {};

	bytes_size = min(bytes_size, LARGE_UINT_MAX_BYTES);

	uint32_t limb_index = 0;
	while(bytes_size > 0)
	{
		uint32_t bytes_to_read = min(sizeof(uint64_t), bytes_size);

		res.limbs[limb_index++] = deserialize_uint64(bytes, bytes_to_read);

		bytes_size -= bytes_to_read;
		bytes += bytes_to_read;
	}

	return res;
}

int cast_large_uint_to_uint64(uint64_t* value, large_uint a)
{
	uint32_t limbs_required = LARGE_UINT_LIMBS_COUNT;
	while(limbs_required > 0 && a.limbs[limbs_required-1] == 0)
		limbs_required--;
	
	if(limbs_required <= 1)
	{
		(*value) = a.limbs[0];
		return 1;
	}

	return 0;
}

#include<stdio.h>

void print_large_uint(large_uint l)
{
	int to_print = 0;
	for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)
	{
		i--;
		to_print = to_print || (!!(l.limbs[i]));
		if(to_print || (i == 0))
		{
			printf("%llu", (unsigned long long int)(l.limbs[i]));
			if(i > 0)
				printf(":");
		}
	}
}