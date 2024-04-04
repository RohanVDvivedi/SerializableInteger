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

	return 0;
}