#include "Parser.h"

Parser::Parser() : faces(new List()), bbx0(-100000), bbx1(100000), bby0(-100000), bby1(100000), bbz0(-100000), bbz1(100000) {}

Parser::~Parser() {
	delete faces;
}

// Parse .obj file
// creates new shape
void Parser::parse(const char *path) {
	tokenizer = new Tokenizer();
	tokenizer->tokenize(path);
	String *token = tokenizer->nextToken();
	while (token != NULL) {
		if (*token == "f") parse_f();
		else if (*token == "g") parse_g();
		else if (*token == "usemtl") parse_usemtl();
		else if (*token == "mtllib") parse_mtllib();
		else if (*token == "vn") parse_vn();
		else if (*token == "vt") parse_vt();
		else if (*token == "v") parse_v();
		else if (*token == "l") parse_l();
		else if (*token == "p") parse_p();
		else if (*token == "s") parse_s();
		else if (*token == "#") parse_comment();
		else {}
		token = tokenizer->nextToken();
	}
	delete tokenizer;
}

// Parse .mtl file
// creates new material
void Parser::parseMaterialLibrary(String *path) {
	materialTokenizer = new Tokenizer();
	materialTokenizer->tokenize(path->getString());
	String *token = materialTokenizer->nextToken();
	while (token != NULL) {
		if (*token == "newmtl") parse_newmtl();
		else if (*token == "illum") parse_illum();
		else if (*token == "Ka") parse_Ka();
		else if (*token == "Kd") parse_Kd();
		else if (*token == "Ks") parse_Ks();
		else if (*token == "Ns") parse_Ns();
		else if (*token == "map_Ka") parse_map_Ka();
		else if (*token == "map_Kd") parse_map_Kd();
		else if (*token == "map_Ks") parse_map_Ks();
		else if (*token == "d") parse_d();
		else if (*token == "#") parse_material_comment();
		else {}
		token = materialTokenizer->nextToken();
	}
	delete materialTokenizer;
}

// Parse camera.txt file
// creates new camera
Camera Parser::parseConfig(const char *path) {
	configTokenizer = new Tokenizer();
	configTokenizer->tokenize(path);
	String *token = configTokenizer->nextToken();
	while (token != NULL) {
		if (*token == "viewpoint") parse_viewpoint();
		else if (*token == "dir") parse_dir();
		else if (*token == "v_up") parse_v_up();
		else if (*token == "f") parse_fl();
		else if (*token == "aspectratio") parse_aspectratio();
		else if (*token == "screenwidth") parse_screenwidth();
		else if (*token == "width") parse_width();
		else if (*token == "viewmode") parse_viewmode();
		else if (*token == "antialiasing") parse_antialiasing();
		else if (*token == "#") parse_config_comment();
		else {}
		token = configTokenizer->nextToken();
	}
	delete configTokenizer;
	return camera;
}

// Find material in material list created from material parser
// returns material to use for the object
Material *Parser::findMaterial(String *material) {
	Node *node = materials.head;
	while (node) {
		if (((Material *)node->data)->getName() == *material) return (Material *)node->data;
		node = node->next;
	}
	return NULL;
}

// get all the triangles created by the parser
// only call after parse is complete
List *Parser::getFaces() const {return faces;}

// get the bounding box surounding the object
// only call after parse is complete
BoundingBox *Parser::getAABB() const {
	return new BoundingBox(bbx1, bbx0, bby1, bby0, bbz1, bbz0);
}

// Parse f token in .obj file
// creates new triangle
// handles three possible configurations v, v/t, v/vn/t
void Parser::parse_f() {
	int v1, v2, v3, n1, n2, n3, t1, t2, t3;
	String *token;
	v1 = tokenizer->nextToken()->toInt() - 1;
	token = tokenizer->nextToken();
	if (*token != "/") {
		v2 = token->toInt() - 1;
		v3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		Triangle *triangle = new Triangle(
			"triangle",
			material,
			*(Vector *)vertexes.getElementAtIndex(v1),
			*(Vector *)vertexes.getElementAtIndex(v2),
			*(Vector *)vertexes.getElementAtIndex(v3));
		if (vertexNormals.getSize() != 0) {
			triangle->setPhongVectors(
				*(Vector *)vertexNormals.getElementAtIndex(v1),
				*(Vector *)vertexNormals.getElementAtIndex(v2),
				*(Vector *)vertexNormals.getElementAtIndex(v3));
		}
		if (textureVertexes.getSize() != 0) {
			triangle->setTextureVectors(
				*(Vector *)textureVertexes.getElementAtIndex(v1),
				*(Vector *)textureVertexes.getElementAtIndex(v2),
				*(Vector *)textureVertexes.getElementAtIndex(v3));
		}
		faces->add(triangle);
		return;
	} 
	token = tokenizer->nextToken();
	if (*token != "/") {
		t1 = token->toInt() - 1;
		token = tokenizer->nextToken();
		if (*token != "/") {
			v2 = token->toInt() - 1;
			tokenizer->nextToken();
			t2 = tokenizer->nextToken()->toInt() - 1;
			v3 = tokenizer->nextToken()->toInt() - 1;
			tokenizer->nextToken();
			t3 = tokenizer->nextToken()->toInt() - 1;
			tokenizer->nextToken();
			Triangle *triangle = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v2),
				*(Vector *)vertexes.getElementAtIndex(v3));
			if (vertexNormals.getSize() != 0) {
				triangle->setPhongVectors(
					*(Vector *)vertexNormals.getElementAtIndex(v1),
					*(Vector *)vertexNormals.getElementAtIndex(v2),
					*(Vector *)vertexNormals.getElementAtIndex(v3));
			}
			if (textureVertexes.getSize() != 0) {
				triangle->setTextureVectors(
					*(Vector *)textureVertexes.getElementAtIndex(t1),
					*(Vector *)textureVertexes.getElementAtIndex(t2),
					*(Vector *)textureVertexes.getElementAtIndex(t3));
			}
			faces->add(triangle);
			return;	
		}
		n1 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		v2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		t2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		n2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		v3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		t3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		n3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		Triangle *triangle = new Triangle(
			"triangle",
			material,
			*(Vector *)vertexes.getElementAtIndex(v1),
			*(Vector *)vertexes.getElementAtIndex(v2),
			*(Vector *)vertexes.getElementAtIndex(v3));
		triangle->setPhongVectors(
			*(Vector *)vertexNormals.getElementAtIndex(n1),
			*(Vector *)vertexNormals.getElementAtIndex(n2),
			*(Vector *)vertexNormals.getElementAtIndex(n3));
		triangle->setTextureVectors(
			*(Vector *)textureVertexes.getElementAtIndex(t1),
			*(Vector *)textureVertexes.getElementAtIndex(t2),
			*(Vector *)textureVertexes.getElementAtIndex(t3));
		faces->add(triangle);
		return;
	}
	if (*token == "/") {
		n1 = tokenizer->nextToken()->toInt() - 1;
		v2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		tokenizer->nextToken();
		n2 = tokenizer->nextToken()->toInt() - 1;
		v3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		tokenizer->nextToken();
		n3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		Triangle *triangle = new Triangle(
			"triangle",
			material,
			*(Vector *)vertexes.getElementAtIndex(v1),
			*(Vector *)vertexes.getElementAtIndex(v2),
			*(Vector *)vertexes.getElementAtIndex(v3));
		triangle->setPhongVectors(
			*(Vector *)vertexNormals.getElementAtIndex(n1),
			*(Vector *)vertexNormals.getElementAtIndex(n2),
			*(Vector *)vertexNormals.getElementAtIndex(n3));
		if (textureVertexes.getSize() != 0) {
			triangle->setTextureVectors(
				*(Vector *)textureVertexes.getElementAtIndex(v1),
				*(Vector *)textureVertexes.getElementAtIndex(v2),
				*(Vector *)textureVertexes.getElementAtIndex(v3));
		}
		faces->add(triangle);
		return;
	}
}

// Parse v token in .obj file
void Parser::parse_v() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	if (vector->x > bbx0) bbx0 = vector->x;
	if (vector->x < bbx1) bbx1 = vector->x;
	vector->y = tokenizer->nextToken()->toFloat();
	if (vector->y > bby0) bby0 = vector->y;
	if (vector->y < bby1) bby1 = vector->y;
	vector->z = tokenizer->nextToken()->toFloat();
	if (vector->z > bbz0) bbz0 = vector->z;
	if (vector->z < bbz1) bbz1 = vector->z;
	vertexes.add(vector);
	tokenizer->nextToken();
}

// Parse vn token in .obj file
void Parser::parse_vn() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	vector->z = tokenizer->nextToken()->toFloat();
	vertexNormals.add(vector);
	tokenizer->nextToken();
}

// Parse vt tokein in .obj file
// adds to texture vertex list
void Parser::parse_vt() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	textureVertexes.add(vector);
	tokenizer->nextToken();
}

// Parse g token in .obj file
// ignored
void Parser::parse_g() {
	if (*tokenizer->nextToken() != '\n') tokenizer->nextToken();
}

// Parse usemtl token in .obj file
// gets material to use from token argument
// puts material on the stack
void Parser::parse_usemtl() {
	material = *findMaterial(tokenizer->nextToken());
	tokenizer->nextToken();
}

// Parse Ka token in .mtl file
// sets the Ka(ambient) value of the material being created
void Parser::parse_Ka() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->color = color;
	materialTokenizer->nextToken();
}

// Parse Kd token in .mtl file
// sets the Kd(diffuse) value of the material being created
void Parser::parse_Kd() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->diffusionCoefficient = color;
	materialTokenizer->nextToken();
}

// Parse Ks(specular) value of the material being created
// .mtl file
void Parser::parse_Ks() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->specularCoefficient = color;
	materialTokenizer->nextToken();
}

// Parse Ns(specular exponent) value of the material being created
// .mtl file
void Parser::parse_Ns() {
	((Material *)materials.tail->data)->specularExponent = materialTokenizer->nextToken()->toInt();
	materialTokenizer->nextToken();
}

// Parse newmtl token
// creates a new material
// name comes from token argument
// .mtl file
void Parser::parse_newmtl() {
	materials.add(new Material(*materialTokenizer->nextToken()));
	materialTokenizer->nextToken();
}

// Parse illum token
// sets the shading model of the material being created
// .mtl file
void Parser::parse_illum() {
	((Material *)materials.tail->data)->shadingModel = materialTokenizer->nextToken()->toInt();
	materialTokenizer->nextToken();
}

// Parse mtllib token
// sets the material library to parse
// .obj file
void Parser::parse_mtllib() { 
	parseMaterialLibrary(tokenizer->nextToken());
	tokenizer->nextToken();
}

// Parse map_Ka
// *funcionality may be removed
// .mtl file
void Parser::parse_map_Ka() {
	Image image;
	((Material *)materials.tail->data)->ambientTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

// Parse map_Kd token
// creates and adds texture to material
// .mtl file
void Parser::parse_map_Kd() {
	Image image;
	((Material *)materials.tail->data)->diffuseTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

// Parse map_Ks
// *funcionality may be removed
// .mtl file
void Parser::parse_map_Ks() {
	Image image;
	((Material *)materials.tail->data)->specularTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

// Parse d token
// sets the alpha value of the texture map
// .mtl file
void Parser::parse_d() {
	material.textureAlpha = materialTokenizer->nextToken()->toFloat();
	materialTokenizer->nextToken();
}

// Parse viewpoint token
// sets the viewpoint of the camera
// camera.txt file
void Parser::parse_viewpoint() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setViewPoint(vector);
	configTokenizer->nextToken();
}

// Parse dir token
// sets the direction of the camera being created
// camera.txt file
void Parser::parse_dir() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setDirection(vector);
	configTokenizer->nextToken();
}

// Parse v_up token
// sets the up direction of the camera being created
// camera.txt file
void Parser::parse_v_up() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setUpDirection(vector);
	configTokenizer->nextToken();
}

// Parse the f token
// sets the focal length of the camera being created
// camera.txt file
void Parser::parse_fl() {
	camera.setFocalLength(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();	
}

// Parse aspectratio token
// sets the aspect ratio of the camera being created
// camera.txt file
void Parser::parse_aspectratio() {
	camera.setAspectRatio(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();
}

// Parse the screenwidth token
// sets the screenwidth of the camera being created
// camera.txt file
void Parser::parse_screenwidth() {
	camera.setScreenWidth(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();
}

// Parse width token
// sets the width of the screen (in pixels) of the camera being created
// camera.txt file
void Parser::parse_width() {
	camera.setScreenPixelWidth(configTokenizer->nextToken()->toInt());
	configTokenizer->nextToken();
}

// Parse viewmode token
// sets the viewmode of the camera being created
// camera.txt file
void Parser::parse_viewmode() {
	if (*configTokenizer->nextToken() == "perspective") camera.setProjectionView();
	else configTokenizer->nextToken();
	configTokenizer->nextToken();
}

// Parse antialiasing token
// sets wether to use antialiasing or not
// also determines how many samples to use
// camera.txt file
void Parser::parse_antialiasing() {
	if (*configTokenizer->nextToken() == "true") {
		camera.enableAntialiasing();
		configTokenizer->nextToken();
		if (*configTokenizer->nextToken() == "samples") {
			camera.setAntialiasingLevel(configTokenizer->nextToken()->toInt());
		}
	}
	configTokenizer->nextToken();
}

// Parse s token
// ignored
// .obj file
void Parser::parse_s() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}

// Parse l token
// ignored
// .obj file
void Parser::parse_l() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}

// Parse p token
// ignored
// .obj file
void Parser::parse_p() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}

// Parse comment in camera.txt file
void Parser::parse_config_comment() {
	String *token = configTokenizer->nextToken();
	while (*token != '\n') token = configTokenizer->nextToken();
}

// Parse comment in .mtl file
void Parser::parse_material_comment() {
	String *token = materialTokenizer->nextToken();
	while (*token != '\n') token = materialTokenizer->nextToken();
}

// Parse comment in .obj file
void Parser::parse_comment() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}
