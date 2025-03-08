#include "Bsp.hpp"
#include "Light.hpp"
#include "Event.hpp"
#include "System.hpp"
#include "codec/CodecInterface.hpp"
#include "display/lcd.hpp"

class MiniStompX: public Bsp {
    public:
    
    MiniStompX() : Bsp() { }

    void initialize(){
        //init footswitch gpio
        gpio_set_direction(GPIO_NUM_10, GPIO_MODE_INPUT); 
        IOArray::initialize(8, 2000, 100, 32, SPI_USE_DEFAULT_PIN, SPI_USE_DEFAULT_PIN, SPI_USE_DEFAULT_PIN, SPI_USE_DEFAULT_PIN);
        //init codec
        Codec::initialize();
        //init LED controller
		Light::initialize(System::systemNode());
        //init LCD display
        LCD::initialize();
        LCD::splash();
    }

    void eventLoop(){
        int evt;
        while((evt = IOArray::has_data())){
        	if(evt == IO_ARRAY_DATA_CHANGED) EventDispatcher::broadcast(EVENT_INPUT);
            //encoder rotate
        	ENCODER(IOArray::get_bit(1), IOArray::get_bit(3), EventDispatcher::addEvent(EVENT_ENC_UP), EventDispatcher::addEvent(EVENT_ENC_DOWN), 1, ENCODER_IO_ARRAY_DEBOUNCE);
			//encoder push
        	PRESS(IOArray::get_bit(0), EventDispatcher::addEvent(EVENT_ENC_PRESSED), EventDispatcher::addEvent(EVENT_ENC_RELEASED), EventDispatcher::addEvent(EVENT_ENC_LONG_PRESSED), EventDispatcher::addEvent(EVENT_ENC_LONG_RELEASED));
			//footswitch push
        	PRESS(gpio_get_level(GPIO_NUM_10), EventDispatcher::addEvent(EVENT_FSW_PRESSED), EventDispatcher::addEvent(EVENT_FSW_RELEASED), EventDispatcher::addEvent(EVENT_FSW_LONG_PRESSED), EventDispatcher::addEvent(EVENT_FSW_LONG_RELEASED));
        }
    }
};