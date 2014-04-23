#include "Parser.h"

Parser::Parser() : faces(new List()), line(1) {}

Parser::~Parser() {
	delete faces;
	Node *node = vertexes.head;
	while (node) {
		delete (Vector *)node->data;
		node = node->next;
	}
   node = vertexNormals.head;
	while (node) {
		delete (Vector *)node->data;
		node = node->next;
	} 
	node = textureVertexes.head;
	while (node) {
		delete (Vector *)node->data;
		node = node->next;
	}
   node = materials.head;
	while (node) {
		delete (Material *)node->data;
		node = node->next;
	} 
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
		else if (*token == "s") parse_s();
		else if (*token == "#") parse_comment();
		else if (*token == "\n") ++line;
		else { 
			printf("Syntax Error: line %d   unexpected token\n", line);
			exit(1);
		}
		token = tokenizer->nextToken();
	}
	delete tokenizer;
}

inline void Parser::parseMaterialLibrary(String path) {
	materialTokenizer = new Tokenizer();
	materialTokenizer->tokenize(path.getString());
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
		else if (*token == "\n") {}
		else { 
			printf("Syntax Error: line %d   unexpected token\n", line);
			exit(1);
		}
		token = materialTokenizer->nextToken();
	}
	delete materialTokenizer;
}

inline Material *Parser::findMaterial(String *material) {
	Node *node = materials.head;
	while (node) {
		if (((Material *)node->data)->getName() == *material) return (Material *)node->data;
		node = node->next;
	}
	return NULL;
}

const List *Parser::getFaces() const {return faces;}

inline void Parser::parse_f() {
	int v1, v2, v3, v4, n1, n2, n3, n4, t1, t2, t3, t4;
	String *token;
	v1 = tokenizer->nextToken()->toInt() - 1;
	token = tokenizer->nextToken();
	if (*token != "/") {
		v2 = token->toInt() - 1;
		v3 = tokenizer->nextToken()->toInt() - 1;
		token = tokenizer->nextToken();
		if (*token != "\n") {
			v4 = token->toInt() - 1;
			if (*tokenizer->nextToken() != "\n") {
				printf("Syntax Error: line %d   unexpected token\n", line);
				exit(1);
			}
			Triangle *triangle1 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v2),
				*(Vector *)vertexes.getElementAtIndex(v3));
			faces->add(triangle1);
			Triangle *triangle2 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v3),
				*(Vector *)vertexes.getElementAtIndex(v4));
			faces->add(triangle2);
			++line;
			return;
		}
		Triangle *triangle = new Triangle(
			"triangle",
			material,
			*(Vector *)vertexes.getElementAtIndex(v1),
			*(Vector *)vertexes.getElementAtIndex(v2),
			*(Vector *)vertexes.getElementAtIndex(v3));
		faces->add(triangle);
		++line;
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
			token = tokenizer->nextToken();
			if (*token != "\n") {
				v4 = token->toInt() - 1;
				tokenizer->nextToken();
				t4 = tokenizer->nextToken()->toInt() - 1;
				token = tokenizer->nextToken();
				if (*token != "\n") {
					printf("Syntax Error: line %d   unexpected token\n", line);
					exit(1);
				}
				Triangle *triangle1 = new Triangle(
					"triangle",
					material,
					*(Vector *)vertexes.getElementAtIndex(v1),
					*(Vector *)vertexes.getElementAtIndex(v2),
					*(Vector *)vertexes.getElementAtIndex(v3));
				triangle1->setTextureVectors(
					*(Vector *)textureVertexes.getElementAtIndex(t1),
					*(Vector *)textureVertexes.getElementAtIndex(t2),
					*(Vector *)textureVertexes.getElementAtIndex(t3));
				faces->add(triangle1);
				Triangle *triangle2 = new Triangle(
					"triangle",
					material,
					*(Vector *)vertexes.getElementAtIndex(v1),
					*(Vector *)vertexes.getElementAtIndex(v3),
					*(Vector *)vertexes.getElementAtIndex(v4));
				triangle2->setTextureVectors(
					*(Vector *)textureVertexes.getElementAtIndex(t1),
					*(Vector *)textureVertexes.getElementAtIndex(t3),
					*(Vector *)textureVertexes.getElementAtIndex(t4));
				faces->add(triangle2);
				++line;
				return;
			}
			Triangle *triangle = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v2),
				*(Vector *)vertexes.getElementAtIndex(v3));
			triangle->setTextureVectors(
				*(Vector *)textureVertexes.getElementAtIndex(t1),
				*(Vector *)textureVertexes.getElementAtIndex(t2),
				*(Vector *)textureVertexes.getElementAtIndex(t3));
			faces->add(triangle);
			++line;
			return;	
		}
		n1 = tokenizer->nextToken()->toInt() - 1;
		v2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		t2 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		n2 = tokenizer->nextToken()->toInt() - 1;
		v3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		t3 = tokenizer->nextToken()->toInt() - 1;
		tokenizer->nextToken();
		n3 = tokenizer->nextToken()->toInt() - 1;
		token = tokenizer->nextToken();
		if (*token != "\n") {
			v4 = token->toInt() - 1;
			tokenizer->nextToken();
			t4 = tokenizer->nextToken()->toInt() - 1;
			tokenizer->nextToken();
			n4 = tokenizer->nextToken()->toInt() - 1;
			token = tokenizer->nextToken();
			if (*token != "\n") {
				printf("Syntax Error: line %d   unexpected token\n", line);
				exit(1);
			}
			Triangle *triangle1 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v2),
				*(Vector *)vertexes.getElementAtIndex(v3));
			triangle1->setTextureVectors(
				*(Vector *)textureVertexes.getElementAtIndex(t1),
				*(Vector *)textureVertexes.getElementAtIndex(t2),
				*(Vector *)textureVertexes.getElementAtIndex(t3));
			triangle1->setPhongVectors(
				*(Vector *)vertexNormals.getElementAtIndex(n1),
				*(Vector *)vertexNormals.getElementAtIndex(n2),
				*(Vector *)vertexNormals.getElementAtIndex(n3));
			faces->add(triangle1);
			Triangle *triangle2 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v3),
				*(Vector *)vertexes.getElementAtIndex(v4));
			triangle2->setTextureVectors(
				*(Vector *)textureVertexes.getElementAtIndex(t1),
				*(Vector *)textureVertexes.getElementAtIndex(t3),
				*(Vector *)textureVertexes.getElementAtIndex(t4));
			triangle2->setPhongVectors(
				*(Vector *)vertexNormals.getElementAtIndex(n1),
				*(Vector *)vertexNormals.getElementAtIndex(n3),
				*(Vector *)vertexNormals.getElementAtIndex(n4));
			faces->add(triangle2);
			++line;
			return;
		}
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
		++line;
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
		token = tokenizer->nextToken();
		if (*token != "\n") {
			v4 = token->toInt() - 1;
			tokenizer->nextToken();
			tokenizer->nextToken();
			n4 = tokenizer->nextToken()->toInt() - 1;
			if (*tokenizer->nextToken() != "\n") {
				printf("Syntax Error: line %d   unexpected token\n", line);
				exit(1);
			}
			Triangle *triangle1 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v2),
				*(Vector *)vertexes.getElementAtIndex(v3));
			triangle1->setPhongVectors(
				*(Vector *)vertexNormals.getElementAtIndex(n1),
				*(Vector *)vertexNormals.getElementAtIndex(n2),
				*(Vector *)vertexNormals.getElementAtIndex(n3));
			faces->add(triangle1);
			Triangle *triangle2 = new Triangle(
				"triangle",
				material,
				*(Vector *)vertexes.getElementAtIndex(v1),
				*(Vector *)vertexes.getElementAtIndex(v3),
				*(Vector *)vertexes.getElementAtIndex(v4));
			triangle2->setPhongVectors(
				*(Vector *)vertexNormals.getElementAtIndex(n1),
				*(Vector *)vertexNormals.getElementAtIndex(n3),
				*(Vector *)vertexNormals.getElementAtIndex(n4));
			faces->add(triangle2);
			++line;
			return;
		}
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
		faces->add(triangle);
		++line;
		return;
	}
}

inline void Parser::parse_v() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	vector->z = tokenizer->nextToken()->toFloat();
	if (*tokenizer->nextToken() != "\n") {
		printf("Syntax Error: line %d   unexpected token\n", line);
		exit(1);
	}
	vertexes.add(vector);
	++line;
}

inline void Parser::parse_vn() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	vector->z = tokenizer->nextToken()->toFloat();
	if (*tokenizer->nextToken() != "\n") {
		printf("Syntax Error: line %d   unexpected token\n", line);
		exit(1);
	}
	vertexNormals.add(vector);
	++line;
}

inline void Parser::parse_vt() {
	Vector *vector = new Vector();
	vector->x = tokenizer->nextToken()->toFloat();
	vector->y = tokenizer->nextToken()->toFloat();
	if (*tokenizer->nextToken() != "\n") {
		if (*tokenizer->nextToken() != "\n") {
			printf("Syntax Error: line %d\n   unexpected token", line);
			exit(1);
		} 
	}
	textureVertexes.add(vector); 
	++line;
}

inline void Parser::parse_g() {
	printf("Warning: line %d   object group declarations not supported\n", line);
	fflush(stdout);
	if (*tokenizer->nextToken() != "\n") tokenizer->nextToken();
	++line;
}

inline void Parser::parse_usemtl() {
	String *token = tokenizer->nextToken();
	Material *mtl = findMaterial(token);
	if (!mtl) {
		printf("Error: line %d   undefined reference to material \"%s\"", line, token->getString());
		exit(1);
	}
	material = *mtl;
	tokenizer->nextToken();
	++line;
}

inline void Parser::parse_Ka() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->color = color;
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_Kd() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->diffusionCoefficient = color;
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_Ks() {
	Color color;
	color.setRed(materialTokenizer->nextToken()->toFloat()); 
	color.setGreen(materialTokenizer->nextToken()->toFloat()); 
	color.setBlue(materialTokenizer->nextToken()->toFloat());
	((Material *)materials.tail->data)->specularCoefficient = color;
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_Ns() {
	((Material *)materials.tail->data)->specularExponent = materialTokenizer->nextToken()->toInt();
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_newmtl() {
	materials.add(new Material(*materialTokenizer->nextToken()));
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_illum() {
	((Material *)materials.tail->data)->shadingModel = materialTokenizer->nextToken()->toInt();
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_mtllib() { 
	String path;
	String *token = tokenizer->nextToken();
	while (*token != "\n") {
		path += *token;
		token = tokenizer->nextToken();
	}
	parseMaterialLibrary(path);
	++line;
}

inline void Parser::parse_map_Ka() {
	Image image;
	String path;
	String *token = materialTokenizer->nextToken();
	while (*token != "\n") {
		path += *token;
		token = materialTokenizer->nextToken();
	}
	((Material *)materials.tail->data)->ambientTexture = image.readImage(path);
}

inline void Parser::parse_map_Kd() {
	Image image;
	String path;
	String *token = materialTokenizer->nextToken();
	while (*token != "\n") {
		path += *token;
		token = materialTokenizer->nextToken();
	}
	((Material *)materials.tail->data)->diffuseTexture = image.readImage(path);
}

inline void Parser::parse_map_Ks() {
	while (*tokenizer->nextToken() != '\n');
}

inline void Parser::parse_d() {
	material.textureAlpha = materialTokenizer->nextToken()->toFloat();
	if (*materialTokenizer->nextToken() != '\n') {
		printf("Syntax Error: line %d\n   unexpected token", line);
		exit(1);
	}
}

inline void Parser::parse_s() {
	printf("Warning: line %d   ? declarations not supported\n", line);
	fflush(stdout);
	while (*tokenizer->nextToken() != '\n');
	++line;
}

inline void Parser::parse_l() {
	printf("Warning: line %d   line declarations not supported\n", line);
	fflush(stdout);
	while (*tokenizer->nextToken() != '\n');
	++line;
}

inline void Parser::parse_p() {
	printf("Warning: line %d   point declarations not supported\n", line);
	fflush(stdout);
	while (*tokenizer->nextToken() != '\n');
	++line;
}

inline void Parser::parse_material_comment() {
	while (*materialTokenizer->nextToken() != "\n");
}

inline void Parser::parse_comment() {
	while (*tokenizer->nextToken() != "\n");
	++line;
}
