#include "../include/DataTransfer.h"
#include "../include/SQLiteImplementation.h"
#include <iostream>

DataTransfer::DataTransfer() {
    m_Connector = new SQLiteImplementation();
    if (m_Connector ){
        m_Connector->connect("file:/mnt/clock_analyzer.db");
        m_Persistor = dynamic_cast<IDataPersistor*>(m_Connector);
    }
    std::cout << "DataTransfer created" << std::endl;
}

DataTransfer::~DataTransfer() {
    if ( m_Connector) {
        m_Connector->disconnect();
        m_Connector = 0;
        m_Persistor = 0;
    }
    std::cout << "DataTransfer deleted" << std::endl;
}

std::list<DataTupel> DataTransfer::getDataListByDate(std::string date) {
    if (m_Persistor) {
        m_DataList = m_Persistor->getDataByDate(date);
    } else {
        m_DataList.clear();
    }
    return m_DataList;    
}

std::list<DataTupel> DataTransfer::getDataListByName(std::string name) {
    if (m_Persistor) {
        m_DataList = m_Persistor->getDataByName(name);
    } else {
        m_DataList.clear();
    }
    return m_DataList;    
}

bool DataTransfer::saveDataList(std::list<DataTupel> data) {
    if (m_Persistor->saveDataList(data) != 0) {
        return false;
    }
    return true;
}
