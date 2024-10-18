#ifndef LARGE_UINT_H
#define LARGE_UINT_H

#include<large_uint_util.h>
#include<serial_int.h>

#include<stdio.h>
#include<inttypes.h>

#include<cutlery_stds.h>
#include<cutlery_math.h>

// LARGE_UINT_LIMBS_COUNT must be lesser than (UINT32_MAX / 64)

#define declarations_large_uint(large_uint, LARGE_UINT_LIMBS_COUNT)                                                                                         \
                                                                                                                                                            \
	typedef struct large_uint large_uint;                                                                                                                   \
	struct large_uint                                                                                                                                       \
	{                                                                                                                                                       \
		uint64_t limbs[LARGE_UINT_LIMBS_COUNT];                                                                                                             \
	};                                                                                                                                                      \
                                                                                                                                                            \
	/* number of maximum bytes of data in a large_uint */                                                                                                   \
	uint32_t get_max_bytes_ ## large_uint();                                                                                                                \
                                                                                                                                                            \
	/* number of bits of data in a large_uint */                                                                                                            \
	uint32_t get_bit_width_ ## large_uint();                                                                                                                \
                                                                                                                                                            \
	/* get a default uint64_t val valued large_uint */                                                                                                      \
	large_uint get_ ## large_uint(uint64_t val);                                                                                                            \
                                                                                                                                                            \
	/* get zero and one values for a large_uint */                                                                                                          \
	large_uint get_0_ ## large_uint();                                                                                                                      \
	large_uint get_1_ ## large_uint();                                                                                                                      \
                                                                                                                                                            \
	/* get min and max values for a large_uint */                                                                                                           \
	large_uint get_min_ ## large_uint();                                                                                                                    \
	large_uint get_max_ ## large_uint();                                                                                                                    \
                                                                                                                                                            \
	/* gets a bit from large_uint */                                                                                                                        \
	int get_bit_from_ ## large_uint(large_uint a, uint32_t bit_index);                                                                                      \
                                                                                                                                                            \
	/* set a bit in large_uint */                                                                                                                           \
	int set_bit_in_ ## large_uint(large_uint* res, uint32_t bit_index);                                                                                     \
                                                                                                                                                            \
	/* reset a bit in large_uint */                                                                                                                         \
	int reset_bit_in_ ## large_uint(large_uint* res, uint32_t bit_index);                                                                                   \
                                                                                                                                                            \
	/* gets a byte from large_uint */                                                                                                                       \
	uint8_t get_byte_from_ ## large_uint(large_uint a, uint32_t byte_index);                                                                                \
                                                                                                                                                            \
	/* set byte at the byte_index in res */                                                                                                                 \
	int set_byte_in_ ## large_uint(large_uint* res, uint32_t byte_index, uint8_t byte);                                                                     \
                                                                                                                                                            \
	/* returns ~a */                                                                                                                                        \
	large_uint bitwise_not_ ## large_uint(large_uint a);                                                                                                    \
                                                                                                                                                            \
	/* returns a & b */                                                                                                                                     \
	large_uint bitwise_and_ ## large_uint(large_uint a, large_uint b);                                                                                      \
                                                                                                                                                            \
	/* returns a | b */                                                                                                                                     \
	large_uint bitwise_or_ ## large_uint(large_uint a, large_uint b);                                                                                       \
                                                                                                                                                            \
	/* returns a ^ b */                                                                                                                                     \
	large_uint bitwise_xor_ ## large_uint(large_uint a, large_uint b);                                                                                      \
                                                                                                                                                            \
	/* returns a << s */                                                                                                                                    \
	large_uint left_shift_ ## large_uint(large_uint a, uint32_t s);                                                                                         \
                                                                                                                                                            \
	/* returns a >> s */                                                                                                                                    \
	large_uint right_shift_ ## large_uint(large_uint a, uint32_t s);                                                                                        \
                                                                                                                                                            \
	/* if(a < b) returns -1 */                                                                                                                              \
	/* else if(a == b) returns 0 */                                                                                                                         \
	/* else if(a > b) returns 1 */                                                                                                                          \
	int compare_ ## large_uint(large_uint a, large_uint b);                                                                                                 \
                                                                                                                                                            \
	/* returns a == b */                                                                                                                                    \
	int are_equal_ ## large_uint(large_uint a, large_uint b);                                                                                               \
                                                                                                                                                            \
	/* returns a == 0 */                                                                                                                                    \
	int is_zero_ ## large_uint(large_uint a);                                                                                                               \
                                                                                                                                                            \
	/* (*res) = a + b + carry and then returns carry */                                                                                                     \
	uint64_t add_with_carry_ ## large_uint(large_uint* res, large_uint a, large_uint b, uint64_t carry_in);                                                 \
                                                                                                                                                            \
	/* returns carry after performing (*res) = a + b; */                                                                                                    \
	uint64_t add_ ## large_uint(large_uint* res, large_uint a, large_uint b);                                                                               \
                                                                                                                                                            \
	/* returns carry after performing (*res) = a - b; */                                                                                                    \
	uint64_t sub_ ## large_uint(large_uint* res, large_uint a, large_uint b);                                                                               \
                                                                                                                                                            \
	/* returns a number with only lowset significant n bits set */                                                                                          \
	/* this function can be used to build bit masks */                                                                                                      \
	/* returns ((1 << n) - 1) */                                                                                                                            \
	large_uint get_bitmask_lower_n_bits_set_ ## large_uint(uint32_t n);                                                                                     \
                                                                                                                                                            \
	/* res will be set with addition (a + b), on success (i.e. return 1) */                                                                                 \
	/* failure happens in case of an overflow OR if the result is greater than or equal to max_limit (max_limit is checked only if it is non zero) */       \
	int add_overflow_safe_ ## large_uint(large_uint* res, large_uint a, large_uint b, large_uint max_limit);                                                \
                                                                                                                                                            \
	/* res will be set with subtraction, on success (i.e. return 1) */                                                                                      \
	/* failure happens in case of an underflow, when (a < b) */                                                                                             \
	int sub_underflow_safe_ ## large_uint(large_uint* res, large_uint a, large_uint b);                                                                     \
                                                                                                                                                            \
	/* the product of a and b, i.e. (a * b) -> this value is 2 lage_uints wide */                                                                           \
	/* the lower half of the result is stored in res, while the upper half is returned at the return value */                                               \
	large_uint mul_ ## large_uint(large_uint* res, large_uint a, large_uint b);                                                                             \
                                                                                                                                                            \
	/* divides dividend by divisor, and returns remainder and sets the quotient to the pointer */                                                           \
	/* there is not limb wise division, this function performs a sequential binary division (restoring shift-substract algorithm) */                        \
	/* it is your duty to ensure that the divisor is not 0 */                                                                                               \
	large_uint div_ ## large_uint(large_uint* quotient, large_uint dividend, large_uint divisor);                                                           \
                                                                                                                                                            \
	/* find gcd of two numbers */                                                                                                                           \
    large_uint gcd_ ## large_uint(large_uint a, large_uint b);                                                                                              \
                                                                                                                                                            \
	/* returns true, if the given large_uint, can fit on a single uint64_t, the value will be set with the value of a */                                    \
	/* else a 0 (false) is returned, with value unset */                                                                                                    \
	int cast_to_uint64_from_ ## large_uint(uint64_t* value, large_uint a);                                                                                  \
                                                                                                                                                            \
	/* serialize and deserialize large_uint-s */                                                                                                            \
	void serialize_ ## large_uint(void* bytes, uint32_t bytes_size, large_uint l);                                                                          \
	large_uint deserialize_ ## large_uint(const char* bytes, uint32_t bytes_size);                                                                          \
                                                                                                                                                            \
	/* print large_uint */                                                                                                                                  \
	void print_ ## large_uint(large_uint l);                                                                                                                \
	/* print large_uint */                                                                                                                                  \
	void sprint_ ## large_uint(char* dest, large_uint l);                                                                                                   \
                                                                                                                                                            \
	/* serialize large_uint as decimal, into res, you must ensure that res is large enough */                                                               \
	uint32_t serialize_to_decimal_ ## large_uint(char* res, large_uint l);                                                                                  \
/* declarations complete */



#define definitions_large_uint(large_uint, LARGE_UINT_LIMBS_COUNT)                                                                                          \
                                                                                                                                                            \
	uint32_t get_max_bytes_ ## large_uint()                                                                                                                 \
	{                                                                                                                                                       \
		return (LARGE_UINT_LIMBS_COUNT * BYTES_PER_LIMB);                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint32_t get_bit_width_ ## large_uint()                                                                                                                 \
	{                                                                                                                                                       \
		return (LARGE_UINT_LIMBS_COUNT * BITS_PER_LIMB);                                                                                                    \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_ ## large_uint(uint64_t val)                                                                                                             \
	{                                                                                                                                                       \
		return ((large_uint){.limbs = {val}});                                                                                                              \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_0_ ## large_uint()                                                                                                                       \
	{                                                                                                                                                       \
		return get_ ## large_uint(0);                                                                                                                       \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_1_ ## large_uint()                                                                                                                       \
	{                                                                                                                                                       \
		return get_ ## large_uint(1);                                                                                                                       \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_min_ ## large_uint()                                                                                                                     \
	{                                                                                                                                                       \
		return get_0_ ## large_uint();                                                                                                                      \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_max_ ## large_uint()                                                                                                                     \
	{                                                                                                                                                       \
		return bitwise_not_ ## large_uint(get_0_ ## large_uint());                                                                                          \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int get_bit_from_ ## large_uint(large_uint a, uint32_t bit_index)                                                                                       \
	{                                                                                                                                                       \
		if(bit_index >= get_bit_width_ ## large_uint())                                                                                                     \
			return 0;                                                                                                                                       \
		return (a.limbs[bit_index / BITS_PER_LIMB] >> (bit_index % BITS_PER_LIMB)) & UINT64_C(1);                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int set_bit_in_ ## large_uint(large_uint* res, uint32_t bit_index)                                                                                      \
	{                                                                                                                                                       \
		if(bit_index >= get_bit_width_ ## large_uint())                                                                                                     \
			return 0;                                                                                                                                       \
		res->limbs[bit_index / BITS_PER_LIMB] |= (UINT64_C(1) << (bit_index % BITS_PER_LIMB));                                                              \
		return 1;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int reset_bit_in_ ## large_uint(large_uint* res, uint32_t bit_index)                                                                                    \
	{                                                                                                                                                       \
		if(bit_index >= get_bit_width_ ## large_uint())                                                                                                     \
			return 0;                                                                                                                                       \
		res->limbs[bit_index / BITS_PER_LIMB] &= (~(UINT64_C(1) << (bit_index % BITS_PER_LIMB)));                                                           \
		return 1;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint8_t get_byte_from_ ## large_uint(large_uint a, uint32_t byte_index)                                                                                 \
	{                                                                                                                                                       \
		if(byte_index >= get_max_bytes_ ## large_uint())                                                                                                    \
			return 0;                                                                                                                                       \
		return (a.limbs[byte_index / BYTES_PER_LIMB] >> ((byte_index % BYTES_PER_LIMB) * CHAR_BIT));                                                        \
	}                                                                                                                                                       \
                                                                                                                                                           	\
	int set_byte_in_ ## large_uint(large_uint* res, uint32_t byte_index, uint8_t byte)                                                                      \
	{                                                                                                                                                       \
		if(byte_index >= get_max_bytes_ ## large_uint())                                                                                                    \
			return 0;                                                                                                                                       \
		res->limbs[byte_index / BYTES_PER_LIMB] &= ~(UINT64_C(0xff) << ((byte_index % BYTES_PER_LIMB) * CHAR_BIT));                                         \
		res->limbs[byte_index / BYTES_PER_LIMB] |= (((uint64_t)(byte)) << ((byte_index % BYTES_PER_LIMB) * CHAR_BIT));                                      \
		return 1;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint bitwise_not_ ## large_uint(large_uint a)                                                                                                     \
	{                                                                                                                                                       \
		large_uint res;                                                                                                                                     \
		for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)                                                                                                \
			res.limbs[i] = ~a.limbs[i];                                                                                                                     \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint bitwise_and_ ## large_uint(large_uint a, large_uint b)                                                                                       \
	{                                                                                                                                                       \
		large_uint res;                                                                                                                                     \
		for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)                                                                                                \
			res.limbs[i] = (a.limbs[i] & b.limbs[i]);                                                                                                       \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint bitwise_or_ ## large_uint(large_uint a, large_uint b)                                                                                        \
	{                                                                                                                                                       \
		large_uint res;                                                                                                                                     \
		for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)                                                                                                \
			res.limbs[i] = (a.limbs[i] | b.limbs[i]);                                                                                                       \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint bitwise_xor_ ## large_uint(large_uint a, large_uint b)                                                                                       \
	{                                                                                                                                                       \
		large_uint res;                                                                                                                                     \
		for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)                                                                                                \
			res.limbs[i] = (a.limbs[i] ^ b.limbs[i]);                                                                                                       \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint left_shift_ ## large_uint(large_uint a, uint32_t s)                                                                                          \
	{                                                                                                                                                       \
		/* shifting by more than or equal to get_bit_width_ ## large_uint() shifts all bits out, making result 0 */                                         \
		if(s >= get_bit_width_ ## large_uint())                                                                                                             \
			return get_0_ ## large_uint();                                                                                                                  \
                                                                                                                                                            \
		large_uint res = get_0_ ## large_uint();                                                                                                            \
                                                                                                                                                            \
		/* bit index into a to move from = a_i */                                                                                                           \
		/* bit index into res to move to = r_i */                                                                                                           \
		uint32_t a_i = 0;                                                                                                                                   \
		uint32_t r_i = s; /* s is the left shift amount */                                                                                                  \
                                                                                                                                                            \
		while(a_i < get_bit_width_ ## large_uint() && r_i < get_bit_width_ ## large_uint())                                                                 \
		{                                                                                                                                                   \
			uint32_t bits_copied = copy_limb_bits(res.limbs, r_i, a.limbs, a_i, LARGE_UINT_LIMBS_COUNT);                                                    \
                                                                                                                                                            \
			/* increment both indices by the amount of bits copied */                                                                                       \
			a_i += bits_copied;                                                                                                                             \
			r_i += bits_copied;                                                                                                                             \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint right_shift_ ## large_uint(large_uint a, uint32_t s)                                                                                         \
	{                                                                                                                                                       \
		/* shifting by more than or equal to get_bit_width_ ## large_uint() shifts all bits out, making result 0 */                                         \
		if(s >= get_bit_width_ ## large_uint())                                                                                                             \
			return get_0_ ## large_uint();                                                                                                                  \
                                                                                                                                                            \
		large_uint res = get_0_ ## large_uint();                                                                                                            \
                                                                                                                                                            \
		/* bit index into a to move from = a_i */                                                                                                           \
		/* bit index into res to move to = r_i */                                                                                                           \
		uint32_t a_i = s; /* s is the right shift amount */                                                                                                 \
		uint32_t r_i = 0;                                                                                                                                   \
                                                                                                                                                            \
		while(a_i < get_bit_width_ ## large_uint() && r_i < get_bit_width_ ## large_uint())                                                                 \
		{                                                                                                                                                   \
			uint32_t bits_copied = copy_limb_bits(res.limbs, r_i, a.limbs, a_i, LARGE_UINT_LIMBS_COUNT);                                                    \
                                                                                                                                                            \
			/* increment both indices by the amount of bits copied */                                                                                       \
			a_i += bits_copied;                                                                                                                             \
			r_i += bits_copied;                                                                                                                             \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int compare_ ## large_uint(large_uint a, large_uint b)                                                                                                  \
	{                                                                                                                                                       \
		int res = 0;                                                                                                                                        \
		for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0 && res == 0;)                                                                                        \
		{                                                                                                                                                   \
			i--;                                                                                                                                            \
			res = compare_numbers(a.limbs[i], b.limbs[i]);                                                                                                  \
		}                                                                                                                                                   \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int are_equal_ ## large_uint(large_uint a, large_uint b)                                                                                                \
	{                                                                                                                                                       \
		return compare_ ## large_uint(a, b) == 0;                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int is_zero_ ## large_uint(large_uint a)                                                                                                                \
	{                                                                                                                                                       \
		return compare_ ## large_uint(a, get_0_ ## large_uint()) == 0;                                                                                      \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint64_t add_with_carry_ ## large_uint(large_uint* res, large_uint a, large_uint b, uint64_t carry_in)                                                  \
	{                                                                                                                                                       \
		uint64_t carry = carry_in;                                                                                                                          \
		for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)                                                                                                \
			carry = add_limbs_with_carry(&(res->limbs[i]), a.limbs[i], b.limbs[i], carry);                                                                  \
		return carry;                                                                                                                                       \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint64_t add_ ## large_uint(large_uint* res, large_uint a, large_uint b)                                                                                \
	{                                                                                                                                                       \
		return add_with_carry_ ## large_uint(res, a, b, 0);                                                                                                 \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint64_t sub_ ## large_uint(large_uint* res, large_uint a, large_uint b)                                                                                \
	{                                                                                                                                                       \
		return add_with_carry_ ## large_uint(res, a, bitwise_not_ ## large_uint(b), 1);                                                                     \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint get_bitmask_lower_n_bits_set_ ## large_uint(uint32_t n)                                                                                      \
	{                                                                                                                                                       \
		large_uint res;                                                                                                                                     \
		sub_ ## large_uint(&res, left_shift_ ## large_uint(get_1_ ## large_uint(), n), get_1_ ## large_uint());                                             \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int add_overflow_safe_ ## large_uint(large_uint* res, large_uint a, large_uint b, large_uint max_limit)                                                 \
	{                                                                                                                                                       \
		large_uint res_temp;                                                                                                                                \
		if(add_ ## large_uint(&res_temp, a, b)) /* carry out implies overflow */                                                                            \
			return 0;                                                                                                                                       \
                                                                                                                                                            \
		/* if max_limit is not 0, i.e. max_limit exists, and res_temp >= max_limit, then fail */                                                            \
		if(compare_ ## large_uint(max_limit, get_0_ ## large_uint()) != 0 && compare_ ## large_uint(res_temp, max_limit) >= 0)                              \
			return 0;                                                                                                                                       \
                                                                                                                                                            \
		(*res) = res_temp;                                                                                                                                  \
		return 1;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int sub_underflow_safe_ ## large_uint(large_uint* res, large_uint a, large_uint b)                                                                      \
	{                                                                                                                                                       \
		/* can not subtract if a < b, underflow condition */                                                                                                \
		if(compare_ ## large_uint(a, b) < 0)                                                                                                                \
			return 0;                                                                                                                                       \
                                                                                                                                                            \
		sub_ ## large_uint(res, a, b);                                                                                                                      \
		return 1;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint mul_ ## large_uint(large_uint* res, large_uint a, large_uint b)                                                                              \
	{                                                                                                                                                       \
		(*res) = get_0_ ## large_uint();                                                                                                                    \
		large_uint res2 = get_0_ ## large_uint();                                                                                                           \
                                                                                                                                                            \
		for(uint32_t ai = 0; ai < LARGE_UINT_LIMBS_COUNT; ai++)                                                                                             \
		{                                                                                                                                                   \
			/* intermediate product of multiplying ai-th limb with b, with all of it's power */                                                             \
			large_uint intermediate[2] = {get_0_ ## large_uint(), get_0_ ## large_uint()};                                                                  \
                                                                                                                                                            \
			uint64_t carry = 0;                                                                                                                             \
			for(uint32_t bi = 0; bi < LARGE_UINT_LIMBS_COUNT; bi++)                                                                                         \
			{                                                                                                                                               \
				uint64_t prod = 0;                                                                                                                          \
				carry = mul_limbs_with_carry(&prod, a.limbs[ai], b.limbs[bi], carry);                                                                       \
                                                                                                                                                            \
				/* calculate limb power for the positon of the prod */                                                                                      \
				{                                                                                                                                           \
					uint32_t power_pos = ai + bi;                                                                                                           \
					intermediate[power_pos / LARGE_UINT_LIMBS_COUNT].limbs[power_pos % LARGE_UINT_LIMBS_COUNT] = prod;                                      \
				}                                                                                                                                           \
			}                                                                                                                                               \
                                                                                                                                                            \
			/* calculate limb power for the position of the carry */                                                                                        \
			{                                                                                                                                               \
				uint32_t power_pos = ai + LARGE_UINT_LIMBS_COUNT;                                                                                           \
				intermediate[power_pos / LARGE_UINT_LIMBS_COUNT].limbs[power_pos % LARGE_UINT_LIMBS_COUNT] = carry;                                         \
			}                                                                                                                                               \
                                                                                                                                                            \
			carry = add_with_carry_ ## large_uint(res, intermediate[0], (*res), 0);                                                                         \
			add_with_carry_ ## large_uint(&res2, intermediate[1], res2, carry);                                                                             \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res2;                                                                                                                                        \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint div_ ## large_uint(large_uint* quotient, large_uint dividend, large_uint divisor)                                                            \
	{                                                                                                                                                       \
		/* 0 initialize, the return values */                                                                                                               \
		(*quotient) = get_0_ ## large_uint();                                                                                                               \
		large_uint remainder = get_0_ ## large_uint();                                                                                                      \
                                                                                                                                                            \
		/* now we just need to perform this loop for bit count of large_uint */                                                                             \
		for(uint32_t i = 0; i < get_bit_width_ ## large_uint(); i++)                                                                                        \
		{                                                                                                                                                   \
			/* shift concatenation of remainer:dividend by 1 bit */                                                                                         \
			remainder = left_shift_ ## large_uint(remainder, 1);                                                                                            \
			if(get_bit_from_ ## large_uint(dividend, get_bit_width_ ## large_uint() - 1))                                                                   \
				set_bit_in_ ## large_uint(&remainder, 0);                                                                                                   \
			dividend = left_shift_ ## large_uint(dividend, 1);                                                                                              \
                                                                                                                                                            \
			/* left shift quotient by 1 bit */                                                                                                              \
			(*quotient) = left_shift_ ## large_uint((*quotient), 1);                                                                                        \
                                                                                                                                                            \
			/* if now the remainder is greater than equal to divisor, then you need to set the corresponding last bit in quotient to 0 */                   \
			/* and substract divisor from remainder */                                                                                                      \
			if(compare_ ## large_uint(remainder, divisor) >= 0)                                                                                             \
			{                                                                                                                                               \
				sub_ ## large_uint(&remainder, remainder, divisor);                                                                                         \
				set_bit_in_ ## large_uint(quotient, 0);                                                                                                     \
			}                                                                                                                                               \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return remainder;                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint gcd_ ## large_uint(large_uint a, large_uint b)                                                                                               \
	{                                                                                                                                                       \
		/* classic euler gcd algorithm */                                                                                                                   \
		while(!is_zero_ ## large_uint(b))                                                                                                                   \
		{                                                                                                                                                   \
			large_uint q;                                                                                                                                   \
			large_uint r = div_ ## large_uint(&q, a, b);                                                                                                    \
			a = b;                                                                                                                                          \
			b = r;                                                                                                                                          \
		}                                                                                                                                                   \
		return a;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	int cast_to_uint64_from_ ## large_uint(uint64_t* value, large_uint a)                                                                                   \
	{                                                                                                                                                       \
		uint32_t limbs_required = LARGE_UINT_LIMBS_COUNT;                                                                                                   \
		while(limbs_required > 0 && a.limbs[limbs_required-1] == 0)                                                                                         \
			limbs_required--;                                                                                                                               \
                                                                                                                                                            \
		if(limbs_required <= 1)                                                                                                                             \
		{                                                                                                                                                   \
			(*value) = a.limbs[0];                                                                                                                          \
			return 1;                                                                                                                                       \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return 0;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	void serialize_ ## large_uint(void* bytes, uint32_t bytes_size, large_uint l)                                                                           \
	{                                                                                                                                                       \
		bytes_size = min(bytes_size, get_max_bytes_ ## large_uint());                                                                                       \
                                                                                                                                                            \
		uint32_t limb_index = 0;                                                                                                                            \
		while(bytes_size > 0)                                                                                                                               \
		{                                                                                                                                                   \
			uint32_t bytes_to_write = min(BYTES_PER_LIMB, bytes_size);                                                                                      \
                                                                                                                                                            \
			serialize_uint64(bytes, bytes_to_write, l.limbs[limb_index++]);                                                                                 \
                                                                                                                                                            \
			bytes_size -= bytes_to_write;                                                                                                                   \
			bytes += bytes_to_write;                                                                                                                        \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	large_uint deserialize_ ## large_uint(const char* bytes, uint32_t bytes_size)                                                                           \
	{                                                                                                                                                       \
		large_uint res = {};                                                                                                                                \
                                                                                                                                                            \
		bytes_size = min(bytes_size, get_max_bytes_ ## large_uint());                                                                                       \
                                                                                                                                                            \
		uint32_t limb_index = 0;                                                                                                                            \
		while(bytes_size > 0)                                                                                                                               \
		{                                                                                                                                                   \
			uint32_t bytes_to_read = min(BYTES_PER_LIMB, bytes_size);                                                                                       \
                                                                                                                                                            \
			res.limbs[limb_index++] = deserialize_uint64(bytes, bytes_to_read);                                                                             \
                                                                                                                                                            \
			bytes_size -= bytes_to_read;                                                                                                                    \
			bytes += bytes_to_read;                                                                                                                         \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	void print_ ## large_uint(large_uint l)                                                                                                                 \
	{                                                                                                                                                       \
		for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)                                                                                                    \
		{                                                                                                                                                   \
			i--;                                                                                                                                            \
			printf("%016"PRIx64, l.limbs[i]);                                                                                                               \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	void sprint_ ## large_uint(char* dest, large_uint l)                                                                                                    \
	{                                                                                                                                                       \
		for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)                                                                                                    \
		{                                                                                                                                                   \
			i--;                                                                                                                                            \
			sprintf(dest, "%016"PRIx64, l.limbs[i]);                                                                                                        \
			dest += 16;                                                                                                                                     \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	uint32_t serialize_to_decimal_ ## large_uint(char* res, large_uint l)                                                                                   \
	{                                                                                                                                                       \
		uint32_t res_size = 0;                                                                                                                              \
                                                                                                                                                            \
		while(!is_zero_ ## large_uint(l))                                                                                                                   \
		{                                                                                                                                                   \
			large_uint d = div_ ## large_uint(&l, l, get_ ## large_uint(10));                                                                               \
			res[res_size++] = ('0' + d.limbs[0]);                                                                                                           \
		}                                                                                                                                                   \
                                                                                                                                                            \
		if(res_size == 0)                                                                                                                                   \
			res[res_size++] = '0';                                                                                                                          \
                                                                                                                                                            \
		for(uint32_t i = 0; i < res_size / 2; i++)                                                                                                          \
		{                                                                                                                                                   \
			char t = res[i];                                                                                                                                \
			res[i] = res[res_size - 1 - i];                                                                                                                 \
			res[res_size - 1 - i] = t;                                                                                                                      \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res_size;                                                                                                                                    \
	}                                                                                                                                                       \
/* definitions complete */

#endif