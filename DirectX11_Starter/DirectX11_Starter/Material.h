#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <map>
#include <string>
#include <d3d11.h>
#include <WICTextureLoader.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DXUtilities.h"
#include "ConstantBuffer.h"
#include "Vertex.h"
#include <iostream>
#include <list>

using namespace DirectX;

class Material {

public:
	static Material* GetMaterial(std::wstring shaderPrefix, UINT numTextures = 0, std::wstring textureName = L"");
	bool Compare(std::wstring shaderPrefix, UINT numTextures = 0, std::wstring textureName = L"");

	// Load the default shaders
	Material();
	// Assumes vertex and pixel shaders have the same prefix, optional texture
	Material(std::wstring shaderPrefix, UINT numTextures = 0, std::wstring textureName = L"");
	// Load specific vertex and pixel shaders, optional texture
	Material(std::wstring vShaderName, std::wstring pShaderName, UINT numTextures = 0, std::wstring textureName = L"");
	~Material();

	void SetConstantBufferData(XMFLOAT4X4 w, XMFLOAT4X4 v, XMFLOAT4X4 p);
	void SetInputAssemblerOptions();

	// Cleanup all of our static objects
	static void Cleanup();

	static std::list<Material*> _materials;

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

	static ID3D11Buffer* currentConstantBuffer;

	void LoadVertexShader(std::wstring vShaderName);
	void LoadPixelShader(std::wstring pShaderName);
	void LoadConstantBuffer(CONSTANT_BUFFER_LAYOUT layout);
	void LoadTexture(std::wstring texName);

	std::wstring _materialName;
	ID3D11PixelShader* pixelShader;
	ID3D11VertexShader* vertexShader;

	std::wstring textureName;
	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* textureSamplerState;

	// A few more odds and ends we'll need
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vsConstantBuffer;
	//VertexShaderConstantBuffer vsConstantBufferData;
};

#endif // _MATERIAL_H