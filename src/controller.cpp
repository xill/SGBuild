#include "controller.h"

#include "math/vec2.h"
#include "math/vec3.h"
#include "SSCon/textfactory.h"
#include <iostream>

Controller *Controller::instance_ = NULL;

Controller::Controller()
	: title_("Playground")
	, running(true)
{
}

Controller *Controller::instance()
{
	if (instance_ == NULL) {
		instance_ = new Controller();
	}

	return instance_;
}

void Controller::run()
{
	unsigned int last_step = 0;
	float dt = 0;
	renderer.initWindow(Vec2f(720,560),32,0,title_);
	renderer.initGraphics();
	terminal.setListener(this);
	terminal.setDimension(720,560);

	while (running) {

		unsigned int duration = SDL_GetTicks() - last_step;

		if (duration > 100) {
			duration = 50;
		}

		if(!terminal.update())
		{
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				onEvent(event);
			}
		}
		last_step = SDL_GetTicks();

		renderer.startDraw();
		TextFactory::instance()->drawText("ekekekekekekasadfsfaffrghhjfbcvbsds",100,100);
		renderer.drawFrame();
		terminal.draw();
		renderer.commitDraw();
	}
}

void Controller::onEvent(const SDL_Event &event)
{
	switch (event.type) {

	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {

		case SDLK_ESCAPE:
			running = false;
			break;

		default:
			break;
		};
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_HOME:
			terminal.open();
		};
		break;
	case SDL_VIDEORESIZE:
		renderer.onResize(Vec2f(event.resize.w, event.resize.h));
		break;
	};
}

std::string Controller::onCommit(std::string line) {
	if(line == "exit") {
		terminal.close();
	} else {
		return "invalid command";
	}
	return "";
}
