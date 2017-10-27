#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "include/GPIO.h"
#include "include/GPIOFileWriter.h"

GPIO::GPIO() {
    this->m_pin = "4";
    this->m_gpioPath = "/sys/class/gpio/gpio"+ m_pin + "/";
    exportPin();
}

GPIO::GPIO(const string& pin)
{
    this->m_pin = pin;
    this->m_gpioPath = "/sys/class/gpio/gpio"+ m_pin + "/";
    exportPin();
}

GPIO::~GPIO()
{ 
    GPIOFileWriter gpio("/sys/class/gpio/unexport");
    gpio << this->m_pin;
}

int GPIO::exportPin(){
    GPIOFileWriter gpio("/sys/class/gpio/export");
    gpio << m_pin;
    return 1;
}

int GPIO::setDirection(eDirection direction)
{
    string s_direction;
    if (direction == GPIO::INPUT){
        s_direction = "in";
    } else if (direction == GPIO::OUTPUT) {
        s_direction = "out";
    }
    GPIOFileWriter gpio(this->m_gpioPath + "direction");
    gpio << s_direction;
    return 1;
}

int GPIO::setValue (eValue value) {
    GPIOFileWriter gpio(this->m_gpioPath + "value");
    gpio << value;
    return 1;
}

int GPIO::readValue () {
    int value;
    ifstream gpio((m_gpioPath + "value").c_str());
    if (gpio.is_open())
        cout << "Error! no file open called " << m_gpioPath << "value" << endl;
    gpio >> value;
    gpio.close();
    return value;
}
