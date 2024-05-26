#include<large_uint.h>

#include<large_uint_util.h>

#include<cutlery_math.h>

uint32_t get_max_bytes_large_uint()
{
	return (LARGE_UINT_LIMBS_COUNT * sizeof(uint64_t));
}

uint32_t get_bit_width_large_uint()
{
	return (LARGE_UINT_LIMBS_COUNT * BITS_PER_LIMB);
}

large_uint get_large_uint(uint64_t val)
{
	return ((large_uint){.limbs = {val}});
}

large_uint get_0_large_uint()
{
	return get_large_uint(0);
}

large_uint get_1_large_uint()
{
	return get_large_uint(1);
}

large_uint get_min_large_uint()
{
	return get_0_large_uint();
}

large_uint get_max_large_uint()
{
	return bitwise_not_large_uint(get_0_large_uint());
}

int get_bit_from_large_uint(large_uint a, uint32_t bit_index)
{
	if(bit_index >= get_bit_width_large_uint())
		return 0;
	return (a.limbs[bit_index / BITS_PER_LIMB] >> (bit_index % BITS_PER_LIMB)) & UINT64_C(1);
}

int set_bit_in_large_uint(large_uint* res, uint32_t bit_index)
{
	if(bit_index >= get_bit_width_large_uint())
		return 0;
	res->limbs[bit_index / BITS_PER_LIMB] |= (UINT64_C(1) << (bit_index % BITS_PER_LIMB));
	return 1;
}

int reset_bit_in_large_uint(large_uint* res, uint32_t bit_index)
{
	if(bit_index >= get_bit_width_large_uint())
		return 0;
	res->limbs[bit_index / BITS_PER_LIMB] &= (~(UINT64_C(1) << (bit_index % BITS_PER_LIMB)));
	return 1;
}

large_uint bitwise_not_large_uint(large_uint a)
{
	large_uint res;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		res.limbs[i] = ~a.limbs[i];
	return res;
}

large_uint bitwise_and_large_uint(large_uint a, large_uint b)
{
	large_uint res;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		res.limbs[i] = (a.limbs[i] & b.limbs[i]);
	return res;
}

large_uint bitwise_or_large_uint(large_uint a, large_uint b)
{
	large_uint res;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		res.limbs[i] = (a.limbs[i] | b.limbs[i]);
	return res;
}

large_uint bitwise_xor_large_uint(large_uint a, large_uint b)
{
	large_uint res;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		res.limbs[i] = (a.limbs[i] ^ b.limbs[i]);
	return res;
}

// returns bits copied, will always return a value <= BITS_PER_LIMB
// it will attempt to copy bits from a to res
// i.e. res[r_i : r_i + BITS_PER_LIMB - 1] = a[a_i : a_i + BITS_PER_LIMB - 1]
static uint32_t copy_limb_bits(large_uint* res, uint32_t r_i, large_uint a, uint32_t a_i)
{
	// can not copy any bits, if their first indices are out of range
	if(a_i >= get_bit_width_large_uint() || r_i >= get_bit_width_large_uint())
		return 0;

	uint64_t m = 0;

	uint32_t bits_copied = BITS_PER_LIMB;

	// copy from a into m
	{
		m |= (a.limbs[(a_i / BITS_PER_LIMB)] >> (a_i % BITS_PER_LIMB));

		if(((a_i % BITS_PER_LIMB) > 0) && (((a_i / BITS_PER_LIMB)) + 1) < LARGE_UINT_LIMBS_COUNT)
			m |= (a.limbs[(a_i / BITS_PER_LIMB) + 1] << (BITS_PER_LIMB - (a_i % BITS_PER_LIMB)));
		else
			bits_copied = min(bits_copied, (BITS_PER_LIMB - (a_i % BITS_PER_LIMB)));
	}

	// copy from m to res
	{
		res->limbs[(r_i / BITS_PER_LIMB)] &= ~(UINT64_MAX << (r_i % BITS_PER_LIMB));
		res->limbs[(r_i / BITS_PER_LIMB)] |= (m << (r_i % BITS_PER_LIMB));

		if(((r_i % BITS_PER_LIMB) > 0) && (((r_i / BITS_PER_LIMB)) + 1) < LARGE_UINT_LIMBS_COUNT)
		{
			res->limbs[(r_i / BITS_PER_LIMB) + 1] &= ~(UINT64_MAX >> (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
			res->limbs[(r_i / BITS_PER_LIMB) + 1] |= (m >> (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
		}
		else
			bits_copied = min(bits_copied, (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
	}

	return bits_copied;
}

large_uint left_shift_large_uint(large_uint a, uint32_t s)
{
	// shifting by more than or equal to get_bit_width_large_uint() shifts all bits out, making result 0
	if(s >= get_bit_width_large_uint())
		return get_0_large_uint();

	large_uint res = get_0_large_uint();

	// bit index into a to move from = a_i
	// bit index into res to move to = r_i
	uint32_t a_i = 0;
	uint32_t r_i = s; // s is the left shift amount

	while(a_i < get_bit_width_large_uint() && r_i < get_bit_width_large_uint())
	{
		uint32_t bits_copied = copy_limb_bits(&res, r_i, a, a_i);

		// increment both indices by the amount of bits copied
		a_i += bits_copied;
		r_i += bits_copied;
	}

	return res;
}

large_uint right_shift_large_uint(large_uint a, uint32_t s)
{
	// shifting by more than or equal to get_bit_width_large_uint() shifts all bits out, making result 0
	if(s >= get_bit_width_large_uint())
		return get_0_large_uint();

	large_uint res = get_0_large_uint();

	// bit index into a to move from = a_i
	// bit index into res to move to = r_i
	uint32_t a_i = s; // s is the right shift amount
	uint32_t r_i = 0;

	while(a_i < get_bit_width_large_uint() && r_i < get_bit_width_large_uint())
	{
		uint32_t bits_copied = copy_limb_bits(&res, r_i, a, a_i);

		// increment both indices by the amount of bits copied
		a_i += bits_copied;
		r_i += bits_copied;
	}

	return res;
}

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

int is_zero_large_uint(large_uint a)
{
	return compare_large_uint(a, get_0_large_uint()) == 0;
}

uint64_t add_with_carry_large_uint(large_uint* res, large_uint a, large_uint b, uint64_t carry_in)
{
	uint64_t carry = carry_in;
	for(uint32_t i = 0; i < LARGE_UINT_LIMBS_COUNT; i++)
		carry = add_limbs_with_carry(&(res->limbs[i]), a.limbs[i], b.limbs[i], carry);
	return carry;
}

uint64_t add_large_uint(large_uint* res, large_uint a, large_uint b)
{
	return add_with_carry_large_uint(res, a, b, 0);
}

uint64_t sub_large_uint(large_uint* res, large_uint a, large_uint b)
{
	return add_with_carry_large_uint(res, a, bitwise_not_large_uint(b), 1);
}

large_uint get_bitmask_lower_n_bits_set_large_uint(uint32_t n)
{
	large_uint res;
	sub_large_uint(&res, left_shift_large_uint(get_1_large_uint(), n), get_1_large_uint());
	return res;
}

int add_overflow_safe_large_uint(large_uint* res, large_uint a, large_uint b, large_uint max_limit)
{
	large_uint res_temp;
	if(add_large_uint(&res_temp, a, b)) // carry out implies overflow
		return 0;

	// if max_limit is not 0, i.e. max_limit exists, and res_temp >= max_limit, then fail
	if(compare_large_uint(max_limit, get_0_large_uint()) != 0 && compare_large_uint(res_temp, max_limit) >= 0)
		return 0;

	(*res) = res_temp;
	return 1;
}

int sub_underflow_safe_large_uint(large_uint* res, large_uint a, large_uint b)
{
	// can not subtract if a < b, underflow condition
	if(compare_large_uint(a, b) < 0)
		return 0;

	sub_large_uint(res, a, b);
	return 1;
}

large_uint mul_large_uint(large_uint* res, large_uint a, large_uint b)
{
	(*res) = get_0_large_uint();
	large_uint res2 = get_0_large_uint();

	for(uint32_t ai = 0; ai < LARGE_UINT_LIMBS_COUNT; ai++)
	{
		// intermediate product of multiplying ai-th limb with b, with all of it's power
		large_uint intermediate[2] = {get_0_large_uint(), get_0_large_uint()};

		uint64_t carry = 0;
		for(uint32_t bi = 0; bi < LARGE_UINT_LIMBS_COUNT; bi++)
		{
			uint64_t prod = 0;
			carry = mul_limbs_with_carry(&prod, a.limbs[ai], b.limbs[bi], carry);

			// calculate limb power for the positon of the prod
			{
				uint32_t power_pos = ai + bi;
				intermediate[power_pos / LARGE_UINT_LIMBS_COUNT].limbs[power_pos % LARGE_UINT_LIMBS_COUNT] = prod;
			}
		}

		// calculate limb power for the position of the carry
		{
			uint32_t power_pos = ai + LARGE_UINT_LIMBS_COUNT;
			intermediate[power_pos / LARGE_UINT_LIMBS_COUNT].limbs[power_pos % LARGE_UINT_LIMBS_COUNT] = carry;
		}

		carry = add_with_carry_large_uint(res, intermediate[0], (*res), 0);
		add_with_carry_large_uint(&res2, intermediate[1], res2, carry);
	}

	return res2;
}

large_uint div_large_uint(large_uint* quotient, large_uint dividend, large_uint divisor)
{
	// 0 initialize, the return values
	(*quotient) = get_0_large_uint();
	large_uint remainder = get_0_large_uint();

	// now we just need to perform this loop for bit count of large_uint
	for(uint32_t i = 0; i < get_bit_width_large_uint(); i++)
	{
		// shift concatenation of remainer:dividend by 1 bit
		remainder = left_shift_large_uint(remainder, 1);
		if(get_bit_from_large_uint(dividend, get_bit_width_large_uint() - 1))
			set_bit_in_large_uint(&remainder, 0);
		dividend = left_shift_large_uint(dividend, 1);

		// left shift quotient by 1 bit
		(*quotient) = left_shift_large_uint((*quotient), 1);

		// if now the remainder is greater than equal to divisor, then you need to set the corresponding last bit in quotient to 0
		// and substract divisor from remainder
		if(compare_large_uint(remainder, divisor) >= 0)
		{
			sub_large_uint(&remainder, remainder, divisor);
			set_bit_in_large_uint(quotient, 0);
		}
	}

	return remainder;
}

int cast_to_uint64_from_large_uint(uint64_t* value, large_uint a)
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

#include<serial_int.h>

void serialize_large_uint(void* bytes, uint32_t bytes_size, large_uint l)
{
	bytes_size = min(bytes_size, get_max_bytes_large_uint());

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

	bytes_size = min(bytes_size, get_max_bytes_large_uint());

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

#include<stdio.h>

void print_large_uint(large_uint l)
{
	for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)
	{
		i--;
		printf("%016"PRIx64, l.limbs[i]);
	}
}