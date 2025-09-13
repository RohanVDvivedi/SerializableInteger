#include<serint/large_ints.h>

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

	return 0;
}