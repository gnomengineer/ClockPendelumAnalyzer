#include "../include/Analyzer.h"
#include <iostream>
//@deprecated
Analyzer::Analyzer() { 
    m_Counter = new I2CHandler();
}

Analyzer::~Analyzer() {
    delete m_Counter;
}

void Analyzer::updateTimerCounterValue() {
    char buffer[60] = {0};
    //m_Counter->readValue(buffer,0x40);
    m_MeasuredTimeFrequency = 31980;
}

double Analyzer::getTimeDifference_us() {
    return getTimeDifference_ns() / Analyzer::US;
}

double Analyzer::getTimeDifference_ms() {
    return getTimeDifference_ns() / Analyzer::MS;
}

int Analyzer::getTimeDifference_ns() {
    return calculateFrequencyDifference() * getTicksInNS();
}

int Analyzer::getTicksInNS() {
    return NS / m_ReferenceTimeFrequency;
}

int Analyzer::calculateFrequencyDifference() {
    this->updateTimerCounterValue();
    return m_ReferenceTimeFrequency - m_MeasuredTimeFrequency;
}
