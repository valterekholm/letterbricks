
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "drinlett.h"


//testing non-graphic functions

void test_getTopPoint_1(){

//getTopPoint(struct coord2d left, struct coord2d right, double directionAngle){

    struct coord2d c2dL = coord2dFromXY(-1, 0);
    struct coord2d c2dR = coord2dFromXY(1, 0);
    double directionA = 10;

    struct coord2d topP = getTopPoint(c2dL, c2dR, directionA);

    printStructCoord2d(topP, 1);
}

void test_getTopPoint_2(){

//getTopPoint(struct coord2d left, struct coord2d right, double directionAngle){

    struct coord2d c2dL = coord2dFromXY(-1, 0);
    struct coord2d c2dR = coord2dFromXY(1, 0);
    double directionA = -10;

    struct coord2d topP = getTopPoint(c2dL, c2dR, directionA);

    printStructCoord2d(topP, 1);
}

void test_getTopPoint_3(){

//getTopPoint(struct coord2d left, struct coord2d right, double directionAngle){

    struct coord2d c2dL = coord2dFromXY(-.3, 0);
    struct coord2d c2dR = coord2dFromXY(.7, 0);
    double directionA = 45;

    struct coord2d topP = getTopPoint(c2dL, c2dR, directionA);

    printStructCoord2d(topP, 1);
}

void test_rotatePoint_1(){

    struct coord2d c2d1 = coord2dFromXY(-1, 0);
    struct coord2d c2d2 = coord2dFromXY(0, 0);
    double angle = 90;

    struct coord2d newP = rotatePoint(c2d1, c2d2, angle);

    printStructCoord2d(newP, 1);
}

//to derive center from a "even polygon"
//known are two coordinates, and how many sides the polygon has
void test_deriveCenter_1(){
//TODO: use radius and angle
printf("test_deriveCenter_1\n");
struct coord2d center = coord2dFromXY(0,0);
int nrSides = 4;
struct gamePolyTile testp = createPolygon(nrSides);

//want the base (root) side
struct coord2d l1 = *(testp.pc->points[3]);
struct coord2d r1 = *(testp.pc->points[0]);

printf("root: ");
printStructCoord2d(l1);
printf("    ");
printStructCoord2d(r1, 1);

//TODO: derive the center from l1 and r1

//1. know the angle of l1 and r1
int step = 360 / nrSides;//in degrees
double angleL1 = (180 + (double)step/2);
double angleR1 = (180 - (double)step/2);
printf("angle L1 R1: %.1f  %.1f\n", angleL1, angleR1);

//2. know the ratio between one side and the radius 
double ratio = getRatioPolygonSideAndRadius(nrSides);

printf("ratio: %.2f\n", ratio);

//get inverted ratio
double ratioI = 1/ratio;

//get distance between l1 r1
double distance = getDistBetweenCoord2ds(l1, r1);
printf("distance: %.2f\n", distance);

//calculate new ratio ... distance to center
double newRatio = distance * ratioI;
printf("newRatio: %.2f\n", newRatio);

//invert the angle, direction to center
double newAngleL1 = (angleL1+180);//use modulus 360?
double newAngleR1 = (angleL1+180);

//continuing with (l)eft

//use sin and cos to get center
double newX = sin_degr(newAngleL1);
double newY = cos_degr(newAngleL1);

//add the known position
newX += l1.x;
newY += l1.y;

printf("newX: %.1f, newY: %.1f\n", newX, newY);

freePolyTile(testp);
}

//now added rotation
void test_deriveCenter_2(){
//TODO: use radius
printf("test_deriveCenter_2\n");
struct coord2d center = coord2dFromXY(0,0);
int nrSides = 4;
struct gamePolyTile testp = createPolygon(nrSides, 30);

//want the base (root) side
struct coord2d l1 = *(testp.pc->points[3]);
struct coord2d r1 = *(testp.pc->points[0]);

printf("root: ");
printStructCoord2d(l1);
printf("    ");
printStructCoord2d(r1, 1);

//TODO: derive the center from l1 and r1

//1. know the angle of l1 and r1
//assuming the polygon is not rotated
int step = 360 / nrSides;//in degrees
double angleL1 = (180 + (double)step/2);
double angleR1 = (180 - (double)step/2);

//but if polygon is rotated!
if(testp.angle != 0){
    angleL1 += testp.angle;
    angleR1 += testp.angle;
}

printf("angle L1 R1: %.1f  %.1f\n", angleL1, angleR1);

//2. know the ratio between one side and the radius 
double ratio = getRatioPolygonSideAndRadius(nrSides);

printf("ratio: %.2f\n", ratio);

//get inverted ratio
double ratioI = 1/ratio;

//get distance between l1 r1
double distance = getDistBetweenCoord2ds(l1, r1);
printf("distance: %.2f\n", distance);

//calculate new ratio ... distance to center
double newRadius = distance * ratioI;
printf("newRadius: %.2f\n", newRadius);

//invert the angle, direction to center
double newAngleL1 = (angleL1+180);
double newAngleR1 = (angleL1+180);

//continuing with (l)eft

//use sin and cos to get center
double newX = sin_degr(newAngleL1);
double newY = cos_degr(newAngleL1);

//add the known position
newX += l1.x;
newY += l1.y;

printf("newX: %.1f, newY: %.1f\n", newX, newY);

freePolyTile(testp);
}

//now removing rotation as a known value
//changing the gpt position also
void test_deriveCenter_3(){
//TODO: use radius
printf("test_deriveCenter_3\n");
struct coord2d center = coord2dFromXY(0,0);
int nrSides = 4;
struct gamePolyTile testp = createPolygon(nrSides, 30);

translateGPT(&testp, 1, 1);

//want the base (root) side
//getting appropriate coordinates
struct coord2d l1 = *(testp.pc->points[3]);
struct coord2d r1 = *(testp.pc->points[0]);

printf("root: ");
printStructCoord2d(l1);
printf("    ");
printStructCoord2d(r1, 1);

//TODO: derive the center from l1 and r1

//1. know the angle of l1 and r1
//assuming the polygon is not rotated
int step = 360 / nrSides;//in degrees
double angleL1 = (180 + (double)step/2);
double angleR1 = (180 - (double)step/2);

//diff between angles
double adiff = angleL1 - angleR1;//i.e. 90 in a square

//get angle between points
float abp = getAngleBetweenPoints(l1, r1);
printf("angle between points: %.1f\n", abp);

//angle towards center should then be 90 less from plane but from a point?
//use adiff
//add half circle
double angleL2 = abp-90+(adiff/2)+180;
printf("angleL2 %.1f\n", angleL2);

double angleR2 = abp-90-(adiff/2)+180;
printf("angleR2 %.1f\n", angleR2);

//2. know the ratio between one side and the radius 
double ratio = getRatioPolygonSideAndRadius(nrSides);

printf("ratio: %.2f\n", ratio);

//get inverted ratio
double ratioI = 1/ratio;

//get distance between l1 r1
double distance = getDistBetweenCoord2ds(l1, r1);
printf("distance: %.2f\n", distance);

//calculate new radius ... distance to center
double newRadius = distance * ratioI;
printf("newRadius: %.2f\n", newRadius);

//invert the angle, direction to center
double newAngleL1 = (angleL2+180);
double newAngleR1 = (angleL2+180);

//continuing with (l)eft

//use sin and cos to get center
double newX = sin_degr(newAngleL1);
double newY = cos_degr(newAngleL1);

//add the known position
newX += l1.x;
newY += l1.y;

printf("newX: %.1f, newY: %.1f\n", newX, newY);

freePolyTile(testp);
}

//now using a separate(d) function
void test_deriveCenter_4(){

printf("test_deriveCenter_4\n");
struct coord2d center = coord2dFromXY(0,0);
int nrSides = 4;
struct gamePolyTile testp = createPolygon(nrSides, 30);

//change position
translateGPT(&testp, 1, 1);

//want the base (root) side
//getting appropriate coordinates
struct coord2d l1 = *(testp.pc->points[3]);
struct coord2d r1 = *(testp.pc->points[0]);

printf("root: ");
printStructCoord2d(l1);
printf("    ");
printStructCoord2d(r1, 1);

struct coord2d newCenter = deriveEvenPolygonCenter(l1,r1,nrSides);


freePolyTile(testp);

printStructCoord2d(newCenter, 1);

}

//new function, getting new center and radius
void test_deriveCenter_5(){

printf("test_deriveCenter_5\n");
struct coord2d center = coord2dFromXY(0,0);
int nrSides = 4;
struct gamePolyTile testp = createPolygon(nrSides, 30);

//change position
translateGPT(&testp, 1, 1);

//want the base (root) side
//getting appropriate coordinates
struct coord2d l1 = *(testp.pc->points[3]);
struct coord2d r1 = *(testp.pc->points[0]);

printf("root: ");
printStructCoord2d(l1);
printf("    ");
printStructCoord2d(r1, 1);

struct cirkle2d newCirkle = deriveEvenPolygonCenterAndRadius(l1,r1,nrSides);


freePolyTile(testp);

printf("newCirkle radius: %.1f, position: ", newCirkle.radius);
printStructCoord2d(newCirkle.center, 1);


}


int main(){
    printf("tests\n");
    test_getTopPoint_1();
    test_getTopPoint_2();
    test_getTopPoint_3();
    test_rotatePoint_1();
    test_deriveCenter_1();
    test_deriveCenter_2();
    test_deriveCenter_3();
    test_deriveCenter_4();
    test_deriveCenter_5();
}
