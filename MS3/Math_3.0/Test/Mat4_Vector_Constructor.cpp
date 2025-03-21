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

TEST(Mat4_Vector_Constructor, TestConfig::ALL)
{
#if Mat4_Vector_Constructor

	Vec4 V0(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 V1(7.0f, 6.0f, 5.0f, 3.0f);
	Vec4 V2(-4.0f, -2.0f, -1.0f, -4.0f);
	Vec4 V3(9.0f, -7.0f, -2.0f, 5.0f);

	CHECK(V0[x] == 1.0f);
	CHECK(V0[y] == 2.0f);
	CHECK(V0[z] == 3.0f);
	CHECK(V0[w] == 4.0f);
	CHECK(V1[x] == 7.0f);
	CHECK(V1[y] == 6.0f);
	CHECK(V1[z] == 5.0f);
	CHECK(V1[w] == 3.0f);
	CHECK(V2[x] == -4.0f);
	CHECK(V2[y] == -2.0f);
	CHECK(V2[z] == -1.0f);
	CHECK(V2[w] == -4.0f);
	CHECK(V3[x] == 9.0f);
	CHECK(V3[y] == -7.0f);
	CHECK(V3[z] == -2.0f);
	CHECK(V3[w] == 5.0f);

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
	CHECK(eq_float(M[m15], 5.0f));

#endif
} TEST_END

// --- End of File ---
