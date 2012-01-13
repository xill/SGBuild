#include "image.h"

void Image::draw()
{
	if(visible) {
		glPushMatrix();
		glTranslatef(location.x,location.y,0);
		glScalef(scale.x,scale.y,1);
		glColor4f(R,G,B,A);

		if(texture == 0) {
			glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_TEXTURE_2D);
		}

		TextureManager::instance()->bindOrDoNothing(texture);

		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex2f(points[TOP_LEFT].x,points[TOP_LEFT].y);
		glTexCoord2f(1,0);
		glVertex2f(points[TOP_RIGHT].x,points[TOP_RIGHT].y);
		glTexCoord2f(1,1);
		glVertex2f(points[LOWER_RIGHT].x,points[LOWER_RIGHT].y);
		glTexCoord2f(0,1);
		glVertex2f(points[LOWER_LEFT].x,points[LOWER_LEFT].y);
		glEnd();
		glColor4f(1,1,1,1);
		glPopMatrix();

		if(texture == 0) {
			glPopAttrib();
		}
	}
}

void Image::update()
{

}