#ifndef GPIOFILEWRITER_H
#define GPIOFILEWRITER_H

class GPIOFileWriter
{
    public:
        GPIOFileWriter(string path);
        ~GPIOFileWriter();
        void operator<<(int input);
        void operator<<(string input);

    private:
        void writeToStream(string input);
        ofstream m_ofstream;
        string m_path;
}

#endif
