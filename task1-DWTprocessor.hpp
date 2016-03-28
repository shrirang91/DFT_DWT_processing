#ifndef TASK1_DWTPROCESSOR_HPP
#define TASK1_DWTPROCESSOR_HPP

#include "task1-blockprocessor.cpp"

using namespace cv;
using namespace std;

class DWTProcessor : public BlockProcessor {

    public:
        DWTProcessor(VideoCapture &capture, string name)
            : BlockProcessor(capture, name) { };
        
        string getOutputFileName();
        void processBlock(Mat frame, int frameIndex, int blockX, int blockY);
        void setInput(int n);
        
    protected:
        void readInput();
        
        Mat generateHaarTransform(int size);
        Mat generateInverseHaarTransform(int size);
        void applyDWT(Mat &matrix, int size);
        void applyInverseDWT(Mat &matrix, int size);
        
        int _numSignificantWavelets;
};

#endif