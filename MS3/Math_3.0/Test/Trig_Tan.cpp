//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"
 
using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

static float AngleTest_0_2PI_C[] // 0-2PI
{
	0.0f,
	1.0f * MATH_PI8,
	2.0f * MATH_PI8,
	3.0f * MATH_PI8,
	4.0f * MATH_PI8,
	5.0f * MATH_PI8,
	6.0f * MATH_PI8,
	7.0f * MATH_PI8,
	8.0f * MATH_PI8,
	9.0f * MATH_PI8,
	10.0f * MATH_PI8,
	11.0f * MATH_PI8,
	12.0f * MATH_PI8,
	13.0f * MATH_PI8,
	14.0f * MATH_PI8,
	15.0f * MATH_PI8,
	16.0f * MATH_PI8
};

TEST(Trig_Tan, TestConfig::ALL)
{
#if Trig_Tan

	float OutAngle[sizeof(AngleTest_0_2PI_C) / sizeof(AngleTest_0_2PI_C[0])]{0};

	float *pOut = &OutAngle[0];
	for(float x : AngleTest_0_2PI_C)
	{
		*pOut++ = Trig::tan(x + 0.15f);
	}

	CHECK(eq_float(OutAngle[0], 0.1511f));
	CHECK(eq_float(OutAngle[1], 0.6031f));
	CHECK(eq_float(OutAngle[2], 1.3561f));
	CHECK(eq_float(OutAngle[3], 4.0391f));
	CHECK(eq_float(OutAngle[4], -6.6166f));
	CHECK(eq_float(OutAngle[5], -1.6581f));
	CHECK(eq_float(OutAngle[6], -0.7374f));
	CHECK(eq_float(OutAngle[7], -0.2476f));
	CHECK(eq_float(OutAngle[8], 0.1511f));
	CHECK(eq_float(OutAngle[9], 0.6031f));
	CHECK(eq_float(OutAngle[10], 1.3561f));
	CHECK(eq_float(OutAngle[11], 4.0391f));
	CHECK(eq_float(OutAngle[12], -6.6166f));
	CHECK(eq_float(OutAngle[13], -1.6581f));
	CHECK(eq_float(OutAngle[14], -0.7374f));
	CHECK(eq_float(OutAngle[15], -0.2476f));
	CHECK(eq_float(OutAngle[16], 0.1511f));

#endif
} TEST_END

// ---  End of File ---
