#pragma once
#include "directx_stuff.h"
#include "DDSTextureLoader.h"
namespace GraphicsProj
{
	class cube_map_stuff
	{
	public:
		cube_map_stuff();
		~cube_map_stuff();

		//functions
		bool init(ID3D11Device* device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn);
		bool render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView *shader);
		void clean_up();
		void load(ID3D11Device* device, LPCWSTR fn);
		//types
		struct cbuffer_struct
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
		};

		ID3D11ShaderResourceView* get_resource_view();

	private:
		//private variables
		ID3D11VertexShader * vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
		ID3D11SamplerState* sample_state;
		ID3D11ShaderResourceView* cube_resource;
	};
}
