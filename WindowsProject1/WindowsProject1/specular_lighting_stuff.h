#pragma once
#include "directx_stuff.h"
#include "light_stuff.h"
namespace GraphicsProj
{


	class specular_lighting_stuff
	{
	public:
		specular_lighting_stuff();
		~specular_lighting_stuff();

		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView * texture, XMFLOAT3 camera_pos);
		void init_info(XMFLOAT4 ambient_color, XMFLOAT3 light_direction, XMFLOAT4 diffuse_color, XMFLOAT4 spec_color, float intensity);
		void clean_up();

		//types
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
		};
		struct camera_struct
		{
			XMFLOAT3 pos;
			float padding;
		};
		struct light_struct
		{
			XMFLOAT4 ambient_color;
			XMFLOAT4 diffuse_color;
			XMFLOAT3 direction;
			float intensity;
			XMFLOAT4 color;
		};

		//Private variables
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
		ID3D11SamplerState* sample_state;
		ID3D11Buffer* light_buffer;
		ID3D11Buffer* camera_buffer;
		light_stuff* info;
	};
}

