#ifndef SQLITEIMPLEMENTATION_H
#define SQLITEIMPLEMENTATION_H

#include "DataTupel.h"
#include "IDBConnector.h"
#include "IDataPersistor.h"
#include <list>
#include <string>
#include <sqlite3.h>

//TODO a static function in a header file of a cpp class ?!
static int callback(void* object,int numberOfRows, char** data, char** columnNames);

class SQLiteImplementation : public IDBConnector, public IDataPersistor {
    public:
        ~SQLiteImplementation();
        void connect(std::string uri);
        void disconnect();
        std::list<DataTupel> getDataByDate(const std::string& date);
        std::list<DataTupel> getDataByName(const std::string& name);
        std::list<DataTupel> getDataByNameDate(const std::string& name, const std::string& date);
        int saveData(DataTupel data);
        int saveDataList(std::list<DataTupel> data);
        int addToList(int numberOfRows, char** data, char** columnNames);
    private:
        const std::string TABLE = "clocktable";
        void printSQLiteError(const std::string errorOccurence = "");
        void printSQLError();
        void createTableOnce();
        void getData(const std::string& key, const std::string& value);

        std::list<DataTupel> m_Result;
        sqlite3* m_DataBase;
        int m_ErrorCode = 0;
        char* m_SQLErrorMessage = 0;
};

#endif 
