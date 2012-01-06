#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include "element.h"

/**
 * handles all elements within a single viewport.
 */
class View {

public:
	View() : current(0) {}
	void add(Element* elem) { viewlist.push_back(elem); sort(); }
	Element* getSet() { return current; }
	std::vector<Element*> getAll() { return viewlist; }

	void draw();
	
	/* sorts the viewlist */
	void sort();

	/* set current active element. */
	void set(int index);

	/* is given key valid. */
	bool isValidKey(int key);

	/* return given index from the viewlist. Will throw if the key is invalid. */
	Element* get(int index);
private:
	/* current active element. */
	Element* current;
	
	std::vector<Element*> viewlist;

	
};

#endif