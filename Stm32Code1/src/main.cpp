#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <LoRa.h>
#include "DHT.h"

// Định nghĩa chân kết nối LoRa
#define SPI1_NSS  PA4  // Chân Chip Select
#define SPI1_SCK  PA5   // Chân SCK
#define SPI1_MISO PA6   // Chân MISO
#define SPI1_MOSI PA7   // Chân MOSI
#define SPI1_RESET PB0   // Chân Reset


// Định nghĩa chân analog cho cảm biến
#define H2S_PIN PA2  // Chân analog cho cảm biến MQ-136
#define NH3_PIN PA1  // Chân analog cho cảm biến MQ-135

#define DHTPIN PA3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    dht.begin();
    // Thiết lập các chân cho LoRa
    pinMode(SPI1_NSS, OUTPUT);
    pinMode(SPI1_RESET, OUTPUT);
    digitalWrite(SPI1_RESET, HIGH); // Đặt chân reset ở mức cao


    // Khởi tạo LoRa
    LoRa.setPins(SPI1_NSS, SPI1_RESET, SPI1_SCK);
    while (!LoRa.begin(433E6));
}

void loop() {
    // Đọc giá trị từ cảm biến H2S (MQ-136)
    int h2s_value = analogRead(H2S_PIN);

    // Đọc giá trị từ cảm biến NH3 (MQ-135)
    int nh3_value = analogRead(NH3_PIN);

    int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
    int t = dht.readTemperature();

    // Gửi dữ liệu qua LoRa
        LoRa.beginPacket();
        LoRa.print("H2S:");
        LoRa.print(h2s_value);
        LoRa.print("; ");
        LoRa.print("NH3:");
        LoRa.print(nh3_value);
        LoRa.print("; ");
        LoRa.print("Temp:");
        LoRa.print(t);
        LoRa.print("; ");
        LoRa.print("Hum:");
        LoRa.print(h);
        LoRa.endPacket();

    // Đợi một chút trước khi đọc lại
    delay(2000);
}
