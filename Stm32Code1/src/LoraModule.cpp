#include "LoraModule.h"

void LoraSetup(void){
    pinMode(SPI1_NSS, OUTPUT);
    pinMode(SPI1_RESET, OUTPUT);
    digitalWrite(SPI1_RESET, HIGH);
    
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6)) {
        failLora();
        Serial.println("LoRa init failed. Check your connections.");
        
        delay(5000);
    }
    Serial.println("LoRa init succeeded.");
    LoRa.sleep();
}


void sendSensorData(int penCode, int nodeId, float t, float h, float nh3, float h2s) {
    // CSMA: Kiểm tra kênh trước khi gửi
    int maxAttempts = 5;  // Số lần thử tối đa nếu kênh bận
    bool sent = false;

    for (int attempt = 0; attempt < maxAttempts; attempt++) {
        // Đọc giá trị RSSI để kiểm tra độ nhiễu của kênh
        int rssi = LoRa.packetRssi();
        
        if (rssi < -90) {  // Ngưỡng RSSI (-90 dBm) để xem kênh có bận không
            // Kênh trống, tiến hành gửi dữ liệu
            LoRa.beginPacket();
            LoRa.print("penCode:");
            LoRa.print(penCode, DEC);
            LoRa.print("; nodeId:");
            LoRa.print(nodeId, DEC);
            LoRa.print("; Temp:");
            LoRa.print(t);
            LoRa.print("; Hum:");
            LoRa.print(h);
            LoRa.print("; NH3:");
            LoRa.print(nh3);
            LoRa.print("; H2S:");
            LoRa.print(h2s);
            LoRa.endPacket();

            LoRa.sleep();  // Đưa LoRa về chế độ ngủ để tiết kiệm năng lượng
            
            Serial.print("LORA PACKET: ");
            Serial.print("penCode:");
            Serial.print(penCode, BIN);
            Serial.print("; nodeId:");
            Serial.print(nodeId, BIN);
            Serial.print("; Temp:");
            Serial.print(t);
            Serial.print("; Hum:");
            Serial.print(h);
            Serial.print("; NH3:");
            Serial.print(nh3);
            Serial.print("; H2S:");
            Serial.println(h2s);
            
            
            Serial.println("Data sent successfully.");
            sent = true;
            break;  // Thoát vòng lặp khi dữ liệu đã được gửi
        } else {
            // Kênh bận, đợi ngẫu nhiên trước khi thử lại
            Serial.println("Channel is busy, retrying...");
            delay(random(100, 500));  // Đợi từ 100ms đến 500ms
        }
    }

    if (!sent) {
        Serial.println("Failed to send data after multiple attempts.");
    }
}