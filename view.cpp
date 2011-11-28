#include "all_includes.hh"

View::View(Chose* root) : root(root), cameraCenter(500,500,10), cameraDist(300), xSight(0), ySight(0), zSight(0), xAngle(0), yAngle(0), moveDist(10) {
	initWindow();
	mainLoop();
}

void View::initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)windowWidth/windowHeight,1,10000);
	glEnable(GL_DEPTH_TEST);
	glewInit();
	
	float MatSpec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float MatDif[4] = {0.0f, 0.5f, 0.0f, 1.0f};
	float MatAmb[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	 
	float Light1Pos[4] = {0.0f, 1.0f, 0.0f, 0.0f};
	float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float Light1Spec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float Light1Amb[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	float shininess = 128.0f;

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
	
	glEnable(GL_LIGHTING); 	// Active l'éclairage
  	glEnable(GL_LIGHT0);	// Active la lumière 0;
}

void View::displayAxes() {
	glDisable(GL_LIGHTING);
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

	Vertex dest = Vertex::fromSpherical(100, xAngle, yAngle);
	glBegin(GL_LINES);
	glColor3ub(255,0,255);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3d(dest.x, dest.y, dest.z); // ending point of the line
	glEnd( );
	
	dest = cameraCenter - dest;
	glBegin(GL_LINES);
	glColor3ub(255,255,0);
	glVertex3d(cameraCenter.x, cameraCenter.y, cameraCenter.z); // origin of the line
	glVertex3d(dest.x, dest.y, dest.z); // ending point of the line
	glEnd( );
	
	glEnable(GL_LIGHTING);
}

void View::renderScene() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1024,512,1356,1024,512,0,0,1,0);
	
	//glClearColor(1,1,1,1); // pour un fond blanc
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	
	//gluLookAt(0,0,cameraDist, 0, 0, 0,0,1,0);
	// glTranslated(-xSight,-ySight,-(zSight+cameraDist));
	glRotatef(-yAngle,1,0,0);
	glRotatef(-xAngle,0,0,1);
	glTranslated(-cameraCenter.x, -cameraCenter.y, -cameraCenter.z);
	
	displayAxes();
	glBegin(GL_TRIANGLES);
	root->display();
	glEnd();
	
	glFlush();
	SDL_GL_SwapBuffers();
}

void View::mainLoop() {
	short continuer = 1;
	SDL_Event event;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_DOWN:
						cameraCenter = cameraCenter + Vertex::fromSpherical(10, xAngle, yAngle);
						break;
					case SDLK_UP:
						cameraCenter = cameraCenter - Vertex::fromSpherical(10, xAngle, yAngle);
						break;
					default:
						break;
				}
				break;
				
			case SDL_MOUSEMOTION:
				xAngle = ((event.motion.x-windowWidth/2)*340/(windowWidth));
				yAngle = (event.motion.y-windowHeight/2)*340/(windowHeight);
				break;
				
			default:
				break;
		}

		renderScene();
	}

	SDL_Quit();
}
