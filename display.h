#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "square.h"
#include <math.h>

int initWindow();
int mainLoop();
void renderScene();
void displayQTTree(QTNode *qn);
//void setNormals(Triangle *t);
//void displayTree(Triangle *t);
//void displayTree2();
void Draw_Axes ();

QTNode *qtn;
int *vertices;
int windowWidth = 1024;
int windowHeight = 768;
int nbVertex = 0;

int cameraDist = 2000;

int xSight = 0;
int ySight = 0;
int zSight = 0;

float xAngle = 0;
float yAngle = 0;
int moveDist = 128;
