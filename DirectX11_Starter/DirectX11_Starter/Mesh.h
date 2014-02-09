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
	Mesh(Vertex* vertices);
	// Construct a mesh with vertices, custom indices
	Mesh(Vertex* vertices, UINT* indices);
	~Mesh();

	void SetVertexBuffer(Vertex* vertices);
	void SetIndexBuffer(UINT* indices);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topo);

	void SetInputAssemblerOptions();

private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// How is the data laid out? 
	D3D_PRIMITIVE_TOPOLOGY topology; // default is D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST 
};


#endif // _MESH_H