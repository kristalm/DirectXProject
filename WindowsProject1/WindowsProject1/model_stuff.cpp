#include "model_stuff.h"
#include "DDSTextureLoader.h"
#include "defines.h"

using namespace GraphicsProj;
model_stuff::model_stuff()
{
	vertex_buffer = 0;
	index_buffer = 0;
	//vertex_count = 0;
	index_count = 0;
	texture = 0;
	texture1 = 0;
	texture2 = 0;
	textures[0] = 0;
	textures[1] = 0;
	instance_buffer = 0;
}


model_stuff::~model_stuff()
{
	
}

bool model_stuff::init(ID3D11Device * device)
{
	HRESULT check;
	vertex_count = 3;
	index_count = 3;

//Create structs to hold information
	vertex_struct* verts = new vertex_struct[3];
	unsigned int* indices = new unsigned int[3];

//Fill out information
	verts[0].pos = {-1.0f, -1.0f, 0.0f};
	verts[0].color = {0.0f, 1.0f, 0.0f, 1.0f};
	verts[1].pos = {0.0f, 1.0f, 0.0f};
	verts[1].color = {0.0f, 1.0f, 0.0f, 1.0f};
	verts[2].pos = {1.0f, -1.0f, 0.0f};
	verts[2].color = {0.0f, 1.0f, 0.0f, 1.0f};

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

//Create buffer descs
	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;

//Fill out descs
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(vertex_struct) * vertex_count; //sizeof(struct type)
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int) * index_count;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

//Create subresource structure
	D3D11_SUBRESOURCE_DATA vertex_data;
	D3D11_SUBRESOURCE_DATA index_data;

//fill out subresource data
	vertex_data.pSysMem = verts;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

//Create buffers
	check = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
	if(FAILED(check)) return false;

	check = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
	if(FAILED(check)) return false;

//Clean up 
	/*delete [] verts;
	verts = 0;
	delete [] indices;
	indices = 0;*/
	return true;
}
bool model_stuff::init2(ID3D11Device * device)
{
	HRESULT check;
	vertex_count = 3;
	index_count = 3;

//Create structs to hold information
	texture_struct* verts = new texture_struct[3];
	unsigned int* indices = new unsigned int[3];

//Fill out information
	verts[0].pos = {-1.0f, -1.0f, 0.0f};
	verts[0].text = {0.0f, 1.0f};
	verts[1].pos = {0.0f, 1.0f, 0.0f};
	verts[1].text = {0.5f, 0.0f};
	verts[2].pos = {1.0f, -1.0f, 0.0f};
	verts[2].text = {1.0f, 1.0f};

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

//Create buffer descs
	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;

//Fill out descs
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(vertex_struct) * vertex_count; //sizeof(struct type)
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int) * index_count;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

//Create subresource structure
	D3D11_SUBRESOURCE_DATA vertex_data;
	D3D11_SUBRESOURCE_DATA index_data;

//fill out subresource data
	vertex_data.pSysMem = verts;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

//Create buffers
	check = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
	if(FAILED(check)) return false;

	check = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
	if(FAILED(check)) return false;

//Clean up 
	/*delete [] verts;
	verts = 0;
	delete [] indices;
	indices = 0;*/
	return true;
}

void model_stuff::render(ID3D11DeviceContext * device_context)
{
	unsigned int stride, offset;

//Set stride
	stride = sizeof(vertex_struct);
	offset = 0;

//Activate vertex & index buffers
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

//Set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void model_stuff::render2(ID3D11DeviceContext * device_context)
{
	unsigned int stride, offset;

//Set stride
	stride = sizeof(texture_struct);
	offset = 0;

//Activate vertex & index buffers
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

//Set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool model_stuff::init3(ID3D11Device * device)
{
	HRESULT check;
	vertex_count = 3;
	index_count = 3;

//Create structs to hold information
	light_struct* verts = new light_struct[3];
	auto indices = new unsigned int[3];

//Fill out information
	verts[0].pos = {-1.0f, -1.0f, 0.0f};
	verts[0].text = {0.0f, 1.0f};
	verts[0].norm = {0.0f, 0.0f, -1.0f};

	verts[1].pos = {0.0f, 1.0f, 0.0f};
	verts[1].text = {0.5f, 0.0f};
	verts[1].norm = {0.0f, 0.0f, -1.0f};

	verts[2].pos = {1.0f, -1.0f, 0.0f};
	verts[2].text = {1.0f, 1.0f};
	verts[2].norm = {0.0f, 0.0f, -1.0f};

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

//Create buffer descs
	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;

//Fill out descs
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(light_struct) * vertex_count; //sizeof(struct type)
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int) * index_count;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

//Create subresource structure
	D3D11_SUBRESOURCE_DATA vertex_data;
	D3D11_SUBRESOURCE_DATA index_data;

//fill out subresource data
	vertex_data.pSysMem = verts;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

//Create buffers
	check = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
	if(FAILED(check)) return false;

	check = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
	if(FAILED(check)) return false;

//Clean up 
	delete[] indices;
	delete[] verts;
	return true;
}

void model_stuff::render3(ID3D11DeviceContext * device_context)
{
	unsigned int stride, offset;

//Set stride
	stride = sizeof(light_struct);
	offset = 0;

//Activate vertex & index buffers
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

//Set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void model_stuff::load_model(light_struct* model, LPCWSTR fn)
{
	auto model_stuff = stuff->load_object(fn);
	int vertex_count = stuff->get_index_count();
	for (size_t i = 0; i < vertex_count; i++)
	{
		model[i].pos.x = model_stuff[i].pos.x;
		model[i].pos.y = model_stuff[i].pos.y;
		model[i].pos.z = model_stuff[i].pos.z;
		model[i].text.x = model_stuff[i].text.x;
		model[i].text.y = model_stuff[i].text.y;
		model[i].norm.x = model_stuff[i].norm.x;
		model[i].norm.y = model_stuff[i].norm.y;
		model[i].norm.z = model_stuff[i].norm.z;

	}
	delete model_stuff;
}

bool model_stuff::init4(ID3D11Device* device, LPCWSTR fn)
{
	HRESULT check;
	vertex_count = 3;
	index_count = 3;

	//Create structs to hold information
	stuff = new loader_stuff;

	//Fill out information
	stuff->get_counts(fn);
	int vertex = stuff->get_index_count();
	vertex_count = vertex;
	index_count = vertex;
	light_struct* verts = new light_struct[vertex];

	load_model(verts, fn);

	auto indices = new unsigned int[vertex];

	for (int i = 0; i < vertex; i++)
		indices[i] = i;

	//Create buffer descs
	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;

	//Fill out descs
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(light_struct) * vertex_count; //sizeof(struct type)
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int) * index_count;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	//Create subresource structure
	D3D11_SUBRESOURCE_DATA vertex_data;
	D3D11_SUBRESOURCE_DATA index_data;

	//fill out subresource data
	vertex_data.pSysMem = verts;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

	//Create buffers
	check = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
	if (FAILED(check)) return false;

	check = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
	if (FAILED(check)) return false;

	//Clean up 
	delete[] indices;

	delete stuff;
	stuff = 0;

	delete[] verts;
	return true;
}

void model_stuff::render4(ID3D11DeviceContext* device_context)
{
	unsigned int stride, offset;

	//Set stride
	stride = sizeof(light_struct);
	offset = 0;

	//Activate vertex & index buffers
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	//Set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void model_stuff::init5(ID3D11Device* device, LPCWSTR fn, int instance_count_, XMFLOAT3 positions[])
{
	HRESULT check;
	vertex_count = 3;
	index_count = 3;
	instance_count = instance_count_;

	
	//Create structs to hold information
	stuff = new loader_stuff;

	//Fill out information
	stuff->get_counts(fn);
	int vertex = stuff->get_index_count();
	vertex_count = vertex;
	index_count = vertex;
	light_struct* verts = new light_struct[vertex];

	load_model(verts, fn);

	auto indices = new unsigned int[vertex];

	for (int i = 0; i < vertex; i++)
		indices[i] = i;
	
	instances = new instance_struct[instance_count];

	for (size_t i = 0; i < instance_count; i++)
	{
		instances[i].position.x = positions[i].x;
		instances[i].position.y = positions[i].y;
		instances[i].position.z = positions[i].z;
	}

	//Create buffer descs
	D3D11_BUFFER_DESC vertex_buffer_desc;
	D3D11_BUFFER_DESC index_buffer_desc;
	D3D11_BUFFER_DESC instance_buffer_desc;
	//Fill out descs
	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	vertex_buffer_desc.ByteWidth = sizeof(light_struct) * vertex_count; //sizeof(struct type)
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = 0;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned int) * index_count;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	instance_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	instance_buffer_desc.ByteWidth = sizeof(instance_struct) * instance_count;
	instance_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instance_buffer_desc.CPUAccessFlags = 0;
	instance_buffer_desc.MiscFlags = 0;
	instance_buffer_desc.StructureByteStride = 0;

	//Create subresource structure
	D3D11_SUBRESOURCE_DATA vertex_data;
	D3D11_SUBRESOURCE_DATA index_data;
	D3D11_SUBRESOURCE_DATA instance_data;

	//fill out subresource data
	vertex_data.pSysMem = verts;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

	instance_data.pSysMem = instances;
	instance_data.SysMemPitch = 0;
	instance_data.SysMemSlicePitch = 0;

	//Create buffers
	check = device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer);
	if (FAILED(check)) return;

	check = device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer);
	if (FAILED(check)) return;

	check = device->CreateBuffer(&instance_buffer_desc, &instance_data, &instance_buffer);
	if (FAILED(check)) return;

	//Clean up 
	delete[] indices;

	delete stuff;
	stuff = 0;

	delete[] verts;
	
	delete[] instances;
	instances = 0;
}
void model_stuff::render5(ID3D11DeviceContext* device_context)
{
	unsigned int stride[2], offset[2];
	ID3D11Buffer * buffer_ptrs[2];

	//Set stride
	stride[1] = sizeof(instance_struct);
	stride[0] = sizeof(light_struct);
	offset[0] = 0;
	offset[1] = 0;

	//create ptr holders
	buffer_ptrs[0] = vertex_buffer;
	buffer_ptrs[1] = instance_buffer;

	//Activate vertex & index buffers
	device_context->IASetVertexBuffers(0, 2, buffer_ptrs, stride, offset);
	device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

	//Set topology
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void model_stuff::init_texture(ID3D11Device * device, LPCWSTR fn)
{
	CreateDDSTextureFromFile(device, fn, &texture_source,&texture);
}

void GraphicsProj::model_stuff::init_textures(ID3D11Device * device, LPCWSTR fn, LPCWSTR fn1)
{
	
	HRESULT check = CreateDDSTextureFromFile(device, fn, &texture_source, &texture1);
	check = CreateDDSTextureFromFile(device, fn1, &texture_source, &texture2);
	textures[0] = texture1;
	textures[1] = texture2;
	
}

ID3D11ShaderResourceView * model_stuff::get_texture()
{
	return texture;
}

ID3D11ShaderResourceView** GraphicsProj::model_stuff::get_textures()
{
	return textures;
}

void GraphicsProj::model_stuff::set_pos(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

XMFLOAT3 GraphicsProj::model_stuff::get_pos()
{
	return position;
}

int model_stuff::get_index_count()
{
	return index_count;
}

void model_stuff::clean_up()
{
	vertex_buffer->Release();
	vertex_buffer = 0;

	index_buffer->Release();
	index_buffer = 0;

	if (texture != NULL)
	texture->Release();
	texture = 0;

	if (instance_buffer != NULL)
	instance_buffer->Release();
}