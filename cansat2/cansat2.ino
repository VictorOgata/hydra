#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP280.h> 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

Servo servo;
int servoPin = A0;
Adafruit_BMP280 bmp; 
RF24 radio(9, 10);
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
    Serial.begin(9600);
    if(!bmp.begin(0x76)){ 
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); 
    while(1);}
    servo.attach(servoPin);

    servo.write(0);
}
void loop() {
servo.write(30);
delay(1000);
  servo.write(180);
     String aux;
  const char text[] = "Temperatura: ";
     radio.write(&text, sizeof(text));
     aux =(String)bmp.readTemperature(); 
     aux.toCharArray(text,6);
     radio.write(&text, sizeof(text));
     aux =String("*C");
     aux.toCharArray(text,3);
     radio.write(&text, sizeof(text)); 
     
     String aux1;
  const char text1[100] = "Pressão: ";
     radio.write(&text1, sizeof(text1));
     aux1 =(String)bmp.readPressure();
     aux1.toCharArray(text1,30);
     radio.write(&text1, sizeof(text1)); 
     aux1 =String("Pa");
     aux1.toCharArray(text1,40);
     radio.write(&text1, sizeof(text1)); 

      String aux2;
  const char text2[100] = "Altitude: ";
     radio.write(&text2, sizeof(text2));
     aux2 =(String)bmp.readAltitude(1013.25);
     aux2.toCharArray(text2,30);
     radio.write(&text2, sizeof(text2)); 
     aux2 =String("m");
     aux2.toCharArray(text2,40);
     radio.write(&text2, sizeof(text2)); 
     
  //delay(1000);
}
