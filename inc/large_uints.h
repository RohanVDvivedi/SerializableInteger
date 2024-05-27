#ifndef LARGE_UINTS_H
#define LARGE_UINTS_H

#include<large_uint.h>

declarations_large_uint(uint128, 2)

declarations_large_uint(uint256, 4)

declarations_large_uint(uint512, 8)

#define assign_large_uints(lhs, rhs) do{                                                                \
	uint32_t bytes_to_copy = min(sizeof((lhs).limbs), sizeof((rhs).limbs));                             \
	memory_move((lhs).limbs, (rhs).limbs, bytes_to_copy);                                               \
	memory_set(((void*)((lhs).limbs)) + bytes_to_copy, 0, sizeof((lhs).limbs) - bytes_to_copy);         \
}while(0);

#endif