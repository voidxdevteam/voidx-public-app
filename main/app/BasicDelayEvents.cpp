
#include "BasicDelayEvents.hpp"
#include "../bsp/MiniStompX.hpp"
#include <malloc.h>
#include "DrawerHome.hpp"
#include "DrawerNode.hpp"
 
/* DELAY_LINE_SIZE: length of the delay buffer */
#define DELAY_LINE_SIZE ((int)(2 * SAMPLING_FREQ)) 
 
/*
parent: application node pointer (typically root/app).
root: root node pointer.
*/
BasicDelayEvents::BasicDelayEvents(Node * parent, Node *root) : AudioBlock("Basic Delay", parent, (bool (*)(void*, float [SAMPLING_CHANNELS][SAMPLING_FRAME]))BasicDelayEvents::exec){
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
 
    //Main ON-OFF Node
    this->onOff = new NodeEnum(parent, "on_off", "Enable", {"ON", "OFF"}, "ON");

    /* Create hfolders for high-level logical division. */
    NodeItem * delayFolder = new NodeItem(parent, "delay", "Delay", "", "hfolder");
    NodeItem * outputFolder = new NodeItem(parent, "output", "Output Mix", "", "hfolder");
    delayFolder->setStyle("color:#0000FF;");

    /* Configure parameter nodes. */
    /* For example, the mix parameter is defined as follows:
       -"mix" as system name (locate the node at root/app/mix). 
       -Assign "Mix" as the display name, visible to the user.
       -Range: 0% to 100%, default: 50%.
       -Linear curve (shape = 0.5f). Log-curve (<0.5), anti-log-curve (>0.5).
       -Inverted = false: parameter increases with value.
       -Displayed as integer (0 decimal values) */

    this->onOffDelay = new NodeEnum(delayFolder, "on_off", "Enable", {"ON", "OFF"}, "OFF");
    this->mix = new NodeFloat(delayFolder, "mix", "Mix", 0.0f, 100.0f, 50.0f, "%", 0.5f, false, 0);
    this->feedback = new NodeFloat(delayFolder, "fdbk", "Feedback", 0.0f, 1.0f, 0.5, "", 0.5f, false, 2);
    this->timeNode = new NodeFloat(delayFolder, "time", "Time", 20.0f, 1000.0f, 100.0f, "ms", 0.5f, false, 0);
    timeNode->setStyle("color:#00FF00;");

    //Arrange the "Output Mix" folder with a volume parameter and a vfolder inside
    this->volume = new NodeFloat(outputFolder, "vol", "Volume", 0.0f, 1.0f, 0.5, "", 0.5f, false, 2);

    /* Create vfolders for lower-level sub-division into the ""Output Mix" folder. */
    NodeItem * advancedFolder = new NodeItem(outputFolder, "advanced", "Advanced", "", "vfolder");
    this->onOffAdvanced = new NodeEnum(advancedFolder, "on_off", "Enable", {"ON", "OFF"}, "OFF");
    this->dummyAdvanced = new NodeFloat(advancedFolder, "dummyadv", "Dummy Advanced", 0.0f, 100.0f, 50.0f, "%", 0.5f, false, 0);

    /* Create sfolder for system-level logical division: "Settings" is the tipical example. */
    NodeItem * setupFolder = new NodeItem(root, "setup", "Setup", "", "sfolder");
    this->dummySettings = new NodeFloat(setupFolder, "dummyset", "Useless Setting", 0.0f, 100.0f, 50.0f, "%", 0.5f, false, 0);
     
    /* Initialize the graphical engine */
    //DrawerHome * drw = new DrawerHome(NULL, NULL, NULL);
    //drw->setNodes(parent, System::systemNode(), NULL);
 
    /* Allocate and reset the circular buffer */
    this->delayLine = (float *) memalign(16, DELAY_LINE_SIZE * sizeof(float)); //16 byte memory aligned
    for(int i = 0; i < DELAY_LINE_SIZE; i++) this->delayLine[i] = 0;
    this->delayLineWritePointer = 0;
 
    this->compile();
}
 
bool BasicDelayEvents::compile(){
    
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
bool IRAM_ATTR BasicDelayEvents::exec(BasicDelayEvents * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]){
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


/* 
This method is called to handle incoming events
in this example EVENT_ENC_UP will increase the mix parameter
in this example EVENT_ENC_DOWN will decrease the mix parameter
in this example EVENT_ENC_RELEASED will open the parameter list starting from the application node
*/
bool BasicDelayEvents::onEvent(int event){
    switch(event){
        case EVENT_ENC_UP:
            this->mix->edit(true);
            break;
        case EVENT_ENC_DOWN:
            this->mix->edit(false);
            break;
        case EVENT_ENC_RELEASED:
            new DrawerNode(this->parent);
            break;
    }
	return true;
}

/* 
This method is called when the LCD need to be drawn
in this example we draw a label and the value of the parameter mix
*/
bool BasicDelayEvents::draw(){
    glcd_drawStringFont(10, 10, (char *)"Mix", Arial14, 1);
    glcd_drawStringFont(10, 30, (char *)this->mix->toString().c_str(), Arial_bold_14, 1);
    return true;
}