#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

#include <dxgi.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace DirectX;

namespace GraphicsProj {
	class directx_stuff
	{
	public:
		directx_stuff();
		~directx_stuff();

		//functions
		bool init(HWND hwnd, float screen_width, float screen_height, float screen_depth, float screen_near);
		void clear_buffer();
		void resize(float screen_width, float screen_height);
		void display();
		void set_back_render();
		void reset_viewport();
		void clean_up();
		void turn_off_z();
		void turn_on_z();

		//Getters & setters
		ID3D11Device* get_device();
		ID3D11DeviceContext* get_device_context();
		XMMATRIX get_proj_matrix();
		XMMATRIX get_world_matrix();
		XMMATRIX get_ortho_matrix();

		ID3D11RasterizerState* get_wire_frame_state();
		ID3D11RasterizerState* get_front_culling_state();
		ID3D11RasterizerState* get_depth_bias_state();
		ID3D11RasterizerState* get_default_raster_state();

		ID3D11BlendState* get_transparent_state();
		ID3D11BlendState* get_default_blend_state();

		ID3D11DepthStencilView* get_depth_stencil_view();
		void set_back_buffer_render_target();

		//Private variables
	private:
		IDXGISwapChain * swap_chain;
		ID3D11Device* device;
		ID3D11DeviceContext* device_context;
		ID3D11RenderTargetView* render_target_view;
		ID3D11Texture2D* depth_stencil_buffer;
		ID3D11DepthStencilState* depth_stencil_state;
		ID3D11DepthStencilView* depth_stencil_view;
		ID3D11RasterizerState* raster_state;
		XMMATRIX proj_matrix;
		XMMATRIX world_matrix;
		XMMATRIX ortho_matrix;
		ID3D11DepthStencilState* depth_disabled_stencil_state;

		//States
		ID3D11RasterizerState* wire_frame;
		ID3D11RasterizerState* front_cull;
		ID3D11RasterizerState* depth_bias;

		ID3D11BlendState* transparent_state;
		ID3D11BlendState* default_blend_state;
		D3D11_VIEWPORT viewport;
	};
}

