#include "bitmap_stuff.h"

namespace GraphicsProj
{

	bitmap_stuff::bitmap_stuff()
	{

		vertex_buffer = 0;
		index_buffer = 0;
	}


	bitmap_stuff::~bitmap_stuff()
	{
	}

	bool GraphicsProj::bitmap_stuff::init(ID3D11Device * device, int screen_width, int screen_height, int bitmap_w, int bitmap_h)
	{
		this->screen_width = screen_width;
		this->screen_height = screen_height;

		bitmap_width = bitmap_w;
		bitmap_height = bitmap_h;

		prev_posx = -1;
		prev_posy = -1;

		cbuffer_struct* vertices;
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;
		int i;


		// Set the number of vertices in the vertex array.
		vertex_count = 6;

		// Set the number of indices in the index array.
		index_count = vertex_count;

		// Create the vertex array.
		vertices = new cbuffer_struct[vertex_count];
		if (!vertices)
		{
			return false;
		}

		// Create the index array.
		indices = new unsigned long[index_count];
		if (!indices)
		{
			return false;
		}

		// Initialize vertex array to zeros at first.
		memset(vertices, 0, (sizeof(cbuffer_struct) * vertex_count));

		// Load the index array with data.
		for (i = 0; i<index_count; i++)
		{
			indices[i] = i;
		}

		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(cbuffer_struct) * vertex_count;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer.
		result = device->CreateBuffer(&vertexBufferDesc , &vertexData , &vertex_buffer);
		if (FAILED(result))
		{
			return false;
		}

		// Set up the description of the static index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * index_count;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		result = device->CreateBuffer(&indexBufferDesc,&indexData , &index_buffer);
		if (FAILED(result))
		{
			return false;
		}

		// Release the arrays now that the vertex and index buffers have been created and loaded.
		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;

		return true;
	}

	bool GraphicsProj::bitmap_stuff::render(ID3D11DeviceContext * device_context, int posx, int posy)
	{
		float left, right, top, bottom;
		cbuffer_struct* vertices;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		cbuffer_struct* verticesPtr;
		HRESULT result;


		// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
		// currently has the correct parameters.
		if ((posx == prev_posx) && (posy == prev_posy))
		{
			return true;
		}

		// If it has changed then update the position it is being rendered to.
		prev_posx = posx;
		prev_posy = posy;

		// Calculate the screen coordinates of the left side of the bitmap.
		left = (float)((screen_width / 2) * -1) + (float)posx;

		// Calculate the screen coordinates of the right side of the bitmap.
		right = left + (float)bitmap_width;

		// Calculate the screen coordinates of the top of the bitmap.
		top = (float)(screen_height / 2) - (float)posy;

		// Calculate the screen coordinates of the bottom of the bitmap.
		bottom = top - (float)bitmap_height;

		// Create the vertex array.
		vertices = new cbuffer_struct[vertex_count];
		if (!vertices)
		{
			return false;
		}

		// Load the vertex array with data.
		// First triangle.
		vertices[0].pos = { left, top, 0.0f };  // Top left.
		vertices[0].text = { 0.0f, 0.0f };

		vertices[1].pos = { right, bottom, 0.0f };  // Bottom right.
		vertices[1].text = { 1.0f, 1.0f };

		vertices[2].pos = { left, bottom, 0.0f };  // Bottom left.
		vertices[2].text = { 0.0f, 1.0f };

		// Second triangle.
		vertices[3].pos = { left, top, 0.0f };  // Top left.
		vertices[3].text = { 0.0f, 0.0f };

		vertices[4].pos = { right, top, 0.0f };  // Top right.
		vertices[4].text = { 1.0f, 0.0f };

		vertices[5].pos = { right, bottom, 0.0f };  // Bottom right.
		vertices[5].text = { 1.0f, 1.0f };

		// Lock the vertex buffer so it can be written to.
		result = device_context->Map(vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			return false;
		}

		// Get a pointer to the data in the vertex buffer.
		verticesPtr = (cbuffer_struct*)mappedResource.pData;

		// Copy the data into the vertex buffer.
		memcpy(verticesPtr, (void*)vertices, (sizeof(cbuffer_struct) * vertex_count));

		// Unlock the vertex buffer.
		device_context->Unmap(vertex_buffer, 0);

		// Release the vertex array as it is no longer needed.
		delete[] vertices;
		vertices = 0;

		unsigned int stride;
		unsigned int offset;


		// Set vertex buffer stride and offset.
		stride = sizeof(cbuffer_struct);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride , &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}

	void GraphicsProj::bitmap_stuff::init_info(XMFLOAT3 light_direction, XMFLOAT4 diffuse_color)
	{
	}

	int bitmap_stuff::get_index_count()
	{
		return index_count;
	}

	void GraphicsProj::bitmap_stuff::clean_up()
	{
		vertex_buffer->Release();
		index_buffer->Release();
	}
}