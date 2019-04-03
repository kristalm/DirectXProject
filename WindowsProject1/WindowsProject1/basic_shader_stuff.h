#pragma once
#include "directx_stuff.h"
namespace GraphicsProj {
	class basic_shader_stuff
	{
	public:
		basic_shader_stuff();
		~basic_shader_stuff();
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
		};

		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext* device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj);
		void clean_up();

	private:
		//private variables
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
	};
}
