#include "Renderer.h"


Renderer::Renderer(){

};

Renderer::~Renderer(){

};

void Renderer::Draw(GameObject* go){
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
};