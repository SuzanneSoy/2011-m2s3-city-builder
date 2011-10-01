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

int initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)640/480,1,10000);
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
	gluLookAt(1024,-200,500,1024,512,0,0,1,0);

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
	/* printf("P5 %d %d 255\n", 256, 256); */
	/* for (y = 0; y < 256; y++) { */
	/* 	for (x = 0; x < 256; x++) { */
	/* 		printf("%c", get_z(x, y));//interpolation(256+x, 256+y, 256, 256, 512, 512, 0, 255, 255, 255)); */
	/* 	} */
	/* } */
	return 0;
}
