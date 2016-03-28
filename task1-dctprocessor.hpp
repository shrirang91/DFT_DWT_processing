#ifndef TASK1_DCTPROCESSOR_HPP
#define TASK1_DCTPROCESSOR_HPP

#include "task1-blockprocessor.cpp"

using namespace cv;
using namespace std;

class DCTProcessor : public BlockProcessor {
	
	public:
		DCTProcessor(VideoCapture &capture, string name) 
			: BlockProcessor(capture, name) { };
		
		string getOutputFileName();
		void processBlock(Mat frame, int frameIndex, int blockX, int blockY);
		void setInput(int n);
		
	protected:
		void readInput();
		
		int _numSignificantFreqs;
};

#endif
