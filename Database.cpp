#include <conio.h>
#include "Database.h"

Database::Widths Database::WIDTHS;

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

bool Database::disconnect () {
    // Release memories
    mysql_free_result (mResult);

    // Close a MySQL connection
    mysql_close (mConnection);

    return true;
}

bool Database::scanAll () {
    

    if (!this->getTables ())
        return false;

    if (!this->getColumns ())
        return false;

    if (!this->getConstraints ())
        return false;

    Database::WIDTHS.MAX = max (Database::WIDTHS.MAX,
                                Database::WIDTHS.NAME * 2 + Database::WIDTHS.TYPE + Database::WIDTHS.NULLABLE + Database::WIDTHS.KEY +
                                Database::WIDTHS.DEFAULT + Database::WIDTHS.EXTRA + 7 * 3 - 1);

    std::cout << "\nDatabase schema scanned. Press Return to continue...";
    std::cin.get ();

    return true;
}

Table * Database::findByName (const std::string name) {
    for (Table & table : mTables) {
        if (table.getName () == name)
            return &table;
    }

    return nullptr;
}

bool Database::executeQuery (std::string query, const unsigned int flags) {
    // Try to execute query
    if (flags & Database::VERBOSE_OUTPUT)
        std::cout << "Executing query:  " << query << std::endl;

    if (mysql_query (mConnection, query.c_str ())) {
        std::cerr << mysql_error (mConnection) << std::endl;
        return false;
    }

    if (!(flags & Database::NO_FETCH)) {
        // Obtain result
        mResult = mysql_use_result (mConnection);
        fetchQuery ();
    }

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
            if (mRow[i] != NULL)
                mFetchedRows.push_back (std::string (mRow[i]));
            else
                mFetchedRows.push_back (std::string (""));
        }
    }
}

void Database::printQueryResults () {
    unsigned int index = 0;
    for (auto & result : mFetchedRows) {
        std::cout << result << " ";

        ++index;
        if (index % mFetchedColNumber == 0)
            std::cout << std::endl;
    }
}

void Database::printAll (const unsigned int flags) {
    // Print all tables, columns and oprionally content
    for (auto & table : mTables) {
        std::string qGetContent = "SELECT * FROM `" + table.getName () + "`";

        // Print table name
        std::cout << std::setw (Database::WIDTHS.MAX) << std::setfill ('=') << "" << std::endl;
        std::cout << std::setw (Database::WIDTHS.MAX / 2 - table.getName ().size () / 2) << std::setfill (' ') << "" << table.getName () << std::endl;
        std::cout << std::setw (Database::WIDTHS.MAX) << std::setfill ('=') << "" << "\n";

        // Print columns' info
        std::cout << std::setfill (' ');
        if (flags & Database::PRINT_COLUMN_INFO) {
            std::cout << std::setw (Database::WIDTHS.NAME) << "Name" << " | ";
            std::cout << std::setw (Database::WIDTHS.TYPE) << "Type" << " | ";
            std::cout << std::setw (Database::WIDTHS.NULLABLE) << "Null" << " | ";
            std::cout << std::setw (Database::WIDTHS.KEY) << "Key" << " | ";
            std::cout << std::setw (Database::WIDTHS.DEFAULT) << "Default" << " | ";
            std::cout << std::setw (Database::WIDTHS.EXTRA) << "Extra" << " | ";
            std::cout << std::setw (Database::WIDTHS.NAME) << "FK." << " |\n";

            std::cout << std::setw (Database::WIDTHS.MAX) << std::setfill ('-') << "";
            std::cout << "\n" << std::setfill (' ');

            for (unsigned int i = 0; i < table.getColumnsCount (); ++i) {
                Column * column = table.getColumn (i);
                std::cout << std::setw (Database::WIDTHS.NAME) << column->getName () << " | ";

                if (column->getType () & (Column::VARCHAR | Column::INT))
                    std::cout << std::setw (Database::WIDTHS.TYPE) << column->getStringType () + "(" +
                    Utilities::convertToString<unsigned int> (column->getLimit ()) + ")" +
                    (column->getIsUnsigned () ? " unsigned" : "");
                else if (column->getType () & Column::FLOAT)
                    std::cout << std::setw (Database::WIDTHS.TYPE) << column->getStringType () + "(" +
                    Utilities::convertToString<unsigned int> (column->getLimit ()) + "," +
                    Utilities::convertToString<unsigned int> (column->getPrecision ()) + ")";
                else
                    std::cout << std::setw (Database::WIDTHS.TYPE) << column->getStringType ();

                std::cout << " | " << std::setw (Database::WIDTHS.NULLABLE) << (column->getIsNullable () ? "YES" : "NO");
                std::cout << " | " << std::setw (Database::WIDTHS.KEY) << (column->getIsPrimaryKey () ? "PRI" : "");
                std::cout << " | " << std::setw (Database::WIDTHS.DEFAULT) << (column->getDefault () == "" ? "-" : "");
                std::cout << " | " << std::setw (Database::WIDTHS.EXTRA) << (column->getIsAutoIncrement () ? "auto_increment" : "");

                std::string refColumnName = " - ";
                if (column->getForeignKey () != nullptr)
                    refColumnName = column->getForeignKey ()->getName ();
                std::cout << " | " << std::setw (Database::WIDTHS.NAME) << refColumnName << " |";

                std::cout << "\n";
            }
        }

        std::cout << std::setw (Database::WIDTHS.MAX) << std::setfill (' ') << "" << "\n";

        // Print column names
        for (unsigned int i = 0; i < table.getColumnsCount (); ++i) {
            std::cout << "| " << std::left << std::setw (table.getColumn (i)->getWidth ()) << table.getColumn (i)->getName () << " ";
        }
        std::cout << "|\n";

        std::cout << std::setw (Database::WIDTHS.MAX) << std::setfill ('-') << "";
        std::cout << std::setfill (' ');

        // Print content
        if (flags & Database::PRINT_CONTENT) {
            unsigned int index = 0;
            if (executeQuery (qGetContent)) {
                for (auto & record : mFetchedRows) {
                    if (index % mFetchedColNumber == 0)
                        std::cout << "\n|";

                    std::cout << " " << std::left << std::setw (table.getColumn (index % mFetchedColNumber)->getWidth ()) << record << " |";
                    ++index;
                }
            }
        }
        std::cout << "\n\n\n";
    }

}

bool Database::getTables () {
    // Get info about tables
    std::cout << "Getting table names...";
    mResult = mysql_list_tables (mConnection, NULL);
    fetchQuery ();
    mysql_free_result (mResult);

    for (auto & name : mFetchedRows) {
        this->mTables.push_back (Table (name));
    }
    std::cout << " done.\n\n";

    return true;
}

bool Database::getColumns () {
    // Scan through tables to obtain columns with their types and widths
    try {
        for (auto & table : mTables) {
            std::cout << "Getting information about '" << table.getName () << "'...";
            std::string qGetColumns = "SHOW COLUMNS FROM `" + table.getName () + "`";
            if (executeQuery (qGetColumns)) {

                for (unsigned int i = 0; i < mFetchedRows.size () / mFetchedColNumber; ++i) {
                    std::string name = mFetchedRows[i * mFetchedColNumber];
                    std::string type = mFetchedRows[i * mFetchedColNumber + 1];
                    std::string nullable = mFetchedRows[i * mFetchedColNumber + 2];
                    std::string key = mFetchedRows[i * mFetchedColNumber + 3];
                    std::string defaultValue = mFetchedRows[i * mFetchedColNumber + 4];
                    std::string extra = mFetchedRows[i * mFetchedColNumber + 5];

                    table.insertColumn (Column::parseRawData (name, type, nullable, key, defaultValue, extra));
                    Database::WIDTHS.NAME = max (Database::WIDTHS.NAME, name.size ());
                }
            }

            std::string qGetContent = "SELECT * FROM `" + table.getName () + "`";
            if (executeQuery (qGetContent)) {

                unsigned int index = 0;
                for (auto & record : mFetchedRows) {
                    Column * column = table.getColumn (index % mFetchedColNumber);
                    column->setWidth (max ((unsigned)column->getWidth (), record.size ()));

                    ++index;
                }
                std::cout << " done.\n";
            }

            Database::WIDTHS.MAX = max (Database::WIDTHS.MAX, 1 + table.getTableWidth () + 3 * table.getColumnsCount ());
        }
    }
    catch (...) {
        std::cout << " failed.\n";
        return false;
    }

    return true;
}

bool Database::getConstraints () {
    for (auto & table : mTables) {
        std::string qUseDB = "USE information_schema; ";
        if (!executeQuery (qUseDB, Database::NO_FETCH))
            return false; 

        std::string qForeignKeyQuery = "SELECT TABLE_NAME,COLUMN_NAME,CONSTRAINT_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME ";
        qForeignKeyQuery += "FROM KEY_COLUMN_USAGE ";
        qForeignKeyQuery += "WHERE TABLE_SCHEMA = '" + mDBInfo.dbName + "' and TABLE_NAME = '" + table.getName () + "' ";
        qForeignKeyQuery += "AND referenced_column_name is not NULL; ";

        if (executeQuery (qForeignKeyQuery)) {
            for (unsigned int i = 0; i < mFetchedRows.size () / mFetchedColNumber; ++i) {

                // Get Column
                Column * column = table.findByName (mFetchedRows[i * mFetchedColNumber + 1]);
                if (column != nullptr) {

                    // Get referenced Table
                    Table * refTable = this->findByName (mFetchedRows[i * mFetchedColNumber + 3]);
                    if (refTable != nullptr) {

                        // Get referenced Column
                        Column * refColumn = refTable->findByName (mFetchedRows[i * mFetchedColNumber + 4]);
                        if (refColumn != nullptr) {

                            // Assign foreign key
                            column->setForeignKey (refColumn);
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        else
            return false;
    }

    std::string qUseDB = "USE " + mDBInfo.dbName + ";";
    if (!executeQuery (qUseDB, Database::NO_FETCH))
        return false;

    return true;
}