#include "animation.h"

void Animation::draw()
{
	if(!this->isVisible() || frames.size() == 0) return;

	glPushMatrix();
	glTranslatef(location.x, location.y, 0);
	glScalef(scale.x,scale.y,1);

	if(running) {
		Uint32 time = SDL_GetTicks();
		Uint32 tmptime = (time - lastframe);
		lastframe = time;

		if(tmptime > 100) tmptime = 100;

		duration += tmptime;
		while(duration >= frames[frameindex]->getDuration() 
			&& frames[frameindex]->getDuration() > 0)
		{
			duration -= frames[frameindex]->getDuration();
			frameindex++;

			if(frameindex >= frames.size()) frameindex = 0;
		}
	}

	frames[frameindex]->draw();
	glPopMatrix();
}

void Animation::update()
{

}

void Animation::setIndex(int i)
{
	if(i < frames.size() && frames[i] != 0) {
		frameindex = i;
	} else {
		throw int();
	}
}

AnimationFrame* Animation::get(int index) 
{
	if(isValidKey(index)){
		return frames[index];
	} else {
		throw int();
	}
}

bool Animation::isValidKey(int key)
{
	return (key < frames.size() && frames[key] != 0);
}

void Animation::restart() 
{
	running = false;
	frameindex = 0;
	duration = 0;
	lastframe = 0;
}