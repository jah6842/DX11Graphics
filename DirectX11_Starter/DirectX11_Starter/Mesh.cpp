#include "Mesh.h"

// Construct a mesh without vertices
Mesh::Mesh(){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

// Construct a mesh with vertices, assume clockwise indices
Mesh::Mesh(void* vertices, UINT numVertices, VERTEX_TYPE vertexType){
	_vertexType = vertexType;
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices, numVertices, vertexType);
};

// Construct a mesh with vertices, custom indices
Mesh::Mesh(void* vertices, UINT numVertices, VERTEX_TYPE vertexType, UINT* indices, UINT numIndices){
	_vertexType = vertexType;
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices, numVertices, _vertexType);
	SetIndexBuffer(indices, numIndices);
};

void Mesh::SetVertexBuffer(void* vertices, UINT numVertices, VERTEX_TYPE vertexType){
	// Set the vertex count
	_numVertices = numVertices;

	// Get the curent Device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Create the vertex buffer
	D3D11_BUFFER_DESC vbd;
    vbd.Usage					= D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth				= Vertex::VertexSize(vertexType) * numVertices; // Number of vertices
    vbd.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags			= 0;
    vbd.MiscFlags				= 0;
	vbd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialVertexData;
    initialVertexData.pSysMem	= vertices;
    HR(device->CreateBuffer(&vbd, &initialVertexData, &_vertexBuffer));
};

void Mesh::SetIndexBuffer(UINT* indices, UINT numIndices){
	// Set the index count
	_numIndices = numIndices;

	// Get the curent Device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Create the index buffer
	D3D11_BUFFER_DESC ibd;
    ibd.Usage					= D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth				= sizeof(UINT) * numIndices; // Number of indices
    ibd.BindFlags				= D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags			= 0;
    ibd.MiscFlags				= 0;
	ibd.StructureByteStride		= 0;
    D3D11_SUBRESOURCE_DATA initialIndexData;
    initialIndexData.pSysMem	= indices;
    HR(device->CreateBuffer(&ibd, &initialIndexData, &_indexBuffer));
};

void Mesh::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topo){
	topology = topo;
};

void Mesh::SetInputAssemblerOptions(){
	// Get the current Device Context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Set buffers in the input assembler
	UINT stride = Vertex::VertexSize(_vertexType);
	UINT offset = 0;
	// Set the current vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	// Set the current index buffer
	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the topology
	deviceContext->IASetPrimitiveTopology(topology);
};

UINT Mesh::IndexCount(){
	return _numIndices;
};

UINT Mesh::VertexCount(){
	return _numVertices;
};

Mesh::~Mesh(){
	ReleaseMacro(_vertexBuffer);
	ReleaseMacro(_indexBuffer);
};