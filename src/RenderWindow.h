#ifndef _BDENGINE_RENDERWINDOW_H
#define _BDENGINE_RENDERWINDOW_H

// GLEW has to be included *before* GLFW or any other OpenGL header.
#include <GL/glew.h>
#include "GLFWpp.h"

#include "Renderer.h"

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
	 * Returns true until window is supposed to close, that is, until stop()
	 * is called.
	 */
	bool keepRunning() const {
		return !window_->shouldClose();
	}
	
	/*!
	 * Signal render window to stop the main loop in order to close the window.
	 * After this, keepRunning() will return false.
	 */
	void stop();
	
	/*!
	 * Draws one single frame. This will prepare drawing, call the Renderer
	 * and finish drawing by swapping buffers.
	 */
	void drawFrame();
	
	/*!
	 * Poll and handle events.
	 */
	void handleEvents();
	
	
	/*******************************************************************
	 * Properties
	 *******************************************************************/
	
	
	/*******************************************************************
	 * XXX Test functions
	 *******************************************************************/
	void _test_key_callback(GLFW::Window& window, GLFW::KeyCode key, int scancode,
		GLFW::InputAction action, GLFW::KeyModifier mods);

private:
	/*! The actual window instance. */
	std::unique_ptr<GLFW::Window> window_;
	
	/*! Renderer instance. This is the actual graphics driver. */
	std::unique_ptr<Renderer> renderer_;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERWINDOW_H */
