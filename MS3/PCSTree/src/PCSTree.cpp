//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{

	// constructor
	PCSTree::PCSTree()
	{
		this->pRoot = nullptr;

		this->mInfo.currNumLevels = 0;
		this->mInfo.currNumNodes = 0;
		this->mInfo.maxNumLevels = 0;
		this->mInfo.maxNumNodes = 0;
	};

	// destructor
	PCSTree::~PCSTree()
	{
	};


	// get Root
	PCSNode* PCSTree::GetRoot() const
	{
		return (PCSNode*)this->pRoot;
	}


	// insert
	void PCSTree::Insert(PCSNode* const pInNode, PCSNode* const pParent)
	{	
		if (pInNode != nullptr)
		{
			//Insert node as head child of parent.
			if (pParent == nullptr)
			{
				this->pRoot = pInNode;
				this->IncrementLevelInfo();
			}
			else
			{
				//Parent is at our current max. Add to level count.
				if (pParent->GetTreeLevel() == this->mInfo.maxNumLevels)
				{
					this->IncrementLevelInfo();
				}

				//No children
				if (pParent->GetChild() == nullptr)
				{
					pParent->SetChild(pInNode);
					pInNode->SetParent(pParent);

					pParent->SetForward(pInNode);
					pInNode->SetReverse(pParent);

					pInNode->SetForward(nullptr);

					if (pParent->GetNextSibling() != nullptr) //if parent has a sibling 
					{
						pInNode->SetForward(pParent->GetNextSibling());
						pParent->GetNextSibling()->SetReverse(pInNode);
					}
					else
					{
						//walk up tree to find path if possible
						PCSNode* pWalk = pParent;
						while (pWalk != this->pRoot)
						{
							if (pWalk->GetNextSibling() != nullptr)
							{
								//if we find a sibling then it's the next in the list
								pInNode->SetForward(pWalk->GetNextSibling());
								pWalk->GetNextSibling()->SetReverse(pInNode);
								break;
							}
							else
							{
								pWalk = pWalk->GetParent();
							}
						}
					}
				}
				//got children
				else
				{
					pInNode->SetNextSibling(pParent->GetChild());
					pInNode->SetParent(pParent);
					pInNode->SetReverse(pParent);
					pInNode->SetForward(pParent->GetChild());
					
					pParent->GetChild()->SetPrevSibling(pInNode);
					pParent->GetChild()->SetReverse(pInNode);
					pParent->SetChild(pInNode);
					pParent->SetForward(pInNode);					
				}
			}
			pInNode->SetTreeLevel(this->mInfo.currNumLevels);
			this->IncrementNodeInfo();
		}
	}

	/// <summary>
	/// Step through the entire tree and find the lowest level throughout the tree. 
	/// Used to update our current max tree counter
	/// </summary>
	/// <returns></returns>
	void PCSTree::SetLowestLevel(PCSNode* const pInNode)
	{		
		if (pInNode->GetChild() != nullptr)
		{
			//Get curr nodes child.
			PCSNode * childNode = pInNode->GetChild();
			while (childNode != nullptr)
			{
				//Loop through all children
				if (childNode->GetChild() != nullptr)
				{
					this->SetLowestLevel(childNode);
				}
				else
				{
					//We are lower than what info is set to
					if (childNode->GetTreeLevel() > this->mInfo.currNumLevels)
					{
						Trace::out2("new level set to: %d\n", childNode->GetTreeLevel());
						this->mInfo.currNumLevels = pInNode->GetTreeLevel();
					}
				}
				

				childNode = childNode->GetNextSibling();				
			}
		}
		//no children in node
		else
		{
			//We are lower than what info is set to
			if (pInNode->GetTreeLevel() > this->mInfo.currNumLevels)
			{
				Trace::out2("new level set to: %d", pInNode->GetTreeLevel());
				this->mInfo.currNumLevels = pInNode->GetTreeLevel();
			}

			//If we're the root. We know it's being deleted
			if (pInNode->GetTreeLevel() == 1)
			{
				Trace::out2("new level set to: %d", pInNode->GetTreeLevel()-1);
				this->mInfo.currNumLevels = pInNode->GetTreeLevel()-1;
			}
		}
	}

	void PCSTree::CountTreeLevel(PCSNode* root)
	{
		if (root == nullptr)
		{
			this->mInfo.currNumLevels = 0; //no tree
		}
		else
		{
			//start the recursive call with the child
			this->mInfo.currNumLevels = RecursiveCount(root->GetChild());
		}

		//max checks to update
		if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes)
		{
			this->mInfo.maxNumNodes = this->mInfo.currNumNodes;
		}
		if (this->mInfo.currNumLevels > this->mInfo.maxNumLevels)
		{
			this->mInfo.maxNumLevels = this->mInfo.currNumLevels;
		}

	}
	//helper function to recursively count the levels of the PCStree
	int PCSTree::RecursiveCount(PCSNode* const pInNode)
	{

		if (pInNode == nullptr)
		{
			return 1; //no need to count more, there is only a root - so only 1 level
		}

		//set three different integers 
		int sibCount = 0;        //this counts the sibling's level
		int childCount = 0;        //this counts the child's level
		int currentCount = 0;    //this is the current level

		//recursive calls
		if (pInNode->GetChild() != nullptr)
		{
			//this will give the largest level count in the childrens branches
			childCount = RecursiveCount(pInNode->GetChild());
		}

		if (pInNode->GetNextSibling() != nullptr)
		{
			//this will give the largest level count in the siblings branches
			sibCount = RecursiveCount(pInNode->GetNextSibling());
		}

		//now count our level by walking to the root
		PCSNode* pWalk = pInNode;
		while (pWalk != nullptr)
		{
			currentCount++; //increment every level
			pWalk = pWalk->GetParent();
		}

		//now we just compare to get the biggest of the three
		if (childCount >= sibCount)
		{
			sibCount = childCount;
		} //if not - then sibling count is larger
		if (sibCount > currentCount)
		{
			currentCount = sibCount;
		} //if not - then current is larger than both sib and child count

		//return the largest count
		return currentCount;
	}


	// Remove
	void PCSTree::Remove(PCSNode* const pInNode)
	{
		assert(pInNode != nullptr);

		PCSNode* const pWalk1 = pInNode->GetChild(); //can be nullptr

		if (pWalk1 != nullptr) //if not at end of children
		{
			pInNode->SetForward(nullptr); //forward can no longer be it's child

			//walk up tree to find path if possible
			PCSNode* pWalk2 = pInNode;
			while (pWalk2 != this->pRoot)
			{
				if (pWalk2->GetNextSibling() != nullptr)
				{
					//if we find a sibling then it's the next in the list
					pInNode->SetForward(pWalk2->GetNextSibling());
					pWalk2->GetNextSibling()->SetReverse(pInNode);
					break;
				}
				else
				{
					pWalk2 = pWalk2->GetParent();
				}
			}

			//start the recursive call to remove children
			RemoveRecursive(pWalk1);
		}

		//update info
		this->mInfo.currNumNodes--;

		//update the current tree root if the node to remove is the tree root
		if (pInNode == this->pRoot)
		{
			this->pRoot = nullptr;
		}

		//pointers time
		if (pInNode->GetParent() != nullptr) //if we have a parent
		{
			//FIRST CHILD
			if (pInNode->GetParent()->GetChild() == pInNode)
			{
				if (pInNode->GetNextSibling() != nullptr) //child has sibling
				{
					pInNode->GetParent()->SetChild(pInNode->GetNextSibling()); //update the new list head
					pInNode->GetNextSibling()->SetPrevSibling(nullptr); //new head prev is null
				}
				else //first and only child
				{
					pInNode->GetParent()->SetChild(nullptr); //there is no sibling to set
				}
			}

			//MIDDLE CHILD
			if (pInNode->GetPrevSibling() != nullptr && pInNode->GetNextSibling() != nullptr) //we are a middle child
			{

				//fix pointers
				pInNode->GetPrevSibling()->SetNextSibling(pInNode->GetNextSibling());   //set the prev's next as the current's next
				pInNode->GetNextSibling()->SetPrevSibling(pInNode->GetPrevSibling());	//set the next's prev as the current prev
			}

			//BABY OF THE FAMILY
			if (pInNode->GetPrevSibling() != nullptr && pInNode->GetNextSibling() == nullptr)
			{

				//fix pointers
				pInNode->GetPrevSibling()->SetNextSibling(nullptr);   //set the prev's next as nullptr - they are now the end of the list
			}
		}


		//set iterators
		if (pInNode->GetReverse() != nullptr)
		{
			pInNode->GetReverse()->SetForward(pInNode->GetForward());
		}
		if (pInNode->GetForward() != nullptr) //cant set a nullptr's reverse
		{
			pInNode->GetForward()->SetReverse(pInNode->GetReverse());
		}

		pInNode->~PCSNode();		 //"delete" the current node
		CountTreeLevel(this->pRoot); //update any levels
	}


	//helper function to recursively remove the PCSNode from the PCStree
	void PCSTree::RemoveRecursive(PCSNode* const pInNode)
	{
		//recursive calls
		if (pInNode->GetChild() != nullptr)
		{
			//will remove the child node
			RemoveRecursive(pInNode->GetChild());
		}
		if (pInNode->GetNextSibling() != nullptr)
		{
			//will remove the sibling node
			RemoveRecursive(pInNode->GetNextSibling());
		}

		//update info and "delete" node
		this->mInfo.currNumNodes--;
		pInNode->~PCSNode();

	}


	// get tree info
	void PCSTree::GetInfo(Info& info)
	{
		info = this->mInfo;
	}

	void PCSTree::IncrementNodeInfo()
	{
		this->mInfo.currNumNodes++;

		//Update max if needed
		if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes)
		{
			this->mInfo.maxNumNodes = this->mInfo.currNumNodes;
		}
	}

	void PCSTree::SetTreeLevel(int inTreeLevel)
	{
		this->mInfo.currNumLevels = inTreeLevel;
	}

	void PCSTree::IncrementLevelInfo()
	{
		this->mInfo.currNumLevels++;

		//Update max if needed
		if (this->mInfo.currNumLevels > this->mInfo.maxNumLevels)
		{
			this->mInfo.maxNumLevels = this->mInfo.currNumLevels;
		}
	}
	
	void PCSTree::DecrementNodeInfo()
	{
		this->mInfo.currNumNodes--;
	}
	
	void PCSTree::DecrementLevelInfo()
	{
		this->mInfo.currNumLevels--;
	}

	void PCSTree::Print() const
	{
		//Print entire tree starting at root
		PCSNode* rootNode = this->GetRoot();

		//Print root
		rootNode->PrintNode();

		if (rootNode->GetChild() != nullptr)
		{
			//Print everything beneath the root.
			this->PrintAll(rootNode);
		}

	}

	void PCSTree::PrintAll(PCSNode * inNode) const
	{
		inNode->PrintChildren();

		PCSNode * siblingNode = inNode->GetChild();

		while (siblingNode != nullptr)
		{
			//Print everything beneath this node.
			this->PrintAll(siblingNode);		

			//Next sibling
			siblingNode = siblingNode->GetNextSibling();
		}		
	}

}

// ---  End of File ---
