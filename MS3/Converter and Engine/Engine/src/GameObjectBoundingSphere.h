//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_BOUNDING_SPHERE_H
#define GAME_OBJECT_BOUNDING_SPHERE_H

#include "MathEngine.h"
#include "GameObject.h"
#include "AnimTime.h"
#include "GameObjectRigid.h"

namespace Azul
{
	class GameObjectBoundingSphere : public GameObjectRigid
	{
	public:
		GameObjectBoundingSphere(GraphicsObject *graphicsObject);

		// Big four
		GameObjectBoundingSphere() = delete;
		GameObjectBoundingSphere(const GameObjectBoundingSphere &) = delete;
		GameObjectBoundingSphere &operator=(GameObjectBoundingSphere &) = delete;
		virtual ~GameObjectBoundingSphere();

		void SetBoundingSphereReference(GameObject *pGameObj);

		virtual void Update(AnimTime currTime) override;

	private:
		void privUpdate(AnimTime currTime);
		void privUpdateBoundingSphereReference(AnimTime currentTime);

		// Data: ------------------
		GameObject *pRefGameObj;

	public:
		Vec3 *poScale;
		Vec3 *poTrans;
	};

}

#endif

// --- End of File ---
