#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform {
public:
	Transform();
	~Transform();

	// Getters
	XMFLOAT3 Pos();
	float PosX();
	float PosY();
	float PosZ();

	// Setters
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 pos);
	void SetRotation(float xRad, float yRad, float zRad);
	void SetRotation(XMFLOAT3 rotRad);
	void SetScale(float x, float y, float z);
	void SetScale(XMFLOAT3 sca);

	// Movement functions
	void Move(float x, float y, float z);
	void Move(XMFLOAT3 pos);

	// Rotation functions
	void Rotate(float x, float y, float z);
	void Rotate(XMFLOAT3 rotRad);
	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);

	// Returns a model matrix of the pos, rot, and scale
	XMFLOAT4X4 WorldMatrix();

	// Returns an XMVECTOR of the position, rotation, or scale. Unused 4th value is 0.
	XMVECTOR PosToVector();
	XMVECTOR RotToVector();
	XMVECTOR ScaleToVector();

	// Returns an identity transform
	// Position/rotation 0,0,0, Scale 1,1,1
	static Transform Identity();

	// Returns a world matrix of the pos, rot, and scale
	static XMFLOAT4X4 WorldMatrix(Transform t);

private:
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
};

#endif // _TRANSFORM_H