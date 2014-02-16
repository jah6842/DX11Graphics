#pragma once

#include <vector>
#include <DirectXMath.h>
#include <random>
#include "DXGame.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer.h"
#include <vld.h>

// Include run-time memory checking in debug builds
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// For DirectX Math
using namespace DirectX;

// Demo class which extends the base DXGame class
class DemoGame : public DXGame
{
public:
	DemoGame(HINSTANCE hInstance);
	~DemoGame();

	// Overrides for base level methods
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 

	// For handing mouse input
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	void OnMouseScroll(WPARAM whlState, int delta);

private:
	//GameObject* gameGO;
	static const int NUM_GO = 15;
	std::vector<GameObject*> gameobjects;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;
	POINT prevMouseScroll;
};