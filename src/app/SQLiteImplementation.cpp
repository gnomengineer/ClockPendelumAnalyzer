#include "../include/SQLiteImplementation.h"
#include <iostream>
#include <iomanip>
#include <sstream>

SQLiteImplementation::~SQLiteImplementation(){
    disconnect();
}

void SQLiteImplementation::connect(std::string uri){
    m_ErrorCode = sqlite3_open_v2(uri.c_str(), &m_DataBase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, NULL);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError("SQLiteImplementation::connect");
    } else {
        std::cout << "database connected" << std::endl;
    }

    if (m_ErrorCode == 0) {
       createTableOnce(); 
    }
}

void SQLiteImplementation::disconnect(){
    m_ErrorCode = sqlite3_close(m_DataBase);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError("SQLiteImplementation::disconnect");
    } else {
        std::cout << "database disconnected" << std::endl;
    }
}

std::list<DataTupel> SQLiteImplementation::getDataByDate(const std::string& date){
    m_Result.clear();
    getData("date", date);
    std::cout << "return Data by Date" << std::endl;
    return m_Result;
}

std::list<DataTupel> SQLiteImplementation::getDataByName(const std::string& name){
    m_Result.clear();
    getData("clock", name);
    std::cout << "return Data by Name" << std::endl;
    return m_Result;
}

void SQLiteImplementation::getData(const std::string& key, const std::string& value) {
    std::stringstream sqlStatement;
    sqlStatement << "SELECT * FROM " << TABLE << " WHERE " << key <<"= '"<< value << "';";

    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.str().c_str(),
            callback, this, &m_SQLErrorMessage);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError("SQLiteImplementation::getData[ByName/ByDate]");
        printSQLError();
    }
}

std::list<DataTupel> SQLiteImplementation::getDataByNameDate(const std::string& name, const std::string& date) {
    m_Result.clear();
    std::stringstream sqlStatement;
    sqlStatement << "SELECT * FROM " << TABLE << " WHERE clock = '"<< name << "' AND date = '" << date << "';";

    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.str().c_str(),
            callback, this, &m_SQLErrorMessage);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError("SQLiteImplementation::getDataByNameDate");
        printSQLError();
    }
    return m_Result;
}

int SQLiteImplementation::saveData(DataTupel data){
    std::stringstream sqlStatement;
    sqlStatement << "INSERT INTO " << TABLE << 
        " (clock, date, absolutetime, ref_frequency, heat, humidity) " <<
        " VALUES('" <<
        data.getClockName() << "'," <<
        data.getDate() << "," <<
        data.getAbsoluteTime() << "," <<
        data.getReferenceFrequency() << "," <<
        data.getHeat() << "," <<
        data.getHumidity() << ");";

    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.str().c_str(),
            NULL, NULL, &m_SQLErrorMessage);

    if ( m_ErrorCode != SQLITE_OK ) {
        printSQLiteError("SQLiteImplementation::saveData");
        printSQLError();
    }

    return m_ErrorCode;
}

int SQLiteImplementation::saveDataList(std::list<DataTupel> data){
    m_ErrorCode = 0; //we assume everything worked fine so far
    for ( std::list<DataTupel>::iterator element = data.begin();
            element != data.end(); ++element) {
        saveData(*element);
    }
    std::cout << "data list saved" << std::endl;
    return m_ErrorCode;
}

void SQLiteImplementation::printSQLiteError(const std::string errorOccurence) {
    std::cerr << "[EE]: database error occured with error code (" <<
        m_ErrorCode << ") in method" << errorOccurence << std::endl;
    //TODO pad the error message
    std::cout << std::setw(5) << sqlite3_errstr(m_ErrorCode) << std::endl;
}

void SQLiteImplementation::printSQLError() {
    std::cerr << "[EE]: SQL syntax error while executing statement" << std::endl;
    //TODO pad the error message
    std::cerr << std::setw(5) << m_SQLErrorMessage << std::endl;
    sqlite3_free(m_SQLErrorMessage);
}

void SQLiteImplementation::createTableOnce() {
    std::string sqlStatement = "SELECT * FROM " + TABLE;
    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.c_str(), NULL, NULL, &m_SQLErrorMessage);

    if (m_ErrorCode != SQLITE_OK ) {
        std::cout << "Table doesn't exist, creating it" << std::endl;

        sqlStatement = "CREATE TABLE " + TABLE + "( ID INTEGER PRIMARY KEY AUTOINCREMENT,"
            + " clock TEXT NOT NULL,"
            + " date INT NOT NULL,"
            + " absolutetime INT NOT NULL,"
            + " ref_frequency INT NOT NULL,"
            + " heat INT,"
            + " humidity INT)";
        m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.c_str(), NULL, NULL, &m_SQLErrorMessage);
        if(m_ErrorCode != SQLITE_OK) {
            printSQLiteError("SQLiteImplementation::createTableOnce");
            printSQLError();
        }
    }
}

int SQLiteImplementation::addToList(int numberOfRows,
        char** data, char** columnNames) {
    std::string clockname, date, heat, humidity;
    uint32_t absolutetime = 0, refFrequency = 0;

    for ( int counter = 0; counter < numberOfRows; counter++ ) {
        DataTupel::Tupel column = static_cast<DataTupel::Tupel>(counter);

        switch ( column) {
            case DataTupel::Tupel::CLOCKNAME: 
                clockname = data[counter];
                break;
            case DataTupel::Tupel::DATE: 
                date = data[counter]; 
                break;
            case DataTupel::Tupel::ABSOLUTETIME:
                absolutetime = static_cast<uint32_t>(std::stoul(data[counter]));
                break;
            case DataTupel::Tupel::REF_FREQUENCY:
                refFrequency = static_cast<uint32_t>(std::stoul(data[counter]));
                /*
            case DataTupel::Tupel::HEAT: 
                heat = (int)data[counter]; 
                break;
            case DataTupel::Tupel::HUMIDITY:
                humidity = (int)data[counter];
                break;
                */
            default: break;
        }
    }
    
    DataTupel resultTupel(clockname, date, absolutetime, refFrequency);
    m_Result.push_back(resultTupel);
    
    return 0;
}

int callback(void* object,int numberOfRows, char** data, char** columnNames) {
    SQLiteImplementation* sql = reinterpret_cast<SQLiteImplementation*>(object);
    return sql->addToList(numberOfRows,data,columnNames);
}
