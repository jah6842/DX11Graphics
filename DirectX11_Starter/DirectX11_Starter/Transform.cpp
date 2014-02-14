#include "Transform.h"

Transform::Transform(){
	position = XMFLOAT3(0,0,0);
	rotation = XMFLOAT3(0,0,0);
	scale    = XMFLOAT3(1,1,1);
};

Transform::~Transform(){

};

// Returns a model matrix of the pos, rot, and scale
XMFLOAT4X4 Transform::ModelMatrix(){
	XMMATRIX pos = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX sca = XMMatrixScaling(scale.x, scale.y, scale.z);
	
	XMMATRIX model = sca * rot * pos;

	XMFLOAT4X4 modelMatrix;
	XMStoreFloat4x4(&modelMatrix, XMMatrixTranspose(model));
	return modelMatrix;
};

// Returns a model matrix of the pos, rot, and scale
XMFLOAT4X4 Transform::ModelMatrix(Transform t){
	XMMATRIX pos = XMMatrixTranslation(t.position.x, t.position.y, t.position.z);
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(t.rotation.x, t.rotation.y, t.rotation.z);
	XMMATRIX sca = XMMatrixScaling(t.scale.x, t.scale.y, t.scale.z);
	
	XMMATRIX model = sca * rot * pos;

	XMFLOAT4X4 modelMatrix;
	XMStoreFloat4x4(&modelMatrix, XMMatrixTranspose(model));
	return modelMatrix;
};

// Returns an identity transform
// Position/rotation 0,0,0, Scale 1,1,1
Transform Transform::Identity(){
	Transform t;
	t.position = XMFLOAT3(0,0,0);
	t.rotation = XMFLOAT3(0,0,0);
	t.scale    = XMFLOAT3(1,1,1);
	return t;
};