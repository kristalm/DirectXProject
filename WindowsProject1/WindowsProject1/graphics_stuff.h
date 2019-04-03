#pragma once
#include "camera_stuff.h"
#include "model_stuff.h"
#include "basic_shader_stuff.h"
#include "texture_shader_stuff.h"
#include "directx_stuff.h"
#include "light_shader_stuff.h"
#include "position_stuff.h"
#include "ambient_light_stuff.h"
#include "specular_lighting_stuff.h"
#include "multi_texture_stuff.h"
#include "cube_map_stuff.h"
#include "spotlight_shader_stuff.h"
#include "instance_shader_stuff.h"
#include "depth_shader_stuff.h"
#include "shadow_map_shader_stuff.h"
#include "render_2_texture_stuff.h"
#include "bitmap_stuff.h"
#include "spotlight2_shader_stuff.h"

//#define MODEL1 0
//#define MODEL2 0
//#define CUBE_MAP 1
//#define PYRAMID 
//#define PLANET 1
//#define STAR 1
//#define ASTEROID 1
//#define PLANE 1
//#define INSTANCE 1
//#define SHADOW 0
//#define DEPTH 0
//#define RENDER2 1
//#define SPOT 1
namespace GraphicsProj
{
	class graphics_stuff
	{
	public:
		graphics_stuff();
		~graphics_stuff();
		//functions
		bool init(HWND hwnd);
		bool render();
		bool render_2_texture();
		void render2_scene();
		void clean_up();

		directx_stuff* get_directx_handle();
	private:
		//private variables
		directx_stuff * directx_handle;

		//Classes
		render_2_texture_stuff * render_texture;
		camera_stuff* camera_handle;

		//Models

		model_stuff* model1;


		model_stuff* model2;


		model_stuff* model3;


		model_stuff* model4;


		model_stuff* model5;


		model_stuff* model6;

		model_stuff* model7;

		model_stuff* model8;

		model_stuff* model9;

		model_stuff* model10;
		model_stuff* model11;
		model_stuff* model12;

		model_stuff* model13;

		model_stuff* model14;
		model_stuff* model16;

		model_stuff* model15;


		//Shaders

		basic_shader_stuff* basic_shader;

		texture_shader_stuff* texture_shader;

		cube_map_stuff* light_shader;

		light_shader_stuff* model4_light_shader;

		ambient_light_stuff* ambient_shader;

		specular_lighting_stuff* specular_shader;

		multi_texture_stuff* multi_shader;

		spotlight_shader_stuff* spot_shader;

		instance_shader_stuff* instance_shader;

		light_shader_stuff* light_shader1;
		texture_shader_stuff* texture_shader1;

		spotlight2_shader_stuff* spotlight2_shader;

		bool MODEL1 = 0;
		bool MODEL2 = 0;
		bool CUBE_MAP = 1;
		bool PYRAMID = 0;
		bool PLANET = 0;
		bool STAR = 0;
		bool ASTEROID = 0;
		bool PLANE = 1;
		bool INSTANCE = 0;
		bool SHADOW = 0;
		bool DEPTH = 0;
		bool RENDER2 = 1;
		bool SPOT = 1;
		bool key = false;
		bool key1 = false;
	};
}
