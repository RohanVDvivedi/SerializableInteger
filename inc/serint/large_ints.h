#ifndef LARGE_INTS_H
#define LARGE_INTS_H

#include<serint/large_uints.h>
#include<serint/large_int.h>

// int64 -> for extension and correctness for base case

declarations_large_int(int64, uint64)

definitions_large_int(int64, uint64)

// int128

declarations_large_int(int128, uint128)

definitions_large_int(int128, uint128)

// int256

declarations_large_int(int256, uint256)

definitions_large_int(int256, uint256)

// int512

declarations_large_int(int512, uint512)

definitions_large_int(int512, uint512)

#endif