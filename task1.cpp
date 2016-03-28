// Phase 3
//
// Task 1: frame block processing
//      [ ] Histogram (n-bin)
//      [x] 2D-DCT
//      [ ] 2D-DWT
//      [ ] Difference

#include <fstream>
#include <iostream>
#include <algorithm>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "task1-blockprocessor.hpp"
#include "task1-dctprocessor.hpp"
#include "task1-dwtprocessor.hpp"
#include "task1-histogramprocessor.hpp"

using namespace std;
using namespace cv;

string removeExtension(string name) {
    string::size_type index = name.rfind('.');
    
    if (index != string::npos) {
        return name.substr(0, index);
    }
    else {
        return name;
    }
}

void blockStandardOut() {
	cout.setstate(ios::failbit);
}

void unblockStandardOut() {
	cout.clear();
}

int main(int argc, const char * argv[]) {
	// Mat f = (Mat_<uchar>(8, 8) <<
	// 		0,   0,   0,   0,   0,   0,   0,   0,
	// 		0,   0,   0,   0,   0,   0,   0,   0,
	// 		0,   0,  63, 127, 127,  63,   0,   0,
	// 		0,   0, 127, 255, 255, 127,   0,   0,
	// 		0,   0, 127, 255, 255, 127,   0,   0,
	// 		0,   0,  63, 127, 127,  63,   0,   0,
	// 		0,   0,   0,   0,   0,   0,   0,   0,
	// 		0,   0,   0,   0,   0,   0,   0,   0
	// );

	// VideoCapture capture;
	// DWTProcessor *p = new DWTProcessor(capture, string());
	// p->initialize();
	// p->processBlock(f, 0, 0, 0);
	// return -1;

    string path, filename, videoname;
	int choice, n;
	bool has_input = false;
	
	Mat frame, ychan;
	Mat frame2, ychan2;
	
	int width, height;
	int findex, fcount;
	BlockProcessor *processor;
		
	if (argc == 5) {
		path = argv[1];
		filename = argv[2];
		videoname = removeExtension(filename);
		choice = atoi(argv[3]);
		n = atoi(argv[4]);
		has_input = true;
		blockStandardOut();
	}
	
	if (!has_input) {
		cout << "Enter the path of the folder containing the videos: ";
		cin >> path;
		
		// Obtain the filename the user wants to operate on in this run
		cout << endl << "Enter video file name: ";
		cin >> filename;
		videoname = removeExtension(filename);
		
		// Obtain the choice of sub-task
		cout << endl << "Sub-tasks: " << endl;
		cout << "    1. Histogram (n-bin)" << endl;
		cout << "    2. 2D-DCT" << endl;
		cout << "    3. 2D-DWT" << endl;
		cout << "    4. Difference between frames" << endl;
		cout << "Enter the number of the sub-task to execute: ";
		cin >> choice;
	}
	
	// Open a capture object to the video
	VideoCapture cap(path + "/" + filename);
	if (!cap.isOpened()) {
		cout << endl << "[*] ERROR: Couldn't open the video for processing. Exiting." << endl;
		return -1;
	}
	
	fcount = cap.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "[*] Frame count for video is: " << fcount << endl;
	
	width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	cout << "[*] Frame size for video is: " << width << " x " << height << endl;
	
	switch (choice) {
		case 1:
			processor = new HistogramProcessor(cap, videoname, /* isDifferenceProcessor = */ false);
			break;
			
		case 2:
			processor = new DCTProcessor(cap, videoname);
			break;
			
		case 3:
			processor = new DWTProcessor(cap, videoname);
			break;
			
		case 4:
			processor = new HistogramProcessor(cap, videoname, /* isDifferenceProcessor = */ true);
			break;
	}
	
	if (has_input) {
		processor->dontReadInput();
		processor->setInput(n);
	}
	
	processor->initialize();
	
	// Extract and process each frame
	for (findex = 0; findex < fcount; findex++) {
		// If we are processing the differences and this is the last frame, stop.
		if (choice == 4 && findex + 1 == fcount)
			break;
			
		cap.set(CV_CAP_PROP_POS_FRAMES, findex);
		
		if(!cap.read(frame)) {
			cout << endl << "[*] ERROR: Couldn't extract frame " << findex << ". Stopping." << endl;
			break;
		}
		
		// Obtain the Y component of the frame (the grayscale component)
		cvtColor(frame, ychan, CV_BGR2GRAY);
		
		// Get the next frame and Y component if we are doing the difference processor
		if (choice == 4) {
			cap.set(CV_CAP_PROP_POS_FRAMES, findex + 1);
			if(!cap.read(frame2)) {
				cout << endl << "[*] ERROR: Couldn't extract frame " << (findex + 1) << ". Stopping." << endl;
				break;
			}
			cvtColor(frame2, ychan2, CV_BGR2GRAY);
			
			// Set the frame to the difference between the two.
			ychan.convertTo(ychan, CV_32S);
			ychan2.convertTo(ychan2, CV_32S);
			ychan = ychan - ychan2;
		}
		
		// Iterate through each 8x8 block of the frame
		for (int blockX = 0; blockX < width/8; blockX++) {
			for (int blockY = 0; blockY < height/8; blockY++) {
				processor->processBlock(ychan, findex, blockX, blockY);
			}
		}
		
		cout << "[*] Processed frame " << findex << endl;
	}
	
	if (has_input) {
		unblockStandardOut();
		cout << processor->getOutputFileName();
	}
	else {
		cout << "[*] Wrote processed output to " << processor->getOutputFileName() << endl;
	}
	
    return 0;
}
