#pragma once
#include <string>
#include <vector>

class Table {
public:
    // Cons. & Des.
    Table ();
    ~Table ();

private:
    // Table name
    std::string mName;

    // Vector of columns' names and legths
    std::vector <std::pair <std::string, int>> mColumns;
};

