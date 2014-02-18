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

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0, 5);

void GameObject::Update(float dt){
	float randX, randY, randZ;
	randX = (dis(gen) - 2.5f) * dt;
	randY = (dis(gen) - 2.5f) * dt;
	randZ = (dis(gen) - 2.5f) * dt;
	transform.Move(randX, randY, randZ);
};

GameObject::~GameObject(){
	// Unregister this GameObject from the renderer
	Renderer::UnRegisterGameObject(this);
};
