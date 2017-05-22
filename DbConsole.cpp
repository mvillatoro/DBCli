//
// Created by mario on 5/20/17.
//

#include "DbConsole.h"

DbConsole::DbConsole() {
    executeCli();
}

void DbConsole::splitCommand(string commandString,  const string& splitter, vector<string>& tokens) {

    size_t prev = 0, pos = 0;
    do
    {
        pos = commandString.find(splitter, prev);
        if (pos == string::npos) pos = commandString.length();
        string token = commandString.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + splitter.length();
    }
    while (pos < commandString.length() && prev < commandString.length());

}

void DbConsole::executeCli() {

    char command[30];
    bool executionState = true;

    do{
        cout<<"~$ ";
        cin.getline(command, sizeof(command));

        vector<string> parameters;
        splitCommand(command, " ", parameters);

        if(compareTokenStrings("exit", parameters)){
            executionState = false;
        }else if(compareTokenStrings("create", parameters)){

            int fileSize = 300;

            if(compareTokenStrings("-z", parameters))
                fileSize = stoi(parameters[4]);

            if(compareTokenStrings("database", parameters))
                createDatabase(parameters[2], fileSize);

            if(compareTokenStrings("table", parameters))
                createTable(parameters[2], command);

        }
        else if(compareTokenStrings("connect", parameters)){
            openDatabaseFile(parameters[2]);
        }else{
            cout << "Command not recognized..." << endl;
        }

    }while(executionState);

}

bool DbConsole::compareTokenStrings(string command, vector<string> tokens) {

    const char * c = command.c_str();
    for(vector<string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i){
        string token = *i;

        if(strcmp(c, token.c_str()) == 0)
            return true;
    }

    return false;
}

void DbConsole::createDatabase(string dbName, int dbSize) {

    std::ofstream ofs(dbName + ".dbc", std::ios::binary | std::ios::out);
    ofs.seekp((dbSize<<20) - 1);
    ofs.write("", 1);

}

void DbConsole::openDatabaseFile(string dbName) {

    dbName += ".dbc";

    if(dbName != DbName){
        if(dbFile.is_open()){

            cout<< "Disconnecting from " + DbName << endl;
            dbFile.close();
            dbFile.open ( dbName, ios::out | ios::app | ios::binary);
            DbName = dbName;

            if(dbFile.is_open())
                cout << "Connection successful!" << endl;

        }
    }else
        cout<< "Already connected to" + DbName <<endl;

}

void DbConsole::createTable(string tableName, string command) {

    vector<string> tableParameters;

    splitCommand(command, "(", tableParameters);




    if (dbFile.is_open())
    {
        dbFile << "";
    }
    else cout << "Unable to open file";
}


/*
 *
 * CREATE TABLE table_name (
    column1 datatype,
    column2 datatype,
    column3 datatype,
   ....
);
 */