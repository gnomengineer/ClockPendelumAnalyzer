#include "../include/SQLiteImplementation.h"
#include <iostream>

SQLiteImplementation::~SQLiteImplementation(){

}

void SQLiteImplementation::connect(std::string uri){
    std::cout << "database connected" << std::endl;
}

void SQLiteImplementation::disconnect(){
    std::cout << "database disconnected" << std::endl;
}

std::list<DataTupel> SQLiteImplementation::getDataByDate(const std::string& date){
    std::cout << "return Data by Date" << std::endl;
    return std::list<DataTupel> dateData;
}

std::list<DataTupel> SQLiteImplementation::getDataByName(const std::string& name){
    std::cout << "return Data by Name" << std::endl;
    return std::list<DataTupel> nameData;
}

void SQLiteImplementation::saveData(DataTupel data){
    std::cout << "data tupel saved" << std::endl;
}

void SQLiteImplementation::saveDataList(std::list<DataTupel> data){
    std::cout << "data list saved" << std::endl;
}
