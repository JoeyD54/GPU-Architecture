//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_H
#define PCSTREE_H

namespace Azul
{

	// forward declare
	class PCSNode;

	// PCSTree class 
	class PCSTree
	{
	public:
		// Simple data structure
		struct Info
		{
			int currNumNodes;
			int maxNumNodes;
			int currNumLevels;
			int maxNumLevels;
		};

	public:
		// constructor
		PCSTree();

		// copy constructor 
		PCSTree(const PCSTree & in) = delete;

		// assignment operator
		PCSTree & operator = (const PCSTree & in) = delete;

		// destructor
		~PCSTree();

		// get Root
		PCSNode * GetRoot() const;

		// insert
		void Insert(PCSNode * const pInNode, PCSNode * const pParent);

		int RecursiveCount(PCSNode* const pInNode);

		// remove
		void Remove(PCSNode * const pInNode);

		void RemoveRecursive(PCSNode* const pInNode);

		void SetLowestLevel(PCSNode* const pInNode);

		void CountTreeLevel(PCSNode* root);

		// get info
		void GetInfo(Info & info);

		void IncrementNodeInfo();
		void SetTreeLevel(int inTreeLevel);
		void IncrementLevelInfo();
		void DecrementNodeInfo();
		void DecrementLevelInfo();

		void Print() const;

		void PrintAll(PCSNode * inNode) const;

	private:

		// Data
		Info	mInfo;
		PCSNode * pRoot;

	};

}

#endif

// ---  End of File ---
