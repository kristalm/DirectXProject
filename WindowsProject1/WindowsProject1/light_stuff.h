#pragma once
#include "directx_stuff.h"

namespace GraphicsProj
{
	class light_stuff
	{
	public:
		light_stuff();
		~light_stuff();

		void clean_up();

		//getters
		XMFLOAT4 get_ambient_color();
		XMFLOAT4 get_diffuse_color();
		XMFLOAT3 get_direction();
		XMFLOAT4 get_spec_color();
		float get_intensity();
		XMFLOAT4* get_diffuse_array();
		XMFLOAT4* get_pos_array();
		int get_instance_count();
		XMMATRIX get_ortho_matrix();
		XMFLOAT3 get_look_at();
		XMMATRIX get_view_matrix();
		XMFLOAT3 get_positon();
		XMMATRIX get_proj_matrix();

		//setters
		void set_ambient_color(XMFLOAT4 color);
		void set_diffuse_color(XMFLOAT4 color);
		void set_direction(XMFLOAT3 direction);
		void set_spec_color(XMFLOAT4 color);
		void set_intensity(float intensity);
		void set_diffuse_array(XMFLOAT4* diffuse, int size);
		void set_pos_array(XMFLOAT4* pos, int size);
		void set_instance_count(int instance_count_);
		void set_ortho_matrix(float width, float height, float depth, float near_plane);
		void set_look_at(float x, float y, float z);
		void set_view_matrix();
		void set_positon(XMFLOAT3 pos);
		void set_proj_matrix(float screen_depth, float screen_near);

		void set_cone(float cone_);

		float get_cone();

		void set_range(float range_);

		float get_range();

		void set_att(XMFLOAT3 att_);

		XMFLOAT3 get_att();

	private:
		//private variables
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		XMFLOAT4 specular;
		float intensity;
		XMFLOAT4* diffuse_array;
		XMFLOAT4* pos_array;
		XMMATRIX ortho_matrix;
		int instance_count;
		XMMATRIX view_matrix;
		XMFLOAT3 position;
		XMFLOAT3 look_at;
		XMMATRIX proj;
		float range;
		float cone;
		XMFLOAT3 att;

	};
}
