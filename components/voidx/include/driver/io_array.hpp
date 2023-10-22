#pragma once

#define IO_ARRAY_NO_DATA		0
#define IO_ARRAY_DATA_SYNC		1
#define IO_ARRAY_DATA_CHANGED	2

#define IO_ARRAY_PWM_DISABLE -1

namespace IOArray {
    void initialize(int max_io, int freq, int queue_time_ms, int pwm_depth);
    void tasks();
    int has_data();
    int in_get(int index);
    void set_byte(int index, unsigned char value);
    void set_bit(int index, unsigned char value);
    unsigned char get_byte(int index);
    unsigned char get_bit(int index);
    void set_pwm(int index, int value);
    void set_pwm_depth(int depth);
    int ms_to_tick(int ms);
    int get_max_io();
    int get_max_pwm();
}

