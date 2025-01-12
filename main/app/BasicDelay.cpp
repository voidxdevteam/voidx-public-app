
#include "BasicDelay.hpp"
#include "../bsp/MiniStompX.hpp"
#include <malloc.h>
#include "DrawerHome.hpp"
 
/* DELAY_LINE_SIZE: length of the delay buffer */
#define DELAY_LINE_SIZE ((int)(2 * SAMPLING_FREQ)) 
 
/*
parent: application node pointer (typically root/app).
root: root node pointer.
*/
BasicDelay::BasicDelay(Node * parent, Node *root) : AudioBlock("Basic Delay", parent, (bool (*)(void*, float [SAMPLING_CHANNELS][SAMPLING_FRAME]))BasicDelay::exec){
    /* Initialize the MiniStompX hardware interface. */
    /* BSP classes encapsulate hardware interactions, triggering hardware events, and controlling hardware devices. */
    new MiniStompX();
 
    /* Define application metadata: name, author, and logo. */
    NodeItem * name = (NodeItem *)root->pathToNode("root\\sys\\_name"); //Access the node using its predefined path.
    if(name != NULL) name->setValue("Basic Delay"); //Assign a value to the node.
 
    NodeItem * author = (NodeItem *)root->pathToNode("root\\sys\\_author");
    if(author != NULL) author->setValue("VoidX-DevTeam");
 
    NodeItem * logo = (NodeItem *)root->pathToNode("root\\sys\\_logo");
    if(logo != NULL) logo->setValue("https://www.voidxdevteam.com/wp-content/uploads/2024/07/logo_square.png");
 
    /* Configure parameter nodes. */
    /* For example, the mix parameter is defined as follows:
       -"mix" as system name (locate the node at root/app/mix). 
       -Assign "Mix" as the display name, visible to the user.
       -Range: 0% to 100%, default: 50%.
       -Linear curve (shape = 0.5f). Log-curve (<0.5), anti-log-curve (>0.5).
       -Inverted = false: parameter increases with value.
       -Displayed as integer (0 decimal values) */
    this->mix = new NodeFloat(parent, "mix", "Mix", 0.0f, 100.0f, 50.0f, "%", 0.5f, false, 0);
    this->feedback = new NodeFloat(parent, "fdbk", "Feedback", 0.0f, 1.0f, 0.5, "", 0.5f, false, 2);
    this->timeNode = new NodeFloat(parent, "time", "Time", 20.0f, 1000.0f, 100.0f, "ms", 0.5f, false, 0);
     
    /* Initialize the graphical engine */
    DrawerHome * drw = new DrawerHome(NULL, NULL, NULL);
    drw->setNodes(parent, System::systemNode(), NULL);
 
    /* Allocate and reset the circular buffer */
    this->delayLine = (float *) memalign(16, DELAY_LINE_SIZE * sizeof(float)); //16 byte memory aligned
    for(int i = 0; i < DELAY_LINE_SIZE; i++) this->delayLine[i] = 0;
    this->delayLineWritePointer = 0;
 
    this->compile();
}
 
bool BasicDelay::compile(){
    
    /* Mix: Convert the percentage value to a 0-1 representation. */
    this->mixDsp = this->mix->getValue() / 100.0f;
 
    /* Feedback: for stability, the actual feedback needs to be strictly less than 1. */
    this->feedbackDsp = 0.999f * this->feedback->getValue();
 
    /* Time: get the amount of delay samples. */
    float msDelay = this->timeNode->getValue();
    this->delaySamplesDsp = (msDelay / 1000.0f) * SAMPLING_FREQ; //SAMPLING_FREQ is 44100 or 48000
    
    //return value
    return false;
}
 
/* 
The data bi-dimensional array stores the raw audio samples.
-The SAMPLING_CHANNELS constant defines the number of audio channels, usually 2 for stereo sound.
-The SAMPLING_FRAME constant defines the number of audio samples processed together, usually 16 samples per batch.
Input is taken from the Left channel only (Right channel is ignored). Output is equal on both channels.
*/
bool IRAM_ATTR BasicDelay::exec(BasicDelay * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]){
    /* Sample-by-sample unoptimized processing */
    /* Vectorization can significantly improve processing speed. */
    for(int i = 0; i < SAMPLING_FRAME; i++){
        /* Determine the readIndex for retrieving samples from the delay line. */
        int delayLineReadIndex = ptr->delayLineWritePointer - ptr->delaySamplesDsp; 
        if(delayLineReadIndex < 0) delayLineReadIndex += DELAY_LINE_SIZE; //circular buffer
 
        /* Add a new sample to the delay line. */
        /* The new sample is formed by adding the current input to a scaled version of a past output (feedback). */
        ptr->delayLine[ptr->delayLineWritePointer] = data[0][i] + ptr->feedbackDsp * ptr->delayLine[delayLineReadIndex]; 
        ptr->delayLineWritePointer++;
        if(ptr->delayLineWritePointer >= DELAY_LINE_SIZE) ptr->delayLineWritePointer = 0; //circular buffer
 
        /* Mix dry and wet signals, ensuring equal left and right outputs. */
        data[0][i] = data[0][i] + ptr->mixDsp * ptr->delayLine[delayLineReadIndex]; 
        data[1][i] = data[0][i];
    }
    //return value
    //if there is more than one block, returning true will stop the dsp chain execution to this point
    return false;
}