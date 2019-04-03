#pragma once
#include "directx_stuff.h"
namespace GraphicsProj
{
	class bitmap_stuff
	{
	public:
		bitmap_stuff();
		~bitmap_stuff();

		//functions
		bool init(ID3D11Device * device, int screen_width, int screen_height, int bitmap_w, int bitmap_h);
		bool render(ID3D11DeviceContext * device_context, int posx, int posy);
		void init_info(XMFLOAT3 light_direction, XMFLOAT4 diffuse_color);
		int get_index_count();
		void clean_up();

		//types
		struct cbuffer_struct
		{
			XMFLOAT3 pos;
			XMFLOAT2 text;
		};

		//Private variables
		ID3D11Buffer * vertex_buffer;
		ID3D11Buffer* index_buffer;
		int vertex_count, index_count;
		int screen_width, screen_height;
		int bitmap_width, bitmap_height;
		int prev_posx, prev_posy;
		ID3D11InputLayout* layout;
		ID3D11Buffer* cbuffer;
		ID3D11SamplerState* sample_state;
		ID3D11Buffer* light_buffer;
	};
}
