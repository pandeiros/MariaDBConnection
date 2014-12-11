#include "Table.h"

Table::Table () {
}

Table::~Table () {
}

Table::Table (std::string name) {
    mName = name;
}

void Table::insertColumn (std::string name, int length) {
    mColumns.push_back (std::make_pair (name, length));
}

std::string Table::getName () {
    return mName;
}

std::pair <std::string, int> Table::getColumn (unsigned int index) {
    if (index >= 0 && index < mColumns.size ())
        return mColumns[index];
    else
        return std::make_pair ("UKNOWN_COLUMN", 13);
}

unsigned int Table::getColumnsNumber () {
    return mColumns.size ();
}