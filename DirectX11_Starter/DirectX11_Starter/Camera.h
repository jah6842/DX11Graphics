#ifndef _CAMERA_H
#define _CAMERA_H

#include <DirectXMath.h>
#include <d3d11.h>
#include "Transform.h"

using namespace DirectX;

class Camera {

public:
	Camera(UINT width, UINT height, float fov = 60.0f, float nearClip = 0.1f, float farClip = 1000.0f);
	~Camera();

	void Resize(UINT width, UINT height);
	XMFLOAT4X4 GetProjectionMatrix();
	XMFLOAT4X4 GetViewMatrix();

	static Camera MainCamera;
	Transform _transform;
	
private:
	XMFLOAT4X4 _projection;
	XMFLOAT4X4 _view;

	float _nearClip;
	float _farClip;
	// Field of view (in radians)
	float _fov;
	UINT _width;
	UINT _height;

	void RecalcProjMatrix();
};

#endif // _CAMERA_H