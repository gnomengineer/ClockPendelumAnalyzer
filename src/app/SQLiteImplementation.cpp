#include "../include/SQLiteImplementation.h"
#include <iostream>
#include <iomanip>
#include <sstream>

SQLiteImplementation::~SQLiteImplementation(){

}

void SQLiteImplementation::connect(std::string uri){
    m_ErrorCode = sqlite3_open_v2(uri.c_str(), &m_DataBase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, NULL);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError();
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
        printSQLiteError();
    } else {
        std::cout << "database disconnected" << std::endl;
    }
}

std::list<DataTupel> SQLiteImplementation::getDataByDate(const std::string& date){
    std::cout << "return Data by Date" << std::endl;
    std::list<DataTupel> dateData;
    return dateData;
}

std::list<DataTupel> SQLiteImplementation::getDataByName(const std::string& name){
    std::stringstream sqlStatement;
    sqlStatement << "SELECT * FROM " << TABLE << " WHERE clock = '"<< name << "';";

    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.str().c_str(),
            addToList, NULL , &m_SQLErrorMessage);
    if (m_ErrorCode != SQLITE_OK) {
        printSQLiteError();
        printSQLError();
    }
    std::cout << "return Data by Name" << std::endl;
    std::list<DataTupel> nameData;
    return nameData;
}

void SQLiteImplementation::saveData(DataTupel data){
    std::stringstream sqlStatement;
    sqlStatement << "INSERT INTO " << TABLE << 
        " (clock, date, absolutetime, heat, humidity) " <<
        " VALUES('" <<
        data.getClockName() << "'," <<
        data.getDate() << "," <<
        data.getAbsoluteTime() << "," <<
        data.getHeat() << "," <<
        data.getHumidity() << ");";

    m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.str().c_str(),
            NULL, NULL, &m_SQLErrorMessage);

    if ( m_ErrorCode != SQLITE_OK ) {
        printSQLiteError();
        printSQLError();
        std::cout << "during saving option" << std::endl;
    } else {
        std::cout << "data tupel saved" << std::endl;
    }
}

void SQLiteImplementation::saveDataList(std::list<DataTupel> data){
    std::cout << "data list saved" << std::endl;
}

void SQLiteImplementation::printSQLiteError() {
    std::cerr << "[EE]: database error occured with error code (" <<
        m_ErrorCode << ")" << std::endl;
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
        std::cout << "Table doesn't exist" << std::endl;
        printSQLError();

        sqlStatement = "CREATE TABLE " + TABLE + "( ID INTEGER PRIMARY KEY AUTOINCREMENT,"
            + " clock TEXT NOT NULL,"
            + " date INT NOT NULL,"
            + " absolutetime INT NOT NULL,"
            + " heat INT,"
            + " humidity INT)";
        m_ErrorCode = sqlite3_exec(m_DataBase, sqlStatement.c_str(), NULL, NULL, &m_SQLErrorMessage);
        if(m_ErrorCode != SQLITE_OK) {
            printSQLiteError();
            printSQLError();
        }
    }
}

int SQLiteImplementation::addToList(void* info, int numberOfRows,
        char** data, char** columnNames) {
    std::cout << "Test" << std::endl;

    //TODO implement adding result rows to a list which will be returned
    return 0;
}