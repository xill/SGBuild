#include "element.h"

Element::Element()
	: visible(true)
	, changed(false)
	, layer(0)
{
	points = new Vec2f[4];
	points[TOP_LEFT] = Vec2f(0,0);
	points[TOP_RIGHT] = Vec2f(1,0);
	points[LOWER_RIGHT] = Vec2f(1,1);
	points[LOWER_LEFT] = Vec2f(0,1);
}

Element::Element(Vec2f loc, Vec2f _scale)
	: visible(true)
	, changed(false)
	, layer(0)
	, location(loc)
	, scale(_scale)
{
	points = new Vec2f[4];
	points[TOP_LEFT] = Vec2f(0,0);
	points[TOP_RIGHT] = Vec2f(1,0);
	points[LOWER_RIGHT] = Vec2f(1,1);
	points[LOWER_LEFT] = Vec2f(0,1);
}