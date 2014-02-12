#include "Renderer.h"

std::vector<GameObject*> Renderer::registeredGOs = std::vector<GameObject*>();

Renderer::Renderer(){

};

Renderer::~Renderer(){

};

void Renderer::Draw(){
	for(auto &go : registeredGOs){

		// Get the current device context
		ID3D11DeviceContext* deviceContext = DeviceManager::GetCurrentDeviceContext();

		// Set mesh-related buffers in the input assembler
		go->mesh->SetInputAssemblerOptions();

		// Set material-related buffers in the input assembler
		go->material->SetInputAssemblerOptions();

		// Finally do the actual drawing
		deviceContext->DrawIndexed(
			go->mesh->IndexCount(),	// The number of indices we're using in this draw
			0,
			0);
	}
};

void Renderer::RegisterGameObject(GameObject* go){
	registeredGOs.push_back(go);
};

void Renderer::UnRegisterGameObject(GameObject* go){
	registeredGOs.erase(std::remove(registeredGOs.begin(), registeredGOs.end(), go), registeredGOs.end());
};
