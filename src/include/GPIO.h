#ifndef GPIO_H
#define GPIO_H

#include <string>
using namespace std;

class GPIO
{
public:
    enum eValue
    {
        HIGH = 1,
        LOW = 0
    };

    enum eDirection
    {
        INPUT,
        OUTPUT
    };

    GPIO();
    GPIO(const string& pin);
    ~GPIO();
    int setDirection(eDirection direction);
    int setValue(eValue value);
    int readValue();
    string pin();

private:
    int writeToFile(const string& path, const string& input);
    int exportPin();
    string m_pin;
    string m_gpioPath;

};

#endif
