#include "saveandloadmanager.h"

SLManager* SLManager::m_instance = 0;

void SLManager::load(View* view,std::string path)
{	// TODO. needs lot more testing... later :D
	std::ifstream myfile (path);
	if(myfile.is_open()) {
		while(myfile.good()) {
			Element* elem = loadHelper(myfile,0);
			if(elem != 0) {
				view->add(elem);
			} else {	// should only return null when empty line is encountered.
				break;
			}
		}
	}
}

Element* SLManager::loadHelper(std::ifstream &myfile, Element* elem, std::string newline) {
	std::string line;
	if(newline != "") {
		line = newline;
	} else {
		getline (myfile,line);
	}

	if(line == "" ) return 0;

	Element* current;
	std::vector<std::string> values = TextFactory::instance()->util()->split(line,' ');
	std::vector<std::string> sublines;
	for(int i = 0; i < values.size(); ++i) {
		sublines = TextFactory::instance()->util()->split(values[i],'=');
		if(sublines.size() > 1) {
			if(sublines[0] == "type") {
				if(sublines[1] == ANIMATION) {
					current = new Animation();
					if(elem == 0) {
						elem = current;
					}
				} else if (sublines[1] == ANIMATIONFRAME) {
					current = new AnimationFrame();
					if(elem == 0) {
						elem = current;
					} else {
						if(elem->type() == ANIMATION) {
							((Animation*) elem)->add((AnimationFrame*)current);
						} else if(elem->type() == ANIMATIONFRAME) {
							((AnimationFrame*) elem)->add((AnimationFrame*)current);
						}
					}
				} else if (sublines[1] == IMAGE) {
					current = new Image();
					if(elem == 0) {
						elem = current;
					}
				}
			} else if(sublines[0] == "path") {
				/* currently preset for rgba images ONLY. rgb will result in a crash. */
				current->setName(sublines[1]);
				if(sublines[1] != "none") {
					TextureManager::instance()->mapTexture(sublines[1]);
					TextureManager::instance()->loadTexture(TextureManager::instance()->getMapped().size()-1, GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_RGBA);
					current->setTexture(TextureManager::instance()->pathToId(sublines[1]));
				}
			} else if(sublines[0] == "t") {
				std::vector<std::string> params = TextFactory::instance()->util()->split(sublines[1],',');
				current->setLocation(Vec2f(f_scast(params[0]),f_scast(params[1])));
			} else if(sublines[0] == "s") {
				std::vector<std::string> params = TextFactory::instance()->util()->split(sublines[1],',');
				current->setScale(Vec2f(f_scast(params[0]),f_scast(params[1])));
			} else if(sublines[0] == "d") {
				((AnimationFrame*)current)->setDuration(i_scast(sublines[1]));
			} else if(sublines[0] == "a") {
				current->setAngle(i_scast(sublines[1]));
			}
		}
	}
	std::vector<std::string> next_values;
	line = "";
	do {
		getline (myfile,line);
		if(line == "") return 0; 
		next_values = TextFactory::instance()->util()->split(line,' ');
		if(next_values.size() > 1) loadHelper(myfile,current,line);
	} while (next_values.size() > 1 || next_values.size() == 0);
	return elem;
}

void SLManager::save(View* view,std::string path)
{
	std::ofstream newfile(path);

	if(newfile.is_open()) {
		std::vector<Element*> elements = view->getAll();

		for(int i = 0; i < elements.size(); ++i) {
			saveHelper(newfile,elements[i]);
		}
		newfile.close();
	}
}

void SLManager::saveHelper(std::ofstream &filestream, Element* elem)
{
	if(elem->type() == "animationframe")
	{
		AnimationFrame* frame = (AnimationFrame*) elem;
		std::vector<AnimationFrame*> list = frame->get();

		filestream << "<Element type="+elem->type()+" ";
		filestream << "path="+TextureManager::instance()->idToPath(frame->getTexture())+" ";
		filestream << "t="+s_cast(elem->getLocation().x)+","+s_cast(elem->getLocation().y)+" ";
		filestream << "s="+s_cast(elem->getScale().x)+","+s_cast(elem->getScale().y)+" ";
		filestream << "a="+s_cast(elem->getAngle())+" ";
		filestream << "d="+s_cast(frame->getDuration())+" >\n";

		if(list.size() > 0) {
			for(int i = 0; i < list.size() ; ++i) {
				AnimationFrame* subframe = list[i];
				if(subframe != 0) saveHelper(filestream,subframe);
			}
		}
		filestream << "</Element>\n";
	} else if(elem->type() == "animationcontainer") {
		Animation* frame = (Animation*) elem;
		std::vector<AnimationFrame*> list = frame->get();

		filestream << "<Element type="+elem->type()+" ";
		filestream << "t="+s_cast(elem->getLocation().x)+","+s_cast(elem->getLocation().y)+" ";
		filestream << "s="+s_cast(elem->getScale().x)+","+s_cast(elem->getScale().y)+" ";
		filestream << "a="+s_cast(elem->getAngle())+" ";
		filestream << ">\n";

		if(list.size() > 0) {
			for(int i = 0; i < list.size() ; ++i) {
				AnimationFrame* subframe = list[i];
				if(subframe != 0) saveHelper(filestream,subframe);
			}
		}
		filestream << "</Element>\n";
	} else if(elem->type() == "image") {
		filestream << "<Element type="+elem->type()+" ";
		filestream << "path="+TextureManager::instance()->idToPath(elem->getTexture())+" ";
		filestream << "t="+s_cast(elem->getLocation().x)+","+s_cast(elem->getLocation().y)+" ";
		filestream << "s="+s_cast(elem->getScale().x)+","+s_cast(elem->getScale().y)+" ";
		filestream << "a="+s_cast(elem->getAngle())+" ";
		filestream << ">\n";
		filestream << "</Element>\n";
	}
}