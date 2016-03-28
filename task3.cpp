// Phase 3
//
// Task 3: Frame matching for each feature type
//
// Description:
//     Each feature type (task 1(a-d) and task 2) associate with a frame
//     multiple feature values. For example in task 1, there were multiple
//     8x8 frame blocks in a frame, and for each of those blocks, we computed
//     histogram values, DCT coefficients, etc. In task 2, we computed 
//     DWT coefficients for the entire frame, for each frame.
//
//     For task 3, we implement frame matching by creating a vector representing
//     the components for that frame for a given feature type. For example, 
//     if a frame is 16x24 pixels and we chose to retain the 7 most significant
//     DCT coefficients for each 8x8 block (of which there are 6 in the frame),
//     then we would create a 42-length vector: 7 coefficients for each of the 
//     6 blocks in the frame. Similar processes apply for the other feature types.
//
//     This way, we can compute vectors that describe the significant components
//     for each frame for a given feature type. We then obtain the query frame's
//     vector and consider that the reference. We can then compute the score of 
//     of every other frame as being the Euclidian distance between the current 
//     frame's component vector and the reference frame's component vector. With
//     this scheme, the best matching frames are those with the smallest distances.

#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

typedef pair<int, double> frame_match;

string removeExtension(string name) {
    string::size_type index = name.rfind('.');
    
    if (index != string::npos) {
        return name.substr(0, index);
    }
    else {
        return name;
    }
}

// Sort a vector
template <typename T>
vector<size_t> sort_indices(vector<T> const& values) {
    vector<size_t> indices(values.size());
	
	for (size_t i = 0; i < values.size(); i++) {
		indices[i] = i;
	}

    sort(begin(indices), end(indices),
        [&](size_t a, size_t b) { return values[a] < values[b]; }
    );
	
    return indices;
}

string executeTask(string command) {
	FILE *outfp = popen(command.c_str(), "r");
	
	if (outfp == NULL) {
		cout << "Error executing task. Exiting." << endl;
		exit(-1);
	}
	
	char buffer[128];
	string outfilename;
	
	// Read from the command's stdout 
	while (fgets(buffer, sizeof(buffer), outfp) != NULL) {
		outfilename.append(buffer);
	} 
	
	return outfilename;
}

Mat extractTask1Features(int task, string featurefilename, int fcount, int blockWidth, int blockHeight, int n) {
	// Task 1(d) does not have information for the last frame
	if (task == 4)
		fcount--;
		
	// Each frame vector contains m components, so the matrix is {fcount x m}
	// The scores/distance vector is of length fcount
	Mat features = Mat::zeros(fcount, blockWidth * blockHeight * n, CV_32S);
	
	// Read the feature file line by line
	ifstream featurefile(featurefilename);
	int findex, blockX, blockY, compindex, compvalue;
	string line;
	
	while (!featurefile.eof()) {
		getline(featurefile, line);
		sscanf(line.c_str(), "%d,%d,%d,%d,%d", &findex, &blockX, &blockY, &compindex, &compvalue);
		// featurefile >> findex;
		// featurefile >> blockX;
		// featurefile >> blockY;
		// featurefile >> compindex;
		// featurefile >> compvalue;
		
		features.at<int>(findex, n*blockHeight*blockX + n*blockY + compindex) = compvalue;
	}
	
	return features;
}

Mat extractTask2Features(string featurefilename, int fcount, int m) {
	// Each frame vector contains m components, so the matrix is {fcount x m}
	// The scores/distance vector is of length fcount
	Mat features = Mat::zeros(fcount, m, CV_32S);
	
	// Read the feature file line by line
	ifstream featurefile(featurefilename);
	int findex, compindex, compvalue;
	string line;
	
	while (!featurefile.eof()) {
		getline(featurefile, line);
		sscanf(line.c_str(), "%d,%d,%d", &findex, &compindex, &compvalue);
		// featurefile >> findex;
		// featurefile >> compindex;
		// featurefile >> compvalue;
		
		features.at<int>(findex, compindex) = compvalue;
	}
	
	return features;
}

vector<frame_match> findMatchingFrames(Mat features, int frameid, int nummatches) {
	// Create vectors for our scores and matches
	vector<double> scores(features.rows);
	vector<frame_match> matches(nummatches);
	
	// Find the query vector (for the given frameid)
	Mat queryvector = features.row(frameid);
	
	// Compute the distance scores for each 
	for (int i = 0; i < features.rows; i++) {
		double score;
		
		if (i == frameid)
			score = numeric_limits<double>::infinity();
		else
			score = norm(features.row(i), queryvector);
		
		scores[i] = score;
	}
	
	// Rank the distance scores
	vector<size_t> ranked = sort_indices(scores);
	
	for (int i = 0; i < nummatches; i++) {
		matches[i] = make_pair(ranked[i], scores[ranked[i]]);
	}
	
	return matches;
}

void displayMatches(string filename, VideoCapture &cap, int fwidth, int fheight, int frameid, vector<frame_match> &matches) {
	Mat original, frame;
	cap.set(CV_CAP_PROP_POS_FRAMES, frameid);
	cap.read(original);
	
	vector<Mat> images(11);
	images[0] = original;
	
	for (int i = 0; i < 10; i++) {
		cap.set(CV_CAP_PROP_POS_FRAMES, matches[i].first);
		cap.read(frame);
		
		images[i + 1] = frame;
	}
	
	int spacing = 20;
	int fontheight = 80;
	
	int width = max(fwidth, 250);
	int height = fheight;
	
	int combwidth = spacing*5 + width*4;
	int combheight = spacing*4 + fontheight*3 + height*3;
	
	Mat combined(combheight, combwidth, CV_8UC3, Scalar(255,255,255));
	
	for (int i = 0; i < 11; i++) {
		int imcol = i % 4;
		int imrow = i / 4;
		
		int x = spacing + imcol*(width+spacing);
		int y = spacing + imrow*(height+fontheight+spacing);
		
		Mat roi = combined(Rect(x + (width - fwidth)/2, y, fwidth, fheight));
		images[i].copyTo(roi);
		
		// Write the match data.
		string line1, line2, line3;
		
		if (i == 0) {
			line1 = "Reference Frame: " + to_string(frameid);
		}
		else {
			frame_match match = matches[i - 1];
			line1 = "Match: " + to_string(i);
			line2 = "Frame: " + to_string(match.first);
			line3 = "Score: " + to_string(match.second);
		}
		
		// Center the label
		int baseline;
		Size textsize1 = getTextSize(line1, CV_FONT_HERSHEY_PLAIN, 1, 1, &baseline);
		Size textsize2 = getTextSize(line2, CV_FONT_HERSHEY_PLAIN, 1, 1, &baseline);
		Size textsize3 = getTextSize(line3, CV_FONT_HERSHEY_PLAIN, 1, 1, &baseline);
		
		putText(combined, line1, Point(x + (width - textsize1.width)/2, y + height + 1*(5 + textsize1.height)), CV_FONT_HERSHEY_PLAIN, 1, Scalar(0,0,0));
		putText(combined, line2, Point(x + (width - textsize2.width)/2, y + height + 2*(5 + textsize2.height)), CV_FONT_HERSHEY_PLAIN, 1, Scalar(0,0,0));
		putText(combined, line3, Point(x + (width - textsize3.width)/2, y + height + 3*(5 + textsize3.height)), CV_FONT_HERSHEY_PLAIN, 1, Scalar(0,0,0));
	}
	
	imwrite(filename + ".jpg", combined);
	cout << "[*] Wrote frame matches and scores to " << filename << ".jpg" << endl;
	
	namedWindow("Task 3");
	imshow("Task 3", combined);
	waitKey(0);
	destroyWindow("Task 3");
}

int main(int argc, const char * argv[]) {
	string path, filename, videoname;
	int frameid, n, m;
	
	Mat frame, ychan;
	
	int width, height;
	int findex, fcount;
	
	cout << "Enter the path of the folder containing the videos: ";
	cin >> path;
	
	// Obtain the filename the user wants to operate on in this run
	cout << "Enter video file name: ";
	cin >> filename;
	videoname = removeExtension(filename);
	
	// Obtain the query frame id
	cout << "Enter the index of query frame: ";
	cin >> frameid;
	
	// Obtain the n and m parameters
	cout << "Enter the value of n: ";
	cin >> n;
	cout << "Enter the value of m: ";
	cin >> m;
	
	// Open a capture object to the video
	VideoCapture cap(path + "/" + filename);
	if (!cap.isOpened()) {
		cout << endl << "[*] ERROR: Couldn't open the video for processing. Exiting." << endl;
		return -1;
	}
	
	fcount = cap.get(CV_CAP_PROP_FRAME_COUNT);
	width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	int choice;
	string command, featurefilename;
	Mat features;
	vector<frame_match> matches;
	
	do {
		// Obtain the choice of sub-task
		cout << endl << "Feature types: " << endl;
		cout << "    1. Block histogram" << endl;
		cout << "    2. Block 2D-DCT" << endl;
		cout << "    3. Block 2D-DWT" << endl;
		cout << "    4. Block difference histogram" << endl;
		cout << "    5. Frame 2D-DWT" << endl;
		cout << "    6. Exit" << endl;
		cout << "Enter the feature type to analyze: ";
		cin >> choice;
		cout << endl;
		
		switch (choice) {
			case 1:
			case 2:
			case 3:
			case 4:
				command = "./task1 \"" + path + "\" \"" + filename + "\" " + to_string(choice) + " " + to_string(n);
				featurefilename = executeTask(command);
				features = extractTask1Features(choice, featurefilename, fcount, width/8, height/8, n);
				matches = findMatchingFrames(features, frameid, 10);
				break;
			
			case 5:
				command = "./task2 \"" + path + "\" \"" + filename + "\" " + to_string(m); 
				featurefilename = executeTask(command);
				features = extractTask2Features(featurefilename, fcount, m);
				matches = findMatchingFrames(features, frameid, 10);
				break;
				
			case 6:
				return 0;
		}
		
		displayMatches(featurefilename, cap, width, height, frameid, matches);
	}
	while (choice != 6);
	
    return 0;
}
