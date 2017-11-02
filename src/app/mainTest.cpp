#include "../include/GPIO.h"
#include "../include/RTCModule.h"
#include <iostream>
//#include <pthread.h>

int main( int argc, const char* argv[] )
{
    int c;
	pthread_t thread;

    RTCModule* module = new RTCModule();

    pthread_create(&thread, NULL, RTCModule::startRTCthread, reinterpret_cast<void*>(module));

    GPIO pin2("27");
    pin2.setDirection(GPIO::INPUT);
    GPIO pin3("17");
    pin3.setDirection(GPIO::OUTPUT);
    pin3.setValue(GPIO::HIGH);

    do {
        std::cout << pin2.readValue() << std::endl;
        c = getchar();
    } while (c != 'q');

    module->stopThread();
    delete module;
}
