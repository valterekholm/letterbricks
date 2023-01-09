
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*this program was made after letter_B*/
/*made from tsq4.cc*/

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
  tTile* t5, * t6, * t7, * t8, * t9, * t10, * t11, * t12, * t13, * t14, * t15, * t16, * t17, * t18, * t19;
  t1 = (tTile*)malloc(sizeof(tTile));
  t2 = (tTile*)malloc(sizeof(tTile));
  t3 = (tTile*)malloc(sizeof(tTile));
  t4 = (tTile*)malloc(sizeof(tTile));
  t5 = (tTile*)malloc(sizeof(tTile));
  t6 = (tTile*)malloc(sizeof(tTile));
  t7 = (tTile*)malloc(sizeof(tTile));
  t8 = (tTile*)malloc(sizeof(tTile));
  t9 = (tTile*)malloc(sizeof(tTile));
  t10 = (tTile*)malloc(sizeof(tTile));
  t11 = (tTile*)malloc(sizeof(tTile));
  t12 = (tTile*)malloc(sizeof(tTile));
  t13 = (tTile*)malloc(sizeof(tTile));
  t14 = (tTile*)malloc(sizeof(tTile));
  t15 = (tTile*)malloc(sizeof(tTile));
  t16 = (tTile*)malloc(sizeof(tTile));
  t17 = (tTile*)malloc(sizeof(tTile));
  t18 = (tTile*)malloc(sizeof(tTile));
  t19 = (tTile*)malloc(sizeof(tTile));
  
  const struct rectangle rect = makeRect(mc2d(1,-1),mc2d(1,1),mc2d(-1,1),mc2d(-1,-1));

  t1->r = t2->r = t3->r = t4->r = t5->r = t6->r = t7->r = t8->r = t9->r = t10->r = t11->r = t12->r = t13->r = t14->r = t15->r = t16->r = t17->r = t18->r = t19->r = rect;
  t1->angle = t2->angle = t3->angle = t4->angle = t5->angle = t6->angle = t7->angle = t8->angle = t9->angle = t10->angle = 18.15;
  t11->angle = 0;
  t1->d = t2->d = t3->d = t4->d = t5->d = t6->d = t7->d = t8->d = t9->d = t10->d = t11->d = r;


  //neighbours
  t1->n2 = t2;
  t2->n2 = t3;
  t3->n2 = t4;
  t4->n2 = t5;
  t5->n2 = t6;
  t6->n2 = t7;
  t7->n2 = t8;
  t8->n2 = t9;
  t9->n2 = t10;
  t10->n2 = t11;
  t11->n2 = t12;
  t12->n1 = t13;//90 degree turn
  t13->n2 = t14;
  t14->n2 = t15;
  t15->n2 = t16;
  t16->n2 = t17;
  t17->n2 = t18;
  t18->n2 = t19;

  struct letter letterD;
  letterD.firstTile = t1;
  letterD.initialAngle = 88;
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 7.0, -30.0);//camera position?!

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

    //renderGameTile(t1, 0);
    renderLetter(letterD);
    
    glFlush();
    glutSwapBuffers();
    free(t1);
    free(t2);
    free(t3);
    free(t4);
    free(t5);
    free(t6);
    free(t7);
    free(t8);
    free(t9);
    free(t10);
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
  printf("Test with freeglut, letter D.\n");
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

  x *= scale;
  y *= scale;
  z *= scale;
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Letter D");
    initRendering();

    //wire frame mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //to switch back
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glutDisplayFunc(drawCube);
    glutReshapeFunc(handleResize);

    //Add a timer for the update(...) function
    //glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
