#pragma once
#include <map>
#include <string>
#include "../Column.h"

class IntegerColumn : public Column {
public:
    IntegerColumn ();
    ~IntegerColumn ();

    IntegerColumn (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                   const bool isUnsigned, const std::string name, const std::string defaultValue, const std::string tableName,
                   const unsigned int width, const unsigned int limit,
                   const Type type, const Column * FK);

    static std::map <Column::Type, std::pair<long, long> > mapRanges;

private:
    bool isUnsigned;
    unsigned int mLimit;
};

