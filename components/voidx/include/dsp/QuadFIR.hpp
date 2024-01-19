#pragma once
#include "esp_dsp.h"
#include "../codec/CodecInterface.hpp"

class QuadFIR {
private:
    float * fir_matrix;
    float * mem_matrix;
    float * res_matrix;
    float past[3];
    int index;
    int size;
    void process4(float * in, float * out);
public:
    QuadFIR(int size);
    float * getInputBuffer();
    void load(float * filter);
    void load_blend(float * buffer, float blend);
    void load_smooth_blend(float * buffer, float blend, float smooth);
    void exec(float * in, float * out, int length);
};
