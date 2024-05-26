#include<large_uints.h>

#include<stdio.h>



int main()
{
	uint256 hx = {0x123456789abcdeff,0x2929292929292929, 0xa5a5a5a5a5a5a5a5, 0x5a5a5a5a5a5a5a5a};

	for(uint32_t s = 0; s <= get_bit_width_uint256() + 4; s += 4)
	{
		print_uint256(left_shift_uint256(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t s = 0; s <= get_bit_width_uint256() + 4; s += 4)
	{
		print_uint256(right_shift_uint256(hx, s));
		printf("\n");
	}
	printf("\n");

	for(uint32_t b = 0; b <= get_bit_width_uint256(); b++)
	{
		print_uint256(get_bitmask_lower_n_bits_set_uint256(b));
		printf("\n");
	}
	printf("\n");

	uint256 max_sum_res;
	uint64_t carry = add_uint256(&max_sum_res, get_max_uint256(), get_max_uint256());
	print_uint256(get_max_uint256());printf(" * 2 = (%lu) ", carry);
	print_uint256(max_sum_res);printf("\n\n");

	uint256 a = {0xabcdef1234567890, 0xabcdef1234567890, 0x908765abcdfecdef, 0x9087654321abcdef};
	uint256 b = {0xfe5678cde6543210, 0x987655678efabcba, 0x987655678efabcba, 0xabcdef1234567890};

	uint256 res0;
	uint256 res1 = mul_uint256(&res0, a, b);

	print_uint256(a);
	printf(" * ");
	print_uint256(b);
	printf("\n");
	printf("= ");
	print_uint256(res1);
	print_uint256(res0);
	printf("\n\n");

	uint256 dividend  = {0xabcdef1234567890, 0x9087654321abcdef, 0xfe5678cde6543210, 0x987655678efabcba};
	uint256 divisor   = {0xabcd, 0x1234, 0x12, 0x50};
	uint256 quotient  = get_0_uint256();
	uint256 remainder = div_uint256(&quotient, dividend, divisor);
	print_uint256(dividend);
	printf(" / ");
	print_uint256(divisor);
	printf("\n");
	printf("= ");
	print_uint256(quotient);
	printf("(");
	print_uint256(remainder);
	printf(")\n\n");

	return 0;
}