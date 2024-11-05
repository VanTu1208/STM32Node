#include <LoraModule.h>
#include "nodeId.h"
#include "dht11.h"
#include "MQ135Module.h"
#include "MQ136Module.h"
#include "Buzz.h"
#define TIME_CALLBACK 10 //Thoi gian giua 2 lan truyen goi tin (s)
#define READ_NUM 5 //So lan doc cam bien de lay trung binh moi lan truyen goi tin

float temp, hum, nh3, h2s;
float humSum, tempSum, nh3Sum, h2sSum;
float humAvg, tempAvg, nh3Avg, h2sAvg;

void setup() {
    Serial.begin(115200);
    //Doc id cua node
    DipSwitch_Setup(); readAllSwitches();
    DHT11_Setup();
    LoraSetup();
    MQ136_Setup();
    MQ135_Setup();

}

void loop() {
    humSum = 0, tempSum = 0, nh3Sum = 0, h2sSum = 0;
    humAvg = 0, tempAvg = 0, nh3Avg = 0, h2sAvg = 0;

    //Bat nguon DHT11
    turnOnDHT(true);  delay(100);
    for(int i = 0; i < READ_NUM; i++){
        //Doc gia tri cam bien
        DHT11_Read(&temp, &hum); delay(5);
        nh3 = readNH3(); delay(5);
        h2s = readH2S(); delay(5);
        humSum += hum; tempSum +=temp; nh3Sum += nh3; h2sSum +=h2s;
        Serial.print("#"); Serial.print(i+1); 
        Serial.print(" Temp:");  Serial.print(temp); 
        Serial.print("C Hum:"); Serial.print(hum); 
        Serial.print("% NH3:"); Serial.print(nh3);  Serial.print("%");  
        Serial.print(" H2S:"); Serial.print(h2s);  Serial.println("%"); 
        delay(2000);
    }
    humAvg  = humSum/READ_NUM;
    tempAvg = tempSum/READ_NUM;
    nh3Avg  = nh3Sum/READ_NUM;
    h2sAvg  = h2sSum/READ_NUM;
    Serial.println("Average Value of Sensor:");
    Serial.print("Temp:");  Serial.print(tempAvg);  
    Serial.print("C Hum:"); Serial.print(humAvg); 
    Serial.print("%  NH3:"); Serial.print(nh3Avg);  Serial.print("%");  
    Serial.print(" H2S:"); Serial.print(h2sAvg);  Serial.println("%"); 
    sendSensorData(penCode, nodeId, tempAvg, humAvg, nh3Avg, h2sAvg);

    turnOnDHT(false);
    delay(TIME_CALLBACK*1000);

}
