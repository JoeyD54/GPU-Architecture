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

TEST(Vec3_Mult_Mat4,TestConfig::ALL)
{
#if Vec3_Mult_Mat4

	Vec3 vA(2.0f, 3.0f, 4.0f);
	Vec4 vOut;

	CHECK(vA[x] == 2.0f);
	CHECK(vA[y] == 3.0f);
	CHECK(vA[z] == 4.0f);
	
	Vec4 V0(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 V1(7.0f, 6.0f, 5.0f, 3.0f);
	Vec4 V2(-4.0f, -2.0f, -1.0f, -4.0f);
	Vec4 V3(9.0f, -7.0f, -2.0f, 5.0f);

	Mat4 M(V0, V1, V2, V3);

	CHECK(M[m0] == 1.0f);
	CHECK(M[m1] == 2.0f);
	CHECK(M[m2] == 3.0f);
	CHECK(M[m3] == 4.0f);
	CHECK(M[m4] == 7.0f);
	CHECK(M[m5] == 6.0f);
	CHECK(M[m6] == 5.0f);
	CHECK(M[m7] == 3.0f);
	CHECK(M[m8] == -4.0f);
	CHECK(M[m9] == -2.0f);
	CHECK(M[m10] == -1.0f);
	CHECK(M[m11] == -4.0f);
	CHECK(M[m12] == 9.0f);
	CHECK(M[m13] == -7.0f);
	CHECK(M[m14] == -2.0f);
	CHECK(eq_float(M[m15],5.0f));

	vOut = vA * M;

	CHECK(M[m0] == 1.0f);
	CHECK(M[m1] == 2.0f);
	CHECK(M[m2] == 3.0f);
	CHECK(M[m3] == 4.0f);
	CHECK(M[m4] == 7.0f);
	CHECK(M[m5] == 6.0f);
	CHECK(M[m6] == 5.0f);
	CHECK(M[m7] == 3.0f);
	CHECK(M[m8] == -4.0f);
	CHECK(M[m9] == -2.0f);
	CHECK(M[m10] == -1.0f);
	CHECK(M[m11] == -4.0f);
	CHECK(M[m12] == 9.0f);
	CHECK(M[m13] == -7.0f);
	CHECK(M[m14] == -2.0f);
	CHECK(eq_float(M[m15],5.0f));

	CHECK(vA[x] == 2.0f);
	CHECK(vA[y] == 3.0f);
	CHECK(vA[z] == 4.0f);

	CHECK(eq_float(vOut[x], 16.0f));
	CHECK(eq_float(vOut[y],  7.0f));
	CHECK(eq_float(vOut[z], 15.0f));
	CHECK(eq_float(vOut[w],  6.0f));

#endif
} TEST_END

// ---  End of File ---------------
