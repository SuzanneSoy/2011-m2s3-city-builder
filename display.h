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

float xCamera = 100;
float yCamera = 500;
float zCamera = 1500;

int xSight = 100;
int ySight = -500;
int zSight = -1500;

float xAngle = 0;
float yAngle = 0;
int moveDist = 64;
