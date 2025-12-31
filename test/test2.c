#include<serint/large_ints.h>

void print_as_decimal(int256 a)
{
	char buffer[100];
	uint32_t bytes = serialize_to_decimal_int256(buffer, a);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

void print_as_decimal2(int256 high, int256 low)
{
	int512 res;
	for(int i = 0; i < 4; i++)
		res.raw_uint_value.limbs[i] = low.raw_uint_value.limbs[i];
	for(int i = 0; i < 4; i++)
		res.raw_uint_value.limbs[i+4] = high.raw_uint_value.limbs[i];

	char buffer[200];
	uint32_t bytes = serialize_to_decimal_int512(buffer, res);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

void print_as_decimal3(uint256 a)
{
	char buffer[100];
	uint32_t bytes = serialize_to_decimal_uint256(buffer, a);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

int main()
{
	// simple operations
	{
		print_int256(get_0_int256()); printf("\n\n");
		print_int256(get_1_int256()); printf("\n\n");
		print_int256(get_min_int256()); printf("\n\n");
		print_int256(get_max_int256()); printf("\n\n");
		print_int256(get_int256(134)); printf("\n\n");
		print_int256(get_int256(-134)); printf("\n\n");
		print_int256(get_bitmask_lower_n_bits_set_int256(100)); printf("\n\n");
	}

	// test bitwise operations
	{
		int256 a = {{0xa000500012345678, 0x5555aaaa12345678, 0x123456780000abcd, 0xffff0000ffff0000}};
		int256 b = {{0x5000400087654321, 0xaaaa555512345678, 0x1234000000005678, 0x0000ffffffff0000}};

		{
			printf("0x");
			print_int256(a);
			printf(" & 0x");
			print_int256(b);
			printf(" == 0x");
			print_int256(bitwise_and_int256(a, b));
			printf("\n\n");
		}

		{
			printf("0x");
			print_int256(a);
			printf(" | 0x");
			print_int256(b);
			printf(" == 0x");
			print_int256(bitwise_or_int256(a, b));
			printf("\n\n");
		}

		{
			printf("0x");
			print_int256(a);
			printf(" ^ 0x");
			print_int256(b);
			printf(" == 0x");
			print_int256(bitwise_xor_int256(a, b));
			printf("\n\n");
		}

		{
			printf("(~0x");
			print_int256(a);
			printf(") & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(bitwise_not_int256(a));
			printf("\n\n");
		}

		{
			printf("(~0x");
			print_int256(b);
			printf(") & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(bitwise_not_int256(b));
			printf("\n\n");
		}

		{
			printf("(0x");
			print_int256(a);
			printf(" << 13) & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(left_shift_int256(a, 13));
			printf("\n\n");
		}

		{
			printf("(0x");
			print_int256(b);
			printf(" << 13) & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(left_shift_int256(b, 13));
			printf("\n\n");
		}

		{
			printf("(0xffff");
			print_int256(a);
			printf(" >> 13) & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(right_shift_int256(a, 13));
			printf("\n\n");
		}

		{
			printf("(0x0000");
			print_int256(b);
			printf(" >> 13) & 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff == 0x");
			print_int256(right_shift_int256(b, 13));
			printf("\n\n");
		}
	}

	// testing arithmetic operations
	{
		// three numbers negative, 0 and a positive
		int256 nums[] = {
			{
				.raw_uint_value = {{
					[3] = 0xffffffffffffffff,
					[2] = 0x12ffffffff901189,
					[1] = 0x0fffefd60000000f,
					[0] = 0x53356ffb6af4f0f0,
				}}
			},
			{
				.raw_uint_value = {{
					[3] = 0xffffffffffffffff,
					[2] = 0x1234000432901189,
					[1] = 0x0fffefd6cfbfaf9f,
					[0] = 0x5ffbffb6af4f0f00,
				}}
			},
			{
				.raw_uint_value = {{
					[3] = 0xffffffffffffffff,
					[2] = 0xffffffffffffffff,
					[1] = 0xffffffffffffffff,
					[0] = 0xfffffff6af4f0f00,
				}}
			},
			get_0_int256(),
			{
				.raw_uint_value = {{
					[3] = 0x0000000000000000,
					[2] = 0x0000000000000000,
					[1] = 0x0000000000000000,
					[0] = 0x0000000000000025,
				}}
			},
			{
				.raw_uint_value = {{
					[3] = 0x0000000000000000,
					[2] = 0x01f2f3f4f5f6f7f8,
					[1] = 0x0fffefdfcfbfaf9f,
					[0] = 0x1234876543290118,
				}}
			},
			{
				.raw_uint_value = {{
					[3] = 0x0000000000000000,
					[2] = 0xfeeeeef4f5f6f7f8,
					[1] = 0x0f9999dfcfbfaf9f,
					[0] = 0x1234876588888118,
				}}
			},
		};

		#define TEST_SUBJECTS (sizeof(nums)/sizeof(nums[0]))


		char* cmps[] = {
			"<",
			"==",
			">"
		};
		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			for(int j = 0; j < TEST_SUBJECTS; j++)
			{
				int cmp = compare_int256(nums[i], nums[j]);
				print_as_decimal(nums[i]);
				printf(" %s ", cmps[cmp+1]);
				print_as_decimal(nums[j]);
				printf("\n\n");
			}
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			for(int j = 0; j < TEST_SUBJECTS; j++)
			{
				int256 res;
				add_int256(&res, nums[i], nums[j]);
				printf("(");
				print_as_decimal(nums[i]);
				printf(") + (");
				print_as_decimal(nums[j]);
				printf(") == ");
				print_as_decimal(res);
				printf("\n\n");
			}
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			for(int j = 0; j < TEST_SUBJECTS; j++)
			{
				int256 res;
				sub_int256(&res, nums[i], nums[j]);
				printf("(");
				print_as_decimal(nums[i]);
				printf(") - (");
				print_as_decimal(nums[j]);
				printf(") == ");
				print_as_decimal(res);
				printf("\n\n");
			}
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			for(int j = 0; j < TEST_SUBJECTS; j++)
			{
				int256 high;
				int256 low;
				high = mul_int256(&low, nums[i], nums[j]);
				printf("(");
				print_as_decimal(nums[i]);
				printf(") * (");
				print_as_decimal(nums[j]);
				printf(") == ");
				print_as_decimal2(high, low);
				printf("\n\n");
			}
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			for(int j = 0; j < TEST_SUBJECTS; j++)
			{
				if(is_zero_int256(nums[j]))
					continue;

				int256 rem;
				int256 quo;
				rem = div_int256(&quo, nums[i], nums[j]);
				printf("(");
				print_as_decimal(nums[i]);
				printf(") == (");
				print_as_decimal(nums[j]);
				printf(") * (");
				print_as_decimal(quo);
				printf(") + (");
				print_as_decimal(rem);
				printf(")\n\n");
			}
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			int64_t value = 0;
			int res = cast_to_int64_from_int256(&value, nums[i]);
			print_as_decimal(nums[i]);
			printf(" => %d => %"PRId64"\n\n", res, value);
		}

		for(int i = 0; i < TEST_SUBJECTS; i++)
		{
			double res = convert_to_double_int256(nums[i]);
			print_as_decimal(nums[i]);
			printf(" -> %lf\n\n", res);
		}
	}

	// testing compare for large_int and large_uint
	{
		int256 x[] = {
			get_min_int256(),
			{{{
				[3] = 0x1000000000000000,
				[2] = 0x123456789abcdef0,
				[1] = 0x00001234abdcef00,
				[0] = 0x0000000000000000,
			}}},
			get_0_int256(),
			get_1_int256(),
			{{{
				[3] = 0x0000000000000000,
				[2] = 0x123456789abcdef0,
				[1] = 0x00001234abdcef00,
				[0] = 0x0000000000000000,
			}}},
			get_max_int256(),
		};

		uint256 y[] = {
			get_0_uint256(),
			get_1_uint256(),
			{{
				[3] = 0x0000000000000000,
				[2] = 0x123456789abcdef0,
				[1] = 0x00001234abdcef00,
				[0] = 0x0000000000000000,
			}},
			{{
				[3] = 0xffffffffffff0000,
				[2] = 0x123456789abcdef0,
				[1] = 0x00001234abdcef00,
				[0] = 0x0000000000000000,
			}},
			get_max_uint256(),
		};

		char* cmps[] = {
			"<",
			"==",
			">"
		};
		for(int i = 0; i < sizeof(x)/sizeof(int256); i++)
		{
			for(int j = 0; j < sizeof(y)/sizeof(uint256); j++)
			{
				printf("(");
				print_as_decimal(x[i]);
				printf(") %s (", cmps[compare_int256_uint256(x[i], y[j]) + 1]);
				print_as_decimal3(y[j]);
				printf(")\n\n");
			}
		}

		for(int i = 0; i < sizeof(x)/sizeof(int256); i++)
		{
			double res = convert_to_double_int256(x[i]);
			print_as_decimal(x[i]);
			printf(" -> %lf\n\n", res);
		}

		for(int i = 0; i < sizeof(y)/sizeof(uint256); i++)
		{
			double res = convert_to_double_uint256(y[i]);
			print_as_decimal3(y[i]);
			printf(" -> %lf\n\n", res);
		}
	}

	// serialization deserialization
	{
		char bytes[12];

		int256 x[] = {
			{{{
				[3] = 0xffffffffffffffff,
				[2] = 0xffffffffffffffff,
				[1] = 0xfffffffffbdcef00,
				[0] = 0x0000000000000000,
			}}},
			get_int256(-111),
			get_int256(-100),
			get_int256(-1),
			get_0_int256(),
			get_1_int256(),
			get_int256(100),
			get_int256(333),
			{{{
				[3] = 0x0000000000000000,
				[2] = 0x0000000000000000,
				[1] = 0x000000001bdcef00,
				[0] = 0x0000000000000000,
			}}},
		};

		for(int i = 0; i < sizeof(x)/sizeof(int256); i++)
		{
			serialize_int256(bytes, 12, x[i]);
			int256 res = deserialize_int256(bytes, 12);
			printf("(");
			print_as_decimal(x[i]);
			printf(") == (");
			print_as_decimal(res);
			printf(")\n\n");
		}
	}

	// find first bit set
	{
		int256 x = {{{0, 0xabcd, 0xabcd000000000000, 0}}};
		print_int256(x);
		printf("\n\n");
		printf("%u\n", get_first_encountered_bit_from_int256(x, 0, 0));
		printf("%u\n", get_first_encountered_bit_from_int256(x, 0, 1));
		printf("%u\n", get_first_encountered_bit_from_int256(x, 1, 0));
		printf("%u\n\n", get_first_encountered_bit_from_int256(x, 1, 1));
		x = bitwise_not_int256(x);
		print_int256(x);
		printf("\n\n");
		printf("%u\n", get_first_encountered_bit_from_int256(x, 0, 0));
		printf("%u\n", get_first_encountered_bit_from_int256(x, 0, 1));
		printf("%u\n", get_first_encountered_bit_from_int256(x, 1, 0));
		printf("%u\n\n", get_first_encountered_bit_from_int256(x, 1, 1));
	}

	return 0;
}