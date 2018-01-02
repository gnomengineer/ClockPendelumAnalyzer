#pragma once

#include <stdint.h>

class IObserver {
public:
    virtual void addToVector(std::string timeKey, uint32_t absoluteTime, uint32_t referenceFrequency) = 0;

};
