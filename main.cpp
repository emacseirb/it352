/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */




 // ---------------------------- Réponses Communiquer avec le capteur ---------------------------- //
/*
Procédure de lecture de la mesure par le capteur (UART) pour la Zest Sensor Dust
UART donc pas d'adresse de registre
=> Start Particle measurement
    - send : 0x68 - 0x01 - 0x01 - data sur 1 octet
    - response (ACK) : 0xA5A5

=> Read Particule Measuring
    - send : 0x68 - 0x01 - 0x04 - data sur 1 octet
    - response (ACK): 0x40 - 0x05 - 0x04 - data sur 5 octets

=> Stop particule measurement
    - send : 0x68 - 0x01 - 0x02 - data sur 1 octet
    - response (ACK) : 0xA5A5
*/

#include "mbed.h"

Ticker flipper;
InterruptIn button(BUTTON1);
DigitalOut led(LED1);


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

int flag = 0;
int mode = 100000;

void speed(){
    flag = 1;
}

void flip(){
    led = !led;
}



int main()
{
    printf("start succesfully !!\n");
    button.rise(&speed);

    while(1){
        if (flag == 1){
            mode += 100000;
            flag = 0;
            flipper.attach_us(&flip, mode);
            printf("mode : %d us\n", (int)mode);
        }
        ThisThread::sleep_for(200);
        
    }

}
