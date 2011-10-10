#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "square.h"
#include <math.h>

int initWindow();
int mainLoop();
void renderScene();
//void setNormals(Triangle *t);
//void displayTree(Triangle *t);
//void displayTree2();
void Draw_Axes ();

//Triangle *t;
int *vertices;
int windowWidth = 1024;
int nbVertex = 0;
int windowHeight = 768;
float xCamera = 1024;
float yCamera = 400;
float zCamera = 1500;
int xSight = 0;
int ySight = 112;
int zSight = -1500;
float xAngle = 0;
float yAngle = 0;
int moveDist = 64;
