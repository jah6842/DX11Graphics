#include "Renderer.h"

std::vector<GameObject*> Renderer::registeredGOs = std::vector<GameObject*>();

Renderer::Renderer(){

};

Renderer::~Renderer(){

};

ID3D11Buffer* instanceBuffer = nullptr;

InstanceType* instances;
D3D11_BUFFER_DESC instanceBufferDesc;
D3D11_SUBRESOURCE_DATA instanceData;

UINT numInstances = 15*15*15;

void Renderer::Draw(){

	// Finally do the actual drawing
	/*
	deviceContext->DrawIndexed(
		go->mesh->IndexCount(),	// The number of indices we're using in this draw
		0,
		0);
	*/

	// Get the current device context
	ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();
	ID3D11Device* device = DeviceManager::GetCurrentDevice();

	instances = new InstanceType[numInstances];

	int i = 0;
	for(auto &go : registeredGOs){
		instances[i].position = go->transform.position;
		i++;
	}

	registeredGOs[0]->material->SetBufferData(
			//registeredGOs[0]->transform.ModelMatrix(),
			Transform::Identity().ModelMatrix(),
			Camera::MainCamera.GetViewMatrix(),
			Camera::MainCamera.GetProjectionMatrix());
	registeredGOs[0]->material->SetInputAssemblerOptions();


	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * numInstances;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	HR(device->CreateBuffer(&instanceBufferDesc, &instanceData, &instanceBuffer));

	// Set buffers in the input assembler
	UINT strides[2];
	UINT offsets[2];
	ID3D11Buffer* bufferPointers[2];

	strides[0] = Vertex::VertexSize(registeredGOs[0]->mesh->VertexType());
	strides[1] = sizeof(InstanceType);

	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = registeredGOs[0]->mesh->VertexBuffer();	
	bufferPointers[1] = instanceBuffer;

	// Set the current vertex buffer
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
	// Set the current index buffer
	deviceContext->IASetIndexBuffer(registeredGOs[0]->mesh->IndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	// Set the topology
	deviceContext->IASetPrimitiveTopology(registeredGOs[0]->mesh->Topology());
	
	deviceContext->DrawIndexedInstanced(
		registeredGOs[0]->mesh->IndexCount(),
		numInstances,
		0,
		0,
		1);

	ReleaseMacro(instanceBuffer);
	delete[] instances;
	instances = nullptr;
};

void Renderer::RegisterGameObject(GameObject* go){
	registeredGOs.push_back(go);
};

void Renderer::UnRegisterGameObject(GameObject* go){
	registeredGOs.erase(std::remove(registeredGOs.begin(), registeredGOs.end(), go), registeredGOs.end());
};
