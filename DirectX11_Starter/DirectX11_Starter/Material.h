#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DXUtilities.h"

using namespace DirectX;

struct VertexShaderConstantBuffer
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

class Material {

public:
	Material(ID3D11Device* device);
	~Material();

	void SetBufferData(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 w, XMFLOAT4X4 v, XMFLOAT4X4 p);
	void SetInputAssemblerOptions(ID3D11DeviceContext* deviceContext);

private:
	void LoadVertexShader(ID3D11Device* device);
	void LoadPixelShader(ID3D11Device* device);
	void LoadConstantBuffer(ID3D11Device* device);

	//ID3D11Texture2D* texture;
	ID3D11PixelShader* pixelShader;
	ID3D11VertexShader* vertexShader;

	// A few more odds and ends we'll need
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vsConstantBuffer;
	VertexShaderConstantBuffer vsConstantBufferData;
};

#endif // _MATERIAL_H