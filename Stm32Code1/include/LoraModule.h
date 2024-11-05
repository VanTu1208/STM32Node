#ifndef LORAMODULE_H  
#define LORAMODULE_H
#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include "nodeId.h"
#include "Buzz.h"
// Định nghĩa chân kết nối LoRa
#define SPI1_NSS  PA4
#define SPI1_SCK  PA5
#define SPI1_MISO PA6
#define SPI1_MOSI PA7  
#define SPI1_RESET PB0


void LoraSetup(void);
void sendSensorData(int penCode, int nodeId, float t, float h, float nh3, float h2s);
#endif 