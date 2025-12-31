#include<serint/large_uints.h>

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
	{
		// printing result as uint512
		uint512 res0b;
		assign_large_uints(res0b, res0);
		uint512 res1b;
		assign_large_uints(res1b, res1);
		uint512 rest = bitwise_or_uint512(left_shift_uint512(res1b, 256), res0b);
		print_uint512(rest);
		printf("\n\n");
	}

	{
		uint256 a = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};
		uint256 b = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};

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
		{
			// printing result as uint512
			uint512 res0b;
			assign_large_uints(res0b, res0);
			uint512 res1b;
			assign_large_uints(res1b, res1);
			uint512 rest = bitwise_or_uint512(left_shift_uint512(res1b, 256), res0b);
			print_uint512(rest);
			printf("\n\n");
		}
	}

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

	uint256 x = {0xff01020304050607, 0x08090a0b0c0d0e0f, 0x1011121314151617, 0x18191a1b1c1d1e1f};
	for(uint32_t i = 0; i < get_max_bytes_uint256(); i++)
		printf("%"PRIu32" -> %"PRIu8"\n", i, get_byte_from_uint256(x, i));

	for(uint32_t i = 0; i < get_max_bytes_uint256(); i++)
		set_byte_in_uint256(&x, i, i * 2);

	for(uint32_t i = 0; i < get_max_bytes_uint256(); i++)
		printf("%"PRIu32" -> %"PRIu8"\n", i, get_byte_from_uint256(x, i));


	{
		uint256 lhs = get_0_uint256();
		uint128 rhs = {0x01, 0x02};
		assign_large_uints(lhs, rhs);
		print_uint256(lhs);
		printf("\n\n");
	}

	{
		uint256 lhs = get_0_uint256();
		uint512 rhs = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
		assign_large_uints(lhs, rhs);
		print_uint256(lhs);
		printf("\n\n");
	}

	// test gcd
	{
		uint256 a = {60, 60, 48, 0};
		uint256 b = {48, 48, 60, 0};
		printf("gcd(");
		print_uint256(a);
		printf(", ");
		print_uint256(b);
		printf(")\n");
		print_uint256(gcd_uint256(a, b));
		printf("\n");
		print_uint256(gcd_uint256(a, b));
		printf("\n\n");
	}

	// test serialize to decimal, to print the number in decimal
	{
		uint256 a = {0xabcdef1234567890, 0xabcdef1234567890, 0x908765abcdfecdef, 0x9087654321abcdef};
		print_uint256(a);
		printf("\n");
		char res[78] = {}; // 256 * log(2) / log(10) // this array must be 0 initialized as the serialize_to_decimal_uint does not append a '\0'
		serialize_to_decimal_uint256(res, a);
		printf("%s\n", res);
	}

	{
		uint256 a = get_uint256(12);
		uint256 b = get_uint256(13);
		print_uint256(min_uint256(a, b));printf("\n");
	}

	{
		uint256 a = get_uint256(12);
		uint256 b = get_uint256(13);
		print_uint256(max_uint256(a, b));printf("\n");
	}

	{
		uint256 a = {0xabcdef1234567890, 0xabcdef1234567890, 0x908765abcdfecdef, 0x9087654321abcdef};
		char hex[65] = "";
		sprint_uint256(hex, a);
		printf("%s\n\n", hex);
	}

	{
		printf("uintb64 add and mul\n");

		uintb64 x = {0xabcd333334567890};
		printf("x = %"PRIu64"\n", x.limbs[0]);
		uintb64 y = {0x9087654311111def};
		printf("y = %"PRIu64"\n", y.limbs[0]);

		char hex[65] = "";

		// add
		uintb64 res;
		uint64_t carry = add_uintb64(&res, x, y);
		uint128 z = {res.limbs[0], carry};
		sprint_uint128(hex, z);
		printf("sum = %s\n\n", hex);

		// mul
		uintb64 resl;
		uintb64 resh = mul_uintb64(&resl, x, y);
		uint128 w = {resl.limbs[0], resh.limbs[0]};
		sprint_uint128(hex, w);
		printf("sum = %s\n\n", hex);
	}

	return 0;
}