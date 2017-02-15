#include "Image.h"

#include <stdexcept>
#include <SOIL/SOIL.h>

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Constructor
Image::Image(const char* filename) {
	// Load image data, retrieve width and height
	imageData = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	
	// Check for errors
	if (imageData == nullptr) {
		// TODO Custom exception types
		throw std::runtime_error( "SOIL loading error for file '" + std::string(filename) + "': "
			+ std::string(SOIL_last_result()) );
	}
}

// Destructor
Image::~Image() {
	if (imageData != nullptr) {
		// Free image resources
		SOIL_free_image_data(imageData);
	}
}

// Move constructor
Image::Image(Image&& other) {
	// Copy image data and other attributes from other object
	imageData = other.imageData;
	width = other.width;
	height = other.height;
	
	// Reset other object so that the destructor doesn't destroy the (moved) image data.
	other.imageData = nullptr;
}

// Move assignment
Image& Image::operator=(Image&& other) {
	if (this != &other) {
		// First, destroy the current object by freeing image resources.
		SOIL_free_image_data(imageData);
		
		// Now, copy data from source object.
		imageData = other.imageData;
		width = other.width;
		height = other.height;
		
		// Reset other object so that the destructor doesn't destroy the (moved) image data.
		other.imageData = nullptr;
	}
	
	return *this;
}


} // end namespace bdEngine
