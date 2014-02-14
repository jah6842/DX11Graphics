#ifndef _CONSTANT_BUFFER_H
#define _CONSTANT_BUFFER_H

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

enum CONSTANT_BUFFER_LAYOUT {
	CONSTANT_BUFFER_LAYOUT_VS_WVP
};

struct VS_CONSTANT_BUFFER_WVP
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

#endif // _CONSTANT_BUFFER_H