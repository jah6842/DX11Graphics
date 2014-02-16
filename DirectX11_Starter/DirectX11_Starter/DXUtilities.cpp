#include "DXUtilities.h"

// Initialize the static device variables
ID3D11Device* DeviceManager::_currentDevice = nullptr;
ID3D11DeviceContext* DeviceManager::_currentDeviceContext = nullptr;

__int64 DebugTimer::frequency = 0;
__int64 DebugTimer::start = 0;
__int64 DebugTimer::stop = 0;

void DebugTimer::Start(){
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	frequency = freq.QuadPart;

	LARGE_INTEGER s;
	QueryPerformanceCounter(&s);
	start = s.QuadPart;
};

void DebugTimer::Stop(){
	LARGE_INTEGER s;
	QueryPerformanceCounter(&s);
	stop = s.QuadPart;

	__int64 diff = stop - start;
	double seconds = (double)diff / (double)frequency;
	std::wcout << "Time taken: " << seconds*1000 << "ms" << std::endl;
};
