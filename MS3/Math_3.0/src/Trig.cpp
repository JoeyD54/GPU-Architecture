//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

namespace Azul
{

	// Do your magic here
	float Trig::sqrt(const float val)
	{
		return sqrtf(val);
	}

	// Do your magic here
	float Trig::sqrtf(const float val)
	{
		float result = 0;

		if (val == 0 || val == 1)
		{
			return val;
		}
		else
		{
			float temp = 0;
			float number = val;
			float sqrt = number / 2;

			while (sqrt != temp)
			{
				temp = sqrt;
				sqrt = (number / temp + temp) / 2;
			}
			result = sqrt;
		}

		return result;
	}

	float Trig::rsqrt(float val)
	{
		float result = 1 / Trig::sqrtf(val);

		return result;
	}

	float Trig::cos(float val)
	{
		return cosf(val);
	}

	float Trig::acos(float val)
	{
		return acosf(val);
	}

	float Trig::sin(float val)
	{
		return sinf(val);
	}

	float Trig::asin(float val)
	{
		return asinf(val);
	}

	void Trig::cossin(float& outCos, float& outSin, float inX)
	{
		outCos = cos(inX);
		outSin = sin(inX);
	}

	float Trig::tan(float val)
	{
		return tanf(val);
	}

	float Trig::atan(float val)
	{
		return atanf(val);
	}

	float Trig::atan2(float x, float y)
	{
		return atan2f(x, y);
	}

}

//--- End of File ---
