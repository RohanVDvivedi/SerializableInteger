#include<serint/double_parts.h>

int main()
{
	double_parts p;

	p = decompose_double(0.5);

	p = decompose_double(-0.5);

	p = decompose_double(50);

	p = decompose_double(-50);

	p = decompose_double(125969.12345);

	p = decompose_double(-125969.12345);

	p = decompose_double(0.0);

	p = decompose_double(-0.0);

	return 0;
}