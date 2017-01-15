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
	// TODO
	
	
	/*******************************************************************
	 * XXX Test functions
	 *******************************************************************/
	void _test_run();
	void _test_key_callback(GLFW::Window& window, GLFW::KeyCode key, int scancode,
		GLFW::InputAction action, GLFW::KeyModifier mods);

private:
	GLFW::Window window_;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERWINDOW_H */
