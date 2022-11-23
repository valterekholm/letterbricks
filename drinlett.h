#define PI 3.14159265
#define TILEW 2 //width

/*for polygons based on circle with radius 1, one side length*/
#define POLY3SIDEL 1.732051
#define POLY4SIDEL 1.414214
#define POLY5SIDEL 1.175570

#include <math.h>

//these are distance for an even polygons' side, ranging from 0 to 55 sides, assuming a radius of 1
//0, 1 or 2 sides are not possible
//by 6 sides each side is the same as the radius
//is there a simple rule for this?
const double dists3_55[] = {
0,
0,
0,
1.73205080756888,
1.4142135623731,
1.17557050458495,
1,
0.867767478235116,
0.765366864730179,
0.684040286651337,
0.618033988749895,
0.563465113682859,
0.517638090205042,
0.478631328575115,
0.445041867912629,
0.415823381635519,
0.390180644032257,
0.367499035633141,
0.347296355333861,
0.329189180561468,
0.312868930080462,
0.298084532352349,
0.28462967654657,
0.272333298192493,
0.261052384440103,
0.250666467128609,
0.241073360510646,
0.23218582825046,
0.223928952206616,
0.216238036847884,
0.209056926535307,
0.202336643974864,
0.196034280659121,
0.190112086608365,
0.184536718926604,
0.179278617806867,
0.174311485495316,
0.169611848951018,
0.165158690944665,
0.160933137433452,
0.15691819145569,
0.153098505672991,
0.149460187172849,
0.145990629321815,
0.142678366398465,
0.139512947488251,
0.136484826729342,
0.133585267490243,
0.130806258460286,
0.128140439961426,
0.125581039058627,
0.123121812267886,
0.120756994844572,
0.118481255787429,
0.116289657820952,
0.114177621725536,
};

double radianDeg = 180 / PI;

struct coord2d{
  double x, y;
};

struct point2d{
  int x, y;
};

int printStructCoord2d(struct coord2d, int);
double getDistBetweenCoord2ds(struct coord2d, struct coord2d);
double getAngleBetweenPoints(struct coord2d, struct coord2d);
struct coord2d coord2dFromXY(double, double);
void adjustPoints(struct polyCell *, double);

struct cirkle2d{
    struct coord2d center;
    double radius;
};

struct coord2d mc2d(double x, double y){
    struct coord2d s;
    s.x = x;
    s.y = y;
    return s;
}

void translateC2d(struct coord2d * c2d, double x, double y){
    c2d->x += x;    
    c2d->y += y;
}

void printCirkle2d(struct cirkle2d c2){
    printf("printCirkle2d\n");
    printStructCoord2d(c2.center, 1);
    printf("radius: %.2f\n", c2.radius);
}

//this is the base shape to build letters from
//an instance should be reused
struct rectangle{
  struct coord2d p1, p2, p3, p4;
};

//version 1 of a triangle, with all sides same
struct triangle{
    double side; //length (of radius - the cirkle tangenting the coorners)
    struct coord2d center;
    float rotation; //120 degrees real use, currently not used - assuming an isometric grid
};

struct triangle makeTri(double side, struct coord2d center = mc2d(0,0)){
    struct triangle tr;
    tr.side = side;
    tr.center = center;
    tr.rotation = 0;
    return tr;
}

void newLineAndIndent(int indent){
    printf("\n");
    for(int i=0; i<indent; i++) printf(" ");
}

void printStructRectangle(struct rectangle r){
  printf("[%f,%f][%f,%f][%f,%f][%f,%f]\n", r.p1.x, r.p1.y, r.p2.x, r.p2.y, r.p3.x, r.p3.y, r.p4.x, r.p4.y);
}

void printStructTriangle(struct triangle t){
    printf("-----   side: %f, center: [%.2f/%.2f], rotation: %f   \\-----\n", t.side, t.center.x, t.center.y, t.rotation);
}




struct rectangle makeRect(struct coord2d p1,struct coord2d p2,struct coord2d p3,struct coord2d p4){
    printf("makeRect\n");
    struct rectangle r;
    r.p1 = p1;
    r.p2 = p2;
    r.p3 = p3;
    r.p4 = p4;
    printStructRectangle(r);
    return r;
}

struct rectangle makeRect(struct rectangle r){
    struct rectangle _r = r;
    return _r;
}

struct rectangle makeRect(struct rectangle * r){
    struct rectangle _r;
    _r.p1 = r->p1;
    _r.p2 = r->p2;
    _r.p3 = r->p3;
    _r.p4 = r->p4;
    const struct rectangle __r = _r;
    return __r;
}

enum dire{ r, l };//direction

typedef enum { male, female } gender; // for triangles in an isometric grid, they're standing on a base (male) or on a peak (female)

typedef enum cirkleQuadrant{ topRight, bottomRight, bottomLeft, topLeft } cirkleQuadrant;

enum aboBel{ ABOVE, BELOW };

void printGender(gender g){
    if(g == male) printf("male");
    else printf("female");
}

int printCirkleQuadrant(cirkleQuadrant cq){
  int rV = 1;
  if(cq == topRight) printf("top-right %d", rV);
  else{
    rV++;
    if(cq == bottomRight) printf("bottom-right %d", rV);
    else{
      rV++;
      if(cq == bottomLeft) printf("bottom-left %d", rV);
      else{
        rV++;
        if(cq == topLeft) printf("top-left %d", rV);
      }
    }
  }
  return rV;
}

gender getOpposite(gender g){
    printf("getOpposite for gender ");
    printGender(g);
    if(g==male){ printf("return fm"); return female; }
    else{ printf("return m"); return male; }
}

//x value
float sin_degr(float angle){
  float val = PI / 180;
  float ret = sin(angle * val);
  return ret;
}

//y value
float cos_degr(float angle){
  float val = PI / 180;
  float ret = cos(angle * val);
  return ret;
}

struct coord2d sin_cos_degr(double angle){
  struct coord2d coord;
  coord.x = sin_degr(angle);
  coord.y = cos_degr(angle);
  return coord;
}

struct coord2d rotatePoint(struct coord2d point, struct coord2d center, double degrees){
  printf("rotatePoint from %.2f %.2f", point.x, point.y);
  printf(" center: %.1f %.1f", center.x, center.y);
  double dist = getDistBetweenCoord2ds(point, center);
  double inboundAngle = getAngleBetweenPoints(center, point);
  double newAngle = degrees+inboundAngle;
  double newX = sin_degr(newAngle) * dist+center.x;
  double newY = cos_degr(newAngle) * dist+center.y;

  struct coord2d newC = coord2dFromXY(newX, newY);

  printf(" to %.2f %.2f\n", newC.x, newC.y);
  return newC;
}

int coordsAreEqual(struct coord2d point1, struct coord2d point2){

  if(point1.x == point2.x && point1.y == point2.y){
    return 1;
  }
  else{
    return 0;
  }
}

//explain the location of point2 compared to point1, using "4 quadrants" style
int explainCoordsOffset(struct coord2d point1, struct coord2d point2){

  if(coordsAreEqual(point1, point2)){
    printf("positionen är densamma för p1 p2");
    return 0;
  }


  if(point2.y > point1.y){
    printf("p2 är ovanför ");
  }
  else if(point2.y == point1.y){
    printf("p2 är bredvid ");
  }
  else{
    printf("p2 är under ");
  }

  if(point2.x > point1.x){
    printf("till höger om ");
  }
  else if(point2.x == point1.x){
    printf("(rakt) ");
  }
  else{
    printf("till vänster om ");
  }
  printf("p1\n");
  return 1;
}

//rotating the supplied struct rectangle through pointers
void rotateRectangle(struct rectangle * rect, double degrees){

    //find middle point
    double minX, maxX, minY, maxY;
    minX = minY = 1000000;
    maxX = maxY = -1000000;

    if(rect->p1.x < minX) minX = rect->p1.x;
    if(rect->p2.x < minX) minX = rect->p2.x;
    if(rect->p3.x < minX) minX = rect->p3.x;
    if(rect->p4.x < minX) minX = rect->p4.x;
    if(rect->p1.y < minY) minY = rect->p1.y;
    if(rect->p2.y < minY) minY = rect->p2.y;
    if(rect->p3.y < minY) minY = rect->p3.y;
    if(rect->p4.y < minY) minY = rect->p4.y;

    if(rect->p1.x > maxX) maxX = rect->p1.x;
    if(rect->p2.x > maxX) maxX = rect->p2.x;
    if(rect->p3.x > maxX) maxX = rect->p3.x;
    if(rect->p4.x > maxX) maxX = rect->p4.x;
    if(rect->p1.y > maxY) maxY = rect->p1.y;
    if(rect->p2.y > maxY) maxY = rect->p2.y;
    if(rect->p3.y > maxY) maxY = rect->p3.y;
    if(rect->p4.y > maxY) maxY = rect->p4.y;

    double middleX = (maxX + minX) / 2;
    double middleY = (maxY + minY) / 2;
    struct coord2d middle = coord2dFromXY(middleX, middleY);

    rect->p1 = rotatePoint(rect->p1, middle, degrees);
    rect->p2 = rotatePoint(rect->p2, middle, degrees);
    rect->p3 = rotatePoint(rect->p3, middle, degrees);
    rect->p4 = rotatePoint(rect->p4, middle, degrees);
}

int printStructCoord2d(struct coord2d s, int newLine = 0){
  printf("[%f,%f]", s.x, s.y);
  if(newLine) printf("\n");
  return 0;
}
int psc2d(struct coord2d s, int newLine = 0){
  return printStructCoord2d(s);
}
struct coord2d coord2dFromXY(double x, double y){
  struct coord2d s;
  s.x = x;
  s.y = y;
  return s;
}

double getDistBetweenCoord2ds(struct coord2d c1, struct coord2d c2){

    float distX = abs(c1.x - c2.x);
    float distY = abs(c1.y - c2.y);

    float dist = sqrt(distX*distX + distY*distY);
    return dist;
}

//polygons based on cirkle
struct polyCell{
  char nrCorners; //also nr of points
  struct coord2d ** points; // array, drawn counter clockwise starting from a bottom right point
  struct coord2d center; // a position for reference i.e. if making a 5-edged polygon around a center, like a cirkle
  //double side; // if making like a cirkle, using sin and cos //what is this?
  double radius; //default should be 1
};

struct gamePolyTile{
  char name;
  struct polyCell * pc;
  double angle; //initial angle added to polyCell shape trough rotation
  struct gamePolyTile ** neighbours; // should be 0 - correspond to the polyCells' points, but have one less, exluding the side from last to first point (the starting)
};

//angle is analog to the tile's direction (2D), an 90 degrees offset from the base (the line between [left] and [right])
//left and right are two points, making up the tile's "base"
//rectangle is defined with points counter clockwise starting at [right], 1,2,3,4, ending at [left]
//width is equal to distance between left and right
struct rectangle getRectangleFromBaseLineAndHeightWidth(struct coord2d left, struct coord2d right, double width, double height){
  printf("getRectangleFromBaseLineAndHeightWidth\n");
  printf("%c left\n", psc2d(left));
  printf("%c right\n", psc2d(right));
  printf("width: %f, height: %f\n", width, height);

  //calc angle from having left and right as base
  double distX = right.x - left.x;
  double distY = (right.y - left.y) * -1;
  double at = atan2(distY, distX) * radianDeg;
  printf("calculated atan from x/y %f %f to %f\n", distX, distY, at);
  double angle = at;
  
  float x = sin_degr(angle);//swap
  float y = cos_degr(angle);

  x *= height;
  y *= height;

  //x and y is offset from a point on baseline to corresponding point on the top

  float p2x = right.x + x;
  float p2y = right.y + y;

  float p3x = left.x + x;
  float p3y = left.y + y;

  struct rectangle r;
  r.p1 = right;
  r.p2 = coord2dFromXY(p2x, p2y);
  r.p3 = coord2dFromXY(p3x, p3y);
  r.p4 = left;

  return r;
}

double smallestFloat(double n1, double n2){
    if(n1 < n2) return n1;
    else return n2;
}

double biggestFloat(double n1, double n2){
    if(n1 > n2) return n1;
    else return n2;
}

double getStructRectHeight(struct rectangle r){
    double smallestY = smallestFloat(smallestFloat(r.p1.y, r.p2.y), smallestFloat(r.p3.y, r.p4.y));
    double biggestY = biggestFloat(biggestFloat(r.p1.y, r.p2.y), biggestFloat(r.p3.y, r.p4.y));

    return abs(biggestY - smallestY);
}



//square
//a struct for an instance of a "tile", having a shape, and up to three connected [gameTile]'s (neighborugs), generally defined counter clockwise
//in this version, the shape is a [rectangle] plus the "top triangle" (angle, direction)
//the rectangle's coordinates are defined in a separate "room" centered around (x/y) 0,0
typedef struct gameTile{
  struct rectangle r; //reference to re-use rectangle(s)
  double angle;
  enum dire d;//this in case of wanting a neighbour tile to turn from this, should be r(ight) or l(eft)

  struct gameTile* n1;
  struct gameTile* n2;
  struct gameTile* n3;
  
} tTile;

union triTileSwapConnection{//not used
  struct gameTriTile* up;
  struct gameTriTile* down;
}; //in an isometric grid with a horizontal line, the cells/triangles can either have a neighbor up OR down.  

void printUnionTriTileSwapConnection(union triTileSwapConnection tsc){
    printf("~~~   ");
    if(tsc.up == NULL) printf("UP is null"); else printf("up is set");
    if(tsc.down == NULL) printf("DOWN is null"); else printf("down is set");
    printf("   ~~~\n");
}

typedef struct gameTriTile{
  struct triangle t;
  struct gameTriTile* nLeft;
  struct gameTriTile* nRight; //since the cells/triangles are part of an isometric grid, they can't be rotated and right would stay right / left stay left
  struct gameTriTile* yNeighbour; //either up or down
  gender g; //"male" pike up, "female" pike down, a logical constraint for yNeighbour, male can have yNeighbour below while female can have above
} tTriTile;

//attempt to fix errors with random neighbours
tTriTile * makeEmptyTriTile(){
    tTriTile * tt = (tTriTile*)malloc(sizeof(tTriTile));
    tt->nRight = NULL;
    tt->nLeft = NULL;
    tt->yNeighbour = NULL;
    return tt;
}

void printGameTriTile(tTriTile* tt){
    printf("printGameTriTile\t");
    printStructTriangle(tt->t);
    printGender(tt->g);
    
    if(tt->nLeft == NULL) printf("0<-"); else printf("this triTile has a left neighbour");
    if(tt->nRight == NULL) printf("->0"); else printf("this triTile has a right neighbour");
    if(tt->yNeighbour == NULL) printf("0=0"); else printf("this triTile has an y-neighbour");
    printf("End of printGameTriTile\n");
    
}


//return angle in degrees
double getAngleBetweenPoints(struct coord2d p1, struct coord2d p2){
  printf("getAngleBetweenPoints %.2f/%.2f and %.2f/%.2f\n", p1.x, p1.y, p2.x, p2.y);
  double distX = p2.x - p1.x;
  double distY = p2.y - p1.y; //comment : this is changed as of 20220129, could affect several programs
  double at = atan2(distX, distY) * radianDeg;//gives seemingly angle between p2 and p1, so I swap

  printf("Will return %f\n", at);
  return at;
}


struct coord2d getTopPoint(struct coord2d left, struct coord2d right, double directionOffset){
  //struct coord2d rotatePoint(struct coord2d point, struct coord2d center, double degrees);

  int factor=1;
  if(directionOffset>0 && directionOffset<=90) factor = 1; // direction right
  else if(directionOffset<0 && directionOffset>=-90) factor = -1; // direction left
  else{
    exit(1);
  }

  struct coord2d topPoint;

  if(factor == 1){
    topPoint = rotatePoint(left, right, directionOffset);
  }
  else{
    topPoint = rotatePoint(right, left, directionOffset);
  }

  return topPoint;

}

//replaced by getTopPoint
struct coord2d getCoordTopTriangle(tTile tile){
  printf("getCoordTopTriangle angle %f\n", tile.angle);
  if(tile.d == l){
    printf("l\n");
  }
  else printf("r\n");

  //since sin (x-related) and cos (y...) would have origin in circle's top I must change the orientation since I want origin to be either right or left end of circle

  double distX = tile.r.p1.x - tile.r.p4.x;
  double distY = (tile.r.p1.y - tile.r.p4.y) * -1;
  double at = atan2(distY, distX) * radianDeg;
  printf("calculated atan from x/y %f %f to %f\n", distX, distY, at);
  double angle = at;

  int factor = tile.d==l ? -1 : 1; // direction
  
  float x = cos_degr((tile.angle) * factor);
  float y = sin_degr((tile.angle) * factor);

  double tileWidth = getDistBetweenCoord2ds(tile.r.p1, tile.r.p4);

  x *= tileWidth;
  y *= tileWidth;

  //the point should be relative to a tile top corner
    
  if(tile.d == r){
    //
    x *= -1;
  }
  else{
    //
  }

  //x += tile.r.p3.x;
  //y += tile.r.p3.y;

  printf("x/y = %f/%f\n", x, y);

  struct coord2d ret;
  ret.x = x;
  ret.y = y;
  return ret;
  
}

struct coord2d getCoordTopTriangle(tTile * tile){
  printf("getCoordTopTriangle angle %f\n", tile->angle);
  if(tile->d == l){
    printf("l\n");
  }
  else printf("r\n");

  //since sin (x-related) and cos (y...) would have origin in circle's top I must change the orientation since I want origin to be either right or left end of circle

  double distX = tile->r.p1.x - tile->r.p4.x;
  double distY = (tile->r.p1.y - tile->r.p4.y) * -1;
  double at = atan2(distY, distX) * radianDeg;
  printf("calculated atan from x/y %f %f to %f\n", distX, distY, at);
  double angle = at;

  int factor = tile->d==l ? -1 : 1; // direction
  
  float x = cos_degr((tile->angle) * factor);
  float y = sin_degr((tile->angle) * factor);

  double tileWidth = getDistBetweenCoord2ds(tile->r.p1, tile->r.p4);

  x *= tileWidth;
  y *= tileWidth;

  //the point should be relative to a tile top corner
    
  if(tile->d == r){
    //
    x *= -1;
  }
  else{
    //
  }

  //x += tile->r.p3.x;
  //y += tile->r.p3.y;

  printf("x/y = %f/%f\n", x, y);

  struct coord2d ret;
  ret.x = x;
  ret.y = y;
  return ret;
  
}

//square
void printStructGameTile(tTile * t){
  printf("\n----tTile----\n");
  printStructRectangle(t->r);
  printf("Angle: %f\n", t->angle);
  printf("Direction: ");
  if(t->d == r) printf("right");
  else printf("left");
  printf("\n");
  if(t->n1 == NULL) printf("n1 is null, "); else printf("n1 is set, ");
  if(t->n2 == NULL) printf("n2 is null, "); else printf("n2 is set, ");
  if(t->n3 == NULL) printf("n3 is null, "); else printf("n3 is set, ");
  printf("\n-------------\n");
  
}

//square
void explainGameTile(tTile * t, int treeLevel, double z = 1){
  printf("\n-----------\n");
  for(int i=0;i<treeLevel;i++) printf(" ");
  
  printf("(%d)Tile with angle %f, ", treeLevel++, t->angle);
  if(t->n1 == NULL) printf("n1 is null, ");
  else explainGameTile(t->n1, treeLevel);
  if(t->n2 == NULL) printf("n2 is null, ");
  else explainGameTile(t->n2, treeLevel);
  if(t->n3 == NULL) printf("n3 is null, ");
  else explainGameTile(t->n3, treeLevel);

  printf("\n");
  /*
  glBegin(GL_POLYGON);
  glColor3f(0.5, 0.3, 0.2);
  glVertex3f(t->r.p1.x, t->r.p1.y, z);
  glVertex3f(t->r.p2.x, t->r.p2.y, z);
  glVertex3f(t->r.p3.x, t->r.p3.y, z);
  glVertex3f(t->r.p4.x, t->r.p4.y, z);
  glEnd();*/ //moved to renderGameTile
}

//to render a chain of square tiles
//return y height
double renderGameTile(tTile * t, int treeLevel, tTile * prev = NULL){
  double z = 1;

  printf("\n");
  printStructGameTile(t);

  for(int i=0;i<treeLevel;i++) printf(" ");

  struct rectangle tempR;

  tempR = makeRect(t->r);//to position relative to previous tile...
  
  printf("(%d)Tile with angle %f, ", treeLevel++, t->angle);


  
  if(prev == NULL){
    printf(" (prev is null) ");
  }
  else{
    //place the rectangle next to prev

    struct coord2d left;
    struct coord2d right;
    
    printf(" (tile should start from ");
    printStructCoord2d(prev->r.p1);
    printStructCoord2d(prev->r.p4);
    printf(")");

    if(t== prev->n1){ printf("is n1! "); left = prev->r.p2; right = prev->r.p1; }
    if(t== prev->n2){ printf("is n2! "); left = prev->r.p3; right = prev->r.p2; }
    if(t== prev->n3){ printf("is n3! "); left = prev->r.p4; right = prev->r.p3; }

    //insert a top triangle if tile has angle (wants turning)

    //rotating a tile only if the previous tile has "angle" 
    if(prev->angle != 0){
        printf("prev has angle\n");
        int direction_swapper = prev->d == r ? 1 : -1;//r is right
        if(prev->d == r){ printf("prev-direction is right\n"); }
        struct coord2d turnXY = getTopPoint(prev->r.p3, prev->r.p2, prev->angle * direction_swapper);
        tempR = getRectangleFromBaseLineAndHeightWidth(turnXY, right, getDistBetweenCoord2ds(turnXY, right), getStructRectHeight(t->r));
    }
    else{
        tempR = getRectangleFromBaseLineAndHeightWidth(left, right, getDistBetweenCoord2ds(left, right), getStructRectHeight(t->r));//TODO: last arg must be calculated
    }

    t->r = tempR;
  }
  if(t->n1 == NULL) printf("n1 is null, ");
  else renderGameTile(t->n1, treeLevel, t);//todo: get the args for getRectangleFromBaseLineAndHeightWidth
  if(t->n2 == NULL) printf("n2 is null, ");
  else renderGameTile(t->n2, treeLevel, t);
  if(t->n3 == NULL) printf("n3 is null, ");
  else renderGameTile(t->n3, treeLevel, t);

  printf("\n");

  struct coord2d nr3;
  if(t->angle != 0){
    int direction_swapper = t->d == r ? 1 : -1;//r is right
    struct coord2d topTri = getTopPoint(t->r.p3, t->r.p2, t->angle * direction_swapper);
    nr3 = topTri;
  }
  else{
    nr3 = t->r.p2;
  }

  glBegin(GL_POLYGON);
  glColor3f(0.5, 0.3, ((float)treeLevel/10));
  glVertex3f(t->r.p1.x, t->r.p1.y, z);
  glVertex3f(t->r.p2.x, t->r.p2.y, z);
  //here if angle topTri
  glVertex3f(nr3.x, nr3.y, z);
  glVertex3f(t->r.p3.x, t->r.p3.y, z);
  glVertex3f(t->r.p4.x, t->r.p4.y, z);
  glEnd();

  double hei = getStructRectHeight(t->r);//TODO: add top-triangle height
  return hei;
}

//todo: use center, rotation
void renderTriangle(struct triangle tri, gender g, int treeLevel){
  printf("renderTriangle with center:\n");
  printStructCoord2d(tri.center, 1);
  printf("side: %f, rotation:%f\n", tri.side, tri.rotation);
  printGender(g);

  double genderAdd = g == male ? 0 : 180; // half circle
  double genderOffset = g == male ? 0 : .51;//todo: calculate //cos_degr(120);

  printf("genderAdd: %f , genderOffset: %f\n", genderAdd, genderOffset);
  tri.center.y += genderOffset;
  
  struct coord2d points[3];
  for(int i = 0; i<3; i++){
    points[i].x = sin_degr(i*120+tri.rotation+genderAdd)*tri.side + tri.center.x;
    points[i].y = cos_degr(i*120+tri.rotation+genderAdd)*tri.side + tri.center.y;// + genderOffset;
  }

  glBegin(GL_POLYGON);
  double color = treeLevel % 10;
  glColor3f(0.5, 0.3, color);
  glVertex3f(points[0].x, points[0].y, 0);
  glVertex3f(points[1].x, points[1].y, 0);
  glVertex3f(points[2].x, points[2].y, 0);
  glEnd();
}



void renderGameTriTile(tTriTile* tt, int treeLevel, tTriTile* prev, gender g){// = male

  newLineAndIndent(treeLevel);
  printf("renderGameTriTile, level %d, ", treeLevel);
  printGender(tt->g);
  newLineAndIndent(treeLevel);

  struct triangle tempT;

  double xOffset = sin_degr(120); //0,866

  double offsetX=0, offsetY=0;

  int neighbourCount=0;

  if(prev != NULL){
    printf("prev is set");
    newLineAndIndent(treeLevel);

    if(prev->nRight == tt){
      printf("this is right-side neighbour   ");
      offsetX=xOffset;
    }
    else if(prev->nLeft == tt){
      printf("this is left-side neighbour   ");
      offsetX=-xOffset;
    }
    else if(prev->yNeighbour == tt && prev->g == female){
      printf("this is upside neighbour   ");
      offsetY=1.5;//xOffset;
    }
    else if(prev->yNeighbour == tt && prev->g == male){
      printf("this is downside neighbour   ");
      offsetY=-1.5;
    }

    tt->t.center.x = prev->t.center.x + offsetX;
    tt->t.center.y = prev->t.center.y + offsetY;
  }
  else{
    printf("prev is NULL");
    newLineAndIndent(treeLevel);
  }

  if(tt->nRight != NULL){
    printf(" ->!");
    tt->nRight->g = getOpposite(tt->g);
    newLineAndIndent(treeLevel);
    //make temp triangle
    //call this method with tt as prev
    renderGameTriTile(tt->nRight, treeLevel+1, tt, getOpposite(tt->g));
    neighbourCount++;
  }
  else{ printf("tri nRight is null  "); }

  if(tt->nLeft != NULL){
    printf(" !<-");
    tt->nLeft->g = getOpposite(tt->g);
    newLineAndIndent(treeLevel);
    //make temp triangle
    renderGameTriTile(tt->nLeft, treeLevel+1, tt, getOpposite(tt->g));
    neighbourCount++;
  }
  else{ printf("tri nLeft is null  "); }

  if(tt->yNeighbour == NULL){
    printf("yNeighbour == NULL  ");
  }
  else{
    printf("yNeighbour is set on this cell ");
    printGender(tt->g);
    tt->yNeighbour->g = getOpposite(tt->g);
    newLineAndIndent(treeLevel);
    //printGameTriTile(tt->yNeighbour);
    renderGameTriTile(tt->yNeighbour, treeLevel+1, tt, getOpposite(tt->g));
    neighbourCount++;
  }

  renderTriangle(tt->t, g, treeLevel);
  printf("End of renderGameTriTile level %d, neighbourCount %d\n", treeLevel, neighbourCount);
}



//assuming tile is centered at 0,0 and spans 2 in width.
//replaced by getTopPoint
struct coord2d getCoordTopTriangle(enum dire d, float angle, struct rectangle rect){
  printf("getCoordTopTriangle angle %f\n", angle);
  if(d == l){
    printf("l\n");
  }
  else printf("r\n");

  //since sin (x-related) and cos (y...) would have origin in circle's top I must change the orientation since I want origin to be either right or left end of circle
  
  float x = cos_degr(angle);
  float y = sin_degr(angle);

  x *= TILEW;
  y *= TILEW;

  //the point should be relative to a tile top corner
    
  if(d == r){
    //
    x *= -1;
  }
  else{
    //
  }

  printf("x/y = %f/%f\n", x, y);

  struct coord2d ret;
  ret.x = x;
  ret.y = y;
  return ret;
}

struct letter{
  tTile * firstTile;
  double initialAngle; // 0 means stright up, 20 means little to the rigth, -20 left... maybe needs constraints
};

struct rectangle renderLetter(struct letter l){
  //TODO: if l has initialAngle != 0, do rotateRectangle on firstTile
  if(l.initialAngle != 0){
    rotateRectangle(&(l.firstTile->r), l.initialAngle);
  }
  renderGameTile(l.firstTile, 0);
}

//get the length of one side of a like-sided polygon, where radius of circle is 1
double getRatioPolygonSideAndRadius(int nrSides){
  if (nrSides < 3) return 0;
  
  struct coord2d p0;
  p0.x = 0;
  p0.y = 1;//top of a circle

  struct coord2d p1;

  double angle = 360 / nrSides;

  p1.x = sin_degr(angle);
  p1.y = cos_degr(angle);

  double distance = getDistBetweenCoord2ds(p0, p1);

  return distance;
}


struct coord2d deriveEvenPolygonCenter(struct coord2d left, struct coord2d right, char nrSides){

//1. know the angle of l1 and r1
//assuming the polygon is not rotated
int step = 360 / nrSides;//in degrees
double angleL1 = (180 + (double)step/2);
double angleR1 = (180 - (double)step/2);

//diff between angles
double adiff = angleL1 - angleR1;//i.e. 90 in a square

//get angle between points
float abp = getAngleBetweenPoints(left, right);
printf("angle between points: %.1f\n", abp);

//angle towards center should then be 90 less from plane but from a point?
//use adiff
//add half circle
double angleL = abp-90+(adiff/2)+180;
printf("angleL %.1f\n", angleL);

double angleR = abp-90-(adiff/2)+180;
printf("angleR %.1f\n", angleR);


//2. know the ratio between one side and the radius 
double ratio = getRatioPolygonSideAndRadius(nrSides);

printf("ratio: %.2f\n", ratio);

//get inverted ratio
double ratioI = 1/ratio;

//get distance between l1 r1
double distance = getDistBetweenCoord2ds(left, right);
printf("distance: %.2f\n", distance);

//calculate new radius ... distance to center
double newRadius = distance * ratioI;
printf("newRadius: %.2f\n", newRadius);

//invert the angle, direction to center
double newAngleL1 = (angleL+180);
double newAngleR1 = (angleL+180);

//continuing with (l)eft

//use sin and cos to get center
double newX = sin_degr(newAngleL1);
double newY = cos_degr(newAngleL1);

//add the known position
newX += left.x;
newY += left.y;

//printf("newX: %.1f, newY: %.1f\n", newX, newY);

struct coord2d c2dL = coord2dFromXY(newX, newY);

return c2dL;

}


struct cirkle2d deriveEvenPolygonCenterAndRadius(struct coord2d left, struct coord2d right, char nrSides){

printf("deriveEvenPolygonCenterAndRadius, nrSides: %d\n", nrSides);

//1. know the angle of l1 and r1
//assuming the polygon is not rotated
int step = 360 / nrSides;//in degrees
double angleL1 = (180 + (double)step/2);
double angleR1 = (180 - (double)step/2);

//diff between angles
double adiff = angleL1 - angleR1;//i.e. 90 in a square

//get angle between points
float abp = getAngleBetweenPoints(left, right);
printf("angle between points: %.1f\n", abp);

//angle towards center should then be 90 less from plane but from a point?
//use adiff
//add half circle
double angleL = abp-90+(adiff/2)+180;
//printf("angleL %.1f\n", angleL);

double angleR = abp-90-(adiff/2)+180;
//printf("angleR %.1f\n", angleR);


//2. know the ratio between one side and the radius 
//double ratio = getRatioPolygonSideAndRadius(nrSides);
double ratio = dists3_55[nrSides];

printf("ratio: %.2f\n", ratio);

//get inverted ratio
double ratioI = 1/ratio;

//get distance between l1 r1
double distance = getDistBetweenCoord2ds(left, right);
printf("distance: %.2f\n", distance);

//calculate new radius ... distance to center
double newRadius = distance * ratioI;
printf("newRadius: %.2f\n", newRadius);

//invert the angle, direction to center
double newAngleL1 = (angleL+180);
//double newAngleR1 = (angleL+180);

//continuing with (l)eft

//use sin and cos to get center
double newX = sin_degr(newAngleL1)*newRadius;//ratio;
double newY = cos_degr(newAngleL1)*newRadius;//ratio;

//add the known position
newX += left.x;
newY += left.y;

printf("newX: %.2f, newY: %.2f\n", newX, newY);

struct coord2d c2d = coord2dFromXY(newX, newY);
struct cirkle2d ci2d;
ci2d.center = c2d;
ci2d.radius = newRadius;

return ci2d;
}

void multiplyRadius(struct polyCell * p, double multiplyWith, char adjust = 0){
    p->radius *= multiplyWith;
    //if adjust
    if(adjust){ adjustPoints(p, multiplyWith); }
}
//scale from position 0,0
void adjustPoints(struct polyCell * p, double multiplyWith){
    if(multiplyWith == 1){ return; }
    else{
        for(int i=0; i<p->nrCorners; i++){
            p->points[i]->x *= multiplyWith;
            p->points[i]->y *= multiplyWith;
        }
    }
}

//create like-sided polygon using circle shape
//todo: think about if position should be an argument
struct gamePolyTile createPolygon(int nrSides, double rotation, double radius = 1){
  printf("createPolygon, nrSides: %d\n", nrSides);
  int step = 360 / nrSides;//in degrees
  double startDeg = (180 - (double)step/2) + rotation;
  double offsetX = 0;
  double offsetY = 0;//TODO:setting

  //not setting the position (coordinates)

  printf("----\n");
  struct polyCell * pc;
  printf("----\n");
  struct gamePolyTile gpt;
  printf("----\n");

  //first points
  printf("will malloc for points %d sides   \n", nrSides);
  struct coord2d ** pts;
  pts = (struct coord2d **) malloc (sizeof(struct coord2d *) * nrSides);

  //test
  struct gamePolyTile ** nghbrs;
  nghbrs = (struct gamePolyTile **) malloc(sizeof(struct gamePolyTile) * nrSides-1);

  for(int i = 0; i < nrSides-1; i++){
    nghbrs[i] = NULL;
  }

  printf("ok\n");
  
  //allocating memory and setting coordinates
  for(int i_ = nrSides-1, j=0; i_>=0; i_--){//making a counter clockwise circle/polygon
    //see how a ** array is assigned
    //first outer array (pts) was set
    //then each inner (tempxy) is set
    //printf("making a point for degree %f  ", startDeg);
    double tempx = sin_degr(startDeg)*radius + offsetX;
    double tempy = cos_degr(startDeg)*radius + offsetY; 
    printf("new coord: x %f y %f\n", tempx, tempy);
    struct coord2d * tempxy = (struct coord2d *) malloc (sizeof(struct coord2d));
    tempxy->x = tempx;
    tempxy->y = tempy;
    pts[j] = tempxy;
    j++;//filling up pts from zero to...
    startDeg -= step;
  }
  
  printf("will malloc for polyCell %ld \n", sizeof(struct polyCell));

  pc = (struct polyCell *) malloc(sizeof(struct polyCell));
  printf("will set center  ");
  pc->center = coord2dFromXY(offsetX, offsetY);

  pc->radius = radius;

  pc->points = pts;

  gpt.neighbours = nghbrs;

  printf("setting up gpt\n");
  //free(pc.points);
  gpt.pc = pc;
  gpt.angle = rotation;
  //gpt.nrCorners = nrSides;

  pc->nrCorners = nrSides;
  return gpt;
}//caller should free() resources

void freePolyTile(struct gamePolyTile gpt){

  printf("freePolyTile %c, having center:\n", gpt.name);
  printStructCoord2d(gpt.pc->center);
  printf("\n");
  
  for(int i=0; i<gpt.pc->nrCorners; i++){
    //each struct coord2d
    free(gpt.pc->points[i]);
  }
  free(gpt.pc);
}

void setPosition(struct gamePolyTile * gpt, double x, double y){
    gpt->pc->center.x = x;
    gpt->pc->center.y = y;
    //TODO: move all points
}

void translateGPT(struct gamePolyTile * gpt, double x, double y){

    //gpt->pc->center.x += x;
    //gpt->pc->center.y += y;
    translateC2d(&(gpt->pc->center), x, y);
    for(int i=0; i<gpt->pc->nrCorners;i++){//what if no pc i assigned?
        translateC2d(gpt->pc->points[i], x, y);
    }
}


