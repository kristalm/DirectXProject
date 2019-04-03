#pragma once
#include "directx_stuff.h"
#include "loader_stuff.h"
namespace GraphicsProj {
	class model_stuff
	{
	public:
		model_stuff();
		~model_stuff();
		struct vertex_struct
		{
			XMFLOAT3 pos;
			XMFLOAT4 color;
		};
		struct texture_struct
		{
			XMFLOAT3 pos;
			XMFLOAT2 text;
		};
		struct light_struct
		{
			XMFLOAT3 pos;
			XMFLOAT2 text;
			XMFLOAT3 norm;
		};
		struct instance_struct
		{
			XMFLOAT3 position;
		};
		//functions
		bool init(ID3D11Device* device);
		void render(ID3D11DeviceContext* device_context);
		bool init2(ID3D11Device* device);
		void render2(ID3D11DeviceContext* device_context);
		bool init3(ID3D11Device* device);
		void render3(ID3D11DeviceContext* device_context);
		void load_model(light_struct* model, LPCWSTR fn);
		bool init4(ID3D11Device* device, LPCWSTR fn);
		void render4(ID3D11DeviceContext* device_context);

		void init5(ID3D11Device * device, LPCWSTR fn, int instance_count_, XMFLOAT3 * positions);

		void render5(ID3D11DeviceContext * device_context);

		void clean_up();

		void init_texture(ID3D11Device* device, LPCWSTR fn);
		void init_textures(ID3D11Device* device, LPCWSTR fn, LPCWSTR fn1);
		

		//Getters and setters
		int get_index_count();
		int get_instance_count();
		ID3D11ShaderResourceView* get_texture();

		ID3D11ShaderResourceView** get_textures();

		void set_pos(float x, float y, float z);
		XMFLOAT3 get_pos();
	private:
		//Private variables
		ID3D11Buffer * vertex_buffer;
		ID3D11Buffer* index_buffer;
		int vertex_count;
		int index_count;

		XMFLOAT3 position;

		ID3D11ShaderResourceView* texture;
		ID3D11Resource* texture_source;

		ID3D11ShaderResourceView* texture1;
		ID3D11ShaderResourceView* texture2;

		ID3D11ShaderResourceView* textures[2];

		XMFLOAT4 diffuse_color;
		XMFLOAT3 light_direction;

		loader_stuff* stuff;

		ID3D11Buffer* instance_buffer;
		int instance_count;

		instance_struct* instances;
	};
}

