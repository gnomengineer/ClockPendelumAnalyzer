#include <fstream>
#include <string>
#include <iostream>
#include "include/GPIOFileWriter.h"

GPIOFileWriter::GPIOFileWriter (const string& path) 
    : m_path(path)
{
    m_ofstream.open(path.c_str());
}

GPIOFileWriter::~GPIOFileWriter () {
    if ( !m_ofstream.is_open() )
        m_ofstream.close();
}

int GPIOFileWriter::operator<<(const string& input) {
    return writeToStream(input);
}

int GPIOFileWriter::operator<<(int input) {
    return writeToStream(to_string(input));
}

int GPIOFileWriter::writeToStream(const string& input) {
    if ( m_ofstream.is_open() ) {
        cout << "Error!, no file open called " << m_path << endl;
        return -1;
    }
    else {
        m_ofstream << input;
        return 0;
    }
}

