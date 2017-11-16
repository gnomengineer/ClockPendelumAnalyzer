#ifndef ANALYZER_H
#define ANALYZER_H

#include "I2CHandler.h"
#include <string>

class Analyzer {
    const double MS = 1000;
    const double US = 1000000;
    const double NS = 1000000000;
public:
    Analyzer();
    ~Analyzer();
    double getTimeDifference_us();
    double getTimeDifference_ms();
    double getTimeDifference_ns();

private:
    void updateTimerCounterValue();
    double calculateDifference(const double &refFreq, 
            const double &mesFreq, 
            const std::string &unit);
    double m_ReferenceTimeFrequency = 32000;
    double m_MeasuredTimeFrequency;
    I2CHandler *m_Counter;

};

#endif
