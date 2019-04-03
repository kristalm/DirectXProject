#pragma once
#include "directx_stuff.h"

namespace GraphicsProj
{
	class render_2_texture_stuff
	{
	public:
		render_2_texture_stuff();
		~render_2_texture_stuff();

		bool init(ID3D11Device*, int, int);
		void clean_up();
		ID3D11ShaderResourceView* get_resource_view();
		void set_render_target(ID3D11DeviceContext*, ID3D11DepthStencilView* stencil_view) const;
		void clear_render(ID3D11DeviceContext*, ID3D11DepthStencilView* stencil_view) const;
		XMMATRIX get_proj_matrix() const;
		XMMATRIX get_ortho_matrix() const;

	private:
		ID3D11Texture2D * render_target_texture_{};
		ID3D11RenderTargetView* render_target_view_{};
		ID3D11ShaderResourceView* shader_resource_view_{};
		ID3D11Texture2D* stencil_buffer_{};
		ID3D11DepthStencilView* stencil_view_{};
		D3D11_VIEWPORT viewport_{};
		XMMATRIX proj_matrix_;
		XMMATRIX ortho_matrix_;
	};
}
