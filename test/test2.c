#include<serint/large_ints.h>

int main()
{
	// test bitwise operations
	{
		int256 a = {{0xa000500012345678, 0x5555aaaa12345678, 0x123456780000abcd, 0xffff0000ffff0000}};
		int256 b = {{0x5000400087654321, 0xaaaa555512345678, 0x1234000000005678, 0x0000ffffffff0000}};

		{
			printf("0x")
			print_int256(a);
			printf(" & 0x");
			print_int256(b);
			printf(" == ");
			print_int256(bitwise_and_int256(a, b));
			printf("\n\n");
		}

		{
			printf("0x")
			print_int256(a);
			printf(" | 0x");
			print_int256(b);
			printf(" == ");
			print_int256(bitwise_or_int256(a, b));
			printf("\n\n");
		}

		{
			printf("0x")
			print_int256(a);
			printf(" ^ 0x");
			print_int256(b);
			printf(" == ");
			print_int256(bitwise_xor_int256(a, b));
			printf("\n\n");
		}

		{
			printf("~");
			print_int256(a);
			printf(" == ");
			print_int256(bitwise_not_int256(a));
			printf("\n\n");
		}

		{
			printf("~");
			print_int256(b);
			printf(" == ");
			print_int256(bitwise_not_int256(b));
			printf("\n\n");
		}

		{
			print_int256(a);
			printf(" << 12 == ");
			print_int256(left_shift_int256(a, 12));
			printf("\n\n");
		}

		{
			printf("~");
			print_int256(b);
			printf(" << 12 == ");
			print_int256(left_shift_int256(b, 12));
			printf("\n\n");
		}

		{
			print_int256(a);
			printf(" >> 12 == ");
			print_int256(right_shift_int256(a, 12));
			printf("\n\n");
		}

		{
			printf("~");
			print_int256(b);
			printf(" >> 12 == ");
			print_int256(right_shift_int256(b, 12));
			printf("\n\n");
		}
	}

	return 0;
}