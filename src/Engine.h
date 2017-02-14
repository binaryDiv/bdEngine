#ifndef _BDENGINE_ENGINE_H
#define _BDENGINE_ENGINE_H

#include "RenderWindow.h"

namespace bdEngine {

class Engine {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	
	/*!
	 * Default constructor. Sets up data structures and stuff, but does not
	 * initialize graphics or anything yet. See init().
	 */
	Engine();
	
	/*!
 	 * Constructor that parses application arguments and does everything the
 	 * default constructor does. See Engine().
 	 * (May alter argc and argv.)
 	 *
	 * @param  argc  Reference to application argc.
	 * @param  argv  Reference to application argv.
	 */
	Engine(int& argc, char**& argv);
	
	
	/*******************************************************************
	 * Engine lifecycle (initialization and main loop)
	 *******************************************************************/
	 
 	/*!
 	 * Initialize engine. This will set everything up, create a RenderWindow,
 	 * initialize graphics driver, load resource, and so on.
 	 *
 	 * This function has to be called before any component of the engine is
 	 * used or any graphics is done.
 	 */
 	void init();
	
	/*!
	 * Returns true if engine is initialized, that is, after init() has been
	 * called.
	 */
	bool isInitialized() const {
		return initialized_;
	}
	
	/*!
	 * Starts engine main loop.
	 * Returning from this function usually means the program is terminating.
	 *
	 * @return  Exit code to be returned by main().
	 */
	int run();

private:
	// Initialization state
	bool initialized_ = false;
	
	// Component: RenderWindow (contains the Renderer instance)
	std::unique_ptr<RenderWindow> renderWindow_;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_ENGINE_H */
