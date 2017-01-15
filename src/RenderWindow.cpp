#include "RenderWindow.h"

#include <iostream>
// #include "Renderer.h"  // XXX

using namespace std::placeholders;

// XXX
using std::cout;
using std::cerr;
using std::endl;

namespace bdEngine {


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

RenderWindow::RenderWindow()
	: window_ {640, 480, "bdEngine test application"}  // XXX Arguments!
{
	// XXX exceptions
	
	// Initialize GLFW library (immediately returns true if already initialized) XXX
	// GLFW::initLib();
	
	// XXX Error handling!
	// void error_callback(int error, const char* description) {
	//	 fprintf(stderr, "Error: %s\n", description);
	// }
	// glfwSetErrorCallback(error_callback);
	
	// Set event callbacks
	window_.setKeyCallback(std::bind(&RenderWindow::_test_key_callback, this, _1, _2, _3, _4, _5));
}

RenderWindow::~RenderWindow() {
	// XXX nothing to do, let GLFW::Window::~Window() do all the work
}


/*******************************************************************
 * Context and main loop
 *******************************************************************/
// TODO


/*******************************************************************
 * XXX Test functions
 *******************************************************************/

void RenderWindow::_test_run() {
	// Switch to context
	GLFW::makeContextCurrent(window_);
	
	// XXX load extension loader library?
	// gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
	// Set swap interval to >0 to avoid screen tearing
	GLFW::setSwapInterval(1);
	
	// XXX -> Engine
	//Renderer renderer {};
	
	// Main loop: exit when window is closed
	while (!window_.shouldClose()) {
		// Get framebuffer size
		GLFW::Size2D fbSize = window_.getFramebufferSize();
		//double ratio = fbSize.width / (double) fbSize.height; // XXX
		
		glViewport(0, 0, fbSize.width, fbSize.height);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// TODO DO THE RENDERY THING
		
		// XXX
		//renderer.drawFrame(*this, fbSize.width, fbSize.height);
		
		window_.swapBuffers();
		GLFW::pollEvents();
	}
}

void RenderWindow::_test_key_callback(GLFW::Window& window, GLFW::KeyCode key, int scancode,
	GLFW::InputAction action, GLFW::KeyModifier mods)
{
	const char* keyname = GLFW::getKeyName(key, scancode);
	
	if (keyname == nullptr) {
		cout << "Key callback: " << scancode;
	}
	else {
		cout << "Key callback: '" << keyname << "'";
	}
	
	cout << " "
		 << (action == GLFW::InputAction::Press ? "pressed"
			: action == GLFW::InputAction::Release ? "released"
			: action == GLFW::InputAction::Repeat ? "repeated" : "")
		<< std::endl;
	
	if (key == GLFW::KeyCode::Escape && action == GLFW::InputAction::Press) {
		window.setShouldClose(true);
	}
}


} // end namespace bdEngine
