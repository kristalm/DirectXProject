#pragma once
#include "directx_stuff.h"
#include "light_stuff.h"
namespace GraphicsProj
{
	class shadow_map_shader_stuff
	{
	public:
		shadow_map_shader_stuff();
		~shadow_map_shader_stuff();

		//functions
		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, XMMATRIX light_view, XMMATRIX light_proj, ID3D11ShaderResourceView * texture, ID3D11ShaderResourceView * depth_texture);
		void init_info(light_stuff* stuff);

		void clean_up();

		//types
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
			XMMATRIX light_view;
			XMMATRIX light_proj;
		};
		struct light_struct
		{
			XMFLOAT4 ambient_color;
			XMFLOAT4 diffuse_color;
			XMFLOAT3 direction;
			float padding;
		};

		//Private variables
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
		ID3D11SamplerState* sample_state_wrap;
		ID3D11SamplerState* sample_state_clamp;
		ID3D11Buffer* light_buffer;
		light_stuff* info;
	};
}
