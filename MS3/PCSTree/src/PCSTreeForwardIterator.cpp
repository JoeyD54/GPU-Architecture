//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeForwardIterator.h"

namespace Azul
{
    PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode *rootNode)
    {
        current = rootNode;
    }

    PCSNode * PCSTreeForwardIterator::First()
    {
        if (current != nullptr)
        {
            while (current->GetReverse() != nullptr)
            {
                current = current->GetReverse();
                //go to top using reverse pointers
            }
        }
        return  current;
    }

    PCSNode * PCSTreeForwardIterator::Next()
    {
        if (current != nullptr)
        {
            current = current->GetForward();
        }
        return current;
    }

    bool PCSTreeForwardIterator::IsDone()
    {
        if (current != nullptr)
        {
            return false;
        }
        else
        {
            //current is nullptr - we are done with list cuz there is no list
            return true;
        }

    }

    PCSNode * PCSTreeForwardIterator::CurrentItem()
    {
        return  current;
    }
}
// ---  End of File ---------------
