#ifndef _VIEW_HH_
#define _VIEW_HH_

#include "all_includes.hh"

class Camera {
public :
	Vertex cameraCenter;
	Vertex cameraSight;

private :
	float xAngle;
	float yAngle;
	int moveSensitivity;
	float mouseSensitivity;
	bool up;
	bool down;
	bool left;
	bool right;
	bool pageUp;
	bool pageDown;

public :
	Camera(Vertex pos, float xA, float yA, int moveSensitivity, float mouseSensitivity);
	void setCamera();
	void mouseMotion(const SDL_MouseMotionEvent &event);
	void keyboard(const SDL_KeyboardEvent &event);
	void animation(int elapsedTime);
	std::ostream& print(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Camera& c) { return c.print(os); }
};


class View {
private :
	Chose* root;

public :
	Camera camera;
	static const int frontFrustum = 1;
	static const int backFrustum = 160000; // 1km
private:
	Lod lod;
    GLfloat fogColor[4];
    GLfloat density;
	static const int windowWidth = 1024;
	static const int windowHeight = 768;

public :
	View(Chose* root);
	void initWindow();
	void mainLoop();
	void renderScene(int lastTime, int currentTime);
	void displayAxes();

	static void setColor(unsigned char r, unsigned char g, unsigned char b);

private :
	void setLight();
};

#endif
