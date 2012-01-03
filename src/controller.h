#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <list>
#include <textbuilder/text_include.h>

#include "graphics/mainrenderer.h"
#include "terminal/terminallistener.h"
#include "terminal/terminal.h"
#include "math/vec2.h"

class MainRenderer;
class CelestialBody;
class MaiWorld;
class MaiBody;
class SoundPool;
union SDL_Event;
struct Object;

class Controller : public TerminalListener
{
protected:

	const std::string title_;

	static Controller *instance_;
	/** singleton */
	Controller();

	MainRenderer renderer;
	Terminal terminal;
	bool running;

public:

	static Controller *instance();
	void onEvent(const SDL_Event &event);
	std::string onCommit(std::string);
	void run();
};

#endif // CONTROLLER_H
