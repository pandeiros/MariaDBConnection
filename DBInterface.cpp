#include "DBInterface.h"

DBInterface::DBInterface (int argc, char* argv[]) : mArgCount (argc) {
    configureParameters ();

    // Parse parameters
    for (int i = 1; i < mArgCount; ++i) {

        std::string parameter (argv[i]);

        if (mapParamBools.find (parameter) != mapParamBools.end () && mapParamBools[parameter].first != true) {
            mapParamBools[parameter].first = mapParamBools[mapParamBools[parameter].second].first = true;
        }
        else if (mapParamStrings.find (parameter) != mapParamStrings.end () &&
                 i + 1 < mArgCount &&
                 mapParamStrings[parameter].first == "") {
            std::string filename (argv[i + 1]);
            mapParamStrings[parameter].first = mapParamStrings[mapParamStrings[parameter].second].first = filename;
            i++;
            continue;
        }
        else {
            mapParamBools["-h"].first = true;
            break;
        }
    }
}

void DBInterface::configureParameters () {
    // TODO Consider loading these from file.
    mapParamBools["--usage"] = std::make_pair (false, "-u");
    mapParamBools["-u"] = std::make_pair (false, "--usage");
    mapParamBools["--help"] = std::make_pair (false, "-h");
    mapParamBools["-h"] = std::make_pair (false, "--help");

    mapParamStrings["--file"] = std::make_pair ("", "-f");
    mapParamStrings["-f"] = std::make_pair ("", "--file");

    //mapParamStrings["--output"] = std::make_pair ("", "-ko");
    //mapParamStrings["-o"] = std::make_pair ("", "--output");
    //mapParamStrings["--stats"] = std::make_pair ("", "-s");
    //mapParamStrings["-s"] = std::make_pair ("", "--stats");
}

bool DBInterface::configureDatabase () {
    // Default specs
    //Database database (dbSpecs);

    if (!mDatabase.connect ()) {
        std::cout << "\nSorry, connection failed. Try again.\n\n";
        return false;
    }

    try {
        if (mDatabase.scanAll ());
           mDatabase.printAll (Database::PRINT_COLUMN_INFO);// (Database::PRINT_CONTENT | Database::PRINT_COLUMN_INFO);
    }
    catch (char *e) {
        std::cerr << "[EXCEPTION] " << e << std::endl;
        return false;
    }

    return true;
}

bool DBInterface::executePendingOperations () {
    /*for (Table * table : *mDatabase.getTableVector()) {
        if (!mDatabase.insertRandomData (table, 1))
            return false;
    }*/
  
    return true;
}

void DBInterface::printParams () {
    // Print usage and help params
    for (auto &x : mapParamBools) {
        if (x.second.first == true)
            std::cout << x.first << "\n";
    }

    // Print filenames params
    for (auto &x : mapParamStrings) {
        if (x.second.first != "")
            std::cout << x.first << " ==> " << x.second.first << "\n";
    }
}

void DBInterface::printHelp () {
    std::cout << mHelpMessage << "\n";
}

void DBInterface::printUsage () {
    std::cout << mUsageMessage << "\n";
}

void DBInterface::terminate () {
    std::cout << "Everything's done. Press Return.";
    std::cin.get ();

    mDatabase.disconnect ();
}