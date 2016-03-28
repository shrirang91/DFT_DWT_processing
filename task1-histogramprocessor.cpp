#include "task1-histogramprocessor.hpp"

void HistogramProcessor::readInput() {
	// Read the number of bins for this histogram
	cout << endl << "Enter the number of the bins in the histogram: ";
	cin >> _bins;
}

void HistogramProcessor::setInput(int n) {
	_bins = n;
}

string HistogramProcessor::getOutputFileName() {
	if (_isDifferenceProcessor)
		return _name + "_diff_" + to_string(_bins) + ".dhc";
	else
		return _name + "_hist_" + to_string(_bins) + ".hst";
}

void HistogramProcessor::processBlock(Mat frame, int frameIndex, int blockX, int blockY) {
	if (frame.depth() != CV_32S)
		frame.convertTo(frame, CV_32S);

	if (!_isDifferenceProcessor)
	{
				//creating bins and assigning pixel the quantized values.
					int binIndex=256/_bins;
					int binValue[_bins+1];
					int binCount[_bins];
					int i;

				//initalizing binCount to zero and creating an array to store the bin values.
				for(i =0;i<_bins;i++)
					{
						binValue[i]=i*binIndex;
						binCount[i]=0;
					}
					binValue[i]=256;

				//calculating the bin histogram for each block and writign it out to a file.
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							int bx = blockX * 8 + i;
							int by = blockY * 8 + j;
							for(int k=0;k<_bins;k++){
								if(frame.at<int>(by,bx) >= binValue[k] && frame.at<int>(by,bx) < binValue[k+1])
									binCount[k]+=1;
							}
						}
					}

					for(int i=0;i<_bins;i++)
					//writing to std file
				_outfile<<frameIndex<<','<<blockY<<','<<blockX<<','<<i<<','<<binCount[i]<<endl;
				//writing binary
				/*
				_outfileb.write(((char*)(&frameIndex)),sizeof(int));
				_outfileb.write(((char*)(&blockY)),sizeof(int));
				_outfileb.write(((char*)(&blockX)),sizeof(int));
				_outfileb.write(((char*)(&binValue[k])),sizeof(int));
				_outfileb.write(((char*)(&binCount[k])),sizeof(int));
				*/

					//displaying the histogram for quantized frame blocks
					/*for(int i=0;i<_bins;i++)
						cout<<endl<<binCount[i]<<"\t"<<endl;

					if (_isDifferenceProcessor)
						cout << "[*] Processing block differences (" << blockX << "," << blockY << ") in frames " << frameIndex << " and " << (frameIndex + 1) << endl;
					else
						cout << "[*] Processing block (" << blockX << "," << blockY << ") in frame " << frameIndex << endl;
						*/

					//
					//
					// If _isDifferenceProcessor is true, then frame will contain the difference values
					// for that block between frameIndex and (frameIndex + 1). The range of the values
					// will be between -255 to 255.
					//
					// Otherwise, frame will contain the pixel values for the block at frameIndex. The
					// range of values will be between 0 and 255.
					//
					//

					// Convert the frame to 32 bit signed integers if it is not already.


					// Debugging: print the output of the frame block;
					/*for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							int bx = blockX * 8 + i;
							int by = blockY * 8 + j;

							cout << frame.at<int>(by, bx) << " ";
						}
						cout << endl;
					}*/
				//	cout << endl;
		}// if close--- normal histogram generator.
	else
	{
		int binIndex=256/_bins;
		int binValue[_bins+1];
		int binCount[_bins];
		int i;

	//initalizing binCount to zero and creating an array to store the bin values.

		for(i=0;i<_bins;i++)
		{
			if(i==0)
				binValue[i]=-255;
			else{
			binValue[i]=binValue[i-1]+(2*binIndex);
			}
			binCount[i]=0;

		}
		binValue[i]=256;

		//display the binValue array
		/*
		for(int i=0;i<=_bins;i++)
			cout<<binValue[i]<<endl;
		*/
			//calculating the bin histogram for each block and writign it out to a file.
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						int bx = blockX * 8 + i;
						int by = blockY * 8 + j;
						for(int k=0;k<_bins;k++){
							if(frame.at<int>(by,bx) >= binValue[k] && frame.at<int>(by,bx) < binValue[k+1])
								binCount[k]+=1;
						}
					}
				}

				for(int i=0;i<_bins;i++)
				//writing to std file
			_outfile<<frameIndex<<','<<blockY<<','<<blockX<<','<<i<<','<<binCount[i]<<endl;
			//writing binary
			/*
			_outfileb.write(((char*)(&frameIndex)),sizeof(int));
			_outfileb.write(((char*)(&blockY)),sizeof(int));
			_outfileb.write(((char*)(&blockX)),sizeof(int));
			_outfileb.write(((char*)(&binValue[k])),sizeof(int));
			_outfileb.write(((char*)(&binCount[k])),sizeof(int));
			*/

	}	//close else--- difference histogram generator
}
