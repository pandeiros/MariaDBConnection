#include "include/mysql.h"
#include "Table.h"

Table::Table () {
}

Table::~Table () {
    for (Column * col : mColumns)
        if (col != nullptr)
            delete col;
}

Table::Table (std::string name) {
    mName = name;
}

void Table::insertColumn (Column * column) {
    mColumns.push_back (column);
}

Column * Table::findByName (const std::string name) {
    for (Column * col : mColumns) {
        if (col->getName () == name)
            return col;
    }

    return nullptr;
}

std::string Table::getName () {
    return mName;
}

Column * Table::getColumn (const unsigned int index) {
    if (index >= 0 && index < mColumns.size ())
        return mColumns[index];
    else
        return nullptr;
}

unsigned int Table::getColumnsCount () {
    return mColumns.size ();
}

unsigned int Table::getTableWidth () {
    unsigned int width = 0;
    for (auto & column : mColumns)
        width += column->getWidth ();

    return width;
}

unsigned int Table::getMaxColumnWidth () {
    unsigned int maxWidth = 0;
    for (auto & column : mColumns)
        maxWidth = max (maxWidth, column->getWidth ());

    return maxWidth;
}

void Table::setColumn (Column * column, const unsigned int index) {
    mColumns[index] = column;
}