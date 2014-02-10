#include "Material.h"

// Static variables
std::map<std::wstring, ID3D11PixelShader*> Material::_pixelShaders;
std::map<std::wstring, ID3D11VertexShader*> Material::_vertexShaders;
std::map<std::wstring, ID3D11InputLayout*> Material::_inputLayouts;
std::map<std::wstring, ID3D11ShaderResourceView*> Material::_textures;
std::map<std::wstring, ID3D11SamplerState*> Material::_textureSamplers;

ID3D11PixelShader* Material::currentPixelShader = nullptr;
ID3D11VertexShader* Material::currentVertexShader = nullptr;
ID3D11InputLayout* Material::currentInputLayout = nullptr;
ID3D11ShaderResourceView* Material::currentTexture = nullptr;
ID3D11SamplerState* Material::currentTextureSampler = nullptr;

Material::Material(){
	LoadVertexShader(L"../Resources/Shaders/TexturedVertexShader.cso");
	LoadPixelShader(L"../Resources/Shaders/TexturedPixelShader.cso");
	LoadConstantBuffer();
	LoadTexture(L"../Resources/Textures/texture.jpg");
};

Material::~Material(){
	ReleaseMacro(vertexShader);
	ReleaseMacro(pixelShader);
	ReleaseMacro(vsConstantBuffer);
	ReleaseMacro(inputLayout);
};

void Material::SetBufferData(XMFLOAT4X4 w, XMFLOAT4X4 v, XMFLOAT4X4 p){
	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Update local constant buffer data
	vsConstantBufferData.world = w;
	vsConstantBufferData.view = v;
	vsConstantBufferData.projection = p;

	// Update the constant buffer itself
	deviceContext->UpdateSubresource(
		vsConstantBuffer,
		0,			
		NULL,		
		&vsConstantBufferData,
		0,
		0);
};

void Material::SetInputAssemblerOptions(){
	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Set the current vertex and pixel shaders, as well the constant buffer for the vert shader
	if(vertexShader != currentVertexShader){
		currentVertexShader = vertexShader;
		deviceContext->VSSetShader(vertexShader, NULL, 0);
	}

	deviceContext->VSSetConstantBuffers(
		0,	// Corresponds to the constant buffer's register in the vertex shader
		1, 
		&vsConstantBuffer);

	if(pixelShader != currentPixelShader){
		currentPixelShader = pixelShader;
		deviceContext->PSSetShader(pixelShader, NULL, 0);
	}

	if(texture != currentTexture){
		currentTexture = texture;
		deviceContext->PSSetShaderResources(0,1,&texture);
	}
	if(textureSamplerState != currentTextureSampler){
		currentTextureSampler = textureSamplerState;
		deviceContext->PSSetSamplers(0,1,&textureSamplerState);
	}

	if(inputLayout != currentInputLayout){
		currentInputLayout = inputLayout;
		deviceContext->IASetInputLayout(inputLayout);
	}
};

void Material::LoadConstantBuffer(){
	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Constant buffers ----------------------------------------
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.ByteWidth			= sizeof(vsConstantBufferData);
	cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags		= 0;
	cBufferDesc.MiscFlags			= 0;
	cBufferDesc.StructureByteStride = 0;
	HR(device->CreateBuffer(
		&cBufferDesc,
		NULL,
		&vsConstantBuffer));
};

void Material::LoadPixelShader(std::wstring pShaderName){

	// Check if the shader already exists
	if(_pixelShaders.count(pShaderName)){
		pixelShader = _pixelShaders[pShaderName];
		return;
	}

	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Load Pixel Shader ---------------------------------------
	ID3DBlob* psBlob;
	D3DReadFileToBlob(pShaderName.c_str(), &psBlob);

	// Create the shader on the device
	HR(device->CreatePixelShader(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		NULL,
		&pixelShader));

	// Clean up
	ReleaseMacro(psBlob);

	// Add it to the static list
	_pixelShaders[pShaderName] = pixelShader;
};

// Loads shaders from compiled shader object (.cso) files, and uses the
// vertex shader to create an input layout which is needed when sending
// vertex data to the device
void Material::LoadVertexShader(std::wstring vShaderName){

	// Check if the shader already exists
	if(_vertexShaders.count(vShaderName)){
		vertexShader = _vertexShaders[vShaderName];
		inputLayout = _inputLayouts[vShaderName];
		return;
	}

	// Set up the vertex layout description
	// This has to match the vertex input layout in the vertex shader
	// We can't set up the input layout yet since we need the actual vert shader
	/*
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0}
	};*/

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
	};

	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Load Vertex Shader --------------------------------------
	ID3DBlob* vsBlob;
	D3DReadFileToBlob(vShaderName.c_str(), &vsBlob);

	// Create the shader on the device
	HR(device->CreateVertexShader(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		NULL,
		&vertexShader));

	// Before cleaning up the data, create the input layout
	HR(device->CreateInputLayout(
		vertexDesc,
		ARRAYSIZE(vertexDesc),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout));

	// Clean up
	ReleaseMacro(vsBlob);

	// Add it to the static list
	_vertexShaders[vShaderName] = vertexShader;
	_inputLayouts[vShaderName] = inputLayout;
};

void Material::LoadTexture(std::wstring texName){
	// Check if the texture already exists
	if(_textures.count(texName)){
		texture = _textures[texName];
		textureSamplerState = _textureSamplers[texName];
		return;
	}

	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	D3DX11CreateShaderResourceViewFromFile( device, texName.c_str(), NULL, NULL, &texture, NULL );

	// Describe the Sample State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    
	//Create the Sample State
	device->CreateSamplerState( &sampDesc, &textureSamplerState );

	// Add it to the static list
	_textures[texName] = texture;
	_textureSamplers[texName] = textureSamplerState;
};