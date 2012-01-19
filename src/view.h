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

	/* set current active element. */
	void set(Element* elem);

	/* is given key valid. */
	bool isValidKey(int key);

	/* return given index from the viewlist. Will throw if the key is invalid. */
	Element* get(int index);

	void setVirtualOrigin(const Vec2f loc);
	Vec2f getVirtualOrigin();
private:
	/* current active element. */
	Element* current;
	
	/* virtual origin which will adjust locations during saving. */
	Vec2f virtual_origin;

	std::vector<Element*> viewlist;

	
};

#endif