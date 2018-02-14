#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

#include "fractalthread.h"
#include "array_utils.h"
#include "image_writer.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "Allocating pixel array..." << endl;
	uint32_t width = 10000, height = 10000;
	uint8_t **pixels = create2dUint8Array(height, width * 4);

	cout << "Creating a value generator..." << endl;
	ValueGenerator g(width, height, 3, 3, -1.5, -1.5, true, 500, 0, 0);

	uint32_t n_threads = thread::hardware_concurrency() + 2;
	cout << "Using " << n_threads << " threads" << endl;

	cout << "Starting the generator threads..." << endl;
	FractalThread *threads = new FractalThread[n_threads];
	uint32_t leftOver = width * height % n_threads;
	size_t i;
	for (i = 0; i < n_threads; i++) {
		threads[i].generateImage(pixels, width, width * height / n_threads + (leftOver > i), i, n_threads, g);
	}

	bool running = true;
	while (running) {
		cout << "Thread progress:" << endl;
		running = false;
		for (i = 0; i < n_threads; i++) {
			cout << threads[i].getProgress() << " %" << (i < n_threads - 1 ? " " : "");
			if (!threads[i].isDone()) {
				running = true;
			}
		}
		cout << endl;

		this_thread::sleep_for(1s);
	}

	cout << "Writing image..." << endl;
	writePNG(pixels, width, height, "output.png");
	
	cout << "Done writing image." << endl;

	delete[] threads;

	delete2dUint8Array(pixels, height);

	cout << "Done." << endl;
	return 0;
}
