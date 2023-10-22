#pragma once
#include "../Node.hpp"
#include "../codec/CodecInterface.hpp"

class AudioBlock {
    Node * parent;
public:
    AudioBlock(Node * parent);
    virtual void compile() = 0;
    virtual void exec(float data[SAMPLING_CHANNELS][SAMPLING_FRAME]) = 0;
};
