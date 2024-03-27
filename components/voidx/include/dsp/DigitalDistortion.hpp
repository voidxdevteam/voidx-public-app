#pragma once
#include "AudioProcessor.hpp"

#define DRIVE_CLIPPER_AA1_FILTER_LENGHT     64
#define DRIVE_CLIPPER_RESAMPLING_FACTOR     8

class DigitalDistortion {
    float clip;
    float buffer[SAMPLING_FRAME * DRIVE_CLIPPER_RESAMPLING_FACTOR + DRIVE_CLIPPER_AA1_FILTER_LENGHT];
    float buffer2[SAMPLING_FRAME * DRIVE_CLIPPER_RESAMPLING_FACTOR + DRIVE_CLIPPER_AA1_FILTER_LENGHT];
    float filter[DRIVE_CLIPPER_AA1_FILTER_LENGHT];
    float temp[SAMPLING_FRAME];
public:
    DigitalDistortion();
    void setClip(float value);
    void drive(float * in, float * out);
};