#include <iostream>

#include "fractalthread.h"

int main(int argc, char **argv) {
	char data[64];
	FractalThread t(data, 8, 64, 0, 0, true, 3, 3, -1.5, -1.5, 0, 0);
	t.start();

	std::cout << "Hello, world!" << std::endl;
	return 0;
}
