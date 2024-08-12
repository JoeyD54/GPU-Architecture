#include "AnimMan.h"

namespace Azul
{

    AnimMan* AnimMan::posInstance = nullptr;

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    AnimMan::AnimMan(int reserveNum, int reserveGrow)
        : ManBase(reserveGrow)
    {
        // Preload the reserve
        this->proFillReservedPool(reserveNum);

        // initialize derived data here
        this->poNodeCompare = new Anim();
    }

    AnimMan::~AnimMan()
    {
        delete this->poNodeCompare;
        this->poNodeCompare = nullptr;

        // iterate through the list and delete
        Iterator* pIt = this->baseGetActiveIterator();

        DLink* pNode = pIt->First();

        // Walk through the nodes
        while (!pIt->IsDone())
        {
            Anim* pDeleteMe = (Anim*)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }

        pIt = this->baseGetReserveIterator();

        pNode = pIt->First();

        // Walk through the nodes
        while (!pIt->IsDone())
        {
            Anim* pDeleteMe = (Anim*)pIt->Curr();
            pNode = pIt->Next();
            delete pDeleteMe;
        }
    }

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
    void AnimMan::Create(int reserveNum, int reserveGrow)
    {
        // make sure values are ressonable 
        assert(reserveNum >= 0);
        assert(reserveGrow > 0);

        // initialize the singleton here
        assert(posInstance == nullptr);

        // Do the initialization
        if (posInstance == nullptr)
        {
            posInstance = new AnimMan(reserveNum, reserveGrow);
        }

    }

    void AnimMan::Destroy()
    {
        AnimMan* pMan = AnimMan::privGetInstance();
        assert(pMan != nullptr);
        AZUL_UNUSED_VAR(pMan);

        delete AnimMan::posInstance;
        AnimMan::posInstance = nullptr;
    }

    Anim* AnimMan::Add(Anim::Name _name, Clip* _pClip)
    {
        AnimMan* pMan = AnimMan::privGetInstance();

        Anim* pNode = (Anim*)pMan->baseAddToFront();
        assert(pNode != nullptr);

        // Initialize the date
        pNode->Set(_name, _pClip);

        return pNode;
    }


    Anim* AnimMan::Find(Anim::Name _name)
    {
        AnimMan* pMan = AnimMan::privGetInstance();
        assert(pMan != nullptr);

        // Compare functions only compares two Nodes

        // So:  Use the Compare Node - as a reference
        //      use in the Compare() function
        pMan->poNodeCompare->animName = _name;

        Anim* pData = (Anim*)pMan->baseFind(pMan->poNodeCompare);
        return pData;
    }


    void AnimMan::Remove(Anim* pNode)
    {
        assert(pNode != nullptr);

        AnimMan* pMan = AnimMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseRemove((DLink*)pNode);
    }

    void AnimMan::Dump()
    {
        AnimMan* pMan = AnimMan::privGetInstance();
        assert(pMan != nullptr);

        pMan->baseDump();
    }

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
    AnimMan* AnimMan::privGetInstance()
    {
        // Safety - this forces users to call Create() first before using class
        assert(posInstance != nullptr);

        return posInstance;
    }

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
    DLink* AnimMan::derivedCreateNode()
    {
        DLink* pNodeBase = new Anim();
        assert(pNodeBase != nullptr);

        return pNodeBase;
    }

}
