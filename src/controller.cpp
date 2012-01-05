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
	terminal.setBackgroundRGBA(0,0,0,1);

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
		view.draw();
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

#include "animation_frame.h"

std::string Controller::onCommit(std::string line) {
	std::vector<std::string> commands = TextFactory::instance()->util()->split(line,' ');
	if(commands[0] == "exit") {
		terminal.close();
	} else if(commands[0] == "add") {
		return add(commands);
	} else if(commands[0] == "list") {
		return list(commands);
	} else if(commands[0] == "set") {
		return set(commands);
	}
	
	return "invalid command";
}

std::string Controller::add(std::vector<std::string> commands)
{
	if(commands.size() == 3) {
		int err = 0;

		Vec2f loc;
		try {
			loc.x = f_scast(commands[1]);
		} catch ( ... ) {
			err += 1;
		}

		try {
			loc.y = f_scast(commands[2]);
		} catch ( ... ) {
			err += 2;
		}

		if(err != 0) 
			return (err==3)
				?"invalid add parameters"
				:(err==2)?"invalid second add parameters"
				:"invalid first add parameters";

		AnimationFrame* img = new AnimationFrame();
		img->setLocation(loc);
		img->setScale(Vec2f(100,100));
		view.add(img);
		view.sort();

		return "";
	} else if(commands.size() == 2 && commands[1] == "-help") {
		return "usage: add <x-value> <y-value>";
	} else if(commands.size() == 1) {
		terminal.push("too few parameters.");
		return "use \"add -help\" for usage.";
	} else if(commands.size() > 3) {
		return "too many parameters.";
	} else {
		return "invalid add parameters";
	}
}

std::string Controller::set(std::vector<std::string> commands) 
{
	if(commands.size() == 3) {
		if(commands[2] == "-active") {
			int tmp = 0;
			try {
				tmp = i_scast(commands[1]);
			} catch ( ... ) {
				return "invalid parameters.";
			}

			try {
				view.set(tmp);
			} catch ( ... ) {
				return "no such element key.";
			}

			return "active element set to "+commands[1];
		}
	} else if(commands.size() == 2 && commands[1] == "-help") {
			terminal.push("Usage: set <target_key> <action>");
			terminal.push(" ");
			terminal.push("Actions:");
			terminal.push("-active");
			return "";
	} else if(commands.size() == 1 || commands.size() == 2) {
		terminal.push("too few parameters.");
		return "use \"set -help\" for usage.";
	} else if(commands.size() > 3) {
		return "too many parameters.";
	}
	
	return "invalid parameters.";
}

std::string Controller::list(std::vector<std::string> commands)
{
	return "";
}

std::string Controller::load(std::vector<std::string> commands)
{
	return "";
}

std::string Controller::save(std::vector<std::string> commands)
{
	return "";
}
