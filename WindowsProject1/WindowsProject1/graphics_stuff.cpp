#include "graphics_stuff.h"
#include "defines.h"



using namespace GraphicsProj;
graphics_stuff::graphics_stuff()
{
//classes
	camera_handle = {0};
	render_texture = { 0 };

//models

	model1 = {0};

	model2 = {0};

	model3 = {0};

	model4 = { 0 };

	model5 = { 0 };

	model6 = { 0 };

	model7 = { 0 };

	model8 = { 0 };

	model9 = { 0 };

	model10 = { 0 };
	model11 = { 0 };
	model12 = { 0 };

	model13 = { 0 };

	model14 = { 0 };

//shaders

	basic_shader = {0};

	texture_shader = {0};

	light_shader = {0};

	model4_light_shader = { 0 };

	ambient_shader = { 0 };

	specular_shader = { 0 };

	multi_shader = { 0 };

	spot_shader = { 0 };

	instance_shader = { 0 };


	render_texture = { 0 };
	light_shader1 = { 0 };
	texture_shader1 = { 0 };

}


graphics_stuff::~graphics_stuff()
{


}

bool graphics_stuff::init(HWND hwnd)
{
	bool check;
	this->directx_handle = new directx_stuff;
//Init classes
	directx_handle->init(hwnd, 800, 800, 1000, 0.1f);

	camera_handle = new camera_stuff;
	camera_handle->set_pos(0, 0, -10.0f);

	
//Init models


	model3 = new model_stuff;
	model3->init4(directx_handle->get_device(), L"../WindowsProject1/data/cube.obj");
	model3->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/ice.dds");


	model4 = new model_stuff;
	model4->init4(directx_handle->get_device(), L"../WindowsProject1/data/pyramid.obj");
	model4->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/ice.dds");


	model5 = new model_stuff;
	model5->init4(directx_handle->get_device(), L"../WindowsProject1/data/PlanetFBX.obj");
	model5->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/ice.dds");


	model6 = new model_stuff;
	model6->init4(directx_handle->get_device(), L"../WindowsProject1/data/star.obj");
	model6->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/ice.dds");


	model7 = new model_stuff;
	model7->init4(directx_handle->get_device(), L"../WindowsProject1/data/Asteroidobj.obj");
	model7->init_textures(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds", L"../WindowsProject1/data/metal001.dds");

	//model8 = new model_stuff;
	//model8->init4(directx_handle->get_device(), L"../WindowsProject1/data/plane2.obj");
	//model8->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds");

	model9 = new model_stuff;
	XMFLOAT3 pos1 = {0.0f, 3.0f, 0.0f};
	XMFLOAT3 pos2 = {3.0f, 0.0f, 0.0f};
	XMFLOAT3 pos3 = {-3.0f, 0.0f, 0.0f};
	XMFLOAT3 pos4 = {0.0f, -3.0f, 0.0f};
	XMFLOAT3 pos[4] = { pos1, pos2, pos3, pos4 };
	model9->init5(directx_handle->get_device(), L"../WindowsProject1/data/cube.obj", 4, pos);
	model9->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds");



	model14 = new model_stuff;
	model14->init4(directx_handle->get_device(), L"../WindowsProject1/data/cube.obj");
	model14->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds");

	model16 = new model_stuff;
	model16->init4(directx_handle->get_device(), L"../WindowsProject1/data/cube.obj");
	model16->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds");

	texture_shader1 = new texture_shader_stuff;
	texture_shader1->init(directx_handle->get_device(), hwnd, L"texture_shader.hlsl", L"texture_shader.hlsl");


	render_texture = new render_2_texture_stuff;
	render_texture->init(directx_handle->get_device(), 800, 800);

	model15 = new model_stuff;
	model15->init4(directx_handle->get_device(), L"../WindowsProject1/data/plane2.obj");
	model15->init_texture(directx_handle->get_device(), L"../WindowsProject1/data/backdrop.dds");


//Init shaders

	basic_shader = new basic_shader_stuff;
	basic_shader->init(directx_handle->get_device(), hwnd, L"basic_shader.hlsl", L"basic_shader.hlsl");


     texture_shader = new texture_shader_stuff;
	texture_shader->init(directx_handle->get_device(), hwnd, L"texture_shader.hlsl", L"texture_shader.hlsl");

	light_shader = new cube_map_stuff;
	light_shader->load(directx_handle->get_device(), L"../WindowsProject1/data/SpaceSkybox.dds");
	light_shader->init(directx_handle->get_device(), hwnd, L"../WindowsProject1/cubemap_shader.hlsl", L"../WindowsProject1/cubemap_shader.hlsl");


	model4_light_shader = new light_shader_stuff;
	model4_light_shader->init_info({ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.5f, 1.0f });
	model4_light_shader->init(directx_handle->get_device(), hwnd, L"light_shader.hlsl", L"light_shader.hlsl");

	ambient_shader = new ambient_light_stuff;
	ambient_shader->init_info({ 0.15f, 0.0f, 0.45f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
	ambient_shader->init(directx_handle->get_device(), hwnd, L"ambient_light.hlsl", L"ambient_light.hlsl");

	specular_shader = new specular_lighting_stuff;
	specular_shader->init_info({ 0.15f, 0.12f, 0.15f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f,0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, 5);
	specular_shader->init(directx_handle->get_device(), hwnd, L"specular_lighting.hlsl", L"specular_lighting.hlsl");

	multi_shader = new multi_texture_stuff;
	multi_shader->init(directx_handle->get_device(), hwnd, L"multi_texture_shader.hlsl", L"multi_texture_shader.hlsl");

	spot_shader = new spotlight_shader_stuff;
	//XMMatrixTranslation(0.0f, 0.0f, 0.0f)
	float scalar = 0.3f;
	XMFLOAT4 position = { 0.0f, 0.0f, 0.0f , 1.0f };
	XMFLOAT4 light1_color = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMFLOAT4 light2_color = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 light3_color = { 0.0f, 0.0f, 0.0f, 0.0f };
	XMFLOAT4 light4_color = { 0.0f, 0.0f, 0.0f, 0.0f };

	XMFLOAT4 light1_pos = { 3.0f, 1.0f, 10.0f, 1.0f };
	XMFLOAT4 light2_pos = { 0.0f, 0.0f, -1.0f, 1.0f };
	XMFLOAT4 light3_pos = { (position.x - 2.0f) * scalar, (position.y + 2.0f) * scalar, (position.z - 2.0f) * scalar, 1.0f };
	XMFLOAT4 light4_pos = { (position.x + 2.0f) * scalar, (position.y + 2.0f) * scalar, (position.z - 2.0f) * scalar, 1.0f };

	XMFLOAT4 light_colors[] = {light1_color, light2_color, light3_color, light4_color};
	XMFLOAT4 light_pos[] = { light1_pos, light2_pos, light3_pos, light4_pos };

	/*spot_shader->init_info(light_colors, light_pos);
	spot_shader->init(directx_handle->get_device(), hwnd, L"spotlight_shader.hlsl", L"spotlight_shader.hlsl"); 
	XMFLOAT4 a[] = { {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f,1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };
	XMFLOAT4 planepos[] = { {0.0f,0.0f,0.0f,1.0f}, {0.0f,0.0f,0.0f,1.0f}, {0.0f,0.0f,0.0f,1.0f}, {0.0f,0.0f,0.0f,1.0f} };
	spot_shader->init_info(a, planepos);*/


	light_shader1 = new light_shader_stuff;
	light_shader1->init(directx_handle->get_device(), hwnd, L"light_shader.hlsl", L"light_shader.hlsl");
	light_shader1->init_info({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });


	spotlight2_shader = new spotlight2_shader_stuff;
	spotlight2_shader->init_info({ 3.0f, 20.0f, 10.0f }, { 0.0f, -1.0f, 0.0f }, { 0.4f, 0.02f, 0.000f }, { 0.2f, 0.2f, 0.2f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 1000.0f, 500.0f);
	spotlight2_shader->init(directx_handle->get_device(), hwnd,L"../WindowsProject1/spotlight2_shader.hlsl", L"../WindowsProject1/spotlight2_shader.hlsl");

	instance_shader = new instance_shader_stuff;
	instance_shader->init_info({ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.5f, 1.0f }, 4);
	instance_shader->init(directx_handle->get_device(), hwnd, L"instance_shader.hlsl", L"instance_shader.hlsl");

	return true;
}

bool graphics_stuff::render()
{
	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		 key != key;
		 MODEL1 = 0;
		 MODEL2 = 0;
		 CUBE_MAP = 1;
		 PYRAMID = !PYRAMID;
		 PLANET = !PLANET;
		 STAR = !STAR;
		 ASTEROID = !ASTEROID;
		 PLANE = 1;
		 INSTANCE = !INSTANCE;
		 SHADOW = 0;
		 DEPTH = 0;
		 RENDER2 = 1;
		 SPOT = 1;
	}
	static float pyramid_rotation = 0.0f;
	static float triangle_rotation = 0.0f;
	static float triangle_rotation1 = 0.0f;
	static float triangle_rotation2 = 0.0f;
	pyramid_rotation += (float)XM_PI * 0.00001f;
	triangle_rotation += (float)XM_PI * 0.00004f;
	triangle_rotation1 += (float)XM_PI * -0.00002f;
	triangle_rotation2 += (float)XM_PI * -0.00002f;
	if (pyramid_rotation > 360.0f )
	{
		pyramid_rotation -= 360.0f;
	}

	if (triangle_rotation > 360.0f)
	{
		triangle_rotation -= 360.0f;
	}
	if (triangle_rotation1 < -360.0f)
	{
		triangle_rotation1 += 360.0f;
	}
	if (triangle_rotation2 < -360.0f)
	{
		triangle_rotation2 += 360.0f;
	}
	static float light_angle = 270.0f;
	float radians;
	static float light_pos_x = 9.0f;

	light_pos_x -= 0.003f;

	if (light_angle < 90.0f)
	{
		light_angle = 270.0f;

		// Reset the light position also.
		light_pos_x = 9.0f;
	}

	XMMATRIX world, view, proj;
	bool check;
	float x = XMConvertToRadians(light_angle);
if (RENDER2== true){
	check = render_2_texture();
}
	directx_handle->clear_buffer();



if (!RENDER2)
	camera_handle->render();


	view = camera_handle->get_view_matrix();
	world = directx_handle->get_world_matrix();
	proj = directx_handle->get_proj_matrix();
	

if (MODEL1 == true){	
	model1->render(directx_handle->get_device_context());
	basic_shader->render(directx_handle->get_device_context(), model1->get_index_count(), world, view, proj);
}
if (MODEL2 == true){
	world = XMMatrixRotationY(pyramid_rotation);
	model2->render2(directx_handle->get_device_context());
	texture_shader->render(directx_handle->get_device_context(), model2->get_index_count(), world, view, proj, model2->get_texture());
}
if (CUBE_MAP== true){
	directx_handle->turn_off_z();
	world = XMMatrixScaling(500.0f, 500.0f, 500.0f) * XMMatrixTranslation(camera_handle->get_pos().x, camera_handle->get_pos().y, camera_handle->get_pos().z);
	model3->render3(directx_handle->get_device_context());
	light_shader->render(directx_handle->get_device_context(), model3->get_index_count(), world, view, proj, light_shader->get_resource_view());
	directx_handle->turn_on_z();
}
if (RENDER2== true){
	render2_scene();
	auto ortho = directx_handle->get_ortho_matrix();

	//TODO: Turn off zbuffer
	directx_handle->turn_off_z();
}
if (INSTANCE == true){
	//const float alpha[] = { 0.3f ,0.3f, 0.4f, 0.4f };
	XMMATRIX rot6 = XMMatrixRotationY(triangle_rotation1) * XMMatrixRotationX(triangle_rotation1);
	XMMATRIX trans6 = XMMatrixTranslation(0.5f, 2.0f, 2.0f);
	XMMATRIX trans6_ = XMMatrixTranslation(-0.5f, -2.0f, 2.0f);
	world = trans6_ * rot6 * trans6 * XMMatrixScaling(0.5f, 0.5f, 0.5f);
	model9->render5(directx_handle->get_device_context());
	directx_handle->get_device_context()->OMSetBlendState(directx_handle->get_transparent_state(), 0, 0xffffffff);
	instance_shader->render(directx_handle->get_device_context(), model9->get_index_count(), world, view, proj, model9->get_texture());
	directx_handle->get_device_context()->OMSetBlendState(directx_handle->get_default_blend_state(), 0, 0);
}
if (PYRAMID == true){

	const float alpha[] = { 0.3f ,0.3f, 0.4f, 0.4f };
	XMMATRIX rot3 = XMMatrixRotationY(triangle_rotation1) * XMMatrixRotationX(triangle_rotation1);
	XMMATRIX trans3 = XMMatrixTranslation(0.5f, 2.0f, 2.0f);
	XMMATRIX trans3_ = XMMatrixTranslation(-0.5f, -2.0f, 2.0f);
	world = trans3_ * rot3 * trans3;
	model4->render4(directx_handle->get_device_context());
	directx_handle->get_device_context()->OMSetBlendState(directx_handle->get_transparent_state(), 0, 0xffffffff);
	model4_light_shader->render(directx_handle->get_device_context(), model4->get_index_count(), world, view, proj, model4->get_texture());
	directx_handle->get_device_context()->OMSetBlendState(directx_handle->get_default_blend_state(), 0, 0xffffffff);

}
if (PLANET== true){
	XMMATRIX rot4 = XMMatrixRotationY(triangle_rotation2);
	XMMATRIX trans4 = XMMatrixTranslation(0.0f, 580.0f, 200.0f);
	XMMATRIX trans4_ = XMMatrixTranslation(-240.0f, -580.0f, -200.0f);
	world = trans4_ * rot4 * trans4 * XMMatrixScaling(0.01f, 0.01f, 0.01f);
	
	model5->render4(directx_handle->get_device_context());
	ambient_shader->render(directx_handle->get_device_context(), model5->get_index_count(), world, view, proj, model5->get_texture());
}
if (STAR == true){ 
	XMMATRIX rot;
	XMMATRIX trans;
	XMMATRIX trans1;
	rot =  XMMatrixRotationY(-triangle_rotation) ;
	trans = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	trans1 = XMMatrixTranslation(90.0f, 0.0f, 90.0f);
	world = trans1 * rot * trans * XMMatrixScaling(0.01f, 0.01f, 0.01f);
	model6->render4(directx_handle->get_device_context());
	specular_shader->render(directx_handle->get_device_context(), model6->get_index_count(), world, view, proj, model6->get_texture(), camera_handle->get_pos());
}
if (ASTEROID == true){

	XMMATRIX rot2 = XMMatrixRotationY(triangle_rotation) * XMMatrixRotationX(triangle_rotation) ;
	XMMATRIX trans2 = XMMatrixTranslation(0.5f, -150.0f, 2.0f);
	XMMATRIX trans2_ = XMMatrixTranslation(-0.0f, -0.0f, 0.0f);
	world = trans2_ * rot2 * trans2 * XMMatrixScaling(0.01f, 0.01f, 0.01f);
	model7->render4(directx_handle->get_device_context()); 
	multi_shader->render(directx_handle->get_device_context(), model7->get_index_count(), world, view, proj, model7->get_textures());
}

if (RENDER2== true){
	directx_handle->get_device_context()->RSSetState(directx_handle->get_depth_bias_state());
	world = XMMatrixScaling(0.5f, 0.5f, 0.5f)* XMMatrixRotationY(triangle_rotation) * XMMatrixTranslation(-3.0f, -2.0f, 0.0f);
	//bitmap_shader->render(directx_handle->get_device_context(), 150, 150);

	//texture_shader1->render(directx_handle->get_device_context(), bitmap_shader->get_index_count(), world, view, ortho, render_texture->get_resource_view());
	model16->render4(directx_handle->get_device_context());
	texture_shader1->render(directx_handle->get_device_context(), model16->get_index_count(), world, view, proj, render_texture->get_resource_view());
	//TODO: Turn on zbuffer
	directx_handle->get_device_context()->RSSetState(directx_handle->get_default_raster_state());
	directx_handle->turn_on_z();
}
if (SPOT== true){ 
	world = XMMatrixTranslation(60.0f, 40.0f, 20.0f) *XMMatrixRotationX(XMConvertToRadians(90))* XMMatrixScaling(0.09f, 0.09f, 0.09f);
	model15->render4(directx_handle->get_device_context());
	spotlight2_shader->render(directx_handle->get_device_context(), model15->get_index_count(), world, view, proj, model15->get_texture());
}
	/*if (PLANE == true){
	world = XMMatrixTranslation(60.0f, 40.0f, 20.0f) * XMMatrixRotationX(XMConvertToRadians(90)) * XMMatrixScaling(0.09f, 0.09f, 0.09f);

	model8->render4(directx_handle->get_device_context());
	spot_shader->render(directx_handle->get_device_context(), model8->get_index_count(), world, view, proj, model8->get_texture());
}*/

	directx_handle->display();
	return true;
}

bool GraphicsProj::graphics_stuff::render_2_texture()
{
if (RENDER2== true){
	render_texture->set_render_target(directx_handle->get_device_context(), directx_handle->get_depth_stencil_view());

	render_texture->clear_render(directx_handle->get_device_context(), directx_handle->get_depth_stencil_view());

	render2_scene();

	directx_handle->set_back_buffer_render_target();

	return true;
}
	return true;
}
void graphics_stuff::render2_scene()
{
if (RENDER2== true){
	XMMATRIX world, view, proj;
	bool result;
	static float rotation = 0.0f;

	camera_handle->render();

	view = camera_handle->get_view_matrix();
	world = directx_handle->get_world_matrix();
	proj = directx_handle->get_proj_matrix();

	rotation += (float)XM_PI * 0.000005f;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	world = XMMatrixRotationY(rotation) * XMMatrixTranslation(3.0f, 3.0f, 15.0f);
	model14->render4(directx_handle->get_device_context());

	result = light_shader1->render(directx_handle->get_device_context(), model14->get_index_count(), world, view, proj, model14->get_texture());
}
}
void graphics_stuff::clean_up()
{

	//models

	if (model3 != NULL) {
		model3->clean_up();
		delete model3;
	}
	if (model4 != NULL) {
		model4->clean_up();
		delete model4;
	}
	if (model5 != NULL) {
		model5->clean_up();
		delete model5;
	}
	if (model6 != NULL) {
		model6->clean_up();
		delete model6;
	}
	if (model7 != NULL) {
		model7->clean_up();
		delete model7;
	}
	if (model8 != NULL) {
		model8->clean_up();
		delete model8;
	}
	if (model9 != NULL) {
		model9->clean_up();
		delete model9;
	}
	if (model10 != NULL) {
		model10->clean_up();
		delete model10;
	}
	if (model11 != NULL) {
		model11->clean_up();
		delete model11;
	}
	if (model11 != NULL) {
		model11->clean_up();
		delete model11;
	}
	if (model12 != NULL) {
		model12->clean_up();
		delete model12;
	}
	if (model13 != NULL) {
		model13->clean_up();
		delete model13;
	}
	if (model14 != NULL) {
		model14->clean_up();
		delete model14;
	}
	if (model15 != NULL) {
		model15->clean_up();
		delete model15;
	}
	if (model16 != NULL) {
		model16->clean_up();
		delete model16;
	}


	//shaders 
	if (basic_shader != NULL) {
		basic_shader->clean_up();
		delete basic_shader;
	}
	if (texture_shader != NULL) {
		texture_shader->clean_up();
		delete texture_shader;
	}
	if (light_shader != NULL) {
		light_shader->clean_up();
		delete light_shader;
	}
	if (model4_light_shader != NULL) {
		model4_light_shader->clean_up();
		delete model4_light_shader;
	}
	if (ambient_shader != NULL) {
		ambient_shader->clean_up();
		delete ambient_shader;
	}
	if (specular_shader != NULL) {
		specular_shader->clean_up();
		delete specular_shader;
	}
	if (multi_shader != NULL) {
		multi_shader->clean_up();
		delete multi_shader;
	}
	if (spot_shader != NULL) {
		spot_shader->clean_up();
		delete spot_shader;
	}
	if (instance_shader != NULL) {
		instance_shader->clean_up();
		delete instance_shader;
	}
	
	if (spotlight2_shader != NULL)
	{
		spotlight2_shader->clean_up();
	delete spotlight2_shader;
}

	if (texture_shader1 != NULL)
	{
		texture_shader1->clean_up();
		delete texture_shader1;
	}
	if (light_shader1 != NULL)
	{
		light_shader1->clean_up();
		delete light_shader1;
	}
	//classes
if (render_texture != NULL) {
	render_texture->clean_up();
	delete render_texture;
}
	delete camera_handle;
	directx_handle->clean_up();
	delete directx_handle;
	//variables

}

directx_stuff* GraphicsProj::graphics_stuff::get_directx_handle()
{
	return directx_handle;
}


