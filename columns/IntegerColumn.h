#pragma once
#include <map>
#include <string>
#include "../Column.h"
#include "../Utilities.h"

class IntegerColumn : public Column {
public:
    IntegerColumn ();
    ~IntegerColumn ();

    IntegerColumn (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                   const bool isUnsigned, const std::string name, const std::string defaultValue, 
                   const std::string tableName, const unsigned int width, const unsigned int limit,
                   const Column::Type type, Column * FK);

    static std::map <Column::Type, std::pair<long, long> > mapRanges;

    virtual unsigned int getLimit ();
    virtual bool getIsUnsigned ();

    virtual std::string autoPK (std::string PK);

private:
    bool isUnsigned;
    unsigned int mLimit;
};

