/*************************************************************************
 * C++ wrapper for GLFW3
 * (Documentation mostly stolen from official GLFW documentation.)
 *************************************************************************/

#ifndef _GLFWPP_H
#define _GLFWPP_H

#include <GLFW/glfw3.h>

#include <exception>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace GLFW {

/*************************************************************************
 * Constants and enumerations
 *************************************************************************/

/*! @brief "Don't care" value. (Equal to -1.) */
const int ValueDontCare = GLFW_DONT_CARE;  // -1

/*! @brief Window hints enum. */
enum class WindowHint {
	// Window related attributes
	Focused      = GLFW_FOCUSED,       // 0x00020001
	Resizable    = GLFW_RESIZABLE,     // 0x00020003
	Visible      = GLFW_VISIBLE,       // 0x00020004
	Decorated    = GLFW_DECORATED,     // 0x00020005
	AutoIconify  = GLFW_AUTO_ICONIFY,  // 0x00020006
	Floating     = GLFW_FLOATING,      // 0x00020007
	Maximized    = GLFW_MAXIMIZED,     // 0x00020008
	
	// Framebuffer related attributes
	RedBits        = GLFW_RED_BITS,          // 0x00021001
	GreenBits      = GLFW_GREEN_BITS,        // 0x00021002
	BlueBits       = GLFW_BLUE_BITS,         // 0x00021003
	AlphaBits      = GLFW_ALPHA_BITS,        // 0x00021004
	DepthBits      = GLFW_DEPTH_BITS,        // 0x00021005
	StencilBits    = GLFW_STENCIL_BITS,      // 0x00021006
	AccumRedBits   = GLFW_ACCUM_RED_BITS,    // 0x00021007
	AccumGreenBits = GLFW_ACCUM_GREEN_BITS,  // 0x00021008
	AccumBlueBits  = GLFW_ACCUM_BLUE_BITS,   // 0x00021009
	AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS,  // 0x0002100A
	AuxBuffers     = GLFW_AUX_BUFFERS,       // 0x0002100B
	Stereo         = GLFW_STEREO,            // 0x0002100C
	Samples        = GLFW_SAMPLES,           // 0x0002100D
	SRGBCapable    = GLFW_SRGB_CAPABLE,      // 0x0002100E
	RefreshRate    = GLFW_REFRESH_RATE,      // 0x0002100F
	Doublebuffer   = GLFW_DOUBLEBUFFER,      // 0x00021010
	
	// Context related attributes
	ClientAPI              = GLFW_CLIENT_API,                // 0x00022001
	ContextVersionMajor    = GLFW_CONTEXT_VERSION_MAJOR,     // 0x00022002
	ContextVersionMinor    = GLFW_CONTEXT_VERSION_MINOR,     // 0x00022003
	ContextRobustness      = GLFW_CONTEXT_ROBUSTNESS,        // 0x00022005
	OpenGLForwardCompat    = GLFW_OPENGL_FORWARD_COMPAT,     // 0x00022006
	OpenGLDebugContext     = GLFW_OPENGL_DEBUG_CONTEXT,      // 0x00022007
	OpenGLProfile          = GLFW_OPENGL_PROFILE,            // 0x00022008
	ContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,  // 0x00022009
	ContextNoError         = GLFW_CONTEXT_NO_ERROR,          // 0x0002200A
	ContextCreationAPI     = GLFW_CONTEXT_CREATION_API       // 0x0002200B
};

/*! @brief Window attributes enum. */
enum class WindowAttribute {
	// Window related attributes
	Focused      = GLFW_FOCUSED,       // 0x00020001
	Iconified    = GLFW_ICONIFIED,     // 0x00020002
	Resizable    = GLFW_RESIZABLE,     // 0x00020003
	Visible      = GLFW_VISIBLE,       // 0x00020004
	Decorated    = GLFW_DECORATED,     // 0x00020005
	Floating     = GLFW_FLOATING,      // 0x00020007
	Maximized    = GLFW_MAXIMIZED,     // 0x00020008
	
	// Context related attributes
	ClientAPI              = GLFW_CLIENT_API,                // 0x00022001
	ContextVersionMajor    = GLFW_CONTEXT_VERSION_MAJOR,     // 0x00022002
	ContextVersionMinor    = GLFW_CONTEXT_VERSION_MINOR,     // 0x00022003
	ContextRevision        = GLFW_CONTEXT_REVISION,          // 0x00022004
	ContextRobustness      = GLFW_CONTEXT_ROBUSTNESS,        // 0x00022005
	OpenGLForwardCompat    = GLFW_OPENGL_FORWARD_COMPAT,     // 0x00022006
	OpenGLDebugContext     = GLFW_OPENGL_DEBUG_CONTEXT,      // 0x00022007
	OpenGLProfile          = GLFW_OPENGL_PROFILE,            // 0x00022008
	ContextCreationAPI     = GLFW_CONTEXT_CREATION_API       // 0x0002200B
};

/*! @brief Value enum for window attribute ClientAPI. */
enum class ClientAPI {
	NoAPI         = GLFW_NO_API,         //          0
	OpenGL_API    = GLFW_OPENGL_API,     // 0x00030001
	OpenGL_ES_API = GLFW_OPENGL_ES_API   // 0x00030002
};

/*! @brief Value enum for window attribute ContextRobustness. */
enum class ContextRobustness {
	NoRobustness        = GLFW_NO_ROBUSTNESS,          //          0
	NoResetNotification = GLFW_NO_RESET_NOTIFICATION,  // 0x00031001
	LoseContextOnReset  = GLFW_LOSE_CONTEXT_ON_RESET   // 0x00031002
};

/*! @brief Value enum for window attribute OpenGLProfile. */
enum class OpenGLProfile {
	Any    = GLFW_OPENGL_ANY_PROFILE,    //          0
	Core   = GLFW_OPENGL_CORE_PROFILE,   // 0x00032001
	Compat = GLFW_OPENGL_COMPAT_PROFILE  // 0x00032002
};

/*! @brief Value enum for window hint ContextReleaseBehavior. */
enum class ContextReleaseBehavior {
	Any   = GLFW_ANY_RELEASE_BEHAVIOR,    //          0
	Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,  // 0x00035001
	None  = GLFW_RELEASE_BEHAVIOR_NONE    // 0x00035002
};

/*! @brief Value enum for window attribute ContextCreationAPI. */
enum class ContextCreationAPI {
	Native = GLFW_NATIVE_CONTEXT_API,  // 0x00036001
	EGL    = GLFW_EGL_CONTEXT_API      // 0x00036002
};


/*! @brief Input modes enum. @sa glfwSetInputMode */
enum class InputModeOption {
	Cursor             = GLFW_CURSOR,               // 0x00033001
	StickyKeys         = GLFW_STICKY_KEYS,          // 0x00033002
	StickyMouseButtons = GLFW_STICKY_MOUSE_BUTTONS  // 0x00033003
};

/*! @brief Cursor modes enum for `InputModeOption::Cursor`. */
enum class CursorMode {
	Normal   = GLFW_CURSOR_NORMAL,   // 0x00034001
	Hidden   = GLFW_CURSOR_HIDDEN,   // 0x00034002
	Disabled = GLFW_CURSOR_DISABLED  // 0x00034003
};


/*! @brief Input action enum (release/press/repeat). */
enum class InputAction {
	Release = GLFW_RELEASE,  // 0
	Press   = GLFW_PRESS,    // 1
	Repeat  = GLFW_REPEAT    // 2
};

/*! @brief Keyboard key enum. */
enum class KeyCode {
	// The unknown key
	Unknown      = GLFW_KEY_UNKNOWN,        // -1

	// Printable keys
	Space        = GLFW_KEY_SPACE,          // 32
	Apostrophe   = GLFW_KEY_APOSTROPHE,     // 39 (')
	Comma        = GLFW_KEY_COMMA,          // 44 (,)
	Minus        = GLFW_KEY_MINUS,          // 45 (-)
	Period       = GLFW_KEY_PERIOD,         // 46 (.)
	Slash        = GLFW_KEY_SLASH,          // 47 (/)
	Key0         = GLFW_KEY_0,              // 48
	Key1         = GLFW_KEY_1,              // 49
	Key2         = GLFW_KEY_2,              // 50
	Key3         = GLFW_KEY_3,              // 51
	Key4         = GLFW_KEY_4,              // 52
	Key5         = GLFW_KEY_5,              // 53
	Key6         = GLFW_KEY_6,              // 54
	Key7         = GLFW_KEY_7,              // 55
	Key8         = GLFW_KEY_8,              // 56
	Key9         = GLFW_KEY_9,              // 57
	Semicolon    = GLFW_KEY_SEMICOLON,      // 59 (;)
	Equal        = GLFW_KEY_EQUAL,          // 61 (=)
	A            = GLFW_KEY_A,              // 65
	B            = GLFW_KEY_B,              // 66
	C            = GLFW_KEY_C,              // 67
	D            = GLFW_KEY_D,              // 68
	E            = GLFW_KEY_E,              // 69
	F            = GLFW_KEY_F,              // 70
	G            = GLFW_KEY_G,              // 71
	H            = GLFW_KEY_H,              // 72
	I            = GLFW_KEY_I,              // 73
	J            = GLFW_KEY_J,              // 74
	K            = GLFW_KEY_K,              // 75
	L            = GLFW_KEY_L,              // 76
	M            = GLFW_KEY_M,              // 77
	N            = GLFW_KEY_N,              // 78
	O            = GLFW_KEY_O,              // 79
	P            = GLFW_KEY_P,              // 80
	Q            = GLFW_KEY_Q,              // 81
	R            = GLFW_KEY_R,              // 82
	S            = GLFW_KEY_S,              // 83
	T            = GLFW_KEY_T,              // 84
	U            = GLFW_KEY_U,              // 85
	V            = GLFW_KEY_V,              // 86
	W            = GLFW_KEY_W,              // 87
	X            = GLFW_KEY_X,              // 88
	Y            = GLFW_KEY_Y,              // 89
	Z            = GLFW_KEY_Z,              // 90
	LeftBracket  = GLFW_KEY_LEFT_BRACKET,   // 91 ([)
	Backslash    = GLFW_KEY_BACKSLASH,      // 92 (\)
	RightBracket = GLFW_KEY_RIGHT_BRACKET,  // 93 (])
	Accent       = GLFW_KEY_GRAVE_ACCENT,   // 96 (`)
	World1       = GLFW_KEY_WORLD_1,        // 161 (non-US #1)
	World2       = GLFW_KEY_WORLD_2,        // 162 (non-US #2)

	// Function keys
	Escape       = GLFW_KEY_ESCAPE,         // 256
	Enter        = GLFW_KEY_ENTER,          // 257
	Tab          = GLFW_KEY_TAB,            // 258
	Backspace    = GLFW_KEY_BACKSPACE,      // 259
	Insert       = GLFW_KEY_INSERT,         // 260
	Delete       = GLFW_KEY_DELETE,         // 261
	Right        = GLFW_KEY_RIGHT,          // 262
	Left         = GLFW_KEY_LEFT,           // 263
	Down         = GLFW_KEY_DOWN,           // 264
	Up           = GLFW_KEY_UP,             // 265
	PageUp       = GLFW_KEY_PAGE_UP,        // 266
	PageDown     = GLFW_KEY_PAGE_DOWN,      // 267
	Home         = GLFW_KEY_HOME,           // 268
	End          = GLFW_KEY_END,            // 269
	CapsLock     = GLFW_KEY_CAPS_LOCK,      // 280
	ScrollLock   = GLFW_KEY_SCROLL_LOCK,    // 281
	NumLock      = GLFW_KEY_NUM_LOCK,       // 282
	PrintScreen  = GLFW_KEY_PRINT_SCREEN,   // 283
	Pause        = GLFW_KEY_PAUSE,          // 284
	F1           = GLFW_KEY_F1,             // 290
	F2           = GLFW_KEY_F2,             // 291
	F3           = GLFW_KEY_F3,             // 292
	F4           = GLFW_KEY_F4,             // 293
	F5           = GLFW_KEY_F5,             // 294
	F6           = GLFW_KEY_F6,             // 295
	F7           = GLFW_KEY_F7,             // 296
	F8           = GLFW_KEY_F8,             // 297
	F9           = GLFW_KEY_F9,             // 298
	F10          = GLFW_KEY_F10,            // 299
	F11          = GLFW_KEY_F11,            // 300
	F12          = GLFW_KEY_F12,            // 301
	F13          = GLFW_KEY_F13,            // 302
	F14          = GLFW_KEY_F14,            // 303
	F15          = GLFW_KEY_F15,            // 304
	F16          = GLFW_KEY_F16,            // 305
	F17          = GLFW_KEY_F17,            // 306
	F18          = GLFW_KEY_F18,            // 307
	F19          = GLFW_KEY_F19,            // 308
	F20          = GLFW_KEY_F20,            // 309
	F21          = GLFW_KEY_F21,            // 310
	F22          = GLFW_KEY_F22,            // 311
	F23          = GLFW_KEY_F23,            // 312
	F24          = GLFW_KEY_F24,            // 313
	F25          = GLFW_KEY_F25,            // 314
	KP_0         = GLFW_KEY_KP_0,           // 320
	KP_1         = GLFW_KEY_KP_1,           // 321
	KP_2         = GLFW_KEY_KP_2,           // 322
	KP_3         = GLFW_KEY_KP_3,           // 323
	KP_4         = GLFW_KEY_KP_4,           // 324
	KP_5         = GLFW_KEY_KP_5,           // 325
	KP_6         = GLFW_KEY_KP_6,           // 326
	KP_7         = GLFW_KEY_KP_7,           // 327
	KP_8         = GLFW_KEY_KP_8,           // 328
	KP_9         = GLFW_KEY_KP_9,           // 329
	KP_Decimal   = GLFW_KEY_KP_DECIMAL,     // 330
	KP_Divide    = GLFW_KEY_KP_DIVIDE,      // 331
	KP_Multiply  = GLFW_KEY_KP_MULTIPLY,    // 332
	KP_Subtract  = GLFW_KEY_KP_SUBTRACT,    // 333
	KP_Add       = GLFW_KEY_KP_ADD,         // 334
	KP_Enter     = GLFW_KEY_KP_ENTER,       // 335
	KP_Equal     = GLFW_KEY_KP_EQUAL,       // 336
	LeftShift    = GLFW_KEY_LEFT_SHIFT,     // 340
	LeftControl  = GLFW_KEY_LEFT_CONTROL,   // 341
	LeftAlt      = GLFW_KEY_LEFT_ALT,       // 342
	LeftSuper    = GLFW_KEY_LEFT_SUPER,     // 343
	RightShift   = GLFW_KEY_RIGHT_SHIFT,    // 344
	RightControl = GLFW_KEY_RIGHT_CONTROL,  // 345
	RightAlt     = GLFW_KEY_RIGHT_ALT,      // 346
	RightSuper   = GLFW_KEY_RIGHT_SUPER,    // 347
	Menu         = GLFW_KEY_MENU,           // 348
	
	// Last key
	Last         = GLFW_KEY_LAST         // GLFW_KEY_MENU
};

// XXX does this work as a bitfield? (like Shift | Control)
/*! @brief Modifier key flags. */
enum class KeyModifier {
	None    = 0,
	Shift   = GLFW_MOD_SHIFT,    // 0x0001
	Control = GLFW_MOD_CONTROL,  // 0x0002
	Alt     = GLFW_MOD_ALT,      // 0x0004
	Super   = GLFW_MOD_SUPER     // 0x0008
};

/*! @brief Mouse buttons enum. */
enum class MouseButton {
	Button1 = GLFW_MOUSE_BUTTON_1,       // 0
	Button2 = GLFW_MOUSE_BUTTON_2,       // 1
	Button3 = GLFW_MOUSE_BUTTON_3,       // 2
	Button4 = GLFW_MOUSE_BUTTON_4,       // 3
	Button5 = GLFW_MOUSE_BUTTON_5,       // 4
	Button6 = GLFW_MOUSE_BUTTON_6,       // 5
	Button7 = GLFW_MOUSE_BUTTON_7,       // 6
	Button8 = GLFW_MOUSE_BUTTON_8,       // 7
	Last    = GLFW_MOUSE_BUTTON_LAST,    // GLFW_MOUSE_BUTTON_8
	Left    = GLFW_MOUSE_BUTTON_LEFT,    // GLFW_MOUSE_BUTTON_1
	Right   = GLFW_MOUSE_BUTTON_RIGHT,   // GLFW_MOUSE_BUTTON_2
	Middle  = GLFW_MOUSE_BUTTON_MIDDLE   // GLFW_MOUSE_BUTTON_3
};

/*! @brief Joystick slot enum. */
enum class Joystick {
	Slot1  = GLFW_JOYSTICK_1,    // 0
	Slot2  = GLFW_JOYSTICK_2,    // 1
	Slot3  = GLFW_JOYSTICK_3,    // 2
	Slot4  = GLFW_JOYSTICK_4,    // 3
	Slot5  = GLFW_JOYSTICK_5,    // 4
	Slot6  = GLFW_JOYSTICK_6,    // 5
	Slot7  = GLFW_JOYSTICK_7,    // 6
	Slot8  = GLFW_JOYSTICK_8,    // 7
	Slot9  = GLFW_JOYSTICK_9,    // 8
	Slot10 = GLFW_JOYSTICK_10,   // 9
	Slot11 = GLFW_JOYSTICK_11,   // 10
	Slot12 = GLFW_JOYSTICK_12,   // 11
	Slot13 = GLFW_JOYSTICK_13,   // 12
	Slot14 = GLFW_JOYSTICK_14,   // 13
	Slot15 = GLFW_JOYSTICK_15,   // 14
	Slot16 = GLFW_JOYSTICK_16,   // 15
	Last   = GLFW_JOYSTICK_LAST  // GLFW_JOYSTICK_16
};

/*! @brief Connection events (connected/disconnected). */
enum class ConnectionEvent {
	Connected    = GLFW_CONNECTED,    // 0x00040001
	Disconnected = GLFW_DISCONNECTED  // 0x00040002
};


/*! @brief errors Error codes */
enum class ErrorCode {
	UnknownError = 0,
	
	/*! @brief GLFW has not been initialized.
	 *
	 *  This occurs if a GLFW function was called that must not be called unless the
	 *  library is [initialized](@ref intro_init).
	 *
	 *  @analysis Application programmer error.  Initialize GLFW before calling any
	 *  function that requires initialization.
	 */
	NotInitialized = GLFW_NOT_INITIALIZED,  // 0x00010001
	
	/*! @brief No context is current for this thread.
	 *
	 *  This occurs if a GLFW function was called that needs and operates on the
	 *  current OpenGL or OpenGL ES context but no context is current on the calling
	 *  thread.  One such function is @ref glfwSwapInterval.
	 *
	 *  @analysis Application programmer error.  Ensure a context is current before
	 *  calling functions that require a current context.
	 */
	NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,  // 0x00010002
	
	/*! @brief One of the arguments to the function was an invalid enum value.
	 *
	 *  One of the arguments to the function was an invalid enum value, for example
	 *  requesting [GLFW_RED_BITS](@ref window_hints_fb) with @ref
	 *  glfwGetWindowAttrib.
	 *
	 *  @analysis Application programmer error.  Fix the offending call.
	 */
	InvalidEnum = GLFW_INVALID_ENUM,  // 0x00010003
	
	/*! @brief One of the arguments to the function was an invalid value.
	 *
	 *  One of the arguments to the function was an invalid value, for example
	 *  requesting a non-existent OpenGL or OpenGL ES version like 2.7.
	 *
	 *  Requesting a valid but unavailable OpenGL or OpenGL ES version will instead
	 *  result in a @ref ErrorCode::VersionUnavailable error.
	 *
	 *  @analysis Application programmer error.  Fix the offending call.
	 */
	InvalidValue = GLFW_INVALID_VALUE,  // 0x00010004
	
	/*! @brief A memory allocation failed.
	 *
	 *  A memory allocation failed.
	 *
	 *  @analysis A bug in GLFW or the underlying operating system.  Report the bug
	 *  to our [issue tracker](https://github.com/glfw/glfw/issues).
	 */
	OutOfMemory = GLFW_OUT_OF_MEMORY,  // 0x00010005
	
	/*! @brief GLFW could not find support for the requested API on the system.
	 *
	 *  GLFW could not find support for the requested API on the system.
	 *
	 *  @analysis The installed graphics driver does not support the requested
	 *  API, or does not support it via the chosen context creation backend.
	 *  Below are a few examples.
	 *
	 *  @par
	 *  Some pre-installed Windows graphics drivers do not support OpenGL.  AMD only
	 *  supports OpenGL ES via EGL, while Nvidia and Intel only support it via
	 *  a WGL or GLX extension.  OS X does not provide OpenGL ES at all.  The Mesa
	 *  EGL, OpenGL and OpenGL ES libraries do not interface with the Nvidia binary
	 *  driver.  Older graphics drivers do not support Vulkan.
	 */
	APIUnavailable = GLFW_API_UNAVAILABLE,  // 0x00010006
	
	/*! @brief The requested OpenGL or OpenGL ES version is not available.
	 *
	 *  The requested OpenGL or OpenGL ES version (including any requested context
	 *  or framebuffer hints) is not available on this machine.
	 *
	 *  @analysis The machine does not support your requirements.  If your
	 *  application is sufficiently flexible, downgrade your requirements and try
	 *  again.  Otherwise, inform the user that their machine does not match your
	 *  requirements.
	 *
	 *  @par
	 *  Future invalid OpenGL and OpenGL ES versions, for example OpenGL 4.8 if 5.0
	 *  comes out before the 4.x series gets that far, also fail with this error and
	 *  not @ref ErrorCode::InvalidValue, because GLFW cannot know what future versions
	 *  will exist.
	 */
	VersionUnavailable = GLFW_VERSION_UNAVAILABLE,  // 0x00010007
	
	/*! @brief A platform-specific error occurred that does not match any of the
	 *  more specific categories.
	 *
	 *  A platform-specific error occurred that does not match any of the more
	 *  specific categories.
	 *
	 *  @analysis A bug or configuration error in GLFW, the underlying operating
	 *  system or its drivers, or a lack of required resources.  Report the issue to
	 *  our [issue tracker](https://github.com/glfw/glfw/issues).
	 */
	PlatformError = GLFW_PLATFORM_ERROR,  // 0x00010008
	
	/*! @brief The requested format is not supported or available.
	 *
	 *  If emitted during window creation, the requested pixel format is not
	 *  supported.
	 *
	 *  If emitted when querying the clipboard, the contents of the clipboard could
	 *  not be converted to the requested format.
	 *
	 *  @analysis If emitted during window creation, one or more
	 *  [hard constraints](@ref window_hints_hard) did not match any of the
	 *  available pixel formats.  If your application is sufficiently flexible,
	 *  downgrade your requirements and try again.  Otherwise, inform the user that
	 *  their machine does not match your requirements.
	 *
	 *  @par
	 *  If emitted when querying the clipboard, ignore the error or report it to
	 *  the user, as appropriate.
	 */
	FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,  // 0x00010009
	
	/*! @brief The specified window does not have an OpenGL or OpenGL ES context.
	 *
	 *  A window that does not have an OpenGL or OpenGL ES context was passed to
	 *  a function that requires it to have one.
	 *
	 *  @analysis Application programmer error.  Fix the offending call.
	 */
	NoWindowContext = GLFW_NO_WINDOW_CONTEXT,  // 0x0001000A
};


/*! @brief shapes Standard cursor shapes.
 *
 *  See [standard cursor creation](@ref cursor_standard) for how these are used.
 */
enum class CursorShape {
	Default = GLFW_ARROW_CURSOR,  // 0x00036001
	
	/*! @brief The regular arrow cursor shape. */
	Arrow = GLFW_ARROW_CURSOR,  // 0x00036001
	
	/*! @brief The text input I-beam cursor shape. */
	IBeam = GLFW_IBEAM_CURSOR,  // 0x00036002
	
	/*! @brief The crosshair shape. */
	Crosshair = GLFW_CROSSHAIR_CURSOR,  // 0x00036003
	
	/*! @brief The hand shape. */
	Hand = GLFW_HAND_CURSOR,  // 0x00036004
	
	/*! @brief The horizontal resize arrow shape. */
	HResize = GLFW_HRESIZE_CURSOR,  // 0x00036005
	
	/*! @brief The vertical resize arrow shape. */
	VResize = GLFW_VRESIZE_CURSOR,  // 0x00036006
};


/*************************************************************************
 * Forward declarations and type aliases
 *************************************************************************/
// -- Class forward declarations
class Window;
class Monitor;
class Cursor;
template <class T> class Point2D;
class Size2D;
class Area2D;

// -- Aliases for GLFW structs
using Image = GLFWimage;
using VidMode = GLFWvidmode;
using GammaRamp = GLFWgammaramp;

// -- Callback function signatures

/*! @brief The function signature for error callbacks.
 *
 *  This is the function signature for error callback functions.
 *
 *  @param[in] error An [error code](@ref errors).
 *  @param[in] description A UTF-8 encoded string describing the error.
 */
using errorCallbackFun_t = std::function<void(ErrorCode, const char*)>;


/*! @brief The function signature for window position callbacks.
 *
 *  This is the function signature for window position callback functions.
 *
 *  @param[in] window The window that was moved.
 *  @param[in] xpos The new x-coordinate, in screen coordinates, of the
 *  upper-left corner of the client area of the window.
 *  @param[in] ypos The new y-coordinate, in screen coordinates, of the
 *  upper-left corner of the client area of the window.
 */
using windowPosCallbackFun_t = std::function<void(Window&, int, int)>;

/*! @brief The function signature for window resize callbacks.
 *
 *  This is the function signature for window size callback functions.
 *
 *  @param[in] window The window that was resized.
 *  @param[in] width The new width, in screen coordinates, of the window.
 *  @param[in] height The new height, in screen coordinates, of the window.
 */
using windowSizeCallbackFun_t = std::function<void(Window&, int, int)>;

/*! @brief The function signature for window close callbacks.
 *
 *  This is the function signature for window close callback functions.
 *
 *  @param[in] window The window that the user attempted to close.
 */
using windowCloseCallbackFun_t = std::function<void(Window&)>;

/*! @brief The function signature for window content refresh callbacks.
 *
 *  This is the function signature for window refresh callback functions.
 *
 *  @param[in] window The window whose content needs to be refreshed.
 */
using windowRefreshCallbackFun_t = std::function<void(Window&)>;

/*! @brief The function signature for window focus/defocus callbacks.
 *
 *  This is the function signature for window focus callback functions.
 *
 *  @param[in] window The window that gained or lost input focus.
 *  @param[in] focused `true` if the window was given input focus, or
 *  `false` if it lost it.
 */
using windowFocusCallbackFun_t = std::function<void(Window&, bool)>;

/*! @brief The function signature for window iconify/restore callbacks.
 *
 *  This is the function signature for window iconify/restore callback
 *  functions.
 *
 *  @param[in] window The window that was iconified or restored.
 *  @param[in] iconified `true` if the window was iconified, or
 *  `false` if it was restored.
 */
using windowIconifyCallbackFun_t = std::function<void(Window&, bool)>;

/*! @brief The function signature for framebuffer resize callbacks.
 *
 *  This is the function signature for framebuffer resize callback
 *  functions.
 *
 *  @param[in] window The window whose framebuffer was resized.
 *  @param[in] width The new width, in pixels, of the framebuffer.
 *  @param[in] height The new height, in pixels, of the framebuffer.
 */
using framebufferSizeCallbackFun_t = std::function<void(Window&, int, int)>;


/*! @brief The function signature for keyboard key callbacks.
 *
 *  This is the function signature for keyboard key callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
 *  @param[in] scancode The system-specific scancode of the key.
 *  @param[in] action `InputAction::Press`, `InputAction::Release` or
 *  `InputAction::Repeat`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 */
using keyCallbackFun_t = std::function<void(Window&, KeyCode, int, InputAction, KeyModifier)>;

/*! @brief The function signature for Unicode character callbacks.
 *
 *  This is the function signature for Unicode character callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] codepoint The Unicode code point of the character.
 */
using charCallbackFun_t = std::function<void(Window&, unsigned int)>;

/*! @brief The function signature for Unicode character with modifiers
 *  callbacks.
 *
 *  This is the function signature for Unicode character with modifiers callback
 *  functions.  It is called for each input character, regardless of what
 *  modifier keys are held down.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] codepoint The Unicode code point of the character.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 */
using charModsCallbackFun_t = std::function<void(Window&, unsigned int, KeyModifier)>;

/*! @brief The function signature for mouse button callbacks.
 *
 *  This is the function signature for mouse button callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] button The [mouse button](@ref buttons) that was pressed or
 *  released.
 *  @param[in] action One of `InputAction::Press` or `InputAction::Release`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 */
using mouseButtonCallbackFun_t = std::function<void(Window&, MouseButton, InputAction, KeyModifier)>;

/*! @brief The function signature for cursor position callbacks.
 *
 *  This is the function signature for cursor position callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] xpos The new cursor x-coordinate, relative to the left edge of
 *  the client area.
 *  @param[in] ypos The new cursor y-coordinate, relative to the top edge of the
 *  client area.
 */
using cursorPosCallbackFun_t = std::function<void(Window&, double, double)>;

/*! @brief The function signature for cursor enter/leave callbacks.
 *
 *  This is the function signature for cursor enter/leave callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] entered `true` if the cursor entered the window's client
 *  area, or `false` if it left it.
 */
using cursorEnterCallbackFun_t = std::function<void(Window&, bool)>;

/*! @brief The function signature for scroll callbacks.
 *
 *  This is the function signature for scroll callback functions.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] xoffset The scroll offset along the x-axis.
 *  @param[in] yoffset The scroll offset along the y-axis.
 */
using scrollCallbackFun_t = std::function<void(Window&, double, double)>;

/*! @brief The function signature for file drop callbacks.
 *
 *  This is the function signature for file drop callbacks.
 *
 *  @param[in] window The window that received the event.
 *  @param[in] count The number of dropped files.
 *  @param[in] paths The UTF-8 encoded file and/or directory path names.
 */
using dropCallbackFun_t = std::function<void(Window&, std::vector<std::string>)>;


/*! @brief The function signature for monitor configuration callbacks.
 *
 *  This is the function signature for monitor configuration callback functions.
 *
 *  @param[in] monitor The monitor that was connected or disconnected.
 *  @param[in] event One of `ConnectionEvent::Connected` or
 *  `ConnectionEvent::Disconnected`.
 */
using monitorCallbackFun_t = std::function<void(Monitor&, ConnectionEvent)>;

/*! @brief The function signature for joystick configuration callbacks.
 *
 *  This is the function signature for joystick configuration callback
 *  functions.
 *
 *  @param[in] joy The joystick that was connected or disconnected.
 *  @param[in] event One of `ConnectionEvent::Connected` or
 *  `ConnectionEvent::Disconnected`.
 */
using joystickCallbackFun_t = std::function<void(Joystick, ConnectionEvent)>;


/*! @brief Client API function pointer type.
 *
 *  Generic function pointer used for returning client API function pointers
 *  without forcing a cast from a regular pointer.
 */
using glProcAddress_t = GLFWglproc;


/*************************************************************************
 * Custom exceptions
 *************************************************************************/

/*! @brief General exception type for GLFW. */
class GLFWException : public std::exception {
public:
	GLFWException(ErrorCode error, const char* description)
		: error {error}
		, description {description}
	{}
	
	virtual const char* what() const throw() {
		return description;
	}
	
	virtual ErrorCode code() const throw() {
		return error;
	}
	
private:
	ErrorCode error;
	const char* description;
};


/*************************************************************************
 * Initialization, version and error
 *************************************************************************/

/*! @brief Initializes the GLFW library.
 *
 *  This function initializes the GLFW library.  Before most GLFW functions can
 *  be used, GLFW must be initialized, and before an application terminates GLFW
 *  should be terminated in order to free any resources allocated during or
 *  after initialization.
 *
 *  This function creates a static object which should be destroyed when the
 *  program ends. On its destruction glfwTerminate will be called automatically.
 *
 *  Additional calls to this function after successful initialization but before
 *  termination will return immediately.
 *
 *  @errors Possible errors include @ref ErrorCode::PlatformError.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
void initLib();

/*! @brief Terminates the GLFW library.
 *
 *  This function destroys all remaining windows and cursors, restores any
 *  modified gamma ramps and frees any other allocated resources.  Once this
 *  function is called, you must again call @ref glfwInit successfully before
 *  you will be able to use most GLFW functions.
 *
 *  If the library was initialized by initLib, there is no need to call this
 *  function as it creates a static object that calls glfwTerminate on its
 *  destruction.
 *
 *  @errors Possible errors include @ref ErrorCode::PlatformError.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline void terminateLib() {
 	glfwTerminate();
}

/*! @brief Sets the error callback.
 *
 *  This function sets the error callback, which is called with an error code
 *  and a human-readable description each time a GLFW error occurs.
 *
 *  The error callback is called on the thread where the error occurred.  If you
 *  are using GLFW from multiple threads, your error callback needs to be
 *  written accordingly.
 *
 *  Because the description string may have been generated specifically for that
 *  error, it is not guaranteed to be valid after the callback has returned.  If
 *  you wish to use it after the callback returns, you need to make a copy.
 *
 *  Once set, the error callback remains set even after the library has been
 *  terminated.
 *
 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
 *  callback.
 *
 *  @remark This function may be called before @ref glfwInit.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
void setErrorCallback(errorCallbackFun_t cbFun);

/*! @brief Deletes the error callback. */
inline void unsetErrorCallback() {
	setErrorCallback(nullptr);
}

/*! @brief Retrieves the version of the GLFW library.
 *
 *  This function retrieves the major, minor and revision numbers of the GLFW
 *  library.  It is intended for when you are using GLFW as a shared library and
 *  want to ensure that you are using the minimum required version.
 *
 *  Any or all of the version arguments may be `nullptr`.
 *
 *  @param[out] major Where to store the major version number, or `nullptr`.
 *  @param[out] minor Where to store the minor version number, or `nullptr`.
 *  @param[out] rev Where to store the revision number, or `nullptr`.
 *
 *  @remark This function may be called before @ref glfwInit.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline void getVersion(int* major, int* minor, int* rev) {
	glfwGetVersion(major, minor, rev);
}

/*! @brief Retrieves the version of the GLFW library.
 *
 *  This function retrieves the major, minor and revision numbers of the GLFW
 *  library.  It is intended for when you are using GLFW as a shared library and
 *  want to ensure that you are using the minimum required version.
 *
 *  @return Library version as a std::tuple<int,int,int>.
 *
 *  @remark This function may be called before @ref glfwInit.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline std::tuple<int, int, int> getVersion() {
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	return std::make_tuple(major, minor, rev);
}

/*! @brief Returns a string describing the compile-time configuration.
 *
 *  This function returns the compile-time generated
 *  [version string](@ref intro_version_string) of the GLFW library binary.  It
 *  describes the version, platform, compiler and any platform-specific
 *  compile-time options.  It should not be confused with the OpenGL or OpenGL
 *  ES version string, queried with `glGetString`.
 *
 *  __Do not use the version string__ to parse the GLFW library version.  The
 *  @ref glfwGetVersion function provides the version of the running library
 *  binary in numerical format.
 *
 *  @return The ASCII encoded GLFW version string.
 *
 *  @remark This function may be called before @ref glfwInit.
 *
 *  @pointer_lifetime The returned string is static and compile-time generated.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline const char* getVersionString() {
	return glfwGetVersionString();
}


/*************************************************************************
 * Auxiliary classes
 *************************************************************************/

/*! @brief Two dimensional point with x- and y-coordinates. */
template <class T>
class Point2D {
public:
	Point2D()
		: x {0}
		, y {0}
	{};
	
	Point2D(T x, T y)
		: x {x}
		, y {y}
	{};
	
	T x;
	T y;
};

/*! @brief Two dimensional size with width and height. */
class Size2D {
public:
	Size2D()
		: width {0}
		, height {0}
	{};
	
	Size2D(int width, int height)
		: width {width}
		, height {height}
	{};
	
	int width;
	int height;
};

/*! @brief Area consisting of left, top, right and bottom coordinates. */
class Area2D {
public:
	Area2D()
		: left {0}
		, top {0}
		, right {0}
		, bottom {0}
	{};
	
	Area2D(int left, int top, int right, int bottom)
		: left {left}
		, top {top}
		, right {right}
		, bottom {bottom}
	{};
	
	int left;
	int top;
	int right;
	int bottom;
	
	int width() {
		return right - left;
	}
	
	int height() {
		return bottom - top;
	}
};


/*************************************************************************
 * Window management
 *************************************************************************/

/*! @brief Window object wrapper.
 *
 *  Wraps GLFW's windows into a real class.
 */
class Window {
public:
	/*********************************************************************
	 * Construction, destruction, copy and move
	 *********************************************************************/
	
	/*! @brief Creates a window and its associated context.
	 *
	 *  This constructor creates a window and its associated OpenGL or OpenGL ES
	 *  context.  Most of the options controlling how the window and its context
	 *  should be created are specified with [window hints](@ref window_hints).
	 *
	 *  Successful creation does not change which context is current.  Before you
	 *  can use the newly created context, you need to
	 *  [make it current](@ref context_current).  For information about the `share`
	 *  parameter, see @ref context_sharing.
	 *
	 *  The created window, framebuffer and context may differ from what you
	 *  requested, as not all parameters and hints are
	 *  [hard constraints](@ref window_hints_hard).  This includes the size of the
	 *  window, especially for full screen windows.  To query the actual attributes
	 *  of the created window, framebuffer and context, see @ref
	 *  glfwGetWindowAttrib, @ref glfwGetWindowSize and @ref glfwGetFramebufferSize.
	 *
	 *  To create a full screen window, you need to specify the monitor the window
	 *  will cover.  If no monitor is specified, the window will be windowed mode.
	 *  Unless you have a way for the user to choose a specific monitor, it is
	 *  recommended that you pick the primary monitor.  For more information on how
	 *  to query connected monitors, see @ref monitor_monitors.
	 *
	 *  For full screen windows, the specified size becomes the resolution of the
	 *  window's _desired video mode_.  As long as a full screen window is not
	 *  iconified, the supported video mode most closely matching the desired video
	 *  mode is set for the specified monitor.  For more information about full
	 *  screen windows, including the creation of so called _windowed full screen_
	 *  or _borderless full screen_ windows, see @ref window_windowed_full_screen.
	 *
	 *  Once you have created the window, you can switch it between windowed and
	 *  full screen mode with @ref glfwSetWindowMonitor.  If the window has an
	 *  OpenGL or OpenGL ES context, it will be unaffected.
	 *
	 *  By default, newly created windows use the placement recommended by the
	 *  window system.  To create the window at a specific position, make it
	 *  initially invisible using the [GLFW_VISIBLE](@ref window_hints_wnd) window
	 *  hint, set its [position](@ref window_pos) and then [show](@ref window_hide)
	 *  it.
	 *
	 *  As long as at least one full screen window is not iconified, the screensaver
	 *  is prohibited from starting.
	 *
	 *  Window systems put limits on window sizes.  Very large or very small window
	 *  dimensions may be overridden by the window system on creation.  Check the
	 *  actual [size](@ref window_size) after creation.
	 *
	 *  The [swap interval](@ref buffer_swap) is not set during window creation and
	 *  the initial value may vary depending on driver settings and defaults.
	 *
	 *  @param[in] width The desired width, in screen coordinates, of the window.
	 *  This must be greater than zero.
	 *  @param[in] height The desired height, in screen coordinates, of the window.
	 *  This must be greater than zero.
	 *  @param[in] title The initial, UTF-8 encoded window title.
	 *  @param[in] monitor The monitor to use for full screen mode, or `nullptr` for
	 *  windowed mode.
	 *  @param[in] share The window whose context to share resources with, or `nullptr`
	 *  to not share resources.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidEnum, @ref ErrorCode::InvalidValue, @ref ErrorCode::APIUnavailable, @ref
	 *  ErrorCode::VersionUnavailable, @ref ErrorCode::FormatUnavailable and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @reentrancy This function must not be called from a callback.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Window(int width, int height, const char* title, Monitor* monitor = nullptr,
		Window* share = nullptr);
	
	/*! @brief Destroys the window and its context.
	 *
	 *  This destructor destroys the specified window and its context. On calling
	 *  this function, no further callbacks will be called for that window.
	 *
	 *  If the context of the specified window is current on the main thread, it is
	 *  detached before being destroyed.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @note The context of the specified window must not be current on any other
	 *  thread when this function is called.
	 *
	 *  @reentrancy This function must not be called from a callback.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	~Window();
	
	// --- Forbid copy operations
	Window(const Window& other)            = delete;  // copy constructor
	Window& operator=(const Window& other) = delete;  // copy assignment
	
	// --- Override move operations
	Window(Window&& other);             // move constructor
	Window& operator=(Window&& other);  // move assignment
	
	
	/*********************************************************************
	 * Member accessors
	 *********************************************************************/
	
	/*! @brief Returns pointer to the internal GLFWwindow struct. */
	GLFWwindow* getPointer() {
		return win_;
	}
	
private:
	/*! Pointer to the wrapped window object. */
	GLFWwindow* win_;
	
	/*********************************************************************
	 * Callback functions
	 *********************************************************************/
	windowPosCallbackFun_t windowPosCallbackFun;
	windowSizeCallbackFun_t windowSizeCallbackFun;
	windowCloseCallbackFun_t windowCloseCallbackFun;
	windowRefreshCallbackFun_t windowRefreshCallbackFun;
	windowFocusCallbackFun_t windowFocusCallbackFun;
	windowIconifyCallbackFun_t windowIconifyCallbackFun;
	framebufferSizeCallbackFun_t framebufferSizeCallbackFun;
	
	keyCallbackFun_t keyCallbackFun;
	charCallbackFun_t charCallbackFun;
	charModsCallbackFun_t charModsCallbackFun;
	mouseButtonCallbackFun_t mouseButtonCallbackFun;
	cursorPosCallbackFun_t cursorPosCallbackFun;
	cursorEnterCallbackFun_t cursorEnterCallbackFun;
	scrollCallbackFun_t scrollCallbackFun;
	dropCallbackFun_t dropCallbackFun;
	
public:
	/*********************************************************************
	 * Wrappers for window related functions
	 *********************************************************************/
	
	/*! @brief Checks the close flag of the specified window.
	 *
	 *  This function returns the value of the close flag of the specified window.
	 *
	 *  @return The value of the close flag.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function may be called from any thread.  Access is not
	 *  synchronized.
	 */
	bool shouldClose() {
		return (glfwWindowShouldClose(win_) == GLFW_TRUE);
	}

	/*! @brief Sets the close flag of the specified window.
	 *
	 *  This function sets the value of the close flag of the specified window.
	 *  This can be used to override the user's attempt to close the window, or
	 *  to signal that it should be closed.
	 *
	 *  @param[in] value The new value.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function may be called from any thread.  Access is not
	 *  synchronized.
	 */
	void setShouldClose(bool value) {
		glfwSetWindowShouldClose(win_, (value ? GLFW_TRUE : GLFW_FALSE));
	}

	/*! @brief Sets the title of the specified window.
	 *
	 *  This function sets the window title, encoded as UTF-8, of the specified
	 *  window.
	 *
	 *  @param[in] title The UTF-8 encoded window title.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setTitle(const char* title) {
		glfwSetWindowTitle(win_, title);
	}

	/*! @brief Sets the icon for the specified window.
	 *
	 *  This function sets the icon of the specified window.  If passed an array of
	 *  candidate images, those of or closest to the sizes desired by the system are
	 *  selected.  If no images are specified, the window reverts to its default
	 *  icon.
	 *
	 *  The desired image sizes varies depending on platform and system settings.
	 *  The selected images will be rescaled as needed.  Good sizes include 16x16,
	 *  32x32 and 48x48.
	 *
	 *  @param[in] count The number of images in the specified array, or zero to
	 *  revert to the default window icon.
	 *  @param[in] images The images to create the icon from.  This is ignored if
	 *  count is zero.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The specified image data is copied before this function
	 *  returns.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setIcon(int count, const Image* images) {
		glfwSetWindowIcon(win_, count, images);
	}

	/*! @brief Retrieves the position of the client area of the window.
	 *
	 *  This function retrieves the position, in screen coordinates, of the
	 *  upper-left corner of the client area of the specified window.
	 *
	 *  Any or all of the position arguments may be `nullptr`.
	 *
	 *  @param[out] xpos Where to store the x-coordinate of the upper-left corner of
	 *  the client area, or `nullptr`.
	 *  @param[out] ypos Where to store the y-coordinate of the upper-left corner of
	 *  the client area, or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void getPos(int* xpos, int* ypos) {
		glfwGetWindowPos(win_, xpos, ypos);
	}
	
	/*! @brief Retrieves the position of the client area of the window as a Point2D.
	 *
	 *  This function retrieves the position, in screen coordinates, of the
	 *  upper-left corner of the client area of the specified window.
	 *
	 *  @return Coordinates as a Point2D.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Point2D<int> getPos() {
		Point2D<int> point;
		glfwGetWindowPos(win_, &point.x, &point.y);
		return point;
	}
	
	/*! @brief Sets the position of the client area of the specified window.
	 *
	 *  This function sets the position, in screen coordinates, of the upper-left
	 *  corner of the client area of the specified windowed mode window.  If the
	 *  window is a full screen window, this function does nothing.
	 *
	 *  __Do not use this function__ to move an already visible window unless you
	 *  have very good reasons for doing so, as it will confuse and annoy the user.
	 *
	 *  The window manager may put limits on what positions are allowed.  GLFW
	 *  cannot and should not override these limits.
	 *
	 *  @param[in] xpos The x-coordinate of the upper-left corner of the client area.
	 *  @param[in] ypos The y-coordinate of the upper-left corner of the client area.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setPos(int xpos, int ypos) {
		glfwSetWindowPos(win_, xpos, ypos);
	}
	
	/*! @brief Sets the position of the client area of the specified window.
	 *
	 *  This function sets the position, as a Point2D, of the upper-left
	 *  corner of the client area of the specified windowed mode window.  If the
	 *  window is a full screen window, this function does nothing.
	 *
	 *  __Do not use this function__ to move an already visible window unless you
	 *  have very good reasons for doing so, as it will confuse and annoy the user.
	 *
	 *  The window manager may put limits on what positions are allowed.  GLFW
	 *  cannot and should not override these limits.
	 *
	 *  @param[in] point The Point2D of the upper-left corner of the client area.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setPos(Point2D<int>& point) {
		glfwSetWindowPos(win_, point.x, point.y);
	}
	
	/*! @brief Retrieves the size of the client area of the window.
	 *
	 *  This function retrieves the size, in screen coordinates, of the client area
	 *  of the specified window.  If you wish to retrieve the size of the
	 *  framebuffer of the window in pixels, see @ref glfwGetFramebufferSize.
	 *
	 *  Any or all of the size arguments may be `nullptr`.
	 *
	 *  @param[out] width Where to store the width, in screen coordinates, of the
	 *  client area, or `nullptr`.
	 *  @param[out] height Where to store the height, in screen coordinates, of the
	 *  client area, or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void getSize(int* width, int* height) {
		glfwGetWindowSize(win_, width, height);
	}
	
	/*! @brief Retrieves the size of the client area of the window.
	 *
	 *  This function retrieves the size, as a Size2D, of the client area
	 *  of the specified window.  If you wish to retrieve the size of the
	 *  framebuffer of the window in pixels, see @ref glfwGetFramebufferSize.
	 *
	 *  @return Coordinates as a Size2D.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Size2D getSize() {
		Size2D size;
		glfwGetWindowSize(win_, &size.width, &size.height);
		return size;
	}
	
	/*! @brief Sets the size limits of the window.
	 *
	 *  This function sets the size limits of the client area of the specified
	 *  window.  If the window is full screen, the size limits only take effect
	 *  once it is made windowed.  If the window is not resizable, this function
	 *  does nothing.
	 *
	 *  The size limits are applied immediately to a windowed mode window and may
	 *  cause it to be resized.
	 *
	 *  The maximum dimensions must be greater than or equal to the minimum
	 *  dimensions and all must be greater than or equal to zero.
	 *
	 *  @param[in] minwidth The minimum width, in screen coordinates, of the client
	 *  area, or `ValueDontCare`.
	 *  @param[in] minheight The minimum height, in screen coordinates, of the
	 *  client area, or `ValueDontCare`.
	 *  @param[in] maxwidth The maximum width, in screen coordinates, of the client
	 *  area, or `ValueDontCare`.
	 *  @param[in] maxheight The maximum height, in screen coordinates, of the
	 *  client area, or `ValueDontCare`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidValue and @ref ErrorCode::PlatformError.
	 *
	 *  @remark If you set size limits and an aspect ratio that conflict, the
	 *  results are undefined.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight) {
		glfwSetWindowSizeLimits(win_, minwidth, minheight, maxwidth, maxheight);
	}

	/*! @brief Sets the aspect ratio of the window.
	 *
	 *  This function sets the required aspect ratio of the client area of the
	 *  specified window.  If the window is full screen, the aspect ratio only takes
	 *  effect once it is made windowed.  If the window is not resizable, this
	 *  function does nothing.
	 *
	 *  The aspect ratio is specified as a numerator and a denominator and both
	 *  values must be greater than zero.  For example, the common 16:9 aspect ratio
	 *  is specified as 16 and 9, respectively.
	 *
	 *  If the numerator and denominator is set to `ValueDontCare` then the aspect
	 *  ratio limit is disabled.
	 *
	 *  The aspect ratio is applied immediately to a windowed mode window and may
	 *  cause it to be resized.
	 *
	 *  @param[in] numer The numerator of the desired aspect ratio, or `ValueDontCare`.
	 *  @param[in] denom The denominator of the desired aspect ratio, or `ValueDontCare`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidValue and @ref ErrorCode::PlatformError.
	 *
	 *  @remark If you set size limits and an aspect ratio that conflict, the
	 *  results are undefined.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setAspectRatio(int numer, int denom) {
		glfwSetWindowAspectRatio(win_, numer, denom);
	}

	/*! @brief Sets the size of the client area of the window.
	 *
	 *  This function sets the size, in screen coordinates, of the client area of
	 *  the specified window.
	 *
	 *  For full screen windows, this function updates the resolution of its desired
	 *  video mode and switches to the video mode closest to it, without affecting
	 *  the window's context.  As the context is unaffected, the bit depths of the
	 *  framebuffer remain unchanged.
	 *
	 *  If you wish to update the refresh rate of the desired video mode in addition
	 *  to its resolution, see @ref glfwSetWindowMonitor.
	 *
	 *  The window manager may put limits on what sizes are allowed.  GLFW cannot
	 *  and should not override these limits.
	 *
	 *  @param[in] width The desired width, in screen coordinates, of the window
	 *  client area.
	 *  @param[in] height The desired height, in screen coordinates, of the window
	 *  client area.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setSize(int width, int height) {
	   glfwSetWindowSize(win_, width, height);
	}
	
	/*! @brief Sets the size of the client area of the specified window.
	 *
	 *  This function sets the size, as a Size2D, of the client area of
	 *  the specified window.
	 *
	 *  For full screen windows, this function updates the resolution of its desired
	 *  video mode and switches to the video mode closest to it, without affecting
	 *  the window's context.  As the context is unaffected, the bit depths of the
	 *  framebuffer remain unchanged.
	 *
	 *  If you wish to update the refresh rate of the desired video mode in addition
	 *  to its resolution, see @ref glfwSetWindowMonitor.
	 *
	 *  The window manager may put limits on what sizes are allowed.  GLFW cannot
	 *  and should not override these limits.
	 *
	 *  @return Coordinates as a Size2D.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setSize(Size2D size) {
	   glfwSetWindowSize(win_, size.width, size.height);
	}
	
	/*! @brief Retrieves the size of the framebuffer of the specified window.
	 *
	 *  This function retrieves the size, in pixels, of the framebuffer of the
	 *  specified window.  If you wish to retrieve the size of the window in screen
	 *  coordinates, see @ref glfwGetWindowSize.
	 *
	 *  Any or all of the size arguments may be `nullptr`.  If an error occurs, all
	 *  non-`nullptr` size arguments will be set to zero.
	 *
	 *  @param[out] width Where to store the width, in pixels, of the framebuffer,
	 *  or `nullptr`.
	 *  @param[out] height Where to store the height, in pixels, of the framebuffer,
	 *  or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void getFramebufferSize(int* width, int* height) {
		glfwGetFramebufferSize(win_, width, height);
	}
	
	/*! @brief Retrieves the size of the framebuffer of the specified window.
	 *
	 *  This function retrieves the size, in pixels, of the framebuffer of the
	 *  specified window.  If you wish to retrieve the size of the window in screen
	 *  coordinates, see @ref glfwGetWindowSize.
	 *
	 *  @return Coordinates as a Point2D.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Size2D getFramebufferSize() {
		Size2D size;
		glfwGetFramebufferSize(win_, &size.width, &size.height);
		return size;
	}

	/*! @brief Retrieves the size of the frame of the window.
	 *
	 *  This function retrieves the size, in screen coordinates, of each edge of the
	 *  frame of the specified window.  This size includes the title bar, if the
	 *  window has one.  The size of the frame may vary depending on the
	 *  [window-related hints](@ref window_hints_wnd) used to create it.
	 *
	 *  Because this function retrieves the size of each window frame edge and not
	 *  the offset along a particular coordinate axis, the retrieved values will
	 *  always be zero or positive.
	 *
	 *  Any or all of the size arguments may be `nullptr`.
	 *
	 *  @param[out] left Where to store the size, in screen coordinates, of the left
	 *  edge of the window frame, or `nullptr`.
	 *  @param[out] top Where to store the size, in screen coordinates, of the top
	 *  edge of the window frame, or `nullptr`.
	 *  @param[out] right Where to store the size, in screen coordinates, of the
	 *  right edge of the window frame, or `nullptr`.
	 *  @param[out] bottom Where to store the size, in screen coordinates, of the
	 *  bottom edge of the window frame, or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
 	void getFrameSize(int* left, int* top, int* right, int* bottom) {
 		glfwGetWindowFrameSize(win_, left, top, right, bottom);
 	}
	
	/*! @brief Retrieves the size of the frame of the window.
	 *
	 *  This function retrieves the size, in screen coordinates, of each edge of the
	 *  frame of the specified window.  This size includes the title bar, if the
	 *  window has one.  The size of the frame may vary depending on the
	 *  [window-related hints](@ref window_hints_wnd) used to create it.
	 *
	 *  Because this function retrieves the size of each window frame edge and not
	 *  the offset along a particular coordinate axis, the retrieved values will
	 *  always be zero or positive.
	 *
	 *  @return The size as an Area2D.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
 	Area2D getFrameSize() {
		Area2D area;
 		glfwGetWindowFrameSize(win_, &area.left, &area.top, &area.right, &area.bottom);
		return area;
 	}
	
	/*! @brief Iconifies the specified window.
	 *
	 *  This function iconifies (minimizes) the specified window if it was
	 *  previously restored.  If the window is already iconified, this function does
	 *  nothing.
	 *
	 *  If the specified window is a full screen window, the original monitor
	 *  resolution is restored until the window is restored.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void iconify() {
		glfwIconifyWindow(win_);
	}

	/*! @brief Restores the specified window.
	 *
	 *  This function restores the specified window if it was previously iconified
	 *  (minimized) or maximized.  If the window is already restored, this function
	 *  does nothing.
	 *
	 *  If the specified window is a full screen window, the resolution chosen for
	 *  the window is restored on the selected monitor.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void restore() {
		glfwRestoreWindow(win_);
	}

	/*! @brief Maximizes the specified window.
	 *
	 *  This function maximizes the specified window if it was previously not
	 *  maximized.  If the window is already maximized, this function does nothing.
	 *
	 *  If the specified window is a full screen window, this function does nothing.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void maximize() {
		glfwMaximizeWindow(win_);
	}

	/*! @brief Makes the specified window visible.
	 *
	 *  This function makes the specified window visible if it was previously
	 *  hidden.  If the window is already visible or is in full screen mode, this
	 *  function does nothing.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void show() {
		glfwShowWindow(win_);
	}

	/*! @brief Hides the specified window.
	 *
	 *  This function hides the specified window if it was previously visible.  If
	 *  the window is already hidden or is in full screen mode, this function does
	 *  nothing.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void hide() {
		glfwHideWindow(win_);
	}

	/*! @brief Brings the specified window to front and sets input focus.
	 *
	 *  This function brings the specified window to front and sets input focus.
	 *  The window should already be visible and not iconified.
	 *
	 *  By default, both windowed and full screen mode windows are focused when
	 *  initially created.  Set the [GLFW_FOCUSED](@ref window_hints_wnd) to disable
	 *  this behavior.
	 *
	 *  __Do not use this function__ to steal focus from other applications unless
	 *  you are certain that is what the user wants.  Focus stealing can be
	 *  extremely disruptive.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void focus() {
		glfwFocusWindow(win_);
	}

	/*! @brief Returns the monitor that the window uses for full screen mode.
	 *
	 *  This function returns a unique_ptr to a Monitor object encapsulating
	 *  the monitor that the window is in full screen on.
	 *
	 *  @return The monitor (as unique_ptr), or `nullptr` if the window is in
	 *  windowed mode or an [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	std::unique_ptr<Monitor> getMonitor();
	
	/*! @brief Sets the mode, monitor, video mode and placement of a window.
	 *
	 *  This function sets the monitor that the window uses for full screen mode or,
	 *  if the monitor is `nullptr`, makes it windowed mode.
	 *
	 *  When setting a monitor, this function updates the width, height and refresh
	 *  rate of the desired video mode and switches to the video mode closest to it.
	 *  The window position is ignored when setting a monitor.
	 *
	 *  When the monitor is `nullptr`, the position, width and height are used to
	 *  place the window client area.  The refresh rate is ignored when no monitor
	 *  is specified.
	 *
	 *  If you only wish to update the resolution of a full screen window or the
	 *  size of a windowed mode window, see @ref glfwSetWindowSize.
	 *
	 *  When a window transitions from full screen to windowed mode, this function
	 *  restores any previous window settings such as whether it is decorated,
	 *  floating, resizable, has size or aspect ratio limits, etc..
	 *
	 *  @param[in] monitor The desired monitor, or `nullptr` to set windowed mode.
	 *  @param[in] xpos The desired x-coordinate of the upper-left corner of the
	 *  client area.
	 *  @param[in] ypos The desired y-coordinate of the upper-left corner of the
	 *  client area.
	 *  @param[in] width The desired with, in screen coordinates, of the client area
	 *  or video mode.
	 *  @param[in] height The desired height, in screen coordinates, of the client
	 *  area or video mode.
	 *  @param[in] refreshRate The desired refresh rate, in Hz, of the video mode,
	 *  or `ValueDontCare`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setMonitor(Monitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
	
	/*! @brief Returns an attribute of the specified window.
	 *
	 *  This function returns the value of an attribute of the specified window or
	 *  its OpenGL or OpenGL ES context.
	 *
	 *  @param[in] attrib The [window attribute](@ref window_attribs) whose value to
	 *  return.
	 *  @return The value of the attribute as type T.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
	 *
	 *  @remark Framebuffer related hints are not window attributes.  See @ref
	 *  window_attribs_fb for more information.
	 *
	 *  @remark Zero is a valid value for many window and context related
	 *  attributes so you cannot use a return value of zero as an indication of
	 *  errors.  However, this function should not fail as long as it is passed
	 *  valid arguments and the library has been [initialized](@ref intro_init).
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	template <class T = int>
	T getAttrib(WindowAttribute attrib);
	
	/*! @brief Swaps the front and back buffers of the specified window.
	 *
	 *  This function swaps the front and back buffers of the specified window when
	 *  rendering with OpenGL or OpenGL ES.  If the swap interval is greater than
	 *  zero, the GPU driver waits the specified number of screen updates before
	 *  swapping the buffers.
	 *
	 *  The specified window must have an OpenGL or OpenGL ES context.  Specifying
	 *  a window without a context will generate a @ref ErrorCode::NoWindowContext
	 *  error.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::NoWindowContext and @ref ErrorCode::PlatformError.
	 *
	 *  @remark __EGL:__ The context of the specified window must be current on the
	 *  calling thread.
	 *
	 *  @thread_safety This function may be called from any thread.
	 */
	void swapBuffers() {
		glfwSwapBuffers(win_);
	}
	
	// No wrappers for the user pointer functions (glfw[SG]etWindowUserPointer())
	// because we need the user pointer to link the GLFWwindow to our Window object.
	
	// -- Callback setters
	
	/*! @brief Sets the position callback for the specified window.
	 *
	 *  This function sets the position callback of the specified window, which is
	 *  called when the window is moved.  The callback is provided with the screen
	 *  position of the upper-left corner of the client area of the window.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowPosCallback(windowPosCallbackFun_t cbFun);

	/*! @brief Sets the size callback for the specified window.
	 *
	 *  This function sets the size callback of the specified window, which is
	 *  called when the window is resized.  The callback is provided with the size,
	 *  in screen coordinates, of the client area of the window.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowSizeCallback(windowSizeCallbackFun_t cbFun);

	/*! @brief Sets the close callback for the specified window.
	 *
	 *  This function sets the close callback of the specified window, which is
	 *  called when the user attempts to close the window, for example by clicking
	 *  the close widget in the title bar.
	 *
	 *  The close flag is set before this callback is called, but you can modify it
	 *  at any time with @ref glfwSetWindowShouldClose.
	 *
	 *  The close callback is not triggered by @ref glfwDestroyWindow.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowCloseCallback(windowCloseCallbackFun_t cbFun);

	/*! @brief Sets the refresh callback for the specified window.
	 *
	 *  This function sets the refresh callback of the specified window, which is
	 *  called when the client area of the window needs to be redrawn, for example
	 *  if the window has been exposed after having been covered by another window.
	 *
	 *  On compositing window systems such as Aero, Compiz or Aqua, where the window
	 *  contents are saved off-screen, this callback may be called only very
	 *  infrequently or never at all.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowRefreshCallback(windowRefreshCallbackFun_t cbFun);

	/*! @brief Sets the focus callback for the specified window.
	 *
	 *  This function sets the focus callback of the specified window, which is
	 *  called when the window gains or loses input focus.
	 *
	 *  After the focus callback is called for a window that lost input focus,
	 *  synthetic key and mouse button release events will be generated for all such
	 *  that had been pressed.  For more information, see @ref glfwSetKeyCallback
	 *  and @ref glfwSetMouseButtonCallback.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowFocusCallback(windowFocusCallbackFun_t cbFun);

	/*! @brief Sets the iconify callback for the specified window.
	 *
	 *  This function sets the iconification callback of the specified window, which
	 *  is called when the window is iconified or restored.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setWindowIconifyCallback(windowIconifyCallbackFun_t cbFun);

	/*! @brief Sets the framebuffer resize callback for the specified window.
	 *
	 *  This function sets the framebuffer resize callback of the specified window,
	 *  which is called when the framebuffer of the specified window is resized.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setFramebufferSizeCallback(framebufferSizeCallbackFun_t cbFun);

	// -- Callback unsetters
	
	/*! @brief Deletes the position callback for the specified window. */
	void unsetWindowPosCallback() {
		setWindowPosCallback(nullptr);
	}

	/*! @brief Deletes the size callback for the specified window. */
	void unsetWindowSizeCallback() {
		setWindowSizeCallback(nullptr);
	}

	/*! @brief Deletes the close callback for the specified window. */
	void unsetWindowCloseCallback() {
		setWindowCloseCallback(nullptr);
	}

	/*! @brief Deletes the refresh callback for the specified window. */
	void unsetWindowRefreshCallback() {
		setWindowRefreshCallback(nullptr);
	}

	/*! @brief Deletes the focus callback for the specified window. */
	void unsetWindowFocusCallback() {
		setWindowFocusCallback(nullptr);
	}

	/*! @brief Deletes the iconify callback for the specified window. */
	void unsetWindowIconifyCallback() {
		setWindowIconifyCallback(nullptr);
	}

	/*! @brief Deletes the framebuffer resize callback for the specified window. */
	void unsetFramebufferSizeCallback() {
		setFramebufferSizeCallback(nullptr);
	}
	
	
	/*********************************************************************
	 * Wrappers for input related functions
	 *********************************************************************/

	/*! @brief Returns the value of an input option for the window.
	 *
	 *  This function returns the value of an input option for the specified window.
	 *
	 *  @param[in] mode One of `InputModeOption::Cursor`, `InputModeOption::StickyKeys`
	 *  or `InputModeOption::StickyMouseButtons`.
	 *  @return `CursorMode` for `InputModeOption::Cursor`, `bool` for the other modes.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::InvalidEnum.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	template <class T = int>
	T getInputMode(InputModeOption mode);

	/*! @brief Sets an input option for the specified window.
	 *
	 *  This function sets an input mode option for the specified window.  The mode
	 *  must be one of `InputModeOption::Cursor`, `InputModeOption::StickyKeys`
	 *  or `InputModeOption::StickyMouseButtons`.
	 *
	 *  If the mode is `InputModeOption::Cursor`, the value must be one of the
	 *  following cursor modes:
	 *  - `CursorMode::Normal` makes the cursor visible and behaving normally.
	 *  - `CursorMode::Hidden` makes the cursor invisible when it is over the client
	 *    area of the window but does not restrict the cursor from leaving.
	 *  - `CursorMode::Disabled` hides and grabs the cursor, providing virtual
	 *    and unlimited cursor movement.  This is useful for implementing for
	 *    example 3D camera controls.
	 *
	 *  If the mode is `InputModeOption::StickyKeys`, the value must be either
	 *  `true` to enable sticky keys, or `false` to disable it.  If sticky keys are
	 *  enabled, a key press will ensure that @ref glfwGetKey returns
	 *  `InputAction::Press` the next time it is called even if the key had been
	 *  released before the call.  This is useful when you are only interested in
	 *  whether keys have been pressed but not when or in which order.
	 *
	 *  If the mode is `InputModeOption::StickyMouseButtons`, the value must be either
	 *  `true` to enable sticky mouse buttons, or `false` to disable it.
	 *  If sticky mouse buttons are enabled, a mouse button press will ensure that
	 *  @ref glfwGetMouseButton returns `InputAction::Press` the next time it is
	 *  called even if the mouse button had been released before the call.  This is
	 *  useful when you are only interested in whether mouse buttons have been pressed
	 *  but not when or in which order.
	 *
	 *  @param[in] mode One of `InputModeOption::Cursor`, `InputModeOption::StickyKeys`
	 *  or `InputModeOption::StickyMouseButtons`.
	 *  @param[in] value The new value of the specified input mode.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	template <class T>
	void setInputMode(InputModeOption mode, T value) {
		glfwSetInputMode(win_, static_cast<int>(mode), static_cast<int>(value));
	}

	/*! @brief Returns the last reported state of a keyboard key for the specified
	 *  window.
	 *
	 *  This function returns the last state reported for the specified key to the
	 *  specified window.  The returned state is one of `InputAction::Press` or
	 *  `InputAction::Release`.  The higher-level action `InputAction::Repeat` is
	 *  only reported to the key callback.
	 *
	 *  If the `InputModeOption::StickyKeys` input mode is enabled, this function
	 *  returns `InputAction::Press` the first time you call it for a key that was
	 *  pressed, even if that key has already been released.
	 *
	 *  The key functions deal with physical keys, with [key tokens](@ref keys)
	 *  named after their use on the standard US keyboard layout.  If you want to
	 *  input text, use the Unicode character callback instead.
	 *
	 *  The [modifier key bit masks](@ref mods) are not key tokens and cannot be
	 *  used with this function.
	 *
	 *  __Do not use this function__ to implement [text input](@ref input_char).
	 *
	 *  @param[in] key The desired [keyboard key](@ref keys).  `KeyCode::Unknown` is
	 *  not a valid key for this function.
	 *  @return One of `InputAction::Press` or `InputAction::Release`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::InvalidEnum.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	InputAction getKey(KeyCode key) {
		return static_cast<InputAction>(glfwGetKey(win_, static_cast<int>(key)));
	}

	/*! @brief Returns the last reported state of a mouse button.
	 *
	 *  This function returns the last state reported for the specified mouse
	 *  button to the window.  The returned state is one of `InputAction::Press`
	 *  or `InputAction::Release`.
	 *
	 *  If the `InputModeOption::StickyMouseButtons` input mode is enabled, this
	 *  function returns `InputAction::Press` the first time you call it for a mouse
	 *  button that was pressed, even if that mouse button has already been
	 *  released.
	 *
	 *  @param[in] button The desired [mouse button](@ref buttons).
	 *  @return One of `InputAction::Press` or `InputAction::Release`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::InvalidEnum.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	InputAction getMouseButton(MouseButton button) {
		return static_cast<InputAction>(glfwGetMouseButton(win_, static_cast<int>(button)));
	}

	/*! @brief Retrieves the position of the cursor relative to the client area of
	 *  the window.
	 *
	 *  This function returns the position of the cursor, in screen coordinates,
	 *  relative to the upper-left corner of the client area of the specified
	 *  window.
	 *
	 *  If the cursor is disabled (with `CursorMode::Disabled`) then the cursor
	 *  position is unbounded and limited only by the minimum and maximum values of
	 *  a `double`.
	 *
	 *  The coordinate can be converted to their integer equivalents with the
	 *  `floor` function.  Casting directly to an integer type works for positive
	 *  coordinates, but fails for negative ones.
	 *
	 *  Any or all of the position arguments may be `nullptr`.
	 *
	 *  @param[out] xpos Where to store the cursor x-coordinate, relative to the
	 *  left edge of the client area, or `nullptr`.
	 *  @param[out] ypos Where to store the cursor y-coordinate, relative to the to
	 *  top edge of the client area, or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void getCursorPos(double* xpos, double* ypos) {
		glfwGetCursorPos(win_, xpos, ypos);
	}
	
	/*! @brief Retrieves the position of the cursor relative to the client area of
	 *  the window.
	 *
	 *  This function returns the position of the cursor, in screen coordinates,
	 *  relative to the upper-left corner of the client area of the specified
	 *  window.
	 *
	 *  If the cursor is disabled (with `GLFW_CURSOR_DISABLED`) then the cursor
	 *  position is unbounded and limited only by the minimum and maximum values of
	 *  a `double`.
	 *
	 *  The coordinate can be converted to their integer equivalents with the
	 *  `floor` function.  Casting directly to an integer type works for positive
	 *  coordinates, but fails for negative ones.
	 *
	 *  @return The cursor position as a Point2D<double>.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Point2D<double> getCursorPos() {
		Point2D<double> point;
		glfwGetCursorPos(win_, &point.x, &point.y);
		return point;
	}
		
	/*! @brief Sets the position of the cursor, relative to the client area of the
	 *  window.
	 *
	 *  This function sets the position, in screen coordinates, of the cursor
	 *  relative to the upper-left corner of the client area of the specified
	 *  window.  The window must have input focus.  If the window does not have
	 *  input focus when this function is called, it fails silently.
	 *
	 *  __Do not use this function__ to implement things like camera controls.  GLFW
	 *  already provides the `CursorMode::Disabled` cursor mode that hides the
	 *  cursor, transparently re-centers it and provides unconstrained cursor
	 *  motion.  See @ref glfwSetInputMode for more information.
	 *
	 *  If the cursor mode is `CursorMode::Disabled` then the cursor position is
	 *  unconstrained and limited only by the minimum and maximum values of
	 *  a `double`.
	 *
	 *  @param[in] point The cursor position as a Point2D<double>.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCursorPos(Point2D<double>& point) {
		glfwSetCursorPos(win_, point.x, point.y);
	}

	/*! @brief Sets the cursor for the window.
	 *
	 *  This function sets the cursor image to be used when the cursor is over the
	 *  client area of the specified window.  The set cursor will only be visible
	 *  when the [cursor mode](@ref cursor_mode) of the window is
	 *  `CursorMode::Normal`.
	 *
	 *  On some platforms, the set cursor may not be visible unless the window also
	 *  has input focus.
	 *
	 *  @param[in] cursor The cursor to set, or `nullptr` to switch back to the
	 *  default arrow cursor.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCursor(Cursor* cursor);
	
	/*! @brief Unsets the cursor for the window. */
	void unsetCursor() {
		setCursor(nullptr);
	}
	
	/*! @brief Sets the clipboard to the specified string.
	 *
	 *  This function sets the system clipboard to the specified, UTF-8 encoded
	 *  string.
	 *
	 *  @param[in] string A UTF-8 encoded string.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The specified string is copied before this function
	 *  returns.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setClipboardString(const char* string) {
		glfwSetClipboardString(win_, string);
	}
	
	/*! @brief Returns the contents of the clipboard as a string.
	 *
	 *  This function returns the contents of the system clipboard, if it contains
	 *  or is convertible to a UTF-8 encoded string.  If the clipboard is empty or
	 *  if its contents cannot be converted, `nullptr` is returned and a @ref
	 *  ErrorCode::FormatUnavailable error is generated.
	 *
	 *  @return The contents of the clipboard as a UTF-8 encoded string, or `nullptr`
	 *  if an [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
	 *  should not free it yourself.  It is valid until the next call to @ref
	 *  glfwGetClipboardString or @ref glfwSetClipboardString, or until the library
	 *  is terminated.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	const char* getClipboardString() {
		return glfwGetClipboardString(win_);
	}
	
	// -- Callback setters
	
	/*! @brief Sets the key callback.
	 *
	 *  This function sets the key callback of the specified window, which is called
	 *  when a key is pressed, repeated or released.
	 *
	 *  The key functions deal with physical keys, with layout independent
	 *  [key tokens](@ref keys) named after their values in the standard US keyboard
	 *  layout.  If you want to input text, use the
	 *  [character callback](@ref glfwSetCharCallback) instead.
	 *
	 *  When a window loses input focus, it will generate synthetic key release
	 *  events for all pressed keys.  You can tell these events from user-generated
	 *  events by the fact that the synthetic ones are generated after the focus
	 *  loss event has been processed, i.e. after the
	 *  [window focus callback](@ref glfwSetWindowFocusCallback) has been called.
	 *
	 *  The scancode of a key is specific to that platform or sometimes even to that
	 *  machine.  Scancodes are intended to allow users to bind keys that don't have
	 *  a GLFW key token.  Such keys have `key` set to `KeyCode::Unknown`, their
	 *  state is not saved and so it cannot be queried with @ref glfwGetKey.
	 *
	 *  Sometimes GLFW needs to generate synthetic key events, in which case the
	 *  scancode may be zero.
	 *
	 *  @param[in] cbfun The new key callback, or `nullptr` to remove the currently
	 *  set callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setKeyCallback(keyCallbackFun_t cbFun);
	
	/*! @brief Sets the Unicode character callback.
	 *
	 *  This function sets the character callback of the specified window, which is
	 *  called when a Unicode character is input.
	 *
	 *  The character callback is intended for Unicode text input.  As it deals with
	 *  characters, it is keyboard layout dependent, whereas the
	 *  [key callback](@ref glfwSetKeyCallback) is not.  Characters do not map 1:1
	 *  to physical keys, as a key may produce zero, one or more characters.  If you
	 *  want to know whether a specific physical key was pressed or released, see
	 *  the key callback instead.
	 *
	 *  The character callback behaves as system text input normally does and will
	 *  not be called if modifier keys are held down that would prevent normal text
	 *  input on that platform, for example a Super (Command) key on OS X or Alt key
	 *  on Windows.  There is a
	 *  [character with modifiers callback](@ref glfwSetCharModsCallback) that
	 *  receives these events.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCharCallback(charCallbackFun_t cbFun);

	/*! @brief Sets the Unicode character with modifiers callback.
	 *
	 *  This function sets the character with modifiers callback of the specified
	 *  window, which is called when a Unicode character is input regardless of what
	 *  modifier keys are used.
	 *
	 *  The character with modifiers callback is intended for implementing custom
	 *  Unicode character input.  For regular Unicode text input, see the
	 *  [character callback](@ref glfwSetCharCallback).  Like the character
	 *  callback, the character with modifiers callback deals with characters and is
	 *  keyboard layout dependent.  Characters do not map 1:1 to physical keys, as
	 *  a key may produce zero, one or more characters.  If you want to know whether
	 *  a specific physical key was pressed or released, see the
	 *  [key callback](@ref glfwSetKeyCallback) instead.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *  @return The previously set callback, or `nullptr` if no callback was set or an
	 *  [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCharModsCallback(charModsCallbackFun_t cbFun);

	/*! @brief Sets the mouse button callback.
	 *
	 *  This function sets the mouse button callback of the specified window, which
	 *  is called when a mouse button is pressed or released.
	 *
	 *  When a window loses input focus, it will generate synthetic mouse button
	 *  release events for all pressed mouse buttons.  You can tell these events
	 *  from user-generated events by the fact that the synthetic ones are generated
	 *  after the focus loss event has been processed, i.e. after the
	 *  [window focus callback](@ref glfwSetWindowFocusCallback) has been called.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setMouseButtonCallback(mouseButtonCallbackFun_t cbFun);

	/*! @brief Sets the cursor position callback.
	 *
	 *  This function sets the cursor position callback of the specified window,
	 *  which is called when the cursor is moved.  The callback is provided with the
	 *  position, in screen coordinates, relative to the upper-left corner of the
	 *  client area of the window.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCursorPosCallback(cursorPosCallbackFun_t cbFun);

	/*! @brief Sets the cursor enter/exit callback.
	 *
	 *  This function sets the cursor boundary crossing callback of the specified
	 *  window, which is called when the cursor enters or leaves the client area of
	 *  the window.
	 *
	 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
	 *  callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setCursorEnterCallback(cursorEnterCallbackFun_t cbFun);

	/*! @brief Sets the scroll callback.
	 *
	 *  This function sets the scroll callback of the specified window, which is
	 *  called when a scrolling device is used, such as a mouse wheel or scrolling
	 *  area of a touchpad.
	 *
	 *  The scroll callback receives all scrolling input, like that from a mouse
	 *  wheel or a touchpad scrolling area.
	 *
	 *  @param[in] cbfun The new scroll callback, or `nullptr` to remove the currently
	 *  set callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setScrollCallback(scrollCallbackFun_t cbFun);

	/*! @brief Sets the file drop callback.
	 *
	 *  This function sets the file drop callback of the specified window, which is
	 *  called when one or more dragged files are dropped on the window.
	 *
	 *  Because the path array and its strings may have been generated specifically
	 *  for that event, they are not guaranteed to be valid after the callback has
	 *  returned.  If you wish to use them after the callback returns, you need to
	 *  make a deep copy.
	 *
	 *  @param[in] cbfun The new file drop callback, or `nullptr` to remove the
	 *  currently set callback.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setDropCallback(dropCallbackFun_t cbFun);
	
	// -- Callback unsetters
	
	/*! @brief Deletes the key callback. */
	void unsetKeyCallback() {
		setKeyCallback(nullptr);
	}
	
	/*! @brief Deletes the Unicode character callback. */
	void unsetCharCallback() {
		setCharCallback(nullptr);
	}
	
	/*! @brief Deletes the Unicode character with modifiers callback. */
	void unsetCharModsCallback() {
		setCharModsCallback(nullptr);
	}
	
	/*! @brief Deletes the mouse button callback. */
	void unsetMouseButtonCallback() {
		setMouseButtonCallback(nullptr);
	}
	
	/*! @brief Deletes the cursor position callback. */
	void unsetCursorPosCallback() {
		setCursorPosCallback(nullptr);
	}
	
	/*! @brief Deletes the cursor enter/exit callback. */
	void unsetCursorEnterCallback() {
		setCursorEnterCallback(nullptr);
	}

	/*! @brief Deletes the scroll callback. */
	void unsetScrollCallback() {
		setScrollCallback(nullptr);
	}

	/*! @brief Deletes the file drop callback. */
	void unsetDropCallback() {
		setDropCallback(nullptr);
	}
};


/*! @brief Resets all window hints to their default values.
 *
 *  This function resets all window hints to their
 *  [default values](@ref window_hints_values).
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline void defaultWindowHints() {
	glfwDefaultWindowHints();
}

/*! @brief Sets the specified window hint to the desired value.
 *
 *  This function sets hints for the next call to @ref glfwCreateWindow.  The
 *  hints, once set, retain their values until changed by a call to @ref
 *  glfwWindowHint or @ref glfwDefaultWindowHints, or until the library is
 *  terminated.
 *
 *  This function does not check whether the specified hint values are valid.
 *  If you set hints to invalid values this will instead be reported by the next
 *  call to @ref glfwCreateWindow.
 *
 *  @param[in] hint The [window hint](@ref window_hints) to set.
 *  @param[in] value The new value of the window hint.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::InvalidEnum.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
template <class T>
inline void setWindowHint(WindowHint hint, T value) {
	glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
}

/*! @brief Processes all pending events.
 *
 *  This function processes only those events that are already in the event
 *  queue and then returns immediately.  Processing events will cause the window
 *  and input callbacks associated with those events to be called.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  On some platforms, certain events are sent directly to the application
 *  without going through the event queue, causing callbacks to be called
 *  outside of a call to one of the event processing functions.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::PlatformError.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline void pollEvents() {
	glfwPollEvents();
}

/*! @brief Waits until events are queued and processes them.
 *
 *  This function puts the calling thread to sleep until at least one event is
 *  available in the event queue.  Once one or more events are available,
 *  it behaves exactly like @ref glfwPollEvents, i.e. the events in the queue
 *  are processed and the function then returns immediately.  Processing events
 *  will cause the window and input callbacks associated with those events to be
 *  called.
 *
 *  Since not all events are associated with callbacks, this function may return
 *  without a callback having been called even if you are monitoring all
 *  callbacks.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  On some platforms, certain callbacks may be called outside of a call to one
 *  of the event processing functions.
 *
 *  If no windows exist, this function returns immediately.  For synchronization
 *  of threads in applications that do not create windows, use your threading
 *  library of choice.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::PlatformError.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline void waitEvents() {
	glfwWaitEvents();
}

/*! @brief Waits with timeout until events are queued and processes them.
 *
 *  This function puts the calling thread to sleep until at least one event is
 *  available in the event queue, or until the specified timeout is reached.  If
 *  one or more events are available, it behaves exactly like @ref
 *  glfwPollEvents, i.e. the events in the queue are processed and the function
 *  then returns immediately.  Processing events will cause the window and input
 *  callbacks associated with those events to be called.
 *
 *  The timeout value must be a positive finite number.
 *
 *  Since not all events are associated with callbacks, this function may return
 *  without a callback having been called even if you are monitoring all
 *  callbacks.
 *
 *  On some platforms, a window move, resize or menu operation will cause event
 *  processing to block.  This is due to how event processing is designed on
 *  those platforms.  You can use the
 *  [window refresh callback](@ref window_refresh) to redraw the contents of
 *  your window when necessary during such operations.
 *
 *  On some platforms, certain callbacks may be called outside of a call to one
 *  of the event processing functions.
 *
 *  If no windows exist, this function returns immediately.  For synchronization
 *  of threads in applications that do not create windows, use your threading
 *  library of choice.
 *
 *  Event processing is not required for joystick input to work.
 *
 *  @param[in] timeout The maximum amount of time, in seconds, to wait.
 *
 *  @reentrancy This function must not be called from a callback.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline void waitEventsTimeout(double timeout) {
	glfwWaitEventsTimeout(timeout);
}

/*! @brief Posts an empty event to the event queue.
 *
 *  This function posts an empty event from the current thread to the event
 *  queue, causing @ref glfwWaitEvents or @ref glfwWaitEventsTimeout to return.
 *
 *  If no windows exist, this function returns immediately.  For synchronization
 *  of threads in applications that do not create windows, use your threading
 *  library of choice.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::PlatformError.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline void postEmptyEvent() {
	glfwPostEmptyEvent();
}


/*************************************************************************
 * Wrappers for context related functions
 *************************************************************************/

/*! @brief Makes the context of the specified window current for the calling
 *  thread.
 *
 *  This function makes the OpenGL or OpenGL ES context of the specified window
 *  current on the calling thread.  A context can only be made current on
 *  a single thread at a time and each thread can have only a single current
 *  context at a time.
 *
 *  By default, making a context non-current implicitly forces a pipeline flush.
 *  On machines that support `GL_KHR_context_flush_control`, you can control
 *  whether a context performs this flush by setting the
 *  [ContextReleaseBehavior](@ref window_hints_ctx) window hint.
 *
 *  The specified window must have an OpenGL or OpenGL ES context.  Specifying
 *  a window without a context will generate a @ref ErrorCode::NoWindowContext
 *  error.
 *
 *  @param[in] window The window whose context to make current, or `nullptr` to
 *  detach the current context.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::NoWindowContext and @ref ErrorCode::PlatformError.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline void makeContextCurrent(Window& win) {
	glfwMakeContextCurrent(win.getPointer());
}

/*! @brief Detach the current context from the calling thread.
 *
 *  This function detaches the current OpenGL or OpenGL ES context from the
 *  calling thread.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized,
 *  @ref ErrorCode::PlatformError.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline void detachCurrentContext() {
	glfwMakeContextCurrent(nullptr);
}

/*! @brief Returns the window whose context is current on the calling thread.
 *
 *  This function returns the window whose OpenGL or OpenGL ES context is
 *  current on the calling thread.
 *
 *  @return The window whose context is current, or `nullptr` if no window's
 *  context is current.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function may be called from any thread.
 */
Window* getCurrentContext();

/*! @brief Sets the swap interval for the current context.
 *
 *  This function sets the swap interval for the current OpenGL or OpenGL ES
 *  context, i.e. the number of screen updates to wait from the time @ref
 *  glfwSwapBuffers was called before swapping the buffers and returning.  This
 *  is sometimes called _vertical synchronization_, _vertical retrace
 *  synchronization_ or just _vsync_.
 *
 *  Contexts that support either of the `WGL_EXT_swap_control_tear` and
 *  `GLX_EXT_swap_control_tear` extensions also accept negative swap intervals,
 *  which allow the driver to swap even if a frame arrives a little bit late.
 *  You can check for the presence of these extensions using @ref
 *  glfwExtensionSupported.  For more information about swap tearing, see the
 *  extension specifications.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref ErrorCode::NoCurrentContext error.
 *
 *  This function does not apply to Vulkan.  If you are rendering with Vulkan,
 *  see the present mode of your swapchain instead.
 *
 *  @param[in] interval The minimum number of screen updates to wait for
 *  until the buffers are swapped by @ref glfwSwapBuffers.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::NoCurrentContext and @ref ErrorCode::PlatformError.
 *
 *  @remark This function is not called during context creation, leaving the
 *  swap interval set to whatever is the default on that platform.  This is done
 *  because some swap interval extensions used by GLFW do not allow the swap
 *  interval to be reset to zero once it has been set to a non-zero value.
 *
 *  @remark Some GPU drivers do not honor the requested swap interval, either
 *  because of a user setting that overrides the application's request or due to
 *  bugs in the driver.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline void setSwapInterval(int interval) {
	glfwSwapInterval(interval);
}

/*! @brief Returns whether the specified extension is available.
 *
 *  This function returns whether the specified
 *  [API extension](@ref context_glext) is supported by the current OpenGL or
 *  OpenGL ES context.  It searches both for client API extension and context
 *  creation API extensions.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref ErrorCode::NoCurrentContext error.
 *
 *  As this functions retrieves and searches one or more extension strings each
 *  call, it is recommended that you cache its results if it is going to be used
 *  frequently.  The extension strings will not change during the lifetime of
 *  a context, so there is no danger in doing this.
 *
 *  This function does not apply to Vulkan.  If you are using Vulkan, see @ref
 *  glfwGetRequiredInstanceExtensions, `vkEnumerateInstanceExtensionProperties`
 *  and `vkEnumerateDeviceExtensionProperties` instead.
 *
 *  @param[in] extension The ASCII encoded name of the extension.
 *  @return `true` if the extension is available, or `false` otherwise.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::NoCurrentContext, @ref ErrorCode::InvalidValue and @ref
 *  ErrorCode::PlatformError.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline bool isExtensionSupported(const char* extension) {
	return (glfwExtensionSupported(extension) == GLFW_TRUE);
}

/*! @brief Returns the address of the specified function for the current
 *  context.
 *
 *  This function returns the address of the specified OpenGL or OpenGL ES
 *  [core or extension function](@ref context_glext), if it is supported
 *  by the current context.
 *
 *  A context must be current on the calling thread.  Calling this function
 *  without a current context will cause a @ref ErrorCode::NoCurrentContext error.
 *
 *  @param[in] procname The ASCII encoded name of the function.
 *  @return The address of the function, or `nullptr` if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::NoCurrentContext and @ref ErrorCode::PlatformError.
 *
 *  @remark The address of a given function is not guaranteed to be the same
 *  between contexts.
 *
 *  @remark This function may return a non-`nullptr` address despite the
 *  associated version or extension not being available.  Always check the
 *  context version or extension string first.
 *
 *  @pointer_lifetime The returned function pointer is valid until the context
 *  is destroyed or the library is terminated.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline glProcAddress_t getProcAddress(const char* procname) {
	return glfwGetProcAddress(procname);
}


/*************************************************************************
 * Monitor class
 *************************************************************************/

/*! @brief Monitor object wrapper.
 *
 *  Encapsulates a pointer to a GLFWmonitor. This class does not allocate
 *  memory for actual GLFWmonitor structs.
 */
class Monitor {
public:
	/*********************************************************************
	 * Construction, destruction, copy and move
	 *********************************************************************/
	
	/*! @brief Creates a Monitor object wrapping a pointer to a GLFWmonitor.
	 *
	 *  The Monitor class does not actually create `GLFWmonitor`s, as GLFW will
	 *  create those in glfwInit(). Thus, Monitor objects only encapsulate those
	 *  pointers without owning the actual data structures.
	 *
	 *  Users should actually not need to create Monitor objects on their own.
	 *
	 *  @param[in] monitor A GLFWmonitor* as returned by GLFW's functions.
	 */
	Monitor(GLFWmonitor* monitor) {
		monitor_ = monitor;
	}
	
	// No destructors needed as we do not own the data.
	// Just to play safe we still delete the copy operations.
	Monitor(const Monitor& other)            = delete;  // copy constructor
	Monitor& operator=(const Monitor& other) = delete;  // copy assignment
	Monitor(Monitor&& other)                 = default;  // move constructor
	Monitor& operator=(Monitor&& other)      = default;  // move assignment
	
	// --- Member accessors
	/*! @brief Returns the wrapped pointer hold by the object. */
	GLFWmonitor* getPointer() {
		return monitor_;
	}
	
private:
	/*! Pointer to the wrapped monitor object. */
	GLFWmonitor* monitor_;
	
public:
	/*********************************************************************
	 * Wrappers for monitor related functions
	 *********************************************************************/
	 
 	/*! @brief Returns the position of the monitor's viewport on the virtual screen.
 	 *
 	 *  This function returns the position, in screen coordinates, of the upper-left
 	 *  corner of the specified monitor.
 	 *
 	 *  Any or all of the position arguments may be `nullptr`.
 	 *
 	 *  @param[out] xpos Where to store the monitor x-coordinate, or `nullptr`.
 	 *  @param[out] ypos Where to store the monitor y-coordinate, or `nullptr`.
 	 *
 	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 	 *  ErrorCode::PlatformError.
 	 *
 	 *  @thread_safety This function must only be called from the main thread.
 	 */
 	void getPos(int* xpos, int* ypos) {
 		glfwGetMonitorPos(monitor_, xpos, ypos);
 	}
	
	/*! @brief Returns the position of the monitor's viewport on the virtual screen.
	 *
	 *  This function returns the position, in screen coordinates, of the upper-left
	 *  corner of the specified monitor.
	 *
	 *  @return Position as a Point2D<int>.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Point2D<int> getPos() {
		Point2D<int> point;
		glfwGetMonitorPos(monitor_, &point.x, &point.y);
		return point;
	}

	/*! @brief Returns the physical size of the monitor.
	 *
	 *  This function returns the size, in millimetres, of the display area of the
	 *  specified monitor.
	 *
	 *  Some systems do not provide accurate monitor size information, either
	 *  because the monitor
	 *  [EDID](https://en.wikipedia.org/wiki/Extended_display_identification_data)
	 *  data is incorrect or because the driver does not report it accurately.
	 *
	 *  Any or all of the size arguments may be `nullptr`.
	 *
	 *  @param[out] widthMM Where to store the width, in millimetres, of the
	 *  monitor's display area, or `nullptr`.
	 *  @param[out] heightMM Where to store the height, in millimetres, of the
	 *  monitor's display area, or `nullptr`.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @remark @win32 calculates the returned physical size from the
	 *  current resolution and system DPI instead of querying the monitor EDID data.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void getPhysicalSize(int* widthMM, int* heightMM) {
		glfwGetMonitorPhysicalSize(monitor_, widthMM, heightMM);
	}
	
	/*! @brief Returns the physical size of the monitor.
	 *
	 *  This function returns the size, in millimetres, of the display area of the
	 *  specified monitor.
	 *
	 *  Some systems do not provide accurate monitor size information, either
	 *  because the monitor
	 *  [EDID](https://en.wikipedia.org/wiki/Extended_display_identification_data)
	 *  data is incorrect or because the driver does not report it accurately.
	 *
	 *  @return Width and height, in millimetres, of the monitor's display area.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	Size2D getPhysicalSize() {
		Size2D size;
		glfwGetMonitorPhysicalSize(monitor_, &size.width, &size.height);
		return size;
	}

	/*! @brief Returns the name of the specified monitor.
	 *
	 *  This function returns a human-readable name, encoded as UTF-8, of the
	 *  specified monitor.  The name typically reflects the make and model of the
	 *  monitor and is not guaranteed to be unique among the connected monitors.
	 *
	 *  @return The UTF-8 encoded name of the monitor, or `nullptr` if an
	 *  [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
	 *
	 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
	 *  should not free it yourself.  It is valid until the specified monitor is
	 *  disconnected or the library is terminated.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	const char* getName() {
		return glfwGetMonitorName(monitor_);
	}
	
	/*! @brief Returns the available video modes for the specified monitor.
	 *
	 *  This function returns an array of all video modes supported by the specified
	 *  monitor.  The returned array is sorted in ascending order, first by color
	 *  bit depth (the sum of all channel depths) and then by resolution area (the
	 *  product of width and height).
	 *
	 *  @return A vector of video modes.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
	 *  should not free it yourself.  It is valid until the specified monitor is
	 *  disconnected, this function is called again for that monitor or the library
	 *  is terminated.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	std::vector<const VidMode*> getVideoModes();

	/*! @brief Returns the current mode of the specified monitor.
	 *
	 *  This function returns the current video mode of the specified monitor.  If
	 *  you have created a full screen window for that monitor, the return value
	 *  will depend on whether that window is iconified.
	 *
	 *  @return The current mode of the monitor, or `nullptr` if an
	 *  [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
	 *  should not free it yourself.  It is valid until the specified monitor is
	 *  disconnected or the library is terminated.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	const VidMode* getVideoMode() {
		return glfwGetVideoMode(monitor_);
	}

	/*! @brief Generates a gamma ramp and sets it for the specified monitor.
	 *
	 *  This function generates a 256-element gamma ramp from the specified exponent
	 *  and then calls @ref glfwSetGammaRamp with it.  The value must be a finite
	 *  number greater than zero.
	 *
	 *  @param[in] gamma The desired exponent.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
	 *  ErrorCode::InvalidValue and @ref ErrorCode::PlatformError.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setGamma(float gamma) {
		glfwSetGamma(monitor_, gamma);
	}

	/*! @brief Returns the current gamma ramp for the specified monitor.
	 *
	 *  This function returns the current gamma ramp of the specified monitor.
	 *
	 *  @return The current gamma ramp, or `nullptr` if an
	 *  [error](@ref error_handling) occurred.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @pointer_lifetime The returned structure and its arrays are allocated and
	 *  freed by GLFW.  You should not free them yourself.  They are valid until the
	 *  specified monitor is disconnected, this function is called again for that
	 *  monitor or the library is terminated.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	const GammaRamp* getGammaRamp() {
		return glfwGetGammaRamp(monitor_);
	}

	/*! @brief Sets the current gamma ramp for the specified monitor.
	 *
	 *  This function sets the current gamma ramp for the specified monitor.  The
	 *  original gamma ramp for that monitor is saved by GLFW the first time this
	 *  function is called and is restored by @ref glfwTerminate.
	 *
	 *  @param[in] ramp The gamma ramp to use.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @remark Gamma ramp sizes other than 256 are not supported by all platforms
	 *  or graphics hardware.
	 *
	 *  @pointer_lifetime The specified gamma ramp is copied before this function
	 *  returns.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	void setGammaRamp(const GammaRamp* ramp) {
		glfwSetGammaRamp(monitor_, ramp);
	}
};

/*! @brief Returns the currently connected monitors.
 *
 *  This function returns a vector of handles for all currently connected
 *  monitors.  The primary monitor is always first in the returned array.  If
 *  no monitors were found, this function returns an empty vector.
 *
 *  @return A vector of monitor handles, or an empty vector if no monitors were
 *  found or if an [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
std::vector<Monitor> getMonitors();

/*! @brief Returns the primary monitor.
 *
 *  This function returns either a unique_ptr to the primary monitor or
 *  `nullptr` if no primary monitor was found. This is usually the monitor
 *  where elements like the task bar or global menu bar are located.
 *
 *  @return The primary monitor, or `nullptr` if no monitors were found or if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function must only be called from the main thread.
 *
 *  @remark The primary monitor is always first in the array returned by @ref
 *  glfwGetMonitors.
 */
std::unique_ptr<Monitor> getPrimaryMonitor();


// -- Callback setters / unsetters

/*! @brief Sets the monitor configuration callback.
 *
 *  This function sets the monitor configuration callback, or removes the
 *  currently set callback.  This is called when a monitor is connected to or
 *  disconnected from the system.
 *
 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
 *  callback.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
void setMonitorCallback(monitorCallbackFun_t cbFun);

/*! @brief Deletes the monitor configuration callback. */
inline void unsetMonitorCallback() {
	setMonitorCallback(nullptr);
}


/*************************************************************************
 * Input
 *************************************************************************/

/*! @brief Cursor object wrapper.
 *
 *  Wraps a cursor object.
 */
class Cursor {
public:
	/*********************************************************************
	 * Construction, destruction, copy and move
	 *********************************************************************/
	 
 	/*! @brief Creates a custom cursor.
 	 *
 	 *  Creates a new custom cursor image that can be set for a window with @ref
 	 *  glfwSetCursor.
 	 *
 	 *  The pixels are 32-bit, little-endian, non-premultiplied RGBA, i.e. eight
 	 *  bits per channel.  They are arranged canonically as packed sequential rows,
 	 *  starting from the top-left corner.
 	 *
 	 *  The cursor hotspot is specified in pixels, relative to the upper-left corner
 	 *  of the cursor image.  Like all other coordinate systems in GLFW, the X-axis
 	 *  points to the right and the Y-axis points down.
 	 *
 	 *  @param[in] image The desired cursor image.
 	 *  @param[in] xhot The desired x-coordinate, in pixels, of the cursor hotspot.
 	 *  @param[in] yhot The desired y-coordinate, in pixels, of the cursor hotspot.
 	 *
 	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 	 *  ErrorCode::PlatformError.
 	 *
 	 *  @pointer_lifetime The specified image data is copied before this function
 	 *  returns.
 	 *
 	 *  @reentrancy This function must not be called from a callback.
 	 *
 	 *  @thread_safety This function must only be called from the main thread.
 	 */
	Cursor(const Image* image, int xhot, int yhot);

 	/*! @brief Creates a cursor with a standard shape.
 	 *
 	 *  Returns a cursor with a [standard shape](@ref shapes), that can be set for
 	 *  a window with @ref glfwSetCursor.
 	 *
 	 *  @param[in] shape One of the [standard shapes](@ref shapes).
 	 *
 	 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 	 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
 	 *
 	 *  @reentrancy This function must not be called from a callback.
 	 *
 	 *  @thread_safety This function must only be called from the main thread.
 	 */
	Cursor(CursorShape shape);
	
	/*! @brief Destroys a cursor.
	 *
	 *  This destructor destroys a cursor previously created with @ref
	 *  glfwCreateCursor.  Any remaining cursors will be destroyed by @ref
	 *  glfwTerminate.
	 *
	 *  @param[in] cursor The cursor object to destroy.
	 *
	 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
	 *  ErrorCode::PlatformError.
	 *
	 *  @reentrancy This function must not be called from a callback.
	 *
	 *  @thread_safety This function must only be called from the main thread.
	 */
	~Cursor();
	
	// --- Forbid copy operations
	Cursor(const Cursor& other)            = delete;  // copy constructor
	Cursor& operator=(const Cursor& other) = delete;  // copy assignment
	
	// --- Define move operations
	Cursor(Cursor&& other);             // move constructor
	Cursor& operator=(Cursor&& other);  // move assignment
	
	// --- Member accessors
	/*! @brief Returns pointer to the internal GLFWcursor struct. */
	GLFWcursor* getPointer() {
		return cursor_;
	}
	
private:
	/*! Pointer to the wrapped cursor object. */
	GLFWcursor* cursor_;
};


/*! @brief Returns the localized name of the specified printable key.
 *
 *  This function returns the localized name of the specified printable key.
 *  This is intended for displaying key bindings to the user.
 *
 *  If the key is `KeyCode::Unknown`, the scancode is used instead, otherwise
 *  the scancode is ignored.  If a non-printable key or (if the key is
 *  `KeyCode::Unknown`) a scancode that maps to a non-printable key is
 *  specified, this function returns `nullptr`.
 *
 *  This behavior allows you to pass in the arguments passed to the
 *  [key callback](@ref input_key) without modification.
 *
 *  The printable keys are:
 *  - `KeyCode::Apostrophe`
 *  - `KeyCode::Comma`
 *  - `KeyCode::Minus`
 *  - `KeyCode::Period`
 *  - `KeyCode::Slash`
 *  - `KeyCode::Semicolon`
 *  - `KeyCode::Equale`
 *  - `KeyCode::LeftBracket`
 *  - `KeyCode::RightBracket`
 *  - `KeyCode::Backslash`
 *  - `KeyCode::World1`
 *  - `KeyCode::World2`
 *  - `KeyCode::0` to `KeyCode::9`
 *  - `KeyCode::A` to `KeyCode::Z`
 *  - `KeyCode::KP_0` to `KeyCode::KP_9`
 *  - `KeyCode::KP_Decimal`
 *  - `KeyCode::KP_Divide`
 *  - `KeyCode::KP_Multiply`
 *  - `KeyCode::KP_Subtract`
 *  - `KeyCode::KP_Add`
 *  - `KeyCode::KP_Equal`
 *
 *  @param[in] key The key to query, or `KeyCode::Unknown`.
 *  @param[in] scancode The scancode of the key to query.
 *  @return The localized name of the key, or `nullptr`.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::PlatformError.
 *
 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the next call to @ref
 *  glfwGetKeyName, or until the library is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline const char* getKeyName(KeyCode key, int scancode) {
	return glfwGetKeyName(static_cast<int>(key), scancode);
}

/*! @brief Returns whether the specified joystick is present.
 *
 *  This function returns whether the specified joystick is present.
 *
 *  @param[in] joy The [joystick](@ref joysticks) to query.
 *  @return `true` if the joystick is present, or `false` otherwise.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline bool joystickPresent(Joystick joy) {
	return (glfwJoystickPresent(static_cast<int>(joy)) == GLFW_TRUE);
}

/*! @brief Returns the values of all axes of the specified joystick.
 *
 *  This function returns the values of all axes of the specified joystick.
 *  Each element in the array is a value between -1.0 and 1.0.
 *
 *  Querying a joystick slot with no device present is not an error, but will
 *  cause this function to return `nullptr`.  Call @ref glfwJoystickPresent to
 *  check device presence.
 *
 *  @param[in] joy The [joystick](@ref joysticks) to query.
 *  @return A vector of axis values, or empty vector if the joystick is not
 *  present or an [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
 *
 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the specified joystick is
 *  disconnected, this function is called again for that joystick or the library
 *  is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
std::vector<float> getJoystickAxes(Joystick joy);

/*! @brief Returns the state of all buttons of the specified joystick.
 *
 *  This function returns the state of all buttons of the specified joystick.
 *  Each element in the array is either `InputAction::Press` or
 *  `InputAction::Release`.
 *
 *  Querying a joystick slot with no device present is not an error, but will
 *  cause this function to return {}.  Call @ref glfwJoystickPresent to
 *  check device presence.
 *
 *  @param[in] joy The [joystick](@ref joysticks) to query.
 *  @return A vector of button states, or empty vector if the joystick is not
 *  present or an [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
 *
 *  @pointer_lifetime The returned array is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the specified joystick is
 *  disconnected, this function is called again for that joystick or the library
 *  is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
std::vector<InputAction> getJoystickButtons(Joystick joy);

/*! @brief Returns the name of the specified joystick.
 *
 *  This function returns the name, encoded as UTF-8, of the specified joystick.
 *  The returned string is allocated and freed by GLFW.  You should not free it
 *  yourself.
 *
 *  Querying a joystick slot with no device present is not an error, but will
 *  cause this function to return `nullptr`.  Call @ref glfwJoystickPresent to
 *  check device presence.
 *
 *  @param[in] joy The [joystick](@ref joysticks) to query.
 *  @return The UTF-8 encoded name of the joystick, or `nullptr` if the joystick
 *  is not present or an [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized, @ref
 *  ErrorCode::InvalidEnum and @ref ErrorCode::PlatformError.
 *
 *  @pointer_lifetime The returned string is allocated and freed by GLFW.  You
 *  should not free it yourself.  It is valid until the specified joystick is
 *  disconnected, this function is called again for that joystick or the library
 *  is terminated.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
inline const char* getJoystickName(Joystick joy) {
	return glfwGetJoystickName(static_cast<int>(joy));
}

// -- Callback setters / unsetters

/*! @brief Sets the joystick configuration callback.
 *
 *  This function sets the joystick configuration callback, or removes the
 *  currently set callback.  This is called when a joystick is connected to or
 *  disconnected from the system.
 *
 *  @param[in] cbfun The new callback, or `nullptr` to remove the currently set
 *  callback.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function must only be called from the main thread.
 */
void setJoystickCallback(joystickCallbackFun_t cbFun);

/*! @brief Deletes the joystick configuration callback. */
inline void unsetJoystickCallback() {
	setJoystickCallback(nullptr);
}


/*************************************************************************
 * Time related functions
 *************************************************************************/

/*! @brief Returns the value of the GLFW timer.
 *
 *  This function returns the value of the GLFW timer.  Unless the timer has
 *  been set using @ref glfwSetTime, the timer measures time elapsed since GLFW
 *  was initialized.
 *
 *  The resolution of the timer is system dependent, but is usually on the order
 *  of a few micro- or nanoseconds.  It uses the highest-resolution monotonic
 *  time source on each supported platform.
 *
 *  @return The current value, in seconds, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function may be called from any thread.  Reading and
 *  writing of the internal timer offset is not atomic, so it needs to be
 *  externally synchronized with calls to @ref glfwSetTime.
 */
inline double getTime() {
	return glfwGetTime();
}

/*! @brief Sets the GLFW timer.
 *
 *  This function sets the value of the GLFW timer.  It then continues to count
 *  up from that value.  The value must be a positive finite number less than
 *  or equal to 18446744073.0, which is approximately 584.5 years.
 *
 *  @param[in] time The new value, in seconds.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized and @ref
 *  ErrorCode::InvalidValue.
 *
 *  @remark The upper limit of the timer is calculated as
 *  floor((2<sup>64</sup> - 1) / 10<sup>9</sup>) and is due to implementations
 *  storing nanoseconds in 64 bits.  The limit may be increased in the future.
 *
 *  @thread_safety This function may be called from any thread.  Reading and
 *  writing of the internal timer offset is not atomic, so it needs to be
 *  externally synchronized with calls to @ref glfwGetTime.
 */
inline void setTime(double time) {
	glfwSetTime(time);
}

/*! @brief Returns the current value of the raw timer.
 *
 *  This function returns the current value of the raw timer, measured in
 *  1/frequency seconds.  To get the frequency, call @ref
 *  glfwGetTimerFrequency.
 *
 *  @return The value of the timer, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline uint64_t getTimerValue() {
	return glfwGetTimerValue();
}

/*! @brief Returns the frequency, in Hz, of the raw timer.
 *
 *  This function returns the frequency, in Hz, of the raw timer.
 *
 *  @return The frequency of the timer, in Hz, or zero if an
 *  [error](@ref error_handling) occurred.
 *
 *  @errors Possible errors include @ref ErrorCode::NotInitialized.
 *
 *  @thread_safety This function may be called from any thread.
 */
inline uint64_t getTimerFrequency() {
	return glfwGetTimerFrequency();
}

} // end namespace GLFW

#endif /* end of include guard: _GLFWPP_H */
