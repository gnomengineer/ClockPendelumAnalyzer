#include "include/GPIO.h"
#include <iostream>
#include <string>

int main( int argc, const char* argv[] )
{
	GPIO pin2("27");
    pin2.setDirection(GPIO::INPUT);
    GPIO pin3("17");
    pin3.setDirection(GPIO::OUTPUT);
    pin3.setValue(GPIO::HIGH);

    while (1)
        std::cout << pin2.readValue();
}
