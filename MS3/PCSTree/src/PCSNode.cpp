//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{
	// constructor
	PCSNode::PCSNode()
	{
		this->pChild = nullptr;
		this->pParent = nullptr;

		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;

		this->pForward = nullptr;
		this->pReverse = nullptr;
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode & in)
	{
		this->pChild = in.pChild;
		this->pParent = in.pParent;

		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;

		this->pForward = in.pForward;
		this->pReverse = in.pReverse;

		memcpy(this->pName, in.pName, this->NAME_SIZE);
		this->pName[this->NAME_SIZE - 1] = '\0';
	}

	// Specialize Constructor
	PCSNode::PCSNode(PCSNode * const pInParent, PCSNode * const pInChild, PCSNode * const pInNextSibling, PCSNode * const pInPrevSibling, const char * const pInName)
	{
		this->pParent = pInParent;
		this->pChild = pInChild;
		this->pNextSibling = pInNextSibling;
		this->pPrevSibling = pInPrevSibling;

		this->pForward = nullptr;
		this->pReverse = nullptr;

		memcpy(this->pName, pInName, this->NAME_SIZE);
		this->pName[this->NAME_SIZE - 1] = '\0';
	}

	PCSNode::PCSNode(const char * const pInName)
	{
		this->pChild = nullptr;
		this->pParent = nullptr;

		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;

		this->pForward = nullptr;
		this->pReverse = nullptr;

		memcpy(this->pName, pInName, this->NAME_SIZE);
		this->pName[this->NAME_SIZE - 1] = '\0';
	}

	// destructor
	PCSNode::~PCSNode()
	{
		//Will need to update pointers when deleting?
		this->pParent = nullptr;
		this->pChild = nullptr;
		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;
		this->pForward = nullptr;
		this->pReverse = nullptr;

	}

	// assignment operator
	PCSNode & PCSNode::operator = (const PCSNode & in)
	{
		this->pChild = in.pChild;
		this->pParent = in.pParent;

		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;

		this->pForward = in.pForward;
		this->pReverse = in.pReverse;

		memcpy(this->pName, in.pName, this->NAME_SIZE);
		this->pName[this->NAME_SIZE - 1] = '\0';

		return *this;
	}

	void PCSNode::SetParent(PCSNode * const pIn)
	{
		this->pParent = pIn;
	}

	void PCSNode::ClearParent()
	{
		this->pParent = nullptr;
	}

	void PCSNode::SetChild(PCSNode * const pIn)
	{
		this->pChild = pIn;
		////Set to child if null
		//if (this->pChild == nullptr)
		//{
		//	this->pChild = pIn;
		//}
		////Otherwise, Update current child pointer and set incoming to new child
		//else
		//{
		//	if (pIn == nullptr)
		//	{
		//		this->pChild = pIn;
		//	}
		//	else
		//	{
		//		this->pChild->SetPrevSibling(pIn);
		//		pIn->SetNextSibling(this->pChild);
		//		this->pChild = pIn;
		//	}

		//}
	}

	//Used primarily for deletions
	void PCSNode::SetToNextChild()
	{
		this->pChild = this->pChild->GetNextSibling();
	}

	void PCSNode::ClearChild()
	{
		this->pChild = nullptr;
	}

	void PCSNode::SetNextSibling(PCSNode * const pIn)
	{
		this->pNextSibling = pIn;
	}

	void PCSNode::ClearNextSibling()
	{
		this->pNextSibling = nullptr;
	}

	void PCSNode::SetPrevSibling(PCSNode * const pIn)
	{
		this->pPrevSibling = pIn;
	}

	void PCSNode::ClearPrevSibling()
	{
		this->pPrevSibling = nullptr;
	}

	void PCSNode::SetTreeLevel(int inTreeLevel)
	{
		this->treeLevel = inTreeLevel;
	}

	int PCSNode::GetTreeLevel()
	{
		return this->treeLevel;
	}

	PCSNode * PCSNode::GetParent(void) const
	{
		return (PCSNode*)this->pParent;
	}

	PCSNode * PCSNode::GetChild(void) const
	{
		return (PCSNode*)this->pChild;
	}

	PCSNode * PCSNode::GetNextSibling(void) const
	{
		return (PCSNode*)this->pNextSibling;
	}

	PCSNode * PCSNode::GetPrevSibling(void) const
	{
		return (PCSNode*)this->pPrevSibling;
	}

	PCSNode* PCSNode::GetForward(void) const
	{
		return this->pForward;
	}

	PCSNode* PCSNode::GetReverse(void) const
	{
		return this->pReverse;
	}

	void PCSNode::SetForward(PCSNode* const pIn)
	{
		this->pForward = pIn;
	}

	void PCSNode::SetReverse(PCSNode* const pIn)
	{
		this->pReverse = pIn;
	}

	PCSNode::Code PCSNode::SetName(const char * const pInName)
	{
		Code RC = Code::FAIL_RETURN_NOT_INITIALIZED;

		if (pInName == nullptr)
		{
			RC = Code::FAIL_NULL_PTR;
		}
		else
		{
			//if (strlen(pInName) < this->NAME_SIZE)
			memcpy(this->pName, pInName, this->NAME_SIZE);
			this->pName[this->NAME_SIZE - 1] = '\0';
			RC = Code::SUCCESS;
		}
		return RC;
	}

	PCSNode::Code PCSNode::GetName(char * const pOutBuffer, unsigned int sizeOutBuffer) const
	{		
		//unsigned int outBufferSize = sizeOutBuffer;
		Code RC = Code::FAIL_RETURN_NOT_INITIALIZED;

		if (pOutBuffer == nullptr)
		{
			RC = Code::FAIL_NULL_PTR;
		}
		else
		{
			memcpy(pOutBuffer, this->pName, sizeOutBuffer);
			pOutBuffer[sizeOutBuffer - 1] = '\0';
			RC = Code::SUCCESS;
		}
		return (Code) RC;
	}

	char PCSNode::GetName()
	{
		return *this->pName;
	}

	void PCSNode::PrintNode() const
	{
		Trace::out2("       name: %s\n", this->pName);
		Trace::out2("       addr: 0x%p\n", this);

		if (this->pParent != nullptr)
		{
			Trace::out2("     parent: %s (0x%p)\n", this->pParent->pName, this->pParent);
		}
		else
		{
			Trace::out2("     parent: null (0x%p)\n", this->pParent);
		}

		if (this->pChild != nullptr)
		{
			Trace::out2("      child: %s (0x%p)\n", this->pChild->pName, this->pChild);
			
		}
		else
		{
			Trace::out2("      child: null (0x%p)\n", this->pChild);
		}

		if (this->pNextSibling != nullptr)
		{
			Trace::out2("nextSibling: %s (0x%p)\n", this->pNextSibling->pName, this->pNextSibling);
		}
		else
		{
			Trace::out2("nextSibling: null (0x%p)\n", this->pNextSibling);
		}
		
		if (this->pPrevSibling != nullptr)
		{
			Trace::out2("prevSibling: %s (0x%p)\n", this->pPrevSibling->pName, this->pPrevSibling);
		}
		else
		{
			Trace::out2("prevSibling: null (0x%p)\n", this->pPrevSibling);
		}

		if (this->GetForward() != nullptr)
		{
			Trace::out2("pForward: %s (%p)\n", this->GetForward()->pName, this->GetForward());
		}
		else
		{
			Trace::out2("pForward: NULL\n");
		}
		if (this->GetReverse() != nullptr)
		{
			Trace::out2("pReverse: %s (%p)\n", this->GetReverse()->pName, this->GetReverse());
		}
		else
		{
			Trace::out2("pReverse: NULL\n");
		}

		Trace::out2("\n");
	}

	void PCSNode::PrintChildren() const
	{
		Trace::out2("%s's Children. Level in tree: %d\n", this->pName, this->treeLevel);
		Trace::out2("---------------------------------\n");

		if (this->GetChild() != nullptr)
		{
			PCSNode * childNode = this->GetChild();
			while (childNode != nullptr)
			{
				childNode->PrintNode();
				childNode = childNode->pNextSibling;
			}
		}
	}

	void PCSNode::PrintSiblings() const
	{
		Trace::out2("\n%s's Siblings. Level in tree: %d\n", this->pName, this->treeLevel);
		Trace::out2("---------------------------------\n");

		//Get to start of list
		if (this->pParent != nullptr)
		{
			//Parent's child will always look at fist in list
			PCSNode * tempNode = this->pParent->pChild;
			while (tempNode != nullptr)
			{
				if (tempNode != this)
				{
					tempNode->PrintNode();
				}
				tempNode = tempNode->GetNextSibling();
			}
		}

	}

	int PCSNode::GetNumSiblings() const
	{
		//Count the siblings. Including current node? why?
		int nodeCount = 1;

		PCSNode tempNode = *this;
		

		//Look left
		while (tempNode.pPrevSibling != nullptr)
		{
			tempNode = *tempNode.GetPrevSibling();
			nodeCount++;
		}

		//Reset node
		tempNode = *this;

		//Look right
		while (tempNode.pNextSibling != nullptr)
		{
			tempNode = *tempNode.GetNextSibling();
			nodeCount++;
		}

		return nodeCount;
	}

	//Get number of all children (and children's children?)
	int PCSNode::GetNumChildren() const
	{
		int childCount = 0;

		//Store child for count check
		if (this->pChild != nullptr)
		{
			PCSNode tempNode = *this->GetChild();
			//We found the other sibling nodes
			childCount += tempNode.GetNumSiblings();
		}

		return childCount;
	}
}

// ---  End of File ---
