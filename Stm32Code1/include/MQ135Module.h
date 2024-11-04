#ifndef MQ135MODULE_H  
#define MQ135MODULE_H
#include <Arduino.h>

#define PIN_MQ135 PA1

void MQ135_Setup(void);
float readNH3(void);

#endif 