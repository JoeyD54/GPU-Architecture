//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"

using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST( Quat_IsNegEqual2, TestConfig::ALL)
{
#if Quat_IsNegEqual2

	Quat  q1,q2;
	bool bvalue1;

	// IsNegEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(-1.0f,-2.0f,-3.05f,-4.0f);
	
	// q1.isNegEqual(q2, 0.1f)
	bvalue1 = q1.isNegEqual(q2, 0.1f);

	CHECK( bvalue1 == true );

#endif
} TEST_END


// ---  End of File ---------------
