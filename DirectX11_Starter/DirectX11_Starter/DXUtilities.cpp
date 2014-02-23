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
	LOG(L"Time taken: ", std::to_wstring(seconds*1000.0f), L"ms");
};

void LogString(std::wstring s){
	std::wcout << s << std::endl;
};
void LogString(std::wstring s1, std::wstring s2){
	std::wcout << s1 << s2 << std::endl;
};
void LogString(std::wstring s1, std::wstring s2, std::wstring s3){
	std::wcout << s1 << s2 << s3 << std::endl;
};
void LogString(std::wstring s1, std::wstring s2, std::wstring s3, std::wstring s4){
	std::wcout << s1 << s2 << s3 << s4 << std::endl;
};
