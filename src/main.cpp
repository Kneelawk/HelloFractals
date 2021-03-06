#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <chrono>

#include "fractalthread.h"
#include "array_utils.h"
#include "image_writer.h"
#include "pixel_utils.h"
#include "program/programdriver.h"
#include "program/parsingexception.h"
#include "program/contextconfigurator.h"
#include "program/programrunner.h"

using namespace std;

const bool crosshair = true;
const bool mandelbrot = true;

uint32_t width = 500, height = 500;

double rpart = -0.8006725, ipart = -0.158388;
double crosshairX = rpart, crosshairY = ipart;

double planeWidth = 0.3, planeHeight = 0.3;
// double planeCenterX = 0.0, planeCenterY = 0.0;
double planeCenterX = crosshairX, planeCenterY = crosshairY;
double planeStartX = planeCenterX - planeWidth / 2, planeStartY = planeCenterY - planeHeight / 2;

uint32_t iterations = 500;

int main(int argc, char **argv) {
	ifstream in("test-input.txt");

	FractalProgram::ProgramDriver driver;
	std::shared_ptr<FractalProgram::Program> program;
	std::complex<double> value;

	try {
		std::cout << "Parsing program...\n";
		program = driver.parse(in);
	} catch (FractalProgram::ParsingException &e) {
		std::cerr << "Error:\n";
		std::cerr << e.what() << std::endl;
		std::cerr << "Exiting...\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Program parsed.\n";

	std::cout << program->to_string() << std::endl;

	std::cout << "Creating Contexts...\n";

	FractalProgram::ContextConfigurator config;
	config.enableStandardFunctions();

	FractalProgram::ValidationContext vctx;
	config.apply(vctx);
	vctx.currentScope()->defineVariable("z");
	vctx.currentScope()->defineVariable("c");

	try {
		std::cout << "Validating program...\n";
		program->validate(vctx);
	} catch (FractalProgram::ValidationException &e) {
		std::cerr << "Validation error:\n";
		std::cerr << e.what() << std::endl;
		std::cerr << "Exiting...\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Program validated.\n";

	FractalProgram::ProgramRunner runner(program, config);

	// allocate 2d array of each pixel
	cout << "Allocating pixel array..." << endl;
	uint8_t **pixels = create2dUint8Array(height, width * 4);

	// create a ValueGenerator with the values for the fractal used by each FractalThread
	cout << "Creating a value generator..." << endl;
	ValueGenerator g(width, height, planeWidth, planeHeight, planeStartX, planeStartY, mandelbrot, iterations, rpart, ipart, runner);

	// get the number hardware of threads
	uint32_t n_threads = thread::hardware_concurrency() + 2;
	cout << "Using " << n_threads << " threads" << endl;

	// create an array of threads depending on how many hardware threads there are
	cout << "Starting the generator threads..." << endl;
	FractalThread *threads = new FractalThread[n_threads];
	uint32_t leftOver = width * height % n_threads;
	size_t i;

	// timing
	chrono::time_point<chrono::steady_clock> genStart = chrono::steady_clock::now();

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

	// print time
	chrono::time_point<chrono::steady_clock> genEnd = chrono::steady_clock::now();
	chrono::milliseconds genDiff = chrono::duration_cast<chrono::milliseconds>(genEnd - genStart);

	cout << "Fractal generator threads finished in " << genDiff.count() << " ms." << endl;

	if (crosshair) {
		ImageLoc loc = g.complex2Image(ComplexLoc(crosshairX, crosshairY));
		cout << "Adding crosshair..." << endl;
		setCrosshair(pixels, width, height, loc.x, loc.y, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	cout << "Writing image..." << endl;

	// make sure output directory exists
	string outDir = "./output";

	if (access(outDir.c_str(), F_OK) == -1) {
		int result = mkdir(outDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	// find a filename that doesn't exist already
	int num = 0;
	stringstream ss;

	while (access([&ss, &outDir, &num]() {
	ss << outDir << "/output" << num << ".png";
	return ss.str();
	}().c_str(), F_OK) != -1) {
		num ++;
		ss.str(string());
	}

	ss.str(string());
	ss << outDir << "/output" << num << ".png";
	cout << "Writing to: " << ss.str() << endl;

	// write to the file
	writePNG(pixels, width, height, ss.str().c_str());

	cout << "Done writing image." << endl;

	delete[] threads;

	delete2dUint8Array(pixels, height);

	cout << "Done." << endl;
	return 0;

}




