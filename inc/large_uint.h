#ifndef LARGE_UINT_H
#define LARGE_UINT_H

#include<inttypes.h>

#include<cutlery_stds.h>

// this can be any value, but 2 is just right for all practical purposes
// if you modify this, be sure to modify LARGE_UINT_MAX
#define LARGE_UINT_LIMBS_COUNT 2

#define LARGE_UINT_MAX_BYTES   (LARGE_UINT_LIMBS_COUNT * sizeof(uint64_t))

typedef struct large_uint large_uint;
struct large_uint
{
	uint64_t limbs[LARGE_UINT_LIMBS_COUNT];
};

#define get_large_uint(val) ((large_uint){.limbs = {val}})

#define LARGE_UINT_MIN ((large_uint){.limbs = {}})
#define LARGE_UINT_MAX ((large_uint){.limbs = {UNSIGNED_MAX_VALUE_OF(uint64_t), UNSIGNED_MAX_VALUE_OF(uint64_t)}})

#define LARGE_UINT_ZERO ((large_uint){.limbs = {}})
#define LARGE_UINT_ONE  ((large_uint){.limbs = {UINT64_C(1)}})

// returns ~a
large_uint bitwise_not_large_uint(large_uint a);

// returns a & b
large_uint bitwise_and_large_uint(large_uint a, large_uint b);

// returns a | b
large_uint bitwise_or_large_uint(large_uint a, large_uint b);

// returns a ^ b
large_uint bitwise_xor_large_uint(large_uint a, large_uint b);

// if(a < b) returns -1
// else if(a == b) returns 0
// else if(a > b) returns 1
int compare_large_uint(large_uint a, large_uint b);

// returns a == b
int are_equal_large_uint(large_uint a, large_uint b);

// returns a == 0
int is_zero_large_uint(large_uint a);

// returns carry after performing (*res) = a + b;
uint64_t add_large_uint(large_uint* res, large_uint a, large_uint b);

// returns carry after performing (*res) = a - b;
uint64_t sub_large_uint(large_uint* res, large_uint a, large_uint b);

// res will be set with addition (a + b), on success (i.e. return 1)
// failure happens in case of an overflow OR if the result is greater than or equal to max_limit (max_limit is checked only if it is non zero)
int add_large_uint_overflow_safe(large_uint* res, large_uint a, large_uint b, large_uint max_limit);

// res will be set with subtraction, on success (i.e. return 1)
// failure happens in case of an underflow, when (a < b)
int sub_large_uint_underflow_safe(large_uint* res, large_uint a, large_uint b);

// set an explicit bit in large_uint
int set_bit_in_large_uint(large_uint* res, uint32_t bit_index);

// returns true, if the given large_uint, can fit on a single uint64_t, the value will be set with the value of a
// else a 0 (false) is returned, with value unset
int cast_large_uint_to_uint64(uint64_t* value, large_uint a);

// serialize and deserialize large_uint-s
void serialize_large_uint(void* bytes, uint32_t bytes_size, large_uint l);
large_uint deserialize_large_uint(const char* bytes, uint32_t bytes_size);

// print large_uint
void print_large_uint(large_uint l);

#endif