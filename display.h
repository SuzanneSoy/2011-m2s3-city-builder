#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "roam.h"

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
int xCamera = 1024;
int yCamera = -800;
int zCamera = 600;
int xSight = 1024;
int ySight = 512;
int zSight = 0;
int yAngle = 0;
int xAngle = 0;
int moveDist = 64;
