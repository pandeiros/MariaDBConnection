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

    void insertColumn (const Column column);

    // Getters
    std::string getName ();
    Column * getColumn (const unsigned int index);
    unsigned int getColumnsCount ();
    unsigned int getWidth ();

    // Setters
    void setColumn (Column newColumn, const unsigned int index);

private:
    // Table name
    std::string mName;

    // Vector of table's columns
    std::vector <Column> mColumns;
};

