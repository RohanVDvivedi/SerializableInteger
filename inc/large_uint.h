#ifndef LARGE_UINT_H
#define LARGE_UINT_H

#include<inttypes.h>

#include<cutlery_stds.h>

// number of bits in each limb of the large_uint
// this number is expected and assumed to be a multiple of 2
#define BITS_PER_LIMB 			(sizeof(uint64_t) * CHAR_BIT)

#define BITS_PER_HALF_LIMB		(BITS_PER_LIMB / 2)

// this can be any value, but 2 is just right for all practical purposes
// if you modify this, be sure to modify LARGE_UINT_MAX
#define LARGE_UINT_LIMBS_COUNT	2

// it is assumed in this library that LARGE_UINT_BIT_WIDTH fits in a 32 bit unsigned integer

typedef struct large_uint large_uint;
struct large_uint
{
	uint64_t limbs[LARGE_UINT_LIMBS_COUNT];
};

// number of maximum bytes of data in a large_uint
uint32_t get_max_bytes_large_uint();

// number of bits of data in a large_uint
uint32_t get_bit_width_large_uint();

// get a default uint64_t val valued large_uint
large_uint get_large_uint(uint64_t val);

// get zero and one values for a large_uint
large_uint get_0_large_uint();
large_uint get_1_large_uint();

// get min and max values for a large_uint
large_uint get_min_large_uint();
large_uint get_max_large_uint();

// gets a bit from large_uint
int get_bit_from_large_uint(large_uint a, uint32_t bit_index);

// set a bit in large_uint
int set_bit_in_large_uint(large_uint* res, uint32_t bit_index);

// reset a bit in large_uint
int reset_bit_in_large_uint(large_uint* res, uint32_t bit_index);

// returns ~a
large_uint bitwise_not_large_uint(large_uint a);

// returns a & b
large_uint bitwise_and_large_uint(large_uint a, large_uint b);

// returns a | b
large_uint bitwise_or_large_uint(large_uint a, large_uint b);

// returns a ^ b
large_uint bitwise_xor_large_uint(large_uint a, large_uint b);

// returns a << s
large_uint left_shift_large_uint(large_uint a, uint32_t s);

// returns a >> s
large_uint right_shift_large_uint(large_uint a, uint32_t s);

// if(a < b) returns -1
// else if(a == b) returns 0
// else if(a > b) returns 1
int compare_large_uint(large_uint a, large_uint b);

// returns a == b
int are_equal_large_uint(large_uint a, large_uint b);

// returns a == 0
int is_zero_large_uint(large_uint a);

// (*res) = a + b + carry and then returns carry
uint64_t add_with_carry_large_uint(large_uint* res, large_uint a, large_uint b, uint64_t carry_in);

// returns carry after performing (*res) = a + b;
uint64_t add_large_uint(large_uint* res, large_uint a, large_uint b);

// returns carry after performing (*res) = a - b;
uint64_t sub_large_uint(large_uint* res, large_uint a, large_uint b);

// returns a number with only lowset significant n bits set
// this function can be used to build bit masks
// returns ((1 << n) - 1)
large_uint get_bitmask_lower_n_bits_set(uint32_t n);

// res will be set with addition (a + b), on success (i.e. return 1)
// failure happens in case of an overflow OR if the result is greater than or equal to max_limit (max_limit is checked only if it is non zero)
int add_large_uint_overflow_safe(large_uint* res, large_uint a, large_uint b, large_uint max_limit);

// res will be set with subtraction, on success (i.e. return 1)
// failure happens in case of an underflow, when (a < b)
int sub_large_uint_underflow_safe(large_uint* res, large_uint a, large_uint b);

// the product of a and b, i.e. (a * b) -> this value is 2 lage_uints wide
// the lower half of the result is stored in res, while the upper half is returned at the return value
large_uint mul_large_uint(large_uint* res, large_uint a, large_uint b);

// divides dividend by divisor, and returns remainder and sets the quotient to the pointer
// there is not limb wise division, this function performs a sequential binary division (restoring shift-substract algorithm)
// it is your duty to ensure that the divisor is not 0
large_uint div_large_uint(large_uint* quotient, large_uint dividend, large_uint divisor);

// returns true, if the given large_uint, can fit on a single uint64_t, the value will be set with the value of a
// else a 0 (false) is returned, with value unset
int cast_large_uint_to_uint64(uint64_t* value, large_uint a);

// serialize and deserialize large_uint-s
void serialize_large_uint(void* bytes, uint32_t bytes_size, large_uint l);
large_uint deserialize_large_uint(const char* bytes, uint32_t bytes_size);

// print large_uint
void print_large_uint(large_uint l);

#endif