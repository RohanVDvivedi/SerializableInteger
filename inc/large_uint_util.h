#ifndef LARGE_UINT_UTIL_H
#define LARGE_UINT_UTIL_H

#include<stdint.h>

// number of bits in each limb of the large_uint
// this number is expected and assumed to be a multiple of 2
#define BITS_PER_LIMB 			(sizeof(uint64_t) * CHAR_BIT)

#define BITS_PER_HALF_LIMB		(BITS_PER_LIMB / 2)

// returns bits copied, will always return a value <= BITS_PER_LIMB
// it will attempt to copy bits from a to res
// i.e. res[r_i : r_i + BITS_PER_LIMB - 1] = a[a_i : a_i + BITS_PER_LIMB - 1]
uint32_t copy_limb_bits(uint64_t* res, uint32_t r_i, const uint64_t* a, uint32_t a_i, uint32_t limbs_count);

// returns carry, and summation in res
uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

// the operation performed here is (a * b) + carry_in
// it returns carry_out and result in res
uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

#endif