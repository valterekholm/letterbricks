#include <unistd.h>//usleep
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../drinlett.h"

int main(int argc, char **argv){

  struct coord2d coords[6];

  struct coord2d l0 = mc2d(0,0);
  struct coord2d r0 = mc2d(2,0);
  struct coord2d l1 = mc2d(2,2);
  struct coord2d r1 = mc2d(0,0);
  struct coord2d l2 = mc2d(0,0);
  struct coord2d r2 = mc2d(3,0);

  struct coord2d l3 = mc2d(-0.71, 0.71);
  struct coord2d r3 = mc2d(0.71, 0.71);

  coords[0] = l0;
  coords[1] = r0;
  coords[2] = l1;
  coords[3] = r1;
  coords[4] = l2;
  coords[5] = r2;
  coords[6] = l3;
  coords[7] = r3;

  struct cirkle2d c2 = deriveEvenPolygonCenterAndRadius(coords[0], coords[1], 4);
  struct cirkle2d c3 = deriveEvenPolygonCenterAndRadius(coords[2], coords[3], 4);
  struct cirkle2d c4 = deriveEvenPolygonCenterAndRadius(coords[4], coords[5], 6);
  struct cirkle2d c5 = deriveEvenPolygonCenterAndRadius(coords[6], coords[7], 5);  
  //printCirkle2d(c2);
  //printCirkle2d(c3);
  //printCirkle2d(c4);
  printCirkle2d(c5);
  
}
