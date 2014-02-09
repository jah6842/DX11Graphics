#ifndef _VERTEX_H
#define _VERTEX_H

#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

// Vertex struct for triangles
struct Vertex
{
	//XMFLOAT2 UV;
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

#endif // _VERTEX_H