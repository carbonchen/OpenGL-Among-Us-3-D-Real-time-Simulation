#ifndef _BOUNDINGSPHERE_H_
#define _BOUNDINGSPHERE_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

using namespace std;

class boundingSphere {
private:
	glm::vec3 center;
	float radius;
public:
	boundingSphere(glm::vec3 center, float radius);
	~boundingSphere();

	void setCenter(glm::vec3 center);

	glm::vec3 getCenter();
	float getRadius();
};

#endif