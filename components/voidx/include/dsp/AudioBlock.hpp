#pragma once
#include "../Node.hpp"
#include "../codec/CodecInterface.hpp"

class AudioBlock {
    Node * parent;
    const char * name;
public:
    static const int AddPushBack = 0;
    static const int AddPushFront = 1;

    AudioBlock(const char * name, Node * parent, bool (* block_dsp)(void * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]), int mode = AudioBlock::AddPushBack);
    const char * getName();
    virtual bool compile() = 0;
};
