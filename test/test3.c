#include<serint/double_parts.h>
#include<serint/large_uints.h>

#include<stdio.h>
#include<inttypes.h>

void print_as_decimal3(uint256 a)
{
	char buffer[100];
	uint32_t bytes = serialize_to_decimal_uint256(buffer, a);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

void print_decomposed_doiuble(double d)
{
	double_parts p = decompose_double(d);
	printf("%lf\n", d);
	printf("is_neg = %d, is_nan = %d, is_inf = %d, exp = %"PRId64", mant = %"PRIu64"\n", !!(p.is_neg), !!(p.is_nan), !!(p.is_inf), p.exp, p.mant);
	double r = compose_double(p);
	printf("result identical after compose = %d\n\n", (d == r));
}

void compare_uint256_and_double(uint256 l, double d)
{
	int res = compare_uint256_double(l, d);
	print_as_decimal3(l);
	switch(res)
	{
		case -1 :
			printf(" < ");break;
		case 0 :
			printf(" == ");break;
		case 1 :
			printf(" > ");break;
		case 2 :
			printf(" !! ");break;
		default :
			printf(" <%d> ", res);break;
	}
	printf("%lf\n", d);
	printf("\n\n");
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