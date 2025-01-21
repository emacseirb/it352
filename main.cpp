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
#include "hpma115/hpma115.h"
#include "mbed.h"


namespace {
#define WAIT 1s
}
using namespace sixtron;
static DigitalOut led(LED1);
static hpma115_data_t data;

int main()
{
    uint8_t coef;
    HPMA115::ErrorType err;

    HPMA115 sensor(P1_UART_TX, P1_UART_RX);

    printf("\n\n------------\nHPMA115 Example\n");

    err = sensor.stop_measurement();
    assert(err == HPMA115::ErrorType::Ok);

    err = sensor.stop_autosend();
    assert(err == HPMA115::ErrorType::Ok);

    err = sensor.set_adjust_coef(200);
    assert(err == HPMA115::ErrorType::Ok);

    err = sensor.read_adjust_coef(&coef);
    assert(err == HPMA115::ErrorType::Ok);
    assert(coef == 200);

    err = sensor.set_adjust_coef(100);
    assert(err == HPMA115::ErrorType::Ok);

    err = sensor.start_measurement();
    assert(err == HPMA115::ErrorType::Ok);

    while (true) {
        led = !led;
        err = sensor.read_measurement(&data);
        if (err == HPMA115::ErrorType::Ok) {
            printf("Data: ");
            if (data.pm1_pm4_valid) {
                printf("PM1.0: %d, PM4.0: %d ", data.pm1_0, data.pm4_0);
            }
            printf("PM10: %d, PM2.5: %d\n", data.pm10, data.pm2_5);
        }

        ThisThread::sleep_for(WAIT);
    }

}
