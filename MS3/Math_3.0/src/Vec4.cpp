//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Do your magic here

	Vec4::Vec4()
	{
		this->_vx = 0.0f;
		this->_vy = 0.0f;
		this->_vz = 0.0f;
		this->_vw = 0.0f;
	}

	Vec4::Vec4(const Vec3& inVec3, float inFloat)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		this->_vw = inFloat;
	}

	Vec4::Vec4(const Vec3& inVec3)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		this->_vw = 1.0f;
	}

	//Copy Constructor
	Vec4::Vec4(const Vec4& inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;
		this->_vw = inVec4._vw;

		//Mat4::SetMs(this);
	}

	//Specialized Constructor
	Vec4::Vec4(const float x, const float y, const float z, const float w)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		this->_vw = w;
	}

	//Destructor
	Vec4::~Vec4()
	{
	}

	void Vec4::set(float x, float y, float z, float w)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		this->_vw = w;
	}

	void Vec4::set(Vec4 inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;
		this->_vw = inVec4._vw;
	}

	void Vec4::set(Vec3 inVec3)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		this->_vw = 1.0f;
	}

	void Vec4::set(Vec3 inVec3, float inFloat)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		this->_vw = inFloat;
	}

	//Assignment Operator
	const Vec4 Vec4::operator=(const Vec4& inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;
		this->_vw = inVec4._vw;

		return *this;
	}

	// + Operator Overloader
	Vec4 Vec4::operator+(Vec4 inVec4)
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx + inVec4._vx;
		newVec4._vy = this->_vy + inVec4._vy;
		newVec4._vz = this->_vz + inVec4._vz;
		newVec4._vw = this->_vw + inVec4._vw;

		return newVec4;
	}

	// - Operator Overloader
	Vec4 Vec4::operator-(Vec4 inVec4) const
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx - inVec4._vx;
		newVec4._vy = this->_vy - inVec4._vy;
		newVec4._vz = this->_vz - inVec4._vz;
		newVec4._vw = this->_vw - inVec4._vw;

		return newVec4;
	}

	// Vec4 - Float Operator Overloader
	Vec4 Vec4::operator-(float inFloat) const
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx - inFloat;
		newVec4._vy = this->_vy - inFloat;
		newVec4._vz = this->_vz - inFloat;
		newVec4._vw = this->_vw - inFloat;

		return newVec4;
	}

	// Vec4 + Float Operator Overloader
	Vec4 Vec4::operator+(float inFloat)
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx + inFloat;
		newVec4._vy = this->_vy + inFloat;
		newVec4._vz = this->_vz + inFloat;
		newVec4._vw = this->_vw + inFloat;

		return newVec4;
	}

	// Float + Vec4 Operator Overloader
	Vec4 operator+(float inFloat, Vec4 inVec4)
	{
		Vec4 newVec4;

		newVec4._vx = inFloat + inVec4._vx;
		newVec4._vy = inFloat + inVec4._vy;
		newVec4._vz = inFloat + inVec4._vz;
		newVec4._vw = inFloat + inVec4._vw;

		return newVec4;
	}

	// Float - Vec4 Operator Overloader
	Vec4 operator-(float inFloat, Vec4 inVec4)
	{
		Vec4 newVec4;

		newVec4._vx = inFloat - inVec4._vx;
		newVec4._vy = inFloat - inVec4._vy;
		newVec4._vz = inFloat - inVec4._vz;
		newVec4._vw = inFloat - inVec4._vw;

		return newVec4;
	}

	// Vec4 * Vec4 Operator Overloader
	Vec4 Vec4::operator*(Vec4 inVec4) const
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx * inVec4._vx;
		newVec4._vy = this->_vy * inVec4._vy;
		newVec4._vz = this->_vz * inVec4._vz;
		newVec4._vw = this->_vw * inVec4._vw;

		return newVec4;
	}

	// Vec4 * Float Operator Overloader
	Vec4 Vec4::operator*(float inFloat) const
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx * inFloat;
		newVec4._vy = this->_vy * inFloat;
		newVec4._vz = this->_vz * inFloat;
		newVec4._vw = this->_vw * inFloat;

		return newVec4;
	}

	const Vec4 Vec4::operator*=(float inFloat)
	{
		this->_vx *= inFloat;
		this->_vy *= inFloat;
		this->_vz *= inFloat;
		this->_vw *= inFloat;

		return *this;
	}

	Vec4 Vec4::operator+=(const Vec4 inVec4)
	{
		this->_vx += inVec4._vx;
		this->_vy += inVec4._vy;
		this->_vz += inVec4._vz;
		this->_vw += inVec4._vw;

		return *this;
	}

	Vec4 Vec4::operator-=(const Vec4 inVec4)
	{
		this->_vx -= inVec4._vx;
		this->_vy -= inVec4._vy;
		this->_vz -= inVec4._vz;
		this->_vw -= inVec4._vw;

		return *this;
	}

	Vec4 Vec4::operator=(const Vec3 inVec3)
	{
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		this->_vw = 1.0f;

		return *this;
	}

	Vec4 Vec4::operator-()
	{
		Vec4 newVec4;

		newVec4._vx = -this->_vx;
		newVec4._vy = -this->_vy;
		newVec4._vz = -this->_vz;
		newVec4._vw = -this->_vw;

		return newVec4;
	}

	Vec4 Vec4::operator+()
	{
		Vec4 newVec4;

		newVec4._vx = this->_vx;
		newVec4._vy = this->_vy;
		newVec4._vz = this->_vz;
		newVec4._vw = this->_vw;

		return newVec4;
	}

	// Float * Vec4 Operator Overloader
	Vec4 operator*(float inFloat, Vec4 inVec4)
	{
		Vec4 newVec4;

		newVec4._vx = inFloat * inVec4._vx;
		newVec4._vy = inFloat * inVec4._vy;
		newVec4._vz = inFloat * inVec4._vz;
		newVec4._vw = inFloat * inVec4._vw;

		return newVec4;
	}

	//Cross Product
	Vec4 Vec4::cross(Vec4 inVec4) const
	{
		Vec4 newVec4;

		newVec4._vx = this->_vy * inVec4._vz - this->_vz * inVec4._vy;
		newVec4._vy = -(this->_vx * inVec4._vz - this->_vz * inVec4._vx);
		newVec4._vz = this->_vx * inVec4._vy - this->_vy * inVec4._vx;

		return newVec4;
	}

	//Dot Product
	float Vec4::dot(Vec4 inVec4)
	{
		float dotProduct;

		dotProduct = this->_vx * inVec4._vx + this->_vy * inVec4._vy +
			this->_vz * inVec4._vz + this->_vw * inVec4._vw;

		return dotProduct;
	}

	float Vec4::getAngle(Vec4 inVec4)
	{
		return acos(this->dot(inVec4) / (this->mag() * inVec4.mag()));
	}

	Vec4 Vec4::norm()
	{
		float mag;

		mag = sqrt(this->_vx * this->_vx + this->_vy * this->_vy +
			this->_vz * this->_vz + this->_vw * this->_vw);

		this->_vx /= mag;
		this->_vy /= mag;
		this->_vz /= mag;
		this->_vw /= mag;

		return *this;
	}

	Vec4 Vec4::getNorm()
	{
		Vec4 newVec4or = *this;
		return newVec4or.norm();
	}

	Vec4Proxy Vec4::mag()
	{
		//float val = this->_vx * this->_vx + this->_vy * this->_vy + this->_vz * this->_vz;
		return Vec4Proxy(this->_vx, this->_vy, this->_vz);
		//return 1;
	}

	float Vec4::len()
	{
		return sqrtf(this->x() * this->x() + this->y() * this->y() +
			this->z() * this->z() + this->w() * this->w());
	}


	//Vec4 * Mat4 Operator Overloader
	Vec4& operator*(Vec4 v, Mat4 m)
	{
		Vec4 v0 = m.GetV0();
		Vec4 v1 = m.GetV1();
		Vec4 v2 = m.GetV2();
		Vec4 v3 = m.GetV3();

		v = Vec4(v._vx * v0._vx + v._vy * v1._vx + v._vz * v2._vx + v._vw * v3._vx,
			v._vx * v0._vy + v._vy * v1._vy + v._vz * v2._vy + v._vw * v3._vy,
			v._vx * v0._vz + v._vy * v1._vz + v._vz * v2._vz + v._vw * v3._vz,
			v._vx * v0._vw + v._vy * v1._vw + v._vz * v2._vw + v._vw * v3._vw);

		return  v;
	}

	Vec4 Vec4::operator*=(Mat4 inMat4)
	{
		Vec4 newVec4;

		Vec4 v0 = inMat4.GetV0();
		Vec4 v1 = inMat4.GetV1();
		Vec4 v2 = inMat4.GetV2();
		Vec4 v3 = inMat4.GetV3();

		newVec4._vx = this->_vx * v0._vx + this->_vy * v1._vx + this->_vz * v2._vx + this->_vw * v3._vx;
		newVec4._vy = this->_vx * v0._vy + this->_vy * v1._vy + this->_vz * v2._vy + this->_vw * v3._vy;
		newVec4._vz = this->_vx * v0._vz + this->_vy * v1._vz + this->_vz * v2._vz + this->_vw * v3._vz;
		newVec4._vw = this->_vx * v0._vw + this->_vy * v1._vw + this->_vz * v2._vw + this->_vw * v3._vw;

		*this = newVec4;

		return *this;
	}



	Vec4& operator*(Vec4 inVec4, Quat inQ)
	{
		Vec3 newV3;

		inQ.Lqcvq(inVec4, newV3);
		
		inVec4 = newV3;
		return inVec4;

	}

	Vec4 Vec4::operator*=(Quat inQ)
	{
		Vec3 newV3;
		inQ.Lqcvq(*this, newV3);
		*this = newV3;

		return *this;
	}

	// [] x Overloader
	const float Vec4::operator[](const x_enum) const
	{
		return this->_vx;
	}

	// [] y Overloader
	const float Vec4::operator[](const y_enum) const
	{
		return this->_vy;
	}

	// [] z Overloader
	const float Vec4::operator[](const z_enum) const
	{
		return this->_vz;
	}

	// [] w Overloader
	const float Vec4::operator[](const w_enum) const
	{
		return this->_vw;
	}

	float& Vec4::operator[](const x_enum)
	{
		return this->_vx;
	}

	float& Vec4::operator[](const y_enum)
	{
		return this->_vy;
	}

	float& Vec4::operator[](const z_enum)
	{
		return this->_vz;
	}

	float& Vec4::operator[](const w_enum)
	{
		return this->_vw;
	}



	const float& Vec4::x() const
	{
		return this->_vx;
	}
	const float& Vec4::y() const
	{
		return this->_vy;
	}
	const float& Vec4::z() const
	{
		return this->_vz;
	}
	const float& Vec4::w() const
	{
		return this->_vw;
	}

	float& Vec4::x()
	{
		return this->_vx;
	}

	float& Vec4::y()
	{
		return this->_vy;
	}

	float& Vec4::z()
	{
		return this->_vz;
	}

	float& Vec4::w()
	{
		return this->_vw;
	}

	void Vec4::x(float inX)
	{
		this->_vx = inX;
	}

	void Vec4::y(float inY)
	{
		this->_vy = inY;
	}

	void Vec4::z(float inZ)
	{
		this->_vz = inZ;
	}

	void Vec4::w(float inW)
	{
		this->_vw = inW;
	}

	bool Vec4::isEqual(Vec4 inVec4, float epsilon)
	{
		bool result = false;

		if (abs(this->_vx - inVec4._vx) < epsilon || abs(this->_vx - inVec4._vx) < epsilon)
		{
			if (abs(this->_vy - inVec4._vy) < epsilon || abs(this->_vy - inVec4._vy) < epsilon)
			{
				if (abs(this->_vz - inVec4._vz) < epsilon || abs(this->_vz - inVec4._vz) < epsilon)
				{
					result = true;
				}
			}
		}
		return result;
	}

	bool Vec4::isZero(float epsilon)
	{
		bool result = false;

		if (abs(this->_vx) <= epsilon && abs(this->_vy) <= epsilon && abs(this->_vz) <= epsilon)
		{
			result = true;
		}

		return result;
	}

	Vec4 operator*(const Vec3& v, const Mat4& m)
	{
		Vec4 localV4(v, 1);
		return localV4 * m;
	}

	Vec4 operator*=(const Vec3& v, const Mat4& m)
	{
		Vec4 localV4(v, 1);
		Vec4 V4ToReturn = localV4 * m;

		return V4ToReturn;
	}

	void Vec4::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	}
}

//--- End of File ---
