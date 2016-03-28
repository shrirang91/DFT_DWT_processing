// Phase 3
//
// Task 2: 2D-DWT on the entire frame

#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Mat generateHaarTransform(int size) {
	Mat H = Mat::zeros(size, size, CV_32F);
	
	// Generate the Haar wavelet transform programmatically
	// Source: http://www.bearcave.com/misl/misl_tech/wavelets/matrix/
	for (int i = 0; i < size/2; i++) {
		H.at<float>(i*2, i*2) = 0.5;
		H.at<float>(i*2, i*2 + 1) = 0.5;
		H.at<float>(i*2 + 1, i*2) = 0.5;
		H.at<float>(i*2 + 1, i*2 + 1) = -0.5;
	}
	
	return H;
}

Mat generateInverseHaarTransform(int size) {
	return 2 * generateHaarTransform(size);
}

void applyDWT(Mat &matrix, int width, int height) {
	Mat Hh = generateHaarTransform(width);
	Mat Hv = generateHaarTransform(height);
	Mat roi = matrix(Rect(0,0,width,height));
	
	int halfw = width/2;
	int halfh = height/2;
	
	// 2D-DWT: 
	//     First multiply by the Haar transform matrix (horizontal), then multiply
	//     the transpose of that result with the Haar transform (vertical)
	//     Then rearrange the order of the rows and columns to achieve the corret result
	Mat transformed = ((roi * Hh).t() * Hv).t();
	Mat colsOrdered = transformed.clone();
	
	for (int i = 0; i < halfw; i++) {
		transformed.col(2*i).copyTo(colsOrdered.col(i));
		transformed.col(2*i + 1).copyTo(colsOrdered.col(i+halfw));
	}
	
	for (int i = 0; i < halfh; i++) {
		colsOrdered.row(2*i).copyTo(roi.row(i));
		colsOrdered.row(2*i + 1).copyTo(roi.row(i+halfh));
	}
}

void processFrameDWT(VideoWriter &writer, ofstream &outfile, Mat data, int frameIndex, int width, int height, int numComponents) {
	// Convert the data to 32 bit float version
	data.convertTo(data, CV_32F);
	
	int dwtwidth = width, dwtheight = height;
	
	// Stop when our corner to operate on is less than 2 in any dimension
	while (dwtwidth >= 2 && dwtheight >= 2) {
		// Apply the DWT on the current top-left corner (width and height) of the frame
		applyDWT(data, dwtwidth, dwtheight);
		
		// Halve the corner size that we will operate on
		dwtwidth /= 2;
		dwtheight /= 2;
	}
	
	// Obtain the m most significant components
	int counted = 0;
	for (int d = 0; d < 16; d++) {
		for (int x = 0; x <= d; x++) {
			int u, v;
			
			// If we are on an even-numbered diagonal, iterate from the
			// bottom-left to the top-right; otherwise, do the reverse.
			if (d % 2 == 0) {
				v = x;
				u = d - x;
			}
			else {
				v = d - x;
				u = x;
			}
			
			// Don't count indices along the diagonal that are not valid
			if (u > 7 || v > 7)
				continue;
				
			// Write out this component to file
			outfile << frameIndex << ','
					 << counted << ','
					 << round(data.at<float>(u,v))
					 << endl;
			
			counted++;
			
			if (counted >= numComponents)
				break;
		}
			
		if (counted >= numComponents)
			break;
	}
	
	// Convert the data back to unsigned bytes
	data.convertTo(data, CV_8U);
	cvtColor(data, data, CV_GRAY2BGR);
	writer.write(data);
}

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
	string path, filename, videoname;
	int numComponents;
	bool has_input = false;
	
	Mat frame, ychan;
	
	int width, height;
	int findex, fcount;
	
	string outfilename;
	ofstream outfile;
	
	if (argc == 4) {
		path = argv[1];
		filename = argv[2];
		videoname = removeExtension(filename);
		numComponents = atoi(argv[3]);
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
		
		// Obtain the number of wavelet components
		cout << endl << "Enter the number of the wavelet components to retain: ";
		cin >> numComponents;
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
	
	// Create the output file
	outfilename = removeExtension(filename) + "_framedwt_" + to_string(numComponents) + ".fwt";
	outfile.open(outfilename);
	
	// Create the video file (debugging!)
	string outvideoname = outfilename + ".mov";
    int codec = CV_FOURCC('m', 'p', '4', 'v');
    VideoWriter writer;
    writer.open(outvideoname, codec, 24.0, Size(width,height), true);
    if (!writer.isOpened()) {
        cout << endl << "[*] FATAL: Couldn't open file to write video" << endl;
        return -1;
    }
	
	// Extract and process each frame
	for (findex = 0; findex < fcount; findex++) {
		if(!cap.read(frame)) {
			cout << endl << "[*] ERROR: Couldn't extract frame " << findex << ". Stopping." << endl;
			break;
		}
		
		// Obtain the Y component of the frame (the grayscale component)
		cvtColor(frame, ychan, CV_BGR2GRAY);
		
		// Process the ychan component
		processFrameDWT(writer, outfile, ychan, findex, width, height, numComponents);
		
		cout << "[*] Processed frame " << findex << endl;
	}
	
	if (has_input) {
		unblockStandardOut();
		cout << outfilename;
	}
	else {
		cout << "[*] Wrote processed output to " << outfilename << endl;
	}
	
    return 0;
}
