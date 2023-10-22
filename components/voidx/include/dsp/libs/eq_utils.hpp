#pragma once
#include "libs.hpp"

#define FIRST_ORDER_IIR_LOW_PASS 	0
#define FIRST_ORDER_IIR_HI_PASS 	1

#define BIQUAD_TYPE_LOW_PASS 		        0
#define BIQUAD_TYPE_HI_PASS 	        	1
#define BIQUAD_TYPE_BAND_PASS 		        2
#define BIQUAD_TYPE_LOW_SHELF 		        3
#define BIQUAD_TYPE_HI_SHELF 		        4
#define BIQUAD_TYPE_PEQ 			        5
#define BIQUAD_TYPE_BAND_PASS_RESONANT      6

#define BIQUAD_TYPE_LOW_PASS_NAME           "LOPASS"
#define BIQUAD_TYPE_HI_PASS_NAME            "HIPASS"
#define BIQUAD_TYPE_BAND_PASS_NAME          "BPASS"
#define BIQUAD_TYPE_LOW_SHELF_NAME          "LOSHELF"
#define BIQUAD_TYPE_HI_SHELF_NAME           "HISHELF"
#define BIQUAD_TYPE_PEQ_NAME                "PEQ"
#define BIQUAD_TYPE_BAND_PASS_RESONANT_NAME "BPRES"

#define FORMANT_WOWEL_A						"A"
#define FORMANT_WOWEL_E						"E"
#define FORMANT_WOWEL_I						"I"
#define FORMANT_WOWEL_O						"O"
#define FORMANT_WOWEL_U						"U"

#define FORMANT_VOICE_ALTO					"ALTO"
#define FORMANT_VOICE_BASS					"BASS"
#define FORMANT_VOICE_COUNTERTENOR			"CONTRA"
#define FORMANT_VOICE_SOPRANO				"SOPRANO"
#define FORMANT_VOICE_TENOR					"TENOR"

#define FIROBJ_SIZE_MAX 			1024

typedef struct {
	unsigned int low_high;
	float cutoff_frequency;
	float b_coeffs[2];
	float a_coeffs[2];
} FirstOrderIIRObj;

typedef struct {
	unsigned int type;
	float value_db;
	float f;
	float q;
} BiquadObj;

typedef struct {
	BiquadObj info;
	float d_state[2];
	float b_coeffs[3];
	float a_coeffs[3];
} BiquadObjExec;

typedef struct {
	float b_coeffs[5];
	float a_coeffs[5];
	float xMemory[SIGNAL_FRAME + 4];
	float yMemory[SIGNAL_FRAME + 4];
} IIR4ObjExec;

typedef struct {
	float coeffs[FIROBJ_SIZE_MAX];
    float ir_state[FIROBJ_SIZE_MAX + SIGNAL_FRAME];
    int ir_start;
    int fir_lenght;
    int c_size;
} FIRExecObj;

typedef struct {
	float f;
	float bw;
	float normalizer;
	float d_state[2] __attribute__((aligned(8)));
	float a_coeffs[3] __attribute__((aligned(8)));
} SinglePoleIIRObj;


//first order IIR
void FirstOrderIIRObj_init(FirstOrderIIRObj * item);
void FirstOrderIIRObj_compile(FirstOrderIIRObj * item);
//second order IIR
void BiquadObj_init(BiquadObj * item);
void BiquadObjExec_init(BiquadObjExec * item);
void BiquadObjExec_compile(BiquadObjExec * item);
void compile_BiquadObjExec_from_2_first_order(BiquadObjExec * biquad, FirstOrderIIRObj * first_order_1, FirstOrderIIRObj * first_order_2);
void BiquadObjExec_exec(BiquadObjExec * item, float * in, float * out);
float BiquadObjExec_abs_at(BiquadObjExec * item, float i);
float BiquadObjExec_abs_at_db(BiquadObjExec * item, float i);
//fourth order IIR
void IIR4Obj_init(IIR4ObjExec * item);
void compile_IIR4ObjExec_from_2_biquads(IIR4ObjExec * iir4, BiquadObjExec * biquad_1, BiquadObjExec * biquad_2);
void IIR4Obj_exec(IIR4ObjExec * iir4, float * in, float * out);
//FIR
void FIRExecObj_init(FIRExecObj * item, int fir_length); //fir_lenght multiplo di SIGNAL_FRAME e <= 1024
void FIRExecObj_reset(FIRExecObj * item);
void FIRExecObj_compile(FIRExecObj * item, float * coeffs);
void FIRExecObj_exec(FIRExecObj * item, float * in, float * out);
//formant filters
/*void createFormantVowelParameter(ParameterEnum * par, char * default_value);
void createFormantVoiceParameter(ParameterEnum * par, char * default_value);
void formant3FCompile(BiquadObjExec * item1, BiquadObjExec * item2, BiquadObjExec * item3, BiquadObjExec * item4, BiquadObjExec * item5, ParameterEnum * vowel_1, ParameterEnum * vowel_2, ParameterEnum * voice_1, ParameterEnum * voice_2, float res_1, float res_2, float ctrl_01);*/
//single pole IIR
void SinglePoleIIRObj_init(SinglePoleIIRObj * item);
void SinglePoleIIRObj_compile(SinglePoleIIRObj * item);
void SinglePoleIIRObj_exec(SinglePoleIIRObj * item, float * in, float * out);

