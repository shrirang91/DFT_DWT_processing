#ifndef TASK1_BLOCKPROCESSOR_HPP
#define TASK1_BLOCKPROCESSOR_HPP

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

/*
 * The typical life cycle of a BlockProcessor sub-class instance:
 *
 *	 - constructor(capture, name)
 *
 *   - initialize()
 *       - readInput()
 *       - createOutputFile()
 *           - getOutputFileName()
 *
 *   - [loop for each block]
 *       - processBlock(frame, frameIndex, blockX, blockY)
 *
 *   - [end]
 *
 *
 *
 * Sub-classes of BlockProcessor should implement the following:
 *
 *   - void setInput(int n):
 *          This is called by the Task 1 driver if providing input values
 *          manually to the processor. The Task 1 driver will call the
 *          "void dontReadInput()" function before calling this function.
 *
 *   - void readInput():
 * 			This is called by BlockProcessor's "void initialize()". You should
 * 			do any reading of user input here.
 *
 *   - string getOutputFileName():
 * 			This is called by BlockProcessor's "void createOutputFile()". You
 * 			should return the name of the output file here.
 *
 *   - void processBlock(Mat frame, int frameIndex, int blockX, int blockY):
 * 			This is called by the Task 1 driver. The arguments are the pixel
 * 			contents of the current frame; the index of the current frame;
 * 			the x coordinate of the block; the y coordinate of the block.
 *
 *			Note: for example, the 8x8 block with its top-left corner at
 *			pixel coordinate (32, 72) will have block coordinates (4, 9).
 *
 *			You should process the block's pixels here and write the output
 * 			into the _outfile field.
 */
class BlockProcessor {

	public:
		BlockProcessor(VideoCapture &capture, string name) {
			_capture = capture;
			_name = name;
		}

		void dontReadInput() {
			_dontReadInput = true;
		}

		void initialize() {
			if (!_dontReadInput)
				this->readInput();

			this->createOutputFile();
		};

		virtual string getOutputFileName() = 0;
		virtual void processBlock(Mat frame, int frameIndex, int blockX, int blockY) = 0;
		virtual void setInput(int n) = 0;

	protected:
		virtual void readInput() = 0;

		void createOutputFile() {
			//writing std file
			_outfile.open(this->getOutputFileName());
			//writing binary
			//_outfileb.open(getOutputFileName(), ios::out | ios::binary);
		}

		VideoCapture _capture;
		string _name;
		ofstream _outfileb;
		ofstream _outfile;
		bool _dontReadInput = false;
};

#endif
