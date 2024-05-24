#include<large_uint.h>

#include<stdio.h>

int main()
{
	large_uint hx = {0x123456789abcdeff,0x2929292929292929};

	for(uint32_t s = 0; s <= LARGE_UINT_BIT_WIDTH + 4; s += 4)
	{
		print_large_uint(left_shift_large_uint(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t s = 0; s <= LARGE_UINT_BIT_WIDTH + 4; s += 4)
	{
		print_large_uint(right_shift_large_uint(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t b = 0; b <= LARGE_UINT_BIT_WIDTH; b++)
	{
		print_large_uint(get_bitmask_lower_n_bits_set(b));
		printf("\n");
	}
	printf("\n");

	large_uint max_sum_res;
	uint64_t carry = add_large_uint(&max_sum_res, LARGE_UINT_MAX, LARGE_UINT_MAX);
	print_large_uint(LARGE_UINT_MAX);printf(" * 2 = (%lu) ", carry);
	print_large_uint(max_sum_res);printf("\n\n");

	large_uint a = {0xabcdef1234567890, 0x9087654321abcdef};
	large_uint b = {0xfedcba9876543210, 0x9876543210fedcba};

	large_uint res0;
	large_uint res1 = mul_large_uint(&res0, a, b);

	print_large_uint(a);
	printf(" * ");
	print_large_uint(b);
	printf("\n");
	printf("= ");
	print_large_uint(res1);
	print_large_uint(res0);
	printf("\n\n");

	large_uint dividend  = {0xabcdef1234567890, 0x9087654321abcdef};
	large_uint divisor   = {0xabcd, 0x1234};
	large_uint quotient  = LARGE_UINT_ZERO;
	large_uint remainder = div_large_uint(&quotient, dividend, divisor);
	print_large_uint(dividend);
	printf(" / ");
	print_large_uint(divisor);
	printf("\n");
	printf("= ");
	print_large_uint(quotient);
	printf("(");
	print_large_uint(remainder);
	printf(")\n\n");

	return 0;
}