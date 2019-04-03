#pragma once
#include "directx_stuff.h"
namespace GraphicsProj {
	class camera_stuff
	{
	public:
		camera_stuff();
		~camera_stuff();

		void move();

		void render();

		// Getters and setters
		void set_pos(float x, float y, float z);
		XMFLOAT3 get_pos();

		void set_rotation(float x, float y, float z);
		XMFLOAT3 get_rotation();

		XMMATRIX get_view_matrix();

	private:
		//Private variables
		float x_pos, y_pos, z_pos;
		float x_rot, y_rot, z_rot;

		XMMATRIX view_matrix;
		XMVECTOR DefaultForward;
		XMVECTOR DefaultRight;
		XMVECTOR camForward;
		XMVECTOR camRight;

		XMMATRIX camRotationMatrix;
		XMMATRIX groundWorld;

		float moveLeftRight;
		float moveBackForward;
		float camYaw;
		float camPitch;
	};
}
