#include "GameObject.h"

GameObject::GameObject(std::wstring meshName){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	material = Material::GetMaterial(L"TexturedInstanced", 1, L"texture.png");

	// Set the mesh
	mesh = Mesh::GetMesh(meshName);
};

GameObject::GameObject(){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	static UINT flip = 1;
	if(flip % 3 == 0)
		material =  Material::GetMaterial(L"TexturedInstanced", 1, L"texture.png");
	else if(flip % 2 == 0)
		material =  Material::GetMaterial(L"TexturedInstanced", 1, L"texture2.png");
	else
		material =  Material::GetMaterial(L"TexturedInstanced", 1, L"desert-texture.jpg");
	
	flip++;
	
	// Set the mesh
	mesh = Mesh::GetMesh(L"StandardCube");
};

void GameObject::Update(float dt){
	transform.rotation.z += XMConvertToRadians(60.0f) * dt;
	transform.rotation.y += XMConvertToRadians(60.0f) * dt;
};

GameObject::~GameObject(){
	// Unregister this GameObject from the renderer
	Renderer::UnRegisterGameObject(this);
};
