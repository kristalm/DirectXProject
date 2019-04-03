#include "instance_shader_stuff.h"

namespace GraphicsProj
{

	instance_shader_stuff::instance_shader_stuff()
	{
		vertex_shader = 0;
		pixel_shader = 0;
		layout = 0;
		cbuffer = 0;
		sample_state = 0;
		light_buffer = 0;
	}


	instance_shader_stuff::~instance_shader_stuff()
	{
	}

	bool instance_shader_stuff::init(ID3D11Device * device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn)
	{
		HRESULT check;
		ID3D10Blob *vertex_shader_blob, *pixel_shader_blob, *error_message;
		vertex_shader_blob = { 0 };
		pixel_shader_blob = { 0 };
		error_message = { 0 };
		check = D3DCompileFromFile(vs_fn, 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertex_shader_blob, &error_message);
		if (FAILED(check))
		{
			// If the shader failed to compile it should have writen something to the error message.
			if (error_message)
			{
				auto error = (char*)error_message->GetBufferPointer();
				return false;
			}

		}

		check = D3DCompileFromFile(ps_fn, 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixel_shader_blob, &error_message);
		if (FAILED(check))
		{
			// If the shader failed to compile it should have writen something to the error message.
			if (error_message)
			{
				auto error = (char*)error_message->GetBufferPointer();
				return false;
			}


			return false;
		}

		device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &vertex_shader);
		device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &pixel_shader);

		D3D11_INPUT_ELEMENT_DESC layout_[4] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 1, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1}
		};
		check = device->CreateInputLayout(layout_, 4, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &layout);
		if (FAILED(check))
			return false;
		vertex_shader_blob->Release();
		pixel_shader_blob->Release();

		D3D11_SAMPLER_DESC texture_sampler_desc;
		texture_sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		texture_sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		texture_sampler_desc.BorderColor[0] = 0;
		texture_sampler_desc.BorderColor[1] = 0;
		texture_sampler_desc.BorderColor[2] = 0;
		texture_sampler_desc.BorderColor[3] = 0;
		texture_sampler_desc.MinLOD = 0;
		texture_sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
		texture_sampler_desc.MaxAnisotropy = 1;
		texture_sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		texture_sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		texture_sampler_desc.MipLODBias = 0.0f;
		texture_sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		device->CreateSamplerState(&texture_sampler_desc, &sample_state);

		D3D11_BUFFER_DESC cbuffer_desc;
		cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		cbuffer_desc.ByteWidth = sizeof(cbuffer_struct);
		cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbuffer_desc.MiscFlags = 0;
		cbuffer_desc.StructureByteStride = 0;

		device->CreateBuffer(&cbuffer_desc, NULL, &cbuffer);


		D3D11_BUFFER_DESC light_buffer_desc;
		light_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		light_buffer_desc.ByteWidth = sizeof(light_struct);
		light_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		light_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		light_buffer_desc.MiscFlags = 0;
		light_buffer_desc.StructureByteStride = 0;

		device->CreateBuffer(&light_buffer_desc, NULL, &light_buffer);

		return true;
	}

	bool instance_shader_stuff::render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj, ID3D11ShaderResourceView * texture)
	{
		HRESULT check;

		world = XMMatrixTranspose(world);
		view = XMMatrixTranspose(view);
		proj = XMMatrixTranspose(proj);

		D3D11_MAPPED_SUBRESOURCE mapped_subresource;
		check = device_context->Map(cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
		if (FAILED(check)) return false;

		cbuffer_struct* data;
		data = (cbuffer_struct*)mapped_subresource.pData;
		data->world = world;
		data->view = view;
		data->proj = proj;

		device_context->Unmap(cbuffer, 0);

		device_context->VSSetConstantBuffers(0, 1, &cbuffer);
		device_context->PSSetShaderResources(0, 1, &texture);

		D3D11_MAPPED_SUBRESOURCE mapped_subresource1;
		check = device_context->Map(light_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource1);
		if (FAILED(check))
			return false;
		light_struct* data2;
		data2 = (light_struct*)mapped_subresource1.pData;

		data2->diffuse_color = info->get_diffuse_color();
		data2->direction = info->get_direction();
		data2->padding = 0.0f;

		device_context->Unmap(light_buffer, 0);

		device_context->PSSetConstantBuffers(0, 1, &light_buffer);

		device_context->IASetInputLayout(layout);

		device_context->VSSetShader(vertex_shader, NULL, 0);
		device_context->PSSetShader(pixel_shader, NULL, 0);

		device_context->PSSetSamplers(0, 1, &sample_state);
		//device_context->DrawIndexed(index_count, 0, 0);

		device_context->DrawIndexedInstanced(index_count, info->get_instance_count(), 0, 0, 0);


		return true;
	}

	void instance_shader_stuff::init_info(XMFLOAT3 light_direction, XMFLOAT4 diffuse_color, int instance_count)
	{
		info = new light_stuff;
		info->set_diffuse_color(diffuse_color);
		info->set_direction(light_direction);
		info->set_instance_count(instance_count);
	}

	void instance_shader_stuff::clean_up()
	{
		vertex_shader->Release();
		pixel_shader->Release();
		layout->Release();
		cbuffer->Release();
		sample_state->Release();
		light_buffer->Release();
		delete info;
	}
}