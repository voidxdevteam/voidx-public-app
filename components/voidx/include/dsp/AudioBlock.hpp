#pragma once
#include "../Node.hpp"
#include "../codec/CodecInterface.hpp"

class AudioBlock {
    Node * parent;
public:
    static const int AddPushBack = 0;
    static const int AddPushFront = 1;

    AudioBlock(Node * parent, int mode = AudioBlock::AddPushBack);
    virtual void compile() = 0;
    virtual void exec(float data[SAMPLING_CHANNELS][SAMPLING_FRAME]) = 0;
};
