#include<serint/double_parts.h>

#include<stdio.h>
#include<inttypes.h>

int main()
{
	double_parts p;

	p = decompose_double(0.5);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(-0.5);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(50);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(-50);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(125969.12345);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(-125969.12345);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(0.0);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	p = decompose_double(-0.0);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", p.is_neg, p.is_nan, p.is_inf, p.exp, p.mant);

	return 0;
}