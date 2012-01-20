#include "all_includes.hh"

View::View(Chose* _root)
: root(_root),
  camera(Camera(Vertex(0,0,5000), 45, 100, 10000, 0.6f)),
  lod(camera.cameraCenter, _root) {

	fogColor[0] = Couleurs::r(Couleurs::fog) / 255.f;
	fogColor[1] = Couleurs::g(Couleurs::fog) / 255.f;
	fogColor[2] = Couleurs::b(Couleurs::fog) / 255.f;
	fogColor[3] = 1.0;
	initWindow();
	mainLoop();
}

void View::setColor(unsigned char r, unsigned char g, unsigned char b) {
	float red   = (float)r / 255.f;
	float green = (float)g / 255.f;
	float blue  = (float)b / 255.f;
	float MatDif[4] = {red, green, blue, 1.0f};
	float MatAmb[4] = {red, green, blue, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
}

void View::initWindow() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Sortie terrain OpenGL",NULL);
	SDL_SetVideoMode(Dimensions::windowWidth, Dimensions::windowHeight, 32, SDL_OPENGL);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,Dimensions::windowWidth/Dimensions::windowHeight,Dimensions::frontFrustum,Dimensions::backFrustum);
	glEnable(GL_DEPTH_TEST);
	glewInit();

	float MatSpec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float MatDif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	float MatAmb[4] = {0.3f, 0.3f, 0.6f, 1.0f};
	float shininess = 128.0f;

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
	glMaterialfv(GL_FRONT,GL_SHININESS,&shininess);

	glEnable(GL_LIGHTING); 	// Active l'éclairage
	glEnable(GL_LIGHT0);	// Active la lumière 0;

	glEnable (GL_FOG);
	glFogi (GL_FOG_MODE, GL_LINEAR);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_START, Dimensions::backFrustum / std::sqrt(3.f) / 2.f);
	glFogf (GL_FOG_END, Dimensions::backFrustum / std::sqrt(3.f) * 0.9f);
	//glHint (GL_FOG_HINT, GL_NICEST);
}

void View::setLight() {
	float Light1Pos[4] = {-0.5f, -1.0f, 1.0f, 0.0f};
	float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float Light1Spec[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float Light1Amb[4] = {0.4f, 0.4f, 0.4f, 1.0f};

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

void View::setSkybox() {
	//int z = 40000;
	float d = Dimensions::backFrustum / std::sqrt(3.f) * 0.9f;
	glDisable(GL_FOG);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(camera.cameraCenter.x,camera.cameraCenter.y,0);
	for(int ii=0; ii<4;ii++) {
		glBegin(GL_QUADS);
		{
			glColor3ub(Couleurs::r(Couleurs::cielBas),Couleurs::g(Couleurs::cielBas),Couleurs::b(Couleurs::cielBas));
			glVertex3f(-d,d,-d);
			glVertex3f(d,d,-d);
			glColor3ub(Couleurs::r(Couleurs::cielHaut),Couleurs::g(Couleurs::cielHaut),Couleurs::b(Couleurs::cielHaut));
			glVertex3f(d,d,d);
			glVertex3f(-d,d,d);
		}
		glEnd();
		glRotated(90,0,0,1);
	}

	glBegin(GL_QUADS);
	{
		glColor3ub(Couleurs::r(Couleurs::cielHaut),Couleurs::g(Couleurs::cielHaut),Couleurs::b(Couleurs::cielHaut));
		glVertex3f(-d,d,d);
		glVertex3f(d,d,d);
		glVertex3f(d,-d,d);
		glVertex3f(-d,-d,d);
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		glColor3ub(Couleurs::r(Couleurs::herbe),Couleurs::g(Couleurs::herbe),Couleurs::b(Couleurs::herbe));
		glVertex3f(-d,d,-d);
		glVertex3f(d,d,-d);
		glVertex3f(d,-d,-d);
		glVertex3f(-d,-d,-d);
	}
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
}

void View::renderScene(int lastTime, int currentTime) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	camera.animation(std::min(100, currentTime-lastTime));
	camera.setCamera();
	lod.setCamera(camera.cameraCenter);

	setLight();
	setSkybox();

	glBegin(GL_TRIANGLES);
	root->display();
	glEnd();
	if (false) { // displayNormals ?
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
		root->displayNormals();
		glEnd();
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	}

	float fps = (int)(1000/(currentTime-lastTime));
	char text[100];	//	Text
	snprintf(&(text[0]), 100, "FPS: %4.2f", fps);
	glLoadIdentity ();
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 0.0f);
	//glRasterPos3f (0, 0, 0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)(&(text[0])));

	glFlush();
	SDL_GL_SwapBuffers();
}

void View::mainLoop() {
	short continuer = 1;
	SDL_Event event;
	SDL_EnableKeyRepeat(40,40);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);
	while ( SDL_PollEvent(&event) ); // empty queue.

	int lastTime = SDL_GetTicks() - 30;
	int currentTime = 0;

	while (continuer) {
		lastTime = currentTime;
		currentTime = SDL_GetTicks();
		while ( SDL_PollEvent(&event) ) {
			switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				camera.keyboard(event.key);
				break;
			case SDL_MOUSEMOTION:
				camera.mouseMotion(event.motion);
				break;
			default:
				break;
			}
		}
		renderScene(lastTime,currentTime);
	}

	SDL_Quit();
}

Camera::Camera(Vertex _cameraCenter, float _xAngle, float _yAngle, int _moveSensitivity, float _mouseSensitivity)
: cameraCenter(_cameraCenter),
  cameraSight(cameraCenter + Vertex::fromSpherical(100,_yAngle,_xAngle)),
  xAngle(_xAngle),
  yAngle(_yAngle),
  moveSensitivity(_moveSensitivity),
  mouseSensitivity(_mouseSensitivity),
  up(false), down(false), left(false), right(false),
  pageUp(false), pageDown(false)
{
}

std::ostream& Camera::print(std::ostream& os) const {
	return os << "Camera = " << cameraCenter << " xAngle = "
			<< xAngle << " yAngle = " << yAngle;
}

void Camera::setCamera() {
	cameraSight = cameraCenter + Vertex::fromSpherical(100, yAngle, xAngle);
	gluLookAt(cameraCenter.x,cameraCenter.y,cameraCenter.z, cameraSight.x, cameraSight.y, cameraSight.z,0,0,1);
}

void Camera::mouseMotion(const SDL_MouseMotionEvent &event) {
	xAngle -= (float)(event.xrel) * mouseSensitivity;
	yAngle += (float)(event.yrel) * mouseSensitivity;
	xAngle = std::fmod(xAngle + 360, 360);
	if(yAngle > 179)
		yAngle = 179;
	else if(yAngle < 1)
		yAngle = 1;
}

void Camera::keyboard(const SDL_KeyboardEvent &eventKey) {
	switch(eventKey.keysym.sym) {
	case SDLK_UP:
		up = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_DOWN:
		down = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_LEFT:
		left = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_RIGHT:
		right = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_PAGEUP:
		pageUp = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_PAGEDOWN:
		pageDown = (eventKey.type == SDL_KEYDOWN);
		break;
	case SDLK_ESCAPE:
		exit(0);
		break;
    case SDLK_KP0:
        moveSensitivity = 0;
        break;
    case SDLK_KP1:
        moveSensitivity = 300;
        break;
    case SDLK_KP2:
        moveSensitivity = 1000;
        break;
    case SDLK_KP3:
        moveSensitivity = 6000;
        break;
	default :
		switch(SDL_GetKeyName(eventKey.keysym.sym)[0]) {
			case 'q':
				exit(0);
				break;
            case 'a' :
                up = true;
                break;
            case 'z' :
                up = false;
                break;
			case 's':
				if (eventKey.type != SDL_KEYDOWN) break;
				moveSensitivity = std::min(50000,std::max(moveSensitivity+1, moveSensitivity*10/9));
				break;
			case 'x':
				if (eventKey.type != SDL_KEYDOWN) break;
				moveSensitivity = std::max(10, moveSensitivity*9/10);
				break;
			case 'p': // _Print _Position
				if (eventKey.type != SDL_KEYDOWN) break;
				std::cout << *this << std::endl;
				break;
			case 't': {
                char* file = new char[256];
                memset(file,'\n',256);
                sprintf(file,"city-builder_%d_%d.bmp",Chose::initialSeed,(int)time(NULL));
				takeScreenshot(file);
				break;
				}
			case 'c':
		        moveSensitivity = 0;
		        break;
		    case 'v':
		        moveSensitivity = 300;
		        break;
		    case 'b':
		        moveSensitivity = 1000;
		        break;
		    case 'n':
		        moveSensitivity = 6000;
		        break;
			default:
				break;
		}
		break;
	}
}

void Camera::animation(int elapsedTime) {
	float diff = ((float)(elapsedTime+1)/1000.f)*(float)moveSensitivity;

	if(up)
		cameraCenter = cameraCenter + Vertex::fromSpherical(diff, yAngle, xAngle);
	if(down)
		cameraCenter = cameraCenter - Vertex::fromSpherical(diff, yAngle, xAngle);
	if(left)
		cameraCenter = cameraCenter - Vertex::fromSpherical(diff, 90, xAngle - 90);
	if(right)
		cameraCenter = cameraCenter + Vertex::fromSpherical(diff, 90, xAngle - 90);
	if(pageUp)
		cameraCenter = cameraCenter - Vertex::fromSpherical(diff, yAngle + 90, xAngle);
	if(pageDown)
		cameraCenter = cameraCenter + Vertex::fromSpherical(diff, yAngle + 90, xAngle);
}




SDL_Surface * flipSurface(SDL_Surface * surface) {
    int current_line,pitch;
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
    surface->w,surface->h,
    surface->format->BitsPerPixel,
    surface->format->Rmask,
    surface->format->Gmask,
    surface->format->Bmask,
    surface->format->Amask);

    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);

    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++) {
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
        &((unsigned char* )surface->pixels)[(surface->h - 1 -
        current_line)*pitch],
        pitch);
    }

    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}

int Camera::takeScreenshot(const char * filename) {
    GLint viewport[4];
    Uint32 rmask, gmask, bmask, amask;
    SDL_Surface * picture, * finalpicture;

    glGetIntegerv(GL_VIEWPORT, viewport);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif

    picture = SDL_CreateRGBSurface(SDL_SWSURFACE,viewport[2],viewport[3], 32,
    rmask, gmask, bmask, amask);
    SDL_LockSurface(picture);
    glReadPixels(viewport[0],viewport[1],viewport[2],viewport[3],GL_RGBA,
    GL_UNSIGNED_BYTE,picture->pixels);
    SDL_UnlockSurface(picture);

    finalpicture = flipSurface(picture);

    if (SDL_SaveBMP(finalpicture, filename)) {
        exit(1);
    }
    SDL_FreeSurface(finalpicture);
    SDL_FreeSurface(picture);

    return 0;
}
