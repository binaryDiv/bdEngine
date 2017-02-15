#include "Renderer.h"

namespace bdEngine {

/*******************************************************************
 * Constants, shader sources
 *******************************************************************/

// Vertex shader source code
const GLchar* vertexShaderSrc = R"__SRC__(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

void main() {
	gl_Position = vec4(position.xyz, 1.0);
	fragColor = color;
}

)__SRC__";

// Fragment shader source code
const GLchar* fragShaderSrc = R"__SRC__(
#version 330 core

in vec3 fragColor;
out vec4 color;

void main() {
	//color = vec4(0.9, 0.2, 0.6, 1);
	color = vec4(fragColor, 1.0);
}

)__SRC__";


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
Renderer::Renderer()
{
	// -- Compile and link shader program
	shaderProgram.addShader(&vertexShaderSrc, GL_VERTEX_SHADER);
	shaderProgram.addShader(&fragShaderSrc, GL_FRAGMENT_SHADER);
	shaderProgram.linkShaders();
	// shaderProgram.useProgram();
	// TODO delete shaders after linking?
	
	// -- Define some objects to render
	
	// Example object
	GLfloat vertices[] = {
		// Positions xyz     // Colors rgb
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // 0: top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // 1: bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // 2: bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // 3: top left
	};
	
	GLuint indices[] = {
		0, 1, 2,  // first triangle
		2, 3, 0,  // second triangle
	};
	
	// Generate Vertex Array Object and Vertex Buffer Object
	glGenVertexArrays(1, &exVAO);
	glGenBuffers(1, &exVBO);
	glGenBuffers(1, &exEBO);
	
	// Bind VAO
	glBindVertexArray(exVAO);
	
	// Bind VBO and copy vertices to buffer
	glBindBuffer(GL_ARRAY_BUFFER, exVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Bind EBO and copy indices to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, exEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Set vertex attributes pointers:
	// -> location 0: position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// -> location 1: color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Unbind VAO
	glBindVertexArray(0);
	
	
	// -- Set up some OpenGL settings
	
	// Set background color to black
	// glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Set wireframe mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::~Renderer() {
}


/*******************************************************************
 * Drawing / Rendering
 *******************************************************************/

void Renderer::setWindowSize(const int width, const int height) {
	// Set viewport
	glViewport(0, 0, width, height);
}

void Renderer::drawFrame() {
	// Clear frame and depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); XXX
	
	// Draw example object
	shaderProgram.useProgram();
	glBindVertexArray(exVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	// RenderProgram will swap buffers now
}

bool Renderer::toggleWireframeMode() {
	wireframeMode = !wireframeMode;
	glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
	return wireframeMode;
}

} // end namespace bdEngine
