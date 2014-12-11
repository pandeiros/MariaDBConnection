#pragma once
#include <string>
#include <vector>

class Table {
public:
    // Cons. & Des.
    Table ();
    ~Table ();

    // Constructor with table name
    Table (std::string name);

    void insertColumn (std::string name, int length);

    // Getters
    std::string getName ();
    std::pair <std::string, int> getColumn (unsigned int index);
    unsigned int getColumnsNumber ();

private:
    // Table name
    std::string mName;

    // Vector of columns' names and legths
    std::vector <std::pair <std::string, int>> mColumns;
};

