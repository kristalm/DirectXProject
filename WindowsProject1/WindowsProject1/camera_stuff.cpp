#include "camera_stuff.h"
#include "defines.h"

using namespace GraphicsProj;

camera_stuff::camera_stuff()
{
	x_pos = 0;
	y_pos= 0;
	z_pos = 0;
	x_rot = 0;
	y_rot = 0;
	z_rot = 0;
}


camera_stuff::~camera_stuff()
{
}
void camera_stuff::move()
{
	
}
void camera_stuff::render()
{

	//look up
	if (GetAsyncKeyState(VK_UP))
		x_rot -= 0.005f;
	if (x_rot > 90.0f)
		x_rot = 90.0f;

	//look down
	if (GetAsyncKeyState(VK_DOWN))
		x_rot += 0.005f;
	if (x_rot < -90.0f)
		x_rot = -90.0f;

	//turn right
	if (GetAsyncKeyState(VK_LEFT))
		y_rot += 0.005f;
	if (y_rot > 360.0f)
		y_rot -= 360.0f;

	//turn left
	if (GetAsyncKeyState(VK_RIGHT))
		y_rot -= 0.005f;
	if (y_rot < 0.0f)
		y_rot += 360.0f;

	//move down
	if (GetAsyncKeyState('S'))
		y_pos -= 0.0005f;

	//move up
	if (GetAsyncKeyState('W'))
		y_pos += 0.0005f;

	//move left
	if (GetAsyncKeyState('A'))
		x_pos -= 0.0005f;

	//move right
	if (GetAsyncKeyState('D'))
		x_pos += 0.0005f;

	//move back
	if (GetAsyncKeyState('N'))
	{
		z_pos += 0.01f;
	}
	if (GetAsyncKeyState('M'))
	{
		z_pos -= 0.01f;
	}
	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rot_matrix;
	

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = x_pos;
	position.y = y_pos;
	position.z = z_pos;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = x_rot * 0.0174532925f;
	yaw   = y_rot * 0.0174532925f;
	roll  = z_rot * 0.0174532925f;

	rot_matrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	auto lookat1 = XMLoadFloat3(&lookAt);
	auto up1 = XMLoadFloat3(&up);
	 lookat1 = XMVector3TransformCoord(lookat1, rot_matrix);
	 up1 = XMVector3TransformCoord(up1, rot_matrix);

	 auto pos1 = XMLoadFloat3(&position);

	lookat1 = pos1 + lookat1;

	view_matrix = XMMatrixLookAtLH(pos1, lookat1, up1);
	
	return;
}

void camera_stuff::set_pos(float x, float y, float z)
{
	x_pos = x;
	y_pos = y;
	z_pos = z;
}

XMFLOAT3 camera_stuff::get_pos()
{
	return {x_pos, y_pos, z_pos};
}

void camera_stuff::set_rotation(float x, float y, float z)
{
	x_rot = x;
	y_rot = y;
	z_rot = z;
}

XMFLOAT3 camera_stuff::get_rotation()
{
	return {x_rot, y_rot, z_rot};
}

XMMATRIX camera_stuff::get_view_matrix()
{
	return view_matrix;
}
