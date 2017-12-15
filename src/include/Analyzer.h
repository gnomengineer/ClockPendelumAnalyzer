#ifndef ANALYZER_H
#define ANALYZER_H

#include "I2CHandler.h"
#include <string>

//@deprecated
class Analyzer {
    const double MS = 1000000;
    const double US = 1000;
    const int NS = 1000000000;
public:
    Analyzer();
    ~Analyzer();
    double getTimeDifference_us();
    double getTimeDifference_ms();
    int getTimeDifference_ns();

private:
    void updateTimerCounterValue();
    int calculateFrequencyDifference();
    int getTicksInNS();
    int m_ReferenceTimeFrequency = 32000;
    int m_MeasuredTimeFrequency;
    I2CHandler *m_Counter;

};

#endif
