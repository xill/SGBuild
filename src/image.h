#ifndef IMAGE_H
#define IMAGE_H

#include "element.h"
#include "SSCon/text_include.h"
#include "graphics/texturemanager.h"

class Image : public Element {

public:
	Image() : Element("image") {}
	Image(Vec2f loc, Vec2f scale) : Element(loc,scale,"image") {}

	void draw();
	void update();
};

#endif