#ifndef SERIAL_INT_H
#define SERIAL_INT_H

#include<stdint.h>

#include<cutlery_stds.h> // for fail_build_on macro

// for using this header, the CHAR_BIT (number of bits in a byte) must be 8
fail_build_on((CHAR_BIT != 8))

/*
	deserialize functions assume that the serialized integer is stored at data (void*) in little endian format
	and it returns uintX_t in the byte ordering of the processor, after reading min(X/8, data_size) bytes from data pointer

	serialize functions take in a uintX_t and serialize it into little endian format occupying only min(X/8, data_size) number of bytes

	It is assumed that you already know the minimum number of bytes required to safely represent the integer
	and that is what must be passed to these functions in data_size param.

	data, the void* passed does not need to be aligned address.

	these functions also allow you to have and operate with integers with varibale length byte widths
	all the way from 1 to 8

	alignment is mostly a problem on systems that fault on an unaligned accesses,
	this file does not restrict any such restrictions on the data param.
*/

/*
	for a function operating on uintX_t or intX_t if data_size == 0
	then the operation is a NO-OP (NOP)
	if the data_size > X/8 then data_size is taken as X/8
	if data_size is between 1 and X/8 then only the specified bytes are read or written to form the number
*/

/*
	deserialize_uintX reads min(X/8, data_size) bytes from data as an uintX_t
*/

static inline uint8_t deserialize_uint8(const void* data, uint32_t data_size);
static inline uint16_t deserialize_uint16(const void* data, uint32_t data_size);
static inline uint32_t deserialize_uint32(const void* data, uint32_t data_size);
static inline uint64_t deserialize_uint64(const void* data, uint32_t data_size);

/*
	deserialize_intX reads min(X/8, data_size) bytes from data as an intX_t
*/

static inline int8_t deserialize_int8(const void* data, uint32_t data_size);
static inline int16_t deserialize_int16(const void* data, uint32_t data_size);
static inline int32_t deserialize_int32(const void* data, uint32_t data_size);
static inline int64_t deserialize_int64(const void* data, uint32_t data_size);

/*
	serialize_uintX writes min(X/8, data_size) bytes to data
*/

static inline void serialize_uint8(void* data, uint32_t data_size, uint8_t x);
static inline void serialize_uint16(void* data, uint32_t data_size, uint16_t x);
static inline void serialize_uint32(void* data, uint32_t data_size, uint32_t x);
static inline void serialize_uint64(void* data, uint32_t data_size, uint64_t x);

/*
	serialize_intX writes min(X/8, data_size) bytes to data
*/

static inline void serialize_int8(void* data, uint32_t data_size, int8_t x);
static inline void serialize_int16(void* data, uint32_t data_size, int16_t x);
static inline void serialize_int32(void* data, uint32_t data_size, int32_t x);
static inline void serialize_int64(void* data, uint32_t data_size, int64_t x);

/*
	get_significant_bit_count_uintX -> returns the number of significant bits required to represent a unsigned int number (discarding the most significant 0s), for 0, it will return 1
	this is equivalent to 
		if(x == 0)
			return 1;
		else
			return (sizeof(uintX_t) * CHAR_BIT) - (number of most significant 0 bits)
	these are the minimum bit count required to represent a unsigned int number
*/

static inline uint32_t get_min_bit_count_uint8(uint8_t x);
static inline uint32_t get_min_bit_count_uint16(uint16_t x);
static inline uint32_t get_min_bit_count_uint32(uint32_t x);
static inline uint32_t get_min_bit_count_uint64(uint64_t x);

/*
	get_significant_bit_count_intX -> returns the number of significant bits required to represent a signed int number (discarding the most significant 1s and 0s except for 1 of them), for 0, it will return 1
	this is equivalent to
		if(x >= 0)
			return (sizeof(intX_t) * CHAR_BIT) - (number of most significant 0 bits) + 1
		else if(x < 0)
			return (sizeof(intX_t) * CHAR_BIT) - (number of most significant 1 bits) + 1
	these are the minimum bit count required to represent a unsigned int number
*/

static inline uint32_t get_min_bit_count_int8(int8_t x);
static inline uint32_t get_min_bit_count_int16(int16_t x);
static inline uint32_t get_min_bit_count_int32(int32_t x);
static inline uint32_t get_min_bit_count_int64(int64_t x);

/*
	uintX_t get_UINTX_MIN(uint32_t data_size) and
	uintX_t get_UINTX_MAX(uint32_t data_size)
	returns minimum and maximum number that can be represented in data_size number of bytes for an unsigned intteger
*/

static inline uint8_t get_UINT8_MIN(uint32_t data_size);
static inline uint16_t get_UINT16_MIN(uint32_t data_size);
static inline uint32_t get_UINT32_MIN(uint32_t data_size);
static inline uint64_t get_UINT64_MIN(uint32_t data_size);

static inline uint8_t get_UINT8_MAX(uint32_t data_size);
static inline uint16_t get_UINT16_MAX(uint32_t data_size);
static inline uint32_t get_UINT32_MAX(uint32_t data_size);
static inline uint64_t get_UINT64_MAX(uint32_t data_size);

/*
	uintX_t get_INTX_MIN(uint32_t data_size) and
	uintX_t get_INTX_MAX(uint32_t data_size)
	returns minimum and maximum number that can be represented in data_size number of bytes for a signed integer
*/

static inline int8_t get_INT8_MIN(uint32_t data_size);
static inline int16_t get_INT16_MIN(uint32_t data_size);
static inline int32_t get_INT32_MIN(uint32_t data_size);
static inline int64_t get_INT64_MIN(uint32_t data_size);

static inline int8_t get_INT8_MAX(uint32_t data_size);
static inline int16_t get_INT16_MAX(uint32_t data_size);
static inline int32_t get_INT32_MAX(uint32_t data_size);
static inline int64_t get_INT64_MAX(uint32_t data_size);

#include<cutlery/cutlery_math.h>
#include<cutlery/cutlery_stds.h>

#include<limits.h>

#define uint(X) uint ## X ## _t
#define sint(X) int ## X ## _t

#define DESERIALIZE_UINT(X)						\
{												\
	if(data_size == 0)							\
		return 0;								\
	data_size = min(data_size, sizeof(uint(X)));\
	uint(X) x = 0;								\
	const uint8_t* data8 = data;				\
	for(uint32_t i = 0; i < data_size; i++)		\
	{											\
		uint(X) temp = data8[i];				\
		x |= (temp << (i * CHAR_BIT));			\
	}											\
	return x;									\
}

static inline uint8_t deserialize_uint8(const void* data, uint32_t data_size)	DESERIALIZE_UINT(8)
static inline uint16_t deserialize_uint16(const void* data, uint32_t data_size)	DESERIALIZE_UINT(16)
static inline uint32_t deserialize_uint32(const void* data, uint32_t data_size)	DESERIALIZE_UINT(32)
static inline uint64_t deserialize_uint64(const void* data, uint32_t data_size)	DESERIALIZE_UINT(64)

#define DESERIALIZE_INT(X)									\
{															\
	if(data_size == 0)										\
		return 0;											\
	data_size = min(data_size, sizeof(sint(X)));			\
	sint(X) x = 0;											\
	const uint8_t* data8 = data;							\
	for(uint32_t i = 0; i < data_size; i++)					\
	{														\
		uint(X) temp = data8[i];							\
		x |= (temp << (i * CHAR_BIT));						\
	}														\
	int is_neg = data8[data_size - 1] & ((uint8_t)0x80);	\
	if(!is_neg)												\
		return x;											\
	for(uint32_t i = data_size; i < sizeof(sint(X)); i++)	\
		x |= (UINT ## X ## _C(0xff) << (i * CHAR_BIT));		\
	return x;												\
}

static inline int8_t deserialize_int8(const void* data, uint32_t data_size)		DESERIALIZE_INT(8)
static inline int16_t deserialize_int16(const void* data, uint32_t data_size)	DESERIALIZE_INT(16)
static inline int32_t deserialize_int32(const void* data, uint32_t data_size)	DESERIALIZE_INT(32)
static inline int64_t deserialize_int64(const void* data, uint32_t data_size)	DESERIALIZE_INT(64)

#define SERIALIZE_UINT(X)							\
{													\
	if(data_size == 0)								\
		return;										\
	data_size = min(data_size, sizeof(uint(X)));	\
	uint8_t* data8 = data;							\
	for(uint32_t i = 0; i < data_size; i++)			\
	{												\
		uint(X) temp = x & UINT ## X ## _C(0xff);	\
		data8[i] = (uint8_t)temp;					\
		x >>= 8;									\
	}												\
}

static inline void serialize_uint8(void* data, uint32_t data_size, uint8_t x)		SERIALIZE_UINT(8)
static inline void serialize_uint16(void* data, uint32_t data_size, uint16_t x)	SERIALIZE_UINT(16)
static inline void serialize_uint32(void* data, uint32_t data_size, uint32_t x)	SERIALIZE_UINT(32)
static inline void serialize_uint64(void* data, uint32_t data_size, uint64_t x)	SERIALIZE_UINT(64)

#define SERIALIZE_INT(X)							\
{													\
	if(data_size == 0)								\
		return;										\
	data_size = min(data_size, sizeof(sint(X)));	\
	uint8_t* data8 = data;							\
	for(uint32_t i = 0; i < data_size; i++)			\
	{												\
		uint(X) temp = x & UINT ## X ## _C(0xff);	\
		data8[i] = (uint8_t)temp;					\
		x >>= 8;									\
	}												\
}

static inline void serialize_int8(void* data, uint32_t data_size, int8_t x)		SERIALIZE_INT(8)
static inline void serialize_int16(void* data, uint32_t data_size, int16_t x)		SERIALIZE_INT(16)
static inline void serialize_int32(void* data, uint32_t data_size, int32_t x)		SERIALIZE_INT(32)
static inline void serialize_int64(void* data, uint32_t data_size, int64_t x)		SERIALIZE_INT(64)

#define MIN_BIT_COUNT_UINT(X)						\
{													\
	uint32_t res = sizeof(uint(X)) * CHAR_BIT;		\
	while(res > 0)									\
	{												\
		if((x >> (res-1)) & 1)						\
			break;									\
		res--;										\
	}												\
	return res;										\
}

static inline uint32_t get_min_bit_count_uint8(uint8_t x)		MIN_BIT_COUNT_UINT(8)
static inline uint32_t get_min_bit_count_uint16(uint16_t x)	MIN_BIT_COUNT_UINT(16)
static inline uint32_t get_min_bit_count_uint32(uint32_t x)	MIN_BIT_COUNT_UINT(32)
static inline uint32_t get_min_bit_count_uint64(uint64_t x)	MIN_BIT_COUNT_UINT(64)

#define MIN_BIT_COUNT_INT(X)						\
{													\
	uint32_t res = sizeof(sint(X)) * CHAR_BIT;		\
	int msb = (x >> (res - 1)) & 1;					\
	while(res > 0)									\
	{												\
		if(((x >> (res-1)) & 1) != msb)				\
			break;									\
		res--;										\
	}												\
	return res + 1;									\
}

static inline uint32_t get_min_bit_count_int8(int8_t x)	MIN_BIT_COUNT_INT(8)
static inline uint32_t get_min_bit_count_int16(int16_t x)	MIN_BIT_COUNT_INT(16)
static inline uint32_t get_min_bit_count_int32(int32_t x)	MIN_BIT_COUNT_INT(32)
static inline uint32_t get_min_bit_count_int64(int64_t x)	MIN_BIT_COUNT_INT(64)

static inline uint8_t get_UINT8_MIN(uint32_t data_size)		{return 0;}
static inline uint16_t get_UINT16_MIN(uint32_t data_size)		{return 0;}
static inline uint32_t get_UINT32_MIN(uint32_t data_size)		{return 0;}
static inline uint64_t get_UINT64_MIN(uint32_t data_size)		{return 0;}

#define GET_UINT_MAX(X)											\
{																\
	if(data_size == 0)											\
		return 0;												\
	data_size = min(data_size, sizeof(uint(X)));				\
	uint(X) x = INT ## X ## _C(-1);								\
	x = x >> ((sizeof(uint(X)) - data_size) * CHAR_BIT);		\
	return x;													\
}

static inline uint8_t get_UINT8_MAX(uint32_t data_size)		GET_UINT_MAX(8)
static inline uint16_t get_UINT16_MAX(uint32_t data_size)		GET_UINT_MAX(16)
static inline uint32_t get_UINT32_MAX(uint32_t data_size)		GET_UINT_MAX(32)
static inline uint64_t get_UINT64_MAX(uint32_t data_size)		GET_UINT_MAX(64)

#define GET_INT_MIN(X)									\
{														\
	if(data_size == 0)									\
		return 0;										\
	data_size = min(data_size, sizeof(sint(X)));		\
	sint(X) x = INT ## X ## _C(-1);						\
	x = x << ((CHAR_BIT * data_size) - 1);				\
	return x;											\
}

static inline int8_t get_INT8_MIN(uint32_t data_size)			GET_INT_MIN(8)
static inline int16_t get_INT16_MIN(uint32_t data_size)		GET_INT_MIN(16)
static inline int32_t get_INT32_MIN(uint32_t data_size)		GET_INT_MIN(32)
static inline int64_t get_INT64_MIN(uint32_t data_size)		GET_INT_MIN(64)

#define GET_INT_MAX(X)											\
{																\
	if(data_size == 0)											\
		return 0;												\
	data_size = min(data_size, sizeof(sint(X)));				\
	uint(X) x = INT ## X ## _C(-1);								\
	x = x >> (((sizeof(uint(X)) - data_size) * CHAR_BIT) + 1);	\
	return x;													\
}

static inline int8_t get_INT8_MAX(uint32_t data_size)			GET_INT_MAX(8)
static inline int16_t get_INT16_MAX(uint32_t data_size)		GET_INT_MAX(16)
static inline int32_t get_INT32_MAX(uint32_t data_size)		GET_INT_MAX(32)
static inline int64_t get_INT64_MAX(uint32_t data_size)		GET_INT_MAX(64)

#endif