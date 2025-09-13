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
		int256 nums[7] = {
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


		char* cmps[] = {
			"<",
			"==",
			">"
		};
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				int cmp = compare_int256(nums[i], nums[j]);
				print_as_decimal(nums[i]);
				printf(" %s ", cmps[cmp+1]);
				print_as_decimal(nums[j]);
				printf("\n\n");
			}
		}

		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
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

		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
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

		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
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

		printf("def c_divmod(a, b):\n\t\tq = int(a / b)\n\t\tr = a - q * b\n\t\treturn (q, r)\n\n\n");

		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				if(is_zero_int256(nums[j]))
					continue;

				int256 rem;
				int256 quo;
				rem = div_int256(&quo, nums[i], nums[j]);
				printf("c_divmod(");
				print_as_decimal(nums[i]);
				printf(", ");
				print_as_decimal(nums[j]);
				printf(") == (");
				print_as_decimal(quo);
				printf(", ");
				print_as_decimal(rem);
				printf(")\n\n");
			}
		}
	}

	return 0;
}