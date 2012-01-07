#include "image.h"

void Image::draw()
{
	if(visible) {
		glPushMatrix();
		glTranslatef(location.x,location.y,0);
		glScalef(scale.x,scale.y,1);
		glColor4f(R,G,B,A);

		glBegin(GL_QUADS);
		glVertex2f(points[TOP_LEFT].x,points[TOP_LEFT].y);
		glVertex2f(points[TOP_RIGHT].x,points[TOP_RIGHT].y);
		glVertex2f(points[LOWER_RIGHT].x,points[LOWER_RIGHT].y);
		glVertex2f(points[LOWER_LEFT].x,points[LOWER_LEFT].y);
		glEnd();
		glColor4f(1,1,1,1);
		glPopMatrix();
	}
}

void Image::update()
{

}