#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <string>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"
#include "Renderer.h"

class GameObject {

public:
	Transform transform;
	Mesh* mesh;
	Material* material;

	GameObject();
	//GameObject(std::wstring meshName);
	~GameObject();

	void Update(float dt);

	// Get and Set
	//void Mesh(std::wstring meshName);
	//void Material(std::wstring matName);
	//std::wstring Mesh();
	//std::wstring Material();

private:
	//std::wstring mesh;
	//std::wstring material;
};

#endif // _GAME_OBJECT_H