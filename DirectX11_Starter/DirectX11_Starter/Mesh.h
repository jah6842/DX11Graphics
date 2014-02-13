#ifndef _MESH_H
#define _MESH_H

#include <DirectXMath.h>
#include <d3d11.h>
#include "Vertex.h"
#include "DXUtilities.h"

using namespace DirectX;

class Mesh {

public:
	// Construct a mesh without vertices
	Mesh();
	// Construct a mesh with vertices, assume clockwise indices
	Mesh(void* vertices, UINT numVertices, VERTEX_TYPE vertexType);
	// Construct a mesh with vertices, custom indices
	Mesh(void* vertices, UINT numVertices, VERTEX_TYPE vertexType, UINT* indices, UINT numIndices);
	~Mesh();

	void SetVertexBuffer(void* vertices, UINT numVertices, VERTEX_TYPE t);
	void SetIndexBuffer(UINT* indices, UINT numIndices);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topo);

	void SetInputAssemblerOptions();

	UINT IndexCount();
	UINT VertexCount();
	VERTEX_TYPE VertexType();
	ID3D11Buffer* VertexBuffer();
	ID3D11Buffer* IndexBuffer();
	D3D_PRIMITIVE_TOPOLOGY Topology();

private:
	ID3D11Buffer* _vertexBuffer;
	UINT _numVertices;
	VERTEX_TYPE _vertexType;
	ID3D11Buffer* _indexBuffer;
	UINT _numIndices;

	// How is the data laid out? 
	D3D_PRIMITIVE_TOPOLOGY topology; // default is D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST 
};


#endif // _MESH_H