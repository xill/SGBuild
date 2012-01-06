#include "view.h"

void View::draw() 
{
	/*
	if(current != 0) {
		current->draw();
	}*/
	for(int i = 0; i < viewlist.size(); ++i) {
		viewlist[i]->draw();
	}
}

void View::sort()
{
	// tmp stuff. change later.
	if(viewlist.size() > 0) {
		current = viewlist[0];
	}
}

void View::set(int index)
{
	if(isValidKey(index)) {
		current = viewlist[index];
	} else {
		throw int();
	}
}

bool View::isValidKey(int key) 
{
	return (key < viewlist.size() && viewlist[key] != 0);
}

Element* View::get(int index)
{
	if(isValidKey(index)) {
		return viewlist[index];
	} else {
		throw int();
	}
}