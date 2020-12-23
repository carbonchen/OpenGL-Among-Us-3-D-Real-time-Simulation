#include "Transform.h"
#include "iostream"

Transform::Transform(glm::mat4 M) {
	transformMat = M;
}

Transform::~Transform() {
}

void Transform::draw(GLuint shaderProgram, glm::mat4 C) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(shaderProgram, C * transformMat);
	}
}

void Transform::update() {
	//transformMat = glm::rotate(transformMat, glm::radians(-0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
	transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, 0.05f));

	//cout << transformMat[0][0] << " " << transformMat[0][1] << " " << transformMat[0][2] << " " << transformMat[0][3] << "\n";
	//cout << transformMat[1][0] << " " << transformMat[1][1] << " " << transformMat[1][2] << " " << transformMat[1][3] << "\n";
	//cout << transformMat[2][0] << " " << transformMat[2][1] << " " << transformMat[2][2] << " " << transformMat[2][3] << "\n";
	//cout << transformMat[3][0] << " " << transformMat[3][1] << " " << transformMat[3][2] << "\n";
}
void Transform::stepBack() {
	transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, -0.1f));
}
void Transform::stepBackAmount(float dist) {
	transformMat = glm::translate(transformMat, glm::vec3(0.0f, 0.0f, -dist));
}

void Transform::addChild(Node* child) {
	children.push_back(child);
}

void Transform::rotate(float rot_angle, glm::vec3 rotAxis) {
	transformMat = glm::rotate(transformMat, rot_angle, rotAxis);
}

void Transform::translate(glm::vec3 transVec) {
	transformMat = glm::translate(transformMat, transVec);
}

std::vector<Node*> Transform::getChildren() {
	return children;
}

glm::mat4 Transform::getMatrix() {
	return transformMat;
}
void Transform::setMatrix(glm::mat4 mat) {
	this->transformMat = mat;
}