#include<serint/double_parts.h>

#include<stdio.h>
#include<inttypes.h>

void print_decomposed_doiuble(double d)
{
	double_parts p = decompose_double(d);
	printf("%f\n", d);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n\n", !!(p.is_neg), !!(p.is_nan), !!(p.is_inf), p.exp, p.mant);
}

int main()
{
	print_decomposed_doiuble(NAN);

	print_decomposed_doiuble(-NAN);

	print_decomposed_doiuble(INFINITY);

	print_decomposed_doiuble(-INFINITY);

	print_decomposed_doiuble(0.5);

	print_decomposed_doiuble(-0.5);

	print_decomposed_doiuble(50);

	print_decomposed_doiuble(-50);

	print_decomposed_doiuble(125969.12345);

	print_decomposed_doiuble(-125969.12345);

	print_decomposed_doiuble(0.0);

	print_decomposed_doiuble(-0.0);

	return 0;
}