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

    ofstream dbFile;
    string DbName = "*";

    DbConsole();
    void executeCli();
    void disconnectFromDatabase();
    void readFromDatabase();
    void openDatabaseFile(string dbName);
    void createDatabase(string dbName, int dbSize);
    void createTable(string tableName, string command);
    void splitCommand(string commandString, const string& delim, vector<string>& tokens);
    bool compareTokenStrings(string command, vector<string> tokens);

};


#endif //DBCLI_DBCONSOLE_H