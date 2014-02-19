#include "GameObject.h"

GameObject::GameObject(std::wstring meshName){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	//material = Material::GetMaterial(L"TexturedInstanced", 1, L"texture.png");

	// Set the mesh
	mesh = Mesh::GetMesh(meshName);
};

GameObject::GameObject(){
	// Register the GameObject with the renderer
	Renderer::RegisterGameObject(this);

	// Set the material
	//static bool flip = false;
	//if(flip == false)
		//material =  Material::GetMaterial(L"TexturedInstanced", 1, L"texture.png");
		MATERIAL_DESCRIPTION matDesc;
		matDesc.cBufferLayout = CONSTANT_BUFFER_LAYOUT_VS_VPMATRIX;
		matDesc.diffuseTextureFilename = L"texture2.png";
		matDesc.vShaderFilename = L"TexturedInstancedVertex.cso";
		matDesc.pShaderFilename = L"TexturedInstancedPixel.cso";
		matDesc.shaderName = L"TexturedInstanced";

		material = Material::GetMaterial(matDesc);
	//else
	//	material =  Material::GetMaterial(L"TexturedInstanced", 1, L"texture2.png");
	
	//flip = !flip;
	
	// Set the mesh
	mesh = Mesh::GetMesh(L"StandardCube");
};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0, 50);

void GameObject::Update(float dt){
	float randX, randY, randZ;
	randX = (dis(gen) - 25) * dt;
	randY = (dis(gen) - 25) * dt;
	randZ = (dis(gen) - 25) * dt;
	transform.Move(randX, randY, randZ);
};

GameObject::~GameObject(){
	// Unregister this GameObject from the renderer
	Renderer::UnRegisterGameObject(this);
};
