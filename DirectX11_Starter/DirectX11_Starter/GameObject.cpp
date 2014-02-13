#include "GameObject.h"

GameObject::GameObject(){
	// TODO: REFER TO MESHES/MATERIALS BY THEIR NAME ONLY?
	//mesh = L"";
	//material = L"mat_Default";

	Renderer::RegisterGameObject(this);

	material = new Material(L"TexturedInstanced", 1, L"desert-texture.jpg");

	// Set up the vertices
	XMFLOAT4 red	= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green	= XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue	= XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	/* QUAD */
	/*
	if(flipFlop){
		Vertex_POS_COLOR vertices[] = 
		{
			Vertex_POS_COLOR( XMFLOAT3(-1.0f, +1.0f, +0.0f), red),
			Vertex_POS_COLOR( XMFLOAT3(+1.0f, -1.0f, +0.0f), red),
			Vertex_POS_COLOR( XMFLOAT3(-1.0f, -1.0f, +0.0f), blue),
			Vertex_POS_COLOR( XMFLOAT3(+1.0f, +1.0f, +0.0f), blue)
		};
		UINT indices[] = { 0, 1, 2, 1, 0, 3 };
		mesh = new Mesh(vertices, 4, VERTEX_TYPE_POS_COLOR, indices, 6);
		return;
	}
	*/
	
	// CUBE
	Vertex_POS_UV vertices[] =
	{
		// Front Face
		Vertex_POS_UV(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex_POS_UV(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex_POS_UV( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex_POS_UV( 1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Back Face
		Vertex_POS_UV(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
		Vertex_POS_UV( 1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		Vertex_POS_UV( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
		Vertex_POS_UV(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),
		// Top Face
		Vertex_POS_UV(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		Vertex_POS_UV(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
		Vertex_POS_UV( 1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
		Vertex_POS_UV( 1.0f, 1.0f, -1.0f, 1.0f, 1.0f),
		// Bottom Face
		Vertex_POS_UV(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		Vertex_POS_UV( 1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex_POS_UV( 1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
		Vertex_POS_UV(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),
		// Left Face
		Vertex_POS_UV(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
		Vertex_POS_UV(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
		Vertex_POS_UV(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex_POS_UV(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Right Face
		Vertex_POS_UV( 1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex_POS_UV( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex_POS_UV( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
		Vertex_POS_UV( 1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
	};
	UINT indices[] = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
		// Back Face
		4,  5,  6,
		4,  6,  7,
		// Top Face
		8,  9, 10,
		8, 10, 11,
		// Bottom Face
		12, 13, 14,
		12, 14, 15,
		// Left Face
		16, 17, 18,
		16, 18, 19,
		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	mesh = new Mesh(vertices, 24,VERTEX_TYPE_POS_UV, indices, 36);
	
};

void GameObject::Update(float dt){
	//transform.position.z += .0001f;
	transform.rotation.z += XMConvertToRadians(60.0f) * dt;
	transform.rotation.y += XMConvertToRadians(60.0f) * dt;

	//material->SetBufferData(transform.Identity().ModelMatrix(),
	//	Camera::MainCamera.GetViewMatrix(),
	//	Camera::MainCamera.GetProjectionMatrix());
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

	Renderer::UnRegisterGameObject(this);
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