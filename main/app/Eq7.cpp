#include "Eq7.hpp"
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "esp_check.h"
#include <malloc.h>
#include <math.h>
#include "display/glcd.h"
#include "Light.hpp"
#include "drawerNode.hpp"
#include "dsp/AudioProcessor.hpp"
#include "../bsp/MiniStompX.hpp"

void BiquadExec_init(BiquadExecData * item){
	item->d_state[0] = 0;
	item->d_state[1] = 0;
	item->a_coeffs[0] = 1.0f;
	item->a_coeffs[1] = 0.0f;
	item->a_coeffs[2] = 0.0f;
	item->b_coeffs[0] = 0.0f;
	item->b_coeffs[1] = 0.0f;
	item->b_coeffs[2] = 0.0f;
}

void BiquadExec_compile(BiquadExecData * item, float value_db, float freq, float q){
	float parameter_geqf_a0;
	float parameter_geqf_a1;
	float parameter_geqf_a2;
	float parameter_geqf_b0;
	float parameter_geqf_b1;
	float parameter_geqf_b2;

	float a = sqrtf(powf(10,(value_db / 20.0f)));
	float w = 2 * M_PI * freq/(float)SAMPLING_FREQ;
	float ws = sinf(w);
	float wc = cosf(w);
	float alpha = ws / (2.0f * q);

	parameter_geqf_b0 = 1+alpha*a;
	parameter_geqf_b1 = -2*wc;
	parameter_geqf_b2 = 1-alpha*a;
	parameter_geqf_a0 = 1+alpha/a;
	parameter_geqf_a1 = -2*wc;
	parameter_geqf_a2 = 1-alpha/a;

	item->a_coeffs[0] = 1.0f;
	item->a_coeffs[1] = parameter_geqf_a1 / parameter_geqf_a0;
	item->a_coeffs[2] = parameter_geqf_a2 / parameter_geqf_a0;
	item->b_coeffs[0] = parameter_geqf_b0 / parameter_geqf_a0;
	item->b_coeffs[1] = parameter_geqf_b1 / parameter_geqf_a0;
	item->b_coeffs[2] = parameter_geqf_b2 / parameter_geqf_a0;
}

void BiquadExec_exec(float * x, float *b, float *a, float * delay, float * y){
    for (int i = 0; i < SAMPLING_FRAME; i++){
		float x_i = x[i];
        y[i] = b[0] * x_i + delay[0];
        delay[0] = b[1] * x_i - a[1] * y[i] + delay[1];
        delay[1] = b[2] * x_i - a[2] * y[i]; 
    }
	/*
	for (int i = 0 ; i < SAMPLING_FRAME ; i++) {
		float d0 = x[i] - a[1] * delay[0] - a[2] * delay[1];
		y[i] = b[0] * d0 +  b[1] * delay[0] + b[2] * delay[1];
		delay[1] = delay[0];
		delay[0] = d0;
	}*/
}

Eq7::Eq7(Node * parent, Node *root, Node * sys) : AudioBlock("Eq7", parent, (bool (*)(void*, float [SAMPLING_CHANNELS][SAMPLING_FRAME]))Eq7::exec){
    new MiniStompX();
	//info data
	this->sys = sys;
	NodeItem * name = (NodeItem *)root->pathToNode("root\\sys\\_name");
	if(name != NULL) name->setValue("Equalizer 7");
	NodeItem * author = (NodeItem *)root->pathToNode("root\\sys\\_author");
	if(author != NULL) author->setValue("VoidX");
	NodeItem * logo = (NodeItem *)root->pathToNode("root\\sys\\_logo");
	if(logo != NULL) logo->setValue("https://futuranet.it/wp-content/uploads/2022/01/cropped-android-chrome-512x512-1-2.png");
	//param data
    this->onoff = new NodeEnum(parent, "on_off", "Enable", {"ON", "OFF"}, "OFF");
	this->band_level[0] = new NodeFloat(parent, "band100", "100 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[1] = new NodeFloat(parent, "band200", "200 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[2] = new NodeFloat(parent, "band400", "400 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[3] = new NodeFloat(parent, "band800", "800 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[4] = new NodeFloat(parent, "band1600", "1600 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[5] = new NodeFloat(parent, "band3200", "3200 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->band_level[6] = new NodeFloat(parent, "band6400", "6400 Hz", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	this->gain = new NodeFloat(parent, "gain", "Gain", -15.0f, 15.0f, 0, "dB", 0.5f, false);
	
	NodeItem * sfolder = new NodeItem(root, "settings", "Settings", "", "sfolder");
	this->mode = new NodeEnum(sfolder, "mode", "Mode", {"Stereo", "Mono"}, "Stereo");

	//set storage
	Storage::addItem(this->onoff);
	Storage::addItem(this->band_level[0]);
	Storage::addItem(this->band_level[1]);
	Storage::addItem(this->band_level[2]);
	Storage::addItem(this->band_level[3]);
	Storage::addItem(this->band_level[4]);
	Storage::addItem(this->band_level[5]);
	Storage::addItem(this->band_level[6]);
	Storage::addItem(this->gain);
	Storage::addItem(this->mode);
	//init biquad
	BiquadExec_init(&this->biquad_data_1_l);
	BiquadExec_init(&this->biquad_data_2_l);
	BiquadExec_init(&this->biquad_data_3_l);
	BiquadExec_init(&this->biquad_data_4_l);
	BiquadExec_init(&this->biquad_data_5_l);
	BiquadExec_init(&this->biquad_data_6_l);
	BiquadExec_init(&this->biquad_data_7_l);
	BiquadExec_init(&this->biquad_data_1_r);
	BiquadExec_init(&this->biquad_data_2_r);
	BiquadExec_init(&this->biquad_data_3_r);
	BiquadExec_init(&this->biquad_data_4_r);
	BiquadExec_init(&this->biquad_data_5_r);
	BiquadExec_init(&this->biquad_data_6_r);
	BiquadExec_init(&this->biquad_data_7_r);
	//init data
	this->compile();
	//init interface
	Light::setStatus(this->onoff);
	this->cursor = 0;
	this->selected = 0;
	this->timer = 0;
}

bool Eq7::compile(){
	//printf("%f %f %f %f %f %f %f\n", this->band_level[0]->getValue(), this->band_level[1]->getValue(), this->band_level[2]->getValue(), this->band_level[3]->getValue(), this->band_level[4]->getValue(), this->band_level[5]->getValue(), this->band_level[6]->getValue());
	//eq L channel
	BiquadExec_compile(&this->biquad_data_1_l, this->band_level[0]->getValue(), 100.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_2_l, this->band_level[1]->getValue(), 200.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_3_l, this->band_level[2]->getValue(), 400.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_4_l, this->band_level[3]->getValue(), 800.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_5_l, this->band_level[4]->getValue(), 1600.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_6_l, this->band_level[5]->getValue(), 3200.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_7_l, this->band_level[6]->getValue(), 6400.0f, 1.4f);
	//eq R channel
	BiquadExec_compile(&this->biquad_data_1_r, this->band_level[0]->getValue(), 100.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_2_r, this->band_level[1]->getValue(), 200.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_3_r, this->band_level[2]->getValue(), 400.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_4_r, this->band_level[3]->getValue(), 800.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_5_r, this->band_level[4]->getValue(), 1600.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_6_r, this->band_level[5]->getValue(), 3200.0f, 1.4f);
	BiquadExec_compile(&this->biquad_data_7_r, this->band_level[6]->getValue(), 6400.0f, 1.4f);
	//gain
	this->gain_data = powf(10,( this->gain->getValue() / 20.0f));
	//return value
	return false;
}

bool IRAM_ATTR Eq7::exec(Eq7 * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]){
	if(ptr->onoff->isValue("ON")){
	//eq L channel
		BiquadExec_exec(data[0], ptr->biquad_data_1_l.b_coeffs, ptr->biquad_data_1_l.a_coeffs, ptr->biquad_data_1_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_2_l.b_coeffs, ptr->biquad_data_2_l.a_coeffs, ptr->biquad_data_2_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_3_l.b_coeffs, ptr->biquad_data_3_l.a_coeffs, ptr->biquad_data_3_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_4_l.b_coeffs, ptr->biquad_data_4_l.a_coeffs, ptr->biquad_data_4_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_5_l.b_coeffs, ptr->biquad_data_5_l.a_coeffs, ptr->biquad_data_5_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_6_l.b_coeffs, ptr->biquad_data_6_l.a_coeffs, ptr->biquad_data_6_l.d_state, data[0]);
		BiquadExec_exec(data[0], ptr->biquad_data_7_l.b_coeffs, ptr->biquad_data_7_l.a_coeffs, ptr->biquad_data_7_l.d_state, data[0]);
		//eq R channel
		BiquadExec_exec(data[1], ptr->biquad_data_1_r.b_coeffs, ptr->biquad_data_1_r.a_coeffs, ptr->biquad_data_1_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_2_r.b_coeffs, ptr->biquad_data_2_r.a_coeffs, ptr->biquad_data_2_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_3_r.b_coeffs, ptr->biquad_data_3_r.a_coeffs, ptr->biquad_data_3_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_4_r.b_coeffs, ptr->biquad_data_4_r.a_coeffs, ptr->biquad_data_4_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_5_r.b_coeffs, ptr->biquad_data_5_r.a_coeffs, ptr->biquad_data_5_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_6_r.b_coeffs, ptr->biquad_data_6_r.a_coeffs, ptr->biquad_data_6_r.d_state, data[1]);
		BiquadExec_exec(data[1], ptr->biquad_data_7_r.b_coeffs, ptr->biquad_data_7_r.a_coeffs, ptr->biquad_data_7_r.d_state, data[1]);
		//gain
		for(int i=0; i<SAMPLING_FRAME; i++){
			data[0][i] *= -ptr->gain_data;
			data[1][i] *= -ptr->gain_data;
		}
	}
	//mode
	if(ptr->mode->isValue("Mono")){
		for(int i=0; i<SAMPLING_FRAME; i++){
			data[1][i] = data[0][i];
		}
	}
	//return value
	return false;
}

bool Eq7::draw(){
	glcd_clear(0);
	int x = 10;
	int y = 5;
	const char * strs[8] = {"100", "200", "400", "800", "1.6", "3.2", "6.4", "Lvl"};
	for(int i=0; i<7; i++){
		glcd_drawStringFont(x-5, y-2, (char *)strs[i], newbasic3x5, 1);
		glcd_drawLine(x,y+11,x,y+43,1);
		glcd_fillCircle(x, y+12 + (int)(15.0f - this->band_level[i]->getValue()), 3, this->cursor == i && (!this->selected || this->timer < 3));
		glcd_drawCircle(x, y+12 + (int)(15.0f - this->band_level[i]->getValue()), 3, 1);
		x+=15;
	}
	//level
	x+=5;
	for(int i=0; i<31;i++)
		if(i & 1) glcd_drawPixel(x-10, y+12+i, 1);
	glcd_drawStringFont(x-5, y-1, (char *)strs[7], newbasic3x5, 1);
	glcd_drawLine(x-1,y+11,x-1,y+43,1);
	glcd_drawLine(x-1,y+11,x+1,y+11,1);
	//glcd_drawLine(x,y+12,x,y+42,1);
	glcd_drawLine(x+1,y+11,x+1,y+43,1);
	glcd_drawLine(x-1,y+43,x+1,y+43,1);
	glcd_fillCircle(x, y+12 + (int)(15.0f - this->gain->getValue()), 3, this->cursor == 7 && (!this->selected || this->timer < 3));
	glcd_drawCircle(x, y+12 + (int)(15.0f - this->gain->getValue()), 3, 1);
	//meters
    glcd_drawLine(0,55,127,55,1);
    if(!this->selected){
    	if(this->mode->isValue("Stereo")) glcd_drawStringFont(4, 56, (char *)"Stereo", Callibri10, 1);
    	if(this->mode->isValue("Mono")) glcd_drawStringFont(4, 56, (char *)"Mono", Callibri10, 1);
    	x = 50;
    	glcd_drawStringFont(x, 56, (char *)"OUT", Callibri10, 1);
    	x += 20;
    	glcd_drawRect(x,58, (int)((float)(x+20)+0.20f*AudioProcessor::meter(1, 0)*100.0f/(-METER_MIN_VIEW_VALUE)),60,1);
    	glcd_drawRect(x,61, (int)((float)(x+20)+0.20f*AudioProcessor::meter(0, 0)*100.0f/(-METER_MIN_VIEW_VALUE)),63,1);
    	x += 28;
    	glcd_drawStringFont(x, 56, (char *)"IN", Callibri10, 1);
    	x += 10;
    	glcd_drawRect(x,58, (int)((float)(x+20)+0.20f*AudioProcessor::meter(1, 1)*100.0f/(-METER_MIN_VIEW_VALUE)),60,1);
    	glcd_drawRect(x,61, (int)((float)(x+20)+0.20f*AudioProcessor::meter(0, 1)*100.0f/(-METER_MIN_VIEW_VALUE)),63,1);
    } else {
    	char str[20];
    	if(this->cursor < 7){
    		sprintf(str, "%s  %s", this->band_level[cursor]->getDisplayName(), this->band_level[cursor]->toString().c_str());
    	} else {
    		sprintf(str, "%s  %s", this->gain->getDisplayName(), this->gain->toString().c_str());
    	}
    	glcd_drawStringFont(4, 56, str, Callibri10, 1);
    }
	return true;
}

bool Eq7::onEvent(int event){
	switch(event){
		case EVENT_FSW_PRESSED:
        	//printf("fsw value");
			if(this->onoff->isValue("ON")) this->onoff->setValue("OFF");
			else this->onoff->setValue("ON");
			break;
		case EVENT_ENC_UP:
			if(this->selected == 0 && this->cursor < 7) this->cursor++;
			else if(this->selected == 1 && this->cursor < 7 && this->cursor >= 0) this->band_level[this->cursor]->edit(true);
			else if(this->selected == 1 && this->cursor == 7) this->gain->edit(true);
			break;
		case EVENT_TIMER_200MS:
			this->timer++;
			if(this->timer > 6) this->timer = 0;
			break;
		case EVENT_ENC_DOWN:
			if(this->selected == 0 && this->cursor > 0) this->cursor--;
			else if(this->selected == 1 && this->cursor < 7 && this->cursor >= 0) this->band_level[this->cursor]->edit(false);
			else if(this->selected == 1 && this->cursor == 7) this->gain->edit(false);
			break;
		case EVENT_ENC_RELEASED:
			if(!this->selected) this->selected = 1;
			else this->selected = 0;
			break;
		case EVENT_ENC_LONG_RELEASED:
			if(this->sys != NULL) new DrawerNode(this->sys);
			break;
	}
	return true;
}
