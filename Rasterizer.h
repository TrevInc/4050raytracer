#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <GL/gl.h>
#include <GL/glu.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

int drawScene();

#endif
