#pragma once
#include "esp_dsp.h"
#include "esp_attr.h"
#include "../codec/CodecInterface.hpp"

//! DSP block to execute a FIR filter
/*!
  Fast FIR filter that uses ESP32S3 fast dsp functions, the length of the filter must be a multiple of 4
*/
class QuadFIR {
private:
    float * fir_matrix;
    float * mem_matrix;
    float * res_matrix;
    float * past;
    int index;
    int size;
    void IRAM_ATTR process4(float * in, float * out);
public:
    //! QuadFIR constructor
    /*!
      \param size the size of the FIR filter
    */
    QuadFIR(int size);
    float * getInputBuffer();
    void load(float * filter);
    void load_blend(float * buffer, float blend);
    void load_smooth_blend(float * buffer, float blend, float smooth);
    void IRAM_ATTR exec(float * in, float * out, int length);
};
