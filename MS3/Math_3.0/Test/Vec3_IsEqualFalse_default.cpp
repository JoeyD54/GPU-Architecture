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

TEST(Vec3_IsEqualFalse_default, TestConfig::ALL)
{
#if Vec3_IsEqualFalse_default

	Vec3 v1(1.0f, 2.0f, 3.0f);
	Vec3 v2(9.0f, -3.0f, 5.0f);
	bool bvalue1;

	bvalue1 = v1.isEqual(v2);

	CHECK(bvalue1 == false);

#endif
} TEST_END

// ---  End of File ---------------
