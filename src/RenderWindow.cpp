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
	// Get framebuffer size
	fbSize_ = window_.getFramebufferSize();
	
	// XXX Set event callbacks
	window_.setKeyCallback(std::bind(&RenderWindow::_test_key_callback, this, _1, _2, _3, _4, _5));
}

RenderWindow::~RenderWindow() {
	// Nothing to do, let GLFW::Window::~Window() do all the work.
}


/*******************************************************************
 * Context and main loop
 *******************************************************************/

/*! Makes window context current and prepares rendering. */
void RenderWindow::activateContext() {
	// Switch to context
	GLFW::makeContextCurrent(window_);
	
	// XXX load extension loader library?
	// gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
	// Set swap interval to >0 to avoid screen tearing
	GLFW::setSwapInterval(1);
	
	// Now the context can be used.
}

/*! Returns true until window is supposed to close. */
bool RenderWindow::keepRunning() {
	return !window_.shouldClose();
}

/*! Signal render window to stop the main loop in order to close the window. */
void RenderWindow::stop() {
	window_.setShouldClose(true);
}

/*! Prepare rendering of one frame. */
void RenderWindow::beginFrame() {
	// Update framebuffer size
	fbSize_ = window_.getFramebufferSize();
}

/*! End rendering of one frame. This will swap buffers.*/
void RenderWindow::endFrame() {
	// Swap buffers.
	window_.swapBuffers();
}

/*! Poll and handle events. */
void RenderWindow::handleEvents() {
	// TODO Do the input thing (do we need to do more than pollEvents()?)
	GLFW::pollEvents();
}


/*******************************************************************
 * XXX Test functions
 *******************************************************************/

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
