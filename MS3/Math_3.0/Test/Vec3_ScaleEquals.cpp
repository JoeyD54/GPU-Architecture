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

TEST(Vec3_ScaleEquals, TestConfig::ALL)
{
#if Vec3_ScaleEquals

	Vec3 A(2.0f, 3.0f, 4.0f);
	const float s = 5.0f;

	CHECK(A[x] == 2.0f);
	CHECK(A[y] == 3.0f);
	CHECK(A[z] == 4.0f);

	A *= s;

	CHECK(A[x] == 10.0f);
	CHECK(A[y] == 15.0f);
	CHECK(A[z] == 20.0f);

#endif
} TEST_END

// ---  End of File ---------------
