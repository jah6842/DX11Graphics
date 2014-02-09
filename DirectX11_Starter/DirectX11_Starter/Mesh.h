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
	Mesh(ID3D11Device* device);
	// Construct a mesh with vertices, assume clockwise indices
	Mesh(ID3D11Device* device, Vertex* vertices);
	// Construct a mesh with vertices, custom indices
	Mesh(ID3D11Device* device, Vertex* vertices, UINT* indices);
	~Mesh();

	void SetDevice(ID3D11Device* device);
	void SetVertexBuffer(Vertex* vertices);
	void SetIndexBuffer(UINT* indices);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topo);

	void SetInputAssemblerOptions(ID3D11DeviceContext* deviceContext);

private:
	ID3D11Device* device;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	D3D_PRIMITIVE_TOPOLOGY topology; // points, lines, triangle strip, triangles, etc
};


#endif // _MESH_H