#include "GameObject.h"

GameObject::GameObject(std::wstring meshName){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	material = new Material(L"TexturedInstanced", 1, L"texture.png");

	// Set the mesh
	mesh = Mesh::GetMesh(meshName);
};

GameObject::GameObject(){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	material = new Material(L"TexturedInstanced", 1, L"texture.png");

	// Set the mesh
	mesh = Mesh::GetMesh(L"StandardCube");
};

void GameObject::Update(float dt){
	transform.rotation.z += XMConvertToRadians(60.0f) * dt;
	transform.rotation.y += XMConvertToRadians(60.0f) * dt;
};

GameObject::~GameObject(){
	if(material != nullptr)
		delete material;

	// Unregister this GameObject from the renderer
	Renderer::UnRegisterGameObject(this);
};
