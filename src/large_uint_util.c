#include<large_uint_util.h>

#include<cutlery_math.h>

uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in)
{
	(*res) = a + b + carry_in;
	uint64_t carry_out = will_unsigned_sum_overflow(uint64_t, a, b) + will_unsigned_sum_overflow(uint64_t, a + b, carry_in);
	return carry_out;
}

uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in)
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