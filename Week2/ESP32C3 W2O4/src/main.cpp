#include <Arduino.h>

int diodePin = 0;
 
void setup() {
Serial.begin(115200);
pinMode(diodePin,INPUT);       // zet pin 0 als input
adcAttachPin(diodePin);        // verbind pin 0 met de ADC
analogReadResolution(12);      // zet ADC in 12 bit mode
analogSetPinAttenuation(diodePin, ADC_0db); // zet de versterking op max!
}

void loop(){
  Serial.println(analogRead(diodePin));
}