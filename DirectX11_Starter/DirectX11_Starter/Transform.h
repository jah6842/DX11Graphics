#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform {
public:
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	XMFLOAT4X4 ModelMatrix(){
		XMFLOAT4X4 modelMatrix;
		XMStoreFloat4x4(&modelMatrix, XMMatrixTranspose(XMMatrixIdentity()));
	};

};

#endif // _TRANSFORM_H