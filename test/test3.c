#include<serint/double_parts.h>
#include<serint/large_uints.h>
#include<serint/large_ints.h>

#include<stdio.h>
#include<inttypes.h>

void print_as_decimal3(uint256 a)
{
	char buffer[100];
	uint32_t bytes = serialize_to_decimal_uint256(buffer, a);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

void print_as_decimal4(int256 a)
{
	char buffer[100];
	uint32_t bytes = serialize_to_decimal_int256(buffer, a);
	buffer[bytes] = '\0';
	printf("%s", buffer);
}

uint256 decimal_to_uint256(char* b)
{
	uint256 l = get_0_uint256();
	while((*b) != 0)
	{
		mul_uint256(&l, l, get_uint256(10));
		add_uint256(&l, l, get_uint256((*b) - '0'));
		b++;
	}
	return l;
}

int256 decimal_to_int256(char* b)
{
	int is_neg = 0;
	int256 l = get_0_int256();
	if((*b) == '-')
	{
		is_neg = 1;
		b++;
	}
	while((*b) != 0)
	{
		mul_int256(&l, l, get_int256(10));
		add_int256(&l, l, get_int256((*b) - '0'));
		b++;
	}
	if(is_neg)
		mul_int256(&l, l, get_int256(-1));
	return l;
}

void print_decomposed_double(double d)
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
			printf(" !>! ");break;
		default :
			printf(" <%d> ", res);break;
	}
	printf("%a\n", d);
	printf("\n\n");
}

void compare_int256_and_double(int256 l, double d)
{
	int res = compare_int256_double(l, d);
	print_as_decimal4(l);
	switch(res)
	{
		case -1 :
			printf(" < ");break;
		case 0 :
			printf(" == ");break;
		case 1 :
			printf(" > ");break;
		case 2 :
			printf(" !>! ");break;
		default :
			printf(" <%d> ", res);break;
	}
	printf("%a\n", d);
	printf("\n\n");
}

void convert_unsigned_and_back(double d)
{
	printf("%lf -> ", d);
	uint256 l;
	if(!convert_from_double_uint256(&l, d))
	{
		printf("errored\n\n");
		return;
	}
	else
	{
		print_as_decimal3(l);
		printf("\n\n");
		return;
	}
}

void convert_signed_and_back(double d)
{
	printf("%lf -> ", d);
	int256 l;
	if(!convert_from_double_int256(&l, d))
	{
		printf("errored\n\n");
		return;
	}
	else
	{
		print_as_decimal4(l);
		printf("\n\n");
		return;
	}
}

int main()
{
	print_decomposed_double(NAN);

	print_decomposed_double(-NAN);

	print_decomposed_double(INFINITY);

	print_decomposed_double(-INFINITY);

	print_decomposed_double(0.5);

	print_decomposed_double(-0.5);

	print_decomposed_double(50);

	print_decomposed_double(-50);

	print_decomposed_double(125969.12345);

	print_decomposed_double(-125969.12345);

	print_decomposed_double(0.0);

	print_decomposed_double(-0.0);






	uint256 l[] = {
		get_0_uint256(),
		get_1_uint256(),
		get_uint256(500),
		get_uint256(501),
		decimal_to_uint256("56575887454795"),
		decimal_to_uint256("56575887454796"),
		get_max_uint256(),
	};

	double d[] = {
		-NAN,
		+NAN,
		-INFINITY,
		-(0x1p256),
		-(0x1.ffffffffffffep255),
		-(0x1p255),
		-56575887454795.78165891658,
		-7454795.78165891658,
		-500.05445146,
		-1.0,
		-0.865682786,
		-0.7645398988980,
		-0.5,
		-0.0,
		0.0,
		0.5,
		0.7645398988980,
		1.0,
		3.5,
		3.75,
		77.5895,
		500.5747,
		56575887454795.78165891658,
		0x1.ffffffffffffep255,
		0x1p256,
		INFINITY,
	};

	for(int i = 0; i < sizeof(l)/sizeof(l[0]); i++)
	{
		for(int j = 0; j < sizeof(d)/sizeof(d[0]); j++)
		{
			compare_uint256_and_double(l[i], d[j]);
		}
		printf("\n\n");
	}

	compare_uint256_and_double(decimal_to_uint256("1606938044258990275541962092341162602522202993782792835301376"), 0x1p200);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("1606938044258990275541962092341162602522202993782792835301375"), 0x1p200);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("1606938044258990275541962092341162602522202993782792835301377"), 0x1p200);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("115792089237316195423570985008687907853269984665640564039457584007913129639680"), 0x1.ffffffffffffep255);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("115792089237316195423570985008687907853269984665640564039457584007913129639424"), 0x1.ffffffffffffep255);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("115792089237316182568066630936765703517573245936339743861833633745570447228928"), 0x1.ffffffffffffep255);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("115792089237316195423570985008687907853269984665640564039457584007913129639934"), 0x1.ffffffffffffep255);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("115792089237316195423570985008687907853269984665640564039457584007913129639935"), 0x1p256);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("1"), 4.9406564584124654e-324);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("0"), 4.9406564584124654e-324);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("9007199254740992"), 9007199254740992.0);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("9007199254740993"), 9007199254740992.0);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("500"), 499.99999999999994);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("500"), 500.00000000000006);
	printf("\n\n");

	compare_uint256_and_double(decimal_to_uint256("18446744073709551617"), 18446744073709551616.0);
	printf("\n\n");

	int256 s[] = {
		get_min_int256(),
		get_int256(-501),
		get_int256(-500),
		decimal_to_int256("-56575887454796"),
		decimal_to_int256("-56575887454795"),
		get_int256(-1),
		get_0_int256(),
		get_1_int256(),
		get_int256(500),
		get_int256(501),
		decimal_to_int256("56575887454795"),
		decimal_to_int256("56575887454796"),
		get_max_int256(),
	};

	for(int i = 0; i < sizeof(s)/sizeof(s[0]); i++)
	{
		for(int j = 0; j < sizeof(d)/sizeof(d[0]); j++)
		{
			compare_int256_and_double(s[i], d[j]);
		}
		printf("\n\n");
	}








	for(int i = 0 ; i < sizeof(d) / sizeof(d[0]); i++)
	{
		convert_unsigned_and_back(d[i]);
	}
	printf("\n\n\n");

	for(int i = 0 ; i < sizeof(d) / sizeof(d[0]); i++)
	{
		convert_signed_and_back(d[i]);
	}
	printf("\n\n\n");

	return 0;
}