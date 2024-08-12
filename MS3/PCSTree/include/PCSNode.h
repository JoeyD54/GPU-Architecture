//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSNODE_H
#define PCSNODE_H

namespace Azul
{
	class PCSNode
	{
	public:
		// Constants for the library
		static const unsigned int NAME_SIZE = 32;
		static const unsigned int MAJOR_VERSION = 3;
		static const unsigned int MINOR_VERSION = 1;

	public:
		// Enums
		enum class Code : uint32_t
		{
			SUCCESS,
			FAIL_NULL_PTR,
			FAIL_RETURN_NOT_INITIALIZED
		};


	public:
		// constructor
		PCSNode();

		// copy constructor
		PCSNode(const PCSNode &in);

		// Specialize Constructor
		PCSNode(PCSNode *const pInParent,
			PCSNode *const pInChild,
			PCSNode *const pInNextSibling,
			PCSNode *const pInPrevSibling,
			const char *const pInName);

		PCSNode(const char *const pInName);

		// destructor
		virtual ~PCSNode();

		// assignment operator
		PCSNode &operator = (const PCSNode &in);

		// accessors
		void SetParent(PCSNode *const pIn);
		void ClearParent();
		void SetChild(PCSNode *const pIn);
		void SetToNextChild();
		void ClearChild();
		void SetNextSibling(PCSNode *const pIn);
		void ClearNextSibling();
		void SetPrevSibling(PCSNode *const pIn);

		void ClearPrevSibling();

		void SetTreeLevel(int treeLevel);
		int GetTreeLevel();

		PCSNode *GetParent(void) const;
		PCSNode *GetChild(void) const;
		PCSNode *GetNextSibling(void) const;
		PCSNode *GetPrevSibling(void) const;

		PCSNode* GetForward(void) const;
		PCSNode* GetReverse(void) const;

		void SetForward(PCSNode* const pIn);
		void SetReverse(PCSNode* const pIn);

		// name
		Code SetName(const char *const pInName);
		Code GetName(char *const pOutBuffer, unsigned int sizeOutBuffer) const;

		char GetName();

		// print
		void PrintNode() const;
		void PrintChildren() const;
		void PrintSiblings() const;

		// get number of children/siblings
		int GetNumSiblings() const;
		int GetNumChildren() const;

	private:
		PCSNode *pParent;
		PCSNode *pChild;
		PCSNode *pNextSibling;
		PCSNode *pPrevSibling;
		PCSNode *pForward;
		PCSNode *pReverse;

		int treeLevel;

		char     pName[PCSNode::NAME_SIZE];
	};

}

#endif

// ---  End of File ---
