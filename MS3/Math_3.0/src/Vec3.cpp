//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
	// add magic

	Vec3::Vec3()
	{
		this->_vx = 0;
		this->_vy = 0;
		this->_vz = 0;
		//this->_vw = 1;
	}

	//Copy Constructor
	Vec3::Vec3(const Vec3& inVec3)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
		//this->_vw = inVec3._vw;

		//Mat4::SetMs(this);
	}

	Vec3::Vec3(const Vec4& inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;
	}

	//Specialized Constructor
	Vec3::Vec3(const float x, const float y, const float z)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		//this->_vw = w;
	}

	//Destructor
	Vec3::~Vec3()
	{
	}

	void Vec3::set(float x, float y, float z)
	{
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		//this->_vw = w;
	}

	void Vec3::set(Vec3 inVec3)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;
	}

	void Vec3::set(Vec4 inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;
	}

	//Assignment Operator
	const Vec3 Vec3::operator=(const Vec3& inVec3)
	{
		this->_mv = inVec3._mv;
		this->_vx = inVec3._vx;
		this->_vy = inVec3._vy;
		this->_vz = inVec3._vz;

		return *this;
	}

	const Vec3 Vec3::operator=(const Vec4& inVec4)
	{
		this->_mv = inVec4._mv;
		this->_vx = inVec4._vx;
		this->_vy = inVec4._vy;
		this->_vz = inVec4._vz;

		return *this;
	}

	// + Operator Overloader
	Vec3 Vec3::operator+(Vec3 inVec3)
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx + inVec3._vx;
		newVec3._vy = this->_vy + inVec3._vy;
		newVec3._vz = this->_vz + inVec3._vz;

		return newVec3;
	}

	// - Operator Overloader
	Vec3 Vec3::operator-(Vec3 inVec3) const
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx - inVec3._vx;
		newVec3._vy = this->_vy - inVec3._vy;
		newVec3._vz = this->_vz - inVec3._vz;

		return newVec3;
	}

	// Vec3 - Float Operator Overloader
	Vec3 Vec3::operator-(float inFloat) const
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx - inFloat;
		newVec3._vy = this->_vy - inFloat;
		newVec3._vz = this->_vz - inFloat;

		return newVec3;
	}

	// Vec3 + Float Operator Overloader
	Vec3 Vec3::operator+(float inFloat)
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx + inFloat;
		newVec3._vy = this->_vy + inFloat;
		newVec3._vz = this->_vz + inFloat;

		return newVec3;
	}

	// Float + Vec3 Operator Overloader
	Vec3 operator+(float inFloat, Vec3 inVec3)
	{
		Vec3 newVec3;

		newVec3._vx = inFloat + inVec3._vx;
		newVec3._vy = inFloat + inVec3._vy;
		newVec3._vz = inFloat + inVec3._vz;

		return newVec3;
	}

	// Float - Vec3 Operator Overloader
	Vec3 operator-(float inFloat, Vec3 inVec3)
	{
		Vec3 newVec3;

		newVec3._vx = inFloat - inVec3._vx;
		newVec3._vy = inFloat - inVec3._vy;
		newVec3._vz = inFloat - inVec3._vz;

		return newVec3;
	}

	// Vec3 * Vec3 Operator Overloader
	Vec3 Vec3::operator*(Vec3 inVec3) const
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx * inVec3._vx;
		newVec3._vy = this->_vy * inVec3._vy;
		newVec3._vz = this->_vz * inVec3._vz;

		return newVec3;
	}

	// Vec3 * Float Operator Overloader
	Vec3 Vec3::operator*(float inFloat) const
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx * inFloat;
		newVec3._vy = this->_vy * inFloat;
		newVec3._vz = this->_vz * inFloat;

		return newVec3;
	}

	Vec3 Vec3::operator*(Quat inQ) const
	{
		Vec3 newV3;
		inQ.Lqcvq(*this, newV3);
		return newV3;
	}

	const Vec3 Vec3::operator*=(float inFloat)
	{
		this->_vx *= inFloat;
		this->_vy *= inFloat;
		this->_vz *= inFloat;
		//this->_vw = 1.0f;

		return *this;
	}

	Vec3 Vec3::operator*=(Quat inQ)
	{
		Vec3 newV3;
		inQ.Lqcvq(*this, newV3);

		*this = newV3;
		return newV3;
	}

	Vec3 Vec3::operator+=(const Vec3 inVec3)
	{
		this->_vx += inVec3._vx;
		this->_vy += inVec3._vy;
		this->_vz += inVec3._vz;
		//this->_vw = 1;

		return *this;
	}

	Vec3 Vec3::operator-=(const Vec3 inVec3)
	{
		this->_vx -= inVec3._vx;
		this->_vy -= inVec3._vy;
		this->_vz -= inVec3._vz;
		//this->_vw = 1;

		return *this;
	}

	Vec3 Vec3::operator-()
	{
		Vec3 newVec3;

		newVec3._vx = -this->_vx;
		newVec3._vy = -this->_vy;
		newVec3._vz = -this->_vz;

		return newVec3;
	}

	Vec3 Vec3::operator+()
	{
		Vec3 newVec3;

		newVec3._vx = this->_vx;
		newVec3._vy = this->_vy;
		newVec3._vz = this->_vz;

		return newVec3;
	}

	// Float * Vec3 Operator Overloader
	Vec3 operator*(float inFloat, Vec3 inVec3)
	{
		Vec3 newVec3;

		newVec3._vx = inFloat * inVec3._vx;
		newVec3._vy = inFloat * inVec3._vy;
		newVec3._vz = inFloat * inVec3._vz;

		return newVec3;
	}

	//Cross Product
	Vec3 Vec3::cross(Vec3 inVec3) const
	{
		Vec3 newVec3;

		newVec3._vx = this->_vy * inVec3._vz - this->_vz * inVec3._vy;
		newVec3._vy = -(this->_vx * inVec3._vz - this->_vz * inVec3._vx);
		newVec3._vz = this->_vx * inVec3._vy - this->_vy * inVec3._vx;

		return newVec3;
	}

	//Dot Product
	float Vec3::dot(const Vec3& inVec3) const
	{
		float dotProduct;

		dotProduct = this->_vx * inVec3._vx + this->_vy * inVec3._vy + this->_vz * inVec3._vz;

		return dotProduct;
	}

	float Vec3::getAngle(Vec3 inVec3)
	{
		return acos(this->dot(inVec3) / (this->mag() * inVec3.mag()));
	}

	Vec3 Vec3::norm()
	{
		float mag;

		mag = sqrt(this->_vx * this->_vx + this->_vy * this->_vy + this->_vz * this->_vz);

		this->_vx /= mag;
		this->_vy /= mag;
		this->_vz /= mag;

		return *this;
	}

	Vec3 Vec3::getNorm()
	{
		Vec3 newVec3or = *this;
		return newVec3or.norm();
	}

	/*Vec3Proxy Vec3::mag()
	{
		return Vec3Proxy();
	}*/

	//float Vec3::mag()
	//{
	//	float val = this->_vx * this->_vx + this->_vy * this->_vy + this->_vz * this->_vz;
	//	return CDM::sqrt(val);
	//}

	Vec3Proxy Vec3::mag()
	{
		//float val = this->_vx * this->_vx + this->_vy * this->_vy + this->_vz * this->_vz;
		return Vec3Proxy(this->_vx, this->_vy, this->_vz);
		//return 1;
	}

	float Vec3::len()
	{
		return Vec3Proxy(this->_vx, this->_vy, this->_vz);
	}



	//Vec3 * Mat4 Operator Overloader
	Vec3& operator*(Vec3 v, Mat3 inMat3)
	{
		Vec3 v0;
		v0.x() = inMat3.m0();
		v0.y() = inMat3.m1();
		v0.z() = inMat3.m2();

		Vec3 v1;
		v1.x() = inMat3.m4();
		v1.y() = inMat3.m5();
		v1.z() = inMat3.m6();

		Vec3 v2;
		v2.x() = inMat3.m8();
		v2.y() = inMat3.m9();
		v2.z() = inMat3.m10();
		//Vec3 v3 = m.GetV3();

		v = Vec3(v._vx * v0._vx + v._vy * v1._vx + v._vz * v2._vx, //+ v._vw * v3._vx,
			v._vx * v0._vy + v._vy * v1._vy + v._vz * v2._vy, //+ v._vw * v3._vy,
			v._vx * v0._vz + v._vy * v1._vz + v._vz * v2._vz); //+ v._vw * v3._vz);
			//v._vx * v0._vw + v._vy * v1._vw + v._vz * v2._vw + v._vw * v3._vw);


		return  v;
	}

	Vec3 Vec3::operator*=(Mat3 inMat3)
	{
		Vec3 newVec3;

		//Vec3 v0 = inMat3.GetV0();

		Vec3 v0;
		v0.x() = inMat3.m0();
		v0.y() = inMat3.m1();
		v0.z() = inMat3.m2();

		Vec3 v1;
		v1.x() = inMat3.m4();
		v1.y() = inMat3.m5();
		v1.z() = inMat3.m6();

		Vec3 v2;
		v2.x() = inMat3.m8();
		v2.y() = inMat3.m9();
		v2.z() = inMat3.m10();

		//Vec3 v3 = inMat3.GetV3();

		newVec3._vx = this->_vx * v0._vx + this->_vy * v1._vx + this->_vz * v2._vx; //+ this->_vw * v3._vx;
		newVec3._vy = this->_vx * v0._vy + this->_vy * v1._vy + this->_vz * v2._vy; //+ this->_vw * v3._vy;
		newVec3._vz = this->_vx * v0._vz + this->_vy * v1._vz + this->_vz * v2._vz; //+ this->_vw * v3._vz;
		//newVec3._vw = this->_vx * v0._vw + this->_vy * v1._vw + this->_vz * v2._vw + this->_vw * v3._vw;

		*this = newVec3;

		return *this;
	}

	// [] x Overloader
	const float Vec3::operator[](const x_enum) const
	{
		return this->_vx;
	}

	// [] y Overloader
	const float Vec3::operator[](const y_enum) const
	{
		return this->_vy;
	}

	// [] z Overloader
	const float Vec3::operator[](const z_enum) const
	{
		return this->_vz;
	}

	// [] w Overloader
	//const float Vec3::operator[](const w_enum) const
	//{
	//	return this->_vw;
	//}

	float& Vec3::operator[](const x_enum)
	{
		return this->_vx;
	}

	float& Vec3::operator[](const y_enum)
	{
		return this->_vy;
	}

	float& Vec3::operator[](const z_enum)
	{
		return this->_vz;
	}

	//float& Vec3::operator[](const w_enum)
	//{
	//	return this->_vw;
	//}



	const float& Vec3::x() const
	{
		return this->_vx;
	}
	const float& Vec3::y() const
	{
		return this->_vy;
	}
	const float& Vec3::z() const
	{
		return this->_vz;
	}
	//const float& Vec3::w() const
	//{
	//	return this->_vw;
	//}

	float& Vec3::x()
	{
		return this->_vx;
	}

	float& Vec3::y()
	{
		return this->_vy;
	}

	float& Vec3::z()
	{
		return this->_vz;
	}

	void Vec3::x(float inX)
	{
		this->_vx = inX;
	}

	void Vec3::y(float inY)
	{
		this->_vy = inY;
	}

	void Vec3::z(float inZ)
	{
		this->_vz = inZ;
	}

	//float& Vec3::w()
	//{
	//	return this->_vw;
	//}

	bool Vec3::isEqual(Vec3 inVec3, float epsilon)
	{
		bool result = false;

		if (abs(this->_vx - inVec3._vx) < epsilon || abs(this->_vx - inVec3._vx) < epsilon)
		{
			if (abs(this->_vy - inVec3._vy) < epsilon || abs(this->_vy - inVec3._vy) < epsilon)
			{
				if (abs(this->_vz - inVec3._vz) < epsilon || abs(this->_vz - inVec3._vz) < epsilon)
				{
					result = true;
				}
			}
		}
		return result;
	}

	bool Vec3::isZero(float epsilon)
	{
		bool result = false;

		if (abs(this->_vx) <= epsilon && abs(this->_vy) <= epsilon && abs(this->_vz) <= epsilon)
		{
			result = true;
		}

		return result;
	}

	void Vec3::Print(const char *pName) const
	{
		Debug::Print(pName, *this);
	}
}

//--- End of File ---
