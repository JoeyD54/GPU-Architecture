//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeReverseIterator.h"

namespace Azul
{
    PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode * rootNode)
    {
        current = rootNode;
    }

    PCSNode * PCSTreeReverseIterator::First()
    {
        if (current != nullptr)
        {
            while (current->GetForward() != nullptr)
            {
                current = current->GetForward();
                //go to last using forward pointers
            }
        }

        return  current;
    }

    PCSNode * PCSTreeReverseIterator::Next()
    {
        if (current != nullptr)
        {
            current = current->GetReverse();
        }
        return current;
    }

    bool PCSTreeReverseIterator::IsDone()
    {
        if (current != nullptr)
        {
            return false;
        }
        else
        {
            return true; //done with list becuase there is no list
        }
    }

    PCSNode * PCSTreeReverseIterator::CurrentItem()
    {
        return  current;
    }

}

// ---  End of File ---------------
