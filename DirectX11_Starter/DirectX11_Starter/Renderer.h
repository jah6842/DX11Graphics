#ifndef _RENDERER_H
#define _RENDERER_H

#include <d3d11.h>
#include <map>
#include <vector>
#include <algorithm>

#include "GameObject.h"

class GameObject;

class Renderer {
private:
	static std::vector<GameObject*> registeredGOs;

	Renderer();
	~Renderer();
public:
	static void Draw();
	static void RegisterGameObject(GameObject* go);
	static void UnRegisterGameObject(GameObject* go);

	//void DrawBatched(GameObject* gos);
};

#endif // _RENDERER_H