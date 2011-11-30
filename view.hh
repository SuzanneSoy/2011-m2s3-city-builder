#ifndef _VIEW_HH_
#define _VIEW_HH_

#include "all_includes.hh"

// TODO :
// flycam : le centre ne bouge pas, la souris contrôle l'angle de vue x & y
//          les flèches avant/arrière permettent d'avancer/reculer.
// Calcul correct des normales dans triangle.cpp
// Prendre en compte tous les évènements X en attente avant de relancer le rendu.

class Camera {
	private:
	Vertexf cameraCenter;
	Vertexf cameraSight;
	float xAngle;
	float yAngle;
	int moveDist;
	float mouseSensitivity;
	bool up;
	bool down;
	bool left;
	bool right;
	bool pageUp;
	bool pageDown;
	
	public:
	Camera(Vertexf pos, float xA, float yA, int moveSensitivity, float mouseSensitivity);
	void setCamera();
	void mouseMotion(const SDL_MouseMotionEvent &event);
	void keyboard(const SDL_KeyboardEvent &event);
	void animation(int elapsedTime);
};


class View {
	private:
	Chose* root;
	Camera camera;
	
	static const int windowWidth = 1024;
	static const int windowHeight = 768;

	public:
	View(Chose* root);
	void initWindow();
	void mainLoop();
	void renderScene(int lastTime, int currentTime);
	void displayAxes();

	static void setColor(unsigned char r, unsigned char g, unsigned char b);
	
	private:
	void setLight();
};

#endif
