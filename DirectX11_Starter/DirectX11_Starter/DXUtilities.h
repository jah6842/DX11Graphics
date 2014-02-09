#ifndef _DXUTILITIES_H
#define _DXUTILITIES_H

#include "dxerr.h"
#include <d3d11.h>

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

#endif // _DXUTILITIES_H
