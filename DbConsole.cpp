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

    char command[100];
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

        }else if(compareTokenStrings("connect", parameters)){
            openDatabaseFile(parameters[2]);
        }else if(compareTokenStrings("drop", parameters)) {

            if (compareTokenStrings("database", parameters)) {
                string dbName = parameters[2] + ".dbc";

                if (remove(dbName.c_str()) != 0)
                    perror("Database does not exists.");
                else
                    puts("Database successfully dropped");
            }
        }else if(compareTokenStrings("help", parameters)){
            cout<< "create database [database name]" <<endl;
            cout<< "drop database [database name]" <<endl;
            cout<< "connect to [database name]" <<endl;

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

    string tableCommand = "[" + tableName + ":";

    string newCommand = command.substr(0, command.size()-1);

    vector<string> tableParameters;

    splitCommand(newCommand, "(", tableParameters);

    tableParameters[0] = "";

    std::stringstream joinedValues;
    for (auto value: tableParameters)
            joinedValues << value;

    vector<string> tableParameter;

    splitCommand(joinedValues.str(), ",", tableParameter);

    for (auto i = tableParameter.begin(); i != tableParameter.end(); ++i){

        string text = *i;

        if(text.at(0) == ' '){
            auto it = std::find(text.begin(), text.end(), ' ');
            if (it != text.end())
                text.erase(it);
        }
        *i = text;

//        cout << *i << endl;
    }

    for (auto i = tableParameter.begin(); i != tableParameter.end(); ++i){
        vector<string> tableColumns;

        splitCommand(*i, " ", tableColumns);

        /*
         * int(4)
         * double(8)
         * char(n)<4000;
         */

        if(compareTokenStrings("int", tableColumns))
            tableCommand += "|" + tableColumns[0] + "," + "int";
//        else if(compareTokenStrings("double", tableColumns))
//            tableCommand += "|" + tableColumns[0] + "double";
//        else if(compareTokenStrings("char", tableColumns))
//            tableCommand += "|" + tableColumns[0] + "char";
//
    }

    tableCommand += "]";

    cout << tableCommand << endl;

//  [tableName:column,dataType|column,dataType|column,dataType]
//    if (dbFile.is_open())
//    {
//        dbFile << "";
//    }
//    else cout << "Unable to open file";
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