#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/GPIO.h"
//#include "include/GPIOFileWriter.h"

GPIO::GPIO() {
    this->m_pin = "4";
    this->m_gpioPath = "/sys/class/gpio/gpio"+ m_pin + "/";
    writeToFile("/sys/class/gpio/export","4");
}

GPIO::GPIO(const string& pin)
{
    this->m_pin = pin;
    this->m_gpioPath = "/sys/class/gpio/gpio"+ m_pin + "/";

    cout << "-- GPIO --: exporting pin " << pin << endl;
    writeToFile("/sys/class/gpio/export",pin);
}

GPIO::~GPIO()
{ 
    cout << "-- GPIO --: cleaning up pin " << m_pin << endl;
    writeToFile("/sys/class/gpio/unexport",m_pin);
}

int GPIO::setDirection(eDirection direction)
{
    string s_direction;
    if (direction == GPIO::INPUT){
        s_direction = "in";
    } else if (direction == GPIO::OUTPUT) {
        s_direction = "out";
    }

    cout << "-- GPIO --: setting direction of pin " << m_pin << endl;
    writeToFile(this->m_gpioPath + "direction",s_direction);
    return 1;
}

int GPIO::setValue (eValue value) {
    cout << "-- GPIO --: setting value to pin " << m_pin << endl;
    writeToFile(this->m_gpioPath + "value", to_string(value));
    return 1;
}

int GPIO::readValue () {
    int value;
    ifstream gpio(m_gpioPath + "value");
    if (! gpio.is_open()) {
        cout << "-- File --: ERROR! no file open called " << m_gpioPath << "value" << endl;
        return -1;
    } else {
        gpio >> value;
        gpio.close();
    }
    return value;
}

int GPIO::writeToFile(const string &path, const string &input){
    ofstream file(path);
    if ( file.is_open()){
        file << input;
        cout << "-- File --: File open and written to it" << endl;
        file.close();
        return 1;
    } else {
        cout << "--File --: ERROR! file not open" << endl;
        return -1;
    }
    return -1;
}


