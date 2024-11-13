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
    //! Loads a FIR filter of the specified size
    /*!
      \param filter array of the filter coefficients
    */
    void load(float * filter);
    
    //! Loads a FIR filter of the specified size and blends it with the identity FIR
    /*!
      \param filter array of the filter coefficients.
      \param blend blend coefficient [0;1]: 0 unit filter, 1 filter loaded from buffer array.
    */
    void load_blend(float * buffer, float blend);
    
    //! Loads a FIR filter in a smooth way in order to reduce bumping. It also blends the filter with the identity FIR
    /*!
      \param filter array of the filter coefficients.
      \param blend blend coefficient [0;1]: 0 unit filter, 1 filter loaded from buffer array.
      \param smooth smoothing coefficient [0;1]: 1 no smoothing, 0 infinite time smoothing.
    */
    void load_smooth_blend(float * buffer, float blend, float smooth);
    void * operator new(size_t size);
    void exec(float * in, float * out, int length);
};
