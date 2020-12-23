#include "boundingSphere.h"

boundingSphere::boundingSphere(glm::vec3 center, float radius) 
	: center(center), radius(radius) {
}

boundingSphere::~boundingSphere() {};

void boundingSphere::setCenter(glm::vec3 center) {
	this->center = center;
}

glm::vec3 boundingSphere::getCenter() {
	return center;
}
float boundingSphere::getRadius() {
	return radius;
}