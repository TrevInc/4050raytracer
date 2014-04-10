#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include "Vector.h"
#include "Color.h"
#include "Material.h"
#include "Camera.h"
#include "Triangle.h"

class Parser {
	private:
		Tokenizer *tokenizer;
		Tokenizer *materialTokenizer;
		Tokenizer *configTokenizer;
		List vertexes;
		List vertexNormals;
		List textureVertexes;
		List materials;
		List *faces;
		Camera camera;
		Material material;
		void parseMaterialLibrary(String *path);
		Material *findMaterial(String *material);
		void parse_v();
		void parse_vn();
		void parse_vt();
		void parse_g();
		void parse_usemtl();
		void parse_f();
		void parse_Ka();
		void parse_Kd();
		void parse_Ks();
		void parse_Ns();
		void parse_newmtl();
		void parse_illum();
		void parse_mtllib();
		void parse_map_Ka();
		void parse_map_Kd();
		void parse_map_Ks();
		void parse_d();
		void parse_viewpoint();
		void parse_dir();
		void parse_v_up();
		void parse_fl();
		void parse_aspectratio();
		void parse_screenwidth();
		void parse_width();
		void parse_viewmode();
		void parse_antialiasing();
		void parse_l();
		void parse_p();
		void parse_material_comment();
		void parse_comment();
		void parse_config_comment();
	public:
		Parser();
		~Parser();
		void parse(const char *path);
		Camera parseConfig(const char *path);
		List *getFaces() const;
};

#endif
