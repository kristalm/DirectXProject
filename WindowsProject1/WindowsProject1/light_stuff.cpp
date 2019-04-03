#include "light_stuff.h"

namespace GraphicsProj
{

	light_stuff::light_stuff()
	{
	}

	void GraphicsProj::light_stuff::clean_up()
	{
	}
	light_stuff::~light_stuff()
	{
	}

	XMFLOAT4 GraphicsProj::light_stuff::get_ambient_color()
	{
		return ambient;
	}

	XMFLOAT4 GraphicsProj::light_stuff::get_diffuse_color()
	{
		return diffuse;
	}

	XMFLOAT3 GraphicsProj::light_stuff::get_direction()
	{
		return direction;
	}

	XMFLOAT4 GraphicsProj::light_stuff::get_spec_color()
	{
		return specular;
	}

	float GraphicsProj::light_stuff::get_intensity()
	{
		return intensity;
	}

	XMFLOAT4 * light_stuff::get_diffuse_array()
	{
		return diffuse_array;
	}

	XMFLOAT4 * light_stuff::get_pos_array()
	{
		return pos_array;
	}

	int light_stuff::get_instance_count()
	{
		return instance_count;
	}

	XMMATRIX light_stuff::get_ortho_matrix()
	{
		return ortho_matrix;
	}

	XMFLOAT3 light_stuff::get_look_at()
	{
		return look_at;
	}

	XMMATRIX light_stuff::get_view_matrix()
	{
		return view_matrix;
	}

	XMFLOAT3 light_stuff::get_positon()
	{
		return position;
	}

	XMMATRIX light_stuff::get_proj_matrix()
	{
		return proj;
	}

	void GraphicsProj::light_stuff::set_ambient_color(XMFLOAT4 color)
	{
		ambient = color;
	}

	void GraphicsProj::light_stuff::set_diffuse_color(XMFLOAT4 color)
	{
		diffuse = color;
	}

	void GraphicsProj::light_stuff::set_direction(XMFLOAT3 direction)
	{
		this->direction = direction;
	}

	void GraphicsProj::light_stuff::set_spec_color(XMFLOAT4 color)
	{
		specular = color;
	}

	void GraphicsProj::light_stuff::set_intensity(float intensity)
	{
		this->intensity = intensity;
	}
	void light_stuff::set_diffuse_array(XMFLOAT4 * diffuse, int size)
	{
		diffuse_array = new XMFLOAT4[size];
		diffuse_array[0].x = diffuse[0].x;
		diffuse_array[1].x = diffuse[1].x;
		diffuse_array[2].x = diffuse[2].x;
		diffuse_array[3].x = diffuse[3].x;
		diffuse_array[0].y = diffuse[0].y;
		diffuse_array[1].y = diffuse[1].y;
		diffuse_array[2].y = diffuse[2].y;
		diffuse_array[3].y = diffuse[3].y;
		diffuse_array[0].z = diffuse[0].z;
		diffuse_array[1].z = diffuse[1].z;
		diffuse_array[2].z = diffuse[2].z;
		diffuse_array[3].z = diffuse[3].z;
		diffuse_array[0].w = diffuse[0].w;
		diffuse_array[1].w = diffuse[1].w;
		diffuse_array[2].w = diffuse[2].w;
		diffuse_array[3].w = diffuse[3].w; 
	}
	void light_stuff::set_pos_array(XMFLOAT4 * pos, int size)
	{
		pos_array = new XMFLOAT4[size];

		pos_array[0].x = pos[0].x;
		pos_array[1].x = pos[1].x;
		pos_array[2].x = pos[2].x;
		pos_array[3].x = pos[3].x;

		pos_array[0].y = pos[0].y;
		pos_array[1].y = pos[1].y;
		pos_array[2].y = pos[2].y;
		pos_array[3].y = pos[3].y;

		pos_array[0].z = pos[0].z;
		pos_array[1].z = pos[1].z;
		pos_array[2].z = pos[2].z;
		pos_array[3].z = pos[3].z; 

		pos_array[0].w = pos[0].w;
		pos_array[1].w = pos[1].w;
		pos_array[2].w = pos[2].w;
		pos_array[3].w = pos[3].w;
	}
	void light_stuff::set_instance_count(int instance_count_)
	{
		instance_count = instance_count_;
	}
	void light_stuff::set_ortho_matrix(float width, float height, float depth, float near_plane)
	{
		ortho_matrix = XMMatrixOrthographicLH(width, width, near_plane, depth);
	}
	void light_stuff::set_look_at(float x, float y, float z)
	{
		look_at = { x, y, z };
	}
	void light_stuff::set_view_matrix()
	{
		XMFLOAT3 direction_;
		direction_.x = 0.0f;
		direction_.y = 1.0f;
		direction_.z = 0.0f;
		XMVECTOR pos = XMLoadFloat3(&position);

		XMVECTOR look = XMLoadFloat3(&look_at);
		XMVECTOR dir = XMLoadFloat3(&direction_);
		view_matrix = XMMatrixLookAtLH(pos, look, dir);
	}
	void light_stuff::set_positon(XMFLOAT3 pos)
	{
		position = pos;
	}
	void light_stuff::set_proj_matrix(float screen_depth, float screen_near)
	{
		auto field_of_view = static_cast<float>(XM_PI) / 2.0f;
		auto screen_aspect = 1.0f;
		proj = XMMatrixPerspectiveFovLH(field_of_view, screen_aspect, screen_near, screen_depth);
	}
	void light_stuff::set_cone(float cone_)
	{
		cone = cone_;
	}
	float light_stuff::get_cone()
	{
		return cone;
	}
	void light_stuff::set_range(float range_)
	{
		range = range_;
	}
	float light_stuff::get_range()
	{
		return range;
	}
	void light_stuff::set_att(XMFLOAT3 att_)
	{
		att = att_;
	}
	XMFLOAT3 light_stuff::get_att()
	{
		return att;
	}
}