/*
   main.cpp
   
   Raytracing       -- Jonathan Hicks
   OpenGL Rendering -- Anthony Bellew

   based heavily on code from
   CP SC 405/605 Computer Graphics    Donald H. House     12/2/08
   
   OpenGL/GLUT Program to View a 3D cube or teapot using a mipmapped textures
   
   Keyboard keypresses have the following effects:
   i       	- reinitialize (reset program to initial default state)
   p		- toggle between orthographic and perspective view
   q or Esc	- quit
   s		- toggle between flat shading and smooth shading
   o		- toggle between wireframe and shaded viewing

   Camera and model controls following the mouse:
   model yaw	- left-button, horizontal motion, rotation of the model around the y axis
   model tilt	- left-button, vertical motion, rotation of the model about the x axis
   camera yaw	- middle-button, horizontal motion, rotation of the camera about the y axis
   camera tilt	- middle-button, vertical motion, rotation of the camera about the x axis
   approach	- right-button, vertical or horizontal motion, translation of camera along z axis
   
   usage: ./run.sh
 */

#include <cassert>
#include <iostream>
#include "List.h"
#include "RayTracer.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "ParallelLight.h"

#include <GL/gl.h>
#include <GL/glu.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cstdlib>
#include <cstdio>

RayTracer rayTracer;

inline double randf(double min, double max) {
    double f = static_cast<double>(rand()) / RAND_MAX;
    return min + f * (max - min);
}

using namespace std;

//*****************************************************************
//  Demo Code
//*****************************************************************

#define FALSE		0
#define TRUE		1

#define HORIZONTAL	0
#define VERTICAL	1

#define ESC		27	// numeric code for keyboard Esc key

#define WIDTH           800	// initial window dimensions
#define HEIGHT          600

#define ORTHO		0	// projection system codes
#define PERSPECTIVE	1

#define NONE		-1	// used to indicate no mouse button pressed

#define DRAWWIDTH	200	// view volume sizes (note: width and
#define DRAWHEIGHT	150	//   height should be in same ratio as window)
#define NEAR		10	// distance of near clipping plane
#define FAR		1000	// distance of far clipping plane

#define CUBEWIDTH	50	// dimension of the cube
#define DEPTH		-100	// initial z coord. of center of cube

#define ROTFACTOR	0.2     // degrees rotation per pixel of mouse movement
#define XLATEFACTOR	0.5     // units of translation per pixel of mouse movement

#define TEXTUREWIDTH	64	// dimensions of texture map image
#define TEXTUREHEIGHT	64

#define AMBIENT_FRACTION 0.2
#define DIFFUSE_FRACTION 0.8
#define SPECULAR_FRACTION 0.3

// Colour_Hs used for lights, and materials for coordinate axes
const float DIM_PALEBLUE[] = {0.1, 0.1, 0.3, 1};
const float BRIGHT_PALEBLUE[] = {0.5, 0.5, 1, 1};
const float GRAY[] = {0.3, 0.3, 0.3, 1};
const float WHITE[] = {1, 1, 1, 1};
const float DIM_WHITE[] = {0.8, 0.8, 0.8, 1};
const float DIM_RED[] = {0.3, 0, 0, 1};
const float RED[] = {1, 0, 0, 1};
const float DIM_GREEN[] = {0, 0.3, 0, 1};
const float GREEN[] = {0, 1, 0, 1};
const float DIM_BLUE[] = {0, 0, 0.3, 1};
const float BLUE[] = {0, 0, 1, 1};

enum TEXTUREMODE{NOTEXTURE, NEARTEXTURE, LINEARTEXTURE, MIPMAPTEXTURE};

// white Colour_H for wireframe drawing
float white[3] = {1, 1, 1};

//
// Global variables updated and shared by callback routines
//

// Window dimensions
static double Width = WIDTH;
static double Height = HEIGHT;

// Viewing parameters
static int Projection;

// Model and Shading parameters
static int CubeModel;
static int Axes;

// Camera position and orientation
static double Pan;
static double Tilt;
static double Approach;

// model orientation
static double ThetaX;
static double ThetaY;

// global variables to track mouse and shift key
static int MouseX;
static int MouseY;
static int Button = NONE;

// global variables to track wireframe/shaded mode, material Colour_H, and textuing mode
static int Wireframe;
static int Colour_H;
static int SmoothShading;
static int TextureMode;
static int ColorMode;

// Texture map to be used by program
static GLuint TextureID;	    // texture ID from OpenGL
static unsigned char *TextureImage;   // pixmap for texture image

//
// routine to create an interesting texture image
//
void makeImage(int w, int h, unsigned char *image[]){
  int row, col;
  unsigned char red, alpha;
  unsigned char *imptr;
  
  *image = (unsigned char *)malloc(w * h * 4 * sizeof(unsigned char));
  imptr = *image;
  for(row = 0; row < h; row++)
    for(col = 0; col < w; col++){
      red = ((row * col / 4) % 2) * 255;
      alpha = red;
      *imptr++ = alpha;	  // store Colour_H in little endian order
      *imptr++ = 50;
      *imptr++ = 50;
      *imptr++ = red;
    }
}

//
// Routine to initialize the state of the program to start-up defaults
//
void setInitialState(){
  
  // initial camera viewing and shading model controls
  Projection = PERSPECTIVE;
  
  // model initially solid with smooth shading
  Wireframe = FALSE;
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  TextureMode = NOTEXTURE;
  ColorMode = GL_MODULATE;
  SmoothShading = TRUE;
  
  // initial model is cube and no axes drawn
  CubeModel = TRUE;
  Axes = FALSE;
  
  // initial camera orientation and position
  Pan = 0;
  Tilt = 0;
  Approach = DEPTH;
  
  // initial model orientation
  ThetaX = 0;
  ThetaY = 0;
}

//
// Set up the projection matrix to be either orthographic or perspective
//
void updateProjection(){
  
  // initialize the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // determine the projection system and drawing coordinates
  if(Projection == ORTHO)
    glOrtho(-DRAWWIDTH/2, DRAWWIDTH/2, -DRAWHEIGHT/2, DRAWHEIGHT/2, NEAR, FAR);
  else{
    // scale drawing coords so center of cube is same size as in ortho
    // if it is at its nominal location
    double scale = fabs((double)NEAR / (double)DEPTH);
    double xmax = scale * DRAWWIDTH / 2;
    double ymax = scale * DRAWHEIGHT / 2;
    glFrustum(-xmax, xmax, -ymax, ymax, NEAR, FAR);
  }
  
  // restore modelview matrix as the one being updated
  glMatrixMode(GL_MODELVIEW);
}

//
// routine to draw a set of coordinate axes centered at the origin
//
void drawAxes(float size, int wireframe){

  if(wireframe){     // wireframe drawing, so draw X, Y, Z axes as Colour_Hed lines
    glBegin(GL_LINES);
      glColor3f(1, 0, 0);		  // x axis drawn in red
      glVertex3f(0, 0, 0);
      glVertex3f(size, 0, 0);
      
      glColor3f(0, 1, 0);		  // y axis drawn in green
      glVertex3f(0, 0, 0);
      glVertex3f(0, size, 0);
      
      glColor3f(0, 0, 1);		  // z axis drawn in blue
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, size);
    glEnd();
  }

  else{      // shaded drawing, so draw X, Y, Z axes as solid arrows
    const float height = size;
    
    // draw arrow shafts. they are all white
    glMaterialfv(GL_FRONT, GL_AMBIENT, GRAY);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, WHITE);
    // Z

    // X
    glPushMatrix();
      glRotatef(90, 0, 1, 0);
    glPopMatrix();
    // Y
    glPushMatrix();
      glRotatef(-90, 1, 0, 0);
    glPopMatrix();
    
    // draw arrow heads. X is red, Y is green, and Z is blue
    // Z
    glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, DIM_BLUE);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, BLUE);
      glTranslatef(0, 0, 0.8 * height);
    glPopMatrix();
    // X
    glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, DIM_RED);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, RED);
      glRotatef(90, 0, 1, 0);
      glTranslatef(0, 0, 0.8 * height);
    glPopMatrix();
    // Y
    glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, DIM_GREEN);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN);
      glRotatef(-90, 1, 0, 0);
      glTranslatef(0, 0, 0.8 * height);
    glPopMatrix();
  }
}

//
// routine to draw the current model
//
void drawModel(int cubemodel, int wireframe){
  float ambient_Colour_H[4];
  float diffuse_Colour_H[4];
  float specular_Colour_H[4];
  int shininess;
  
  if(wireframe){
    glDisable(GL_TEXTURE_2D);
    
    // set drawing Colour_H to current hue, and draw with thicker wireframe lines
    glColor3f(white[0], white[1], white[2]);
    glLineWidth(2);
  }
  else{
    // set up material Colour_H to be white
    for(int i = 0; i < 3; i++){
      ambient_Colour_H[i] = AMBIENT_FRACTION * white[i];
      diffuse_Colour_H[i] = DIFFUSE_FRACTION * white[i];
      specular_Colour_H[i] = SPECULAR_FRACTION * white[i];
      shininess = 60;
    }
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Colour_H);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Colour_H);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Colour_H);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    if(TextureMode != NOTEXTURE){
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, ColorMode);
      glBindTexture(GL_TEXTURE_2D, TextureID);	    // set the active texture
      switch(TextureMode){
	case NEARTEXTURE:
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	  break;
	case LINEARTEXTURE:
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  break;
	case MIPMAPTEXTURE:
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	  break;
      }
    }
  }
  

  if(wireframe)
    glutWireTeapot(3 * CUBEWIDTH / 5);
  else
    glutSolidTeapot(3 * CUBEWIDTH / 5);
  
  glDisable(GL_TEXTURE_2D);
}

//
// Display callback
//
void doDisplay(){
  // distant light source, parallel rays coming from front upper right
  const float light_position[] = {1, 1, 1, 0};
  
  // clear the window to the background Colour_H
  glClear(GL_COLOR_BUFFER_BIT);
  
  if(!Wireframe)
    glClear(GL_DEPTH_BUFFER_BIT);  // solid - clear depth buffer
  
  if(!Wireframe && SmoothShading)  // establish shading model, flat or smooth
    glShadeModel(GL_SMOOTH);
  else
    glShadeModel(GL_FLAT);
  
  // light is positioned in camera space so it does not move with object
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  
  // establish camera coordinates
  glRotatef(Tilt, 1, 0, 0);	    // tilt - rotate camera about x axis
  glRotatef(Pan, 0, 1, 0);	    // pan - rotate camera about y axis
  glTranslatef(0, 0, Approach);     // approach - translate camera along z axis
  
  // rotate the model
  glRotatef(ThetaY, 0, 1, 0);       // rotate model about x axis
  glRotatef(ThetaX, 1, 0, 0);       // rotate model about y axis

  if(Wireframe) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  
  // TODO: DRAW THE THING wireframe or not
        Node* shapeHead = rayTracer.getScene()->shapes.head;
        Node* shapePtr  = shapeHead; 
        int polyCount = 0;

        while (shapePtr){
            polyCount++;

            Triangle* currentTri = (Triangle *)shapePtr->data; 

                float currentNorm[3] = { (float)((Vector)(currentTri->orientation)).x,
                                         (float)((Vector)(currentTri->orientation)).y,
                                         (float)((Vector)(currentTri->orientation)).z };

                float currentVertex0[3]    = { (float)((Vector)(currentTri->p0)).x,
                                               (float)((Vector)(currentTri->p0)).y,
                                               (float)((Vector)(currentTri->p0)).z };

                float currentVertex1[3]    = { (float)((Vector)(currentTri->p1)).x,
                                               (float)((Vector)(currentTri->p1)).y,
                                               (float)((Vector)(currentTri->p1)).z };

                float currentVertex2[3]    = { (float)((Vector)(currentTri->p2)).x,
                                               (float)((Vector)(currentTri->p2)).y,
                                               (float)((Vector)(currentTri->p2)).z };

            glBegin(GL_TRIANGLES); //--

                //glPushMatrix();

                //glColor3f((float)(randf(0.0,1.0)),(float)(randf(0.0,1.0)),(float)(randf(0.0,1.0)));

                glNormal3fv(currentNorm);
                // insert texture array and glTexCoords2f() call here;
                glVertex3fv(currentVertex0);

                glNormal3fv(currentNorm);
                // insert texture array and glTexCoords2f() call here;
                glVertex3fv(currentVertex1);

                glNormal3fv(currentNorm);
                // insert texture array and glTexCoords2f() call here;
                glVertex3fv(currentVertex2); 

                //glPopMatrix();

            glEnd();

            shapePtr = shapePtr->next;
        }
    
  glutSwapBuffers();
}

//
// Keyboard callback routine. 
// Set various modes or take actions based on key presses
//
void handleKey(unsigned char key, int x, int y){
  
  switch(key){
      
    case 'p':			// P -- toggle between ortho and perspective
    case 'P':
      Projection = !Projection;
      updateProjection();
      glutPostRedisplay();
      break;
            
    case 'i':			// I -- reinitialize 
    case 'I':
      setInitialState();
      updateProjection();
      glutPostRedisplay();
      break;
        
    case 'q':			// Q or Esc -- exit program
    case 'Q':
    case ESC:
      exit(0);
      
    case 's':			// S -- toggle between flat and smooth shading
    case 'S':
      SmoothShading = !SmoothShading;
      glutPostRedisplay();
      break;

     case 'r':
     case 'R':
      //trace image and display in window
      std::cout << "Rendering..." << std::endl;
      //TODO: pass OpenGL camera info to rayTracer
      // direction
      // orientation
      // position
      // screen height/width/aspect
      rayTracer.render();
      std::cout << "Rendering complete." << std::endl;
      //TODO: system call to display traced image
      break;
      
     case 'w':
     case 'W':
      //write raytraced image to disk
      //TODO: add prompt
      std::cout << "Saving..." << std::endl;
      rayTracer.saveImage("images/out.png");
      std::cout << "Saving complete." << std::endl;
      break;
      
    case 'o':			// M -- toggle between wireframe and shaded viewing
    case 'O':
      Wireframe = !Wireframe;
      if(Wireframe){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
      }
      else{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
      }
      glutPostRedisplay();
      break;
  }
}

//
// Mouse Button Callback
// on button press, record mouse position and which button is pressed
//
void handleButtons(int button, int state, int x, int y){
  
  if(state == GLUT_UP)
    Button = NONE;		// no button pressed
  else{
    MouseY = -y;		// invert y window coordinate to correspond with OpenGL
    MouseX = x;
    
    Button = button;		// store which button pressed
  }
}

//
// Mouse Motion Callback
// when mouse moves with a button down, update appropriate camera parameter
//
void handleMotion(int x, int y){
  int delta;
  
  y = -y;
  int dy = y - MouseY;
  int dx = x - MouseX;
  
  switch(Button){
    case GLUT_LEFT_BUTTON:
      ThetaX -= ROTFACTOR * dy;
      ThetaY += ROTFACTOR * dx;
      glutPostRedisplay();
      break;
    case GLUT_MIDDLE_BUTTON:
      Pan -= ROTFACTOR * dx;
      Tilt += ROTFACTOR * dy;
      glutPostRedisplay();
      break;
    case GLUT_RIGHT_BUTTON:
      delta = (fabs(dx) > fabs(dy)? dx: dy);
      Approach += XLATEFACTOR * delta;
      glutPostRedisplay();
      break;
  }
  
  MouseX = x;
  MouseY = y;
}

//
// Reshape Callback
// Keep viewport the entire screen
//
void doReshape(int width, int height){
  
  glViewport(0, 0, width, height);
  Width = width;
  Height = height;
  
  updateProjection();
}

//
// Initialize OpenGL to establish lighting and Colour_Hs
// and initialize viewing and model parameters
//
void initialize(){
  
  // initialize modelview matrix to identity
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // specify window clear (background) Colour_H to be black
  glClearColor(0, 0, 0, 0);
  
  // position light and turn it on
  glEnable(GL_LIGHT0);
  
  // initialize viewing and model parameters
  setInitialState();
  updateProjection();
  
  //
  // create the texture map image and assign a texture ID
  //
  makeImage(TEXTUREWIDTH, TEXTUREHEIGHT, &TextureImage);   // create texture pixmap
  glGenTextures(1, &TextureID);		  // get OpenGL ID for this texture

  // make this texture the active texture
  glBindTexture(GL_TEXTURE_2D, TextureID);

  // set texture drawing parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // build mipmap in texture memory
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXTUREWIDTH, TEXTUREHEIGHT,		    GL_RGBA, GL_UNSIGNED_BYTE, TextureImage);

  // This is texture map sent to texture memory without mipmapping:
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTUREWIDTH, TEXTUREHEIGHT,
  //	       0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage);  
}

//
// Main program to create window, setup callbacks, and initiate GLUT
//
int main(int argc, char* argv[]){

    rayTracer.cameraViewPoint(Vector(0, -40, 35));
    rayTracer.cameraViewDirection(Vector(0, 1, -0.7));
    rayTracer.screenPixelWidth(600);
    rayTracer.cameraFocalLength(0.5);
    rayTracer.cameraOrientation(Vector(0,0,1));
    rayTracer.loadShape("teapot-lite.obj");
    rayTracer.ambientLight(Color(0,0,0));
    rayTracer.enableReflections();

    //rayTracer.addLight(new SpotLight("SpotLight1", Color(1, 1, 1), Vector(0, 0, 100), Vector(0, 0, -1), 1, 20, 5));
    rayTracer.addLight(new PointLight("PointLight1", Vector(0,40, 40), Color(1, 1, 1), 1));
    rayTracer.addLight(new PointLight("PointLight1", Vector(40,0,0), Color(1, 1, 1), 0.8));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,1,0), 0.5));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,0,-1), 0.5));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(1,1,0), 0.4));

    //rayTracer.render();
    //rayTracer.saveImage("images/out.png");

  
  // start up the glut utilities
  glutInit(&argc, argv);
  
  // create the graphics window, giving width, height, and title text
  // and establish double buffering, RGBA Colour_H
  // Depth buffering must be available for drawing the shaded model
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("3D Texture Viewer with Mipmaps");
  
  // register callback to draw graphics when window needs updating
  glutDisplayFunc(doDisplay);
  glutReshapeFunc(doReshape);
  glutKeyboardFunc(handleKey);
  glutMouseFunc(handleButtons);
  glutMotionFunc(handleMotion);
  
  initialize();
  
  glutMainLoop();
}
