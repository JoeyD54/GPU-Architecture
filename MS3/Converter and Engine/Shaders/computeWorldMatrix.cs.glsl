//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#version 430 core

// ------------------------------------------
//    Compute World Matrix
// ------------------------------------------

// localize breakdown
layout(local_size_x = 10) in;

struct Bone
{
	vec3 t;
	vec4 q;
	vec3 s;
};


layout (std430, binding = 0) buffer LocalBone
{
	Bone LocalBone_array[];
};

layout (std430, binding = 1) buffer HierarchyTable
{
	int HierarchyTable_Entry[];
};

layout (std430, binding = 2) buffer Result
{
	mat4 Result_array[];
};

layout (std430, binding = 3) buffer InvBind
{
	mat4 InvBind_array[];
};

// Uniforms
// ...

uniform int boneCount;
uniform int hierarchyDepth;

// Function
mat4 Bone2Matrix( Bone bone );
mat4 TransMatrix( vec3 trans );
mat4 ScaleMatrix( vec3 scale );
mat4 RotMatrix( vec4 quat );



void main()
{
	uint boneIndex = gl_GlobalInvocationID.x;

	if( gl_GlobalInvocationID.x < boneCount )
	{
		// identity
		mat4 tmp = mat4(1.0);

		for( int i = 0; i < hierarchyDepth; i++)
		{
		    //  parentIndex <- Table(Row + offset)
			int parentIndex = HierarchyTable_Entry[(boneIndex * hierarchyDepth) + i ];

			if(parentIndex == -1)
			{
				tmp = tmp * mat4(1.0);
			}
			else
			{
				// multiply in reverse order...
				tmp =  tmp * Bone2Matrix(LocalBone_array[parentIndex]);
			}
		}

		Result_array[boneIndex] =  tmp * InvBind_array[boneIndex];
	}
	
};


mat4  Bone2Matrix( Bone bone )
{
	mat4 mTrans = TransMatrix(bone.t);
	mat4 mScale = ScaleMatrix(bone.s);
	mat4 mRot = RotMatrix(bone.q);

	mat4 result;

	result = mTrans * mRot * mScale;

	return result;
}

mat4 TransMatrix( vec3 trans )
{
	mat4 result = mat4(1.0);
	result[3] = vec4(trans.xyz,1.0);
	return result;
}

mat4 ScaleMatrix( vec3 scale )
{
	mat4 result = mat4(1.0);
	result[0].x = scale.x;
	result[1].y = scale.y;
	result[2].z = scale.z;
	return result;
}

mat4 RotMatrix( vec4 q )
{
	mat4  result;

	float x2, y2, z2;

	x2 = 2 * q.x;
	y2 = 2 * q.y;
	z2 = 2 * q.z;

	float xx, xy, xz;
	float yy, yz, zz;
	float wx, wy, wz;

	xx = q.x * x2;
	xy = q.x * y2;
	xz = q.x * z2;

	yy = q.y * y2;
	yz = q.y * z2;
	zz = q.z * z2;

	wx = q.w * x2;
	wy = q.w * y2;
	wz = q.w * z2;

	result[0] = vec4(1.0 - (yy+zz), xy+wz, xz-wy, 0 );
	result[1] = vec4(xy-wz, 1 -(xx+zz), yz+wx, 0 );
	result[2] = vec4(xz+wy, yz-wx, 1-(xx+yy), 0 );
	result[3] = vec4(0,0,0,1);

	return result;

}

// --- End of File ---
