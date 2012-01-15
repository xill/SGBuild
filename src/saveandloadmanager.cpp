#include "saveandloadmanager.h"

SLManager* SLManager::m_instance = 0;

void SLManager::load(View* view,std::string path)
{

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
		filestream << ">\n";
		filestream << "</Element>\n";
	}
}