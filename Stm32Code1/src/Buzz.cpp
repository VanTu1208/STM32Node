#include "Buzz.h"

void buzzer_Setup(void) {
  pinMode(buzzerPin,OUTPUT);
}

void failLora(void){
    digitalWrite(buzzerPin,HIGH);
      tone(buzzerPin, 3000);    delay(200);
      noTone(buzzerPin);        delay(200);
      tone(buzzerPin, 1000);    delay(200);
      noTone(buzzerPin);
    digitalWrite(buzzerPin,LOW);
}

void failDHT(void){
    digitalWrite(buzzerPin,HIGH);
      tone(buzzerPin, 800);    delay(200);
      noTone(buzzerPin);        delay(200);
      tone(buzzerPin, 800);    delay(200);
      noTone(buzzerPin);
    digitalWrite(buzzerPin,LOW);
}


