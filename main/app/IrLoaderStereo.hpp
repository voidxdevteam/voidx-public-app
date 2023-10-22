#pragma once
#include "dsp/AudioBlock.hpp"
#include "dsp/QuadFIR.hpp"
#include "System.hpp"
#include "NodeParList.hpp"

#define FIR_LENGTH  1024

class IrLoaderStereo: public AudioBlock {
private:
    NodeParList * left_ir_node;
    NodeParList * right_ir_node;
    Node * input_mode;
    Node * output_mode;
    Node * onoff;
    Node * lvl;
    Node * left_gain;
    Node * right_gain;
    Node * left_onoff;
    Node * right_onoff;
    QuadFIR * left_fir;
    QuadFIR * right_fir;
    float level;
    float lgain;
    float rgain;
    float left_ir[FIR_LENGTH];
    float right_ir[FIR_LENGTH];
public:
    IrLoaderStereo(Node * parent, Node * parentControl);
    void compile();
    void exec(float data[SAMPLING_CHANNELS][SAMPLING_FRAME]);
};
