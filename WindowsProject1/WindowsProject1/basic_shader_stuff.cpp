#include "basic_shader_stuff.h"
#include "defines.h"

using namespace GraphicsProj;

basic_shader_stuff::basic_shader_stuff()
{
	vertex_shader = 0;
	pixel_shader = 0;
	layout = 0;
	cbuffer = 0;
}


basic_shader_stuff::~basic_shader_stuff()
{

}

bool basic_shader_stuff::init(ID3D11Device * device, HWND hwnd, LPCWSTR vs_fn, LPCWSTR ps_fn)
{
	ID3D10Blob *vertex_shader_blob, *pixel_shader_blob, *error_message;
	D3DCompileFromFile(vs_fn, 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG, 0, &vertex_shader_blob, &error_message );
	if (error_message != NULL)
	{
		auto errors = (char*)(error_message->GetBufferPointer());
		return false;
	}

	D3DCompileFromFile(vs_fn, 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG, 0, &pixel_shader_blob, &error_message );
	if (error_message != NULL)
	{
		auto errors = (char*)(error_message->GetBufferPointer());
		return false;
	}

	device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &vertex_shader);
	device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &pixel_shader);

	D3D11_INPUT_ELEMENT_DESC layout_desc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	device->CreateInputLayout(layout_desc, 2, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &layout);

	vertex_shader_blob->Release();
	pixel_shader_blob->Release();

	D3D11_BUFFER_DESC cbuffer_desc;
	cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	cbuffer_desc.ByteWidth = sizeof(cbuffer_struct);
	cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbuffer_desc.MiscFlags = 0;
	cbuffer_desc.StructureByteStride = 0;

	device->CreateBuffer(&cbuffer_desc, NULL, &cbuffer);

	return true;
}

bool basic_shader_stuff::render(ID3D11DeviceContext * device_context, int index_count, XMMATRIX world, XMMATRIX view, XMMATRIX proj)
{
	HRESULT check;
	world= XMMatrixTranspose(world);
	view= XMMatrixTranspose(view);
	proj= XMMatrixTranspose(proj);

	D3D11_MAPPED_SUBRESOURCE mapped_subresource;
	check = device_context->Map(cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
	if(FAILED(check)) return false;

	cbuffer_struct* data;
	data = (cbuffer_struct*)mapped_subresource.pData;
	data->world = world;
	data->view = view;
	data->proj = proj;

	device_context->Unmap(cbuffer, 0);

	device_context->VSSetConstantBuffers(0, 1, &cbuffer);

	device_context->IASetInputLayout(layout);

	device_context->VSSetShader(vertex_shader,NULL, 0);
	device_context->PSSetShader(pixel_shader, NULL, 0);

	device_context->DrawIndexed(index_count, 0, 0);
	return true;
}

void GraphicsProj::basic_shader_stuff::clean_up()
{
	vertex_shader->Release();
	vertex_shader = 0;
	pixel_shader->Release();
	pixel_shader = 0;
	layout->Release();
	layout = 0;
	cbuffer->Release();
	cbuffer = 0;
}
