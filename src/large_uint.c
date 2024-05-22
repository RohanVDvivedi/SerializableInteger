#include<large_uint.h>

#include<cutlery_math.h>

int get_bit_from_large_uint(large_uint a, uint32_t bit_index)
{
	if(bit_index >= LARGE_UINT_BIT_WIDTH)
		return 0;
	return (a.limbs[bit_index / BITS_PER_LIMB] >> (bit_index % BITS_PER_LIMB)) & UINT64_C(1);
}

int set_bit_in_large_uint(large_uint* res, uint32_t bit_index)
{
	if(bit_index >= LARGE_UINT_BIT_WIDTH)
		return 0;
	res->limbs[bit_index / BITS_PER_LIMB] |= (UINT64_C(1) << (bit_index % BITS_PER_LIMB));
	return 1;
}

int reset_bit_in_large_uint(large_uint* res, uint32_t bit_index)
{
	if(bit_index >= LARGE_UINT_BIT_WIDTH)
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
	if(a_i >= LARGE_UINT_BIT_WIDTH || r_i >= LARGE_UINT_BIT_WIDTH)
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
	// shifting by more than or equal to LARGE_UINT_BIT_WIDTH shifts all bits out, making result 0
	if(s >= LARGE_UINT_BIT_WIDTH)
		return LARGE_UINT_ZERO;

	large_uint res = LARGE_UINT_ZERO;

	// bit index into a to move from = a_i
	// bit index into res to move to = r_i
	uint32_t a_i = 0;
	uint32_t r_i = s; // s is the left shift amount

	while(a_i < LARGE_UINT_BIT_WIDTH && r_i < LARGE_UINT_BIT_WIDTH)
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
	// shifting by more than or equal to LARGE_UINT_BIT_WIDTH shifts all bits out, making result 0
	if(s >= LARGE_UINT_BIT_WIDTH)
		return LARGE_UINT_ZERO;

	large_uint res = LARGE_UINT_ZERO;

	// bit index into a to move from = a_i
	// bit index into res to move to = r_i
	uint32_t a_i = s; // s is the right shift amount
	uint32_t r_i = 0;

	while(a_i < LARGE_UINT_BIT_WIDTH && r_i < LARGE_UINT_BIT_WIDTH)
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
	return compare_large_uint(a, LARGE_UINT_ZERO) == 0;
}

// returns carry, and summation in res
static uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in)
{
	(*res) = a + b + carry_in;
	uint64_t carry_out = will_unsigned_sum_overflow(uint64_t, a, b) + will_unsigned_sum_overflow(uint64_t, a + b, carry_in);
	return carry_out;
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

large_uint get_bitmask_lower_n_bits_set(uint32_t n)
{
	large_uint res;
	sub_large_uint(&res, left_shift_large_uint(LARGE_UINT_ONE, n), LARGE_UINT_ONE);
	return res;
}

int add_large_uint_overflow_safe(large_uint* res, large_uint a, large_uint b, large_uint max_limit)
{
	large_uint res_temp;
	if(add_large_uint(&res_temp, a, b)) // carry out implies overflow
		return 0;

	// if max_limit is not 0, i.e. max_limit exists, and res_temp >= max_limit, then fail
	if(compare_large_uint(max_limit, LARGE_UINT_MIN) != 0 && compare_large_uint(res_temp, max_limit) >= 0)
		return 0;

	(*res) = res_temp;
	return 1;
}

int sub_large_uint_underflow_safe(large_uint* res, large_uint a, large_uint b)
{
	// can not subtract if a < b, underflow condition
	if(compare_large_uint(a, b) < 0)
		return 0;

	sub_large_uint(res, a, b);
	return 1;
}

// the operation performed here is (a * b) + carry_in
// it returns carry_out and result in res
static uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry)
{
	uint64_t a_0 = a & ((UINT64_C(1) << 32) - UINT64_C(1)); // upper 32 bits of a
	uint64_t a_1 = a >> 32; // lower 32 bits of a

	// similarly extract upper and lower 32 bits of b
	uint64_t b_0 = b & ((UINT64_C(1) << 32) - UINT64_C(1));
	uint64_t b_1 = b >> 32;

	// a_0 and b_0's product will always go to res
	// a_1 and b_1's product will always go to carry_out
	(*res) = a_0 * b_0;
	uint64_t carry_out = a_1 * b_1;

	// add carry_in to the (carry_out, res) pair
	{
		carry_out += will_unsigned_sum_overflow(uint64_t, (*res), carry_in);
		(*res) += carry_in;
	}

	// process this cross product
	uint64_t temp = a_0 * b_1;
	{
		uint64_t ct = will_unsigned_sum_overflow(uint64_t, (*res), (temp << 32));
		r_0 += (temp << 32);
		r_1 += ((temp >> 32) + ct);
	}

	// process this cross product
	temp = a_1 * b_0;
	{
		uint64_t ct = will_unsigned_sum_overflow(uint64_t, (*res), (temp << 32));
		r_0 += (temp << 32);
		r_1 += ((temp >> 32) + ct);
	}

	return carry_out;
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
	for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)
	{
		i--;
		printf("%016"PRIx64, l.limbs[i]);
	}
}