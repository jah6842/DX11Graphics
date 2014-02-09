#include "DXUtilities.h"

// Initialize the static variables
ID3D11Device* DeviceManager::_currentDevice = nullptr;
ID3D11DeviceContext* DeviceManager::_currentDeviceContext = nullptr;