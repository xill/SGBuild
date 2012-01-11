#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include <vector>

#include "element.h"
#include "SSCon/text_include.h"

class AnimationFrame : public Element {

public:
	AnimationFrame(int dur = 0) : Element("animationframe") , frame_duration(dur) {}
	AnimationFrame(Vec2f loc, Vec2f scale,int dur = 0) : Element(loc,scale,"animationframe") , frame_duration(dur) {}

	void draw();
	void update();

	int getDuration() { return frame_duration; }
	void setDuration(int dur) { frame_duration = dur; }

	void add(AnimationFrame* elem) { frames.push_back(elem); }
	std::vector<AnimationFrame*> get() { return frames; }
	AnimationFrame* get(int index);

	bool isValidKey(int key);

private:
	std::vector<AnimationFrame*> frames;

	int frame_duration;

};

#endif