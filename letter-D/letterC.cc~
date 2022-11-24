
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*this program was made to find the steps involved in drawing two 'tiles' connected but with a turn involved*/
/*made after tsq3.cc*/

// the GLUT and OpenGL libraries have to be linked correctly
// g++ rotateCube.cc -lglut -lGL -lGLU -o rotateCube
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../drinlett.h"

using namespace std;

// The coordinates for the vertices of the cube
double x = 1;
double y = 1;
double z = 1;

float angle = 0.0;

float scale = 1;//for squares

void drawCube()
{
  printf("draw\n");

  tTile* t1;
  tTile* t2;
  tTile* t3;
  tTile* t4;
  tTile* t5;
  t1 = (tTile*)malloc(sizeof(tTile));
  t2 = (tTile*)malloc(sizeof(tTile));
  t3 = (tTile*)malloc(sizeof(tTile));
  t4 = (tTile*)malloc(sizeof(tTile));
  t5 = (tTile*)malloc(sizeof(tTile));
  
  const struct rectangle rect = makeRect(mc2d(1,-1),mc2d(1,0.3),mc2d(-1,0.3),mc2d(-1,-1));

  t1->r = t2->r = t3->r = t4->r = t5->r = rect;
  t1->angle = t2->angle = t3->angle = t4->angle = 22;
  t1->d = t2->d = t3->d = t4->d = r;


  t1->n2 = t2;
  t2->n2 = t3;
  t3->n2 = t4;
  t4->n2 = t5;
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -30.0);//camera position?!

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

    renderGameTile(t1, 0);
    
    glFlush();
    glutSwapBuffers();
    free(t1);
    free(t2);
    free(t3);
    free(t4);
    free(t5);
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
  printf("Test with freeglut, connected turning squares 3.\n");
  //printf("tsq1 with argc %d\n", argc);

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

  printf("getAngleBetweenPoints test\n");
  printf("0/0 to 0/1 should be 0\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(0,1));
  printf("getAngleBetweenPoints test\n");
  printf("0/0 to 1/0 should be 90\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(1,0));
  printf("getAngleBetweenPoints test\n");
  printf("0/0 to 0/-1 should be 180\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(0,-1));
  printf("getAngleBetweenPoints test\n");
  printf("0/0 to -1/0 should be 270\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(-1,0));
  printf("getAngleBetweenPoints test\n");
  printf("0/0 to 1/1 should be 45\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(1,1));
  printf("getAngleBetweenPoints test\n");
  printf("0/0 to -1/-1 should be 225\n");
  getAngleBetweenPoints(coord2dFromXY(0,0), coord2dFromXY(-1,-1));
  printf("getAngleBetweenPoints test\n");
  printf("1/1 to 0/0 should be 225\n");
  getAngleBetweenPoints(coord2dFromXY(1,1), coord2dFromXY(0,0));
  
  x *= scale;
  y *= scale;
  z *= scale;
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Rotating a Cube");
    initRendering();

    glutDisplayFunc(drawCube);
    glutReshapeFunc(handleResize);

    //Add a timer for the update(...) function
    //glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
