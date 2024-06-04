#include<serial_int.h>

#include<cutlery_math.h>
#include<cutlery_stds.h>

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

uint8_t deserialize_uint8(const void* data, uint32_t data_size)	DESERIALIZE_UINT(8)
uint16_t deserialize_uint16(const void* data, uint32_t data_size)	DESERIALIZE_UINT(16)
uint32_t deserialize_uint32(const void* data, uint32_t data_size)	DESERIALIZE_UINT(32)
uint64_t deserialize_uint64(const void* data, uint32_t data_size)	DESERIALIZE_UINT(64)

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

int8_t deserialize_int8(const void* data, uint32_t data_size)		DESERIALIZE_INT(8)
int16_t deserialize_int16(const void* data, uint32_t data_size)	DESERIALIZE_INT(16)
int32_t deserialize_int32(const void* data, uint32_t data_size)	DESERIALIZE_INT(32)
int64_t deserialize_int64(const void* data, uint32_t data_size)	DESERIALIZE_INT(64)

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

void serialize_uint8(void* data, uint32_t data_size, uint8_t x)		SERIALIZE_UINT(8)
void serialize_uint16(void* data, uint32_t data_size, uint16_t x)	SERIALIZE_UINT(16)
void serialize_uint32(void* data, uint32_t data_size, uint32_t x)	SERIALIZE_UINT(32)
void serialize_uint64(void* data, uint32_t data_size, uint64_t x)	SERIALIZE_UINT(64)

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

void serialize_int8(void* data, uint32_t data_size, int8_t x)		SERIALIZE_INT(8)
void serialize_int16(void* data, uint32_t data_size, int16_t x)		SERIALIZE_INT(16)
void serialize_int32(void* data, uint32_t data_size, int32_t x)		SERIALIZE_INT(32)
void serialize_int64(void* data, uint32_t data_size, int64_t x)		SERIALIZE_INT(64)

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

uint32_t get_min_bit_count_uint8(uint8_t x)		MIN_BIT_COUNT_UINT(8)
uint32_t get_min_bit_count_uint16(uint16_t x)	MIN_BIT_COUNT_UINT(16)
uint32_t get_min_bit_count_uint32(uint32_t x)	MIN_BIT_COUNT_UINT(32)
uint32_t get_min_bit_count_uint64(uint64_t x)	MIN_BIT_COUNT_UINT(64)

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

uint32_t get_min_bit_count_int8(int8_t x)	MIN_BIT_COUNT_INT(8)
uint32_t get_min_bit_count_int16(int16_t x)	MIN_BIT_COUNT_INT(16)
uint32_t get_min_bit_count_int32(int32_t x)	MIN_BIT_COUNT_INT(32)
uint32_t get_min_bit_count_int64(int64_t x)	MIN_BIT_COUNT_INT(64)

uint8_t get_UINT8_MIN(uint32_t data_size)		{return 0;}
uint16_t get_UINT16_MIN(uint32_t data_size)		{return 0;}
uint32_t get_UINT32_MIN(uint32_t data_size)		{return 0;}
uint64_t get_UINT64_MIN(uint32_t data_size)		{return 0;}

#define GET_UINT_MAX(X)											\
{																\
	if(data_size == 0)											\
		return 0;												\
	data_size = min(data_size, sizeof(uint(X)));				\
	uint(X) x = INT ## X ## _C(-1);								\
	x = x >> ((sizeof(uint(X)) - data_size) * CHAR_BIT);		\
	return x;													\
}

uint8_t get_UINT8_MAX(uint32_t data_size)		GET_UINT_MAX(8)
uint16_t get_UINT16_MAX(uint32_t data_size)		GET_UINT_MAX(16)
uint32_t get_UINT32_MAX(uint32_t data_size)		GET_UINT_MAX(32)
uint64_t get_UINT64_MAX(uint32_t data_size)		GET_UINT_MAX(64)

#define GET_INT_MIN(X)									\
{														\
	if(data_size == 0)									\
		return 0;										\
	data_size = min(data_size, sizeof(sint(X)));		\
	sint(X) x = INT ## X ## _C(-1);						\
	x = x << ((CHAR_BIT * data_size) - 1);				\
	return x;											\
}

int8_t get_INT8_MIN(uint32_t data_size)			GET_INT_MIN(8)
int16_t get_INT16_MIN(uint32_t data_size)		GET_INT_MIN(16)
int32_t get_INT32_MIN(uint32_t data_size)		GET_INT_MIN(32)
int64_t get_INT64_MIN(uint32_t data_size)		GET_INT_MIN(64)

#define GET_INT_MAX(X)											\
{																\
	if(data_size == 0)											\
		return 0;												\
	data_size = min(data_size, sizeof(sint(X)));				\
	uint(X) x = INT ## X ## _C(-1);								\
	x = x >> (((sizeof(uint(X)) - data_size) * CHAR_BIT) + 1);	\
	return x;													\
}

int8_t get_INT8_MAX(uint32_t data_size)			GET_INT_MAX(8)
int16_t get_INT16_MAX(uint32_t data_size)		GET_INT_MAX(16)
int32_t get_INT32_MAX(uint32_t data_size)		GET_INT_MAX(32)
int64_t get_INT64_MAX(uint32_t data_size)		GET_INT_MAX(64)