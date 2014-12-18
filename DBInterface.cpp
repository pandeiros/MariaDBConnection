#include "DBInterface.h"
#include <ctime>
#include <algorithm>
#include <climits>

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
        //mDatabase.printAll (Database::PRINT_CONTENT | Database::PRINT_COLUMN_INFO);
    }
    catch (char *e) {
        std::cerr << "[EXCEPTION] " << e << std::endl;
        return false;
    }

    return true;
}

bool DBInterface::executePendingOperations () {
    // MALESZ
    // Tu mo¿esz sobie zrobiæ inserty dla ró¿nej iloœci rekordów dla ka¿dej tabeli
    std::vector <int> recordLimits = {100, 200};// 1000, 2000, 5000, 10000, 15000};
    int record2 = 0;
    for (auto & records : recordLimits) {
        int blockSize = 10000;

        // Delete data
        mDatabase.truncateAll ();

        // Insert data into all tables
        double sumtime = 0;

        for (Table * table : *mDatabase.getTableVector ()) {
            //if (!mDatabase.insertRandomData (table, 100, 10, Database::VERBOSE_OUTPUT))

            // MALESZ
            if (table->getName () == "Developers")
                record2 = 8000;
            else
                record2 = records;

            clock_t begin = clock ();
            if (record2 < blockSize)
                blockSize = record2;

            if (mDatabase.insertRandomData (table, record2, blockSize)) {
                clock_t end = clock ();
                double elapsed_secs = double (end - begin) / CLOCKS_PER_SEC;
                sumtime += elapsed_secs;
                std::cout << "Time: " << elapsed_secs << " secs.\n";
            }
            else
                return false;

            for (unsigned int iColumn = 0; iColumn < table->getColumnsCount (); ++iColumn)
                table->getColumn (iColumn)->getForeignKeyFetched ()->clear ();
        }

        std::cout << "\nTotal inserting time: " << sumtime << " secs.\n\n";

        // MALESZ
        // Tu sobie zmien query, ktore sie wykona dla kazdej liczby rekordow podanych wy¿ej
        // Query
        std::string query = "SELECT Steam.StoreItems.*, Steam.ItemOS.name AS \"osName\", Steam.StoreItems.genre FROM Steam.StoreItems\
            JOIN Steam.ItemOS\
            ON Steam.ItemOS.storeItemID = Steam.StoreItems.storeItemID\
            JOIN Steam.Genres\
            ON Steam.Genres.name = Steam.StoreItems.genre\
            WHERE Steam.ItemOS.name LIKE \"A\"\
            AND Steam.StoreItems.genre LIKE \"C\"\
            AND Steam.StoreItems.baseGame IS NULL\
            ORDER BY Steam.StoreItems.name";
        clock_t begin = clock ();
        if (mDatabase.executeQuery (query, Database::VERBOSE_OUTPUT)) {
            clock_t end = clock ();
            double elapsed_secs = double (end - begin) / CLOCKS_PER_SEC;
            sumtime += elapsed_secs;
            std::cout << " > Query executing time: " << elapsed_secs << " secs.\n\n\n";
        }

    }
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