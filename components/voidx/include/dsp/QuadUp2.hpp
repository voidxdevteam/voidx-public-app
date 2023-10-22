#pragma once
#include "esp_dsp.h"
#include "QuadFIR.hpp"
#include "../../codec/CodecInterface.hpp"

class QuadUp2 {
private:
	int index;
    int size;
    float * h1;
    float * buffer;
    fir_f32_t fir_data;
public:
    QuadUp2(int size);
    void exec(float * in, float * out, int length);
};
