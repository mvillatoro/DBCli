//
// Created by mario on 5/20/17.
//

#ifndef DBCLI_DBCONSOLE_H
#define DBCLI_DBCONSOLE_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class DbConsole {
public:

    string DbName = "*";
    char * memoryBlock = new char[512];
    int bitMapSize;

    DbConsole();
    void getBitmap();
    void executeCli();
    void disconnectFromDatabase();
    void openDatabaseFile(string dbName);
    void createDatabase(string dbName, int dbSize);
    void createTable(string tableName, string command);
    void insertIntoTable(string tableName, string parameters);
    void splitCommand(string commandString, const string& delim, vector<string>& tokens);
    bool compareTokenStrings(string command, vector<string> tokens);
    string tableExists(string tableName);

    void dropTable(string tableName);
    void updateTable(string tableName, string updatedData,  string whereCondition);

    char * readBlock(int readPointer);
    void writeAddBlock(int writePointer, string data);
    void writeReplaceBlock(int writePointer, string data, string message);

    int getColumnPointer(string tableHeader, string column);

};


#endif //DBCLI_DBCONSOLE_H