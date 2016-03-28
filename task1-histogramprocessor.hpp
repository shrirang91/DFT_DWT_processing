#ifndef TASK1_HISTOGRAMPROCESSOR_HPP
#define TASK1_HISTOGRAMPROCESSOR_HPP

#include "task1-blockprocessor.cpp"

using namespace cv;
using namespace std;

class HistogramProcessor : public BlockProcessor {
	
	public:
		HistogramProcessor(VideoCapture &capture, string name, bool isDifferenceProcessor) 
			: BlockProcessor(capture, name)
			, _isDifferenceProcessor(isDifferenceProcessor) { };
		
		string getOutputFileName();
		void processBlock(Mat frame, int frameIndex, int blockX, int blockY);
		void setInput(int n);
	
	protected:
		void readInput();
		
		int _bins;
		bool _isDifferenceProcessor;
};

#endif