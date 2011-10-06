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
