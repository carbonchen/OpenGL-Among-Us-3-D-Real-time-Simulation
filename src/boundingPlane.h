#ifndef _BOUNDINGPLANE_H_
#define _BOUNDINGPLANE_H_

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

class boundingPlane {
private:
	glm::vec3 origin;
	glm::vec3 normal;
public:
	boundingPlane(glm::vec3 origin, glm::vec3 normal);
	~boundingPlane();

	glm::vec3 getOrigin();
	glm::vec3 getNormal();
};

#endif