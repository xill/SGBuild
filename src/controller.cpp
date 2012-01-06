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
#include "animation.h"

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
	switch(commands.size()) {
	case 1:
	{
		terminal.push("too few parameters.");
		return "use \"add -help\" for usage.";
	}
	case 2:
	{
		if(commands[1] == "-help") {
			terminal.push("usage: add <element type> <target>");
			terminal.push(" ");
			terminal.push("element types:");
			terminal.push("-image            < single image. doesn't require a target. >");
			terminal.push("-animation        < animation wrapper. doesn't require a target. >");
			terminal.push("-animationframe   < animation element. requires a animation wrapper target key >");
			return "";
		} else if(commands[1] == "-image") {

		} else if(commands[1] == "-animation") {
			Animation* anim = new Animation(data.transform,data.scaling);
			view.add(anim);
		}
		break;
	}
	case 3:
	{
		if(commands[1] == "-animationframe") {
			int key = 0;

			/* if last parameter is actually a number. */
			try {
				key = i_scast(commands[2]);
			} catch ( ... ) {
				return "invalid parameters.";
			}

			Element* elem;
			/* if element key is a valid animation element. */
			try {
				elem = view.get(key);
			} catch ( ... ) {
				return "element key is not valid.";
			}

			if(elem->type() == "animation") {
				AnimationFrame* frame = new AnimationFrame(Vec2f(0,0),Vec2f(1,1));
				((Animation*)elem)->add(frame);
				return "";
			} else {
				return "element is not valid.";
			}
		}
	}
	default:
		terminal.push("too many parameters.");
		return "use \"add -help\" for usage.";
	};

	return "invalid parameters.";
}

std::string Controller::set(std::vector<std::string> commands) 
{
	if (commands.size() >= 4) {
		if(commands[1] == "-translate") {
			// TODO. active element translate.
		} else if(commands[1] == "-scale") {
			// TODO. active element scaling.
		}

	} else if(commands.size() == 3) {
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
			terminal.push("usage: set <target key> <action>");
			terminal.push(" ");
			terminal.push("actions:");
			terminal.push("-active        < sets target key as the active element. >");
			terminal.push("or");
			terminal.push("usage: set <modification target> <value 1> <value 2> etc.");
			terminal.push(" ");
			terminal.push("modification targets:");
			terminal.push("-translate");
			terminal.push("-scale");
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
	if(commands.size() == 2) {
		if(commands[1] == "-help") {
			terminal.push("usage: list <action>");
			terminal.push(" ");
			terminal.push("actions:");
			terminal.push("-all        < list all >");
		} else if(commands[1] == "-all") {
			std::vector<Element*> elements = view.getAll();
			if(elements.size() > 0) {
				for(int i = 0; i < elements.size(); ++i) {
					terminal.push(s_cast(i)+" "+elements[i]->type());
					// TODO. animation sub element listing.
				}
			} else {
				return "nothing to list.";
			}
		}
		// TODO. add type specific checks when their done.
	} else if(commands.size() == 1) {
		terminal.push("too few parameters.");
		return "use \"list -help\" for usage.";
	}
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
