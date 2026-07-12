#pragma once
#include <directx/d3d12.h>
#include "Sign/Math/SignMath.h"

struct VertexPosColor
{
	Sign::Vector3D Position;
	Sign::Vector3D Color;
	uint32_t FaceID;

};

//Indices
static WORD trianlgeIndices[3] = { 0,1,2 };
static WORD quadIndices[6] = { 0,1,2 , 0,2,3 };
static WORD cubeIndices[36] =
{	
	0,1,2 , 0,2,3,
	4,6,5 , 4,7,6,
	8,11,10, 8,10,9,
	12,13,14 , 12,14,15,
	16,17,18 , 16,18,19,
	20,23,22 , 20,22,21
};