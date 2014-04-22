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

void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    /* for each polygon { */
        /* select material properties -- ambient, diffuse, specular, exponent Ka Kd Ks Ns*/
            //	glMaterialfv(GL_FRONT_AND_BACK,   GL_AMBIENT, something.Ka);
	        //  glMaterialfv(GL_FRONT_AND_BACK,   GL_DIFFUSE, something.Kd);
	        //  glMaterialfv(GL_FRONT_AND_BACK,  GL_SPECULAR, something.Ks);
	        //   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, something.Ns);
        /* bind a texture if applicable */
            //  if (something.hasTexture()) {
            //      glBindTexture (GL_TEXTURE_2D, something.textureID);
            //  }
        /* render the polygon */
        	/*  draw each face as follows */
	        //  glColor3f(1, 1, 0);
	        //  glBegin(GL_POLYGON);
	        /*  for each vertex { */
            //      glNormal3fv( something.thisvertexnormal );
            //      if (something.hasTexture() && something.hasTextureCoords())
	        //         { glTexCoord3fv(something.thisvertextexturecoords); } 
            //      glVertex3fv( something.thisvertexlocation );
            //  }
            //  glEnd();	//	GL_POLYGON
    //}
    /* enable lighting if it's called for */
    /* for each light -- activate lights */
    /* now shade everything */
    /* if I'm forgetting something add it here */
    /* now call gluLookAt to transform everything to where the camera is now */

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

     case 'r':
     case 'R':
      //trace image and display in window
      break;
      
     case 'w':
     case 'W':
      //write raytraced image to disk
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
    RayTracer rayTracer;
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

    glutDisplayFunc(display); 
    glutKeyboardFunc(handleKey);
    glutReshapeFunc(reshape);

    glClearColor(1, 1, 1, 1);
    glutMainLoop();
    return 0;
}
