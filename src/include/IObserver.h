#pragma once

class IObserver {
public:
    virtual void addToVector(std::string timeKey, int absoluteTime) = 0;

};
