#ifndef ELEMENT_H
#define ELEMENT_H

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define LOWER_RIGHT 2
#define LOWER_LEFT 3

#include "math/vec2.h"
#include <string>
#include "SSCon/text_include.h"

class Element {
	
public :
	Element(std::string _typename);
	Element(Vec2f loc, Vec2f _scale, std::string _typename);

	virtual void draw() {};
	virtual void update() {};

	bool isVisible() { return visible; }
	void setVisible(const bool state) { visible = state; }

	Vec2f getLocation() { return location; }
	void setLocation(const Vec2f loc) { this->location = loc; }

	Vec2f getScale() { return scale; }
	void setScale(const Vec2f _scale) { this->scale = _scale; }

	Vec2f getPivot() { return pivot; }
	void setPivot(const Vec2f _pivot) { this->pivot = _pivot; }

	float getAngle() { return angle; }
	void setAngle(float _angle) { this->angle = _angle; }

	Vec2f* dimensionPoints() { return points; }

	std::string type() { return m_typename; }

	void setTexture(const GLuint tex) { texture = tex; }
	GLuint getTexture() { return texture; }

	void setName(const std::string name) { m_pathname = name; }
	std::string getName() { return m_pathname; }

	bool hasChanged()
	{
		if(changed){
			changed = false;
			return true;
		} else {
			return false;
		}
	}

	/* sets RGBA values when drawing this object. */
	void setRGBA(float r, float g, float b, float a);
	void pivotalRotate();

protected:
	/* actual xy location of this image. top left corner. */
	Vec2f location;
	/* pivot point which this element rotates around. */
	Vec2f pivot;
	/* xy scale factor of this image. */
	Vec2f scale;
	/* all corner points are relative to location point. */
	Vec2f *points;

	float angle;
	bool visible;
	bool changed;

	/* todo. something with layers. */
	int layer;

	float R,G,B,A;

	const std::string m_typename;
	std::string m_pathname;

	GLuint texture;
};

#endif