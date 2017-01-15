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
	 * Default constructor. Initializes everything.
	 */
	Engine();
	
	/*!
 	 * Constructor that parses application arguments and initializes everything.
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
	 * Starts engine main loop.
	 * Returning from this function usually means the program is terminating.
	 *
	 * @return  Exit code to be returned by main().
	 */
	int run();

private:
	RenderWindow renderWindow;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_ENGINE_H */
