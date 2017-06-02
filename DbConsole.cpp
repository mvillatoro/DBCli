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

            int fileSize = 200;

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
            cout << "insert into [tableName] ([column1], [column2]...): values([value1], [value2]...)" << endl;
            cout << "disconnect" << endl;
        }else if(compareTokenStrings("disconnect", parameters)) {
            disconnectFromDatabase();
        }else if(compareTokenStrings("insert", parameters)){
            string newCommand = parameters[2];
            vector<string> tableName;
            splitCommand(newCommand, "(", tableName);
            insertIntoTable(tableName[0], command);
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

    string MyName = dbName + ".dbc";

    int fileSize = (1024 * dbSize) + 4;
    int bitmapSize = (fileSize - 4) / 512;
    char bitmapBlock[512];

    for (int j = 0; j < bitmapSize; ++j) {
        bitmapBlock[j] = '0';
    }

    vector<char> empty(1024, 0);
    ofstream ofs(MyName, ios::binary | ios::out);

    for (int i = 0; i < fileSize; i++)
        if (!ofs.write(&empty[0], empty.size())) {
            std::cerr << "problem writing to file" << std::endl;
            return;
        }

    ofstream dataBase(MyName, ios::binary | ios::in);

    if (dataBase.is_open())
    {

        vector <unsigned char> arrayOfBytes(4);
        for (int i = 0; i < 4; i++)
            arrayOfBytes[3 - i] = (bitmapSize >> (i * 8));

        dataBase <<  arrayOfBytes[3];
        dataBase <<  arrayOfBytes[2];
        dataBase <<  arrayOfBytes[1];
        dataBase <<  arrayOfBytes[0];


        for (int i = 0; i < bitmapSize; ++i)
            dataBase << bitmapBlock[i];

        dataBase.seekp(4);
        dataBase << '1';
        dataBase << '1';

    }

    dataBase.close();

    cout<< "Database created." << endl;

}

void DbConsole::openDatabaseFile(string dbName) {

    dbName += ".dbc";

    if(DbName == "*"){

        ifstream my_file(dbName);

        if (!my_file)
        {
            cout << "Database does not exists" << endl;
        }else{
            my_file.open ( dbName, ios::out | ios::app | ios::binary);
            DbName = dbName;

            if(my_file.is_open()){
                cout << "Connection successful!" << endl;
                my_file.close();
            }
        }
    }else
        cout << "First disconnect from database." << endl;

}

void DbConsole::createTable(string tableName, string command) {

    string tableCommand = tableName + ":";

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

        }

    }

    tableCommand += ";";

    if(DbName == "*")
        cout << "No database found." << endl;
    else{
        ifstream file (DbName, ios::out|ios::binary);
        ofstream dbFile( DbName, ios::binary | ios::in);

        getBitmap();


        char * memblock;
        memblock = new char [512];
        file.seekg(516, ios::beg);
        file.read(memblock, 512);

        int z = 0;
        for(int i = 0; i < 512; i++) {
            if ((memblock[i] == NULL) && (memblock[i] == '\0')){
                if(z < tableCommand.length()){
                    memblock[i] = tableCommand[z];
                    z++;
                }
            }
        }

        dbFile.seekp(516);
        dbFile << memblock;
        dbFile.close();
        cout << "Table created" << endl;

    }

}

void DbConsole::disconnectFromDatabase() {
    DbName = "*";
    cout << "Connection closed." << endl;
}

void DbConsole::getBitmap() {

    char * memblock;

    ifstream file (DbName, ios::out|ios::binary);
    if(file.is_open()){

        uint32_t bitmapSize;

        file.read(reinterpret_cast<char *>(&bitmapSize), sizeof(bitmapSize));

        memblock = new char [512];
        file.seekg(4, ios::beg);
        file.read(memblock, 512);
        file.close();

        bitMapSize =  bitmapSize;
        for(int i = 0; i < bitmapSize; i++)
            memoryBlock[i] = memblock[i];

        delete[] memblock;
    }
    else cout << "Unable to open file" << endl;
}

void DbConsole::insertIntoTable(string tableName, string parameters) {

    if(DbName == "*"){
        cout << "You must be connected to a database" << endl;
        return;
    }

    string tableHeader = tableExists(tableName);

    if(tableHeader == "-1"){
        cout << "Table not found" << endl;
        return;
    }

    getBitmap();

    int cleanBitDiskAddress = 0;

    for (int i = 0; i < bitMapSize; ++i) {
        if(memoryBlock[i] == '0'){
            cleanBitDiskAddress = i;
            break;
        }
    }

    int writePointer = (cleanBitDiskAddress * 512) + 4;

    char * memblock2;

    ifstream file (DbName, ios::out|ios::binary);
    if(file.is_open()){

        uint32_t bitmapSize;
        file.read(reinterpret_cast<char *>(&bitmapSize), sizeof(bitmapSize));
        memblock2 = new char [512];
        file.seekg(writePointer, ios::beg);
        file.read(memblock2, 512);
        file.close();
    }
    else cout << "Unable to open file" << endl;

    string rowHeader = tableName + ":";

    vector<string> rowParams;

    splitCommand(parameters, "(", rowParams);

    if(rowParams[1].size() >= 2)
        rowParams[1] = rowParams[1].substr(0, rowParams[1].size() -1);
    else
        return;

    vector<string> tableColumns;
    splitCommand(tableHeader, "|" , tableColumns);

    for(vector<string>::const_iterator i = tableColumns.begin() +1; i != tableColumns.end(); ++i) {
        string token = *i;

        vector<string> columnData;
        splitCommand(token, ",", columnData);

        size_t found = columnData[1].find("char");

        //rowData += columnData[1] + ",";

        if(found != string::npos){
            vector<string> charParam;
            splitCommand(columnData[1], ".", charParam);
            int charSize = stoi(charParam[1]);
            rowHeader += charParam[0] + "." + charParam[1] + ",";

        }else{
            rowHeader += columnData[1] + ",";
        }
    }

    rowHeader = rowHeader.substr(0, rowHeader.size() -1);
   // cout << rowHeader << endl;
   // cout << rowParams[1] << endl;

    string dataRow  = tableName + ":";

    vector<string> rowHead;
    vector<string> rowData;

    splitCommand(rowHeader, ",", rowHead);
    splitCommand(rowParams[1], ",", rowData);

    for(int i = 0; i < rowHead.size(); i++){
//        cout<< rowHead[i];
//        cout<< ": ";
//        cout<< rowData[i]<<endl;

        size_t found = rowHead[i].find("char");

        if(found != string::npos){
            string x;
            x = rowHead[i].substr(rowHead[i].find(".") +1);

            int charSize = stoi(x);

            char *charData = new char[charSize];

            for (int j = 0; j < charSize; j++) {
                if(j < rowData[i].length()){
                    charData[j] = rowData[i].at(j);
                }else{
                    charData[j] = '*';
                }

            }

            for(int k = 0; k < charSize; k++){
                dataRow += charData[k];
            }
            dataRow += ",";
        }else{
            dataRow += rowData[i];
            dataRow += ",";
        }
    }
    dataRow = dataRow.substr(0, dataRow.size() -1);

    dataRow += "|";

    int x = 0;
    for(int i = 0; i < bitMapSize; i++){
        if((memblock2[i] == NULL) && (memblock2[i] == '\0')){
            if(i < dataRow.length()){
                memblock2[i] = dataRow[x];
                x++;
            }
        }
    }

//    for(int t = 0; t < 512; t++)
//        cout <<  memblock[t];


    if(DbName == "*")
        cout << "No database found." << endl;
    else{
        ifstream file (DbName, ios::out|ios::binary);
        ofstream dbFile( DbName, ios::binary | ios::in);

        getBitmap();

        char * memblock;
        memblock = new char [512];

        file.seekg(writePointer, ios::beg);
        file.read(memblock, 512);

        int z = 0;
        for(int i = 0; i < 512; i++) {
            if ((memblock[i] == NULL) && (memblock[i] == '\0')){
                if(z < dataRow.length()){
                    memblock[i] = dataRow[z];
                    z++;
                }
            }
        }

        dbFile.seekp(writePointer);
        dbFile << memblock;
        dbFile.close();
        cout << "Value inserted" << endl;
    }

    delete[] memblock2;

}

string DbConsole::tableExists(string tableName) {

    char * memblock;

    ifstream file (DbName, ios::out|ios::binary);
    if(file.is_open()){

        uint32_t bitmapSize;

        file.read(reinterpret_cast<char *>(&bitmapSize), sizeof(bitmapSize));

        memblock = new char [512];
        file.seekg(516, ios::beg);
        file.read(memblock, 512);
        file.close();

        for(int i = 0; i < bitmapSize; i++)
            memoryBlock[i] = memblock[i];

        delete[] memblock;
    }
    else cout << "Unable to open file" << endl;

    vector<string> tableNames;

    splitCommand(memblock, ";", tableNames);

    char delimiter(';');

    string nuTableName;

    for(vector<string>::const_iterator i = tableNames.begin(); i != tableNames.end(); ++i){
        string const& token = *i;

        std::string::size_type pos = token.find(':');
        if (pos != std::string::npos)
        {
            nuTableName = token.substr(0, pos);
            if (tableName == nuTableName)
                return token;
        }
    }

    return "-1";
}