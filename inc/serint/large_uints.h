#ifndef LARGE_UINTS_H
#define LARGE_UINTS_H

#include<serint/large_uint.h>

// uint64 -> for extension and correctness for base case

declarations_large_uint(uint64, 1)

definitions_large_uint(uint64, 1)

// uint128

declarations_large_uint(uint128, 2)

definitions_large_uint(uint128, 2)

// uint256

declarations_large_uint(uint256, 4)

definitions_large_uint(uint256, 4)

// uint512

declarations_large_uint(uint512, 8)

definitions_large_uint(uint512, 8)

// below is a macro to assign between them

#define assign_large_uints(lhs, rhs) do{                                                                \
	uint32_t bytes_to_copy = min(sizeof((lhs).limbs), sizeof((rhs).limbs));                             \
	memory_move((lhs).limbs, (rhs).limbs, bytes_to_copy);                                               \
	memory_set(((void*)((lhs).limbs)) + bytes_to_copy, 0, sizeof((lhs).limbs) - bytes_to_copy);         \
}while(0);

#endif