#include "RenderWindow.h"

#include <functional>

using namespace std::placeholders;

// TODO implement own logging class
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

RenderWindow::RenderWindow()
{
	// Initialize GLFW
	GLFW::initLib();
	
	// Set GLFW window hints
	// -> require OpenGL 3.3 and use core profile
	GLFW::setWindowHint(GLFW::WindowHint::ContextVersionMajor, 3);
	GLFW::setWindowHint(GLFW::WindowHint::ContextVersionMinor, 3);
	GLFW::setWindowHint(GLFW::WindowHint::OpenGLProfile, GLFW::OpenGLProfile::Core);
	
	// Create GLFW::Window instance (which will actually create and open the window)
	window_ = std::make_unique<GLFW::Window>(800, 600, "bdEngine test application");
	
	// Make context current
	GLFW::makeContextCurrent(*window_);
	
	// Initialize GLEW to load GL extensions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW.");
	}
	
	// Set swap interval to >0 to avoid screen tearing
	GLFW::setSwapInterval(1);
	
	// Set event callbacks
	window_->setKeyCallback(std::bind(&RenderWindow::_test_key_callback, this, _1, _2, _3, _4, _5));
	
	// Create Renderer instance
	renderer_ = std::make_unique<Renderer>();
	
	// Get framebuffer size and apply to renderer
	GLFW::Size2D fbSize = window_->getFramebufferSize();
	renderer_->setWindowSize(fbSize.width, fbSize.height);
	
	// Set callback for window resize event
	window_->setWindowSizeCallback(std::bind(&Renderer::setWindowSize, renderer_.get(), _2, _3));
}

RenderWindow::~RenderWindow() {
	// Nothing to do, let GLFW::Window::~Window() do all the work.
}


/*******************************************************************
 * Context and main loop
 *******************************************************************/

/*! Signal render window to stop the main loop in order to close the window. */
void RenderWindow::stop() {
	window_->setShouldClose(true);
}

/*! Draw one single frame, calling the Renderer and swapping buffers. */
void RenderWindow::drawFrame() {
	// Call Renderer to render frame
	renderer_->drawFrame();
	
	// Swap buffers
	window_->swapBuffers();
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
	
	if (action == GLFW::InputAction::Press) {
		switch (key) {
		case GLFW::KeyCode::Escape:
		case GLFW::KeyCode::Q:
			window.setShouldClose(true);
			break;
			
		case GLFW::KeyCode::F:
			cout << "Wireframe mode: "
			     << (renderer_->toggleWireframeMode() ? "on" : "off")
			     << endl;
			break;
			
		default:
			cout << "Unbound key pressed: ";
			if (keyname == nullptr) {
				cout << scancode << endl;
			}
			else {
				cout << "'" << keyname << "'" << endl;
			}
			break;
		}
	}
}


} // end namespace bdEngine
