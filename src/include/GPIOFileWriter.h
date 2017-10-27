#ifndef GPIOFILEWRITER_H
#define GPIOFILEWRITER_H

#include <string>
#include <fstream>
using namespace std;

class GPIOFileWriter
{
    public:
        GPIOFileWriter(const string& path);
        ~GPIOFileWriter();
        int operator<<(int input);
        int operator<<(const string& input);

    private:
        int writeToStream(const string& input);
        ofstream m_ofstream;
        string m_path;
};

#endif
