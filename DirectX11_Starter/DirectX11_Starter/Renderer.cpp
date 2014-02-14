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

//UINT numInstances = 15*15*15;

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

	std::vector<GameObject*> openList = std::vector<GameObject*>(registeredGOs.size());
	std::vector<GameObject*> renderList = std::vector<GameObject*>();
	std::vector<Material*> seenMaterials = std::vector<Material*>();

	// Add all gameobjects to the open list
	for(int i = 0; i < registeredGOs.size(); i++){
		openList[i] = registeredGOs[i];
	}

	Material* currentRenderMaterial = nullptr;
	// Get all gameobjects with a certain material and draw them
	while(openList.size() > 0){

		// Get the first material from the render list
		currentRenderMaterial = openList[0]->material;
		seenMaterials.push_back(currentRenderMaterial);

		// Set the proper input options for this material
		openList[0]->material->SetConstantBufferData(
				openList[0]->transform.ModelMatrix(), // Model matrix of the first object
				//Transform::Identity().ModelMatrix(), // Model matrix of an identity matrix
				Camera::MainCamera.GetViewMatrix(),
				Camera::MainCamera.GetProjectionMatrix());
		openList[0]->material->SetInputAssemblerOptions();

		// Loop through the open list and get all of the objects with the 
		// same material that we should add to the render list.
		for(int i = 0; i < openList.size(); i++){
			if(openList[i]->material == currentRenderMaterial){
				renderList[i] = openList[i];
				openList.erase(openList.begin() + i);
				i--;
			}
		}

		// Allocate memory for all of the instance data
		instances = new InstanceType[renderList.size()];

		// Loop through all render items and put them into the instance array
		for(int i = 0; i < renderList.size(); i++){
			instances[i].position = renderList[i]->transform.position;
		}

		// Set up the description of the instance buffer.
		instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		instanceBufferDesc.ByteWidth = sizeof(InstanceType) * renderList.size();
		instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		instanceBufferDesc.CPUAccessFlags = 0;
		instanceBufferDesc.MiscFlags = 0;
		instanceBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the instance data.
		instanceData.pSysMem = instances;
		instanceData.SysMemPitch = 0;
		instanceData.SysMemSlicePitch = 0;

		// Create an instance buffer for the instance data
		HR(device->CreateBuffer(&instanceBufferDesc, &instanceData, &instanceBuffer));

		// Set buffers in the input assembler
		UINT strides[2];
		UINT offsets[2];
		ID3D11Buffer* bufferPointers[2];

		strides[0] = Vertex::VertexSize(renderList[0]->mesh->VertexType());
		strides[1] = sizeof(InstanceType);

		offsets[0] = 0;
		offsets[1] = 0;

		bufferPointers[0] = renderList[0]->mesh->VertexBuffer();	
		bufferPointers[1] = instanceBuffer;

		// Set the current vertex buffer
		deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
		// Set the current index buffer
		deviceContext->IASetIndexBuffer(renderList[0]->mesh->IndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
		// Set the topology
		deviceContext->IASetPrimitiveTopology(renderList[0]->mesh->Topology());
	
		deviceContext->DrawIndexedInstanced(
			renderList[0]->mesh->IndexCount(),
			renderList.size(),
			0,
			0,
			1);

		ReleaseMacro(instanceBuffer);
		delete[] instances;
		instances = nullptr;
		renderList.clear();
	}
};

void Renderer::RegisterGameObject(GameObject* go){
	registeredGOs.push_back(go);
};

void Renderer::UnRegisterGameObject(GameObject* go){
	registeredGOs.erase(std::remove(registeredGOs.begin(), registeredGOs.end(), go), registeredGOs.end());
};
