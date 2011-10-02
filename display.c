#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "roam.h"

int initWindow();
int mainLoop();
void renderScene();
void displayTree(Triangle *t);
void Draw_Axes ();

Triangle *t;
int windowWidth = 1024;
int windowHeight = 768;
int xCamera = 1024;
int yCamera = -800;
int zCamera = 600;
int xSight = 1024;
int ySight = 512;
int zSight = 0;
int moveDist = 64;

int initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)windowWidth/windowHeight,1,10000);
	glEnable(GL_DEPTH_TEST);

	return 0;
}

int mainLoop() {
	short continuer = 1;
	SDL_Event event;

	while (continuer) {
		SDL_WaitEvent(&event);
		
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_DOWN:
						yCamera-=moveDist;
						ySight-=moveDist;
						break;
					case SDLK_UP:
						yCamera+=moveDist;
						ySight+=moveDist;
						break;
					case SDLK_LEFT:
						xCamera-=moveDist;
						xSight-=moveDist;
						break;
					case SDLK_RIGHT:
						xCamera+=moveDist;
						xSight+=moveDist;
						break;
					default:
						break;
				}
		}

		renderScene();
	}

	SDL_Quit();

	return 0;
}

void drawAxes() {
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(2500.0f, 0.0f, 0.0f); // ending point of the line
	glEnd( );
	
	glBegin(GL_LINES);
	glColor3ub(0,255,0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 2500.0f, 0.0f); // ending point of the line
	glEnd( );
	
	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, -2500.0f); // ending point of the line
	glEnd( );
}

void renderScene() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1024,512,1356,1024,512,0,0,1,0);
	gluLookAt(xCamera,yCamera,zCamera,xSight,ySight,zSight,0,1,0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	drawAxes();
	displayTree(t);
	
	glFlush();
	SDL_GL_SwapBuffers();
}

void displayTree(Triangle *t) {
	if(t->tLeftChild == NULL) {
		glBegin(GL_LINE_LOOP);
			glColor3ub(255,255,255);
			glVertex3d(t->vLeft->x,t->vLeft->y,t->vLeft->z);
			glVertex3d(t->vApex->x,t->vApex->y,t->vApex->z);
			glVertex3d(t->vRight->x,t->vRight->y,t->vRight->z);
		glEnd();
	}
	else {
		displayTree(t->tLeftChild);
		displayTree(t->tRightChild);
	}
}

int main() {
	initWindow();
	t = initDefaultExample();
	
	mainLoop();

	// Pour afficher le terrain :
	/* int x; */
	/* int y; */
	/* #define SIZE 256 */
	/* printf("P5 %d %d 255\n", SIZE, SIZE); */
	/* for (y = 0; y < SIZE; y++) { */
	/* 	for (x = 0; x < SIZE; x++) { */
	/* 		//int bit = y / (SIZE/32); */
	/* 		//int h = hash2(t,hash2(x, y)); */
	/* 		//if (y % (SIZE/32) == 0) h = 0; */
	/* 		//printf("%c", ((h >> (31-bit)) & 1) * 255); */
	/* 		//printf("%c", interpolation(256+x, 256+y, 256, 256, 512, 512, 0, 255, 255, 255)); */
	/* 		printf("%c", get_z(x,y)); */
	/* 	} */
	/* } */
	return 0;
}
