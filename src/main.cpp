#include <iostream>

#include "controller.h"

int main(int argc, char **argv)
{
	std::cout << "hello world!" << std::endl;

	Controller::instance()->run();

	return 0;
}
