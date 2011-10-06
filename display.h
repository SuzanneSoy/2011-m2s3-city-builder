#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "roam.h"
#include <math.h>

int initWindow();
int mainLoop();
void renderScene();
void setNormals(Triangle *t);
void displayTree(Triangle *t);
void displayTree2();
void Draw_Axes ();

Triangle *t;
int *vertices;
int windowWidth = 1024;
int nbVertex = 0;
int windowHeight = 768;
int xCamera = 256;
int yCamera = 100;
int zCamera = 400;
int xSight = 256;
int ySight = 128;
int zSight = 0;
int yAngle = 0;
int xAngle = 0;
int moveDist = 16;
