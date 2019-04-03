#include "directx_stuff.h"
#include <minwinbase.h>
#include "defines.h"

using namespace GraphicsProj;
directx_stuff::directx_stuff()
{
	swap_chain = nullptr;
	device = nullptr;
	device_context= nullptr;
	render_target_view= nullptr;
	depth_stencil_buffer= nullptr;
	depth_stencil_state= nullptr;
	depth_stencil_view= nullptr;
	raster_state= nullptr;
}
void directx_stuff::clean_up()
{
	raster_state->Release();
	depth_stencil_view->Release();
	depth_stencil_state->Release();
	depth_stencil_buffer->Release();
	render_target_view->Release();
	swap_chain->Release();
	device_context->Release();
	device->Release();
	
	ID3D11Debug* DebugDevice = nullptr;
	HRESULT Result = device->QueryInterface(__uuidof(ID3D11Debug), (void**)(&DebugDevice));
	DebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	DebugDevice->Release();
}

directx_stuff::~directx_stuff()
{
	
}

bool directx_stuff::init(HWND hwnd, float screen_width, float screen_height, float screen_depth, float screen_near)
{
	HRESULT work_check;
	ID3D11Texture2D* back_buffer_ptr;
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	scd.BufferDesc.Height = screen_height;
	scd.BufferDesc.Width = screen_width;
	
	//TODO: maybe to resize screen?
	/*scd.BufferDesc.Height = {0};
	scd.BufferDesc.Width = {0};*/



	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &scd, &swap_chain, &device, NULL, &device_context);
	
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_ptr);

	work_check = device->CreateRenderTargetView(back_buffer_ptr, NULL, &render_target_view);

	back_buffer_ptr->Release();

//Create Depth Buffer

	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));

	depth_buffer_desc.Width = screen_width;
	depth_buffer_desc.Height = screen_height;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;

	
	work_check = device->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer);

	
//Create Depth Stencil
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;

	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc) );

	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xff;
	depth_stencil_desc.StencilWriteMask = 0xff;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	work_check = device->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);

    device_context->OMSetDepthStencilState(depth_stencil_state, 1);

//Create Depth Stencil View

	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));

	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	work_check = device->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, &depth_stencil_view);
	if (FAILED(work_check))
		return false;

	device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);

//Create Rasterizer State
	D3D11_RASTERIZER_DESC rasterizer_desc;

	rasterizer_desc.AntialiasedLineEnable = false;
	rasterizer_desc.CullMode = D3D11_CULL_NONE;
	rasterizer_desc.DepthBias = 0;
	rasterizer_desc.DepthBiasClamp = 0.0f;
	rasterizer_desc.DepthClipEnable = true;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.FrontCounterClockwise = false;
	rasterizer_desc.MultisampleEnable = false;
	rasterizer_desc.ScissorEnable = false;
	rasterizer_desc.SlopeScaledDepthBias = 0.0f;

	work_check = device->CreateRasterizerState(&rasterizer_desc, &raster_state);

	device_context->RSSetState(raster_state);

//Wire frame state
	rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizer_desc.AntialiasedLineEnable = TRUE;

	device->CreateRasterizerState(&rasterizer_desc, &wire_frame);

//Back face state
	rasterizer_desc.CullMode = D3D11_CULL_FRONT;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	device->CreateRasterizerState(&rasterizer_desc, &front_cull);

//Depth bias state
	rasterizer_desc.AntialiasedLineEnable = false;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;
	rasterizer_desc.DepthBias = 0;
	rasterizer_desc.DepthBiasClamp = 0.0f;
	rasterizer_desc.DepthClipEnable = true;
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.FrontCounterClockwise = false;
	rasterizer_desc.MultisampleEnable = false;
	rasterizer_desc.ScissorEnable = false;
	rasterizer_desc.SlopeScaledDepthBias = 0.0f;

	device->CreateRasterizerState(&rasterizer_desc, &depth_bias);

//Transparent blend state
	D3D11_BLEND_DESC bd;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	bd.IndependentBlendEnable = FALSE;
	bd.AlphaToCoverageEnable = FALSE;

	HRESULT check = device->CreateBlendState(&bd, &transparent_state);

//Default

	D3D11_BLEND_DESC bd_;
	bd_.RenderTarget[0].BlendEnable = FALSE;
	bd_.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd_.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd_.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd_.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd_.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd_.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd_.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	bd_.IndependentBlendEnable = FALSE;
	bd_.AlphaToCoverageEnable = FALSE;

	check = device->CreateBlendState(&bd_, &default_blend_state);
//Create View Port
	D3D11_VIEWPORT viewport;

	viewport.Width = static_cast<float>(screen_width);
	viewport.Height = static_cast<float>(screen_height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	device_context->RSSetViewports(1, &viewport);

//Create proj matrix

	auto field_of_view = static_cast<float>(XM_PI)/ 4.0f;
	auto screen_aspect = static_cast<float>(screen_width) / static_cast<float>(screen_height);

	proj_matrix = XMMatrixPerspectiveFovLH(field_of_view, screen_aspect, screen_near, screen_depth);

//Create world Matrix 
	world_matrix = XMMatrixIdentity();
	ortho_matrix = XMMatrixOrthographicLH(static_cast<float>(screen_width), static_cast<float>(screen_height), screen_near, screen_depth);

//depth stencil

	D3D11_DEPTH_STENCIL_DESC depth_disabled_stencil_desc;
	depth_disabled_stencil_desc.DepthEnable = false;
	depth_disabled_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_disabled_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_disabled_stencil_desc.StencilEnable = true;
	depth_disabled_stencil_desc.StencilReadMask = 0xFF;
	depth_disabled_stencil_desc.StencilWriteMask = 0xFF;
	depth_disabled_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_disabled_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_disabled_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_disabled_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the state using the device.
	work_check = device->CreateDepthStencilState(&depth_disabled_stencil_desc, &depth_disabled_stencil_state);
	if (FAILED(work_check))
	{
		return false;
	}
	return work_check;
}

void directx_stuff::clear_buffer()
{
	float color[] = {0.0f, 0.0f, 0.0f, 1.0f};

	device_context->ClearRenderTargetView(render_target_view, color);

	device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void directx_stuff::resize(float screen_width, float screen_height)
{
	device_context->OMGetRenderTargets(0, 0, 0);
		render_target_view->Release();

		swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		ID3D11Texture2D* buffer;
		swap_chain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&buffer);

		device->CreateRenderTargetView(buffer, NULL, &render_target_view);

		buffer->Release();

		
		viewport.Width = static_cast<float>(screen_width);
		viewport.Height = static_cast<float>(screen_height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		device_context->RSSetViewports(1, &viewport);
}
//Getters
void directx_stuff::display()
{
	HRESULT check;
	check = swap_chain->Present(0, 0);

	ID3D11ShaderResourceView * tab[1];
	tab[0] = NULL;
	device_context->PSSetShaderResources(0,1, tab);
	if(FAILED(check))
		return;
}
void directx_stuff::set_back_render()
{
	device_context->OMGetRenderTargets(1, &render_target_view, &depth_stencil_view);
}
void directx_stuff::turn_on_z()
{
	device_context->OMSetDepthStencilState(depth_stencil_state, 1);
}
void directx_stuff::turn_off_z()
{
	device_context->OMSetDepthStencilState(depth_disabled_stencil_state, 1);
}

void directx_stuff::reset_viewport()
{
	D3D11_VIEWPORT viewport;

	viewport.Width = static_cast<float>(500);
	viewport.Height = static_cast<float>(500);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	device_context->RSSetViewports(1, &viewport);
}
ID3D11Device * directx_stuff::get_device()
{
	return device;
}

ID3D11DeviceContext * directx_stuff::get_device_context()
{
	return device_context;
}

XMMATRIX directx_stuff::get_proj_matrix()
{
	return proj_matrix;
}

XMMATRIX directx_stuff::get_world_matrix()
{
	return world_matrix;
}

XMMATRIX directx_stuff::get_ortho_matrix()
{
	return ortho_matrix;
}

ID3D11RasterizerState * GraphicsProj::directx_stuff::get_front_culling_state()
{
	return front_cull;
}

ID3D11RasterizerState * GraphicsProj::directx_stuff::get_depth_bias_state()
{
	return depth_bias;
}

ID3D11RasterizerState * GraphicsProj::directx_stuff::get_default_raster_state()
{
	return raster_state;
}

ID3D11BlendState * GraphicsProj::directx_stuff::get_transparent_state()
{
	return transparent_state;
}

ID3D11BlendState * GraphicsProj::directx_stuff::get_default_blend_state()
{
	return default_blend_state;
}

ID3D11DepthStencilView * GraphicsProj::directx_stuff::get_depth_stencil_view()
{
	return depth_stencil_view;
}

void GraphicsProj::directx_stuff::set_back_buffer_render_target()
{
	device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
}

ID3D11RasterizerState * GraphicsProj::directx_stuff::get_wire_frame_state()
{
	return wire_frame;
}
