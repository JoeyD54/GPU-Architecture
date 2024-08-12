//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "MathEngine.h"

namespace Azul
{
	class Sphere : public Align16
	{
	public:
		Sphere();
		Sphere(const Sphere &) = default;
		Sphere &operator = (const Sphere &) = default;
		~Sphere() = default;

		void RitterSphere(Vec3 *pt, int numPts);

		// Data: ---------------------------------
		Vec3 cntr;
		float rad;
		float pad[3];  // love and hate this new compiler

	private:
		void privMostSeparatedPointsOnAABB(int &min, int &max, Vec3 *pt, int numPts);
		void privSphereFromDistantPoints(Vec3 *pt, int numPts);
		void privSphereOfSphereAndPt(Vec3 &p);
	};

	void RitterSphere(Sphere &s, Vec3 *pt, int numPts);
}

#endif

// --- End of File ---
