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
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

void main() {
	gl_Position = vec4(position.xyz, 1.0);
	fragColor = color;
	// Flip texture coordinates vertically because otherwise textures are upside down.
	fragTexCoord = vec2(texCoord.x, 1 - texCoord.y);
}

)__SRC__";

// Fragment shader source code
const GLchar* fragShaderSrc = R"__SRC__(
#version 330 core

in vec3 fragColor;
in vec2 fragTexCoord;
out vec4 color;

uniform sampler2D texSampler1;
uniform sampler2D texSampler2;

void main() {
	//color = vec4(0.9, 0.2, 0.6, 1);
	color = mix(texture(texSampler1, fragTexCoord), texture(texSampler2, fragTexCoord), 0.5);
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
		// Positions xyz     // Colors rgb      // Texture coords
		 0.7f,  0.7f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // 0: top right
		 0.7f, -0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // 1: bottom right
		-0.7f, -0.7f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // 2: bottom left
		-0.7f,  0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 3: top left
	};
	
	GLuint indices[] = {
		0, 1, 3,  // first triangle
		1, 2, 3,  // second triangle
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// -> location 1: color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// -> location 2: texCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	// Unbind VAO
	glBindVertexArray(0);
	
	
	// -- Load/create textures
	// TODO Error handling with exceptions
	
	// Load image data and create example texture 1
	// Image img {"res/textures/bg_honk.png"};
	Image img {"res/textures/bg_clouds.png"};
	exTexture1 = Texture2D {img};
	
	// Load image data and create example texture 2
	// img = Image {"res/textures/gamzee.png"};
	img = Image {"res/textures/john.png"};
	exTexture2 = Texture2D {img};
	
	
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
	
	// Activate shader
	shaderProgram.useProgram();
	
	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, exTexture1.getTextureID());
	glUniform1i(shaderProgram.getUniformLocation("texSampler1"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, exTexture2.getTextureID());
	glUniform1i(shaderProgram.getUniformLocation("texSampler2"), 1);
	
	// Draw example object
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
