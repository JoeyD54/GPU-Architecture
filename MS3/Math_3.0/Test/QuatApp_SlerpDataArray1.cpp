//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-----------------------------------------------------------------------------  

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"
#include "MathApp.h"

using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

#if QuatApp_SlerpDataArray1

Quat QuatSourceC[] =
{
	Quat(-0.006912f, -0.027648f,  0.000000f, 0.999594f),
	Quat(0.022118f, -0.005529f, -0.006912f, 0.999716f),
	Quat(0.000000f,  0.000000f,  0.000000f, 1.000000f),
	Quat(0.002764f, -0.113358f,  0.029030f, 0.993126f),
	Quat(-0.164508f, -0.510112f, -0.062208f, 0.841934f),
	Quat(0.000000f,  0.023501f, -0.226717f, 0.973677f),
	Quat(0.016589f,  0.099534f, -0.015206f, 0.994780f),
	Quat(-0.001382f,  0.129947f, -0.026265f, 0.991172f),
	Quat(-0.157596f,  0.504583f,  0.143771f, 0.836594f),
	Quat(0.006912f, -0.008294f,  0.276484f, 0.960958f),
	Quat(-0.013824f, -0.004147f,  0.033178f, 0.999345f),
	Quat(-0.033178f,  0.004147f,  0.000000f, 0.999441f),
	Quat(-0.132712f,  0.004147f,  0.001382f, 0.991145f),
	Quat(0.058061f,  0.124418f,  0.060826f, 0.988660f),
	Quat(-0.270954f,  0.034560f, -0.052531f, 0.960536f),
	Quat(-0.023501f, -0.110593f, -0.060826f, 0.991724f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.066356f, -0.045619f, -0.031795f, 0.996245f),
	Quat(-0.317956f,  0.012441f, -0.047002f, 0.946858f),
	Quat(-0.004147f,  0.066356f, -0.037325f, 0.997089f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.000000f, -0.022118f,  0.145153f, 0.989161f),
	Quat(-0.000000f,  0.022118f, -0.145153f,-0.989161f),
	Quat(-0.006912f, -0.027648f,  0.000000f, 0.999594f),
};

#define numQuatC (sizeof(QuatSourceC)/sizeof(QuatSourceC[0]))

Quat QuatTargetC[] =
{
	Quat(-0.002764f, -0.024883f,  0.001382f, 0.999686f),
	Quat(0.020736f, -0.001382f, -0.008294f, 0.999750f),
	Quat(0.000000f,  0.000000f,  0.000000f, 1.000000f),
	Quat(0.002764f, -0.114741f,  0.027648f, 0.993007f),
	Quat(-0.163125f, -0.507347f, -0.058061f, 0.844167f),
	Quat(0.001382f,  0.023501f, -0.218422f, 0.975570f),
	Quat(0.019353f,  0.106446f, -0.012441f, 0.994052f),
	Quat(-0.001382f,  0.128565f, -0.026265f, 0.991352f),
	Quat(-0.158978f,  0.500435f,  0.136859f, 0.839976f),
	Quat(0.008294f, -0.005529f,  0.301367f, 0.953456f),
	Quat(-0.009676f,  0.005529f,  0.020736f, 0.999723f),
	Quat(-0.031795f,  0.000000f,  0.001382f, 0.999493f),
	Quat(-0.131330f,  0.001382f,  0.001382f, 0.991337f),
	Quat(0.059444f,  0.114741f,  0.058061f, 0.989914f),
	Quat(-0.283396f,  0.026265f, -0.041472f, 0.957746f),
	Quat(-0.013824f, -0.099534f, -0.051149f, 0.993622f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.067738f, -0.059444f, -0.038707f, 0.995178f),
	Quat(-0.312426f,  0.009676f, -0.035942f, 0.949212f),
	Quat(-0.009676f,  0.073268f, -0.024883f, 0.996955f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.005529f, -0.001382f,  0.194920f, 0.980802f),
	Quat(0.005529f, -0.001382f,  0.194920f, 0.980802f),
	Quat(0.002764f,  0.024883f, -0.001382f,-0.999686f),
};

Quat QuatResultC[] =
{
	Quat(-0.004123f, -0.025789f,  0.000929f, 0.999656f),
	Quat(0.021189f, -0.002740f, -0.007841f, 0.999739f),
	Quat(0.000000f,  0.000000f,  0.000000f, 1.000000f),
	Quat(0.002764f, -0.114288f,  0.028101f, 0.993046f),
	Quat(-0.163578f, -0.508253f, -0.059419f, 0.843436f),
	Quat(0.000929f,  0.023501f, -0.221138f, 0.974950f),
	Quat(0.018448f,  0.104182f, -0.013347f, 0.994290f),
	Quat(-0.001382f,  0.129018f, -0.026265f, 0.991293f),
	Quat(-0.158525f,  0.501794f,  0.139123f, 0.838869f),
	Quat(0.007841f, -0.006435f,  0.293218f, 0.955913f),
	Quat(-0.011035f,  0.002360f,  0.024810f, 0.999599f),
	Quat(-0.032248f,  0.001358f,  0.000929f, 0.999476f),
	Quat(-0.131782f,  0.002287f,  0.001382f, 0.991274f),
	Quat(0.058991f,  0.117910f,  0.058967f, 0.989504f),
	Quat(-0.279321f,  0.028982f, -0.045094f, 0.958660f),
	Quat(-0.016993f, -0.103156f, -0.054318f, 0.993001f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.067285f, -0.054916f, -0.036444f, 0.995528f),
	Quat(-0.314237f,  0.010582f, -0.039564f, 0.948441f),
	Quat(-0.007865f,  0.071004f, -0.028958f, 0.996999f),
	Quat(0.069120f,  0.000000f,  0.000000f, 0.997608f),
	Quat(0.003719f,-0.008177f,0.178679f,0.983866f),
	Quat(-0.003719f,0.008177f,-0.178679f,-0.983866f),
	Quat(-0.004122f,-0.025789f,0.000929f,0.999656f)
};
#endif

TEST(QuatApp_SlerpDataArray1, TestConfig::ALL)
{
#if QuatApp_SlerpDataArray1

	int i;

	// Slerp Data Test	
	Quat out2[numQuatC];
	QuatApp::SlerpArray(out2, QuatSourceC, QuatTargetC, 1.0f, numQuatC);

	i = 0;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 1;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 2;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 3;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 4;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 5;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 6;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 7;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 8;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 9;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 10;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 11;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 12;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 13;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 14;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 15;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 16;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 17;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 18;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 19;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 20;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 21;
	CHECK(eq_float(out2[i][x], QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], QuatTargetC[i][w]));

	i = 22;
	CHECK(eq_float(out2[i][x], -QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], -QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], -QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], -QuatTargetC[i][w]));

	i = 23;
	CHECK(eq_float(out2[i][x], -QuatTargetC[i][x]));
	CHECK(eq_float(out2[i][y], -QuatTargetC[i][y]));
	CHECK(eq_float(out2[i][z], -QuatTargetC[i][z]));
	CHECK(eq_float(out2[i][w], -QuatTargetC[i][w]));

#endif
} TEST_END


// --- End of File ---
