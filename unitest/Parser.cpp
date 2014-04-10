#include "Parser.h"

Parser::Parser() : faces(new List()) {}

Parser::~Parser() {
	delete faces;
}

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
		else if (*token == "#") parse_comment();
		else {}
		token = tokenizer->nextToken();
	}
	delete tokenizer;
}

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

Material *Parser::findMaterial(String *material) {
	Node *node = materials.head;
	while (node) {
		if (((Material *)node->data)->getName() == *material) return (Material *)node->data;
		node = node->next;
	}
	return NULL;
}

List *Parser::getFaces() const {return faces;}

void Parser::parse_f() {
	int a, b, c;
	a = tokenizer->nextToken()->toInt() - 1;
	b = tokenizer->nextToken()->toInt() - 1;
	c = tokenizer->nextToken()->toInt() - 1;
	Triangle *triangle = new Triangle(
		"triangle",
		material,
		*(Vector *)vertexes.getElementAtIndex(a),
		*(Vector *)vertexes.getElementAtIndex(b),
		*(Vector *)vertexes.getElementAtIndex(c));
	triangle->setPhongVectors(
		*(Vector *)vertexNormals.getElementAtIndex(a),
		*(Vector *)vertexNormals.getElementAtIndex(b),
		*(Vector *)vertexNormals.getElementAtIndex(c));
	triangle->setTextureVectors(
		*(Vector *)textureVertexes.getElementAtIndex(a),
		*(Vector *)textureVertexes.getElementAtIndex(b),
		*(Vector *)textureVertexes.getElementAtIndex(c));
	faces->add(triangle);
	tokenizer->nextToken();
}

void Parser::parse_v() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	vector->z = tokenizer->nextToken()->toFloat();
	vertexes.add(vector);
	tokenizer->nextToken();
}

void Parser::parse_vn() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	vector->z = tokenizer->nextToken()->toFloat();
	vertexNormals.add(vector);
	tokenizer->nextToken();
}

void Parser::parse_vt() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	textureVertexes.add(vector);
	tokenizer->nextToken();
}

void Parser::parse_g() {
	tokenizer->nextToken();
	tokenizer->nextToken();
}

void Parser::parse_usemtl() {
	material = *findMaterial(tokenizer->nextToken());
	tokenizer->nextToken();
}

void Parser::parse_Ka() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->color = color;
	materialTokenizer->nextToken();
}

void Parser::parse_Kd() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->diffusionCoefficient = color;
	materialTokenizer->nextToken();
}

void Parser::parse_Ks() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->specularCoefficient = color;
	materialTokenizer->nextToken();
}

void Parser::parse_Ns() {
	((Material *)materials.tail->data)->specularExponent = materialTokenizer->nextToken()->toInt();
	materialTokenizer->nextToken();
}

void Parser::parse_newmtl() {
	materials.add(new Material(*materialTokenizer->nextToken()));
	materialTokenizer->nextToken();
}

void Parser::parse_illum() {
	((Material *)materials.tail->data)->shadingModel = materialTokenizer->nextToken()->toInt();
	materialTokenizer->nextToken();
}

void Parser::parse_mtllib() { 
	parseMaterialLibrary(tokenizer->nextToken());
	tokenizer->nextToken();
}

void Parser::parse_map_Ka() {
	Image image;
	((Material *)materials.tail->data)->ambientTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

void Parser::parse_map_Kd() {
	Image image;
	((Material *)materials.tail->data)->diffuseTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

void Parser::parse_map_Ks() {
	Image image;
	((Material *)materials.tail->data)->specularTexture = image.readImage(*materialTokenizer->nextToken());
	materialTokenizer->nextToken();
}

void Parser::parse_d() {
	materialTokenizer->nextToken();
	materialTokenizer->nextToken();
}

void Parser::parse_viewpoint() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setViewPoint(vector);
	configTokenizer->nextToken();
}

void Parser::parse_dir() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setDirection(vector);
	configTokenizer->nextToken();
}

void Parser::parse_v_up() {
	Vector vector;
	vector.x = configTokenizer->nextToken()->toFloat();
	vector.y = configTokenizer->nextToken()->toFloat();
	vector.z = configTokenizer->nextToken()->toFloat();
	camera.setUpDirection(vector);
	configTokenizer->nextToken();
}

void Parser::parse_fl() {
	camera.setFocalLength(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();	
}

void Parser::parse_aspectratio() {
	camera.setAspectRatio(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();
}

void Parser::parse_screenwidth() {
	camera.setScreenWidth(configTokenizer->nextToken()->toFloat());
	configTokenizer->nextToken();
}

void Parser::parse_width() {
	camera.setScreenPixelWidth(configTokenizer->nextToken()->toInt());
	configTokenizer->nextToken();
}

void Parser::parse_viewmode() {
	if (*configTokenizer->nextToken() == "perspective") camera.setProjectionView();
	else configTokenizer->nextToken();
	configTokenizer->nextToken();
}

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

void Parser::parse_l() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}

void Parser::parse_p() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}

void Parser::parse_config_comment() {
	String *token = configTokenizer->nextToken();
	while (*token != '\n') token = configTokenizer->nextToken();
}

void Parser::parse_material_comment() {
	String *token = materialTokenizer->nextToken();
	while (*token != '\n') token = materialTokenizer->nextToken();
}

void Parser::parse_comment() {
	String *token = tokenizer->nextToken();
	while (*token != '\n') token = tokenizer->nextToken();
}
