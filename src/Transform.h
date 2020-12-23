#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Node.h"
#include <vector>
#include <string>

using namespace std;

class Transform : public Node {
private:
	glm::mat4 transformMat;
	std::vector<Node*> children;

public:
	Transform(glm::mat4 M);
	~Transform();

	void draw(GLuint shaderProgram, glm::mat4 C);
	void update();
	void addChild(Node* child); 

	void rotate(float rot_angle, glm::vec3 rotAxis);
	void translate(glm::vec3 transVec);

	std::vector<Node*> getChildren();
	void stepBack();
	void stepBackAmount(float dist);

	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 mat);
};

#endif