#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform {
public:
	Transform();
	~Transform();

	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	// Returns a model matrix of the pos, rot, and scale
	XMFLOAT4X4 WorldMatrix();

	// Returns an identity transform
	// Position/rotation 0,0,0, Scale 1,1,1
	static Transform Identity();

	// Returns a model matrix of the pos, rot, and scale
	static XMFLOAT4X4 WorldMatrix(Transform t);
};

#endif // _TRANSFORM_H