#ifndef SL_MANAGER_H
#define SL_MANAGER_H

#define ANIMATION "animationcontainer"
#define ANIMATIONFRAME "animationframe"
#define IMAGE "image"

#include <string>
#include <iostream>
#include <fstream>
#include <istream>

#include "math/vec2.h"
#include "view.h"
#include "animation.h"
#include "animation_frame.h"
#include "image.h"
#include "element.h"
#include "graphics/texturemanager.h"
#include "SSCon/textfactory.h"
#include "stringutil.h"

class SLManager {

public:

	static SLManager* instance() {
		if(m_instance == 0) {
			m_instance = new SLManager();
		}
		return m_instance;
	}

	/* load save file from the path to given view. */
	void load(View* view,std::string path);

	/* save the given view to a file in the given path. */
	void save(View* view,std::string path);

private:
	SLManager() {}

	static SLManager* m_instance;

	Element* loadHelper(std::ifstream &myfile, Element* elem, std::string newline = "");
	void saveHelper(std::ofstream &filestream, View* view, Element* elem);
};

#endif