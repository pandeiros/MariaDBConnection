#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "include/mysql.h"
#include "Table.h"
#include "Utilities.h"

class Database {
public:
    enum Flags {
        NONE = 0,
        PRINT_CONTENT = 1,
        PRINT_COLUMN_INFO = 1 << 1,
        VERBOSE_OUTPUT = 1 << 2
    };

    // Displaying widths
    static unsigned int CONSOLE_WIDTH;
    static const unsigned int TYPE_WIDTH = 20;
    static const unsigned int DEFAULT_WIDTH = 10;
    static const unsigned int EXTRA_WIDTH = 20;

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

