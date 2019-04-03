#pragma once
#include "directx_stuff.h"

namespace GraphicsProj
{
	class depth_shader_stuff
	{
	public:
		depth_shader_stuff();
		//functions
	
		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj);
		void clean_up();

		//types
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
		};

		//Private variables
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;

	};

}