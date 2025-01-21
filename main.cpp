/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono;

InterruptIn button(BUTTON1);
DigitalOut led(LED1);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

long long unsigned int counter = 0;

Timer t;

void flip(){
    t.start();
    led = 1;
}

void flip_2(){
    t.stop();
    counter = duration_cast<milliseconds>(t.elapsed_time()).count();
    led = 0;
    t.reset();
}

int main()
{
    printf("start succesfully !!\n");
    button.rise(&flip);
    button.fall(&flip_2);
    while(1){
        printf("The duration of the button push was : %llu\n", counter);
        ThisThread::sleep_for(500);
        
    }

}
