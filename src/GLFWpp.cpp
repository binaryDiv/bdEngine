/*************************************************************************
 * C++ wrapper for GLFW3
 * (Documentation mostly stolen from official GLFW documentation.)
 *************************************************************************/

#include "GLFWpp.h"

namespace GLFW {

/*************************************************************************
 * Internal "global" data / callback functions
 *************************************************************************/
// Anonymous namespace for callback functions
namespace {
	// Error handling
	errorCallbackFun_t errorCallbackFun;
	
	// Input callbacks
	monitorCallbackFun_t monitorCallbackFun;
	joystickCallbackFun_t joystickCallbackFun;
}

// Forward declaration
void _exceptionErrorCallback(int error, const char* description);


/*************************************************************************
 * Initialization, version and error handling
 *************************************************************************/

class _LibInitializer {
private:
	_LibInitializer() {
		if (glfwInit() != GLFW_TRUE) {
			// This shouldn't happen.
			throw GLFWException {ErrorCode::UnknownError, "glfwInit returned false."};
		}
	}
	
	~_LibInitializer() {
		// Ignore exceptions in destructor
		try {
			glfwTerminate();
		}
		catch(...) {}
	}
	
	friend void initLib();
};

void initLib() {
	// Set error callback (that throws exceptions).
	glfwSetErrorCallback(_exceptionErrorCallback);
	
	// Instantiate static object that calls glfwInit() on its construction
	// and glfwTerminate() on its destruction (at program end).
	static _LibInitializer libInitializer;
}

// -- Error handling

/*! @brief Error callback function.
 *
 *  Calls custom error callback set by setErrorCallback (if set) and throws
 *  an exception which should be passed to the caller of the function that
 *  caused the error.
 */
void _exceptionErrorCallback(int error, const char* description) {
	// Determine error code enum value
	ErrorCode errorCode = static_cast<ErrorCode>(error);
	
	// Call custom error callback if set
	if (errorCallbackFun != nullptr) {
		errorCallbackFun(errorCode, description);
	}
	
	// Throw exception
	throw GLFWException {errorCode, description};
}

/*! @brief Sets the custom error callback. */
void setErrorCallback(errorCallbackFun_t cbFun) {
   // Set callback function (can also be nullptr to unset)
   errorCallbackFun = cbFun;
}


/*************************************************************************
 * Window management
 *************************************************************************/

/*! @brief Creates a window and its associated context. */
Window::Window(int width, int height, const char* title, Monitor* monitor, Window* share) {
	// Initialize GLFW if not initialized yet
	initLib();
	
	GLFWmonitor* monitorglfw = (monitor == nullptr ? nullptr : monitor->getPointer());
	GLFWwindow* shareglfw = (share == nullptr ? nullptr : share->getPointer());
	
	// Create window and its associated context.
	win_ = glfwCreateWindow(width, height, title, monitorglfw, shareglfw);
	
	if (win_ == nullptr) {
		throw GLFWException {ErrorCode::UnknownError, "glfwCreateWindow returned nullptr."};
	}
	
	// Associate window with object
	glfwSetWindowUserPointer(win_, this);
}

/*! @brief Destroys the window and its context. */
Window::~Window() {
	if (win_ != nullptr) {
		// Ignore exceptions in destructor
		try {
			glfwDestroyWindow(win_);
		}
		catch(...) {}
	}
}

// Window copy constructor/assignment: deleted

// Window move constructor
Window::Window(Window&& other) {
	// Copy data from other object
	win_ = other.win_;
	
	// Reset other object to default state - it now shouldn't be used anymore!
	other.win_ = nullptr;
}

// Window move assignment
Window& Window::operator=(Window&& other) {
	if (this != &other) {
		// Clean up old data from this object (see ~Window())
		if (win_ != nullptr) {
			glfwDestroyWindow(win_);
		}
		
		// Copy data from other object
		win_ = other.win_;
		
		// Reset other object to default state - it now shouldn't be used anymore!
		other.win_ = nullptr;
	}
	return *this;
}

/*! @brief Returns the monitor that the window uses for full screen mode. */
std::unique_ptr<Monitor> Window::getMonitor() {
	GLFWmonitor* monitorPtr = glfwGetWindowMonitor(win_);
	
	if (monitorPtr == nullptr) {
		// No monitor if we are in windowed mode.
		return nullptr;
	}
	else {
		return std::make_unique<Monitor>(monitorPtr);
	}
}

/*! @brief Sets the mode, monitor, video mode and placement of a window. */
void Window::setMonitor(Monitor* monitor, int xpos, int ypos, int width, int height, int refreshRate) {
	glfwSetWindowMonitor(win_, monitor->getPointer(), xpos, ypos, width, height, refreshRate);
}

/*! @brief Returns an attribute of the specified window. */
template <class T>
T Window::getAttrib(WindowAttribute attrib) {
	return static_cast<T>(glfwGetWindowAttrib(win_, static_cast<int>(attrib)));
}

template <>
bool Window::getAttrib<bool>(WindowAttribute attrib) {
	return (glfwGetWindowAttrib(win_, static_cast<int>(attrib)) == GLFW_TRUE);
}


// -- Callback setters

/*! @brief Sets the position callback for the specified window. */
void Window::setWindowPosCallback(windowPosCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowPosCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int xpos, int ypos) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowPosCallbackFun(*window, xpos, ypos);
		};
		glfwSetWindowPosCallback(win_, lambda);
	}
	else {
		glfwSetWindowPosCallback(win_, nullptr);
	}
}

/*! @brief Sets the size callback for the specified window. */
void Window::setWindowSizeCallback(windowSizeCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowSizeCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int width, int height) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowSizeCallbackFun(*window, width, height);
		};
		glfwSetWindowSizeCallback(win_, lambda);
	}
	else {
		glfwSetWindowSizeCallback(win_, nullptr);
	}
}

/*! @brief Sets the close callback for the specified window. */
void Window::setWindowCloseCallback(windowCloseCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowCloseCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowCloseCallbackFun(*window);
		};
		glfwSetWindowCloseCallback(win_, lambda);
	}
	else {
		glfwSetWindowCloseCallback(win_, nullptr);
	}
}

/*! @brief Sets the refresh callback for the specified window. */
void Window::setWindowRefreshCallback(windowRefreshCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowRefreshCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowRefreshCallbackFun(*window);
		};
		glfwSetWindowRefreshCallback(win_, lambda);
	}
	else {
		glfwSetWindowRefreshCallback(win_, nullptr);
	}
}

/*! @brief Sets the focus callback for the specified window. */
void Window::setWindowFocusCallback(windowFocusCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowFocusCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int focused) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowFocusCallbackFun(*window, (focused == GLFW_TRUE));
		};
		glfwSetWindowFocusCallback(win_, lambda);
	}
	else {
		glfwSetWindowFocusCallback(win_, nullptr);
	}
}

/*! @brief Sets the iconify callback for the specified window. */
void Window::setWindowIconifyCallback(windowIconifyCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	windowIconifyCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int iconified) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->windowIconifyCallbackFun(*window, (iconified == GLFW_TRUE));
		};
		glfwSetWindowIconifyCallback(win_, lambda);
	}
	else {
		glfwSetWindowIconifyCallback(win_, nullptr);
	}
}

/*! @brief Sets the framebuffer resize callback for the specified window. */
void Window::setFramebufferSizeCallback(framebufferSizeCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	framebufferSizeCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int width, int height) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->framebufferSizeCallbackFun(*window, width, height);
		};
		glfwSetFramebufferSizeCallback(win_, lambda);
	}
	else {
		glfwSetFramebufferSizeCallback(win_, nullptr);
	}
}


/*************************************************************************
 * Window related input handling
 *************************************************************************/
 
/*! @brief Returns the value of an input option for the window. */
template <class T>
T Window::getInputMode(InputModeOption mode) {
	return static_cast<T>(glfwGetInputMode(win_, static_cast<int>(mode)));
}

template <>
bool Window::getInputMode<bool>(InputModeOption mode) {
	return (glfwGetInputMode(win_, static_cast<int>(mode)) == GLFW_TRUE);
}


/*! @brief Sets the cursor for the window. */
void Window::setCursor(Cursor* cursor) {
	if (cursor == nullptr) {
		// Unset cursor / reset to default cursor
		glfwSetCursor(win_, nullptr);
	}
	else {
		glfwSetCursor(win_, cursor->getPointer());
	}
}

// -- Callback setters

void Window::setKeyCallback(keyCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	keyCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int key_i, int scancode_i, int action_i, int mods_i) {
			Window* window     = static_cast<Window*>(glfwGetWindowUserPointer(win));
			KeyCode key        = static_cast<KeyCode>(key_i);
			InputAction action = static_cast<InputAction>(action_i);
			KeyModifier mods   = static_cast<KeyModifier>(mods_i);
			window->keyCallbackFun(*window, key, scancode_i, action, mods);
		};
		glfwSetKeyCallback(win_, lambda);
	}
	else {
		glfwSetKeyCallback(win_, nullptr);
	}
}

void Window::setCharCallback(charCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	charCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, unsigned int codepoint) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->charCallbackFun(*window, codepoint);
		};
		glfwSetCharCallback(win_, lambda);
	}
	else {
		glfwSetCharCallback(win_, nullptr);
	}
}

void Window::setCharModsCallback(charModsCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	charModsCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, unsigned int codepoint, int mods_i) {
			Window* window   = static_cast<Window*>(glfwGetWindowUserPointer(win));
			KeyModifier mods = static_cast<KeyModifier>(mods_i);
			window->charModsCallbackFun(*window, codepoint, mods);
		};
		glfwSetCharModsCallback(win_, lambda);
	}
	else {
		glfwSetCharModsCallback(win_, nullptr);
	}
}

void Window::setMouseButtonCallback(mouseButtonCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	mouseButtonCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int button_i, int action_i, int mods_i) {
			Window* window     = static_cast<Window*>(glfwGetWindowUserPointer(win));
			MouseButton button = static_cast<MouseButton>(button_i);
			InputAction action = static_cast<InputAction>(action_i);
			KeyModifier mods   = static_cast<KeyModifier>(mods_i);
			window->mouseButtonCallbackFun(*window, button, action, mods);
		};
		glfwSetMouseButtonCallback(win_, lambda);
	}
	else {
		glfwSetMouseButtonCallback(win_, nullptr);
	}
}

void Window::setCursorPosCallback(cursorPosCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	cursorPosCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, double xpos, double ypos) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->cursorPosCallbackFun(*window, xpos, ypos);
		};
		glfwSetCursorPosCallback(win_, lambda);
	}
	else {
		glfwSetCursorPosCallback(win_, nullptr);
	}
}

void Window::setCursorEnterCallback(cursorEnterCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	cursorEnterCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int entered) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->cursorEnterCallbackFun(*window, (entered == GLFW_TRUE));
		};
		glfwSetCursorEnterCallback(win_, lambda);
	}
	else {
		glfwSetCursorEnterCallback(win_, nullptr);
	}
}

void Window::setScrollCallback(scrollCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	scrollCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, double xoffset, double yoffset) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			window->scrollCallbackFun(*window, xoffset, yoffset);
		};
		glfwSetScrollCallback(win_, lambda);
	}
	else {
		glfwSetScrollCallback(win_, nullptr);
	}
}

void Window::setDropCallback(dropCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	dropCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWwindow* win, int count, const char** paths) {
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
			
			// Convert paths to string vector
			std::vector<std::string> pathsVec (count);
			for (int i = 0; i < count; ++i) {
				pathsVec.push_back( std::string {paths[i]} );
			}
						
			window->dropCallbackFun(*window, pathsVec);
		};
		glfwSetDropCallback(win_, lambda);
	}
	else {
		glfwSetDropCallback(win_, nullptr);
	}
}


/*************************************************************************
 * Wrappers for context related functions
 *************************************************************************/

/*! @brief Returns the window whose context is current on the calling thread. */
Window* getCurrentContext() {
	GLFWwindow* glfwWin = glfwGetCurrentContext();
	
	if (glfwWin == nullptr) {
		// No context is current on the calling thread.
		return nullptr;
	}
	else if (glfwGetWindowUserPointer(glfwWin) == nullptr) {
		// There is a current context, but it isn't associated with a Window.
		// This should not happen, though... (Unless the user is messing
		// around with glfwCreateWindow on their own.)
		return nullptr;
	}
	else {
		// Retrieve pointer to associated Window.
		return static_cast<Window*>(glfwGetWindowUserPointer(glfwWin));
	}
}


/*************************************************************************
 * Monitor
 *************************************************************************/

/*! @brief Returns the available video modes for the specified monitor. */
std::vector<const VidMode*> Monitor::getVideoModes() {
	int count;
	const VidMode* modePtrs = glfwGetVideoModes(monitor_, &count);
	
	if (count == 0 || modePtrs == nullptr) {
		return {};
	}
	else {
		std::vector<const VidMode*> modeVec;
		
		for (int i = 0; i < count; ++i) {
			modeVec.push_back( &modePtrs[i] );
		}
		return modeVec;
	}
}


/*! @brief Returns the currently connected monitors. */
std::vector<Monitor> getMonitors() {
	int count;
	GLFWmonitor** monitorPtrs = glfwGetMonitors(&count);
	
	if (count == 0 || monitorPtrs == nullptr) {
		// No monitors found -> return empty vector
		return std::vector<Monitor> {};
	}
	else {
		std::vector<Monitor> monitorVec;
		
		for (int i = 0; i < count; ++i) {
			// Create Monitor objects that encapsulate the pointers
			// and add it to the vector.
			monitorVec.push_back( Monitor {monitorPtrs[i]} );
		}
		return monitorVec;
	}
}

/*! @brief Returns the primary monitor. */
std::unique_ptr<Monitor> getPrimaryMonitor() {
	GLFWmonitor* mon = glfwGetPrimaryMonitor();
	if (mon == nullptr) {
		return nullptr;
	}
	else {
		return std::make_unique<Monitor>(mon);
	}
}


// -- Callback setters

/*! @brief Sets the monitor configuration callback. */
void setMonitorCallback(monitorCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	monitorCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](GLFWmonitor* monitorglfw, int event_i) {
			Monitor monitor {monitorglfw};
			ConnectionEvent event = static_cast<ConnectionEvent>(event_i);
			monitorCallbackFun(monitor, event);
		};
		glfwSetMonitorCallback(lambda);
	}
	else {
		glfwSetMonitorCallback(nullptr);
	}
}


/*************************************************************************
 * Cursors
 *************************************************************************/

/*! @brief Creates a custom cursor. */
Cursor::Cursor(const Image* image, int xhot, int yhot) {
   cursor_ = glfwCreateCursor(image, xhot, yhot);
   
   if (cursor_ == nullptr) {
	   throw GLFWException {ErrorCode::UnknownError, "glfwCreateCursor returned nullptr."};
   }
}

/*! @brief Creates a cursor with a standard shape. */
Cursor::Cursor(CursorShape shape) {
	cursor_ = glfwCreateStandardCursor(static_cast<int>(shape));
	
	if (cursor_ == nullptr) {
		throw GLFWException {ErrorCode::UnknownError, "glfwCreateStandardCursor returned nullptr."};
	}
}

/*! @brief Destroys a cursor. */
Cursor::~Cursor() {
	// Ignore exceptions in destructor
	try {
		if (cursor_ != nullptr) {
			glfwDestroyCursor(cursor_);
		}
	}
	catch(...) {}
}

// move constructor
Cursor::Cursor(Cursor&& other) {
	// Copy data from other object
	cursor_ = other.cursor_;

	// Reset other object to default state - it now shouldn't be used anymore!
	other.cursor_ = nullptr;
}

// move assignment
Cursor& Cursor::operator=(Cursor&& other) {
	if (this != &other) {
		// Clean up old data from this object (see ~Cursor())
		if (cursor_ != nullptr) {
			glfwDestroyCursor(cursor_);
		}

		// Copy data from other object
		cursor_ = other.cursor_;

		// Reset other object to default state - it now shouldn't be used anymore!
		other.cursor_ = nullptr;
	}
	return *this;
}


/*************************************************************************
 * Input handling
 *************************************************************************/

/*! @brief Returns the values of all axes of the specified joystick. */
std::vector<float> getJoystickAxes(Joystick joy) {
	int count;
	const float* axesPtrs = glfwGetJoystickAxes(static_cast<int>(joy), &count);
	
	if (count == 0 || axesPtrs == nullptr) {
		// No joystick present -> return empty vector
		return {};
	}
	else {
		std::vector<float> axesVec;
		
		for (int i = 0; i < count; ++i) {
			axesVec.push_back(axesPtrs[i]);
		}
		return axesVec;
	}
}

/*! @brief Returns the state of all buttons of the specified joystick. */
std::vector<InputAction> getJoystickButtons(Joystick joy) {
	int count;
	const unsigned char* buttonsPtrs = glfwGetJoystickButtons(static_cast<int>(joy), &count);
	
	if (count == 0 || buttonsPtrs == nullptr) {
		// No joystick present -> return empty vector
		return {};
	}
	else {
		std::vector<InputAction> buttonsVec;
		
		for (int i = 0; i < count; ++i) {
			buttonsVec.push_back(static_cast<InputAction>(buttonsPtrs[i]));
		}
		return buttonsVec;
	}
}


// -- Callback setters

/*! @brief Sets the joystick configuration callback. */
void setJoystickCallback(joystickCallbackFun_t cbFun) {
	// Set callback function (can also be nullptr to unset)
	joystickCallbackFun = cbFun;
	
	if (cbFun) {
		auto lambda = [](int joy_i, int event_i) {
			Joystick joy          = static_cast<Joystick>(joy_i);
			ConnectionEvent event = static_cast<ConnectionEvent>(event_i);
			joystickCallbackFun(joy, event);
		};
		glfwSetJoystickCallback(lambda);
	}
	else {
		glfwSetJoystickCallback(nullptr);
	}
}

} // end namespace GLFW
