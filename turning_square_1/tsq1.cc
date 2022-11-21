
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*this program was made to find the steps involved in drawing two 'tiles' connected but with a turn involved, when calling by terminal 
  the argument l or r can be added (left or right)*/

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

enum dire DIRE;


void drawCube()
{
  printf("draw\n");

  float _angle = 10; //degrees of turn 0-90 allowed

  if(_angle < 0) _angle = 0;
  else if(_angle > 90) _angle = 90;
  //assure is under 90
  
  printf("from sin_degr(%f): %f, cos: %f\n", _angle, sin_degr(_angle), cos_degr(_angle));

  struct rectangle r0 = makeRect(mc2d(1,-1),mc2d(1,1),mc2d(-1,1),mc2d(-1,-1));//a square

  struct coord2d turnXY = getCoordTopTriangle(DIRE, _angle, r0);

  printf("Got turnXY %f, %f\n", turnXY.x, turnXY.y);
  //since a tile with it's possible top-triangle, has local coordinates, a turnXY with positive x is turn-left'ish but a neagtive x i turn-right'ish
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0.0, 0.0, -10.0);//camera position?!

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

        // Create the 3D cube

	double leftSide = -x;
	double rightSide = x;
	double newX, newY;

	if(turnXY.x < 0){
	  //turn right
	  newX = rightSide+turnXY.x;
	}
	else{
	  //left
	  newX = leftSide+turnXY.x;
	}

	newY = y+turnXY.y;

	//double diffX = newX -

	
    // sq01
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.3, 0.2);
    glVertex3f(r0.p1.x, r0.p1.y, z);//bottom right
    glVertex3f(r0.p2.x, r0.p2.y, z);//top right
    glVertex3f(newX, newY, z);
    glVertex3f(r0.p3.x, r0.p3.y, z);
    glVertex3f(r0.p4.x, r0.p4.y, z);
    glEnd();

    //sq02
    struct rectangle r1;
    if(turnXY.x < 0){//right
      r1 = getRectangleFromBaseLineAndHeightWidth(coord2dFromXY(newX, newY), coord2dFromXY(x,y), 2, 2);
    }
    else{//left
      r1 = getRectangleFromBaseLineAndHeightWidth(coord2dFromXY(-x,y), coord2dFromXY(newX, newY), 2, 2);
    }

    printStructRectangle(r1);

    //if angle != 0 make new positions
    //third is a copy of 2:nd
    /*double xpoints[] = {x,x,x,-x,-x};
    double ypoints[] = {y,TILEW*y,TILEW*y,TILEW*y,y};
    if(_angle != 0){
      if(turnXY.x < 0){//right
	//first point stay
	xpoints[4] = newX;
	ypoints[4] = newY;
      }
      }*/
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.3, 0.5);
    
    glVertex3f(r1.p1.x, r1.p1.y, z);
    glVertex3f(r1.p2.x, r1.p2.y, z);
    glVertex3f(r1.p3.x, r1.p3.y, z);
    glVertex3f(r1.p4.x, r1.p4.y, z);
    glEnd();

    
    glFlush();
    glutSwapBuffers();
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
  printf("Test with freeglut, connected turning squares. You can add command line arg: r or l\n\n");
  printf("tsq1 with argc %d\n", argc);

  if(argc==2){
    printf("Argument is %s\n", argv[1]);

    char fl = argv[1][0];

    printf("first letter of arg; %c\n", fl);

    if(fl=='r'){
      DIRE = r;
    }
    else if(fl=='l'){
      DIRE = l;
    }
    else{
      printf("Argument should be r or l (right/left)\n");
    }
  }
  else{
    DIRE = r; //default right
  }
  //TODO: arg for angle

  
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

        // Add a timer for the update(...) function
    //glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
