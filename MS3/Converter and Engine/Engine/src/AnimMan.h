#ifndef ANIM_MAN_H
#define ANIM_MAN_H

#include "Anim.h"
#include "ManBase.h"

namespace Azul
{
	//Anim Manager is tasked with holding multiple Animations.
	//Anim Manager will also handle blending two animations together over time
	//Allows for smooth blending anim transitions
	//Might be better used in AnimController
	class AnimMan : public ManBase
	{
	public:
        static void Create(int reserveNum = 0, int reserveGrow = 1);
        static void Destroy();
        static Anim* Add(Anim::Name _name, Clip* _pClip);

        static Anim* Find(Anim::Name name);

        static void Remove(Anim* pNode);
        static void Dump();

        //----------------------------------------------------------------------
        // Private methods
        //----------------------------------------------------------------------
    private:
        static AnimMan* privGetInstance();

        AnimMan() = delete;
        AnimMan(const AnimMan&) = delete;
        AnimMan& operator=(const AnimMan&) = delete;
        virtual ~AnimMan();

        AnimMan(int reserveNum, int reserveGrow);

        //----------------------------------------------------------------------
        // Override Abstract methods
        //----------------------------------------------------------------------
    protected:
        DLink* derivedCreateNode() override;

        //----------------------------------------------------------------------
        // Data: unique data for this manager 
        //----------------------------------------------------------------------
    private:
        Anim* poNodeCompare;
        static AnimMan* posInstance;
	};
}
#endif
