#include "Mesh.h"

// Construct a mesh without vertices
Mesh::Mesh(){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

// Construct a mesh with vertices, assume clockwise indices
Mesh::Mesh(Vertex* vertices){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices);
};

// Construct a mesh with vertices, custom indices
Mesh::Mesh(Vertex* vertices, UINT* indices){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices);
	SetIndexBuffer(indices);
};

void Mesh::SetVertexBuffer(Vertex* vertices){
	// Get the curent Device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

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
	// Get the curent Device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

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

void Mesh::SetInputAssemblerOptions(){
	// Get the current Device Context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Set buffers in the input assembler
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	// Set the current vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// Set the current index buffer
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the topology
	deviceContext->IASetPrimitiveTopology(topology);
};

Mesh::~Mesh(){
	ReleaseMacro(vertexBuffer);
	ReleaseMacro(indexBuffer);
};