#ifndef _BDENGINE_TEXTURE2D_H
#define _BDENGINE_TEXTURE2D_H

#include <GL/glew.h>

#include "Image.h"

namespace bdEngine {

class Texture2D {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	/*!
	 * Default constructor. Doesn't actually do anything, getTextureID()
	 * will return 0.
	 */
	Texture2D() {}
	
	/*!
	 * Creates texture from an Image object.
	 */
	Texture2D(Image& srcImage);
	
	/*!
	 * Releases texture resources.
	 */
	~Texture2D();
	
	// --- Forbid copy operations
	Texture2D(const Texture2D& other)            = delete;  // copy constructor
	Texture2D& operator=(const Texture2D& other) = delete;  // copy assignment
	
	// --- Override move operations
	Texture2D(Texture2D&& other);             // move constructor
	Texture2D& operator=(Texture2D&& other);  // move assignment
	
	
	/*******************************************************************
	 * Properties
	 *******************************************************************/
	/*!
	 * Returns the texture object ID to be used by the GL functions.
	 */
	GLuint getTextureID() const {
		return textureID;
	}
	
private:
	// GL texture object ID
	GLuint textureID;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_TEXTURE2D_H */
