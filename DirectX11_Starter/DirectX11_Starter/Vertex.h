#ifndef _VERTEX_H
#define _VERTEX_H

#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

// Vertex struct for triangles
struct Vertex
{
	//Vertex(XMFLOAT3 pos, XMFLOAT4 c) : Position(pos), Color(c){}
	Vertex(float x, float y, float z, XMFLOAT4 c) : Position(x,y,z), Color(c){}

	//XMFLOAT2 UV;
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

#endif // _VERTEX_H