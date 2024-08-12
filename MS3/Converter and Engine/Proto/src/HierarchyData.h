//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef HIERACRCHY_DATA_H
#define HIERACRCHY_DATA_H

#include "HierarchyData.pb.h"

namespace Azul
{
	class HierarchyData
	{
	public:
		HierarchyData();
		HierarchyData(const HierarchyData &) = delete;
		HierarchyData &operator = (const HierarchyData &);
		~HierarchyData();

		HierarchyData(unsigned int _numNodes, unsigned int _maxDepth);

		// Serialization 
		void Serialize(HierarchyData_proto &out) const;
		void Deserialize(const HierarchyData_proto &in);

		void Print(const char *const pName) const;

	public:
		unsigned int numNodes;
		unsigned int maxDepth;
		unsigned int *poData;
	};

}

#endif

// --- End of File ---
