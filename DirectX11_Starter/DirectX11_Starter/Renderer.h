#ifndef _RENDERER_H
#define _RENDERER_H

#include <d3d11.h>
#include <map>

#include "Mesh.h"
#include "Material.h"

class Renderer {
	static std::map<std::wstring, Mesh> meshes;
	static std::map<std::wstring, Material> materials;

	Renderer();
	~Renderer();
};

#endif // _RENDERER_H