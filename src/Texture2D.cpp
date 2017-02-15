#include "Texture2D.h"

#include <stdexcept>

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Constructor
Texture2D::Texture2D(Image& srcImage) {
	// Generate and bind GL texture object
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Set alignment to fix glitches for images with row sizes that are not multiples of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// Generate texture image and mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, srcImage.getWidth(), srcImage.getHeight(), 0,
		GL_RGB, GL_UNSIGNED_BYTE, srcImage.getData());
	glGenerateMipmap(GL_TEXTURE_2D);
	
	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Destructor
Texture2D::~Texture2D() {
	if (textureID != 0) {
		// Delete texture object in GPU
		glDeleteTextures(1, &textureID);
	}
}

// Move constructor
Texture2D::Texture2D(Texture2D&& other) {
	// Copy texture ID from other object so the new object owns the resource
	textureID = other.textureID;
	
	// Reset other object so that the destructor delete the texture object
	other.textureID = 0;
}

// Move assignment
Texture2D& Texture2D::operator=(Texture2D&& other) {
	if (this != &other) {
		// First, destroy the current object by deleting its texture object
		glDeleteTextures(1, &textureID);
	
		// Now, copy data from source object
		textureID = other.textureID;
		
		// Reset other object so that the destructor delete the texture object
		other.textureID = 0;
	}
	
	return *this;
}


} // end namespace bdEngine
