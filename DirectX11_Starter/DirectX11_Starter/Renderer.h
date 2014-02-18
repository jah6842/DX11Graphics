#ifndef _RENDERER_H
#define _RENDERER_H

#include <d3d11.h>
#include <map>
#include <unordered_set>
#include <vector>
#include <list>
#include <algorithm>

#include "GameObject.h"

class GameObject;

class Renderer {
private:
	static std::unordered_set<GameObject*> registeredGOs;

	Renderer();
	~Renderer();
public:
	static void Draw();
	static void RegisterGameObject(GameObject* go);
	static void UnRegisterGameObject(GameObject* go);
};

#endif // _RENDERER_H