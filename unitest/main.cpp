#include "Parser.h"

int main() {
	//Parser parser = Parser();
	//parser.parse("tetrahedron.obj");
	Image image;
	Pixmap *pixmap;
	pixmap = image.readImage("brazil-flag.png");
	image.writeImage("out.png", pixmap);
}
