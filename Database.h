#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "include/mysql.h"
#include "Table.h"

class Database {
public:
    enum Flags {
        NONE = 0,
        PRINT_CONTENT = 1,
        VERBOSE_OUTPUT = 1 << 1
    };

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
    bool scanAll ();

    // Executes given query
    bool executeQuery (std::string query, const unsigned int flags = Database::NONE);

    // Obtains rows from result
    void fetchQuery ();

    // Displays fetched rows from query
    void printQueryResults ();

    // Displays all tables and columns and optionally content ad well
    void printAll (const unsigned int flags = Database::NONE);

private:
    // Methods for scanning the database to obtain all tables, columns, their widths and 
    // constraints between them.
    bool getTables ();
    bool getColumns ();
    bool getConstraints ();

    // Structure with database information
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

