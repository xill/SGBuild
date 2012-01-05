#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include "element.h"
#include "SSCon/text_include.h"

class AnimationFrame : public Element {

public:
	AnimationFrame(int dur = 0) : Element() , frame_duration(dur) {}
	AnimationFrame(Vec2f loc, Vec2f scale,int dur = 0) : Element(loc,scale) , frame_duration(dur) {}

	void draw();
	void update();

	int getDuration() { return frame_duration; }
private:
	int frame_duration;
};

#endif