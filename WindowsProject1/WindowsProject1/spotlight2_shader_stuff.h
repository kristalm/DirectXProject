#pragma once
#include "directx_stuff.h"
#include "light_stuff.h"
using namespace GraphicsProj;
class spotlight2_shader_stuff
{
public:
	spotlight2_shader_stuff();
	~spotlight2_shader_stuff();

	//functions
	bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
	bool render(ID3D11DeviceContext* device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView
		* texture);
	void init_info(XMFLOAT3 pos, XMFLOAT3 dir, XMFLOAT3 att, XMFLOAT4 ambient, XMFLOAT4 diffuse, float range, float cone);
	
	void clean_up();

	//types
	struct cbuffer_struct
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX proj;
	};
	struct light_struct
	{
		light_struct()
		{
			ZeroMemory(this, sizeof(light_struct));
		}
		XMFLOAT3 pos;
		float  range;
		XMFLOAT3 dir;
		float cone;
		XMFLOAT3 att;
		float pad;
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
	};

	//Private variables
	ID3D11VertexShader * vertex_shader;
	ID3D11PixelShader* pixel_shader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* cbuffer;
	ID3D11SamplerState* sample_state;
	ID3D11Buffer* light_buffer;
	light_stuff* info;
};

