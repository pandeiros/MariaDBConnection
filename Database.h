#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "include/mysql.h"
#include "Table.h"

class Database {
public:
    // Window width
    static unsigned int CONSOLE_WIDTH;

    // Database and connection specifications
    struct DatabaseInfo {
        std::string hostname = "127.0.0.1";
        std::string dbName = "Steam";
        std::string username = "root";
        int portNumber = 6969;
        int options = 0;
    };

    // Cons. & Des.
    Database ();
    ~Database ();

    // Constructor with information about database as a parameter
    Database (DatabaseInfo & dbInfo);

    // Constructor with filename with database config.
    Database (std::string configFilename);

    // Connects with given host
    bool connect ();

    // Performs full database scan for tables and their columns
    void scanAll ();

    // Executes given query
    bool executeQuery (std::string query, bool verbose = false);

    // Obtains rows from result
    void fetchQuery ();

    void printAll (bool ifPrintContent = false);

private:
    DatabaseInfo mDBInfo;

    // Database tables vector
    std::vector <Table> mTables;

    // Attributes for executing queries and fetching results
    MYSQL * mConnection;
    MYSQL_RES * mResult;
    MYSQL_ROW mRow;

    // Holds all current row fecthing results
    std::vector <std::string> mFetchedRows;
    unsigned int mFetchedColNumber;
};

