#pragma once
#include "dsp/AudioBlock.hpp"
#include "NodeFloat.hpp"
 
class BasicDelay: public AudioBlock {
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
    BasicDelay(Node * parent, Node *root); //Class constructor
    bool compile(); //Inherited from AudioBlock
    static bool exec(BasicDelay * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]); //DSP function is a static function
};