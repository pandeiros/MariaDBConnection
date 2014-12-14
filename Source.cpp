#include <iostream>
#include <string>
#include <sstream>
#include "include/mysql.h"
#include "DBInterface.h"

int main (int argc, char *argv[]) {
    // Create interface class
    DBInterface mInterface (argc, argv);
   
    // Configure DB
    if (!mInterface.configureDatabase ()) {
        std::cout << "Configuring Database failed...\n";
        exit (EXIT_FAILURE);
    }

    // Parse commands
    if (!mInterface.executePendingOperations ()) {
        std::cout << "Executing commands failes...\n";
        exit (EXIT_FAILURE);
    }

    mInterface.terminate ();

    return 0;
}