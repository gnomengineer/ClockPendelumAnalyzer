#include <fstream>
#include <string>
#include "include/GPIOFileWriter.h"

GPIOFileWriter::GPIOFileWriter (string path) 
    : m_path(path)
{
    m_ofstream(path.c_str())
}

GPIOFileWriter::~GPIOFileWriter () {
    if ( m_ofstream >= 0 )
        m_ofstream.close()
}

GPIOFileWriter::operator<<(string input) {
    writeToStream(input);
}

GPIOFileWriter::operator<<(int input) {
    writeToStream(to_string(input));
}

GPIOFileWriter::writeToStream(string input) {
    if ( m_ofstream < 0 ) {
        cout << "Error!, no file open called " << m_path << endl;
    }
    else {
        m_ofstream << input;
    }
}

