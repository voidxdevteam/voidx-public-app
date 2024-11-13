#pragma once
#include "esp_dsp.h"
#include "dsp/AudioBlock.hpp"
#include "NodeEnum.hpp"
#include "NodeFloat.hpp"
#include "NodeItem.hpp"
#include "Event.hpp"

typedef struct {
	float d_state[2];
	float b_coeffs[3];
	float a_coeffs[3];
} BiquadExecData;

class Eq7: public AudioBlock,  public Listener {
private:
	Node * sys;
	//params
	NodeFloat * band_level[7];
	NodeFloat * gain;
	NodeEnum * mode;
	NodeEnum * onoff;
	//exec data
	BiquadExecData biquad_data_1_l;
	BiquadExecData biquad_data_2_l;
	BiquadExecData biquad_data_3_l;
	BiquadExecData biquad_data_4_l;
	BiquadExecData biquad_data_5_l;
	BiquadExecData biquad_data_6_l;
	BiquadExecData biquad_data_7_l;
	BiquadExecData biquad_data_1_r;
	BiquadExecData biquad_data_2_r;
	BiquadExecData biquad_data_3_r;
	BiquadExecData biquad_data_4_r;
	BiquadExecData biquad_data_5_r;
	BiquadExecData biquad_data_6_r;
	BiquadExecData biquad_data_7_r;
	float gain_data;
	//interface
	int cursor;
	int selected;
	int timer;
public:
    Eq7(Node * parent, Node *root, Node * sys);
    bool compile();
    static bool exec(Eq7 * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]);
    bool draw();
    bool onEvent(int event);
};
