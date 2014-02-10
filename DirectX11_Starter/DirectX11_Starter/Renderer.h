#ifndef _RENDERER_H
#define _RENDERER_H

#include <d3d11.h>
#include <map>

#include "Mesh.h"
#include "Material.h"
#include "GameObject.h"

class Renderer {
	static std::map<std::wstring, Mesh> meshes;
	static std::map<std::wstring, Material> materials;

	Renderer();
	~Renderer();
public:
	static void Draw(GameObject* go);
	//void DrawBatched(GameObject* gos);
};

#endif // _RENDERER_H