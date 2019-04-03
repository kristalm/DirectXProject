#include "render_2_texture_stuff.h"
using namespace DirectX;
namespace GraphicsProj
{

	render_2_texture_stuff::render_2_texture_stuff()
	{
		render_target_texture_ = nullptr;
		render_target_view_ = nullptr;
		shader_resource_view_ = nullptr;
		stencil_buffer_ = nullptr;
		stencil_view_ = nullptr;
	}


	render_2_texture_stuff::~render_2_texture_stuff()
	{
	}

	bool GraphicsProj::render_2_texture_stuff::init(ID3D11Device * device, int texture_width, int texture_height)
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		HRESULT result;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;


		// Initialize the render target texture description.
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		// Setup the render target texture description.
		textureDesc.Width = texture_width;
		textureDesc.Height = texture_height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		// Create the render target texture.
		result = device->CreateTexture2D(&textureDesc, NULL, &render_target_texture_);
		if (FAILED(result))
		{
			return false;
		}

		// Setup the description of the render target view.
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		// Create the render target view.
		result = device->CreateRenderTargetView(render_target_texture_, &renderTargetViewDesc, &render_target_view_);
		if (FAILED(result))
		{
			return false;
		}

		// Setup the description of the shader resource view.
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		result = device->CreateShaderResourceView(render_target_texture_, &shaderResourceViewDesc, &shader_resource_view_);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	void GraphicsProj::render_2_texture_stuff::clean_up()
	{
		if (stencil_view_)
		{
			stencil_view_->Release();
			stencil_view_ = nullptr;
		}

		if (stencil_buffer_)
		{
			stencil_buffer_->Release();
			stencil_buffer_ = nullptr;
		}

		if (shader_resource_view_)
		{
			shader_resource_view_->Release();
			shader_resource_view_ = nullptr;
		}

		if (render_target_view_)
		{
			render_target_view_->Release();
			render_target_view_ = nullptr;
		}

		if (render_target_texture_)
		{
			render_target_texture_->Release();
			render_target_texture_ = nullptr;
		}

		return;
	}

	ID3D11ShaderResourceView * render_2_texture_stuff::get_resource_view()
	{
		return shader_resource_view_;
	}

	void GraphicsProj::render_2_texture_stuff::set_render_target(ID3D11DeviceContext * device, ID3D11DepthStencilView* stencil_view) const
	{
		device->OMSetRenderTargets(1, &render_target_view_, stencil_view);

		return;
	}

	void GraphicsProj::render_2_texture_stuff::clear_render(ID3D11DeviceContext *device, ID3D11DepthStencilView* stencil_view) const
	{
		float color[4];


		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 1.0f;
		color[3] = 0.0f;

		device->ClearRenderTargetView(render_target_view_, color);

		device->ClearDepthStencilView(stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

		return;
	}

	XMMATRIX GraphicsProj::render_2_texture_stuff::get_proj_matrix() const
	{
		return proj_matrix_;
	}

	XMMATRIX GraphicsProj::render_2_texture_stuff::get_ortho_matrix() const
	{
		return ortho_matrix_;
	}
}