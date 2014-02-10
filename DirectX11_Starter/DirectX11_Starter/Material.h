#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <map>
#include <string>
#include <d3d11.h>
#include <DirectX\D3DX11.h>
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
	Material();
	~Material();

	void SetBufferData(XMFLOAT4X4 w, XMFLOAT4X4 v, XMFLOAT4X4 p);
	void SetInputAssemblerOptions();

	static void Cleanup();

private:
	// Static containers so we don't end up with duplicates
	static std::map<std::wstring, ID3D11PixelShader*> _pixelShaders;
	static ID3D11PixelShader* currentPixelShader;

	static std::map<std::wstring, ID3D11VertexShader*> _vertexShaders;
	static ID3D11VertexShader* currentVertexShader;

	static std::map<std::wstring, ID3D11InputLayout*> _inputLayouts;
	static ID3D11InputLayout* currentInputLayout;

	static std::map<std::wstring, ID3D11ShaderResourceView*> _textures;
	static ID3D11ShaderResourceView* currentTexture;

	static std::map<std::wstring, ID3D11SamplerState*> _textureSamplers;
	static ID3D11SamplerState* currentTextureSampler;

	void LoadVertexShader(std::wstring vShaderName);
	void LoadPixelShader(std::wstring pShaderName);
	void LoadConstantBuffer();
	void LoadTexture(std::wstring texName);

	ID3D11PixelShader* pixelShader;
	ID3D11VertexShader* vertexShader;

	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* textureSamplerState;

	// A few more odds and ends we'll need
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vsConstantBuffer;
	VertexShaderConstantBuffer vsConstantBufferData;
};

#endif // _MATERIAL_H