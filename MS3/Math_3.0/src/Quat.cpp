//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{ 

// Do your magic here
    Quat::Quat()
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 1.0f;
    }

    Quat::Quat(const Quat& inQuat)
    {
        this->_qx = inQuat._qx;
        this->_qy = inQuat._qy;
        this->_qz = inQuat._qz;
        this->_qw = inQuat._qw;
    }

    Quat& Quat::operator=(const Quat& inQuat)
    {
        this->_qx = inQuat._qx;
        this->_qy = inQuat._qy;
        this->_qz = inQuat._qz;
        this->_qw = inQuat._qw;

        return *this;
    }

    Quat::~Quat()
    {
    }

    Quat::Quat(float F1, float F2, float F3, float F4)
    {
        this->_qx = F1;
        this->_qy = F2;
        this->_qz = F3;
        this->_qw = F4;
    }

    Quat::Quat(Vec3 inVec, float F1)
    {
        this->_qx = inVec._vx;
        this->_qy = inVec._vy;
        this->_qz = inVec._vz;
        this->_qw = F1;
    }

    Quat::Quat(Special special)
    {
        if (special == Quat::Special::Zero)
        {
            this->_qx = 0.0f;
            this->_qy = 0.0f;
            this->_qz = 0.0f;
            this->_qw = 0.0f;
        }
        else if (special == Quat::Special::Identity)
        {
            this->_qx = 0.0f;
            this->_qy = 0.0f;
            this->_qz = 0.0f;
            this->_qw = 1.0f;
        }
    }

    Quat::Quat(Mat4 M)
    {
        float tr = M.m0() + M.m5() + M.m10();
        float S;

        if (tr > 0.0f)
        {
            S = 2 * sqrtf(tr + 1.0f);
            this->qw() = 0.25f * S;
            this->qx() = -(M.m9() - M.m6()) / S;
            this->qy() = -(M.m2() - M.m8()) / S;
            this->qz() = -(M.m4() - M.m1()) / S;
        }
        else if((M.m0() > M.m5()) && (M.m0() > M.m10()))
        {
            S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
            this->qw() = -(M.m9() - M.m6()) / S;
            this->qx() = 0.25f * S;
            this->qy() = (M.m1() + M.m4()) / S;
            this->qz() = (M.m2() + M.m8()) / S;
        }
        else if(M.m5() > M.m10())
        {
            S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
            this->qw() = -(M.m2() - M.m8()) / S;
            this->qx() = (M.m1() + M.m4()) / S;
            this->qy() = 0.25f * S;
            this->qz() = (M.m6() + M.m9()) / S;
        }
        else
        {
            S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
            this->qw() = -(M.m4() - M.m1()) / S;
            this->qx() = (M.m2() + M.m8()) / S;
            this->qy() = (M.m6() + M.m9()) / S;
            this->qz() = 0.25f * S;
        }
    }

    Quat::Quat(Quat::Rot rot, Vec3 inV3, float inF)
    {
        if (rot == Quat::Rot::AxisAngle)
        {
            Quat tmpQ = Quat(inV3, inF);
            *this = tmpQ.axisAngle();
        }
    }

    Quat::Quat(Quat::Rot3 rot, float inX, float inY, float inZ)
    {
        if (rot == Quat::Rot3::XYZ)
        {
            Quat xRot(Quat::Rot1::X, inX);
            Quat yRot(Quat::Rot1::Y, inY);
            Quat zRot(Quat::Rot1::Z, inZ);

            *this = xRot * yRot * zRot;
        }
    }

    Quat::Quat(Quat::Rot1 rot, float inF)
    {
        Quat tmp(0.0f, 0.0f, 0.0f, inF);
        
        if (rot == Quat::Rot1::X)
        {            
            tmp.qx() = 1.0f;
        }
        else if (rot == Quat::Rot1::Y)
        {
            tmp.qy() = 1.0f;
        }
        else if (rot == Quat::Rot1::Z)
        {
            tmp.qz() = 1.0f;
        }

        *this = tmp.axisAngle();

    }

    Quat::Quat(Quat::Orient orient, Vec3 in1V3, Vec3 in2V3)
    {
        Mat4 mOrient;
        Quat qOrient;

        if (orient == Quat::Orient::LocalToWorld)
        {
            mOrient = Mat4(Mat4::Orient::LocalToWorld, in1V3, in2V3);
            qOrient = mOrient;
        }
        if (orient == Quat::Orient::WorldToLocal)
        {
            mOrient = Mat4(Mat4::Orient::WorldToLocal, in1V3, in2V3);
            qOrient = mOrient;
        }

        *this = qOrient;
    }

    void Quat::set(float x, float y, float z, float w)
    {
        this->_qx = x;
        this->_qy = y;
        this->_qz = z;
        this->_qw = w;
    }

    void Quat::set(Quat inQ)
    {
        this->_qx = inQ._qx;
        this->_qy = inQ._qy;
        this->_qz = inQ._qz;
        this->_qw = inQ._qw;        
    }

    void Quat::set(Mat4 M)
    {
        float tr = M.m0() + M.m5() + M.m10();
        float S;

        if (tr > 0.0f)
        {
            S = 2 * sqrtf(tr + 1.0f);
            this->qw() = 0.25f * S;
            this->qx() = -(M.m9() - M.m6()) / S;
            this->qy() = -(M.m2() - M.m8()) / S;
            this->qz() = -(M.m4() - M.m1()) / S;
        }
        else if ((M.m0() > M.m5()) && (M.m0() > M.m10()))
        {
            S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
            this->qw() = -(M.m9() - M.m6()) / S;
            this->qx() = 0.25f * S;
            this->qy() = (M.m1() + M.m4()) / S;
            this->qz() = (M.m2() + M.m8()) / S;
        }
        else if (M.m5() > M.m10())
        {
            S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
            this->qw() = -(M.m2() - M.m8()) / S;
            this->qx() = (M.m1() + M.m4()) / S;
            this->qy() = 0.25f * S;
            this->qz() = (M.m6() + M.m9()) / S;
        }
        else
        {
            S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
            this->qw() = -(M.m4() - M.m1()) / S;
            this->qx() = (M.m2() + M.m8()) / S;
            this->qy() = (M.m6() + M.m9()) / S;
            this->qz() = 0.25f * S;
        }
    }

    void Quat::set(Special special)
    {
        if (special == Quat::Special::Zero)
        {
            this->_qx = 0.0f;
            this->_qy = 0.0f;
            this->_qz = 0.0f;
            this->_qw = 0.0f;
        }
        else if (special == Quat::Special::Identity)
        {
            this->_qx = 0.0f;
            this->_qy = 0.0f;
            this->_qz = 0.0f;
            this->_qw = 1.0f;
        }
    }

    void Quat::set(Quat::Rot1 rot, float inF)
    {
        
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = inF;

        if (rot == Quat::Rot1::X)
        {
            this->_qx = 1.0f;
        }
        else if (rot == Quat::Rot1::Y)
        {
            this->_qy = 1.0f;
        }
        else if (rot == Quat::Rot1::Z)
        {
            this->_qz = 1.0f;
        }

        *this = this->axisAngle();
    }

    //void Quat::set(Quat::Rot1 rot, Vec3& inV3, float inF)
    //{
    //    AZUL_REPLACE_ME(inF);
    //    AZUL_REPLACE_ME(inV3);
    //    if (rot == Quat::Rot1::X)
    //    {

    //    }
    //    else if (rot == Quat::Rot1::Y)
    //    {

    //    }
    //    else if (rot == Quat::Rot1::Z)
    //    {

    //    }
    //}

    void Quat::set(Quat::Rot rot, Vec3 inV3, float inF)
    {
        if (rot == Quat::Rot::AxisAngle)
        {
            Quat tmpQ = Quat(inV3, inF);
            *this = tmpQ.axisAngle();
        }
    }

    void Quat::set(Quat::Rot3 rot, float inX, float inY, float inZ)
    {
        if (rot == Quat::Rot3::XYZ)
        {
            Quat xRot(Quat::Rot1::X, inX);
            Quat yRot(Quat::Rot1::Y, inY);
            Quat zRot(Quat::Rot1::Z, inZ);

            *this = xRot * yRot * zRot;
        }        
    }

    void Quat::set(Quat::Orient orient, Vec3 in1V3, Vec3 in2V3)
    {
        Mat4 mOrient;
        Quat qOrient;

        if (orient == Quat::Orient::LocalToWorld)
        {
            mOrient = Mat4(Mat4::Orient::LocalToWorld, in1V3, in2V3);
            qOrient = mOrient;
        }
        if (orient == Quat::Orient::WorldToLocal)
        {
            mOrient = Mat4(Mat4::Orient::WorldToLocal, in1V3, in2V3);
            qOrient = mOrient;
        }

        *this = qOrient;
    }



    Quat Quat::operator+(Quat inQ)
    {
        Quat newQuat;

        newQuat._qx = this->_qx + inQ._qx;
        newQuat._qy = this->_qy + inQ._qy;
        newQuat._qz = this->_qz + inQ._qz;
        newQuat._qw = this->_qw + inQ._qw;

        return newQuat;
    }

    Quat Quat::operator+(float inFloat)
    {
        Quat newQuat;

        newQuat._qx = this->_qx + inFloat;
        newQuat._qy = this->_qy + inFloat;
        newQuat._qz = this->_qz + inFloat;
        newQuat._qw = this->_qw + inFloat;

        return newQuat;
    }

    Quat Quat::operator-(Quat inQ) const
    {
        Quat newQuat;

        newQuat._qx = this->_qx - inQ._qx;
        newQuat._qy = this->_qy - inQ._qy;
        newQuat._qz = this->_qz - inQ._qz;
        newQuat._qw = this->_qw - inQ._qw;

        return newQuat;
    }

    Quat Quat::operator-(float inFloat) const
    {
        Quat newQuat;

        newQuat._qx = this->_qx - inFloat;
        newQuat._qy = this->_qy - inFloat;
        newQuat._qz = this->_qz - inFloat;
        newQuat._qw = this->_qw - inFloat;

        return newQuat;
    }

    Quat Quat::operator*(Quat inQ) const
    {
        Vec3 newV3;        

        newV3 = inQ._qV3.cross(this->_qV3);
        newV3 += inQ._qw * this->_qV3;
        newV3 += this->qw() * inQ._qV3;

        Vec3 test = this->_qV3;
        float newReal = 0.0f;

        newReal += this->qw() * inQ.qw();
        newReal -= test.dot(inQ._qV3);
      
        return Quat(newV3, newReal);
    }

    Quat Quat::operator*(float inFloat) const
    {
        Quat newQuat;

        newQuat._qx = this->_qx * inFloat;
        newQuat._qy = this->_qy * inFloat;
        newQuat._qz = this->_qz * inFloat;
        newQuat._qw = this->_qw * inFloat;

        return newQuat;
    }

    Quat Quat::operator/(Quat inQ) const
    {
        Quat newQuat;

        newQuat._qx = this->_qx / inQ._qx;
        newQuat._qy = this->_qy / inQ._qy;
        newQuat._qz = this->_qz / inQ._qz;
        newQuat._qw = this->_qw / inQ._qw;

        return newQuat;
    }

    Quat Quat::operator/(float inFloat) const
    {
        Quat newQuat;

        newQuat._qx = this->_qx / inFloat;
        newQuat._qy = this->_qy / inFloat;
        newQuat._qz = this->_qz / inFloat;
        newQuat._qw = this->_qw / inFloat;

        return newQuat;
    }

    Quat Quat::operator+=(const Quat inQ)
    {
        this->_qx += inQ._qx;
        this->_qy += inQ._qy;
        this->_qz += inQ._qz;
        this->_qw += inQ._qw;

        return *this;
    }

    Quat Quat::operator-=(const Quat inQ)
    {
        this->_qx -= inQ._qx;
        this->_qy -= inQ._qy;
        this->_qz -= inQ._qz;
        this->_qw -= inQ._qw;

        return *this;
    }

    Quat Quat::operator+=(const float inF)
    {
        this->_qx += inF;
        this->_qy += inF;
        this->_qz += inF;
        this->_qw += inF;

        return *this;
    }

    Quat Quat::operator-=(const float inF)
    {
        this->_qx -= inF;
        this->_qy -= inF;
        this->_qz -= inF;
        this->_qw -= inF;

        return *this;
    }

    Quat Quat::operator*=(const Quat inQ)
    {
        //P = this
        //Q = inQ
        // 
        //v = full vector ( xyz or xyzw?)
        //w = real (qw)
        //PQ = cross(PvQv) + QwPv + PwQv + PwQw - dot(PvQv)

        Vec3 newV3;

        newV3 = inQ._qV3.cross(this->_qV3);
        newV3 += inQ._qw * this->_qV3;
        newV3 += this->qw() * inQ._qV3;

        Vec3 test = this->_qV3;
        float newReal = 0.0f;

        newReal += this->qw() * inQ.qw();
        newReal -= test.dot(inQ._qV3);

        *this = Quat(newV3, newReal);

        return *this;
    }

    Quat Quat::operator/=(const Quat inQ)
    {
        this->_qx /= inQ._qx;
        this->_qy /= inQ._qy;
        this->_qz /= inQ._qz;
        this->_qw /= inQ._qw;

        return *this;
    }

    Quat Quat::operator*=(const float inF)
    {
        this->_qx *= inF;
        this->_qy *= inF;
        this->_qz *= inF;
        this->_qw *= inF;

        return *this;
    }

    Quat Quat::operator/=(const float inF)
    {
        this->_qx /= inF;
        this->_qy /= inF;
        this->_qz /= inF;
        this->_qw /= inF;

        return *this;
    }

    Quat Quat::operator-()
    {
        Quat newQuat;

        newQuat._qx = -this->_qx;
        newQuat._qy = -this->_qy;
        newQuat._qz = -this->_qz;
        newQuat._qw = -this->_qw;

        return newQuat;
    }

    Quat Quat::operator+()
    {
        Quat newQuat;

        newQuat._qx = this->_qx;
        newQuat._qy = this->_qy;
        newQuat._qz = this->_qz;
        newQuat._qw = this->_qw;

        return newQuat;
    }

    void Quat::Lqcvq(const Vec3& inV3, Vec3& outV3) const
    {
        outV3 = (2.0f * this->_qw) * this->_qV3.cross(inV3);
        outV3 += (this->_qw * this->_qw - this->_qV3.dot(this->_qV3)) * inV3;
        outV3 += this->_qV3 * (2.0f * this->_qV3.dot(inV3));
    }

    void Quat::Lqvqc(const Vec3& inV3, Vec3& outV3) const
    {
        outV3 = (2.0f * this->_qw) * inV3.cross(this->_qV3);
        outV3 += (this->_qw * this->_qw - this->_qV3.dot(this->_qV3)) * inV3;
        outV3 += this->_qV3 * (2.0f * this->_qV3.dot(inV3));      
    }

    Quat Quat::getConj()
    {
        return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
    }

    Quat Quat::conj()
    {
        *this = Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
        return *this;
    }

    Quat Quat::getT()
    {
        Mat4 mThis(*this);
        Quat qT = Quat(mThis.T());
        return qT;
    }

    Quat Quat::T()
    {
        Mat4 mThis(*this);
        *this = Quat(mThis.T());
        return *this;
    }

    Quat Quat::inv()
    {
        Quat qConjugate = this->getConj();
        float magSquared = this->magSquared();

        *this = qConjugate / magSquared;

        return *this;
    }

    Quat Quat::getInv()
    {     
        Quat qConjugate = this->getConj();        
        float magSquared = this->magSquared();

        return qConjugate / magSquared;
    }

    Quat Quat::cross(Quat inQ) const
    {
        Quat newQ;

		newQ._qx = this->_qy * inQ._qz - this->_qz * inQ._qy;
		newQ._qy = -(this->_qx * inQ._qz - this->_qz * inQ._qx);
		newQ._qz = this->_qx * inQ._qy - this->_qy * inQ._qx;

		return newQ;
    }

    float Quat::dot(Quat inQ)
    {       
       return this->qx() * inQ.qx() + this->qy() * inQ.qy() 
           + this->qz() * inQ.qz() + this->qw() * inQ.qw();      
    }

    Quat Quat::norm()
    {
        float mag;
        mag = this->mag();

        this->_qx /= mag;
        this->_qy /= mag;
        this->_qz /= mag;
        this->_qw /= mag;

        return *this;
    }

    Quat Quat::getNorm()
    {
        Quat newQ = *this;
        return newQ.norm();
    }

    void Quat::getAxis(Vec3& outV3)
    {       
        Vec3 normV = this->_qV3.getNorm();                        
        outV3 = normV;
    }

    float Quat::getAngle()
    {
        float radian = this->qw();

        if (this->qw() > 1.0f)
        {
            radian = (3.14f / 180.0f) * this->_qw;
        }
        
        float angle = 2 * (Trig::acos(radian));
        return angle;
    }

    Quat Quat::axisAngle()
    {
        float angle = this->qw();

        float sinAngle = sin(angle * 0.5f);
        float cosAngle = cos(angle * 0.5f);

        Vec3 axis;
        this->getAxis(axis);

        Quat tmpQ = Quat(axis * sinAngle, cosAngle);
             
        return tmpQ;
    }

        //sin(angle / 2)axis + cos(angle / 2)

        //q inverse = sin(angle / 2)(-Axis) + cos(angle / 2);

        //-qv + real is inverse

    void Quat::set(Vec3 inVec, float F1)
    {
        this->_qx = inVec._vx;
        this->_qy = inVec._vy;
        this->_qz = inVec._vz;
        this->_qw = F1;
    }

    void Quat::getVec3(Vec3& setVec)
    {
        setVec._vx = this->_qx;
        setVec._vy = this->_qy;
        setVec._vz = this->_qz;
    }

    Vec3 Quat::setVec3()
    {
        return this->_qV3;
    }

    void Quat::setVec3(Vec3& setVec)
    {
        this->_qx = setVec._vx;
        this->_qy = setVec._vy;
        this->_qz = setVec._vz;
    }

    void Quat::getVec4(Vec4& setVec)
    {
        setVec._vx = this->_qx;
        setVec._vy = this->_qy;
        setVec._vz = this->_qz;
        setVec._vw = this->_qw;
    }

    Vec4 Quat::setVec4()
    {
        return this->_qV4;
    }

    void Quat::setVec4(Vec4& setVec)
    {
        this->_qV4 = setVec;
    }

    float Quat::mag()
    {
        return sqrtf(this->_qx * this->_qx + this->_qy * this->_qy + this->_qz * this->_qz + this->_qw * this->_qw);
    }

    float Quat::magSquared()
    {
        return this->_qx * this->_qx + this->_qy * this->_qy + this->_qz * this->_qz + this->_qw * this->_qw;
    }

    float Quat::invMag()
    {
        Quat invQ = this->getInv();

        return invQ.mag();
    }

    float Quat::len()
    {
        return sqrtf(this->qx() * this->qx() + this->qy() * this->qy() +
            this->qz() * this->qz() + this->qw() * this->qw());
    }

    Vec3 Quat::getVec3()
    {
        return this->_qV3;
    }

    bool Quat::isEqual(Quat inQ, float tolerance)
    {
        if (Util::isEqual(this->_qx, inQ._qx, tolerance) &&
            Util::isEqual(this->_qy, inQ._qy, tolerance) &&
            Util::isEqual(this->_qz, inQ._qz, tolerance) &&
            Util::isEqual(this->_qw, inQ._qw, tolerance))
        {
            return true;
        }

        return false;
    }

    bool Quat::isNegEqual(Quat inQ, float tolerance)
    {        
        return this->isEqual(-inQ,tolerance);
    }

    bool Quat::isZero(float tolerance)
    {
        if (this->_qx == 0 && this->_qy == 0 && this->_qz == 0 && this->_qw == 0)
        {
            return true;
        }

        if (abs(this->_qx) < tolerance && abs(this->_qy) < tolerance && abs(this->_qz) < tolerance)
        {
            return true;

        }

        return false;
    }

    bool Quat::isNormalized(float tolerance)
    {
        if (Util::isEqual(this->len(), 1.0f, tolerance))
        {
            return true;
        }

        return false;
    }

    bool Quat::isEquivalent(Quat v, float tolerance)
    {
        Quat tmp = -v;
        if (this->isEqual(v, tolerance) || this->isEqual(tmp, tolerance))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Quat::isIdentity(float tolerance)
    {
        if (Util::isEqual(this->_qx, 0, tolerance) &&
            Util::isEqual(this->_qy, 0, tolerance) &&
            Util::isEqual(this->_qz, 0, tolerance) &&
            Util::isEqual(this->_qw, 1, tolerance)
            )
        {            
            return true;
        }

        return false;
    }

    bool Quat::isConjugateEqual(Quat inQ, float tolerance)
    {
        Quat tmp = Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);

        return tmp.isEqual(inQ, tolerance);
    }

    const float Quat::operator[](const x_enum) const
    {
        return this->_qx;
    }

    const float Quat::operator[](const y_enum) const
    {
        return this->_qy;
    }

    const float Quat::operator[](const z_enum) const
    {
        return this->_qz;
    }

    const float Quat::operator[](const w_enum) const
    {        
        return this->_qw;
    }

    float& Quat::operator[](const x_enum)
    {
        return this->_qx;
    }

    float& Quat::operator[](const y_enum)
    {
        return this->_qy;
    }

    float& Quat::operator[](const z_enum)
    {
        return this->_qz;
    }

    float& Quat::operator[](const w_enum)
    {
        return this->_qw;
    }

    const float& Quat::qx() const
    {
        return this->_qx;
    }

    const float& Quat::qy() const
    {
        return this->_qy;
    }

    const float& Quat::qz() const
    {
        return this->_qz;
    }

    const float& Quat::qw() const
    {
        return this->_qw;
    }

    const float& Quat::real() const
    {
        return this->_qw;
    }

    float& Quat::qx()
    {
        return this->_qx;
    }

    float& Quat::qy()
    {
        return this->_qy;
    }

    float& Quat::qz()
    {
        return this->_qz;
    }

    float& Quat::qw()
    {
        return this->_qw;
    }

    float& Quat::real()
    {
        return this->_qw;
    }

    void Quat::qx(float inX)
    {
        this->_qx = inX;
    }

    void Quat::qy(float inY)
    {
        this->_qy = inY;
    }

    void Quat::qz(float inZ)
    {
        this->_qz = inZ;
    }

    void Quat::qw(float inW)
    {
        this->_qw = inW;
    }

    void Quat::real(float inW)
    {
        this->_qw = inW;
    }


    Quat operator+(float inFloat, Quat inQ)
    {
        Quat newQ;

        newQ._qx = inFloat + inQ._qx;
        newQ._qy = inFloat + inQ._qy;
        newQ._qz = inFloat + inQ._qz;
        newQ._qw = inFloat + inQ._qw;

        return newQ;
    }

    Quat operator-(float inFloat, Quat inQ)
    {
        Quat newQ;

        newQ._qx = inFloat - inQ._qx;
        newQ._qy = inFloat - inQ._qy;
        newQ._qz = inFloat - inQ._qz;
        newQ._qw = inFloat - inQ._qw;

        return newQ;
    }

    Quat operator*(float inFloat, Quat inQ)
    {
        Quat newQ;

        newQ._qx = inFloat * inQ._qx;
        newQ._qy = inFloat * inQ._qy;
        newQ._qz = inFloat * inQ._qz;
        newQ._qw = inFloat * inQ._qw;

        return newQ;
    }

    Quat operator/(float inFloat, Quat inQ)
    {
        Quat newQ;

        newQ._qx = inFloat / inQ._qx;
        newQ._qy = inFloat / inQ._qy;
        newQ._qz = inFloat / inQ._qz;
        newQ._qw = inFloat / inQ._qw;

        return newQ;
    }

}

//--- End of File ---
