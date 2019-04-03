#include "loader_stuff.h"
#include <string>
#include <fstream>
#include "defines.h"

using namespace std;
namespace GraphicsProj {
	loader_stuff::loader_stuff()
	{
	}


	loader_stuff::~loader_stuff()
	{
	}

	void loader_stuff::Clean_Up()
	{
		delete final_struct;
		final_struct = 0;
	}

	typedef struct
	{
		int v1, v2, v3;
		int t1, t2, t3;
		int n1, n2, n3;
	}face_struct;
	typedef struct
	{
		float x, y, z;
	}verts;
	typedef struct
	{
		float x, y;
	}texts;
	typedef struct
	{
		float x, y, z;
	}norms;
	loader_stuff::light_struct* loader_stuff::load_object(LPCWSTR fn)
	{
		fstream stream;
		char input;
		int index = 0;
		auto* face = new face_struct[face_count];
		verts* verts_ = new verts[vertex_count];
		texts* texts_ = new texts[texture_count];
		norms* norms_ = new norms[normal_count];
		stream.open(fn);

		int vertex_index = 0;
		int text_index = 0;
		int norm_index = 0;
		int face_index = 0;
		if (stream.fail())
		{
			return false;
		}
		stream.get(input);
		while (!stream.eof())
		{
			if (input == 'v')
			{
				stream.get(input);
				if (input == ' ')
				{
					stream >> verts_[vertex_index].x >> verts_[vertex_index].y >> verts_[vertex_index].z;

					verts_[vertex_index].z *= -1.0f;
					vertex_index++;
				}
				if (input == 't')
				{
					stream >> texts_[text_index].x >> texts_[text_index].y;

					texts_[text_index].y = 1.0f - texts_[text_index].y;
					text_index++;
				}

				if (input == 'n')
				{
					stream >> norms_[norm_index].x >> norms_[norm_index].y >> norms_[norm_index].z;

					norms_[norm_index].z *= -1.0f;
					norm_index++;
				}
			}
			else if (input == 'f')
			{
				char slash;
				stream.get(input);
				if (input == ' ')
				{
					stream >> face[face_index].v3 >> slash >> face[face_index].t3 >> slash >> face[face_index].n3
						>> face[face_index].v2 >> slash >> face[face_index].t2 >> slash >> face[face_index].n2
						>> face[face_index].v1 >> slash >> face[face_index].t1 >> slash >> face[face_index].n1;

					face_index++;
				}
				
			}
			while (input != '\n')
				stream.get(input);

			stream.get(input);
		}
		
		
		int v_index = face_index * 3;
		final_struct = new light_struct[v_index];
		for (size_t i = 0; i < face_index; i++)
		{
			auto v = face[i].v1 - 1;
			auto t = face[i].t1 - 1;
			auto n = face[i].n1 - 1;

			final_struct[index].pos.x = verts_[v].x; final_struct[index].pos.y = verts_[v].y; final_struct[index].pos.z = verts_[v].z;
			final_struct[index].text.x = texts_[t].x; final_struct[index].text.y = texts_[t].y;
			final_struct[index].norm.x = norms_[n].x; final_struct[index].norm.y = norms_[n].y; final_struct[index].norm.z = norms_[n].z;
			index++;

			v = face[i].v2 - 1;
			t = face[i].t2 - 1;
			n = face[i].n2 - 1;

			final_struct[index].pos.x = verts_[v].x; final_struct[index].pos.y = verts_[v].y; final_struct[index].pos.z = verts_[v].z;
			final_struct[index].text.x = texts_[t].x; final_struct[index].text.y = texts_[t].y;
			final_struct[index].norm.x = norms_[n].x; final_struct[index].norm.y = norms_[n].y; final_struct[index].norm.z = norms_[n].z;
			index++;
			v = face[i].v3 - 1;
			t = face[i].t3 - 1;
			n = face[i].n3 - 1;

			final_struct[index].pos.x = verts_[v].x; final_struct[index].pos.y = verts_[v].y; final_struct[index].pos.z = verts_[v].z;
			final_struct[index].text.x = texts_[t].x; final_struct[index].text.y = texts_[t].y;
			final_struct[index].norm.x = norms_[n].x; final_struct[index].norm.y = norms_[n].y; final_struct[index].norm.z = norms_[n].z;
			index++;
		}
		vertex_count = v_index;
		//TODO: Clean up
		delete[] verts_;
		delete[] texts_;
		delete[] norms_;
		delete[] face;
		return final_struct;
	}

	void loader_stuff::get_counts(LPCWSTR fn)
	{
		ifstream stream;
		vertex_count = 0;
		normal_count = 0;
		texture_count = 0;
		face_count = 0;
		char input;
		stream.open(fn);
		if (stream.fail())
			return;
		stream.get(input);
		while (!stream.eof())
		{
			if (input == 'v')
			{
				stream.get(input);
				if (input == ' ') { vertex_count++; };
				if (input == 'n') { normal_count++; };
				if (input == 't') { texture_count++; };
			}
			else if (input == 'f')
			{
				stream.get(input);
				if (input == ' ') { face_count++; };
			}
			while (input != '\n')
				stream.get(input);
			stream.get(input);
		}
		stream.close();
	}

	int loader_stuff::get_vertex_count()
	{
		return vertex_count;
	}
	int loader_stuff::get_index_count()
	{
		return face_count * 3;
	}
}
