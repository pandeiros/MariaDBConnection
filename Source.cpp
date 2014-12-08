/*
* Example to connect to MariaDB(MySQL)
*/
#include <iostream>
#include "include/mysql.h"
#include <string>
#include <sstream>

using namespace std;

/*
* [CLASS] Process
*/
class Proc {
    long RECORD_COUNT = 50;
    const char* MY_HOSTNAME;
    const char* MY_DATABASE;
    const char* MY_USERNAME;
    const char* MY_PASSWORD;
    const char* MY_SOCKET;
    enum {
        MY_PORT_NO = 6969,
        MY_OPT = 0
    };
    MYSQL     *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

public:
    Proc ();           // Constructor
    bool execMain ();  // Main Process

    bool execQuery (string query) {
        // Execute a sql statement
        if (mysql_query (conn, query.c_str ())) {
            cerr << mysql_error (conn) << endl;
            return false;
        }
        return true;
    }

    char ** fetchQuery () {
        return mysql_fetch_row (res);
    }

    void insertRandomData (string table, long recordCount) {
        string countQuery = "SELECT Count(*) FROM information_schema.columns WHERE table_name = '" + table + "'";
        string query = "INSERT INTO `" + table + "` (name, location, website, email) VALUES ";
        int count;

        // Execute a sql statement
        if (!execQuery (countQuery))
            return;

        // Get a result set
        res = mysql_use_result (conn);
        while ((row = fetchQuery ()) != NULL)
            count = atoi (row[0]);

        string randomSet = "";
        for (int i = 1; i <= recordCount; ++i) {
            stringstream ss;
            ss << i;
            string s = ss.str ();;
            randomSet = "('Developer" + s;
            randomSet += "', 'a', 'b', 'c')";


            if (!execQuery (query + randomSet))
                return;

            // Get a result set
            //res = mysql_use_result (conn);
        }
    }
};

/*
* Proc - Constructor
*/
Proc::Proc () {
    // Initialize constants
    MY_HOSTNAME = "193.238.183.9";
    MY_DATABASE = "Steam";
    MY_USERNAME = "root";
    MY_PASSWORD = "pikejchuj";
    MY_SOCKET = NULL;

}

/*
* Main Process
*/
bool Proc::execMain () {
    try {
        // Format a MySQL object
        conn = mysql_init (NULL);

        // Establish a MySQL connection
        cout << "Connecting.....";
        if (!mysql_real_connect (
            conn,
            MY_HOSTNAME, MY_USERNAME,
            MY_PASSWORD, MY_DATABASE,
            MY_PORT_NO, MY_SOCKET, MY_OPT)) {
            cerr << mysql_error (conn) << endl;
            return false;
        }

        cout << "connected!\n";

        ///////////////////////////////////////////////

        string deleteQuery = "DELETE FROM Developers";
        string countQuery = "SELECT Count(*) FROM information_schema.columns WHERE table_name = 'Developers'";
        string selectQuery = "SELECT * FROM Developers";
        int count;

        // Execute a sql statement
        if (!execQuery (countQuery))
            return false;

        // Get a result set
        res = mysql_use_result (conn);
        cout << "Query: " << countQuery << endl;
        while ((row = fetchQuery ()) != NULL)
            count = atoi (row[0]);
        cout << "Columns: " << count << endl;

        cout << "Press Return";
        cin.get ();

        ///////////////////////////////////////////////

        cout << "Inserting " << Proc::RECORD_COUNT << " random records.......";
        insertRandomData ("Developers", Proc::RECORD_COUNT);
        cout << "done!" << endl;
      
        cout << "Press Return";
        cin.get ();

        ///////////////////////////////////////////////

        cout << "Query: " << selectQuery << endl;

        if (!execQuery (selectQuery))
            return false;

        // Get a result set
        res = mysql_use_result (conn);
        while ((row = fetchQuery ()) != NULL) {
            for (int i = 0; i < count; ++i)
                cout << row[i] << " ";
            cout << endl;
        }

        cout << "Press Return";
        cin.get ();

        ///////////////////////////////////////////////
        
        cout << "Deleting all records!" << endl;
        if (!execQuery (deleteQuery))
            return false;

        res = mysql_use_result (conn);

        ///////////////////////////////////////////////

        // Release memories
        mysql_free_result (res);

        // Close a MySQL connection
        mysql_close (conn);
    }
    catch (char *e) {
        cerr << "[EXCEPTION] " << e << endl;
        return false;
    }
    return true;
}

/*
* Execution
*/
int main () {
    try {
        Proc objMain;
        bool bRet = objMain.execMain ();
        if (!bRet) cout << "ERROR!" << endl;
    }
    catch (char *e) {
        cerr << "[EXCEPTION] " << e << endl;
        return 1;
    }

    cout << "Everything's done. Press Return.";
    cin.get ();
    return 0;
}