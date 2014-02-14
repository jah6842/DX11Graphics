#include "Mesh.h"

std::map<std::wstring, Mesh*> Mesh::meshes;

void Mesh::Cleanup(){
	typedef std::map<std::wstring, Mesh*>::iterator meshItr;
	for(meshItr iterator = meshes.begin(); iterator != meshes.end(); iterator++) {
		//iterator->second->~Mesh();
		delete iterator->second;
		iterator->second = nullptr;
		std::wcout << L"Released: " << iterator->first.c_str() << std::endl;
	}

};

// Construct a mesh without vertices
Mesh::Mesh(){
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

Mesh* Mesh::GetMesh(std::wstring meshName){
	if(meshes.count(meshName)){
		return meshes[meshName];
	}

	return new Mesh(meshName);
};

// Construct a mesh by name
Mesh::Mesh(std::wstring meshName){
	// Check if the mesh already exists
	
	if(meshes.count(meshName)){
		_vertexBuffer = meshes[meshName]->_vertexBuffer;
		_numVertices = meshes[meshName]->VertexCount();
		_vertexType = meshes[meshName]->VertexType();
		_indexBuffer = meshes[meshName]->IndexBuffer();
		_numIndices = meshes[meshName]->IndexCount();
		topology = meshes[meshName]->Topology();
		return;
	}
	std::wcout << "Continued" << std::endl;
	
	if(meshName == L"StandardCube")
	{
		ConstructMesh(L"StandardCube", StandardCubeVertices, 24, VERTEX_TYPE_POS_UV, StandardCubeIndices, 36);
		meshes[L"StandardCube"] = this;
	}

};

// Construct a mesh with vertices, assume clockwise indices
void Mesh::ConstructMesh(std::wstring meshName, void* vertices, UINT numVertices, VERTEX_TYPE vertexType){
	_vertexType = vertexType;
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices, numVertices, vertexType);
};

// Construct a mesh with vertices, custom indices
void Mesh::ConstructMesh(std::wstring meshName, void* vertices, UINT numVertices, VERTEX_TYPE vertexType, UINT* indices, UINT numIndices){
	_vertexType = vertexType;
	topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	SetVertexBuffer(vertices, numVertices, _vertexType);
	SetIndexBuffer(indices, numIndices);
};

void Mesh::CreateMeshFromModel(std::wstring modelName){

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

UINT Mesh::IndexCount(){
	return _numIndices;
};

UINT Mesh::VertexCount(){
	return _numVertices;
};

VERTEX_TYPE Mesh::VertexType(){
	return _vertexType;
};

ID3D11Buffer* Mesh::VertexBuffer(){
	return _vertexBuffer;
};

ID3D11Buffer* Mesh::IndexBuffer(){
	return _indexBuffer;
};

D3D_PRIMITIVE_TOPOLOGY Mesh::Topology(){
	return topology;
};

Mesh::~Mesh(){
	std::wcout << "Mesh destroyed" << std::endl;
	ReleaseMacro(_vertexBuffer);
	ReleaseMacro(_indexBuffer);
};
