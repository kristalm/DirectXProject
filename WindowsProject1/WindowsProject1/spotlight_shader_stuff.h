#pragma once
#include "directx_stuff.h"
#include "light_stuff.h"
#define NUM_LIGHTS 4
namespace GraphicsProj
{
	class spotlight_shader_stuff
	{
	public:
		spotlight_shader_stuff();
		~spotlight_shader_stuff();

		//functions
		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView * texture);
		void init_info(XMFLOAT4 diffuse_[], XMFLOAT4 pos_[]);

		void clean_up(); 
		//types
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
		};
		struct light_color_struct
		{
			XMFLOAT4 diffuseColor[NUM_LIGHTS];
		};

		struct light_pos_struct
		{
			XMFLOAT4 lightPosition[NUM_LIGHTS];
		};

		//Private variables
		light_stuff* info;
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
		ID3D11SamplerState* sample_state;
		ID3D11Buffer* light_buffer;
		ID3D11Buffer* light_pos_buffer;
	};
}

