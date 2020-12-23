#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "OpenGL Project";

// Objects to Render
Transform* Window::world;
Geometry* Window::lobby;

Geometry* Window::red;
Geometry* Window::pink;
Geometry* Window::cyan;
Geometry* Window::yellow;
Geometry* Window::purple;
Geometry* Window::blue;
Geometry* Window::green;
Geometry* Window::white;
Geometry* Window::orange;
Geometry* Window::black;

Transform* Window::rotate_red;
Transform* Window::rotate_pink;
Transform* Window::rotate_cyan;
Transform* Window::rotate_yellow;
Transform* Window::rotate_purple;
Transform* Window::rotate_blue;
Transform* Window::rotate_green;
Transform* Window::rotate_white;
Transform* Window::rotate_orange;
Transform* Window::rotate_black;

Transform* Window::translate_red;
Transform* Window::translate_pink;
Transform* Window::translate_cyan;
Transform* Window::translate_yellow;
Transform* Window::translate_purple;
Transform* Window::translate_blue;
Transform* Window::translate_green;
Transform* Window::translate_white;
Transform* Window::translate_orange;
Transform* Window::translate_black;

std::vector<Transform*> Window::astroList;
std::vector<boundingSphere*> Window::boxes;
std::vector<boundingPlane*> Window::planeList;

boundingSphere* Window::box1;
boundingSphere* Window::box2;
boundingPlane* Window::stairs;
boundingPlane* Window::leftWall;
boundingPlane* Window::rightWall;
boundingPlane* Window::leftDiagWall;
boundingPlane* Window::rightDiagWall;
boundingPlane* Window::bottomWall;

int Window::holdMove = 0;
bool Window::pinkGone = false;
bool Window::cyanGone = false;
bool Window::yellowGone = false;
bool Window::purpleGone = false;
bool Window::blueGone = false;
bool Window::greenGone = false;
bool Window::whiteGone = false;
bool Window::orangeGone = false;
bool Window::blackGone = false;

// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection; 

// View Matrix:
glm::vec3 Window::eyePos(0, 40, 20);			// Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);		// The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);		// The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

// Shader Program ID
GLuint Window::shaderProgram;
GLuint Window::lobbyShader;

// Interaction options
bool Window::mouseDown;
glm::vec3 Window::lastMousePoint;
// track Red's movement
std::string Window::lastDir = "s";

bool Window::initializeProgram() {
	// Create shader programs with vertex and fragment shaders
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
	lobbyShader = LoadShaders("shaders/lobbyShader.vert", "shaders/lobbyShader.frag");

	// Check the shader programs
	if (!shaderProgram || !lobbyShader)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	return true;
}

bool Window::initializeObjects()
{
	// initialize objects and construct world graph here
	world = new Transform(glm::mat4(1.0f));
	lobby = new Geometry("./lobby/amongus_lobby.obj", "lobby");

	red = new Geometry("./astronauts/amongus_astro_still.obj", "red");
	pink = new Geometry("./astronauts/amongus_astro_still.obj", "pink");
	cyan = new Geometry("./astronauts/amongus_astro_still.obj", "cyan");
	yellow = new Geometry("./astronauts/amongus_astro_still.obj", "yellow");
	purple = new Geometry("./astronauts/amongus_astro_still.obj", "purple");
	blue = new Geometry("./astronauts/amongus_astro_still.obj", "blue");
	green = new Geometry("./astronauts/amongus_astro_still.obj", "green");
	white = new Geometry("./astronauts/amongus_astro_still.obj", "white");
	orange = new Geometry("./astronauts/amongus_astro_still.obj", "orange");
	black = new Geometry("./astronauts/amongus_astro_still.obj", "black");

	rotate_red = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 8.0f)));
	rotate_pink = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-14.0f, 0.3f, 16.0f)));
	rotate_cyan = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-13.0f, 0.3f, 7.0f)));
	rotate_yellow = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.3f, 13.0f)));
	rotate_purple = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.3f, 15.0f)));
	rotate_blue = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 12.0f)));
	rotate_green = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.3f, 17.0f)));
	rotate_white = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.3f, 10.0f)));
	rotate_orange = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 17.0f)));
	rotate_black = new Transform(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.3f, 19.0f)));

	translate_red = new Transform(glm::mat4(1.0f));
	translate_pink = new Transform(glm::mat4(1.0f));
	translate_cyan = new Transform(glm::mat4(1.0f));
	translate_yellow = new Transform(glm::mat4(1.0f));
	translate_purple = new Transform(glm::mat4(1.0f));
	translate_blue = new Transform(glm::mat4(1.0f));
	translate_green = new Transform(glm::mat4(1.0f));
	translate_white = new Transform(glm::mat4(1.0f));
	translate_orange = new Transform(glm::mat4(1.0f));
	translate_black = new Transform(glm::mat4(1.0f));

	box1 = new boundingSphere(glm::vec3(-9.5, 0.3, 11.0), 3.0);
	box2 = new boundingSphere(glm::vec3(10.5, 0.3, 8.0), 3.0);
	stairs = new boundingPlane(glm::vec3(0.0, 0.3, 4.0), glm::vec3(0, 0, 1));
	leftWall = new boundingPlane(glm::vec3(-16.5, 0.3, 12.0), glm::vec3(1, 0, 0));
	rightWall = new boundingPlane(glm::vec3(16.5, 0.3, 12.0), glm::vec3(-1, 0, 0));
	leftDiagWall = new boundingPlane(glm::vec3(-14.0, 0.3, 19.0), glm::vec3(1, 0, -1));
	rightDiagWall = new boundingPlane(glm::vec3(14.0, 0.3, 19.0), glm::vec3(-1, 0, -1));
	bottomWall = new boundingPlane(glm::vec3(0.0, 0.3, 21.0), glm::vec3(0, 0, -1));

	world->addChild(translate_red);
	world->addChild(translate_pink);
	world->addChild(translate_cyan);
	world->addChild(translate_yellow);
	world->addChild(translate_purple);
	world->addChild(translate_blue);
	world->addChild(translate_green);
	world->addChild(translate_white);
	world->addChild(translate_orange);
	world->addChild(translate_black);

	translate_red->addChild(rotate_red);
	translate_pink->addChild(rotate_pink);
	translate_cyan->addChild(rotate_cyan);
	translate_yellow->addChild(rotate_yellow);
	translate_purple->addChild(rotate_purple);
	translate_blue->addChild(rotate_blue);
	translate_green->addChild(rotate_green);
	translate_white->addChild(rotate_white);
	translate_orange->addChild(rotate_orange);
	translate_black->addChild(rotate_black);

	rotate_red->addChild(red);
	rotate_pink->addChild(pink);
	rotate_cyan->addChild(cyan);
	rotate_yellow->addChild(yellow);
	rotate_purple->addChild(purple);
	rotate_blue->addChild(blue);
	rotate_green->addChild(green);
	rotate_white->addChild(white);
	rotate_orange->addChild(orange);
	rotate_black->addChild(black);

	astroList.push_back(translate_red);
	astroList.push_back(translate_pink);
	astroList.push_back(translate_cyan);
	astroList.push_back(translate_yellow);
	astroList.push_back(translate_purple);
	astroList.push_back(translate_blue);
	astroList.push_back(translate_green);
	astroList.push_back(translate_white);
	astroList.push_back(translate_orange);
	astroList.push_back(translate_black);

	boxes.push_back(box1);
	boxes.push_back(box2);

	planeList.push_back(stairs);
	planeList.push_back(leftWall);
	planeList.push_back(rightWall);
	planeList.push_back(leftDiagWall);
	planeList.push_back(rightDiagWall);
	planeList.push_back(bottomWall);

	return true;
}

void Window::cleanUp()
{
	// Deallocate objects
	delete world;
	delete lobby;

	delete red;
	delete pink;
	delete cyan;
	delete yellow;
	delete purple;
	delete blue;
	delete green;
	delete white;
	delete orange;
	delete black;

	delete rotate_red;
	delete rotate_pink;
	delete rotate_cyan;
	delete rotate_yellow;
	delete rotate_purple;
	delete rotate_blue;
	delete rotate_green;
	delete rotate_white;
	delete rotate_orange;
	delete rotate_black;

	delete translate_red;
	delete translate_pink;
	delete translate_cyan;
	delete translate_yellow;
	delete translate_purple;
	delete translate_blue;
	delete translate_green;
	delete translate_white;
	delete translate_orange;
	delete translate_black;

	delete box1;
	delete box2;
	delete stairs;
	delete leftWall;
	delete rightWall;
	delete leftDiagWall;
	delete rightDiagWall;
	delete bottomWall;

	// Delete shader programs
	glDeleteProgram(shaderProgram);
	glDeleteProgram(lobbyShader);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height); 
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	Window::projection = glm::perspective(glm::radians(60.0), 
								double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
	if (holdMove) {
		rotate_red->update();
	}

	// random appearances/disappearances logic
	int v1 = rand() % 1000;
	if (v1 == 1) {
		if (pinkGone) {
			rotate_pink->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-14.0f, 0.3f, 16.0f)));
			pinkGone = false;
		}
		else {
			rotate_pink->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f, 0.3f, 1000.0f)));
			pinkGone = true;
		}
	}
	if (v1 == 2) {
		if (cyanGone) {
			rotate_cyan->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-13.0f, 0.3f, 7.0f)));
			cyanGone = false;
		}
		else {
			rotate_cyan->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-13.0f, 0.3f, 1000.0f)));
			cyanGone = true;
		}
	}
	if (v1 == 3) {
		if (yellowGone) {
			rotate_yellow->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.3f, 13.0f)));
			yellowGone = false;
		}
		else {
			rotate_yellow->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.3f, 1000.0f)));
			yellowGone = true;
		}
	}
	if (v1 == 4) {
		if (purpleGone) {
			rotate_purple->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.3f, 15.0f)));
			purpleGone = false;
		}
		else {
			rotate_purple->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.3f, 1000.0f)));
			purpleGone = true;
		}
	}
	if (v1 == 5) {
		if (blueGone) {
			rotate_blue->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 12.0f)));
			blueGone = false;
		}
		else {
			rotate_blue->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 1000.0f)));
			blueGone = true;
		}
	}
	if (v1 == 6) {
		if (greenGone) {
			rotate_green->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.3f, 17.0f)));
			greenGone = false;
		}
		else {
			rotate_green->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.3f, 1000.0f)));
			greenGone = true;
		}
	}
	if (v1 == 7) {
		if (whiteGone) {
			rotate_white->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.3f, 10.0f)));
			whiteGone = false;
		}
		else {
			rotate_white->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.3f, 1000.0f)));
			whiteGone = true;
		}
	}
	if (v1 == 8) {
		if (orangeGone) {
			rotate_orange->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 17.0f)));
			orangeGone = false;
		}
		else {
			rotate_orange->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.3f, 1000.0f)));
			orangeGone = true;
		}
	}
	if (v1 == 9) {
		if (blackGone) {
			rotate_black->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.3f, 19.0f)));
			blackGone = false;
		}
		else {
			rotate_black->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.3f, 1000.0f)));
			blackGone = true;
		}
	}

	// move NPCs indefinitely
	rotate_pink->update();
	rotate_cyan->update();
	rotate_yellow->update();
	rotate_purple->update();
	rotate_blue->update();
	rotate_green->update();
	rotate_white->update();
	rotate_orange->update();
	rotate_black->update();

	// resolve astro-astro collisions
	for (int i = 0; i < astroList.size() - 1; i++) {
		for (int j = i + 1; j < astroList.size(); j++) {
			Transform* astro1Rot = (Transform*)astroList[i]->getChildren()[0];
			Geometry* astro1 = (Geometry*)astro1Rot->getChildren()[0];
			Transform* astro2Rot = (Transform*)astroList[j]->getChildren()[0];
			Geometry* astro2 = (Geometry*)astro2Rot->getChildren()[0];
			boundingSphere* astro1Sphere = astro1->getSphere();
			boundingSphere* astro2Sphere = astro2->getSphere();

			if (sphereToSphereCollision(astro1Sphere, astro2Sphere)) {
				// precalculate collision resolution values
				glm::mat4 astro1Inverted = glm::inverse(astro1Rot->getMatrix());
				glm::vec3 astro1Direction = normalize(glm::vec3(astro1Inverted[2]));
				glm::vec3 astro1Norm = astro1Sphere->getCenter() - astro2Sphere->getCenter();
				glm::vec3 astro1ReflectDir = glm::reflect(astro1Direction, astro1Norm);
				float astro1ReflectAngle = acos(glm::dot(astro1Direction, astro1ReflectDir) / (glm::length(astro1Direction) * glm::length(astro1ReflectDir)));
				
				glm::mat4 astro2Inverted = glm::inverse(astro2Rot->getMatrix());
				glm::vec3 astro2Direction = normalize(glm::vec3(astro2Inverted[2]));
				glm::vec3 astro2Norm = astro2Sphere->getCenter() - astro1Sphere->getCenter();
				glm::vec3 astro2ReflectDir = glm::reflect(astro2Direction, astro2Norm);
				float astro2ReflectAngle = acos(glm::dot(astro2Direction, astro2ReflectDir) / (glm::length(astro2Direction) * glm::length(astro2ReflectDir)));

				glm::vec3 travelDir = glm::normalize(astro1Sphere->getCenter() - astro2Sphere->getCenter());
				float travelDist = astro1Sphere->getRadius() + astro2Sphere->getRadius() - glm::length(astro1Sphere->getCenter() - astro2Sphere->getCenter()) + 0.1f;

				if (astro1Rot == rotate_red) {
					astro2Rot->rotate(astro2ReflectAngle, glm::vec3(0, 1, 0));
					if (holdMove) {
						astroList[i]->translate(travelDist * travelDir);
					}
					astroList[j]->translate(-travelDist * travelDir);
				}
				else if (astro2Rot == rotate_red) {
					astro1Rot->rotate(astro1ReflectAngle, glm::vec3(0, 1, 0));
					astroList[i]->translate(-travelDist * travelDir);
					if (holdMove) {
						astroList[j]->translate(travelDist * travelDir);
					}
				}
				else {
					astro1Rot->rotate(astro1ReflectAngle, glm::vec3(0, 1, 0));
					astro2Rot->rotate(astro2ReflectAngle, glm::vec3(0, 1, 0));
					astroList[i]->translate(travelDist * travelDir);
					astroList[j]->translate(-travelDist * travelDir);
				}
			}
		}
	}
	// resolve astro-box collisions
	for (int i = 0; i < astroList.size(); i++) {
		Transform* astroRot = (Transform*)astroList[i]->getChildren()[0];
		Geometry* astro = (Geometry*)astroRot->getChildren()[0];
		boundingSphere* astroSphere = astro->getSphere();

		// check collision against box1
		if (sphereToSphereCollision(astroSphere, boxes[0])) {
			if (astroRot != rotate_red) {
				glm::mat4 inverted = glm::inverse(astroRot->getMatrix());
				glm::vec3 direction = normalize(glm::vec3(inverted[2]));
				glm::vec3 norm = astroSphere->getCenter() - boxes[0]->getCenter();
				glm::vec3 reflectDir = glm::reflect(direction, norm);
				float reflectAngle = acos(glm::dot(direction, reflectDir) / (glm::length(direction) * glm::length(reflectDir)));
				astroRot->rotate(reflectAngle, glm::vec3(0, 1, 0));
			}
			glm::vec3 travelDir = glm::normalize(astroSphere->getCenter() - boxes[0]->getCenter());
			float travelDist = boxes[0]->getRadius() + astroSphere->getRadius() - glm::length(boxes[0]->getCenter() - astroSphere->getCenter()) + 0.1f;
			astroList[i]->translate(travelDist * travelDir);
		}
		//// check collision against box2
		if (sphereToSphereCollision(astroSphere, boxes[1])) {
			if (astroRot != rotate_red) {
				glm::mat4 inverted = glm::inverse(astroRot->getMatrix());
				glm::vec3 direction = normalize(glm::vec3(inverted[2]));
				glm::vec3 norm = astroSphere->getCenter() - boxes[1]->getCenter();
				glm::vec3 reflectDir = glm::reflect(direction, norm);
				float reflectAngle = acos(glm::dot(direction, reflectDir) / (glm::length(direction) * glm::length(reflectDir)));
				astroRot->rotate(reflectAngle, glm::vec3(0, 1, 0));
			}
			glm::vec3 travelDir = glm::normalize(astroSphere->getCenter() - boxes[1]->getCenter());
			float travelDist = boxes[1]->getRadius() + astroSphere->getRadius() - glm::length(boxes[1]->getCenter() - astroSphere->getCenter()) + 0.1f;
			astroList[i]->translate(travelDist * travelDir);
		}
	}
	// resolve sphere-wall collisions
	for (int i = 0; i < astroList.size(); i++) {
		for (int j = 0; j < planeList.size(); j++) {
			Transform* astroRot = (Transform*)astroList[i]->getChildren()[0];
			Geometry* astro = (Geometry*)astroRot->getChildren()[0];
			boundingSphere* astroSphere = astro->getSphere();

			if (sphereToPlaneCollision(astroSphere, planeList[j])) {
				if (astroRot != rotate_red) {
					glm::mat4 inverted = glm::inverse(astroRot->getMatrix());
					glm::vec3 direction = normalize(glm::vec3(inverted[2]));
					glm::vec3 planeNorm = planeList[j]->getNormal();
					glm::vec3 reflectDir = glm::reflect(direction, planeNorm);
					float reflectAngle = acos(glm::dot(direction, reflectDir) / (glm::length(direction) * glm::length(reflectDir)));
					astroRot->rotate(reflectAngle, glm::vec3(0, 1, 0));
				}

				float dist = glm::dot(astroSphere->getCenter(), planeList[j]->getNormal()) - glm::dot(planeList[j]->getOrigin(), planeList[j]->getNormal());
				float travLength = astroSphere->getRadius() - dist + 0.1f;
				astroList[i]->translate(travLength * planeList[j]->getNormal());
			}
		}
	}
}

void Window::displayCallback(GLFWwindow* window)
{	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// pass in eyePos to shader
	glUseProgram(shaderProgram);
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(eyePos));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, false, glm::value_ptr(projection));
	glUseProgram(0);
	// same for lobby shader
	glUseProgram(lobbyShader);
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(eyePos));
	glUniformMatrix4fv(glGetUniformLocation(lobbyShader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(lobbyShader, "projection"), 1, false, glm::value_ptr(projection));
	glUseProgram(0);

	// Draw scene graph
	//world->draw(shaderProgram, projection * view);
	world->draw(shaderProgram, glm::mat4(1.0f));
	lobby->draw(lobbyShader, glm::mat4(1.0f));

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers.
	glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;

		case GLFW_KEY_W:
			if (lastDir == "w") {
				holdMove = 1;
				lastDir = "w";
			}
			else if (lastDir == "a") {
				rotate_red->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "w";
			}
			else if (lastDir == "s") {
				rotate_red->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "w";
			}
			else {
				rotate_red->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "w";
			}
			break;
		case GLFW_KEY_A:
			if (lastDir == "w") {
				rotate_red->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "a";
			}
			else if (lastDir == "a") {
				holdMove = 1;
				lastDir = "a";
			}
			else if (lastDir == "s") {
				rotate_red->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "a";
			}
			else {
				rotate_red->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "a";
			}
			break;
		case GLFW_KEY_S:
			if (lastDir == "w") {
				rotate_red->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "s";
			}
			else if (lastDir == "a") {
				rotate_red->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "s";
			}
			else if (lastDir == "s") {
				holdMove = 1;
				lastDir = "s";
			}
			else {
				rotate_red->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "s";
			}
			break;
		case GLFW_KEY_D:
			if (lastDir == "w") {
				rotate_red->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "d";
			}
			else if (lastDir == "a") {
				rotate_red->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "d";
			}
			else if (lastDir == "s") {
				rotate_red->rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
				holdMove = 1;
				lastDir = "d";
			}
			else {
				holdMove = 1;
				lastDir = "d";
			}
			break;

		default:
			break;
		}
	}

	if (action == GLFW_RELEASE) {
		holdMove = 0;
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	float xmove = eyePos.x / 5;
	float ymove = eyePos.y / 5;
	float zmove = eyePos.z / 5;

	float dist = sqrt((eyePos.x * eyePos.x) + (eyePos.y * eyePos.y) + (eyePos.z * eyePos.z));

	// scroll up = move away from origin
	if (yoffset > 0) {
		if (dist > 8.0f) {
			eyePos.x -= xmove;
			eyePos.y -= ymove;
			eyePos.z -= zmove;
		}
	}
	// scroll down = move to origin
	else {
		eyePos.x += xmove;
		eyePos.y += ymove;
		eyePos.z += zmove;
	}

	// update view
	view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
}

// when mouse button held down, allow object rotation on cursor move
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouseDown = true;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		lastMousePoint = trackball(glm::vec2(xpos, ypos));
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseDown = false;
	}
}

// performs rotation based on cursor movement
void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	double pos_x = xpos;
	double pos_y = ypos;
	glm::vec2 mouseCoord;
	mouseCoord.x = pos_x;
	mouseCoord.y = pos_y;

	glm::vec3 currPoint = trackball(mouseCoord);
	if (mouseDown) {
		glm::vec3 direction = currPoint - lastMousePoint;
		float velocity = glm::length(direction);
		if (velocity > 0.0001) {
			glm::vec3 rotAxis = glm::cross(lastMousePoint, currPoint);
			float rot_angle = velocity * 1.5f;
			
			// rotate eyePos on y axis
			if (rotAxis.y > 0) {
				glm::vec4 rotatedEyePos = glm::rotate(glm::mat4(1.0), rot_angle, glm::vec3(0, -1, 0)) * glm::vec4(eyePos, 1.0f);
				eyePos = glm::vec3(rotatedEyePos);
			}
			else {
				glm::vec4 rotatedEyePos = glm::rotate(glm::mat4(1.0), rot_angle, glm::vec3(0, 1, 0)) * glm::vec4(eyePos, 1.0f);
				eyePos = glm::vec3(rotatedEyePos);
			}
			// recalculate view matrix
			view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

			lastMousePoint = currPoint;
		}
	}
}

// map 2d point on screen to 3d point on object
glm::vec3 Window::trackball(glm::vec2 mouseCoord) {
	glm::vec3 v;
	float d;
	v.x = (2.0 * mouseCoord.x - width) / width;
	v.y = (height - 2.0 * mouseCoord.y) / height;
	v.z = 0.0;
	d = glm::length(v);
	d = (d < 1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d * d);
	v = glm::normalize(v);
	return v;
}

bool Window::sphereToSphereCollision(boundingSphere* sphere1, boundingSphere* sphere2) {
	glm::vec3 sphere1Center = sphere1->getCenter();
	glm::vec3 sphere2Center = sphere2->getCenter();
	float sphere1Radius = sphere1->getRadius();
	float sphere2Radius = sphere2->getRadius();
	float dist = sqrt((sphere1Center.x - sphere2Center.x) * (sphere1Center.x - sphere2Center.x) + (sphere1Center.z - sphere2Center.z) * (sphere1Center.z - sphere2Center.z));
	if (dist < (sphere1Radius + sphere2Radius)) {
		return true;
	}
	return false;
}

bool Window::sphereToPlaneCollision(boundingSphere* sphere, boundingPlane* plane) {
	float dist = glm::dot(sphere->getCenter(), plane->getNormal()) - glm::dot(plane->getOrigin(), plane->getNormal());
	if (abs(dist) <= sphere->getRadius()) {
		return true;
	}
	return false;
}