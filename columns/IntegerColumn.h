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

    virtual unsigned int getLimit ();
    virtual bool getIsUnsigned ();

    virtual std::string autoPK (std::string PK);
    virtual std::string generateData (const unsigned int recordIndex);

private:
    static std::map <Column::Type, std::pair<long long, long long> > mapRanges;

    bool isUnsigned;
    unsigned int mLimit;

    static std::map<Column::Type, std::pair<signed long long,signed long long> > initializeMapRanges () {
        std::map<Column::Type, std::pair<signed long long,signed long long> > map;
        map[Column::BIT] = std::make_pair (0LL, 1LL);
        map[Column::INT] = std::make_pair (-2147483648LL, 2147483647LL);

        return map;
    }
};

