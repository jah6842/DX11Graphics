#ifndef _VERTEX_H
#define _VERTEX_H

#include <DirectXMath.h>
#include <d3d11.h>

using namespace DirectX;

// Vertex struct for triangles
struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, float u, float v) : pos(x,y,z), texCoord(u, v){}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

#endif // _VERTEX_H