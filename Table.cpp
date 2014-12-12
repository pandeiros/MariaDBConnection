#include "Table.h"

Table::Table () {
}

Table::~Table () {
}

Table::Table (std::string name) {
    mName = name;
}

void Table::insertColumn (const Column column) {
    mColumns.push_back (column);
}

std::string Table::getName () {
    return mName;
}

Column * Table::getColumn (const unsigned int index) {
    if (index >= 0 && index < mColumns.size ())
        return &mColumns[index];
    else
        return nullptr;
}

unsigned int Table::getColumnsCount () {
    return mColumns.size ();
}

unsigned int Table::getWidth () {
    unsigned int width = 0;
    for (auto & column : mColumns)
        width += column.getWidth ();

    return width;
}

void Table::setColumn (const Column column, const unsigned int index) {
    mColumns[index] = column;
}