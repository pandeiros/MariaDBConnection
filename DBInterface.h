/**
    Organizes input parameters, filenames and displays useful information.
    */
#ifndef DBINTERFACE
#define DBINTERFACE

#include <iostream>
#include <string>
#include <map>
#include "Database.h"

class DBInterface {
public:
    // Cons. & Des.
    DBInterface () {
    };
    ~DBInterface () {
    };

    // Constructor with input parameters
    DBInterface (int argc, char* argv[]);

    // Configures maps with proper parameters
    void configureParameters ();

    // Configures whole database, based on file (or console input)
    bool configureDatabase ();

    // Executes all input commands, base on file (or console input)
    bool executePendingOperations ();

    // Prints all input parameters
    void printParams ();

    // Prints some helpful information to the user before terminating.
    void printUsage ();
    void printHelp ();

    // Closes all connections and files and exits.
    void terminate ();

private:
    Database mDatabase;

    int mArgCount = 0;

    std::string mUsageMessage = "Usage msg.";    // TEMP
    std::string mHelpMessage = "Help msg.";

    // Param name => (if exists; associated param)
    std::map <std::string, std::pair<bool, std::string>> mapParamBools;

    // Param name => (filename; associated param)
    std::map <std::string, std::pair<std::string, std::string>> mapParamStrings;
};

#endif