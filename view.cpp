#include "all_includes.hh"

View::View(Chose* root) : root(root), cameraCenter(127,14,128), xAngle(44), yAngle(101), moveDist(4), mouseSensitivity(0.4) {
	cameraSight = cameraCenter + Vertex::fromSpherical(100, yAngle, xAngle);
	initWindow();
	mainLoop();
}

void View::setColor(unsigned char r, unsigned char g, unsigned char b) {
	float MatDif[4] = {r/255.f, g/255.f, b/255.f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
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
	float MatDif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	float MatAmb[4] = {0.4f, 0.4f, 0.4f, 1.0f};
	float shininess = 128.0f;
	 
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);
	
	glEnable(GL_LIGHTING); 	// Active l'éclairage
  	glEnable(GL_LIGHT0);	// Active la lumière 0;
}

void View::setLight() {
	float Light1Pos[4] = {0.5f, 1.0f, 1.0f, 0.0f};
	float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float Light1Spec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float Light1Amb[4] = {0.2f, 0.2f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);
	glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);
}

void View::displayAxes() {
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);
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
	glVertex3f(0.0f, 0.0f, 2500.0f); // ending point of the line
	glEnd( );

	glEnable(GL_LIGHTING);
}

void View::renderScene() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	
	cameraSight = cameraCenter + Vertex::fromSpherical(100, yAngle, xAngle);
	gluLookAt(cameraCenter.x,cameraCenter.y,cameraCenter.z, cameraSight.x, cameraSight.y, cameraSight.z,0,0,1);
	setLight();
	displayAxes();
	root->display();
	
	glFlush();
	SDL_GL_SwapBuffers();
}

void View::mainLoop() {
	short continuer = 1;
	SDL_Event event;
	SDL_EnableKeyRepeat(40,40);
	SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);


	while (continuer) {
		while ( SDL_PollEvent(&event) ) {
			switch(event.type) {
				case SDL_QUIT:
					continuer = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_DOWN:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, yAngle, xAngle);
							break;
						case SDLK_UP:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, yAngle, xAngle);
							break;
						case SDLK_PAGEUP:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, yAngle + 90, xAngle);
							break;
						case SDLK_PAGEDOWN:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, yAngle + 90, xAngle);
							break;
						case SDLK_LEFT:
							cameraCenter = cameraCenter - Vertex::fromSpherical(moveDist, 90, xAngle - 90);
							break;
						case SDLK_RIGHT:
							cameraCenter = cameraCenter + Vertex::fromSpherical(moveDist, 90, xAngle - 90);
							break;
						case SDLK_ESCAPE:
							continuer = 0;
							break;
						default:
							if (SDL_GetKeyName(event.key.keysym.sym)[0] == 'q')
								continuer = 0;
							if (SDL_GetKeyName(event.key.keysym.sym)[0] == 'p') { // _Print _Position
								std::cout << "Camera = " << cameraCenter << " xAngle = " << xAngle << " yAngle = " << yAngle << std::endl;
							}
							break;
					}
					break;
					
				case SDL_MOUSEMOTION:
					xAngle -= event.motion.xrel*mouseSensitivity;
					yAngle += event.motion.yrel*mouseSensitivity;
					if(yAngle > 179)
						yAngle = 179;
					else if(yAngle < 1)
						yAngle = 1;
					break;
					
				default:
					break;
			}
		}

		renderScene();
	}

	SDL_Quit();
}
