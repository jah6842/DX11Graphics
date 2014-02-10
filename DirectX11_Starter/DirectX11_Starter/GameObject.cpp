#include "GameObject.h"

GameObject::GameObject(){
	//mesh = L"";
	//material = L"mat_Default";

	material = new Material();

	// Set up the vertices
	XMFLOAT4 red	= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green	= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue	= XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	Vertex vertices[] = 
	{
		{ XMFLOAT3(+0.0f, +1.5f, +0.0f), red },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), green },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
	};
	UINT indices[] = { 0, 2, 1 };
	mesh = new Mesh(vertices, indices);
};

void GameObject::Update(float dt){
	//transform.position.z += .0001f;
	transform.rotation.z += XMConvertToRadians(360.0f) * dt;

	material->SetBufferData(transform.ModelMatrix(),
		Camera::MainCamera.GetViewMatrix(),
		Camera::MainCamera.GetProjectionMatrix());

};

void GameObject::Render(){
	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Set mesh-related buffers in the input assembler
	mesh->SetInputAssemblerOptions();

	// Set material-related buffers in the input assembler
	material->SetInputAssemblerOptions();

	// Finally do the actual drawing
	deviceContext->DrawIndexed(
		3,	// The number of indices we're using in this draw
		0,
		0);
};

/*
GameObject::GameObject(std::wstring meshName){
	mesh = meshName;
};
*/

GameObject::~GameObject(){
	if(mesh != nullptr)
		delete mesh;
	if(material != nullptr)
		delete material;
};

/*
// Get and Set
void GameObject::Mesh(std::wstring meshName){
	mesh = meshName;
};
void GameObject::Material(std::wstring matName){
	material = matName;
};

std::wstring GameObject::Mesh(){
	return mesh;
};
std::wstring GameObject::Material(){
	return material;
};
*/