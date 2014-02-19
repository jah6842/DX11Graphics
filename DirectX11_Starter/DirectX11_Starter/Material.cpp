#include "Material.h"

// Static variables
std::list<Material*> Material::_materials;
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
ID3D11Buffer* Material::currentConstantBuffer = nullptr;

// Static class to cleanup all necessary items
void Material::Cleanup(){
	typedef std::list<Material*>::iterator matItr;
	for(matItr iterator = _materials.begin(); iterator != _materials.end(); iterator++) {
		std::wcout << L"Deleting material: " << (*iterator)->_shaderName << std::endl;
		delete *iterator;
	}
	typedef std::map<std::wstring, ID3D11PixelShader*>::iterator pixelItr;
	for(pixelItr iterator = _pixelShaders.begin(); iterator != _pixelShaders.end(); iterator++) {
		ReleaseMacro(iterator->second);
		std::wcout << L"  Released Pixel Shader: " << iterator->first.c_str() << std::endl;
	}
	typedef std::map<std::wstring, ID3D11VertexShader*>::iterator vertexItr;
	for(vertexItr iterator = _vertexShaders.begin(); iterator != _vertexShaders.end(); iterator++) {
		ReleaseMacro(iterator->second);
		std::wcout << L"  Released Vertex Shader: " << iterator->first.c_str() << std::endl;
	}
	typedef std::map<std::wstring, ID3D11InputLayout*>::iterator inputItr;
	for(inputItr iterator = _inputLayouts.begin(); iterator != _inputLayouts.end(); iterator++) {
		ReleaseMacro(iterator->second);
		std::wcout << L"  Released Input Layout: " << iterator->first.c_str() << std::endl;
	}
	typedef std::map<std::wstring, ID3D11ShaderResourceView*>::iterator texItr;
	for(texItr iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
		ReleaseMacro(iterator->second);
		std::wcout << L"  Released Shader Resource View: " << iterator->first.c_str() << std::endl;
	}
	typedef std::map<std::wstring, ID3D11SamplerState*>::iterator texSampItr;
	for(texSampItr iterator = _textureSamplers.begin(); iterator != _textureSamplers.end(); iterator++) {
		ReleaseMacro(iterator->second);
		std::wcout << L"  Released Sampler State: " << iterator->first.c_str() << std::endl;
	}

	//ReleaseMacro(currentConstantBuffer);
};

Material* Material::GetMaterial(MATERIAL_DESCRIPTION description){
	// Check if the material already exists
	for(std::list<Material*>::iterator itr = _materials.begin(); itr != _materials.end(); itr++){
		if((*itr)->Compare(description)){
			return *itr;
		}
	}

	//std::wcout << L"New material created: " << shaderPrefix << std::endl;
	return new Material(description);
};

// Compare two shaders, returns a boolean if they are the same
bool Material::Compare(MATERIAL_DESCRIPTION description){
	if(_shaderName == description.shaderName &&
		_vShaderName == description.vShaderFilename &&
		_pShaderName == description.pShaderFilename &&
		_diffuseTextureName == description.diffuseTextureFilename &&
		_cBufferLayout == description.cBufferLayout){
		return true;
	}

	return false;
};

// Constructor
Material::Material(MATERIAL_DESCRIPTION description){
	_shaderName = description.shaderName;
	_vShaderName = description.vShaderFilename;
	_pShaderName = description.pShaderFilename;
	_cBufferLayout = description.cBufferLayout;
	_diffuseTextureName = description.diffuseTextureFilename;

	// Load the vertex shader
	std::wstring vShaderPath = SHADER_PATH;
	vShaderPath += description.vShaderFilename;
	LoadVertexShader(vShaderPath);

	// Load the pixel shader
	std::wstring pShaderPath = SHADER_PATH;
	pShaderPath += description.pShaderFilename;
	LoadPixelShader(pShaderPath);

	// Load the constant buffer
	LoadConstantBuffer(description.cBufferLayout);

	// Load textures
	std::wstring dTexturePath = TEXTURE_PATH;
	dTexturePath += description.diffuseTextureFilename;
	LoadTexture(dTexturePath);

	_materials.push_back(this);
};

Material::~Material(){
	// Most releases are handled by the Material Cleanup() function called when the application exits.
	ReleaseMacro(_vsConstantBuffer);
};

void Material::SetConstantBufferData(){
	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// World, View, Projection matrices
	if(_cBufferLayout == CONSTANT_BUFFER_LAYOUT_VS_WVP){
		VS_CONSTANT_BUFFER_WVP wvpData;
		wvpData.world = Transform::Identity().WorldMatrix();
		wvpData.view = Camera::MainCamera.GetViewMatrix();
		wvpData.projection = Camera::MainCamera.GetProjectionMatrix();

		// Update the constant buffer itself
		deviceContext->UpdateSubresource(_vsConstantBuffer,
			0,			
			NULL,		
			&wvpData,
			0,
			0);
	} 
	// View*Projection Matrix
	else if(_cBufferLayout == CONSTANT_BUFFER_LAYOUT_VS_VPMATRIX){
		VS_CONSTANT_BUFFER_VPMATRIX vpData;
		vpData.viewProj = Camera::MainCamera.GetViewProjMatrix();

		// Update the constant buffer itself
		deviceContext->UpdateSubresource(_vsConstantBuffer,
			0,			
			NULL,		
			&vpData,
			0,
			0);
	}
};

void Material::SetInputAssemblerOptions(){
	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// Check if we need to change state, if not use the current state.
	if(_vertexShader != currentVertexShader){
		currentVertexShader = _vertexShader;
		deviceContext->VSSetShader(_vertexShader, NULL, 0);
	}
	if(_vsConstantBuffer != currentConstantBuffer){
		deviceContext->VSSetConstantBuffers(0, 1, &_vsConstantBuffer);
		currentConstantBuffer = _vsConstantBuffer;
	}
	if(_pixelShader != currentPixelShader){
		currentPixelShader = _pixelShader;
		deviceContext->PSSetShader(_pixelShader, NULL, 0);
	}
	if(_diffuseTexture != currentTexture){
		currentTexture = _diffuseTexture;
		deviceContext->PSSetShaderResources(0,1,&_diffuseTexture);
	}
	if(_diffuseTextureSamplerState != currentTextureSampler){
		currentTextureSampler = _diffuseTextureSamplerState;
		deviceContext->PSSetSamplers(0,1,&_diffuseTextureSamplerState);
	}
	if(_inputLayout != currentInputLayout){
		currentInputLayout = _inputLayout;
		deviceContext->IASetInputLayout(_inputLayout);
	}
};

void Material::LoadConstantBuffer(CONSTANT_BUFFER_LAYOUT layout){
	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	// Create a constant buffer
	D3D11_BUFFER_DESC cBufferDesc;

	switch(layout){
	case CONSTANT_BUFFER_LAYOUT_VS_WVP:
		cBufferDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER_WVP); break;
	case CONSTANT_BUFFER_LAYOUT_VS_VPMATRIX:
		cBufferDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER_VPMATRIX); break;
	default:
		std::wcout << "INVALID CONSTANT BUFFER TYPE" << std::endl;
	}

	cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags		= 0;
	cBufferDesc.MiscFlags			= 0;
	cBufferDesc.StructureByteStride = 0;
	HR(device->CreateBuffer(
		&cBufferDesc,
		NULL,
		&_vsConstantBuffer));
};

void Material::LoadPixelShader(std::wstring pShaderName){

	// Check if the shader already exists
	if(_pixelShaders.count(pShaderName)){
		_pixelShader = _pixelShaders[pShaderName];
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
		&_pixelShader));

	// Clean up
	ReleaseMacro(psBlob);

	// Add it to the static list
	_pixelShaders[pShaderName] = _pixelShader;
};

// Loads shaders from compiled shader object (.cso) files, and uses the
// vertex shader to create an input layout which is needed when sending
// vertex data to the device
void Material::LoadVertexShader(std::wstring vShaderName){

	// Check if the shader already exists
	if(_vertexShaders.count(vShaderName)){
		_vertexShader = _vertexShaders[vShaderName];
		_inputLayout = _inputLayouts[vShaderName];
		return;
	}

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
		&_vertexShader));
	
	D3D11_INPUT_ELEMENT_DESC* description = nullptr;
	UINT descriptionSize = 0;

	if(vShaderName.find(L"Colored") != std::wstring::npos){
		description = VERTEX_DESCRIPTION_POS_COLOR;
		descriptionSize = 2;
	}
	if(vShaderName.find(L"Textured") != std::wstring::npos){
		description = VERTEX_DESCRIPTION_POS_UV;
		descriptionSize = 2;
	}
	if(vShaderName.find(L"TexturedInstanced") != std::wstring::npos){
		description = VERTEX_DESCRIPTION_POS_UV_INSTANCED;
		descriptionSize = 6;
	}

	assert(description != nullptr);
	assert(descriptionSize != 0);

	// Before cleaning up the data, create the input layout
	HR(device->CreateInputLayout(
		description,
		descriptionSize,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&_inputLayout));

	// Clean up
	ReleaseMacro(vsBlob);

	// Add it to the static list
	_vertexShaders[vShaderName] = _vertexShader;
	_inputLayouts[vShaderName] = _inputLayout;
};

void Material::LoadTexture(std::wstring texName){
	// Check if the texture already exists
	if(_textures.count(texName)){
		_diffuseTexture = _textures[texName];
		_diffuseTextureSamplerState = _textureSamplers[texName];
		return;
	}

	// Get the current device
	ID3D11Device* device = DeviceManager::GetCurrentDevice();
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

	// NEW DirectXTK Texture Loading
	HR(CreateWICTextureFromFile(device, deviceContext, texName.c_str(), NULL, &_diffuseTexture));

	// Describe the Sample State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    
	//Create the Sample State
	device->CreateSamplerState( &sampDesc, &_diffuseTextureSamplerState );

	// Add it to the static list
	_textures[texName] = _diffuseTexture;
	_textureSamplers[texName] = _diffuseTextureSamplerState;
};