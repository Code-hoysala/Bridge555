#include "Bridge555.h"

// Define pins for X9C104 Digital Potentiometer connected to Arduino Uno R3
const uint8_t POT_CS = 2;
const uint8_t POT_INC = 3;
const uint8_t POT_UD = 4;
const uint8_t FEEDBACK_PIN = 8; // Connect NE555 output back to pin 8

Bridge555 signalGen(POT_CS, POT_INC, POT_UD);

void setup() {
    Serial.begin(9600);
    
    // Initialize with 1µF timing capacitor and 1k fixed resistor on NE555 circuit
    signalGen.begin(1.0, 1000); 
    
    Serial.println(F("Bridge555 Initialized. Setting target frequency to 1 kHz..."));
    signalGen.setFrequency(1000); // Command analog circuit to output 1 kHz
}

void loop() {
    // Continuously monitor and self-correct drift using Uno's pin 8 feedback loop
    signalGen.autoCalibrate(FEEDBACK_PIN);
    
    delay(2000);
}
