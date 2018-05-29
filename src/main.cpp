#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

#include "fractalthread.h"
#include "array_utils.h"
#include "image_writer.h"
#include "program/programdriver.h"

using namespace std;

int main(int argc, char **argv) {
	ifstream in("test-input.txt");

	FractalProgram::ProgramDriver driver;
	driver.parse(in);

	/*
    // allocate 2d array of each pixel
	cout << "Allocating pixel array..." << endl;
	uint32_t width = 10000, height = 10000;
	uint8_t **pixels = create2dUint8Array(height, width * 4);

    // create a ValueGenerator with the values for the fractal used by each FractalThread
	cout << "Creating a value generator..." << endl;
	ValueGenerator g(width, height, 0.15, 0.15, -0.075, -0.075, false, 500, -0.8006725, -0.158388);

    // get the number hardware of threads
	uint32_t n_threads = thread::hardware_concurrency() + 2;
	cout << "Using " << n_threads << " threads" << endl;

    // create an array of threads depending on how many hardware threads there are
	cout << "Starting the generator threads..." << endl;
	FractalThread *threads = new FractalThread[n_threads];
	uint32_t leftOver = width * height % n_threads;
	size_t i;

    // start all the threads
	for (i = 0; i < n_threads; i++) {
		threads[i].generateImage(pixels, width, width * height / n_threads + (leftOver > i), i, n_threads, g);
	}

	// wait for each of the threads to finish
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

	// make sure output directory exists
	string outDir = "output/";

	if (access(outDir.c_str(), F_OK) == 0) {
		mkdir(outDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	// find a filename that doesn't exist already
	int num = 0;
	stringstream ss;

	while (access([&ss, &outDir, &num]() {
	ss << outDir << "output" << num << ".png";
	return ss.str();
	}().c_str(), F_OK) != -1) {
		num ++;
		ss.clear();
	}

	ss << outDir << "output" << num << ".png";

	// write to the file
	writePNG(pixels, width, height, ss.str().c_str());

	cout << "Done writing image." << endl;

	delete[] threads;

	delete2dUint8Array(pixels, height);

	cout << "Done." << endl;
	return 0;
	*/
}

