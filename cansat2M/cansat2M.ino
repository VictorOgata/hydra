#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10);
int flag=0;
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  String alt;
  String aux;
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    aux = String(text);
    Serial.println(aux);
    if(flag==1){
      flag=0;
      alt = aux;
        if(alt.toInt()<450)
    Serial.println("musica");
    }
  }
  if(aux.compareTo("Altitude: ")==0)
  flag =1;
}
