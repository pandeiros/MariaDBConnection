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
        VERBOSE_OUTPUT = 1 << 2,
        NO_FETCH = 1 << 3
    };

    // Displaying widths
    struct Widths {
        unsigned int MAX = 0;
        unsigned int NAME = 0;
        const unsigned int TYPE = 20;
        const unsigned int NULLABLE = 4;
        const unsigned int KEY = 3;
        const unsigned int DEFAULT = 10;
        const unsigned int EXTRA = 20;
    };
    static Widths WIDTHS;

    // Database and connection specifications
    struct DatabaseInfo {
        std::string hostname = "127.0.0.1";     // 193.238.183.9
        std::string dbName = "_4sportlab";
        std::string username = "root";
        int portNumber = 3306;      // 3306
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

    // Disconnects with previously connected host
    bool disconnect ();

    // Performs full database scan for tables and their columns
    bool scanAll ();

    // Return pointer to table which name matches the argument
    Table * findByName (const std::string name);

    // Executes given query
    bool executeQuery (std::string query, const unsigned int flags = Database::NONE);

    // Obtains rows from result
    void fetchQuery ();

    // Sorts Tables in order of increasing foreing key dependencies
    void sortTablesByDependencies ();

    // Inserts random data based on column type and foreign key dependecies
    bool insertRandomData (Table * const table, const unsigned int recordCount);

    // Creates a random std::string value based on column type and record index
    std::string createRandomData (Column * const column, const unsigned int recordIndex);

    // Displays fetched rows from query
    void printQueryResults ();

    // Displays all tables and columns and optionally content ad well
    void printAll (const unsigned int flags = Database::NONE);

    // Getters
    std::vector <Table *> * getTableVector ();

private:
    // Methods for scanning the database to obtain all tables, columns, their widths and 
    // constraints between them.
    bool getTables ();
    bool getColumns ();
    bool getConstraints ();

    // Structure with database information
    DatabaseInfo mDBInfo;

    // Database tables vector
    std::vector <Table*> mTables;

    // Attributes for executing queries and fetching results
    MYSQL * mConnection;
    MYSQL_RES * mResult;
    MYSQL_ROW mRow;

    // Holds all current row fecthing results
    std::vector <std::string> mFetchedRows;
    unsigned int mFetchedColNumber;
};

