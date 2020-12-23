#include "boundingPlane.h"

boundingPlane::boundingPlane(glm::vec3 origin, glm::vec3 normal)
	: origin(origin), normal(normal) {}

boundingPlane::~boundingPlane() {};

glm::vec3 boundingPlane::getOrigin() {
	return origin;
}
glm::vec3 boundingPlane::getNormal() {
	return normal;
}