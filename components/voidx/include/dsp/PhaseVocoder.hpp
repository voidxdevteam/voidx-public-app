#pragma once
#include "esp_dsp.h"
#include "../codec/CodecInterface.hpp"

class PhaseVocoder {
private:
    float * twiddle;
    float * window;
    float * input_mem;
    float * output_mem;
    float * circshift;
    float * input_cplx;
    float * angle;
    float * magnitude;
    float * prev_angle;
    float * unwrap;
    float * yunwrap;
    float * rounded;
    float * ysangle;
    float * output_cplx;
    int index;
    int hop_size;
    int size;
    int phase;
    float shift;
    int first;
public:
    PhaseVocoder(int size);
    float * getInputBuffer();
    void setShift(float shift);
    void load(float * filter);
    void exec(float * in, float * out, int length);
};