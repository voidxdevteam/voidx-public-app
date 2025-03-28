#pragma once
#include "esp_dsp.h"
#include "esp_attr.h"
#include "../codec/CodecInterface.hpp"

//! DSP block to execute a clipping funcion
/*!
  Signal clipping that uses ESP32S3 fast dsp functions, the length of the input block must be a multiple of 4
*/
class QuadDIST {
private:
    float * up_matrix;
    float * down_matrix;
    float * input_mem_matrix; 
    float * dist_mem_matrix;
    float * LUT;
    float * output_matrix;
    float * past_in;
    float * past_out;
    float * LUT_tanh;
    float * LUT_tanh2;
    int up_index;
    int down_index;
    int offset;
    int filter_size;
    int upsampling;
    int dist_cycles;

    void createLUT();
    void process4(float * in, float * out);
public:
    //! QuadDIST constructor
    /*!
      \param filter_size the size of the anlialiasing filter
      \param upsampling the upsampling factor
    */
    QuadDIST(int filter_size, int upsampling);
    void load_filter();
    void setCurve(float alpha);
    void load_filter(float * filter);
    void * operator new(size_t size);
    void exec(float * in, float * out, int length);
};
