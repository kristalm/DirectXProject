#pragma once
#include "directx_stuff.h"
#include "light_stuff.h"
namespace GraphicsProj {
	class light_shader_stuff
	{
	public:
		light_shader_stuff();
		~light_shader_stuff();

		//functions
		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext* device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView
		            * texture);
		void init_info(XMFLOAT3 light_direction, XMFLOAT4 diffuse_color);

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
			XMFLOAT4 diffuse_color;
			XMFLOAT3 direction;
			float padding;
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
}

