#include <conio.h>
#include "Database.h"

unsigned int Database::CONSOLE_WIDTH = 20;

Database::Database () {
}

Database::~Database () {
}

Database::Database (Database::DatabaseInfo & dbInfo) {
    mDBInfo = dbInfo;
}

Database::Database (std::string configFilename) {

}

bool Database::connect () {
    // Format a MySQL object
    mConnection = mysql_init (NULL);

    // Establish a MySQL connection
    std::cout << "Connecting to " << mDBInfo.hostname << std::endl
        << "Database name: " << mDBInfo.dbName << std::endl
        << "Username: " << mDBInfo.username << std::endl;

    std::cout << "Please enter Your password: ";

    // Obtaining password
    std::string tempPassword = "";
    char c = ' ';
    while (c != 13) {
        c = _getch ();
        if (c != 13)
            tempPassword += c;

        std::cout << "*";
    }

    // Connection.
    std::cout << "\nConnecting...";
    if (!mysql_real_connect (
        mConnection, mDBInfo.hostname.c_str (), mDBInfo.username.c_str (),
        tempPassword.c_str (), mDBInfo.dbName.c_str (),
        mDBInfo.portNumber, NULL, mDBInfo.options)) {

        // Failure
        std::cerr << "failed!\n" << mysql_error (mConnection) << std::endl;
        return false;
    }

    // Success
    std::cout << "connected!\n\n";
    return true;
}

void Database::scanAll () {
    // Get info about tables
    std::cout << "Getting table names...";
    mResult = mysql_list_tables (mConnection, NULL);
    fetchQuery ();
    mysql_free_result (mResult);

    for (auto & name : mFetchedRows) {
        this->mTables.push_back (Table (name));
    }
    std::cout << " done.\n\n";


    // Get columns from each table
    for (auto & table : mTables) {
        std::cout << "Getting columns of '" << table.getName () << "'...";
        std::string qGetTableCols = "SELECT column_name FROM information_schema.columns WHERE table_schema = '" + mDBInfo.dbName + "' AND table_name = '" + table.getName () + "'";
        if (executeQuery (qGetTableCols)) {

            unsigned int tableWidth = 1;
            for (auto & col : mFetchedRows) {
                tableWidth += col.size () + 3;
                table.insertColumn (col, col.size ());
            }

            CONSOLE_WIDTH = max (CONSOLE_WIDTH, tableWidth);

            std::cout << " done.\n";
        }
        else
            std::cout << " failed!\n";
    }

    std::cout << "\n";
    // Scan through all record to obtain column widths
    for (auto & table : mTables) {
        std::cout << "Getting width of '" << table.getName () << "'...";
        std::string qGetContent = "SELECT * FROM `" + table.getName () + "`";
        if (executeQuery (qGetContent)) {

            unsigned int index = 0;
            for (auto & record : mFetchedRows) {
                auto column = table.getColumn (index % mFetchedColNumber);
                column.second = max ((unsigned) column.second, record.size());

                table.setColumn (column, index % mFetchedColNumber);
                ++index;
            }
            std::cout << " done.\n";
        }
        else
            std::cout << " failed!\n";
    }

    std::cout << "\nDatabase schema scanned. Press Return to continue...";
    std::cin.get ();
}

bool Database::executeQuery (std::string query, bool verbose) {
    // Try to execute query
    if (verbose)
        std::cout << "Executing query:  " << query << std::endl;
    if (mysql_query (mConnection, query.c_str ())) {
        std::cerr << mysql_error (mConnection) << std::endl;
        return false;
    }

    // Obtain result
    mResult = mysql_use_result (mConnection);
    fetchQuery ();

    return true;
}

void Database::fetchQuery () {
    // Erase all previously saved results
    mFetchedRows.clear ();

    // Save all rows to vector
    while ((mRow = mysql_fetch_row (mResult)) != NULL) {
        mFetchedColNumber = mysql_num_fields (mResult);
        unsigned long * colLengths = mysql_fetch_lengths (mResult);

        for (unsigned int i = 0; i < mFetchedColNumber; ++i) {
            mFetchedRows.push_back (std::string (mRow[i]));
        }
    }
}

void Database::printAll (bool ifPrintContent) {
    // Print all tables, columns and oprionally content
    for (auto & table : mTables) {
        std::string qGetContent = "SELECT * FROM `" + table.getName () + "`";
        
        std::cout << std::setw (Database::CONSOLE_WIDTH) << std::setfill ('=') << "" << std::endl;
        std::cout << std::setw (Database::CONSOLE_WIDTH / 2 - table.getName ().size () / 2) << std::setfill (' ') << "" << table.getName () << std::endl;
        std::cout << std::setw (Database::CONSOLE_WIDTH) << std::setfill ('=') << "" << "\n";
        
        std::cout << std::setfill (' ');
        std::cout << "|";
        for (unsigned int i = 0; i < table.getColumnsNumber (); ++i) {
            std::cout << " " << std::left << std::setw (table.getColumn (i).second) << table.getColumn (i).first << " |";
        }
        std::cout << "\n";

        std::cout << std::setw (Database::CONSOLE_WIDTH) << std::setfill ('-') << "";

        std::cout << std::setfill (' ');
        unsigned int index = 0;
        if (executeQuery (qGetContent)) {
            for (auto & record : mFetchedRows) {
                if (index % mFetchedColNumber == 0)
                    std::cout << "\n|";

                std::cout << " " << std::left << std::setw (table.getColumn (index % mFetchedColNumber).second) << record << " |";
                ++index;                
            }
        }
        std::cout << "\n\n\n";
    }

}