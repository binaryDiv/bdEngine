#ifndef _BDENGINE_IMAGE_H
#define _BDENGINE_IMAGE_H

namespace bdEngine {

class Image {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	/*!
	 * Default constructor. Doesn't load anything, getData() will return nullptr.
	 */
	Image() {}
	
	/*!
	 * Loads image from file.
	 */
	Image(const char* filename);
	
	/*!
	 * Releases image resources.
	 */
	~Image();
	
	// --- Forbid copy operations
	Image(const Image& other)            = delete;  // copy constructor
	Image& operator=(const Image& other) = delete;  // copy assignment
	
	// --- Override move operations
	Image(Image&& other);             // move constructor
	Image& operator=(Image&& other);  // move assignment
	
	
	/*******************************************************************
	 * Properties
	 *******************************************************************/
	/*!
	 * Returns the pointer to the image data.
	 * This data is only available as long as this object exists!
	 */
	unsigned char* getData() const {
		return imageData;
	}

	/*!
	 * Returns image width.
	 */
	int getWidth() const {
		return width;
	}
	
	/*!
	 * Returns image height.
	 */
	int getHeight() const {
		return height;
	}
	
private:
	// Image pixel data
	unsigned char* imageData = nullptr;
	
	// Image size
	int width = 0;
	int height = 0;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_IMAGE_H */
