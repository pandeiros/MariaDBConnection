#pragma once
#include <string>
#include "../Column.h"
#include "../Utilities.h"

class TextColumn : public Column {
public:
    TextColumn ();
    ~TextColumn ();

    TextColumn (const bool isPrimaryKey, const bool isNullable, const std::string name,
                const std::string defaultValue, const std::string tableName,
                const unsigned int width, const unsigned int limit,
                const Column::Type type, Column * FK);

    unsigned int getLimit ();

    virtual std::string autoPK (std::string PK);
    virtual std::string generateData (const unsigned int recordIndex);

private:
    unsigned int mLimit;
};

