#include "Bsp.hpp"
#include "Light.hpp"
#include "Event.hpp"
#include "System.hpp"
#include "codec/CodecInterface.hpp"
#include "display/lcd.hpp"
#include "controller/SourceMidi.hpp"

class MiniStompX: public Bsp {
    public:
    
    MiniStompX() : Bsp() {
        new SourceMidi(SOURCE_MIDI, UART_NUM_1, GPIO_NUM_14, GPIO_NUM_13);
    }

    void initialize(){
        gpio_set_direction(GPIO_NUM_10, GPIO_MODE_INPUT); //Audioscape bug
        IOArray::initialize(8, 4000, 100, 32);
        //IOArray::initialize(488, 4000, 100, 16);
        //update_initialize();
        Codec::initialize();
		Light::initialize(System::systemNode());
        //lcd must be started after codec
        lcd_initialize();
    }

    void eventLoop(){
        int evt;
        while((evt = IOArray::has_data())){
        	if(evt == IO_ARRAY_DATA_CHANGED) EventDispatcher::broadcast(EVENT_INPUT);
			//encoder rotate
        	ENCODER(IOArray::get_bit(1), IOArray::get_bit(3), EventDispatcher::addEvent(EVENT_ENC_UP), EventDispatcher::addEvent(EVENT_ENC_DOWN), 1);
			//encoder push
        	PRESS(IOArray::get_bit(0), EventDispatcher::addEvent(EVENT_ENC_PRESSED), EventDispatcher::addEvent(EVENT_ENC_RELEASED), EventDispatcher::addEvent(EVENT_ENC_LONG_RELEASED));
			//footswitch push
        	int value = gpio_get_level(GPIO_NUM_10);
        	if(value) value = 0;
        	else value = 1;
        	PRESS(value, EventDispatcher::addEvent(EVENT_FSW_PRESSED), EventDispatcher::addEvent(EVENT_FSW_RELEASED), EventDispatcher::addEvent(EVENT_FSW_LONG_RELEASED));
        }
    }
};