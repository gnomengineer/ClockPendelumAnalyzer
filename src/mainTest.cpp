#include "include/GPIO.h"
#include <iostream>
#include <string>

int main( int argc, const char* argv[] )
{
    int c;
	GPIO pin2("27");
    pin2.setDirection(GPIO::INPUT);
    GPIO pin3("17");
    pin3.setDirection(GPIO::OUTPUT);
    pin3.setValue(GPIO::HIGH);

    do {
        std::cout << pin2.readValue() << std::endl;
        c = getchar();
    } while (c != 'q');
}
