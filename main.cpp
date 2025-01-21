/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led(LED1);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

void flip(){
    led = 1;
}

void flip_2(){
    led = 0;
}

int main()
{
    printf("start succesfully !!\n");
    button.rise(&flip);
    button.fall(&flip_2);
    /*while(1){
        printf("nothing here for the moment \n");
        ThisThread::sleep_for(250);
    }*/
}
