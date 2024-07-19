#pragma once
#include "dsp/AudioBlock.hpp"
#include "NodeFloat.hpp"
 
class DigitalDelay: public AudioBlock {
private:
    //Parameters
    NodeFloat * mix;
    NodeFloat * feedback; 
    NodeFloat * timeNode;
 
    //Low-level DSP parameters.
    float * delayLine; //Delay circular buffer
    int delayLineWritePointer; //Write index for the delay line.
    float mixDsp; //Blend level
    float feedbackDsp; //Feedback amount
    int delaySamplesDsp; //Delay length in samples
 
public:
    DigitalDelay(Node * parent, Node *root); //Class constructor
    void compile(); //Inherited from AudioBlock
    void exec(float data[SAMPLING_CHANNELS][SAMPLING_FRAME]); //Inherited from AudioBlock
};