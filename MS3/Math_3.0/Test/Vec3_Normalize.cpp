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

TEST(Vec3_Normalize, TestConfig::ALL)
{
#if Vec3_Normalize

	Vec3 v1(1.0f, 2.0f, 3.0f);

	v1.norm();

	CHECK(eq_float(v1[x],  0.2672f));
	CHECK(eq_float(v1[y],  0.5345f));
	CHECK(eq_float(v1[z], 0.80174f));


#endif
} TEST_END

// ---  End of File ---------------
