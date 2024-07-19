#include "../bsp/MiniStompX.hpp"
#include "IrLoaderStereo.hpp"
#include "Light.hpp"
#include "System.hpp"
#include "NodeEnum.hpp"
#include "NodeItem.hpp"
#include "NodeFloat.hpp"
#include "DrawerHome.hpp"
#include "NodePreset.hpp"
#include "NodeControlMidiPC.hpp"
#include <math.h>

IrLoaderStereo::IrLoaderStereo(Node * parent, Node * root) : AudioBlock(parent) {
    new MiniStompX();
	//info data
	NodeItem * name = (NodeItem *)root->pathToNode("root\\sys\\_name");
	if(name != NULL) name->setValue("Stereo IR Loader");
	NodeItem * author = (NodeItem *)root->pathToNode("root\\sys\\_author");
	if(author != NULL) author->setValue("Frog");
    NodeItem * logo = (NodeItem *)root->pathToNode("root\\sys\\_logo");
	if(logo != NULL) logo->setValue("https://globaluserfiles.com/media/7446_dd23cbcb77fd40f990aaa6555e6cf07f9eeb811f.png/v1/w_427,h_0/logo-frog-amps-gold-header.fw.png");

	NodeList * list = new NodeList(System::rootNode(), "ir", "ir list", "wav_48000", 4096, 16);
    //on off
    this->onoff = new NodeEnum(parent, "on_off", "Enable", {"ON", "OFF"}, "ON");
    Light::setStatus((NodeEnum *)this->onoff);
    //presets
    NodePreset * pres = new NodePreset(parent, "preset", "Preset", "", new NodeList(System::rootNode(), "presets", "Presets", "pst", 4096, 128));
    //data
	this->lvl = new NodeFloat(parent, "vol", "Volume", 0, 1.0f, 1.0f, "", 0.1f, false);
	Node * left_folder = new NodeItem(parent, "left", "Left channel", "", NODE_ITEM_TYPE_HFOLDER);
	Node * right_folder = new NodeItem(parent, "right", "Right channel", "", NODE_ITEM_TYPE_HFOLDER);
	Node * routing_folder = new NodeItem(parent, "routing", "Routing", "tc", NODE_ITEM_TYPE_VFOLDER_TC);
    this->left_onoff = new NodeEnum(left_folder, "on_off", "Enable", {"ON", "OFF"}, "ON");
	this->left_gain = new NodeFloat(left_folder, "lgain", "Gain", -20.0f, 40.0f, 0.0f, "dB", 0.5f, false);
    this->right_onoff = new NodeEnum(right_folder, "on_off", "Enable", {"ON", "OFF"}, "ON");
	this->right_gain = new NodeFloat(right_folder, "rgain", "Gain", -20.0f, 40.0f, 0.0f, "dB", 0.5f, false);
    this->left_ir_node = new NodeParList(left_folder, "lir", "IR", "", list);
    this->right_ir_node = new NodeParList(right_folder, "rir", "IR", "", list);
    this->input_mode = new NodeEnum(routing_folder, "in_mode", "In Mode", {"STEREO", "LEFT", "RIGHT", "SUM"}, "STEREO");
    this->output_mode = new NodeEnum(routing_folder, "out_mode", "Out Mode", {"STEREO", "LEFT", "RIGHT", "SUM"}, "STEREO");
    //Storage::addItem(new NodeControlMidiPC(parentControl, "midi1", "MIDI PC", this->right_ir_node, 1));

    //presets
    Storage::addItem(pres);
    //drawerhome
    DrawerHome * drw = new DrawerHome(NULL, NULL, NULL);
	drw->setNodes(parent, System::systemNode(), pres);

    for(int i=0; i<FIR_LENGTH; i++){
        this->left_ir[i] = 0;
        this->right_ir[i] = 0;
    }
    left_ir[0] = 1.0f;
    right_ir[0] = 1.0f;
    this->level = 0.0f;
    this->lgain = 1.0f;
    this->rgain = 1.0f;
    this->left_fir = new QuadFIR(FIR_LENGTH);
    this->right_fir = new QuadFIR(FIR_LENGTH);
    this->left_fir->load(left_ir);
    this->right_fir->load(right_ir);
}

void IrLoaderStereo::compile(){
    float * left_ptr = (float *)this->left_ir_node->getData();
    float * right_ptr = (float *)this->right_ir_node->getData();
    this->lgain = exp10f(((NodeFloat *)(this->left_gain))->getValue()/20.0f);
    this->rgain = exp10f(((NodeFloat *)(this->right_gain))->getValue()/20.0f);
    if(((NodeEnum *)this->left_onoff)->isValue("OFF")) this->lgain = 0;
    if(((NodeEnum *)this->right_onoff)->isValue("OFF")) this->rgain = 0;
    this->level = (((NodeFloat *)(this->lvl))->getValue());
    //printf("left = %d right = %d\n\n", (int)left_ptr, (int)right_ptr);
    if(left_ptr != 0) this->left_fir->load(left_ptr);
    if(right_ptr != 0) this->right_fir->load(right_ptr);
}

void IrLoaderStereo::exec(float data[SAMPLING_CHANNELS][SAMPLING_FRAME]){
	if(((NodeEnum *)this->onoff)->isValue("OFF")) return;
	if(((NodeEnum *)this->input_mode)->isValue("LEFT")){
		for(int i=0; i<SAMPLING_FRAME; i++)
			data[1][i] = data[0][i];
	} else if(((NodeEnum *)this->input_mode)->isValue("RIGHT")){
		for(int i=0; i<SAMPLING_FRAME; i++)
			data[0][i] = data[1][i];
	} else if(((NodeEnum *)this->input_mode)->isValue("SUM")){
		for(int i=0; i<SAMPLING_FRAME; i++){
			data[0][i] = 0.5f*(data[0][i] + data[1][i]);
			data[1][i] = data[0][i];
		}
	}
	static float _rgain = 0;
	static float _lgain = 0;
	_rgain = 0.995f * _rgain + 0.005f * this->rgain;
	_lgain = 0.995f * _lgain + 0.005f * this->lgain;

	for(int i=0; i<SAMPLING_FRAME; i++){
		data[1][i] *= _rgain;
		data[0][i] *= _lgain;
	}
    this->left_fir->exec(&data[0][0], &data[0][0], SAMPLING_FRAME);
    this->right_fir->exec(&data[1][0], &data[1][0], SAMPLING_FRAME);


	static float _level = 0;
	_level = 0.995f * _level + 0.005f * this->level;
    for(int i=0; i<SAMPLING_FRAME; i++){
		data[1][i] *= _level;
		data[0][i] *= _level;
	}
    if(((NodeEnum *)this->output_mode)->isValue("LEFT")){
    	for(int i=0; i<SAMPLING_FRAME; i++)
    		data[1][i] = data[0][i];
    } else if(((NodeEnum *)this->output_mode)->isValue("RIGHT")){
    	for(int i=0; i<SAMPLING_FRAME; i++)
    		data[0][i] = data[1][i];
    } else if(((NodeEnum *)this->output_mode)->isValue("SUM")){
    	for(int i=0; i<SAMPLING_FRAME; i++){
    		data[0][i] = 0.5f*(data[0][i] + data[1][i]);
    		data[1][i] = data[0][i];
    	}
    }
}
