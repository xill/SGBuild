#ifndef ANIMATION_H
#define ANIMATION_H

//#include <string>
#include <vector>
#include "element.h"
#include "animation_frame.h"
#include "SSCon/text_include.h"

class Animation : public Element {

public:
	Animation() 
		: Element("animationcontainer") 
		, frameindex(0)
		, duration(0)
		, lastframe(0)
		, running(false)
		, looping(false)
	{}
	Animation(Vec2f loc, Vec2f scale) 
		: Element(loc,scale,"animationcontainer") 
		, frameindex(0)
		, duration(0)
		, lastframe(0)
		, running(false) 
		, looping(false)
	{}

	void draw();
	void update();

	/* sets the current frame index. will throw if the index is invalid. */
	void setIndex(int i);

	/* sets all values to default */
	void restart();

	void setRunning(bool state) { running = state; }
	void setLooping(bool state) { looping = state; }
	void add(AnimationFrame* elem) { frames.push_back(elem); }

private:
	int frameindex;
	Uint32 duration;
	Uint32 lastframe;
	bool running;
	bool looping;
	std::vector<AnimationFrame*> frames;
};

#endif