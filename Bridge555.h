#ifndef BRIDGE_555_H
#define BRIDGE_555_H

#include <Arduino.h>

class Bridge555 {
public:
    // Constructor: Takes Digital Potentiometer pins (CS, INC, U/D)
    Bridge555(uint8_t csPin, uint8_t incPin, uint8_t udPin);

    void begin(float capacitanceUf, uint32_t fixedResistorOhms = 1000);
    bool setFrequency(unsigned long targetFreq);
    void autoCalibrate(uint8_t feedbackPin);

private:
    uint8_t _csPin;
    uint8_t _incPin;
    uint8_t _udPin;
    
    float _capacitance;
    uint32_t _rFixed;
    uint8_t _currentWiper; // X9C pots typically have 100 steps (0-99)

    void setWiperPosition(uint8_t targetWiper);
    unsigned long measureFrequency(uint8_t feedbackPin);
};

#endif
