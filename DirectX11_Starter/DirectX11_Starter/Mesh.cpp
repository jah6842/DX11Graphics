#include "Mesh.h"

// Construct a mesh without vertices
Mesh::Mesh(ID3D11Device* device){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetDevice(device);
};

// Construct a mesh with vertices, assume clockwise indices
Mesh::Mesh(ID3D11Device* device, Vertex* vertices){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetDevice(device);
	SetVertexBuffer(vertices);
};

// Construct a mesh with vertices, custom indices
Mesh::Mesh(ID3D11Device* device, Vertex* vertices, UINT* indices){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetDevice(device);
	SetVertexBuffer(vertices);
	SetIndexBuffer(indices);
};

void Mesh::SetDevice(ID3D11Device* dev){
	device = dev;
};


void Mesh::SetVertexBuffer(Vertex* vertices){
	// Create the vertex buffer
	D3D11_BUFFER_DESC vbd;
    vbd.Usage					= D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth				= sizeof(Vertex) * 3; // Number of vertices
    vbd.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags			= 0;
    vbd.MiscFlags				= 0;
	vbd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialVertexData;
    initialVertexData.pSysMem	= vertices;
    HR(device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer));
};

void Mesh::SetIndexBuffer(UINT* indices){
	// Create the index buffer
	D3D11_BUFFER_DESC ibd;
    ibd.Usage					= D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth				= sizeof(UINT) * 3; // Number of indices
    ibd.BindFlags				= D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags			= 0;
    ibd.MiscFlags				= 0;
	ibd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialIndexData;
    initialIndexData.pSysMem	= indices;
    HR(device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer));
};

void Mesh::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topo){
	topology = topo;
};

void Mesh::SetInputAssemblerOptions(ID3D11DeviceContext* deviceContext){
	// Set buffers in the input assembler
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(topology);
};

Mesh::~Mesh(){
	ReleaseMacro(vertexBuffer);
	ReleaseMacro(indexBuffer);
};