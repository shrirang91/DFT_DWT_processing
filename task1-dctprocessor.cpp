#include "task1-dctprocessor.hpp"

#include <cmath>

void DCTProcessor::readInput() {
	// Read the number of frequencies to keep for this DCT
	cout << endl << "Enter the number of the frequency components to retain: ";
	cin >> _numSignificantFreqs;
}

void DCTProcessor::setInput(int n) {
	_numSignificantFreqs = n;
}

string DCTProcessor::getOutputFileName() {
	return _name + "_blockdct_" + to_string(_numSignificantFreqs) + ".bct";
}

void DCTProcessor::processBlock(Mat frame, int frameIndex, int blockX, int blockY) {
	cout << "[*] Processing block (" << blockX << "," << blockY << ") in frame " << frameIndex << endl;
	
	/*
	 * From page 8 of "lossy_compression_lectures.pdf":
	 *
	 *  f(i,j) = pixel (i,j)
	 * 	G(i,v) = 0.5 * C(v) * Σ(j=0..7){ cos((2j + 1)vπ / 16) * f(i,j) }
	 * 	F(u,v) = 0.5 * C(u) * Σ(i=0..7){ cos((2i + 1)uπ / 16) * G(i,v) }
	 *
	 *  C(ξ) =  if (ξ = 0) then (√2/2) else (1)
	 */
	
	// Create storage for f, G, and F 
	int f[8][8] = {0};
	double G[8][8] = {0};
	int F[8][8] = {0};
	
	// Copy the block data into f, normalized from [0, 255] to [-128, 127]
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int bx = blockX * 8 + i;
			int by = blockY * 8 + j;
			
			f[i][j] = frame.at<uchar>(by, bx) - 128;
		}
	}
	
	// Compute the G DCT coefficients
	for (int i = 0; i < 8; i++) {
		for (int v = 0; v < 8; v++) {
			double C = 1;
			double result = 0;
			
			for (int j = 0; j < 8; j++) {
				result += cos((2*j + 1) * v * M_PI / 16) * f[i][j];
			}
			
			if (v == 0)
				C = sqrt(2.0) / 2;
				
			result *= 0.5 * C;
			
			G[i][v] = result;
		}
	}
	
	// Compute the F DCT coefficients
	for (int u = 0; u < 8; u++) {
		for (int v = 0; v < 8; v++) {
			double C = 1;
			double result = 0;
			
			for (int i = 0; i < 8; i++) {
				result += cos((2*i + 1) * u * M_PI / 16) * G[i][v];
			}
			
			if (u == 0)
				C = sqrt(2.0) / 2;
				
			result *= 0.5 * C;
			
			F[u][v] = round(result);
		}
	}
	
	// Output the components in order of importance
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
				
			// // Output in the form of: 
			// // 	frame_id block_coord freq_comp_id value
			_outfile << frameIndex << ","
			         << blockX << ","
					 << blockY << ","
			         << counted << ","
			         << round(F[u][v])
					 << endl;
			
			counted++;
			
			if (counted >= _numSignificantFreqs)
				break;
		}
			
		if (counted >= _numSignificantFreqs)
			break;
		
	}
}