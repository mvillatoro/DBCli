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


//        string var = "create table client(id int, name char.6000, money double)";
//        string var = "create table client(id int, money double)";
//        strcpy(command, var.c_str());

        vector<string> parameters;
        splitCommand(command, " ", parameters);

        if(compareTokenStrings("exit", parameters)){
            executionState = false;
        }else if(compareTokenStrings("create", parameters)){

            int fileSize = 3;

            if(compareTokenStrings("-z", parameters))
                fileSize = stoi(parameters[4]);

            if(compareTokenStrings("database", parameters))
                createDatabase(parameters[2], fileSize);

            if(compareTokenStrings("table", parameters)){

                string newCommand = parameters[2];

                vector<string> tableName;

                splitCommand(newCommand, "(", tableName);


                createTable(tableName[0], command);
            }

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
        }else if(compareTokenStrings("help", parameters)) {
            cout << "create database [database name]" << endl;
            cout << "drop database [database name]" << endl;
            cout << "connect to [database name]" << endl;
            cout << "disconnect" << endl;
        }else if(compareTokenStrings("disconnect", parameters)) {
            disconnectFromDatabase();
        }else if(compareTokenStrings("read", parameters)){

            readFromDatabase();
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

    string DbName = dbName + ".dbc";

    ifstream my_file(DbName);
    if (!my_file)
    {
        std::ofstream ofs(DbName, std::ios::binary | std::ios::out);
        ofs.seekp((dbSize<<20) - 1);
        ofs.write("", 1);

        cout << "Database " + dbName + " created." << endl;
    }else{
        cout << "Database " + dbName + " already exists." << endl;
    }

}

void DbConsole::openDatabaseFile(string dbName) {

    dbName += ".dbc";

    if(DbName == "*"){

        ifstream my_file(dbName);

        if (!my_file)
        {
            cout << "Database does not exists" << endl;
        }else{
            dbFile.open ( dbName, ios::out | ios::app | ios::binary);
            DbName = dbName;

            if(dbFile.is_open()){
                cout << "Connection successful!" << endl;
                dbFile.close();
            }
        }
    }else
        cout << "First disconnect from database." << endl;

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
    }

    for (auto i = tableParameter.begin(); i != tableParameter.end(); ++i){
        vector<string> tableColumns;

        splitCommand(*i, " ", tableColumns);


        string varchar = *i;

        vector<string> charSplit;
        size_t found = varchar.find("char");
        if (found!=string::npos){
            //cout << varchar << endl;
            splitCommand(varchar, ".", charSplit);

            int charSize = stoi(charSplit[1]);

            if(charSize > 4000){
                cout<< "Char size overflow." << endl;
                return;
            }

            tableCommand += "|" + tableColumns[0] + "," + tableColumns[1];
        }


        if(compareTokenStrings("int", tableColumns))
            tableCommand += "|" + tableColumns[0] + "," + "int";
        else if(compareTokenStrings("double", tableColumns))
            tableCommand += "|" + tableColumns[0] + "," + "double";
        else if(compareTokenStrings("char", tableColumns)){
            tableCommand += "|" + tableColumns[0] + "," + tableColumns[1];
            //tableCommand += "|" + tableColumns[0] + "," + "char";

        }

    }

    tableCommand += "]";

    cout << tableCommand << endl;

    if(DbName == "*"){
        cout << "No database found." << endl;
    }else{
        dbFile.open ( DbName, ios::out | ios::app | ios::binary);

        if (dbFile.is_open())
        {
            dbFile << tableCommand;
            dbFile.close();
        }
        else cout << "Unable to open file" << endl;
    }

}

void DbConsole::disconnectFromDatabase() {

    DbName = "*";
    dbFile.close();
    cout << "Connection closed." << endl;

}

void DbConsole::readFromDatabase() {

    if(DbName == "*"){
        cout << "No database found." << endl;
    }else{
        string line;
        ifstream myDatabase(DbName);

        if(myDatabase.is_open()){
            while (getline(myDatabase,line )){
                cout << line <<endl;
            }

            myDatabase.close();
        }else{
            cout << "Unable to access database" << endl;
        }

    }
}
