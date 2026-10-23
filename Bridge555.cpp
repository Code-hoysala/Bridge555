#include "Bridge555.h"

Bridge555::Bridge555(uint8_t csPin, uint8_t incPin, uint8_t udPin) {
    _csPin = csPin;
    _incPin = incPin;
    _udPin = udPin;
    _currentWiper = 50; // Start midway
}

void Bridge555::begin(float capacitanceUf, uint32_t fixedResistorOhms) {
    _capacitance = capacitanceUf * 0.000001; // Convert uF to Farads
    _rFixed = fixedResistorOhms;

    pinMode(_csPin, OUTPUT);
    pinMode(_incPin, OUTPUT);
    pinMode(_udPin, OUTPUT);

    digitalWrite(_csPin, HIGH);
    digitalWrite(_incPin, HIGH);
}

void Bridge555::setWiperPosition(uint8_t targetWiper) {
    if (targetWiper > 99) targetWiper = 99;

    // Bring CS low to select the digital pot
    digitalWrite(_csPin, LOW);
    
    // Direction: HIGH for up, LOW for down
    digitalWrite(_udPin, (targetWiper > _currentWiper) ? HIGH : LOW);
    
    int steps = abs((int)targetWiper - (int)_currentWiper);
    for (int i = 0; i < steps; i++) {
        digitalWrite(_incPin, LOW);
        delayMicroseconds(2);
        digitalWrite(_incPin, HIGH);
        delayMicroseconds(2);
    }
    
    digitalWrite(_csPin, HIGH);
    _currentWiper = targetWiper;
}

bool Bridge555::setFrequency(unsigned long targetFreq) {
    if (targetFreq == 0) return false;

    // Astable 555 formula approximation: f = 1.44 / ((R1 + 2*R2) * C)
    // Solving for variable resistance R2 based on target frequency:
    // R2 = ( (1.44 / (targetFreq * C)) - R1 ) / 2
    float totalResistanceNeeded = (1.440 / (targetFreq * _capacitance));
    
    if (totalResistanceNeeded <= _rFixed) {
        setWiperPosition(0); // Max frequency limit reached
        return false;
    }
    
    float rVarNeeded = (totalResistanceNeeded - _rFixed) / 2.0;
    
    // Assuming a 100k digital pot (like X9C104), map resistance to 0-99 steps
    int estimatedWiper = (int)((rVarNeeded / 100000.0) * 99.0);
    
    if (estimatedWiper < 0) estimatedWiper = 0;
    if (estimatedWiper > 99) estimatedWiper = 99;

    setWiperPosition((uint8_t)estimatedWiper);
    return true;
}

unsigned long Bridge555::measureFrequency(uint8_t feedbackPin) {
    // Measure pulse width using Uno's pulseIn (timeout after 50ms)
    unsigned long highPulse = pulseIn(feedbackPin, HIGH, 50000);
    unsigned long lowPulse = pulseIn(feedbackPin, LOW, 50000);
    
    if (highPulse == 0 || lowPulse == 0) return 0; // No signal detected
    
    unsigned long periodUs = highPulse + lowPulse;
    return 1000000UL / periodUs;
}

void Bridge555::autoCalibrate(uint8_t feedbackPin) {
    pinMode(feedbackPin, INPUT);
    
    unsigned long measuredFreq = measureFrequency(feedbackPin);
    // Basic closed-loop adjustment hook can be expanded here based on drift error.
}
