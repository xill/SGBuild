#ifndef ELEMENT_H
#define ELEMENT_H

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define LOWER_RIGHT 2
#define LOWER_LEFT 3

#include "math/vec2.h"

class Element {
	
public :
	Element();
	Element(Vec2f loc, Vec2f _scale);

	virtual void draw() {};
	virtual void update() {};

	bool isVisible() { return visible; }
	void setVisible(bool state) { visible = state; }

	Vec2f getLocation() { return location; }
	void setLocation(Vec2f loc) { this->location = loc; }

	Vec2f getScale() { return scale; }
	void setScale(Vec2f _scale) { this->scale = _scale; }

	Vec2f* dimensionPoints() { return points; }

	bool hasChanged()
	{
		if(changed){
			changed = false;
			return true;
		} else {
			return false;
		}
	}

protected:
	Vec2f location;
	Vec2f scale;

	/* all corner points are relative to location point. */
	Vec2f *points;

	bool visible;
	bool changed;
	int layer;
};

#endif