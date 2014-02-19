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

	_transform.Move(0,0,-5);

	RecalcProjMatrix();
};

Camera::~Camera(){

};

void Camera::Update(float dt){
	MainCamera.RecalcViewMatrix();
};

XMFLOAT4X4 Camera::GetProjectionMatrix(){
	return _projection;
};

XMFLOAT4X4 Camera::GetViewMatrix(){
	return _view;
};

XMFLOAT4X4 Camera::GetViewProjMatrix(){
	XMMATRIX v = XMLoadFloat4x4(&_view);
	XMMATRIX p = XMLoadFloat4x4(&_projection);

	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, (p*v));
	return viewProj;
};

void Camera::RecalcViewMatrix(){
	// Set up view matrix (camera)
	XMVECTOR position	= _transform.PosToVector();
	XMVECTOR target		= XMVectorSet(0, 0, 1, 0);
	XMVECTOR up			= XMVectorSet(0, 1, 0, 0);
	XMMATRIX V			= XMMatrixLookToLH(position, target, up);
	XMStoreFloat4x4(&_view, XMMatrixTranspose(V));

	RecalcFrustum();
};

void Camera::RecalcFrustum(){

	XMMATRIX m_view = XMLoadFloat4x4(&_view);
	XMMATRIX m_projection = XMLoadFloat4x4(&_projection);
	XMMATRIX viewProjection = XMMatrixMultiply(m_view, m_projection );

	// Left Frustum Plane
    // Add first column of the matrix to the fourth column
	_frustum[0][0] = _view._14 + _view._11; 
	_frustum[0][1] = _view._24 + _view._21;
	_frustum[0][2] = _view._34 + _view._31;
	_frustum[0][3] = _view._44 + _view._41;

	// Right Frustum Plane
    // Subtract first column of matrix from the fourth column
	_frustum[1][0] = _view._14 - _view._11; 
	_frustum[1][1] = _view._24 - _view._21;
	_frustum[1][2] = _view._34 - _view._31;
	_frustum[1][3] = _view._44 - _view._41;

	// Top Frustum Plane
    // Subtract second column of matrix from the fourth column
	_frustum[2][0] = _view._14 - _view._12; 
	_frustum[2][1] = _view._24 - _view._22;
	_frustum[2][2] = _view._34 - _view._32;
	_frustum[2][3] = _view._44 - _view._42;

	// Bottom Frustum Plane
    // Add second column of the matrix to the fourth column
	_frustum[3][0] = _view._14 + _view._12;
	_frustum[3][1] = _view._24 + _view._22;
	_frustum[3][2] = _view._34 + _view._32;
	_frustum[3][3] = _view._44 + _view._42;

	// Near Frustum Plane
    // We could add the third column to the fourth column to get the near plane,
    // but we don't have to do this because the third column IS the near plane
	_frustum[4][0] = _view._13;
	_frustum[4][1] = _view._23;
	_frustum[4][2] = _view._33;
	_frustum[4][3] = _view._43;

	// Far Frustum Plane
    // Subtract third column of matrix from the fourth column
	_frustum[5][0] = _view._14 - _view._13; 
	_frustum[5][1] = _view._24 - _view._23;
	_frustum[5][2] = _view._34 - _view._33;
	_frustum[5][3] = _view._44 - _view._43;

	for(int i = 0; i < 6; ++i)
	{
		float length = sqrt((_frustum[i][0] * _frustum[i][0]) + (_frustum[i][1] * _frustum[i][1]) + (_frustum[i][2] * _frustum[i][2]));
		_frustum[i][0] /= length;
		_frustum[i][1] /= length;
		_frustum[i][2] /= length;
		_frustum[i][3] /= length;
	}

};

bool Camera::PointInFrustum(float x, float y, float z){
	
	/*
	for(int planeID = 0; planeID < 6; ++planeID)
	{
		XMVECTOR planeNormal = XMVectorSet(_frustum[planeID][0], _frustum[planeID][1], _frustum[planeID][2], 0.0f);
		float planeConstant = _frustum[planeID][3];

		// Check each axis (x,y,z) to get the AABB vertex furthest away from the direction the plane is facing (plane normal)
		XMFLOAT3 axisVert = XMFLOAT3(x,y,z);

		// Now we get the signed distance from the AABB vertex that's furthest down the frustum planes normal,
		// and if the signed distance is negative, then the entire bounding box is behind the frustum plane, which means
		// that it should be culled
		if(XMVectorGetX(XMVector3Dot(planeNormal, XMLoadFloat3(&axisVert))) + planeConstant < 0.0f)
		{
			return false;
		}
	}

	return true;
	
	/*
	for ( int i = 0; i < 6; i++ )
    {
		XMVECTOR m_frustum = XMVectorSet(_frustum[i][0], _frustum[i][1], _frustum[i][2], _frustum[i][3]);
		XMVECTOR position = XMVectorSet(x,y,z,1.0f);
        if ( XMPlaneDotCoord( m_frustum, position ) < 0 )
        {
            // Outside the frustum, reject it!
            return FALSE;
        }
    }
	*/
	int p;
	for( p = 0; p < 6; p++ )
		if( _frustum[p][0] * x + _frustum[p][1] * y + _frustum[p][2] * z + _frustum[p][3]    <= 0 )
			return false;
	return true;
	
};

bool Camera::PointInFrustum(XMFLOAT3 position){
	return PointInFrustum(position.x, position.y, position.z);
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