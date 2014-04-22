#include <iostream>
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

RayTracer rayTracer;

void display () {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* for each polygon P in rayTracer.scene.shapes { */
    //TODO: can you write an iterator over List for this?

        /* render the polygon */
        	/*  draw each face as follows */
	        //  glColor3f(1, 1, 0);
	        //  glBegin(GL_POLYGON); // TODO: can also write separate render pipes of fixed size for
                                     // tris and quads if you don't want to make a vertex iterator

	        /*  for each vertex V in P { */ // TODO: make iterator for vertices
            //      glNormal3fv( P.orientation );
            //      if (something.hasTexture() && something.hasTextureCoords())
	        //         { glTexCoord3fv( /* texture map data here*/ ); } 
            //      glVertex3fv( /* p0, p1, p2 as applicable */ );
            //  }

            //  glEnd();	//	GL_POLYGON
    //}


    /* now call gluLookAt to transform everything to where the camera is now */
    /* found at http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml */

    //TODO: get the appropriate values for this from the camera
    /*
    gluLookAt(	
    eyeX, eyeY, eyeZ,           //Location of viewscreen
 	centerX, centerY, centerZ,  //Direction to look
    upX, upY, upZ);             //Direction of up
    */

    /* now pipe this beautiful image to the screen */
    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {

  // put window shaping code in here
  // make the viewport the entire window
  glViewport(0, 0, w, h);
  
  // define the drawing coordinate system on the viewport
  // to be measured in pixels
  glMatrixMode(GL_PROJECTION); //Orthogonal if selected
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void handleKey(unsigned char key, int x, int y){
  
  switch(key){

     //TODO: keybindings for arrows and A/Z to move in scene
     //Do by altering dimensions of eye point

     //TODO: keybindings for TGFH to aim up/down/left/right
     //Since WASD is taken. Use trig to rotate forward/up vectors

     case 'r':
     case 'R':
      //trace image and display in window
      std::cout << "Rendering..." << std::endl;
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
      
    case 'q':		
    case 'Q':
    case 27:		
      exit(0);        
      
    default:		
      return;
  }
}

int main( int argc, char** argv) {
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

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (600, 475); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Raytracer Final");

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

    // TODO: count up the number of textures in the image -- iterator or counter?
    // TODO: Generate texture names for every texture

    // glGenTextures(	GLsizei n, GLuint * textures); //<< texture name unsigned ints stored in this array

    /* for each polygon P in rayTracer.scene.shapes { */
    //TODO: can you write an iterator over List for this?

        /* select material properties -- ambient, diffuse, specular, exponent Ka Kd Ks Ns*/
            //	glMaterialfv(GL_FRONT_AND_BACK,   GL_AMBIENT, P.material.ambientCoefficient); // TODO: doesn't exist -- need
	        //  glMaterialfv(GL_FRONT_AND_BACK,   GL_DIFFUSE, P.material.diffuseCoefficient);
	        //  glMaterialfv(GL_FRONT_AND_BACK,  GL_SPECULAR, P.material.specularCoefficient);
	        //   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, P.material.specularExponent);

        /* bind a texture if applicable */

            //  if (P.textureMap == true) {
            //      glBindTexture (GL_TEXTURE_2D, P.material->ambientTexture.textureID); // TODO: get or store textureID of texture being bound
            //  }

    //}

    /* enable lighting if it's called for */

    //if (rayTracer.scene.lights.getSize > 0) {
    //
    // TODO: write iterator for list of lights to define them here
    // TODO: glEnable(GL_LIGHT0) through whatever

    /* traverse list of lights and declare glLightfv for each */
    /* instructions for type params at http://www.opengl.org/sdk/docs/man2/xhtml/glLight.xml‎ */
    //
    //  glLightfv(light_number, pname,  params);
    //
    //}
    /* for each light that is on -- assign location/directions from your list of lights */
    //if (rayTracer.scene.lights.getSize > 0) {
    // TODO: use same iterator for lights to move them around the scene

         //GLfloat lightpos[] = {.5, 1., 1., 0.}; //or whatever your light position is
         //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


    //}    

    /* if I'm forgetting something add it here */


    glutDisplayFunc(display); 
    glutKeyboardFunc(handleKey);
    glutReshapeFunc(reshape);

    glClearColor(1, 1, 1, 1);
    glutMainLoop();
    return 0;
}
