#include "element.h"

Element::Element(std::string _typename)
	: visible(true)
	, changed(false)
	, layer(0)
	, m_typename(_typename)
	, texture(0)
	, angle(0)
	, R(1)
	, G(1)
	, B(1)
	, A(1)
{
	points = new Vec2f[4];
	points[TOP_LEFT] = Vec2f(0,0);
	points[TOP_RIGHT] = Vec2f(1,0);
	points[LOWER_RIGHT] = Vec2f(1,1);
	points[LOWER_LEFT] = Vec2f(0,1);
}

Element::Element(Vec2f loc, Vec2f _scale, std::string _typename)
	: visible(true)
	, changed(false)
	, layer(0)
	, location(loc)
	, scale(_scale)
	, m_typename(_typename)
	, texture(0)
	, angle(0)
	, R(1)
	, G(1)
	, B(1)
	, A(1)
{
	points = new Vec2f[4];
	points[TOP_LEFT] = Vec2f(0,0);
	points[TOP_RIGHT] = Vec2f(1,0);
	points[LOWER_RIGHT] = Vec2f(1,1);
	points[LOWER_LEFT] = Vec2f(0,1);
}

void Element::setRGBA(float r, float g, float b, float a) {
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}

void Element::pivotalRotate() {
	if(angle != 0) {
		glTranslatef(-pivot.x,-pivot.y,0);
		glRotatef(angle,0,0,1);
		glTranslatef(pivot.x,pivot.y,0);
	}
}