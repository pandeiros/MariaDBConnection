#pragma once
#include <string>
#include <vector>
#include "include/mysql.h"
#include "Table.h"

class Database {
public:
    // Database and connection specifications
    struct DatabaseInfo {
        std::string hostname = "193.238.183.9";
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

    // Executes given query and displays results
    void executeQuery (std::string query);

private:
    DatabaseInfo mDBInfo;

    // Database tables vector
    std::vector <Table> mTables;

    // Attributes for executing queries and fetching results
    MYSQL * mConnection;
    MYSQL_RES * mResult;
    MYSQL_ROW mRow;

};

