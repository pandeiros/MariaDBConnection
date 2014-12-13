#pragma once
#include <string>
#include <vector>
#include "Column.h"

class Table {
public:
    // Cons. & Des.
    Table ();
    ~Table ();

    // Constructor with table name
    Table (std::string name);

    // Creates new Column
    void insertColumn (const Column column);

    // Return pointer to Column which name matches the argument
    Column * findByName (const std::string name);

    // Getters
    std::string getName ();
    Column * getColumn (const unsigned int index);
    unsigned int getColumnsCount ();
    unsigned int getTableWidth ();
    unsigned int getMaxColumnWidth ();

    // Setters
    void setColumn (Column newColumn, const unsigned int index);

private:
    // Table name
    std::string mName;

    // Vector of table's columns
    std::vector <Column> mColumns;
};

