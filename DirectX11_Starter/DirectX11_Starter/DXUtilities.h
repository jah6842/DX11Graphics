#ifndef _DXUTILITIES_H
#define _DXUTILITIES_H

#include <Windows.h>
#include "dxerr.h"
#include <d3d11.h>
#include <string>
#include <iostream>
//#include <random>
//#include <vld.h>

// Convenience macro for releasing a COM object
#define ReleaseMacro(x) { if(x){ x->Release(); x = 0; } }




// Macro for popping up a text box based
// on a failed HRESULT and then quitting (only in debug builds)
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)												\
	{															\
		HRESULT hr = (x);										\
		if(FAILED(hr))											\
		{														\
			DXTrace(__FILEW__, (DWORD)__LINE__, hr, L#x, true);	\
			PostQuitMessage(0);									\
		}														\
	}														
	#endif
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif


// Static class to manage DirectX devices and contexts
class DeviceManager {
private:
	static ID3D11Device* _currentDevice;
	static ID3D11DeviceContext* _currentDeviceContext;
public:
	static ID3D11Device* GetCurrentDevice(){
		return _currentDevice;
	};
	static ID3D11DeviceContext* GetCurrentDeviceContext(){
		return _currentDeviceContext;
	};

	static void SetCurrentDevice(ID3D11Device* device){
		_currentDevice = device;
	};
	static void SetCurrentDeviceContext(ID3D11DeviceContext* deviceContext){
		_currentDeviceContext = deviceContext;
	};
};

// A high performance timer that uses QueryPerformanceCounter
class DebugTimer {
	static __int64 frequency;
	static __int64 start;
	static __int64 stop;
public:
	static void Start();
	static void Stop();
};

// Macro for debug logging
// In debug builds will log to console
// In release builds will replace with a NO-OP
#if defined(DEBUG) | defined(_DEBUG)
	#define LOG LogString													
#else
	#define LOG __noop
#endif

// Debug logging
#if defined(DEBUG) | defined(_DEBUG)
static void LogString(std::wstring s);
static void LogString(std::wstring s1, std::wstring s2);
static void LogString(std::wstring s1, std::wstring s2, std::wstring s3);
static void LogString(std::wstring s1, std::wstring s2, std::wstring s3, std::wstring s4);
#endif

#endif // _DXUTILITIES_H
