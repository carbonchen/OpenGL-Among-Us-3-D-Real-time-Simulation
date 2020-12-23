#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Node.h"
#include "boundingSphere.h"
#include <vector>
#include <string>

#include "stb_image.h"

using namespace std;

class Geometry : public Node
{
private:
	glm::mat4 model;

	std::vector<glm::vec3> points;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::ivec3> faces;

	std::string name;

	boundingSphere* sphere;

	GLuint VAO, VBO, VBO2, VBO3;

	unsigned int texture;

public:
	Geometry(std::string objFilename, std::string name);
	~Geometry();
	
	void draw(GLuint shaderProgram, glm::mat4 C);
	void update();

	void parseObj(std::string objFilename);

	boundingSphere* getSphere();
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
};

#endif
