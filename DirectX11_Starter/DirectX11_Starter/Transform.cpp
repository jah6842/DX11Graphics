#include "Transform.h"

Transform::Transform(){
	position = XMFLOAT3(0,0,0);
	rotation = XMFLOAT3(0,0,0);
	scale    = XMFLOAT3(1,1,1);
};

Transform::~Transform(){

};

// Getters
XMFLOAT3 Transform::Pos(){
	return position;
};
float Transform::PosX(){
	return position.x;
};
float Transform::PosY(){
	return position.y;
};
float Transform::PosZ(){
	return position.z;
};

// Setters
void Transform::SetPosition(float x, float y, float z){
	position = XMFLOAT3(x,y,z);
};
void Transform::SetPosition(XMFLOAT3 pos){
	position = pos;
};
void Transform::SetRotation(float xRad, float yRad, float zRad){
	rotation = XMFLOAT3(xRad, yRad, zRad);
};
void Transform::SetRotation(XMFLOAT3 rotRad){
	rotation = rotRad;
};
void Transform::SetScale(float x, float y, float z){
	scale = XMFLOAT3(x,y,z);
};
void Transform::SetScale(XMFLOAT3 sca){
	scale = sca;
};

// Movement functions
void Transform::Move(float x, float y, float z){
	position.x += x;
	position.y += y;
	position.z += z;
};
void Transform::Move(XMFLOAT3 pos){
	Move(pos.x, pos.y, pos.z);
};

// Rotation functions
void Transform::Rotate(float xRad, float yRad, float zRad){
	RotateX(xRad);
	RotateY(yRad);
	RotateZ(zRad);
};
void Transform::Rotate(XMFLOAT3 rotRad){
	Rotate(rotRad.x, rotRad.y, rotRad.z);
};
void Transform::RotateX(float xRad){
	rotation.x += xRad;
};
void Transform::RotateY(float yRad){
	rotation.y += yRad;
};
void Transform::RotateZ(float zRad){
	rotation.z += zRad;
};

// Returns a model matrix of the pos, rot, and scale
XMFLOAT4X4 Transform::WorldMatrix(){
	XMMATRIX pos = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX sca = XMMatrixScaling(scale.x, scale.y, scale.z);
	
	XMMATRIX model = sca * rot * pos;

	XMFLOAT4X4 modelMatrix;
	XMStoreFloat4x4(&modelMatrix, XMMatrixTranspose(model));
	return modelMatrix;
};

// Returns an XMVECTOR of the position, rotation, or scale. Unused 4th value is 1.0f.
XMVECTOR Transform::PosToVector(){
	XMVECTOR v = XMVectorSet(position.x, position.y, position.z, 0.0f);
	return v;
};
XMVECTOR Transform::RotToVector(){
	XMVECTOR v = XMVectorSet(rotation.x, rotation.y, rotation.z, 0.0f);
	return v;
};
XMVECTOR Transform::ScaleToVector(){
	XMVECTOR v = XMVectorSet(scale.x, scale.y, scale.z, 0.0f);
	return v;
};

// Returns a model matrix of the pos, rot, and scale
XMFLOAT4X4 Transform::WorldMatrix(Transform t){
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