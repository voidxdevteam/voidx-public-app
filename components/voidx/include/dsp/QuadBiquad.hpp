#pragma once
#include "esp_dsp.h"
#include "esp_attr.h"

class QuadBiquad {
private:
    float * w;
    float * coeffs;
public:
    QuadBiquad();
    void set_coeffs(float b0, float b1, float b2, float a1, float a2);
    void set_lohi_1_order(float freq_lo_hz, float freq_hi_hz);
    void set_lohi_1_order(float freq_lo_hz, float freq_hi_hz, float scale);
    void set_lpf_2_order(float freq_hz, float q);
    void set_hpf_2_order(float freq_hz, float q);
    void set_lpf_shelf(float freq_hz, float q, float gain_db);
    void set_hpf_shelf(float freq_hz, float q, float gain_db);
    void set_peaking(float freq_hz, float q, float gain_db);
    void scale(float scale);

    void * operator new(size_t size);
    void exec(float * in, float * out, int length);
};
