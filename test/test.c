#include<large_uints.h>

#include<stdio.h>



int main()
{
	uint128 hx = {0x123456789abcdeff,0x2929292929292929};

	for(uint32_t s = 0; s <= get_bit_width_uint128() + 4; s += 4)
	{
		print_uint128(left_shift_uint128(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t s = 0; s <= get_bit_width_uint128() + 4; s += 4)
	{
		print_uint128(right_shift_uint128(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t b = 0; b <= get_bit_width_uint128(); b++)
	{
		print_uint128(get_bitmask_lower_n_bits_set_uint128(b));
		printf("\n");
	}
	printf("\n");

	uint128 max_sum_res;
	uint64_t carry = add_uint128(&max_sum_res, get_max_uint128(), get_max_uint128());
	print_uint128(get_max_uint128());printf(" * 2 = (%lu) ", carry);
	print_uint128(max_sum_res);printf("\n\n");

	uint128 a = {0xabcdef1234567890, 0x908765abcdfecdef};
	uint128 b = {0xfe5678cde6543210, 0x987655678efabcba};

	uint128 res0;
	uint128 res1 = mul_uint128(&res0, a, b);

	print_uint128(a);
	printf(" * ");
	print_uint128(b);
	printf("\n");
	printf("= ");
	print_uint128(res1);
	print_uint128(res0);
	printf("\n\n");

	uint128 dividend  = {0xabcdef1234567890, 0x9087654321abcdef};
	uint128 divisor   = {0xabcd, 0x1234};
	uint128 quotient  = get_0_uint128();
	uint128 remainder = div_uint128(&quotient, dividend, divisor);
	print_uint128(dividend);
	printf(" / ");
	print_uint128(divisor);
	printf("\n");
	printf("= ");
	print_uint128(quotient);
	printf("(");
	print_uint128(remainder);
	printf(")\n\n");

	return 0;
}