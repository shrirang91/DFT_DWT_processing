#include "task1-dwtprocessor.hpp"
#include <iomanip>
#include <cmath>

void DWTProcessor::readInput() {
	// Read the number of wavelets from user input to keep for this DWT 
	cout << endl << "Enter the number of the wavelet components to retain: ";
	cin >> _numSignificantWavelets;
}

void DWTProcessor::setInput(int n) {
	_numSignificantWavelets = n;
}

string DWTProcessor::getOutputFileName() {
	return _name + "_blockdwt_" + to_string(_numSignificantWavelets) + ".bwt";
}

Mat DWTProcessor::generateHaarTransform(int size) {
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

Mat DWTProcessor::generateInverseHaarTransform(int size) {
	return 2 * generateHaarTransform(size);
}

void DWTProcessor::applyDWT(Mat &matrix, int size) {
	Mat H = generateHaarTransform(size);
	Mat roi = matrix(Rect(0,0,size,size));
	
	int half = size/2;
	
	// 2D-DWT: 
	//     First multiply by the Haar transform matrix (horizontal), then multiply
	//     the transpose of that result with the Haar transform (vertical)
	//     Then rearrange the order of the rows and columns to achieve the corret result
	Mat transformed = (roi * H).t() * H;
	Mat colsOrdered = transformed.clone();
	
	for (int i = 0; i < half; i++) {
		transformed.col(2*i).copyTo(colsOrdered.col(i));
		transformed.col(2*i + 1).copyTo(colsOrdered.col(i+half));
	}
	
	for (int i = 0; i < half; i++) {
		colsOrdered.row(2*i).copyTo(roi.row(i));
		colsOrdered.row(2*i + 1).copyTo(roi.row(i+half));
	}
}

void DWTProcessor::applyInverseDWT(Mat &matrix, int size) {
	Mat IH = generateInverseHaarTransform(size);
	Mat roi = matrix(Rect(0,0,size,size));
	
	int half = size/2;
	
	// 2D-DWT: 
	//     First rearrange the order of the rows and columns, 
	//     then multiply by the Haar inverse transform matrix (horizontal), then multiply
	//     the transpose of that result with the Haar inverse transform (vertical).
	Mat colsOrdered = roi.clone();
	Mat transformed = roi.clone();
	
	for (int i = 0; i < half; i++) {
		roi.col(i).copyTo(colsOrdered.col(2*i));
		roi.col(i+half).copyTo(colsOrdered.col(2*i + 1));
	}
	
	for (int i = 0; i < half; i++) {
		colsOrdered.row(i).copyTo(transformed.row(2*i));
		colsOrdered.row(i+half).copyTo(transformed.row(2*i + 1));
	}
	
	Mat inverted = (transformed * IH).t() * IH;
	inverted.copyTo(roi);
}

void outputBlock(Mat data) {
	for (int i = 0; i < data.size().height; i++) {
		for (int j = 0; j < data.size().width; j++) {
			cout << setw(4) << round(data.at<float>(i, j)) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void DWTProcessor::processBlock(Mat frame, int frameIndex, int blockX, int blockY) {
	cout << "[*] Processing block (" << blockX << "," << blockY << ") in frame " << frameIndex << endl;
	
	frame = frame(Rect(blockX*8, blockY*8, 8, 8));
	frame.convertTo(frame, CV_32F);
	
	// Mat original = frame.clone();
	
	// Apply the DWT enough times to obtain single coefficients
	applyDWT(frame, 8);
	applyDWT(frame, 4);
	applyDWT(frame, 2);

	// Count the significant DWT components
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
			_outfile << frameIndex << ','
					 << blockX << ','
					 << blockY << ','
					 << counted << ','
					 << round(frame.at<float>(u,v))
					 << endl;
			
			counted++;
			
			// // Zero the non-significant components for debugging
			// if (counted > _numSignificantWavelets)
			// 	frame.at<float>(u,v) = 0;
			
			if (counted >= _numSignificantWavelets)
				break;
		}
			
		if (counted >= _numSignificantWavelets)
			break;
	}
	
	// // Output the inverted DWT transform for debugging's sake
	
	// outputBlock(frame);
	
	// applyInverseDWT(frame, 2);
	// applyInverseDWT(frame, 4);
	// applyInverseDWT(frame, 8);
	
	// outputBlock(frame);
	
	// Mat diff = original - frame;
	// float totaldiff = 0;
	
	// for (int i = 0; i < 8; i++) {
	// 	for (int j = 0; j < 8; j++) {
	// 		float val = diff.at<float>(i, j);
	// 		totaldiff += abs(val);
	// 	}
	// }
	
	// outputBlock(diff);
	
	// cout << totaldiff << endl;
}

