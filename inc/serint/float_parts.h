#ifndef FLOAT_PARTS_H
#define FLOAT_PARTS_H

#include<math.h>
#include<float.h>

typedef struct float_parts float_parts;
struct float_parts
{
	int is_neg:1; // this bit is always present, be the number 0, nan, inf or anything real

	int is_nan:1; // if this is set, no attributes needed further

	int is_inf:1; // if this is set, it is infinity, no attributes needed further

	int64_t exp; // exponent of the corresponing float + number of bits in mantissa of the floating type
	uint64_t mant; // mantissa as an integer
};

static inline float_parts make_floating_parts(double d)
{
	float_parts res = {};

	res.is_neg = signbit(d);

	if(isnan(d))
	{
		res.is_nan = 1;
		return res;
	}

	if(isinf(d))
	{
		res.is_inf = 1;
		return res;
	}

	if(d == 0.0)
	{
		res.exp = 0;
		res.mant = 0;
		return res;
	}

	int e;
	double m = frexp(fabs(d), &e);

	res.mant = (uint64_t)scalbn(m, DBL_MANT_DIG);
	res.exp = ((int64_t)e) - DBL_MANT_DIG;

	return res;
}

#endif