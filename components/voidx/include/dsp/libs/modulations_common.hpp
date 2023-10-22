#pragma once

#include "libs.hpp"

#define MODULATIONS_REF_PERIOD 			2048
#define MODULATIONS_REF_PERIOD_F 		((float)MODULATIONS_REF_PERIOD)
#define MODULATIONS_REF_BUFFER_MARGIN   128
#define MODULATIONS_REF_BUFFER_SIZE     (MODULATIONS_REF_PERIOD + MODULATIONS_REF_BUFFER_MARGIN)

extern float triangle_wave_modulations_ref[MODULATIONS_REF_BUFFER_SIZE];
extern float square_wave_modulations_ref[MODULATIONS_REF_BUFFER_SIZE];
extern float sine_wave_modulations_ref[MODULATIONS_REF_BUFFER_SIZE];
extern float log_sine_wave_modulations_ref[MODULATIONS_REF_BUFFER_SIZE];
extern float noise_like_wave_modulations_ref[MODULATIONS_REF_BUFFER_SIZE];

void init_modulations_common();

typedef struct {
	float * delay_line;
	unsigned int peak_delay_samples;
	unsigned int delay_line_index;
	float * delay_line_virtual_zero;
	float * modulations_ref_waveform;
	unsigned int central_delay;
	float modulations_ref_value_voice_1;
	float modulations_ref_value_voice_2;
	float modulations_ref_value_voice_3;
	float modulation_ref_index;
	float rate_step;
	float depth_linear;
	unsigned int n_voices;
	float voices_offset;
} VibratoObj;

typedef struct {
    float * delay_line;
    unsigned int index;
    unsigned int size;
    unsigned int mask;
} ModulationObj;

void modulationObj_exec(ModulationObj * item, float * frame_in, float * frame_out, float * delay_frame);
void modulationObj_init(ModulationObj * item, float * buffer, int size);

void vibratoObj_init(VibratoObj * item, float * delay_line, unsigned int peak_delay_samples, unsigned int central_delay); //delay_line assumed >= 2 * peak_delay_samples; peak_delay_samples assunto potenza di 2
void vibratoObj_exec_more_voices(VibratoObj * item, float * in, float * out);
void vibratoObj_exec_single_voice(VibratoObj * item, float * in, float * out);
void vibratoObj_buffer_update(VibratoObj * item, float * in);
void vibratoObj_compile(VibratoObj * item, float rate_f, float depth_samples, float * waveform, unsigned int n_voices);
