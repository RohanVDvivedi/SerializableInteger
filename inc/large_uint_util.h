#ifndef LARGE_UINT_UTIL_H
#define LARGE_UINT_UTIL_H

#include<stdint.h>

// number of bits in each limb of the large_uint
// this number is expected and assumed to be a multiple of 2
#define BITS_PER_LIMB 			(sizeof(uint64_t) * CHAR_BIT)

#define BITS_PER_HALF_LIMB		(BITS_PER_LIMB / 2)

// returns carry, and summation in res
uint64_t add_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

// the operation performed here is (a * b) + carry_in
// it returns carry_out and result in res
uint64_t mul_limbs_with_carry(uint64_t* res, uint64_t a, uint64_t b, uint64_t carry_in);

#endif