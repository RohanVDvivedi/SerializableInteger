#ifndef LARGE_UINT_UTIL_H
#define LARGE_UINT_UTIL_H

#include<stdint.h>

#define BYTES_PER_LIMB			(sizeof(uint64_t))

#define BITS_PER_LIMB 			(BYTES_PER_LIMB * CHAR_BIT)

#define BITS_PER_HALF_LIMB		(BITS_PER_LIMB / 2)

// returns bits copied, will always return a value <= BITS_PER_LIMB
// it will attempt to copy bits from a to res
// i.e. res[r_i : r_i + BITS_PER_LIMB - 1] = a[a_i : a_i + BITS_PER_LIMB - 1]
static inline uint32_t copy_limb_bits(uint64_t* res, uint32_t r_i, const uint64_t* a, uint32_t a_i, uint32_t limbs_count);

// returns carry, and summation in res
static inline uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

// the operation performed here is (a * b) + carry_in
// it returns carry_out and result in res
static inline uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

#include<cutlery/cutlery_math.h>

// inline implementations

static inline uint32_t copy_limb_bits(uint64_t* res, uint32_t r_i, const uint64_t* a, uint32_t a_i, uint32_t limbs_count)
{
	// can not copy any bits, if their first indices are out of range
	if(a_i >= (limbs_count * BITS_PER_LIMB) || r_i >= (limbs_count * BITS_PER_LIMB))
		return 0;

	uint64_t m = 0;

	uint32_t bits_copied = BITS_PER_LIMB;

	// copy from a into m
	{
		m |= (a[(a_i / BITS_PER_LIMB)] >> (a_i % BITS_PER_LIMB));

		if(((a_i % BITS_PER_LIMB) > 0) && (((a_i / BITS_PER_LIMB)) + 1) < limbs_count)
			m |= (a[(a_i / BITS_PER_LIMB) + 1] << (BITS_PER_LIMB - (a_i % BITS_PER_LIMB)));
		else
			bits_copied = min(bits_copied, (BITS_PER_LIMB - (a_i % BITS_PER_LIMB)));
	}

	// copy from m to res
	{
		res[(r_i / BITS_PER_LIMB)] &= ~(UINT64_MAX << (r_i % BITS_PER_LIMB));
		res[(r_i / BITS_PER_LIMB)] |= (m << (r_i % BITS_PER_LIMB));

		if(((r_i % BITS_PER_LIMB) > 0) && (((r_i / BITS_PER_LIMB)) + 1) < limbs_count)
		{
			res[(r_i / BITS_PER_LIMB) + 1] &= ~(UINT64_MAX >> (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
			res[(r_i / BITS_PER_LIMB) + 1] |= (m >> (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
		}
		else
			bits_copied = min(bits_copied, (BITS_PER_LIMB - (r_i % BITS_PER_LIMB)));
	}

	return bits_copied;
}

static inline uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in)
{
	(*res) = a + b + carry_in;
	uint64_t carry_out = will_unsigned_sum_overflow(uint64_t, a, b) + will_unsigned_sum_overflow(uint64_t, a + b, carry_in);
	return carry_out;
}

static inline uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in)
{
	uint64_t a_0 = a & ((UINT64_C(1) << BITS_PER_HALF_LIMB) - UINT64_C(1)); // upper 32 bits of a
	uint64_t a_1 = a >> BITS_PER_HALF_LIMB; // lower 32 bits of a

	// similarly extract upper and lower 32 bits of b
	uint64_t b_0 = b & ((UINT64_C(1) << BITS_PER_HALF_LIMB) - UINT64_C(1));
	uint64_t b_1 = b >> BITS_PER_HALF_LIMB;

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
		uint64_t ct = will_unsigned_sum_overflow(uint64_t, (*res), (temp << BITS_PER_HALF_LIMB));
		(*res) += (temp << BITS_PER_HALF_LIMB);
		carry_out += ((temp >> BITS_PER_HALF_LIMB) + ct);
	}

	// process this cross product
	temp = a_1 * b_0;
	{
		uint64_t ct = will_unsigned_sum_overflow(uint64_t, (*res), (temp << BITS_PER_HALF_LIMB));
		(*res) += (temp << BITS_PER_HALF_LIMB);
		carry_out += ((temp >> BITS_PER_HALF_LIMB) + ct);
	}

	return carry_out;
}

#endif