/*
Jonathan Hicks
4/1/14

The program will fail if the parser encounters an error while parsing.
The .mtl file must be in the same directory as the .obj file.
All camera settings are in the camera.txt.
The ambient light is set low by default and there is one spotlight.
Error checking will be implimented later as well as a text file to set up the scene.
*/



#include "rayTracer.h"

Scene *scene;
Pixmap *pixmap;
Image *image;
Tokenizer *tokenizer;
bool writeImage;
int samples;
String outputPath;

void displayImage(void) {
   glRasterPos2i(0, 0);
   glDrawPixels(pixmap->getColumnSize(), pixmap->getRowSize(), GL_RGBA, GL_UNSIGNED_BYTE, pixmap->getPixles());
   glutReshapeWindow(pixmap->getColumnSize(), pixmap->getRowSize());
   glutSwapBuffers();
}

void handleKey(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
    case 'W':
      if (writeImage) image->writeImage(outputPath, pixmap);
      break;
    case 'q':
    case 'Q':
    case 27:
      exit(0);
  }
}

void handleReshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    
  	Parser *parser = new Parser();
  	Camera camera = parser->parseConfig("camera.txt");
  	image = new Image();
   scene = new Scene();
	String objectFile;

   switch (argc) {
      case 2:
			objectFile = argv[1];
         break;
      case 3:
      	objectFile = argv[1];
         samples = atoi(argv[2]);
         camera.enableAntialiasing();
         camera.setAntialiasingLevel(samples);
         break;
      case 4:
      	objectFile = argv[1];
			samples = atoi(argv[2]);
			camera.enableAntialiasing();
         camera.setAntialiasingLevel(samples); 
         outputPath = argv[3];
         writeImage = true;
         break;
      default:
         std::cout << "Usage: raytrace [modelfile.obj] [samples] [outputFile]" << std::endl;
         return 1;
    }
     
    parser->parse(objectFile.getString());
    
    camera.addAABB(parser->getAABB());
   
    scene->addCamera(&camera);
    scene->setAmbientLight(Color(0.1, 0.1, 0.1));
    //scene->addShape(new Sphere("Sphere1", RED_GLASS, 0.050, Vector(-0.3, 0.1, -0.5)));
    //scene->addShape(new Sphere("Sphere2", GREEN_GLASS, 0.150, Vector(0.0, -0.2, -0.8)));
    //scene->addShape(new Sphere("Sphere3", BLUE_GLASS, 0.300, Vector(0.3, 0.3, -1.1)));
    //scene->addShape(new Plane("Plane1", IVORY, Vector(0, 0, 1), Vector(0, 0, -5)));
    //scene->addShape(new Sphere("Sphere4", ORANGE_GLASS, 0.075, Vector(0.1, 0.2, -0.3)));
    //scene->addShape(new Sphere("Sphere5", PURPLE_GLASS, 0.225, Vector(-0.2, -0.25, -0.4)));
    //scene->addLight(new PointLight("PointLight1", Vector(1, 0.3, 0), Color(WHITE), 1));
    //scene->addLight(new PointLight("PointLight2", Vector(2, 0.5, 3), Color(WHITE), 1));
    //scene->addLight(new PointLight("PointLight3", Vector(0, 1, 2), Color(WHITE), 1));
    scene->addLight(new SpotLight("SpotLight1", Color(WHITE), Vector(0, 0, 5), Vector(-0.5, 0, -1), 1, 20, 10));

	List *faces = parser->getFaces();
	Node *node = faces->head;
	while (node) {
		scene->addShape((Shape *)node->data);
		node = node->next;
	}
	
    scene->renderImages();
    
    pixmap = (Pixmap *)scene->getImages()->head->data;

    image->writeImage("images/out.png", pixmap);
    
    //delete image;
    delete parser;
  
  /*glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(100, 100);
  glutCreateWindow("Ray Tracer");
  glutDisplayFunc(displayImage);
  glutKeyboardFunc(handleKey);
  glutReshapeFunc(handleReshape);
  glClearColor(0, 0, 0, 1);
  glutMainLoop();*/
  
  //delete pixmap;
}