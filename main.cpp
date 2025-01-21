/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

Ticker flipper;

DigitalOut led(LED1);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


void flip(){
    led = !led;
}

int main()
{
    printf("start succesfully !!\n");
    flipper.attach(&flip, 0.5);
    while(1){
        ThisThread::sleep_for(200);
        
    }

}
