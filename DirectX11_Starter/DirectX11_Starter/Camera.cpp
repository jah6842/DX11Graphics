#include "Camera.h"

Camera Camera::MainCamera(0,0);

Camera::Camera(UINT width,
			   UINT height,
			   float fov,
			   float nearClip,
			   float farClip ){
	_width = width;
	_height = height;
	_fov = XMConvertToRadians(fov);
	_nearClip = nearClip;
	_farClip = farClip;

	_transform.position.z = -5;

	RecalcProjMatrix();
};

Camera::~Camera(){

};

XMFLOAT4X4 Camera::GetProjectionMatrix(){
	return _projection;
};

XMFLOAT4X4 Camera::GetViewMatrix(){
	// Set up view matrix (camera)
	// In an actual game, update this when the camera moves (so every frame)
	XMVECTOR position	= XMVectorSet(_transform.position.x, _transform.position.y, _transform.position.z, 0);
	XMVECTOR target		= XMVectorSet(0, 0, 1, 0);
	XMVECTOR up			= XMVectorSet(0, 1, 0, 0);
	XMMATRIX V			= XMMatrixLookToLH(position, target, up);
	XMStoreFloat4x4(&_view, XMMatrixTranspose(V));

	return _view;
};

void Camera::RecalcProjMatrix(){
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		_fov,
		(float)_width / (float)_height,
		_nearClip,
		_farClip);
	XMStoreFloat4x4(&_projection, XMMatrixTranspose(P));
};

void Camera::Resize(UINT width, UINT height){
	_width = width;
	_height = height;
	RecalcProjMatrix();
};