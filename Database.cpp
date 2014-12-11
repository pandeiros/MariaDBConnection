#include <iostream>
#include <conio.h>
#include "Database.h"

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
    std::string tempPassword;
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
            tempPassword.c_str(), mDBInfo.dbName.c_str (), 
            mDBInfo.portNumber, NULL, mDBInfo.options)) {
        
        // Failure
        std::cerr << "failed!\n" << mysql_error (mConnection) << std::endl;
        return false;
    }

    // Success
    std::cout << "connected!\n";
    return true;
}

void Database::scanAll () {

}

void Database::executeQuery (std::string query) {

}