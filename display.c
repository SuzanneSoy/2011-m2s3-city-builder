#include "display.h"

int initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)windowWidth/windowHeight,1,10000);
	glEnable(GL_DEPTH_TEST);
	glewInit();
	
	float MatSpec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float MatDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float MatAmb[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	 
	float Light1Pos[4] = {0.0f, 0.0f, -1.0f, 0.0f};
	float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float Light1Spec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float Light1Amb[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	//float shininess = 128.0f;

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
	//glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	
	glEnable(GL_LIGHTING); 	// Active l'éclairage
  	glEnable(GL_LIGHT0);	// Active la lumière 0;
  	
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
					case SDLK_y:
						yAngle += 8;
						break;
					case SDLK_x:
						xAngle += 8;
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
	
	//glClearColor(1,1,1,1); // pour un fond blanc
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	drawAxes();
	glRotated(yAngle,0,1,0);
	glRotated(xAngle,1,0,0);
	//displayTree2();
	displayTree(t);
	
	glFlush();
	SDL_GL_SwapBuffers();
}


int nbTriangles(Triangle *t) {
	int sum = 0;
	
	if(t->tLeftChild == NULL) {
		return 1;
	}
	else {
		sum += nbTriangles(t->tLeftChild);
		sum += nbTriangles(t->tRightChild);
	}
	
	return sum;
}


void insertValues(Triangle *t,int *vertices) {
	if(t->tLeftChild == NULL) {
		vertices[9*nbVertex] = t->vLeft->x;
		vertices[9*nbVertex+1] = t->vLeft->y;
		vertices[9*nbVertex+2] = t->vLeft->z;
		vertices[9*nbVertex+3] = t->vApex->x;
		vertices[9*nbVertex+4] = t->vApex->y;
		vertices[9*nbVertex+5] = t->vApex->z;
		vertices[9*nbVertex+6] = t->vRight->x;
		vertices[9*nbVertex+7] = t->vRight->y;
		vertices[9*nbVertex+8] = t->vRight->z;
		nbVertex++;
	}
	else {
		insertValues(t->tLeftChild,vertices);
		insertValues(t->tRightChild,vertices);
	}
}


void displayTree2() {
	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glColor3ub(255,255,255);
	glDrawArrays(GL_LINE_LOOP,0, nbVertex*3);
}

void setNormals(Triangle *t) {
	if(t->tLeftChild == NULL) {
		int ax = t->vLeft->x - t->vApex->x;
		int ay = t->vLeft->y - t->vApex->y;
		int az = t->vLeft->z - t->vApex->z;
		int bx = t->vApex->x - t->vRight->x;
		int by = t->vApex->y - t->vRight->y;
		int bz = t->vApex->z - t->vRight->z;
		
		float x = (float)((ay * bz) - (az * by));
		float y = (float)((az * bx) - (ax * bz));
		float z = (float)((ax * by) - (ay * bx));
		float length = sqrt(((int)x^2) + ((int)y^2) + ((int)z^2));
		
		length = length*100;
		x = x/length;
		y = y/length;
		z = z/length;

		
	printf("%f %f %f\n",x,y,z);
		t->vLeft->xNormal = x;
		t->vLeft->yNormal = y;
		t->vLeft->zNormal = z;
		t->vRight->xNormal = x;
		t->vRight->yNormal = y;
		t->vRight->zNormal = z;
		t->vApex->xNormal = x;
		t->vApex->yNormal = y;
		t->vApex->zNormal = z;
	}
	else {
		setNormals(t->tLeftChild);
		setNormals(t->tRightChild);
	}
}

void displayTree(Triangle *t) {
	if(t->tLeftChild == NULL) {
		glNormal3f(t->vLeft->xNormal,t->vLeft->yNormal,t->vLeft->zNormal);
		//glNormal3d(0,1,0);
		glBegin(GL_TRIANGLES);
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
	
	// Calcul des normales des traingles.
	setNormals(t);
	
	// Réorganisation des sommets pour l'affichage optimisé.
	//vertices = (int*) malloc(sizeof(int) * nbTriangles(t)*9+1);
	//insertValues(t,vertices);
	
	printf("nombre de triangles : %d\n",nbVertex);
	
	mainLoop();

	// Pour afficher le terrain :
	/* int x; */
	/* int y; */
	/* #define SIZE 1024 */
	/* printf("P5 %d %d 255\n", SIZE, SIZE); */
	/* for (y = 0; y < SIZE; y++) { */
	/* 	for (x = 0; x < SIZE; x++) { */
	/* 		//int bit = y / (SIZE/32); */
	/* 		//int h = hash2(x, 300+y); */
	/* 		//if (y % (SIZE/32) == 0) h = 0; */
	/* 		//printf("%c", ((h >> (31-bit)) & 1) * 255); */
	/* 		//printf("%c", interpolation(256+x, 256+y, 256, 256, 512, 512, 0, 255, 255, 255)); */
	/* 		printf("%c", get_z(x,y)); */
	/* 	} */
	/* } */
	return 0;
}
