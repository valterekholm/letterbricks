#include <unistd.h>//usleep
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*this program was made to find the steps involved in drawing cells connected to form letter B*/
/*To build the junktion of the two rings in 'B' I begin using a 5 corner shape, needing to make a new struct; polyCell*/
/*made after letter-a.cc, 4 dec -21*/
/*notes*/
/*2022-11-23 got stuck on the step from the middle 5-sided polygon to the 3:rd square. The 3:rd polygon is missplaced to far down/left*/
/*Also stuck in the formulation, about the order of actions, and should each polytiles polygon have a 0/0 position to easy up scaling,*/
/*cloning it to a temp struct (like turning_square_4, where one square was shared) for the rendering or should they have all positions firm*/
/*also wondering if the recursive calls could mess upp the positions, as each position/tile is calculated while iterating/building/rendering */
/*letter C would be easier*/

// the GLUT and OpenGL libraries have to be linked correctly
// g++ rotateCube.cc -lglut -lGL -lGLU
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../drinlett.h"

using namespace std;

// The coordinates for the vertices of the cube

double z = 1;

float angle = 0.0;

float scale = 1;//for squares

double getRatioPolygonSideAndRadius(int nrSides);

void resizePolyCell(struct polyCell * pc, double newRadius){

  printf("resizePolyCell, from %f to %f\n", pc->radius, newRadius);
  double sizesRatio = newRadius / pc->radius;

  double offsetX = pc->center.x;
  double offsetY = pc->center.y;

  for(int i=0; i<pc->nrCorners; i++){
    double tempx = pc->points[i]->x - offsetX;
    double tempy = pc->points[i]->y - offsetY;
    tempx *= sizesRatio;
    tempy *= sizesRatio;
    pc->points[i]->x = tempx+offsetX;
    pc->points[i]->y = tempy+offsetY;
  }
}

//"even" - that all sides are of same length
//in case of a 3,4 (polygon check) arg, this function gives how much the 4-sider should increase (scale) to have sides as long as the 3-sider
double evenPolygonsSideRatio(char nrSides1, char nrSides2){
  printf("evenPolygonsSideRatio with %d and %d\n", nrSides1, nrSides2);
  if(nrSides1 == 0 || nrSides2 == 0){
    printf("why give 0 as arg?\n");
    return 0;
  }
  
  if(nrSides1 == nrSides2){
    return 1;
  }

  if(nrSides1 >= nrSides2){
    printf("arg 1 should be less than arg 2\n");
    return 0;
  }//first arg should be less than second

  struct coord2d fourPoints[4];

  fourPoints[0] = fourPoints[2] = sin_cos_degr(0);
  fourPoints[1] = sin_cos_degr(360/(double)nrSides1);
  printStructCoord2d(fourPoints[1], 1);
  fourPoints[3] = sin_cos_degr(360/(double)nrSides2);
  printStructCoord2d(fourPoints[3], 1);

  double dist1 = getDistBetweenCoord2ds(fourPoints[0], fourPoints[1]);
  double dist2 = getDistBetweenCoord2ds(fourPoints[2], fourPoints[3]);
  printf("dist1: %f, dist2: %f\n", dist1, dist2);
  //dist1 should be greater than dist2, as any side of a likesided triangle is longer than a square (fit in a cirkle)

  return dist1/dist2;
}

// printing text info
void printGamePolyTile(struct gamePolyTile gpt){
  printf("printGamePolyTile\n-----------------\n");
  printf("nrCorners: %d\n", gpt.pc->nrCorners);
  printf("angle: %f\n", gpt.angle);
  printf("polycell:\n");
  printf("center: ");
  printStructCoord2d(gpt.pc->center, 1);
  printf("points:\n");
  for(int i = 0; i<gpt.pc->nrCorners; i++){
    printStructCoord2d(*(gpt.pc->points[i]), 1);
  }
  double distFirst2 = getDistBetweenCoord2ds(*(gpt.pc->points[0]), *(gpt.pc->points[1]));
  printf("Distance between two first corners: %f\n", distFirst2);  
}

void rotatePolyCell(struct polyCell pc, double rotate){
  printf("rotatePolyCell\n");
  if(rotate != 0){
    printf("rotate is %.1f... ", rotate);
    
    for(int i=0; i< pc.nrCorners; i++){
      struct coord2d newPoint = rotatePoint(*(pc.points[i]), pc.center, rotate);
      pc.points[i]->x = newPoint.x;
      pc.points[i]->y = newPoint.y;
    }
  }  
}

//having offset as argument could unburden the polyCell of any relocation assignment
void renderPolyCell(struct polyCell pc, struct coord2d * offset = NULL){

  printf("renderPolyCell... ");

  glBegin(GL_POLYGON);
  double color = 0.8;
  glColor3f(0.5, 0.3, color);
  for(int i=0; i< pc.nrCorners; i++){
    glVertex3f(pc.points[i]->x, pc.points[i]->y, 0);
  }
  glEnd();
}

void movePCPoints(struct polyCell pc, double moveX, double moveY){
  for(int i=0; i< pc.nrCorners; i++){
    pc.points[i]->x += moveX;
    pc.points[i]->y += moveY;
  }
}

//for circle based polygon tiles
//a recursive function
void renderPolyTiles(struct gamePolyTile * gpt, int treeLevel, struct gamePolyTile * prev = NULL){
  printf("renderPolyTiles, treeLevel %d, name: %c\n", treeLevel, gpt->name);
  double newAngle = 0, diffX, diffY;
  if(prev == NULL){
    printf("This is the first polygon\n");
  }
  else{
    printf("This is a follower polygon\n");

    //look at prev
    for(int i=0; i < prev->pc->nrCorners-1; i++){
      if(gpt == prev->neighbours[i]){
	//get base points
	//TODO: find error, the lef, rig got wrong
	struct coord2d lef = mc2d((prev->pc->points[i+1])->x, (prev->pc->points[i+1])->y);
	struct coord2d rig = mc2d((prev->pc->points[i])->x, (prev->pc->points[i])->y);
	printf("This is neighbour at dock %d, with coords (left,right) :\n", i);
	printStructCoord2d(lef);
	printStructCoord2d(rig);
	//find angle from the dock's angle...
	newAngle = getAngleBetweenPoints(lef, rig);

	//side ratio
	//sides of the two "even" polygons
	double sRatio;

	/*printf("the previous one had sides of length: %.2f, this one have sides of length %.2f",
	       dists3_55[prev->pc->nrCorners]*prev->pc->radius,
	       dists3_55[gpt->pc->nrCorners]*gpt->pc->radius);*/ //verkar funka

	//newAngle is between left->right base point but need angle "up" from that base
	newAngle -= 90;
	//printf("newAngle is %.1f\n", newAngle); //verkar funka

	//set angle
	gpt->angle = newAngle;
	//printf("This angle is set to %.1f\n", gpt->angle); //verkar funka
	
		
	//derive where the new circle should be
	//also getting the radius
	cirkle2d newPolygonSpecs = deriveEvenPolygonCenterAndRadius(lef,rig,gpt->pc->nrCorners, treeLevel);

	diffX = newPolygonSpecs.center.x - gpt->pc->center.x;
	diffY = newPolygonSpecs.center.y - gpt->pc->center.y;

	printf("    DiffX Y: %f   %f\n", diffX, diffY);

	//position self
	gpt->pc->center.x = newPolygonSpecs.center.x;
	gpt->pc->center.y = newPolygonSpecs.center.y;

	//update points?
	

	//size
	printf("old radius: %f, new radius: %f\n", gpt->pc->radius, newPolygonSpecs.radius);

	multiplyRadius(gpt->pc, newPolygonSpecs.radius / gpt->pc->radius, 1);

	//clearify offset position
	explainCoordsOffset(prev->pc->center, gpt->pc->center);
      }
    }
  }

  movePCPoints(*(gpt->pc), diffX, diffY);//seems to be the best place here, to call
  rotatePolyCell(*(gpt->pc), newAngle);
  
  for(int i=0; i< gpt->pc->nrCorners-1; i++){
    if(gpt->neighbours[i]==NULL){
      printf("neighbour dock %d is null\n", i);
    }
    else{
      printf("neighbour dock %d is not null\n", i);
      //calling itself
      renderPolyTiles(gpt->neighbours[i], treeLevel+1, gpt);
    }
  }

  
  //finally render itself

  renderPolyCell(*(gpt->pc));
  printf("-----%d\n", treeLevel);
}


void drawCube()
{
  char SIDES3 = 3, SIDES4 = 4, SIDES5 = 5, SIDES6 = 6;
  printf("draw\n");

  struct gamePolyTile gpt4_0 = createPolygon(SIDES4,0);
  struct gamePolyTile gpt = createPolygon(SIDES5,0);
  struct gamePolyTile gpt4 = createPolygon(SIDES4,0);
  struct gamePolyTile gpt4_2 = createPolygon(SIDES4,0);
  struct gamePolyTile gpt3_0 = createPolygon(SIDES3,0);
  struct gamePolyTile gpt4_3 = createPolygon(SIDES4,0);
  

  gpt4_0.name = 'a';
  gpt.name = 'b';
  gpt4.name = 'c';
  gpt4_2.name = 'd';
  gpt3_0.name = 'e';
  gpt4_3.name = 'f';

  /*3 neighbours (docks) of gpt4_0*/
  gpt4_0.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 3);
  gpt4_0.neighbours[0] = NULL;
  gpt4_0.neighbours[1] = &gpt;
  gpt4_0.neighbours[0] = NULL;

  
  /*set all 4 neighbours (docks) of gpt*/
  gpt.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 4);
  gpt.neighbours[0] = NULL;
  gpt.neighbours[1] = &gpt4;
  gpt.neighbours[2] = &gpt4_2;
  gpt.neighbours[3] = NULL;

  gpt4.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 3);
  gpt4.neighbours[0] = NULL;
  gpt4.neighbours[1] = &gpt3_0;
  gpt4.neighbours[2] = NULL;
  
  gpt4_2.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 3);
  gpt4_2.neighbours[0] = NULL;
  gpt4_2.neighbours[1] = NULL;
  gpt4_2.neighbours[2] = NULL;

  gpt3_0.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 2);
  gpt3_0.neighbours[0] = &gpt4_3;
  gpt3_0.neighbours[1] = NULL;

  gpt4_3.neighbours = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * 3);
  gpt4_3.neighbours[0] = NULL;
  gpt4_3.neighbours[1] = NULL;
  gpt4_3.neighbours[2] = NULL;

  //compare sides lengths
  //useful if scaling circle-based polygons of different corner-count so that sides match lengthwise 
  //double ratio4_5 = evenPolygonsSideRatio(SIDES4, SIDES5);

  //printf("Ratio between a side of even-polygon-%d and even-polygon-%d is %f?\n", SIDES4, SIDES5, dists3_55[4] / dists3_55[5]);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0.0, 0.0, -20.0);//camera position?!

  // Add an ambient light
  GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  // Add a positioned light
  GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  glTranslatef(0.5, 1.0, 0.0);
  glRotatef(angle, 1.0, 1.0, 1.0);

  glRotatef( angle, 1.0, 0.0, 1.0 );
  glRotatef( angle, 0.0, 1.0, 1.0 );
  glTranslatef(-0.5, -1.0, 0.0);

  renderPolyTiles(&gpt4_0,0);

  //todo: make it one function, freePolyTiles
  freePolyTile(gpt);
  freePolyTile(gpt4);
  freePolyTile(gpt4_0);
  freePolyTile(gpt4_2);
  freePolyTile(gpt3_0);
  freePolyTile(gpt4_3);
  
  glFlush();
  glutSwapBuffers();
}

int freePolyTiles(struct gamePolyTile * gpt){
  return 0;//count of free'd
}

// Function for increasing the angle variable smoothly, 
// keeps it <=360
// It can also be implemented using the modulo operator.
void update(int value)
{
  angle += 1.0f;
  if (angle > 360)
    {
      angle -= 360;
    }
  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

// Initializes 3D rendering
void initRendering()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

	// Set the color of the background
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
}


// Called when the window is resized
void handleResize(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


int main(int argc, char **argv)
{
  printf("Test with freeglut, letter B.\n");
  //printf("tsq1 with argc %d\n", argc);

  //TODO: test rotateRectangle

  //testing getAngle
  getAngleBetweenPoints(mc2d(0,0),mc2d(1,0));

  //testing evenPolygonsSideRatio
  //printf("Test av evenPolygonsSideRatio\n");
  //double ra1 = evenPolygonsSideRatio(3,4);
  //printf("%.2f\n", ra1);

  if(argc == 2){
    char * arg = argv[1];

    char fl = argv[1][0];

    int asDigit = fl-48;
    
    printf("%c %d\n", fl, asDigit);
  }
  

  if(argc==2){
    printf("Argument is %s\n", argv[1]);

    char fl = argv[1][0];

    printf("first letter of arg; %c\n", fl);

 }
  else{
    
  }
  
  z *= scale;
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Rotating a Cube");
    initRendering();
    
    //wire frame mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glutDisplayFunc(drawCube);
    glutReshapeFunc(handleResize);

    //Add a timer for the update(...) function
    //glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
