#include "../include/Analyzer.h"
#include <iostream>

Analyzer::Analyzer() { 
    m_Counter = new I2CHandler();
}

Analyzer::~Analyzer() {
    delete m_Counter;
}

void Analyzer::updateTimerCounterValue() {
    char buffer[60] = {0};
    m_Counter->readValue(buffer,0x40);
}

double Analyzer::getTimeDifference_us() {
    this->updateTimerCounterValue();
    double refFreq_us = m_ReferenceTimeFrequency / Analyzer::US;
    double mesFreq_us = m_MeasuredTimeFrequency / Analyzer::US;
    return calculateDifference(refFreq_us, mesFreq_us, "us");
}

double Analyzer::getTimeDifference_ms() {
    this->updateTimerCounterValue();
    double refFreq_ms = m_ReferenceTimeFrequency / Analyzer::MS;
    double mesFreq_ms = m_MeasuredTimeFrequency / Analyzer::MS;
    return calculateDifference(refFreq_ms, mesFreq_ms, "ms");
}

double Analyzer::getTimeDifference_ns() {
    this->updateTimerCounterValue();
    double refFreq_ns = m_ReferenceTimeFrequency / Analyzer::NS;
    double mesFreq_ns = m_MeasuredTimeFrequency / Analyzer::NS;
    return calculateDifference(refFreq_ns, mesFreq_ns, "ns");
}

double Analyzer::calculateDifference(const double &refFreq,
        const double &mesFreq,
        const std::string &unit) {
    double diffFreq = 0.0;
    //TODO recheck the calculation
    if (!(diffFreq = refFreq - mesFreq)) {
        std::cerr << "not possible to measure " 
            << unit << " due to low frequency" << std::endl;
    }
    return diffFreq;
}
