#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <list>
#include <SSCon/text_include.h>

#include "graphics/mainrenderer.h"
#include "SSCon/terminallistener.h"
#include "SSCon/terminal.h"
#include "view.h"
#include "math/vec2.h"
#include "stringutil.h"

#include "animation_frame.h"
#include "animation.h"
#include "image.h"

#define ANIMATION "animationcontainer"
#define ANIMATIONFRAME "animationframe"
#define IMAGE "image"

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
	View view;
	bool running;

public:

	static Controller *instance();
	void onEvent(const SDL_Event &event);
	std::string onCommit(std::string);
	void run();

private:
	std::string add(std::vector<std::string> commands);
	std::string set(std::vector<std::string> commands);
	std::string list(std::vector<std::string> commands);
	std::string load(std::vector<std::string> commands);
	std::string save(std::vector<std::string> commands);

	void listRecursion(AnimationFrame* frame , std::string app_str);

	struct datawrapper
	{
		Vec2f scaling;
		Vec2f transform;

		datawrapper() : scaling(Vec2f(1,1)) , transform(Vec2f(0,0)) {

		}
	} data;
};

#endif // CONTROLLER_H
