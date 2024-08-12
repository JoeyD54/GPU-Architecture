//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// Do your magic here

    Mat3::Mat3()
    {
        this->_m0 = 0;
        this->_m1 = 0;
        this->_m2 = 0;
        this->_m3 = 0;
        this->_m4 = 0;
        this->_m5 = 0;
        this->_m6 = 0;
        this->_m7 = 0;
        this->_m8 = 0;
        this->_m9 = 0;
        this->_m10 = 0;
        this->_m11 = 0;
        this->_m12 = 0;
        this->_m13 = 0;
        this->_m14 = 0;
        this->_m15 = 0;

    }

    Mat3::Mat3(Vec4 vA, Vec4 vB, Vec4 vC, Vec4 vD)
    {
        this->_v0 = vA;
        this->_v1 = vB;
        this->_v2 = vC;
        this->_v3 = vD;

        this->SetMs(vA);
        this->SetMs(vB);
        this->SetMs(vC);
        this->SetMs(vD);
    }

    Mat3::Mat3(Vec4 vA, Vec4 vB, Vec4 vC)
    {
        //4th row
        Vec4 vD(0, 0, 0, 1);

        this->_v0 = vA;
        this->_v1 = vB;
        this->_v2 = vC;
        this->_v3 = vD;

        this->SetMs(vA);
        this->SetMs(vB);
        this->SetMs(vC);
        this->SetMs(vD);
    }

    Mat3::Mat3(Vec3 inVA, Vec3 inVB, Vec3 inVC)
    {
        //4th row
        Vec4 vA(inVA, 0);
        Vec4 vB(inVB, 0);
        Vec4 vC(inVC, 0);
        Vec4 vD(0, 0, 0, 1);

        this->_v0 = vA;
        this->_v1 = vB;
        this->_v2 = vC;
        this->_v3 = vD;

        this->SetMs(vA);
        this->SetMs(vB);
        this->SetMs(vC);
        this->SetMs(vD);
    }

    Mat3::Mat3(const Mat3& inMat3)
    {
        this->_v0 = inMat3._v0;
        this->_v1 = inMat3._v1;
        this->_v2 = inMat3._v2;
        this->_v3 = inMat3._v3;
    }

    Mat3::Mat3(const Mat4& inMat4)
    {
        this->_v0 = inMat4._v0;
        this->_v1 = inMat4._v1;
        this->_v2 = inMat4._v2;
        this->_v3 = inMat4._v3;
    }

    const Mat3& Mat3::operator=(const Mat3& inMat3)
    {
        this->_v0 = inMat3._v0;
        this->_v1 = inMat3._v1;
        this->_v2 = inMat3._v2;
        this->_v3 = inMat3._v3;

        return *this;
    }

    Mat3::~Mat3()
    {
    }

    Mat3 Mat3::T()
    {
        //swap rows and columns 
        //our Mat3 is a 4x4
        Vec3 v0 = Vec3(_rows[0][x], _rows[1][x], _rows[2][x]);
        Vec3 v1 = Vec3(_rows[0][y], _rows[1][y], _rows[2][y]);
        Vec3 v2 = Vec3(_rows[0][z], _rows[1][z], _rows[2][z]);

        *this = Mat3(v0, v1, v2);

        return *this;

    }

    Mat3 Mat3::getT()
    {
        //swap rows and columns 
        //our Mat3 is a 4x4
        Vec4 v0 = Vec4(_rows[0][x], _rows[1][x], _rows[2][x]);
        Vec4 v1 = Vec4(_rows[0][y], _rows[1][y], _rows[2][y]);
        Vec4 v2 = Vec4(_rows[0][z], _rows[1][z], _rows[2][z]);

        Mat3 tmpMat = Mat3(v0, v1, v2);
        //this = tmpMat;

        return tmpMat;
    }

    Mat3::Mat3(Mat3::Special special)
    {
        if (special == Mat3::Special::Identity)
        {
            this->_m0 = 1.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 1.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 1.0f;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
        else if (special == Mat3::Special::Zero)
        {
            this->_m0 = 0.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 0.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 0.0f;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 0.0f;
        }
    }

    //Mat3::Mat3(Mat3::Trans tran, float in1, float in2, float in3)
    //{
    //    if (tran == Mat3::Trans::XYZ)
    //    {
    //        this->_m0 = 1.0f;
    //        this->_m1 = 0.0f;
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = 1.0f;
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = 0.0f;
    //        this->_m10 = 1.0f;
    //        this->_m11 = 0.0f;
    //        this->_m12 = in1;
    //        this->_m13 = in2;
    //        this->_m14 = in3;
    //        this->_m15 = 1.0f;
    //    }
    //}

    //Mat3::Mat3(Mat3::Trans tran, Vec4 inVec4)
    //{
    //    float in1 = inVec4.x();
    //    float in2 = inVec4.y();
    //    float in3 = inVec4.z();

    //    if (tran == Mat3::Trans::XYZ)
    //    {
    //        this->_m0 = 1.0;
    //        this->_m1 = 0.0f;
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = 1.0;
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = 0.0f;
    //        this->_m10 = 1.0;
    //        this->_m11 = 0.0f;
    //        this->_m12 = in1;
    //        this->_m13 = in2;
    //        this->_m14 = in3;
    //        this->_m15 = 1.0f;
    //    }
    //}

    //Mat3::Mat3(Mat3::Scale scale, float in1, float in2, float in3)
    //{
    //    if (scale == Mat3::Scale::XYZ)
    //    {
    //        this->_m0 = in1;
    //        this->_m1 = 0.0f;
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = in2;
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = 0.0f;
    //        this->_m10 = in3;
    //        this->_m11 = 0.0f;
    //        this->_m12 = 0.0f;
    //        this->_m13 = 0.0f;
    //        this->_m14 = 0.0f;
    //        this->_m15 = 1.0f;
    //    }
    //}

    //Mat3::Mat3(Mat3::Scale scale, Vec4 inVec4)
    //{
    //    float in1 = inVec4.x();
    //    float in2 = inVec4.y();
    //    float in3 = inVec4.z();

    //    if (scale == Mat3::Scale::XYZ)
    //    {
    //        this->_m0 = in1;
    //        this->_m1 = 0.0f;
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = in2;
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = 0.0f;
    //        this->_m10 = in3;
    //        this->_m11 = 0.0f;
    //        this->_m12 = 0.0f;
    //        this->_m13 = 0.0f;
    //        this->_m14 = 0.0f;
    //        this->_m15 = 1.0f;
    //    }
    //}

    ////Mat3::Mat3(Mat3::Rot rot)
    ////{
    ////}

    //Mat3::Mat3(Mat3::Rot rot, Vec4& inVec4, float inFloat)
    //{
    //    if (rot == Mat3::Rot::AxisAngle)
    //    {
    //        // angle
    //        // axis;
    //        const float angle_a = 0.5f * inFloat;
    //        float cos_a;
    //        float sin_a;

    //        cos_a = cosf(angle_a);
    //        sin_a = sinf(angle_a);

    //        Vec4 qV = inVec4.getNorm();

    //        qV *= sin_a;

    //        Vec4 Q;
    //        Q[x] = qV[x];
    //        Q[y] = qV[y];
    //        Q[z] = qV[z];
    //        Q[w] = cos_a;

    //        // this function has been transposed
    //        float x2, y2, z2;
    //        float xx, xy, xz;
    //        float yy, yz, zz;
    //        float wx, wy, wz;

    //        // ADD test to make sure that quat is normalized

    //        x2 = Q[x] + Q[x];
    //        y2 = Q[y] + Q[y];
    //        z2 = Q[z] + Q[z];

    //        xx = Q[x] * x2;
    //        xy = Q[x] * y2;
    //        xz = Q[x] * z2;

    //        yy = Q[y] * y2;
    //        yz = Q[y] * z2;
    //        zz = Q[z] * z2;

    //        wx = Q[w] * x2;
    //        wy = Q[w] * y2;
    //        wz = Q[w] * z2;

    //        this->_m0 = 1.0f - (yy + zz);
    //        this->_m1 = xy + wz;
    //        this->_m2 = xz - wy;
    //        this->_m3 = 0.0f;

    //        this->_m4 = xy - wz;
    //        this->_m5 = 1.0f - (xx + zz);
    //        this->_m6 = yz + wx;
    //        this->_m7 = 0.0f;

    //        this->_m8 = xz + wy;
    //        this->_m9 = yz - wx;
    //        this->_m10 = 1.0f - (xx + yy);
    //        this->_m11 = 0.0f;

    //        this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
    //    }
    //}

    //Mat3::Mat3(Mat3::Rot1 rot, float inFloat)
    //{
    //    if (rot == Mat3::Rot1::X)
    //    {
    //        this->_m0 = 1.0f;
    //        this->_m1 = 0.0f;
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = Trig::cos(inFloat);
    //        this->_m6 = Trig::sin(inFloat);
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = -Trig::sin(inFloat);
    //        this->_m10 = Trig::cos(inFloat);
    //        this->_m11 = 0.0f;
    //        this->_m12 = 0.0f;
    //        this->_m13 = 0.0f;
    //        this->_m14 = 0.0f;
    //        this->_m15 = 1.0f;
    //    }
    //    else if (rot == Mat3::Rot1::Y)
    //    {
    //        this->_m0 = Trig::cos(inFloat);
    //        this->_m1 = 0.0f;
    //        this->_m2 = -Trig::sin(inFloat);
    //        this->_m3 = 0.0f;
    //        this->_m4 = 0.0f;
    //        this->_m5 = 1.0f;
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = Trig::sin(inFloat);
    //        this->_m9 = 0.0f;
    //        this->_m10 = Trig::cos(inFloat);
    //        this->_m11 = 0.0f;
    //        this->_m12 = 0.0f;
    //        this->_m13 = 0.0f;
    //        this->_m14 = 0.0f;
    //        this->_m15 = 1.0f;
    //    }
    //    else if (rot == Mat3::Rot1::Z)
    //    {
    //        this->_m0 = Trig::cos(inFloat);
    //        this->_m1 = Trig::sin(inFloat);
    //        this->_m2 = 0.0f;
    //        this->_m3 = 0.0f;
    //        this->_m4 = -Trig::sin(inFloat);
    //        this->_m5 = Trig::cos(inFloat);
    //        this->_m6 = 0.0f;
    //        this->_m7 = 0.0f;
    //        this->_m8 = 0.0f;
    //        this->_m9 = 0.0f;
    //        this->_m10 = 1.0f;
    //        this->_m11 = 0.0f;
    //        this->_m12 = 0.0f;
    //        this->_m13 = 0.0f;
    //        this->_m14 = 0.0f;
    //        this->_m15 = 1.0f;
    //    }
    //}

    //Mat3::Mat3(Mat3::Rot3 rot, float inFloatX, float inFloatY, float inFloatZ)
    //{
    //    Mat3 rotX;
    //    Mat3 rotY;
    //    Mat3 rotZ;

    //    if (rot == Mat3::Rot3::XYZ)
    //    {
    //        rotX.set(Mat3::Rot1::X, inFloatX);
    //        rotY.set(Mat3::Rot1::Y, inFloatY);
    //        rotZ.set(Mat3::Rot1::Z, inFloatZ);

    //        *this = rotX * rotY * rotZ;
    //    }
    //}

    Mat3 Mat3::operator*(Mat3 inMat3)
    {
        Mat3 newMat3;

        //Vec4or 1
        newMat3._m0 = this->m0() * inMat3.m0() + this->m1() * inMat3.m4() + this->m2() * inMat3.m8() + this->m3() * inMat3.m12();
        newMat3._m1 = this->m0() * inMat3.m1() + this->m1() * inMat3.m5() + this->m2() * inMat3.m9() + this->m3() * inMat3.m13();
        newMat3._m2 = this->m0() * inMat3.m2() + this->m1() * inMat3.m6() + this->m2() * inMat3.m10() + this->m3() * inMat3.m14();
        newMat3._m3 = this->m0() * inMat3.m3() + this->m1() * inMat3.m7() + this->m2() * inMat3.m11() + this->m3() * inMat3.m15();

        //Vec4or 2
        newMat3._m4 = this->m4() * inMat3.m0() + this->m5() * inMat3.m4() + this->m6() * inMat3.m8() + this->m7() * inMat3.m12();
        newMat3._m5 = this->m4() * inMat3.m1() + this->m5() * inMat3.m5() + this->m6() * inMat3.m9() + this->m7() * inMat3.m13();
        newMat3._m6 = this->m4() * inMat3.m2() + this->m5() * inMat3.m6() + this->m6() * inMat3.m10() + this->m7() * inMat3.m14();
        newMat3._m7 = this->m4() * inMat3.m3() + this->m5() * inMat3.m7() + this->m6() * inMat3.m11() + this->m7() * inMat3.m15();

        //Vec4or 3
        newMat3._m8 = this->m8() * inMat3.m0() + this->m9() * inMat3.m4() + this->m10() * inMat3.m8() + this->m11() * inMat3.m12();
        newMat3._m9 = this->m8() * inMat3.m1() + this->m9() * inMat3.m5() + this->m10() * inMat3.m9() + this->m11() * inMat3.m13();
        newMat3._m10 = this->m8() * inMat3.m2() + this->m9() * inMat3.m6() + this->m10() * inMat3.m10() + this->m11() * inMat3.m14();
        newMat3._m11 = this->m8() * inMat3.m3() + this->m9() * inMat3.m7() + this->m10() * inMat3.m11() + this->m11() * inMat3.m15();

        //Vec4or 4
        newMat3._m12 = this->m12() * inMat3.m0() + this->m13() * inMat3.m4() + this->m14() * inMat3.m8() + this->m15() * inMat3.m12();
        newMat3._m13 = this->m12() * inMat3.m1() + this->m13() * inMat3.m5() + this->m14() * inMat3.m9() + this->m15() * inMat3.m13();
        newMat3._m14 = this->m12() * inMat3.m2() + this->m13() * inMat3.m6() + this->m14() * inMat3.m10() + this->m15() * inMat3.m14();
        newMat3._m15 = this->m12() * inMat3.m3() + this->m13() * inMat3.m7() + this->m14() * inMat3.m11() + this->m15() * inMat3.m15();


        return newMat3;
    }
    Mat3 Mat3::operator*=(Mat3 inMat3)
    {
        Mat3 newMat3;

        //Vec4or 1
        newMat3._m0 = this->m0() * inMat3.m0() + this->m1() * inMat3.m4() + this->m2() * inMat3.m8() + this->m3() * inMat3.m12();
        newMat3._m1 = this->m0() * inMat3.m1() + this->m1() * inMat3.m5() + this->m2() * inMat3.m9() + this->m3() * inMat3.m13();
        newMat3._m2 = this->m0() * inMat3.m2() + this->m1() * inMat3.m6() + this->m2() * inMat3.m10() + this->m3() * inMat3.m14();
        newMat3._m3 = this->m0() * inMat3.m3() + this->m1() * inMat3.m7() + this->m2() * inMat3.m11() + this->m3() * inMat3.m15();

        //Vec4or 2
        newMat3._m4 = this->m4() * inMat3.m0() + this->m5() * inMat3.m4() + this->m6() * inMat3.m8() + this->m7() * inMat3.m12();
        newMat3._m5 = this->m4() * inMat3.m1() + this->m5() * inMat3.m5() + this->m6() * inMat3.m9() + this->m7() * inMat3.m13();
        newMat3._m6 = this->m4() * inMat3.m2() + this->m5() * inMat3.m6() + this->m6() * inMat3.m10() + this->m7() * inMat3.m14();
        newMat3._m7 = this->m4() * inMat3.m3() + this->m5() * inMat3.m7() + this->m6() * inMat3.m11() + this->m7() * inMat3.m15();

        //Vec4or 3
        newMat3._m8 = this->m8() * inMat3.m0() + this->m9() * inMat3.m4() + this->m10() * inMat3.m8() + this->m11() * inMat3.m12();
        newMat3._m9 = this->m8() * inMat3.m1() + this->m9() * inMat3.m5() + this->m10() * inMat3.m9() + this->m11() * inMat3.m13();
        newMat3._m10 = this->m8() * inMat3.m2() + this->m9() * inMat3.m6() + this->m10() * inMat3.m10() + this->m11() * inMat3.m14();
        newMat3._m11 = this->m8() * inMat3.m3() + this->m9() * inMat3.m7() + this->m10() * inMat3.m11() + this->m11() * inMat3.m15();

        //Vec4or 4
        newMat3._m12 = this->m12() * inMat3.m0() + this->m13() * inMat3.m4() + this->m14() * inMat3.m8() + this->m15() * inMat3.m12();
        newMat3._m13 = this->m12() * inMat3.m1() + this->m13() * inMat3.m5() + this->m14() * inMat3.m9() + this->m15() * inMat3.m13();
        newMat3._m14 = this->m12() * inMat3.m2() + this->m13() * inMat3.m6() + this->m14() * inMat3.m10() + this->m15() * inMat3.m14();
        newMat3._m15 = this->m12() * inMat3.m3() + this->m13() * inMat3.m7() + this->m14() * inMat3.m11() + this->m15() * inMat3.m15();

        *this = newMat3;

        return *this;
    }
    Mat3 Mat3::operator+(Mat3 inMat3)
    {
        Mat3 newMat3;

        //Vec4or 1
        newMat3._m0 = this->_m0 + inMat3._m0;
        newMat3._m1 = this->_m1 + inMat3._m1;
        newMat3._m2 = this->_m2 + inMat3._m2;
        newMat3._m3 = this->_m3 + inMat3._m3;

        //newMat3._v0 = this->_v0 + inMat3._v0;

        //Vec4or 2
        newMat3._m4 = this->_m4 + inMat3._m4;
        newMat3._m5 = this->_m5 + inMat3._m5;
        newMat3._m6 = this->_m6 + inMat3._m6;
        newMat3._m7 = this->_m7 + inMat3._m7;

        //newMat3._v1 = this->_v1 + inMat3._v1;

        //Vec4or 3
        newMat3._m8 = this->_m8 + inMat3._m8;
        newMat3._m9 = this->_m9 + inMat3._m9;
        newMat3._m10 = this->_m10 + inMat3._m10;
        newMat3._m11 = this->_m11 + inMat3._m11;

        //newMat3._v2 = this->_v2 + inMat3._v2;

        //Vec4or 4
        newMat3._m12 = this->_m12 + inMat3._m12;
        newMat3._m13 = this->_m13 + inMat3._m13;
        newMat3._m14 = this->_m14 + inMat3._m14;
        newMat3._m15 = this->_m15 + inMat3._m15;

        //newMat3._v3 = this->_v3 + inMat3._v3;

        return newMat3;

    }
    Mat3 Mat3::operator+=(Mat3 inMat3)
    {
        //Vec4or 1
        this->_m0 += inMat3._m0;
        this->_m1 += inMat3._m1;
        this->_m2 += inMat3._m2;
        this->_m3 += inMat3._m3;

        //newMat3._v0 = this->_v0 + inMat3._v0;

        //Vec4or 2
        this->_m4 += inMat3._m4;
        this->_m5 += inMat3._m5;
        this->_m7 += inMat3._m7;
        this->_m6 += inMat3._m6;

        //newMat3._v1 = this->_v1 + inMat3._v1;

        //Vec4or 3
        this->_m8 += inMat3._m8;
        this->_m9 += inMat3._m9;
        this->_m10 += inMat3._m10;
        this->_m11 += inMat3._m11;

        //newMat3._v2 = this->_v2 + inMat3._v2;

        //Vec4or 4
        this->_m12 += inMat3._m12;
        this->_m13 += inMat3._m13;
        this->_m14 += inMat3._m14;
        this->_m15 += inMat3._m15;

        //newMat3._v3 = this->_v3 + inMat3._v3;

        return *this;
    }

    Mat3 Mat3::operator-(Mat3 inMat3)
    {
        Mat3 newMat3;

        //Vec4or 1
        newMat3._m0 = this->_m0 - inMat3._m0;
        newMat3._m1 = this->_m1 - inMat3._m1;
        newMat3._m2 = this->_m2 - inMat3._m2;
        newMat3._m3 = this->_m3 - inMat3._m3;

        //newMat3._v0 = this->_v0 + inMat3._v0;

        //Vec4or 2
        newMat3._m4 = this->_m4 - inMat3._m4;
        newMat3._m5 = this->_m5 - inMat3._m5;
        newMat3._m6 = this->_m6 - inMat3._m6;
        newMat3._m7 = this->_m7 - inMat3._m7;

        //newMat3._v1 = this->_v1 + inMat3._v1;

        //Vec4or 3
        newMat3._m8 = this->_m8 - inMat3._m8;
        newMat3._m9 = this->_m9 - inMat3._m9;
        newMat3._m10 = this->_m10 - inMat3._m10;
        newMat3._m11 = this->_m11 - inMat3._m11;

        //newMat3._v2 = this->_v2 + inMat3._v2;

        //Vec4or 4
        newMat3._m12 = this->_m12 - inMat3._m12;
        newMat3._m13 = this->_m13 - inMat3._m13;
        newMat3._m14 = this->_m14 - inMat3._m14;
        newMat3._m15 = this->_m15 - inMat3._m15;

        //newMat3._v3 = this->_v3 + inMat3._v3;

        return newMat3;
    }

    Mat3 Mat3::operator-=(Mat3 inMat3)
    {
        //Vec4or 1
        this->_m0 -= inMat3._m0;
        this->_m1 -= inMat3._m1;
        this->_m2 -= inMat3._m2;
        this->_m3 -= inMat3._m3;

        //newMat3._v0 = this->_v0 + inMat3._v0;

        //Vec4or 2
        this->_m4 -= inMat3._m4;
        this->_m5 -= inMat3._m5;
        this->_m7 -= inMat3._m7;
        this->_m6 -= inMat3._m6;

        //newMat3._v1 = this->_v1 + inMat3._v1;

        //Vec4or 3
        this->_m8 -= inMat3._m8;
        this->_m9 -= inMat3._m9;
        this->_m10 -= inMat3._m10;
        this->_m11 -= inMat3._m11;

        //newMat3._v2 = this->_v2 + inMat3._v2;

        //Vec4or 4
        this->_m12 -= inMat3._m12;
        this->_m13 -= inMat3._m13;
        this->_m14 -= inMat3._m14;
        this->_m15 -= inMat3._m15;

        //newMat3._v3 = this->_v3 + inMat3._v3;

        return *this;
    }

    Mat3 Mat3::operator+()
    {
        Mat3 newMat3;

        newMat3._v0 = this->_v0;
        SetMs(newMat3._v0);

        newMat3._v1 = this->_v1;
        SetMs(newMat3._v1);

        newMat3._v2 = this->_v2;
        SetMs(newMat3._v2);

        newMat3._v3 = this->_v3;
        SetMs(newMat3._v3);

        return newMat3;
    }

    Mat3 Mat3::operator-()
    {
        Mat3 newMat3;

        newMat3._v0 = -this->_v0;
        newMat3._m0 = -this->_m0;
        newMat3._m1 = -this->_m1;
        newMat3._m2 = -this->_m2;
        newMat3._m3 = -this->_m3;


        newMat3._v1 = -this->_v1;
        newMat3._m4 = -this->_m4;
        newMat3._m5 = -this->_m5;
        newMat3._m6 = -this->_m6;
        newMat3._m7 = -this->_m7;

        newMat3._v2 = -this->_v2;
        newMat3._m8 = -this->_m8;
        newMat3._m9 = -this->_m9;
        newMat3._m10 = -this->_m10;
        newMat3._m11 = -this->_m11;

        newMat3._v3 = -this->_v3;
        newMat3._m12 = -this->_m12;
        newMat3._m13 = -this->_m13;
        newMat3._m14 = -this->_m14;
        newMat3._m15 = -this->_m15;

        return newMat3;
    }

    void Mat3::SetMs(Vec4& inVec4)
    {
        if (this->_v0.isEqual(inVec4, 0.1f))
        {
            this->_m0 = inVec4.x();
            this->_m1 = inVec4.y();
            this->_m2 = inVec4.z();
            this->_m3 = inVec4.w();
        }
        else if (this->_v1.isEqual(inVec4, 0.1f))
        {
            this->_m4 = inVec4.x();
            this->_m5 = inVec4.y();
            this->_m6 = inVec4.z();
            this->_m7 = inVec4.w();
        }
        else if (this->_v2.isEqual(inVec4, 0.1f))
        {
            this->_m8 = inVec4.x();
            this->_m9 = inVec4.y();
            this->_m10 = inVec4.z();
            this->_m11 = inVec4.w();
        }
        else if (this->_v3.isEqual(inVec4, 0.1f))
        {
            this->_m12 = inVec4.x();
            this->_m13 = inVec4.y();
            this->_m14 = inVec4.z();
            this->_m15 = inVec4.w();
        }
    }

    void Mat3::set(Mat3::Special type)
    {
        if (type == Mat3::Special::Identity)
        {
            this->_m0 = 1.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 1.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 1.0f;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
        else if (type == Mat3::Special::Zero)
        {
            this->_m0 = 0.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 0.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 0.0f;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 0.0f;
        }
    }

    /*void Mat3::set(Mat3::Trans type, float in1, float in2, float in3)
    {
        if (type == Mat3::Trans::XYZ)
        {
            this->_m0 = 1.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 1.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 1.0f;
            this->_m11 = 0.0f;
            this->_m12 = in1;
            this->_m13 = in2;
            this->_m14 = in3;
            this->_m15 = 1.0f;
        }
    }

    void Mat3::set(Mat3::Trans type, Vec4 inVec4)
    {
        float in1 = inVec4.x();
        float in2 = inVec4.y();
        float in3 = inVec4.z();

        if (type == Mat3::Trans::XYZ)
        {
            this->_m0 = 1.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 1.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 1.0f;
            this->_m11 = 0.0f;
            this->_m12 = in1;
            this->_m13 = in2;
            this->_m14 = in3;
            this->_m15 = 1.0f;
        }
    }

    void Mat3::set(Mat3::Scale type, float in1, float in2, float in3)
    {
        if (type == Mat3::Scale::XYZ)
        {
            this->_m0 = in1;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = in2;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = in3;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
    }

    void Mat3::set(Mat3::Scale type, Vec4 inVec4)
    {
        float in1 = inVec4.x();
        float in2 = inVec4.y();
        float in3 = inVec4.z();

        if (type == Mat3::Scale::XYZ)
        {
            this->_m0 = in1;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = in2;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = in3;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
    }*/


    void Mat3::set(Mat3::Row row, Vec4 inVec4)
    {
        if (row == Mat3::Row::i0)
        {
            this->_v0 = inVec4;
            SetMs(inVec4);
        }
        else if (row == Mat3::Row::i1)
        {
            this->_v1 = inVec4;
            SetMs(inVec4);
        }
        else if (row == Mat3::Row::i2)
        {
            this->_v2 = inVec4;
            SetMs(inVec4);
        }
        /*else if (row == Mat3::Row::i3)
        {
            this->_v3 = inVec4;
            SetMs(inVec4);
        }*/
    }

    void Mat3::set(Mat3::Row row, Vec3 inVec3)
    {
        Vec4 inVec4(inVec3, 0);
        if (row == Mat3::Row::i0)
        {
            this->_v0 = inVec4;
            SetMs(inVec4);
        }
        else if (row == Mat3::Row::i1)
        {
            this->_v1 = inVec4;
            SetMs(inVec4);
        }
        else if (row == Mat3::Row::i2)
        {
            this->_v2 = inVec4;
            SetMs(inVec4);
        }
    }

    Vec4 Mat3::get(Mat3::Row row)
    {
        Vec4 foundVec4or;

        if (row == Mat3::Row::i0)
        {
            foundVec4or = this->_v0;
        }
        else if (row == Mat3::Row::i1)
        {
            foundVec4or = this->_v1;
        }
        else if (row == Mat3::Row::i2)
        {
            foundVec4or = this->_v2;
        }
        //else if (row == Mat3::Row::i3)
        //{
        //    foundVec4or = this->_v3;
        //}

        return foundVec4or;
    }

    //void Mat3::set(Mat3::Rot rot, Vec4& inVec4, float inFloat)
    //{
    //    if (rot == Mat3::Rot::AxisAngle)
    //    {
    //        // angle
    //        // axis;
    //        const float angle_a = 0.5f * inFloat;
    //        float cos_a;
    //        float sin_a;

    //        cos_a = cosf(angle_a);
    //        sin_a = sinf(angle_a);

    //        Vec4 qV = inVec4.getNorm();

    //        qV *= sin_a;

    //        Vec4 Q;
    //        Q[x] = qV[x];
    //        Q[y] = qV[y];
    //        Q[z] = qV[z];
    //        Q[w] = cos_a;

    //        // this function has been transposed
    //        float x2, y2, z2;
    //        float xx, xy, xz;
    //        float yy, yz, zz;
    //        float wx, wy, wz;

    //        // ADD test to make sure that quat is normalized

    //        x2 = Q[x] + Q[x];
    //        y2 = Q[y] + Q[y];
    //        z2 = Q[z] + Q[z];

    //        xx = Q[x] * x2;
    //        xy = Q[x] * y2;
    //        xz = Q[x] * z2;

    //        yy = Q[y] * y2;
    //        yz = Q[y] * z2;
    //        zz = Q[z] * z2;

    //        wx = Q[w] * x2;
    //        wy = Q[w] * y2;
    //        wz = Q[w] * z2;

    //        this->_m0 = 1.0f - (yy + zz);
    //        this->_m1 = xy + wz;
    //        this->_m2 = xz - wy;
    //        this->_m3 = 0.0f;

    //        this->_m4 = xy - wz;
    //        this->_m5 = 1.0f - (xx + zz);
    //        this->_m6 = yz + wx;
    //        this->_m7 = 0.0f;

    //        this->_m8 = xz + wy;
    //        this->_m9 = yz - wx;
    //        this->_m10 = 1.0f - (xx + yy);
    //        this->_m11 = 0.0f;

    //        this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
    //    }
    //}

   /* void Mat3::set(Mat3::Rot1 rot, float inFloat)
    {
        if (rot == Mat3::Rot1::X)
        {
            this->_m0 = 1.0f;
            this->_m1 = 0.0f;
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = Trig::cos(inFloat);
            this->_m6 = Trig::sin(inFloat);
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = -Trig::sin(inFloat);
            this->_m10 = Trig::cos(inFloat);
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
        else if (rot == Mat3::Rot1::Y)
        {
            this->_m0 = Trig::cos(inFloat);
            this->_m1 = 0.0f;
            this->_m2 = -Trig::sin(inFloat);
            this->_m3 = 0.0f;
            this->_m4 = 0.0f;
            this->_m5 = 1.0f;
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = Trig::sin(inFloat);
            this->_m9 = 0.0f;
            this->_m10 = Trig::cos(inFloat);
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
        else if (rot == Mat3::Rot1::Z)
        {
            this->_m0 = Trig::cos(inFloat);
            this->_m1 = Trig::sin(inFloat);
            this->_m2 = 0.0f;
            this->_m3 = 0.0f;
            this->_m4 = -Trig::sin(inFloat);
            this->_m5 = Trig::cos(inFloat);
            this->_m6 = 0.0f;
            this->_m7 = 0.0f;
            this->_m8 = 0.0f;
            this->_m9 = 0.0f;
            this->_m10 = 1.0f;
            this->_m11 = 0.0f;
            this->_m12 = 0.0f;
            this->_m13 = 0.0f;
            this->_m14 = 0.0f;
            this->_m15 = 1.0f;
        }
    }

    void Mat3::set(Mat3::Rot3 rot, float inFloatX, float inFloatY, float inFloatZ)
    {
        Mat3 rotX;
        Mat3 rotY;
        Mat3 rotZ;


        if (rot == Mat3::Rot3::XYZ)
        {
            rotX.set(Mat3::Rot1::X, inFloatX);
            rotY.set(Mat3::Rot1::Y, inFloatY);
            rotZ.set(Mat3::Rot1::Z, inFloatZ);

            *this = rotX * rotY * rotZ;
        }
    }

    void Mat3::set(Mat3::Orient orientType, Vec4 inVec41, Vec4 inVec42)
    {
        if (orientType == Mat3::Orient::LocalToWorld)
        {
            this->privSetRotOrient(inVec41, inVec42);
        }
        else if (orientType == Mat3::Orient::WorldToLocal)
        {
            this->privSetRotOrient(inVec41, inVec42);
            this->inv();
        }
    }*/

    float Mat3::det()
    {
        //is the mass or magnitude of the Mat3
        //need to break down into other determinants

        float tmp =
            this->_m12 * this->_m9 * this->_m6 * this->_m3 - this->_m8 * this->_m13 * this->_m6 * this->_m3 -
            this->_m12 * this->_m5 * this->_m10 * this->_m3 + this->_m4 * this->_m13 * this->_m10 * this->_m3 +
            this->_m8 * this->_m5 * this->_m14 * this->_m3 - this->_m4 * this->_m9 * this->_m14 * this->_m3 -
            this->_m12 * this->_m9 * this->_m2 * this->_m7 + this->_m8 * this->_m13 * this->_m2 * this->_m7 +
            this->_m12 * this->_m1 * this->_m10 * this->_m7 - this->_m0 * this->_m13 * this->_m10 * this->_m7 -
            this->_m8 * this->_m1 * this->_m14 * this->_m7 + this->_m0 * this->_m9 * this->_m14 * this->_m7 +
            this->_m12 * this->_m5 * this->_m2 * this->_m11 - this->_m4 * this->_m13 * this->_m2 * this->_m11 -
            this->_m12 * this->_m1 * this->_m6 * this->_m11 + this->_m0 * this->_m13 * this->_m6 * this->_m11 +
            this->_m4 * this->_m1 * this->_m14 * this->_m11 - this->_m0 * this->_m5 * this->_m14 * this->_m11 -
            this->_m8 * this->_m5 * this->_m2 * this->_m15 + this->_m4 * this->_m9 * this->_m2 * this->_m15 +
            this->_m8 * this->_m1 * this->_m6 * this->_m15 - this->_m0 * this->_m9 * this->_m6 * this->_m15 -
            this->_m4 * this->_m1 * this->_m10 * this->_m15 + this->_m0 * this->_m5 * this->_m10 * this->_m15;

        return tmp;
        ////Determinant of a 4x4 Mat3. Different from my subMDet because that's a 3x3 Mat3.

        //float Adet = (_m0 * ((_m5 * +(_m10 * _m15 - _m11 * _m14)) - (_m6 * (_m9 * _m15 - _m11 * _m13)) + (_m7 * (_m9 * _m14 - _m10 * _m13))));
        //float Bdet = -(_m1 * ((_m4 * +(_m10 * _m15 - _m11 * _m14)) - (_m6 * (_m8 * _m15 - _m11 * _m12)) + (_m7 * (_m8 * _m14 - _m10 * _m12))));
        //float Cdet = (_m2 * ((_m4 * +(_m9 * _m15 - _m11 * _m13)) - (_m5 * (_m8 * _m15 - _m11 * _m12)) + (_m7 * (_m8 * _m13 - _m9 * _m12))));
        //float Ddet = -(_m3 * ((_m4 * +(_m9 * _m14 - _m10 * _m13)) - (_m5 * (_m8 * _m14 - _m10 * _m12)) + (_m6 * (_m8 * _m13 - _m9 * _m12))));

        //return Adet + Bdet + Cdet + Ddet;
    }


    /*Mat3::Mat3(Mat3::Orient orientType, Vec4 inVec41, Vec4 inVec42)
    {
        if (orientType == Mat3::Orient::LocalToWorld)
        {
            this->privSetRotOrient(inVec41, inVec42);
        }
        else if (orientType == Mat3::Orient::WorldToLocal)
        {
            this->privSetRotOrient(inVec41, inVec42);
            this->inv();

        }
    }*/

    void Mat3::privSetRotOrient(Vec4& v1, Vec4& v2)
    {

        Vec4 rz = v1.getNorm();

        Vec4 rx = v2.cross(rz);
        rx.norm();

        Vec4 ry = rz.cross(rx);
        ry.norm();

        this->set(rx, ry, rz, Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        this->_m3 = 0.0f;
        this->_m7 = 0.0f;
        this->_m11 = 0.0f;
        this->_m15 = 1.0f;

    }

    void Mat3::privSetRotInverseOrient()
    {

    }

    void Mat3::set(Vec4 inVec41, Vec4 inVec42, Vec4 inVec43, Vec4 inVec44)
    {
        this->_v0 = inVec41;
        SetMs(inVec41);

        this->_v1 = inVec42;
        SetMs(inVec42);

        this->_v2 = inVec43;
        SetMs(inVec43);

        this->_v3 = inVec44;
        SetMs(inVec44);
    }

    void Mat3::set(Vec3 inVec31, Vec3 inVec32, Vec3 inVec33)
    {
        Vec4 inVec41(inVec31, 0);
        Vec4 inVec42(inVec32, 0);
        Vec4 inVec43(inVec33, 0);

        this->_v0 = inVec41;
        SetMs(inVec41);

        this->_v1 = inVec42;
        SetMs(inVec42);

        this->_v2 = inVec43;
        SetMs(inVec43);
    }

    bool Mat3::isEqual(Mat3 inMat3)
    {
        bool result = false;

        if (Util::isEqual(this->_m0, inMat3._m0, MATH_TOLERANCE)
            && Util::isEqual(this->_m1, inMat3._m1, MATH_TOLERANCE)
            && Util::isEqual(this->_m2, inMat3._m2, MATH_TOLERANCE)
            && Util::isEqual(this->_m3, inMat3._m3, MATH_TOLERANCE)
            && Util::isEqual(this->_m4, inMat3._m4, MATH_TOLERANCE)
            && Util::isEqual(this->_m5, inMat3._m5, MATH_TOLERANCE)
            && Util::isEqual(this->_m6, inMat3._m6, MATH_TOLERANCE)
            && Util::isEqual(this->_m7, inMat3._m7, MATH_TOLERANCE)
            && Util::isEqual(this->_m8, inMat3._m8, MATH_TOLERANCE)
            && Util::isEqual(this->_m9, inMat3._m9, MATH_TOLERANCE)
            && Util::isEqual(this->_m10, inMat3._m10, MATH_TOLERANCE)
            && Util::isEqual(this->_m11, inMat3._m11, MATH_TOLERANCE)
            && Util::isEqual(this->_m12, inMat3._m12, MATH_TOLERANCE)
            && Util::isEqual(this->_m13, inMat3._m13, MATH_TOLERANCE)
            && Util::isEqual(this->_m14, inMat3._m14, MATH_TOLERANCE)
            && Util::isEqual(this->_m15, inMat3._m15, MATH_TOLERANCE)) //one big check
        {
            //if it's all true - we are equal
            result = true;
        }

        return result;
    }

    bool Mat3::isIdentity(float tolerance)
    {
        bool result = false;

        if (Util::isEqual(this->_m0, 1, tolerance) &&
            Util::isEqual(this->_m1, 0, tolerance) &&
            Util::isEqual(this->_m2, 0, tolerance) &&
            Util::isEqual(this->_m3, 0, tolerance) &&
            Util::isEqual(this->_m4, 0, tolerance) &&
            Util::isEqual(this->_m5, 1, tolerance) &&
            Util::isEqual(this->_m6, 0, tolerance) &&
            Util::isEqual(this->_m7, 0, tolerance) &&
            Util::isEqual(this->_m8, 0, tolerance) &&
            Util::isEqual(this->_m9, 0, tolerance) &&
            Util::isEqual(this->_m10, 1, tolerance) &&
            Util::isEqual(this->_m11, 0, tolerance) &&
            Util::isEqual(this->_m12, 0, tolerance) &&
            Util::isEqual(this->_m13, 0, tolerance) &&
            Util::isEqual(this->_m14, 0, tolerance) &&
            Util::isEqual(this->_m15, 1, tolerance))//one big check
        {
            //if it's all true - we are equal
            result = true;
        }

        return result;
    }

    bool Mat3::isRotation()
    {
        bool result = false;

        if (this->det() == 1)
        {
            Mat3 invMat3 = this->getInv();
            Mat3 transposeMat3 = this->getT();

            if (invMat3.isEqual(transposeMat3))
            {
                result = true;
            }
        }

        return result;
    }


    Mat3 Mat3::inv()
    {
        Mat3 tmpMat;

        float a00 = this->m0();
        float a01 = this->m1();
        float a02 = this->m2();
        float a03 = this->m3();
        float a10 = this->m4();
        float a11 = this->m5();
        float a12 = this->m6();
        float a13 = this->m7();
        float a20 = this->m8();
        float a21 = this->m9();
        float a22 = this->m10();
        float a23 = this->m11();
        float a30 = this->m12();
        float a31 = this->m13();
        float a32 = this->m14();
        float a33 = this->m15();

        tmpMat._m0 = (a12 * a23 * a31) - (a13 * a22 * a31) + (a13 * a21 * a32) - (a11 * a23 * a32) - (a12 * a21 * a33) + (a11 * a22 * a33);
        tmpMat._m1 = (a03 * a22 * a31) - (a02 * a23 * a31) - (a03 * a21 * a32) + (a01 * a23 * a32) + (a02 * a21 * a33) - (a01 * a22 * a33);
        tmpMat._m2 = (a02 * a13 * a31) - (a03 * a12 * a31) + (a03 * a11 * a32) - (a01 * a13 * a32) - (a02 * a11 * a33) + (a01 * a12 * a33);
        tmpMat._m3 = (a03 * a12 * a21) - (a02 * a13 * a21) - (a03 * a11 * a22) + (a01 * a13 * a22) + (a02 * a11 * a23) - (a01 * a12 * a23);
        tmpMat._m4 = (a13 * a22 * a30) - (a12 * a23 * a30) - (a13 * a20 * a32) + (a10 * a23 * a32) + (a12 * a20 * a33) - (a10 * a22 * a33);
        tmpMat._m5 = (a02 * a23 * a30) - (a03 * a22 * a30) + (a03 * a20 * a32) - (a00 * a23 * a32) - (a02 * a20 * a33) + (a00 * a22 * a33);
        tmpMat._m6 = (a03 * a12 * a30) - (a02 * a13 * a30) - (a03 * a10 * a32) + (a00 * a13 * a32) + (a02 * a10 * a33) - (a00 * a12 * a33);
        tmpMat._m7 = (a02 * a13 * a20) - (a03 * a12 * a20) + (a03 * a10 * a22) - (a00 * a13 * a22) - (a02 * a10 * a23) + (a00 * a12 * a23);
        tmpMat._m8 = (a11 * a23 * a30) - (a13 * a21 * a30) + (a13 * a20 * a31) - (a10 * a23 * a31) - (a11 * a20 * a33) + (a10 * a21 * a33);
        tmpMat._m9 = (a03 * a21 * a30) - (a01 * a23 * a30) - (a03 * a20 * a31) + (a00 * a23 * a31) + (a01 * a20 * a33) - (a00 * a21 * a33);
        tmpMat._m10 = (a01 * a13 * a30) - (a03 * a11 * a30) + (a03 * a10 * a31) - (a00 * a13 * a31) - (a01 * a10 * a33) + (a00 * a11 * a33);
        tmpMat._m11 = (a03 * a11 * a20) - (a01 * a13 * a20) - (a03 * a10 * a21) + (a00 * a13 * a21) + (a01 * a10 * a23) - (a00 * a11 * a23);
        tmpMat._m12 = (a12 * a21 * a30) - (a11 * a22 * a30) - (a12 * a20 * a31) + (a10 * a22 * a31) + (a11 * a20 * a32) - (a10 * a21 * a32);
        tmpMat._m13 = (a01 * a22 * a30) - (a02 * a21 * a30) + (a02 * a20 * a31) - (a00 * a22 * a31) - (a01 * a20 * a32) + (a00 * a21 * a32);
        tmpMat._m14 = (a02 * a11 * a30) - (a01 * a12 * a30) - (a02 * a10 * a31) + (a00 * a12 * a31) + (a01 * a10 * a32) - (a00 * a11 * a32);
        tmpMat._m15 = (a01 * a12 * a20) - (a02 * a11 * a20) + (a02 * a10 * a21) - (a00 * a12 * a21) - (a01 * a10 * a22) + (a00 * a11 * a22);

        const float det = this->det();
        const float inverseDet = 1.0f / det;

        //Trace::out("%f", det);
        //Trace::out("%f", inverseDet);

        tmpMat = tmpMat * inverseDet;
        *this = tmpMat;


        //return tmpMat;
        return *this;
    }

    Mat3 Mat3::getInv()
    {
        Mat3 tmpMat;

        float a00 = this->m0();
        float a01 = this->m1();
        float a02 = this->m2();
        float a03 = this->m3();
        float a10 = this->m4();
        float a11 = this->m5();
        float a12 = this->m6();
        float a13 = this->m7();
        float a20 = this->m8();
        float a21 = this->m9();
        float a22 = this->m10();
        float a23 = this->m11();
        float a30 = this->m12();
        float a31 = this->m13();
        float a32 = this->m14();
        float a33 = this->m15();

        tmpMat._m0 = (a12 * a23 * a31) - (a13 * a22 * a31) + (a13 * a21 * a32) - (a11 * a23 * a32) - (a12 * a21 * a33) + (a11 * a22 * a33);
        tmpMat._m1 = (a03 * a22 * a31) - (a02 * a23 * a31) - (a03 * a21 * a32) + (a01 * a23 * a32) + (a02 * a21 * a33) - (a01 * a22 * a33);
        tmpMat._m2 = (a02 * a13 * a31) - (a03 * a12 * a31) + (a03 * a11 * a32) - (a01 * a13 * a32) - (a02 * a11 * a33) + (a01 * a12 * a33);
        tmpMat._m3 = (a03 * a12 * a21) - (a02 * a13 * a21) - (a03 * a11 * a22) + (a01 * a13 * a22) + (a02 * a11 * a23) - (a01 * a12 * a23);
        tmpMat._m4 = (a13 * a22 * a30) - (a12 * a23 * a30) - (a13 * a20 * a32) + (a10 * a23 * a32) + (a12 * a20 * a33) - (a10 * a22 * a33);
        tmpMat._m5 = (a02 * a23 * a30) - (a03 * a22 * a30) + (a03 * a20 * a32) - (a00 * a23 * a32) - (a02 * a20 * a33) + (a00 * a22 * a33);
        tmpMat._m6 = (a03 * a12 * a30) - (a02 * a13 * a30) - (a03 * a10 * a32) + (a00 * a13 * a32) + (a02 * a10 * a33) - (a00 * a12 * a33);
        tmpMat._m7 = (a02 * a13 * a20) - (a03 * a12 * a20) + (a03 * a10 * a22) - (a00 * a13 * a22) - (a02 * a10 * a23) + (a00 * a12 * a23);
        tmpMat._m8 = (a11 * a23 * a30) - (a13 * a21 * a30) + (a13 * a20 * a31) - (a10 * a23 * a31) - (a11 * a20 * a33) + (a10 * a21 * a33);
        tmpMat._m9 = (a03 * a21 * a30) - (a01 * a23 * a30) - (a03 * a20 * a31) + (a00 * a23 * a31) + (a01 * a20 * a33) - (a00 * a21 * a33);
        tmpMat._m10 = (a01 * a13 * a30) - (a03 * a11 * a30) + (a03 * a10 * a31) - (a00 * a13 * a31) - (a01 * a10 * a33) + (a00 * a11 * a33);
        tmpMat._m11 = (a03 * a11 * a20) - (a01 * a13 * a20) - (a03 * a10 * a21) + (a00 * a13 * a21) + (a01 * a10 * a23) - (a00 * a11 * a23);
        tmpMat._m12 = (a12 * a21 * a30) - (a11 * a22 * a30) - (a12 * a20 * a31) + (a10 * a22 * a31) + (a11 * a20 * a32) - (a10 * a21 * a32);
        tmpMat._m13 = (a01 * a22 * a30) - (a02 * a21 * a30) + (a02 * a20 * a31) - (a00 * a22 * a31) - (a01 * a20 * a32) + (a00 * a21 * a32);
        tmpMat._m14 = (a02 * a11 * a30) - (a01 * a12 * a30) - (a02 * a10 * a31) + (a00 * a12 * a31) + (a01 * a10 * a32) - (a00 * a11 * a32);
        tmpMat._m15 = (a01 * a12 * a20) - (a02 * a11 * a20) + (a02 * a10 * a21) - (a00 * a12 * a21) - (a01 * a10 * a22) + (a00 * a11 * a22);

        const float det = this->det();
        const float inverseDet = 1.0f / det;

        //Trace::out("%f", det);
        //Trace::out("%f", inverseDet);

        tmpMat = tmpMat * inverseDet;
        //*this = tmpMat;


        //return tmpMat;
        return tmpMat;


        //Mat3 newMat3;


        //float det = this->det();
        //float invDet = 1 / det;

        //////get cofactor of Mat3
        ////newMat3 = this->getAdjoint();


        ///*
        //
        //copying ed's notes


        //a00 a01 a02 a03
        //a10 a11 a12 a13 
        //a20 a21 a22 a23  
        //a30 a31 a32 a33

        //is the same as

        //m00 m01 m02 m03
        //m04 m05 m06 m07
        //m08 m09 m10 m11
        //m12 m13 m14 m15        
        //
        //*/

        //float a00 = this->m0();
        //float a01 = this->m1();
        //float a02 = this->m2();
        //float a03 = this->m3();
        //float a10 = this->m4();
        //float a11 = this->m5();
        //float a12 = this->m6();
        //float a13 = this->m7();
        //float a20 = this->m8();
        //float a21 = this->m9();
        //float a22 = this->m10();
        //float a23 = this->m11();
        //float a30 = this->m12();
        //float a31 = this->m13();
        //float a32 = this->m14();
        //float a33 = this->m15();

        //newMat3._m0  = (a12 * a23 * a31) - (a13 * a22 * a31) + (a13 * a21 * a32) - (a11 * a23 * a32) - (a12 * a21 * a33) + (a11 * a22 * a33);
        //newMat3._m1  = (a03 * a22 * a31) - (a02 * a23 * a31) - (a03 * a21 * a32) + (a01 * a23 * a32) + (a02 * a21 * a33) - (a01 * a22 * a33);
        //newMat3._m2  = (a02 * a13 * a31) - (a03 * a12 * a31) + (a03 * a11 * a32) - (a01 * a13 * a32) - (a02 * a11 * a33) + (a01 * a12 * a33);
        //newMat3._m3  = (a03 * a12 * a21) - (a02 * a13 * a21) - (a03 * a11 * a22) + (a01 * a13 * a22) + (a02 * a11 * a23) - (a01 * a12 * a23);
        //newMat3._m4  = (a13 * a22 * a30) - (a12 * a23 * a30) - (a13 * a20 * a32) + (a10 * a23 * a32) + (a12 * a20 * a33) - (a10 * a22 * a33);
        //newMat3._m5  = (a02 * a23 * a30) - (a03 * a22 * a30) + (a03 * a20 * a32) - (a00 * a23 * a32) - (a02 * a20 * a33) + (a00 * a22 * a33);
        //newMat3._m6  = (a03 * a12 * a30) - (a02 * a13 * a30) - (a03 * a10 * a32) + (a00 * a13 * a32) + (a02 * a10 * a33) - (a00 * a12 * a33);
        //newMat3._m7  = (a02 * a13 * a20) - (a03 * a12 * a20) + (a03 * a10 * a22) - (a00 * a13 * a22) - (a02 * a10 * a23) + (a00 * a12 * a23);
        //newMat3._m8  = (a11 * a23 * a30) - (a13 * a21 * a30) + (a13 * a20 * a31) - (a10 * a23 * a31) - (a11 * a20 * a33) + (a10 * a21 * a33);
        //newMat3._m9  = (a03 * a21 * a30) - (a01 * a23 * a30) - (a03 * a20 * a31) + (a00 * a23 * a31) + (a01 * a20 * a33) - (a00 * a21 * a33);
        //newMat3._m10 = (a01 * a13 * a30) - (a03 * a11 * a30) + (a03 * a10 * a31) - (a00 * a13 * a31) - (a01 * a10 * a33) + (a00 * a11 * a33);
        //newMat3._m11 = (a03 * a11 * a20) - (a01 * a13 * a20) - (a03 * a10 * a21) + (a00 * a13 * a21) + (a01 * a10 * a23) - (a00 * a11 * a23);
        //newMat3._m12 = (a12 * a21 * a30) - (a11 * a22 * a30) - (a12 * a20 * a31) + (a10 * a22 * a31) + (a11 * a20 * a32) - (a10 * a21 * a32);
        //newMat3._m13 = (a01 * a22 * a30) - (a02 * a21 * a30) + (a02 * a20 * a31) - (a00 * a22 * a31) - (a01 * a20 * a32) + (a00 * a21 * a32);
        //newMat3._m14 = (a02 * a11 * a30) - (a01 * a12 * a30) - (a02 * a10 * a31) + (a00 * a12 * a31) + (a01 * a10 * a32) - (a00 * a11 * a32);
        //newMat3._m15 = (a01 * a12 * a20) - (a02 * a11 * a20) + (a02 * a10 * a21) - (a00 * a12 * a21) - (a01 * a10 * a22) + (a00 * a11 * a22);

        //newMat3 *= invDet;

        //return newMat3;
    }

    Mat3 Mat3::getAdjoint()
    {
        //float cof = 0.0f;

        Mat3 newMat3;

        //Location in Mat3: x,y
        //1,1
        newMat3._m0 = subMDet(this->m5(), this->m9(), this->m13(), this->m6(), this->m10(), this->m14(), this->m7(), this->m11(), this->m15());
        //2,1
        newMat3._m1 = subMDet(this->m4(), this->m8(), this->m12(), this->m6(), this->m10(), this->m14(), this->m7(), this->m11(), this->m15());
        //3,1
        newMat3._m2 = subMDet(this->m4(), this->m8(), this->m12(), this->m5(), this->m9(), this->m13(), this->m7(), this->m11(), this->m15());
        //4,1
        newMat3._m3 = subMDet(this->m4(), this->m8(), this->m12(), this->m5(), this->m9(), this->m13(), this->m6(), this->m10(), this->m14());
        //1,2
        newMat3._m4 = subMDet(this->m1(), this->m9(), this->m13(), this->m2(), this->m10(), this->m14(), this->m3(), this->m11(), this->m15());
        //2,2
        newMat3._m5 = subMDet(this->m0(), this->m8(), this->m12(), this->m2(), this->m10(), this->m14(), this->m3(), this->m11(), this->m15());
        //3,2
        newMat3._m6 = subMDet(this->m0(), this->m8(), this->m12(), this->m1(), this->m9(), this->m13(), this->m3(), this->m11(), this->m15());
        //4,2
        newMat3._m7 = subMDet(this->m0(), this->m8(), this->m12(), this->m1(), this->m9(), this->m13(), this->m2(), this->m10(), this->m14());
        //1,3
        newMat3._m8 = subMDet(this->m1(), this->m5(), this->m13(), this->m2(), this->m6(), this->m14(), this->m3(), this->m7(), this->m15());
        //2,3
        newMat3._m9 = subMDet(this->m0(), this->m4(), this->m12(), this->m2(), this->m6(), this->m14(), this->m3(), this->m7(), this->m15());
        //3,3
        newMat3._m10 = subMDet(this->m0(), this->m4(), this->m12(), this->m1(), this->m5(), this->m13(), this->m3(), this->m7(), this->m15());
        //4,3
        newMat3._m11 = subMDet(this->m0(), this->m4(), this->m12(), this->m1(), this->m5(), this->m13(), this->m2(), this->m6(), this->m14());
        //1,4
        newMat3._m12 = subMDet(this->m1(), this->m5(), this->m9(), this->m2(), this->m6(), this->m10(), this->m3(), this->m7(), this->m11());
        //2,4
        newMat3._m13 = subMDet(this->m0(), this->m4(), this->m8(), this->m2(), this->m6(), this->m10(), this->m3(), this->m7(), this->m11());
        //3,4
        newMat3._m14 = subMDet(this->m0(), this->m4(), this->m8(), this->m1(), this->m5(), this->m9(), this->m3(), this->m7(), this->m11());
        //4,4
        newMat3._m15 = subMDet(this->m0(), this->m4(), this->m8(), this->m1(), this->m5(), this->m9(), this->m2(), this->m6(), this->m10());

        ////Location in Mat3: x,y
        ////1,1
        //newMat3._m0 = powf(-1, 2) * subMDet(this->m5(), this->m9(), this->m13(), this->m6(), this->m10(), this->m14(), this->m7(), this->m11(), this->m15());
        ////2,1
        //newMat3._m1 = powf(-1, 3) * subMDet(this->m4(), this->m8(), this->m12(), this->m6(), this->m10(), this->m14(), this->m7(), this->m11(), this->m15());
        ////3,1
        //newMat3._m2 = powf(-1, 4) * subMDet(this->m4(), this->m8(), this->m12(), this->m5(), this->m9(), this->m13(), this->m7(), this->m11(), this->m15());
        ////4,1
        //newMat3._m3 = powf(-1, 5) * subMDet(this->m4(), this->m8(), this->m12(), this->m5(), this->m9(), this->m13(), this->m6(), this->m10(), this->m14());
        ////1,2
        //newMat3._m4 = powf(-1, 3) * subMDet(this->m1(), this->m9(), this->m13(), this->m2(), this->m10(), this->m14(), this->m3(), this->m11(), this->m15());
        ////2,2
        //newMat3._m5 = powf(-1, 4) * subMDet(this->m0(), this->m8(), this->m12(), this->m2(), this->m10(), this->m14(), this->m3(), this->m11(), this->m15());
        ////3,2
        //newMat3._m6 = powf(-1, 5) * subMDet(this->m0(), this->m8(), this->m12(), this->m1(), this->m9(), this->m13(), this->m3(), this->m11(), this->m15());
        ////4,2
        //newMat3._m7 = powf(-1, 6) * subMDet(this->m0(), this->m8(), this->m12(), this->m1(), this->m9(), this->m13(), this->m2(), this->m10(), this->m14());
        ////1,3
        //newMat3._m8 = powf(-1, 4) * subMDet(this->m1(), this->m5(), this->m13(), this->m2(), this->m6(), this->m14(), this->m3(), this->m7(), this->m15());
        ////2,3
        //newMat3._m9 = powf(-1, 5) * subMDet(this->m0(), this->m4(), this->m12(), this->m2(), this->m6(), this->m14(), this->m3(), this->m7(), this->m15());
        ////3,3
        //newMat3._m10 = powf(-1, 6) * subMDet(this->m0(), this->m4(), this->m12(), this->m1(), this->m5(), this->m13(), this->m3(), this->m7(), this->m15());
        ////4,3
        //newMat3._m11 = powf(-1, 7) * subMDet(this->m0(), this->m4(), this->m12(), this->m1(), this->m5(), this->m13(), this->m2(), this->m6(), this->m14());
        ////1,4
        //newMat3._m12 = powf(-1, 5) * subMDet(this->m1(), this->m5(), this->m9(), this->m2(), this->m6(), this->m10(), this->m3(), this->m7(), this->m11());
        ////2,4
        //newMat3._m13 = powf(-1, 6) * subMDet(this->m0(), this->m4(), this->m8(), this->m2(), this->m6(), this->m10(), this->m3(), this->m7(), this->m11());
        ////3,4
        //newMat3._m14 = powf(-1, 7) * subMDet(this->m0(), this->m4(), this->m8(), this->m1(), this->m5(), this->m9(), this->m3(), this->m7(), this->m11());
        ////4,4
        //newMat3._m15 = powf(-1, 8) * subMDet(this->m0(), this->m4(), this->m8(), this->m1(), this->m5(), this->m9(), this->m2(), this->m6(), this->m10());


        return newMat3;
    }

    //4x4 Mat3, so we pass in a 3x3 subMat3, or 9 floats
    float Mat3::subMDet(float inX1, float inX2, float inX3, float inY1, float inY2, float inY3, float inZ1, float inZ2, float inZ3)
    {

        //sub Mat3 looks like this
        /*
        x1, y1, z1
        x2, y2, z2
        x3, y3, z3
        */

        float subMat3Det = 0.0f;

        subMat3Det = (inX1 * inY2 * inZ3) + (inY1 * inZ2 * inX3) + (inZ1 * inX2 * inY3)
            - (inZ1 * inY2 * inX3) - (inY1 * inX2 * inZ3) - (inX1 * inZ2 * inY3);

        return subMat3Det;
    }

    Vec4& Mat3::GetV0()
    {
        return this->_v0;
    }
    Vec4& Mat3::GetV1()
    {
        return this->_v1;
    }
    Vec4& Mat3::GetV2()
    {
        return this->_v2;
    }
    Vec4& Mat3::GetV3()
    {
        return this->_v3;
    }

    const float Mat3::m0()  const
    {
        return this->_m0;
    }
    const float Mat3::m1()  const
    {
        return this->_m1;
    }
    const float Mat3::m2()  const
    {
        return this->_m2;
    }
    const float Mat3::m3()  const
    {
        return this->_m3;
    }
    const float Mat3::m4()  const
    {
        return this->_m4;
    }
    const float Mat3::m5()  const
    {
        return this->_m5;
    }
    const float Mat3::m6()  const
    {
        return this->_m6;
    }
    const float Mat3::m7()  const
    {
        return this->_m7;
    }
    const float Mat3::m8()  const
    {
        return this->_m8;
    }
    const float Mat3::m9()  const
    {
        return this->_m9;
    }
    const float Mat3::m10()  const
    {
        return this->_m10;
    }
    const float Mat3::m11()  const
    {
        return this->_m11;
    }
    const float Mat3::m12()  const
    {
        return this->_m12;
    }
    const float Mat3::m13()  const
    {
        return this->_m13;
    }
    const float Mat3::m14()  const
    {
        return this->_m14;
    }
    const float Mat3::m15()  const
    {
        return this->_m15;
    }

    float& Mat3::m0()
    {
        return this->_m0;
    }

    float& Mat3::m1()
    {
        return this->_m1;
    }

    float& Mat3::m2()
    {
        return this->_m2;
    }

    float& Mat3::m3()
    {
        return this->_m3;
    }

    float& Mat3::m4()
    {
        return this->_m4;
    }

    float& Mat3::m5()
    {
        return this->_m5;
    }

    float& Mat3::m6()
    {
        return this->_m6;
    }

    float& Mat3::m7()
    {
        return this->_m7;
    }

    float& Mat3::m8()
    {
        return this->_m8;
    }

    float& Mat3::m9()
    {
        return this->_m9;
    }

    float& Mat3::m10()
    {
        return this->_m10;
    }

    float& Mat3::m11()
    {
        return this->_m11;
    }

    float& Mat3::m12()
    {
        return this->_m12;
    }

    float& Mat3::m13()
    {
        return this->_m13;
    }

    float& Mat3::m14()
    {
        return this->_m14;
    }

    float& Mat3::m15()
    {
        return this->_m15;
    }

    const float Mat3::operator[](m0_enum) const
    {
        return this->_m0;
    }
    const float Mat3::operator[](m1_enum) const
    {
        return this->_m1;
    }
    const float Mat3::operator[](m2_enum) const
    {
        return this->_m2;
    }
    const float Mat3::operator[](m3_enum) const
    {
        return this->_m3;
    }
    const float Mat3::operator[](m4_enum) const
    {
        return this->_m4;
    }
    const float Mat3::operator[](m5_enum) const
    {
        return this->_m5;
    }
    const float Mat3::operator[](m6_enum) const
    {
        return this->_m6;
    }
    const float Mat3::operator[](m7_enum) const
    {
        return this->_m7;
    }
    const float Mat3::operator[](m8_enum) const
    {
        return this->_m8;
    }
    const float Mat3::operator[](m9_enum) const
    {
        return this->_m9;
    }
    const float Mat3::operator[](m10_enum) const
    {
        return this->_m10;
    }
    const float Mat3::operator[](m11_enum) const
    {
        return this->_m11;
    }
    const float Mat3::operator[](m12_enum) const
    {
        return this->_m12;
    }
    const float Mat3::operator[](m13_enum) const
    {
        return this->_m13;
    }
    const float Mat3::operator[](m14_enum) const
    {
        return this->_m14;
    }
    const float Mat3::operator[](m15_enum) const
    {
        return this->_m15;
    }

    float& Mat3::operator[](m0_enum)
    {
        return this->_m0;
    }
    float& Mat3::operator[](m1_enum)
    {
        return this->_m1;
    }
    float& Mat3::operator[](m2_enum)
    {
        return this->_m2;
    }
    float& Mat3::operator[](m3_enum)
    {
        return this->_m3;
    }
    float& Mat3::operator[](m4_enum)
    {
        return this->_m4;
    }
    float& Mat3::operator[](m5_enum)
    {
        return this->_m5;
    }
    float& Mat3::operator[](m6_enum)
    {
        return this->_m6;
    }
    float& Mat3::operator[](m7_enum)
    {
        return this->_m7;
    }
    float& Mat3::operator[](m8_enum)
    {
        return this->_m8;
    }
    float& Mat3::operator[](m9_enum)
    {
        return this->_m9;
    }
    float& Mat3::operator[](m10_enum)
    {
        return this->_m10;
    }
    float& Mat3::operator[](m11_enum)
    {
        return this->_m11;
    }
    float& Mat3::operator[](m12_enum)
    {
        return this->_m12;
    }
    float& Mat3::operator[](m13_enum)
    {
        return this->_m13;
    }
    float& Mat3::operator[](m14_enum)
    {
        return this->_m14;
    }
    float& Mat3::operator[](m15_enum)
    {
        return this->_m15;
    }

    void Mat3::m0(float inM0)
    {
        this->_m0 = inM0;
    }

    void Mat3::m1(float inM1)
    {
        this->_m1 = inM1;
    }

    void Mat3::m2(float inM2)
    {
        this->_m2 = inM2;
    }

    void Mat3::m3(float inM3)
    {
        this->_m3 = inM3;
    }

    void Mat3::m4(float inM4)
    {
        this->_m4 = inM4;
    }

    void Mat3::m5(float inM5)
    {
        this->_m5 = inM5;
    }

    void Mat3::m6(float inM6)
    {
        this->_m6 = inM6;
    }

    void Mat3::m7(float inM7)
    {
        this->_m7 = inM7;
    }

    void Mat3::m8(float inM8)
    {
        this->_m8 = inM8;
    }

    void Mat3::m9(float inM9)
    {
        this->_m9 = inM9;
    }

    void Mat3::m10(float inM10)
    {
        this->_m10 = inM10;
    }

    void Mat3::m11(float inM11)
    {
        this->_m11 = inM11;
    }

    void Mat3::m12(float inM12)
    {
        this->_m12 = inM12;
    }

    void Mat3::m13(float inM13)
    {
        this->_m13 = inM13;
    }

    void Mat3::m14(float inM14)
    {
        this->_m14 = inM14;
    }

    void Mat3::m15(float inM15)
    {
        this->_m15 = inM15;
    }

    Mat3 operator*(float inFloat, Mat3 inMat3)
    {
        Mat3 newMat3;

        newMat3._m0 = inMat3._m0 * inFloat;
        newMat3._m1 = inMat3._m1 * inFloat;
        newMat3._m2 = inMat3._m2 * inFloat;
        newMat3._m3 = inMat3._m3 * inFloat;
        newMat3._m4 = inMat3._m4 * inFloat;
        newMat3._m5 = inMat3._m5 * inFloat;
        newMat3._m6 = inMat3._m6 * inFloat;
        newMat3._m7 = inMat3._m7 * inFloat;
        newMat3._m8 = inMat3._m8 * inFloat;
        newMat3._m9 = inMat3._m9 * inFloat;
        newMat3._m10 = inMat3._m10 * inFloat;
        newMat3._m11 = inMat3._m11 * inFloat;
        newMat3._m12 = inMat3._m12 * inFloat;
        newMat3._m13 = inMat3._m13 * inFloat;
        newMat3._m14 = inMat3._m14 * inFloat;
        newMat3._m15 = inMat3._m15 * inFloat;

        return newMat3;
    }

    Mat3 operator*(Mat3 inMat3, float inFloat)
    {
        Mat3 newMat3;

        newMat3._m0 = inMat3._m0 * inFloat;
        newMat3._m1 = inMat3._m1 * inFloat;
        newMat3._m2 = inMat3._m2 * inFloat;
        newMat3._m3 = inMat3._m3 * inFloat;
        newMat3._m4 = inMat3._m4 * inFloat;
        newMat3._m5 = inMat3._m5 * inFloat;
        newMat3._m6 = inMat3._m6 * inFloat;
        newMat3._m7 = inMat3._m7 * inFloat;
        newMat3._m8 = inMat3._m8 * inFloat;
        newMat3._m9 = inMat3._m9 * inFloat;
        newMat3._m10 = inMat3._m10 * inFloat;
        newMat3._m11 = inMat3._m11 * inFloat;
        newMat3._m12 = inMat3._m12 * inFloat;
        newMat3._m13 = inMat3._m13 * inFloat;
        newMat3._m14 = inMat3._m14 * inFloat;
        newMat3._m15 = inMat3._m15 * inFloat;

        return newMat3;
    }

    Mat3 operator/(Mat3 inMat3, float inFloat)
    {
        Mat3 newMat3;

        newMat3._m0 = inMat3._m0 / inFloat;
        newMat3._m1 = inMat3._m1 / inFloat;
        newMat3._m2 = inMat3._m2 / inFloat;
        newMat3._m3 = inMat3._m3 / inFloat;
        newMat3._m4 = inMat3._m4 / inFloat;
        newMat3._m5 = inMat3._m5 / inFloat;
        newMat3._m6 = inMat3._m6 / inFloat;
        newMat3._m7 = inMat3._m7 / inFloat;
        newMat3._m8 = inMat3._m8 / inFloat;
        newMat3._m9 = inMat3._m9 / inFloat;
        newMat3._m10 = inMat3._m10 / inFloat;
        newMat3._m11 = inMat3._m11 / inFloat;
        newMat3._m12 = inMat3._m12 / inFloat;
        newMat3._m13 = inMat3._m13 / inFloat;
        newMat3._m14 = inMat3._m14 / inFloat;
        newMat3._m15 = inMat3._m15 / inFloat;

        return newMat3;
    }

    Mat3 Mat3::operator*=(float inFloat)
    {
        this->_m0 *= inFloat;
        this->_m1 *= inFloat;
        this->_m2 *= inFloat;
        this->_m3 *= inFloat;
        this->_m4 *= inFloat;
        this->_m5 *= inFloat;
        this->_m6 *= inFloat;
        this->_m7 *= inFloat;
        this->_m8 *= inFloat;
        this->_m9 *= inFloat;
        this->_m10 *= inFloat;
        this->_m11 *= inFloat;
        this->_m12 *= inFloat;
        this->_m13 *= inFloat;
        this->_m14 *= inFloat;
        this->_m15 *= inFloat;

        return *this;
    }

	void Mat3::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	};

}

// ---  End of File ---
