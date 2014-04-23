#include "Rasterizer.h"

int drawScene () {
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
        	// draw each face...
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
    /* for each light -- add lights */
    /* now shade everything */
    /* if I'm forgetting something add it here */
    /* now call gluLookAt to transform everything to where the camera is now */
    return true;
}
