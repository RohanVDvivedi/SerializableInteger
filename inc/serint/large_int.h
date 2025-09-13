#ifndef LARGE_INT_H
#define LARGE_INT_H

/*
	large_int is and will always be based off some large_uint and will use it internally for storing its raw bits
*/

#define declarations_large_int(large_uint)                                                                                                                  \
                                                                                                                                                            \
	typedef struct large_int large_int;                                                                                                                     \
	struct large_int                                                                                                                                        \
	{                                                                                                                                                       \
		large_uint raw_uint_value;                                                                                                                          \
	};                                                                                                                                                      \
                                                                                                                                                            \
	/* number of maximum bytes of data in a large_int */                                                                                                    \
	static inline uint32_t get_max_bytes_ ## large_int();                                                                                                   \
                                                                                                                                                            \
	/* number of bits of data in a large_int */                                                                                                             \
	static inline uint32_t get_bit_width_ ## large_int();                                                                                                   \
                                                                                                                                                            \
	/* get a default uint64_t val valued large_int */                                                                                                       \
	static inline large_int get_ ## large_int(int64_t val);                                                                                                 \
                                                                                                                                                            \
	/* get zero and one values for a large_int */                                                                                                           \
	static inline large_int get_0_ ## large_int();                                                                                                          \
	static inline large_int get_1_ ## large_int();                                                                                                          \
                                                                                                                                                            \
	/* get min and max values for a large_int */                                                                                                            \
	static inline large_int get_min_ ## large_int();                                                                                                        \
	static inline large_int get_max_ ## large_int();                                                                                                        \
                                                                                                                                                            \
	/* gets a bit from large_int */                                                                                                                         \
	static inline int get_bit_from_ ## large_int(large_int a, uint32_t bit_index);                                                                          \
                                                                                                                                                            \
	/* set a bit in large_int */                                                                                                                            \
	static inline int set_bit_in_ ## large_int(large_int* res, uint32_t bit_index);                                                                         \
                                                                                                                                                            \
	/* reset a bit in large_int */                                                                                                                          \
	static inline int reset_bit_in_ ## large_int(large_int* res, uint32_t bit_index);                                                                       \
                                                                                                                                                            \
	/* gets a byte from large_int */                                                                                                                        \
	static inline uint8_t get_byte_from_ ## large_int(large_int a, uint32_t byte_index);                                                                    \
                                                                                                                                                            \
	/* set byte at the byte_index in res */                                                                                                                 \
	static inline int set_byte_in_ ## large_int(large_int* res, uint32_t byte_index, uint8_t byte);                                                         \
                                                                                                                                                            \
	/* returns ~a */                                                                                                                                        \
	static inline large_int bitwise_not_ ## large_int(large_int a);                                                                                         \
                                                                                                                                                            \
	/* returns a & b */                                                                                                                                     \
	static inline large_int bitwise_and_ ## large_int(large_int a, large_int b);                                                                            \
                                                                                                                                                            \
	/* returns a | b */                                                                                                                                     \
	static inline large_int bitwise_or_ ## large_int(large_int a, large_int b);                                                                             \
                                                                                                                                                            \
	/* returns a ^ b */                                                                                                                                     \
	static inline large_int bitwise_xor_ ## large_int(large_int a, large_int b);                                                                            \
                                                                                                                                                            \
	/* returns a << s */                                                                                                                                    \
	static inline large_int left_shift_ ## large_int(large_int a, uint32_t s);                                                                              \
                                                                                                                                                            \
	/* returns a >> s */                                                                                                                                    \
	static inline large_int right_shift_ ## large_int(large_int a, uint32_t s);                                                                             \
                                                                                                                                                            \
	/* if(a < b) returns -1 */                                                                                                                              \
	/* else if(a == b) returns 0 */                                                                                                                         \
	/* else if(a > b) returns 1 */                                                                                                                          \
	static inline int compare_ ## large_int(large_int a, large_int b);                                                                                      \
	/* same exact implementation but with void pointers to easily create and use as comparators */                                                          \
	static inline int compare_ ## large_int ## _with_ptrs(const void* a, const void* b);                                                                    \
                                                                                                                                                            \
	/* returns a == b */                                                                                                                                    \
	static inline int are_equal_ ## large_int(large_int a, large_int b);                                                                                    \
                                                                                                                                                            \
	/* returns a == 0 */                                                                                                                                    \
	static inline int is_zero_ ## large_int(large_int a);                                                                                                   \
                                                                                                                                                            \
	/* calculate min of 2 values */                                                                                                                         \
	static inline large_int min_ ## large_int(large_int a, large_int b);                                                                                    \
                                                                                                                                                            \
	/* calculate max of 2 values */                                                                                                                         \
	static inline large_int max_ ## large_int(large_int a, large_int b);                                                                                    \
                                                                                                                                                            \
	/* get sign bit */                                                                                                                                      \
	static inline int get_sign_bit_ ## large_int(large_int a);                                                                                              \
                                                                                                                                                            \
	/* get absolute value */                                                                                                                                \
	static inline large_uint get_absolute_ ## large_int(large_int a);                                                                                       \
                                                                                                                                                            \
	/* get 2's complement value, returns negative value */                                                                                                  \
	static inline large_uint get_2s_complement_ ## large_int(large_int a);                                                                                  \
                                                                                                                                                            \
	/* (*res) = a + b + carry and then returns carry */                                                                                                     \
	static inline uint64_t add_with_carry_ ## large_int(large_int* res, large_int a, large_int b, uint64_t carry_in);                                       \
                                                                                                                                                            \
	/* returns carry after performing (*res) = a + b; */                                                                                                    \
	static inline uint64_t add_ ## large_int(large_int* res, large_int a, large_int b);                                                                     \
                                                                                                                                                            \
	/* returns carry after performing (*res) = a - b; */                                                                                                    \
	static inline uint64_t sub_ ## large_int(large_int* res, large_int a, large_int b);                                                                     \
                                                                                                                                                            \
	/* returns a number with only lowset significant n bits set */                                                                                          \
	/* this function can be used to build bit masks */                                                                                                      \
	/* returns ((1 << n) - 1) */                                                                                                                            \
	static inline large_int get_bitmask_lower_n_bits_set_ ## large_int(uint32_t n);                                                                         \
                                                                                                                                                            \
	/* res will be set with addition (a + b), on success (i.e. return 1) */                                                                                 \
	/* failure happens in case of an overflow OR if the result is greater than or equal to max_limit (max_limit is checked only if it is non zero) */       \
	static inline int add_overflow_safe_ ## large_int(large_int* res, large_int a, large_int b, large_int max_limit);                                       \
                                                                                                                                                            \
	/* res will be set with subtraction, on success (i.e. return 1) */                                                                                      \
	/* failure happens in case of an underflow, when (a < b) */                                                                                             \
	static inline int sub_underflow_safe_ ## large_int(large_int* res, large_int a, large_int b);                                                           \
                                                                                                                                                            \
	/* the product of a and b, i.e. (a * b) -> this value is 2 lage_uints wide */                                                                           \
	/* the lower half of the result is stored in res, while the upper half is returned at the return value */                                               \
	static inline large_int mul_ ## large_int(large_int* res, large_int a, large_int b);                                                                    \
                                                                                                                                                            \
	/* divides dividend by divisor, and returns remainder and sets the quotient to the pointer */                                                           \
	/* there is not limb wise division, this function performs a sequential binary division (restoring shift-substract algorithm) */                        \
	/* it is your duty to ensure that the divisor is not 0 */                                                                                               \
	static inline large_int div_ ## large_int(large_int* quotient, large_int dividend, large_int divisor);                                                  \
                                                                                                                                                            \
	/* find gcd of two numbers */                                                                                                                           \
    static inline large_int gcd_ ## large_int(large_int a, large_int b);                                                                                    \
                                                                                                                                                            \
	/* returns true, if the given large_int, can fit on a single uint64_t, the value will be set with the value of a */                                     \
	/* else a 0 (false) is returned, with value unset */                                                                                                    \
	static inline int cast_to_int64_from_ ## large_int(uint64_t* value, large_int a);                                                                       \
                                                                                                                                                            \
	/* serialize and deserialize large_int-s */                                                                                                             \
	static inline void serialize_ ## large_int(void* bytes, uint32_t bytes_size, large_int l);                                                              \
	static inline large_int deserialize_ ## large_int(const char* bytes, uint32_t bytes_size);                                                              \
                                                                                                                                                            \
	/* print large_int */                                                                                                                                   \
	static inline void print_ ## large_int(large_int l);                                                                                                    \
	/* print large_int */                                                                                                                                   \
	static inline void sprint_ ## large_int(char* dest, large_int l);                                                                                       \
                                                                                                                                                            \
	/* serialize large_int as decimal, into res, you must ensure that res is large enough, this function does not append '\0' to res */                     \
	static inline uint32_t serialize_to_decimal_ ## large_int(char* res, large_int l);                                                                      \
/* declarations complete */



#define definitions_large_int(large_uint)                                                                                                                   \
                                                                                                                                                            \
	static inline uint32_t get_max_bytes_ ## large_int()                                                                                                    \
	{                                                                                                                                                       \
		return get_max_bytes_ ## large_uint();                                                                                                              \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint32_t get_bit_width_ ## large_int()                                                                                                    \
	{                                                                                                                                                       \
		return get_bit_width_ ## large_uint();                                                                                                              \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_ ## large_int(int64_t val)                                                                                                  \
	{                                                                                                                                                       \
		large_int res;                                                                                                                                      \
		if(val < 0)                                                                                                                                         \
			res = (large_int){get_max_ ## large_uint()};                                                                                                    \
		else                                                                                                                                                \
			res = (large_int){get_0_ ## large_uint()};                                                                                                      \
		res.raw_uint_value.limbs[0] = val;                                                                                                                  \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_0_ ## large_int()                                                                                                           \
	{                                                                                                                                                       \
		return get_ ## large_int(0);                                                                                                                        \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_1_ ## large_int()                                                                                                           \
	{                                                                                                                                                       \
		return get_ ## large_int(1);                                                                                                                        \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_min_ ## large_int()                                                                                                         \
	{                                                                                                                                                       \
		large_int res = {get_0_ ## large_uint()};                                                                                                           \
		set_bit_in_ ## large_int(&res, get_bit_width_ ## large_int() - 1);                                                                                  \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_max_ ## large_int()                                                                                                         \
	{                                                                                                                                                       \
		large_int res = {get_max_ ## large_uint()};                                                                                                         \
		reset_bit_in_ ## large_int(&res, get_bit_width_ ## large_int() - 1);                                                                                \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int get_bit_from_ ## large_int(large_int a, uint32_t bit_index)                                                                           \
	{                                                                                                                                                       \
		return get_bit_from_ ## large_uint(a.raw_uint_value, bit_index);                                                                                    \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int set_bit_in_ ## large_int(large_int* res, uint32_t bit_index)                                                                          \
	{                                                                                                                                                       \
		return set_bit_in_ ## large_uint(&(res->raw_uint_value), bit_index);                                                                                \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int reset_bit_in_ ## large_int(large_int* res, uint32_t bit_index)                                                                        \
	{                                                                                                                                                       \
		return reset_bit_in_ ## large_uint(&(res->raw_uint_value), bit_index);                                                                              \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint8_t get_byte_from_ ## large_int(large_int a, uint32_t byte_index)                                                                     \
	{                                                                                                                                                       \
		return get_byte_from_ ## large_uint(&(a.raw_uint_value), byte_index);                                                                               \
	}                                                                                                                                                       \
                                                                                                                                                           	\
	static inline int set_byte_in_ ## large_int(large_int* res, uint32_t byte_index, uint8_t byte)                                                          \
	{                                                                                                                                                       \
		return set_byte_in_ ## large_uint(&(res->raw_uint_value), byte_index, byte);                                                                        \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int bitwise_not_ ## large_int(large_int a)                                                                                          \
	{                                                                                                                                                       \
		return (large_int){bitwise_not_ ## large_uint(&(a.raw_uint_value))};                                                                                \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int bitwise_and_ ## large_int(large_int a, large_int b)                                                                             \
	{                                                                                                                                                       \
		return (large_int){bitwise_and_ ## large_uint(a.raw_uint_value, b.raw_uint_value)};                                                                 \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int bitwise_or_ ## large_int(large_int a, large_int b)                                                                              \
	{                                                                                                                                                       \
		return (large_int){bitwise_or_ ## large_uint(a.raw_uint_value, b.raw_uint_value)};                                                                  \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int bitwise_xor_ ## large_int(large_int a, large_int b)                                                                             \
	{                                                                                                                                                       \
		return (large_int){bitwise_xor_ ## large_uint(a.raw_uint_value, b.raw_uint_value)};                                                                 \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int left_shift_ ## large_int(large_int a, uint32_t s)                                                                               \
	{                                                                                                                                                       \
		return (large_int){left_shift_ ## large_uint(a.raw_uint_value, s)};                                                                                 \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int right_shift_ ## large_int(large_int a, uint32_t s)                                                                              \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int compare_ ## large_int(large_int a, large_int b)                                                                                       \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int compare_ ## large_int ## _with_ptrs(const void* a, const void* b)                                                                     \
	{                                                                                                                                                       \
		return compare_ ## large_int(*((const large_int*)a), *((const large_int*)b));                                                                       \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int are_equal_ ## large_int(large_int a, large_int b)                                                                                     \
	{                                                                                                                                                       \
		return compare_ ## large_int(a, b) == 0;                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int is_zero_ ## large_int(large_int a)                                                                                                    \
	{                                                                                                                                                       \
		return compare_ ## large_int(a, get_0_ ## large_int()) == 0;                                                                                        \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int min_ ## large_int(large_int a, large_int b)                                                                                     \
	{                                                                                                                                                       \
		if(compare_ ## large_int(a, b) >= 0)                                                                                                                \
			return b;                                                                                                                                       \
		return a;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int max_ ## large_int(large_int a, large_int b)                                                                                     \
	{                                                                                                                                                       \
		if(compare_ ## large_int(a, b) >= 0)                                                                                                                \
			return a;                                                                                                                                       \
		return b;                                                                                                                                           \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int get_sign_bit_ ## large_int(large_int a)                                                                                               \
	{                                                                                                                                                       \
        return get_bit_from_ ## large_int(a, get_bit_width_ ## large_int() - 1);                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_uint get_absolute_ ## large_int(large_int a)                                                                                        \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_2s_complement_ ## large_int(large_int a)                                                                                    \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint64_t add_with_carry_ ## large_int(large_int* res, large_int a, large_int b, uint64_t carry_in)                                        \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint64_t add_ ## large_int(large_int* res, large_int a, large_int b)                                                                      \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint64_t sub_ ## large_int(large_int* res, large_int a, large_int b)                                                                      \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int get_bitmask_lower_n_bits_set_ ## large_int(uint32_t n)                                                                          \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int add_overflow_safe_ ## large_int(large_int* res, large_int a, large_int b, large_int max_limit)                                        \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int sub_underflow_safe_ ## large_int(large_int* res, large_int a, large_int b)                                                            \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int mul_ ## large_int(large_int* res, large_int a, large_int b)                                                                     \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int div_ ## large_int(large_int* quotient, large_int dividend, large_int divisor)                                                   \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int gcd_ ## large_int(large_int a, large_int b)                                                                                     \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline int cast_to_int64_from_ ## large_int(uint64_t* value, large_int a)                                                                        \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline void serialize_ ## large_int(void* bytes, uint32_t bytes_size, large_int l)                                                               \
	{                                                                                                                                                       \
		bytes_size = min(bytes_size, get_max_bytes_ ## large_uint());                                                                                       \
                                                                                                                                                            \
		uint32_t limb_index = 0;                                                                                                                            \
		while(bytes_size > 0)                                                                                                                               \
		{                                                                                                                                                   \
			uint32_t bytes_to_write = min(BYTES_PER_LIMB, bytes_size);                                                                                      \
                                                                                                                                                            \
			serialize_uint64(bytes, bytes_to_write, l.raw_uint_value.limbs[limb_index++]);                                                                  \
                                                                                                                                                            \
			bytes_size -= bytes_to_write;                                                                                                                   \
			bytes += bytes_to_write;                                                                                                                        \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline large_int deserialize_ ## large_int(const char* bytes, uint32_t bytes_size)                                                               \
	{                                                                                                                                                       \
		large_int res = {};                                                                                                                                 \
                                                                                                                                                            \
		bytes_size = min(bytes_size, get_max_bytes_ ## large_int());                                                                                        \
                                                                                                                                                            \
		uint32_t limb_index = 0;                                                                                                                            \
		while(bytes_size > 0)                                                                                                                               \
		{                                                                                                                                                   \
			uint32_t bytes_to_read = min(BYTES_PER_LIMB, bytes_size);                                                                                       \
                                                                                                                                                            \
			res.raw_uint_value.limbs[limb_index++] = deserialize_uint64(bytes, bytes_to_read);                                                              \
                                                                                                                                                            \
			bytes_size -= bytes_to_read;                                                                                                                    \
			bytes += bytes_to_read;                                                                                                                         \
		}                                                                                                                                                   \
                                                                                                                                                            \
		return res;                                                                                                                                         \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline void print_ ## large_int(large_int l)                                                                                                     \
	{                                                                                                                                                       \
		for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)                                                                                                    \
		{                                                                                                                                                   \
			i--;                                                                                                                                            \
			printf("%016"PRIx64, l.raw_uint_value.limbs[i]);                                                                                                \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline void sprint_ ## large_int(char* dest, large_int l)                                                                                        \
	{                                                                                                                                                       \
		for(uint32_t i = LARGE_UINT_LIMBS_COUNT; i > 0;)                                                                                                    \
		{                                                                                                                                                   \
			i--;                                                                                                                                            \
			sprintf(dest, "%016"PRIx64, l.raw_uint_value.limbs[i]);                                                                                         \
			dest += 16;                                                                                                                                     \
		}                                                                                                                                                   \
	}                                                                                                                                                       \
                                                                                                                                                            \
	static inline uint32_t serialize_to_decimal_ ## large_int(char* res, large_int l)                                                                       \
	{                                                                                                                                                       \
                                                                                                                                                            \
	}                                                                                                                                                       \
/* definitions complete */

#endif