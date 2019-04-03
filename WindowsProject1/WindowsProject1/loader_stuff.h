#pragma once
#include "directx_stuff.h"
namespace GraphicsProj {
	class loader_stuff
	{
	public:
		loader_stuff();
		~loader_stuff();
		void Clean_Up();
		struct light_struct
		{
			XMFLOAT3 pos;
			XMFLOAT2 text;
			XMFLOAT3 norm;
		};

		light_struct* load_object(LPCWSTR fn);
		light_struct* final_struct;
		void get_counts(LPCWSTR fn);
		
	//Getters and setters
		int get_vertex_count();
		int get_index_count();
	private:
		//Private variables
		int vertex_count;
		int texture_count;
		int normal_count;
		int face_count;
	};
}

