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

TEST(Mat4_Special_RotX, TestConfig::ALL)
{
#if Mat4_Special_RotX

	// Rot_X Type Constructor:
	Mat4 Rx(Mat4::Rot1::X, 1.0471975512f);

	CHECK(Rx[m0] == 1.0f);
	CHECK(Rx[m1] == 0.0f);
	CHECK(Rx[m2] == 0.0f);
	CHECK(Rx[m3] == 0.0f);
	CHECK(Rx[m4] == 0.0f);
	CHECK(eq_float(Rx[m5], 0.5f));
	CHECK(eq_float(Rx[m6], 0.866f));
	CHECK(Rx[m7] == 0.0f);
	CHECK(Rx[m8] == 0.0f);
	CHECK(eq_float(Rx[m9], -0.866f));
	CHECK(eq_float(Rx[m10], 0.5f));
	CHECK(Rx[m11] == 0.0f);
	CHECK(Rx[m12] == 0.0f);
	CHECK(Rx[m13] == 0.0f);
	CHECK(Rx[m14] == 0.0f);
	CHECK(eq_float(Rx[m15],1.0f));

#endif
} TEST_END

// --- End of File ---
