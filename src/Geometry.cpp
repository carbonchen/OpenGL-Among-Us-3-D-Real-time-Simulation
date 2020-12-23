#include "Geometry.h"
#include <iostream>
#include <sstream>
#include <fstream>

Geometry::Geometry(std::string objFilename, std::string name)
	: name(name)
{
	// try special parser
	parseObj(objFilename);

	// Set the model matrix to an identity matrix. 
	model = glm::mat4(1);

	// initialize bounding sphere
	sphere = new boundingSphere(glm::vec3(1), 1.0f);

	// Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO to the bound VAO, and store the point data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	// Enable Vertex Attribute 0 to pass point data through to the shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Send normals info
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Send texture info and generate texture
	if (name == "lobby") {
		// generating lobby texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("./lobby/amongus_lobby.png", &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		// apply texture
		glGenBuffers(1, &VBO3);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoords.size(), texCoords.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

		this->texture = texture;
	}

	// Unbind the VBO/VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Geometry::~Geometry() 
{
	// Delete the VBO and the VAO.
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &VBO3);
	glDeleteVertexArrays(1, &VAO);
	delete sphere;
}


void Geometry::parseObj(std::string objFilename) {

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::ifstream objFile(objFilename);
	// Check whether the file can be opened.
	if (objFile.is_open())
	{
		std::string line; // A line in the file.

		// Read lines from the file.
		while (std::getline(objFile, line))
		{
			// replace all "/" with " " for easy parsing of cylinder
			auto idx = line.find("/");
			while (idx != std::string::npos) {
				line.replace(idx, 1, " ");
				idx = line.find("/");
			}

			// Turn the line into a string stream for processing.
			std::stringstream ss;
			ss << line;

			// Read the first word of the line.
			std::string label;
			ss >> label;

			// If the line is about vertex (starting with a "v").
			if (label == "v") {
				// Read the three float numbers and use them as coordinates.
				glm::vec3 point;
				ss >> point.x >> point.y >> point.z;
				temp_vertices.push_back(point);
			}

			// store texture coordinates
			if (label == "vt") {
				glm::vec2 uv;
				ss >> uv.x >> uv.y;
				temp_uvs.push_back(uv);
			}

			// store normal vertices
			if (label == "vn") {
				glm::vec3 normal;
				ss >> normal.x >> normal.y >> normal.z;
				temp_normals.push_back(normal);
			}

			// store face vertices
			if (label == "f") {
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				ss >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		// reorder vertices
		for (int i = 0; i < vertexIndices.size(); i++) {
			int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			points.push_back(vertex);

			int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			texCoords.push_back(uv);

			int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			normals.push_back(normal);
		}
	}
	else
	{
		std::cerr << "Can't open the file " << objFilename << std::endl;
	}

	objFile.close();
}

void Geometry::draw(GLuint shaderProgram, glm::mat4 C)
{
	
	// Activate shader program 
	glUseProgram(shaderProgram);

	// set model to parent transform matrix's model
	model = C;

	// update bounding sphere
	sphere->setCenter(glm::vec3(model[3][0], model[3][1], model[3][2]));

	// Get the shader variable locations and send uniform data to shader 
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

	if (name == "red"){
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(197, 18, 17))));
	}
	else if (name == "pink") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(236, 84, 187))));
	}
	else if (name == "cyan") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(57, 254, 221))));
	}
	else if (name == "yellow") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(246, 246, 87))));
	}
	else if (name == "purple") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(108, 47, 188))));
	}
	else if (name == "blue") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(19, 46, 209))));
	}
	else if (name == "green") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(19, 128, 44))));
	}
	else if (name == "white") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(214, 223, 241))));
	}
	else if (name == "orange") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(241, 125, 12))));
	}
	else if (name == "black") {
		glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(glm::normalize(glm::vec3(62, 71, 78))));
	}

	// Bind the VAO
	glBindVertexArray(VAO);

	// Bind texture
	if (name == "lobby") {
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// draw
	glDrawArrays(GL_TRIANGLES, 0, points.size());
	
	// Unbind the VAO and shader program
	glBindVertexArray(0);
	glUseProgram(0);
}

void Geometry::update()
{
}

boundingSphere* Geometry::getSphere() {
	return sphere;
}
glm::mat4 Geometry::getModel() {
	return model;
}
void Geometry::setModel(glm::mat4 model) {
	this->model = model;
}