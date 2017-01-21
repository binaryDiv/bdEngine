#ifndef _BDENGINE_RENDERWINDOW_H
#define _BDENGINE_RENDERWINDOW_H

// #include <glad/glad.h> // XXX?
#include "GLFWpp.h"

namespace bdEngine {

class RenderWindow {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	RenderWindow();
	~RenderWindow();
	
	
	/*******************************************************************
	 * Context and main loop
	 *******************************************************************/
	
	/*!
	 * Makes window context current and prepares rendering.
	 * (This function needs to be called once before any rendering is done.)
	 */
	void activateContext();
	
	/*!
	 * Returns true until window is supposed to close, that is, until stop()
	 * is called.
	 */
	bool keepRunning();
	
	/*!
	 * Signal render window to stop the main loop in order to close the window.
	 * After this, keepRunning() will return false.
	 */
	void stop();
	
	/*!
	 * Prepare rendering of one frame. End frame with endFrame().
	 */
	void beginFrame();
	
	/*!
	 * End rendering of one frame. This will swap buffers.
	 */
	void endFrame();
	
	/*!
	 * Poll and handle events.
	 */
	void handleEvents();
	
	
	/*******************************************************************
	 * Properties
	 *******************************************************************/
	
	/*!
	 * Returns width of framebuffer. Value is updated in every beginFrame().
	 */
	inline int getFramebufferWidth() {
		return fbSize_.width;
	}
	
	/*!
	 * Returns height of framebuffer. Value is updated in every beginFrame().
	 */
	inline int getFramebufferHeight() {
		return fbSize_.height;
	}
	
	
	/*******************************************************************
	 * XXX Test functions
	 *******************************************************************/
	void _test_key_callback(GLFW::Window& window, GLFW::KeyCode key, int scancode,
		GLFW::InputAction action, GLFW::KeyModifier mods);

private:
	/*! The actual window instance. */
	GLFW::Window window_;
	
	/*! Current frame buffer size (updated in every beginFrame()). */
	GLFW::Size2D fbSize_;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERWINDOW_H */
