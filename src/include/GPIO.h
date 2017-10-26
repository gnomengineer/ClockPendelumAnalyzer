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

    GPIO(int pin);
    ~GPIO();
    void setDirection(eDirection direction);
    void setValue(eValue value);
    int readValue();
    int pin();

private:
    int m_pin;

}
