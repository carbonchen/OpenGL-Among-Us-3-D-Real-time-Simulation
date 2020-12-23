#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Geometry.h"
#include "Transform.h"
#include "boundingSphere.h"
#include "boundingPlane.h"

class Window
{
public:

	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;

	// Objects to Render
	static Transform* world;

	static Geometry* lobby;
	static Geometry* red;
	static Geometry* pink;
	static Geometry* cyan;
	static Geometry* yellow;
	static Geometry* purple;
	static Geometry* blue;
	static Geometry* green;
	static Geometry* white;
	static Geometry* orange;
	static Geometry* black;

	static Transform* rotate_red;
	static Transform* rotate_pink;
	static Transform* rotate_cyan;
	static Transform* rotate_yellow;
	static Transform* rotate_purple;
	static Transform* rotate_blue;
	static Transform* rotate_green;
	static Transform* rotate_white;
	static Transform* rotate_orange;
	static Transform* rotate_black;

	static Transform* translate_red;
	static Transform* translate_pink;
	static Transform* translate_cyan;
	static Transform* translate_yellow;
	static Transform* translate_purple;
	static Transform* translate_blue;
	static Transform* translate_green;
	static Transform* translate_white;
	static Transform* translate_orange;
	static Transform* translate_black;

	static std::vector<Transform*> astroList;
	static std::vector<boundingSphere*> boxes;
	static std::vector<boundingPlane*> planeList;

	static boundingSphere* box1;
	static boundingSphere* box2;
	static boundingPlane* stairs;
	static boundingPlane* leftWall;
	static boundingPlane* rightWall;
	static boundingPlane* leftDiagWall;
	static boundingPlane* rightDiagWall;
	static boundingPlane* bottomWall;

	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector;

	// Shader Program ID
	static GLuint shaderProgram;
	static GLuint lobbyShader;

	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);

	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	// mouse and movement interaction
	static glm::vec3 trackball(glm::vec2 mouseCoord);
	static bool mouseDown;
	static glm::vec3 lastMousePoint;
	static std::string lastDir;

	// detect collision
	static bool sphereToSphereCollision(boundingSphere* sphere1, boundingSphere* sphere2);
	static bool sphereToPlaneCollision(boundingSphere* sphere, boundingPlane* plane);

	static int holdMove;
	static bool pinkGone;
	static bool cyanGone;
	static bool yellowGone;
	static bool purpleGone;
	static bool blueGone;
	static bool greenGone;
	static bool whiteGone;
	static bool orangeGone;
	static bool blackGone;
};

#endif
