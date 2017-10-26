#ifndef GPIO_H
#define GPIO_H

class GPIO
{
public:
    static enum eValue
    {
        HIGH = 1,
        LOW = 0
    };

    static enum eDirection
    {
        INPUT,
        OUTPUT
    };

    GPIO();
    GPIO(string pin);
    ~GPIO();
    void setDirection(eDirection direction);
    void setValue(eValue value);
    int readValue();
    string pin();

private:
    void exportPin();
    string m_pin;
    string m_gpioPath;

}

#endif
