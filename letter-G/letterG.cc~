
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/*this program was made after letter-E*/

// the GLUT and OpenGL libraries have to be linked correctly
// g++ rotateCube.cc -lglut -lGL -lGLU -o rotateCube
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
//test
#include <GL/freeglut_ext.h>//to allow free()-code after closing
#endif

#include "../drinlett.h"

using namespace std;

// The coordinates for the vertices of the cube
//double x = 1;
//double y = 1;
//double z = 1;

float angle = 0.0;

float scale = 1;//for squares

//test rotate by keys
double rX=0;
double rY=-20;
double rZ=-50;

//test count draw function
int countDraw=0;


//variables global because drawXXX has no args
//yeah drawXXX might be called repeatedly(?)
tTile* t1, * t2, * t3, * t4, * t5, * t6, * t7, * t8, * t9, * t10, * t11, * t12, * t13, * t14, * t15, * t16, * t17, * t18, * t19;
  const int HEIGHT_ = 8;
  const struct rectangle rect = makeRectAround00(TILEW,TILEW);
  

  struct letter letterF;

int equipWithRects(tTile * tile, struct rectangle rawRect, int counter = 0){
  tile->r = makeRect(rawRect);
  if(tile->n1 != NULL){
    counter = equipWithRects(tile->n1, rawRect, counter);
  }
  if(tile->n2 != NULL){
    counter = equipWithRects(tile->n2, rawRect, counter);
  }
  if(tile->n3 != NULL){
    counter = equipWithRects(tile->n3, rawRect, counter);
  }
  return counter;
}
  
    

void mallocInitTilesF(){
  
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
  


  //neighbours, starting from top-left, going down
  t1->n3 = t2;//left wing, from tiles' persp.
  t2->n2 = t3;
  t3->n2 = t4;
  t4->n2 = t5;
  
  t1->n2 = t6;
  t6->n2 = t7;
  t7->n2 = t8;

  t8->n3 = t9;
  t9->n2 = t10;
  t10->n2 = t11;
  
  t8->n2 = t12;
  t12->n2 = t13;
  t13->n2 = t14;
  t14->n2 = t15;
  

  //TODO: call a function to generate a rectangle for each of the tiles, going through the neighbour-pointers
  int rectCount = equipWithRects(t1, rect);

  letterF.firstTile = t1;
  letterF.initialAngle = 180;//pointing down
  //TODO: maybe combine the three previous steps in one function

  if(letterF.initialAngle != 0){
    rotateRectangle(&(letterF.firstTile->r), letterF.initialAngle);
  }
}

int freeTileR(tTile * tile, int counter=0){
  if(tile->n1 != NULL){
    counter = freeTileR(tile->n1, counter);
  }
  if(tile->n2 != NULL){
    counter = freeTileR(tile->n2, counter);
  }
  if(tile->n3 != NULL){
    counter = freeTileR(tile->n3, counter);
  }
counter++;
  return counter;
}

void keyboard(int key, int x, int y)
{
    int mod = glutGetModifiers();

    if (mod != 0) //ALT=4  SHIFT=1  CTRL=2
    {      
          switch(mod)
          {
             case 1 :  printf("SHIFT key %d\n",mod);  break;
             case 2 :  printf("CTRL  key %d\n",mod);  break;
             case 4 :  printf("ALT   key %d\n",mod);  break;
             mod=0;
          }
    }

    if (key == GLUT_KEY_RIGHT)
        {
                rY += 10;
        }
    else if (key == GLUT_KEY_LEFT)
        {
                rY -= 10;
        }
    else if (key == GLUT_KEY_DOWN)
        {
if(mod== 1) rZ+=5;
else rX -= 10;
        }
    else if (key == GLUT_KEY_UP)
        {
if(mod== 1) rZ-=5;
else rX += 10;
        }

    // Request display update
    glutPostRedisplay();
}

void drawCube()
{
  //TODO: move out all variables for graphics/shapes and it's mem allocation
  countDraw++;

  printf("draw\n"); 

  /*
          // Set Background Color
    glClearColor(0.4, 0.4, 0.4, 1.0);
        // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
  */
    // Rotate when user changes rX and rY
glRotatef( 30, rY*2, rZ, 0.3);
    //glRotatef( rY, 0.0, 1.0, 0.0 );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(rY, rX, rZ);//camera position?!

    // Add an ambient light
    GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add a positioned light
    GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //glTranslatef(0.5, 1.0, 0.0);
    ////glRotatef(angle, 1.0, 1.0, 1.0);
    ////glRotatef( angle, 1.0, 0.0, 1.0 );
    //glRotatef( angle, 0.0, 1.0, 1.0 );

    /*test rotating by keys*/
    //glRotatef( rX, 1.0, 0.0, 0.0 );
    //glRotatef( rY, 0.0, 1.0, 0.0 );
    
    //glTranslatef(-0.5, -1.0, 0.0);

    //renderGameTile(t1, 0);
    renderLetter(letterF);
    
    glFlush();
    glutSwapBuffers();
 
    printf("-----\ncountDraw: %d\n", countDraw);
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
  printf("Test with freeglut, letter F.\n");
  printf("Try arrows and SHIFT\n");
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //test to allow free() by returning here after closing
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Letter F");
    initRendering();

    //wire frame mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //to switch back
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glutDisplayFunc(drawCube);
    glutReshapeFunc(handleResize);
    glutSpecialFunc(keyboard);//test

    //Add a timer for the update(...) function
    //glutTimerFunc(25, update, 0);

    mallocInitTilesF();
   
    glutMainLoop();

    //freeTilesD();
    int freeCount = freeTileR(t1);

    printf("-----\ncountDraw: %d, freeCount = %d\n", countDraw, freeCount);
    
    return 0;
}


