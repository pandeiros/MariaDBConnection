#pragma once
#include <string>
#include "../Column.h"

class TextColumn : public Column {
public:
    TextColumn ();
    ~TextColumn ();

    TextColumn (const bool isPrimaryKey, const bool isNullable, const std::string name,
                const std::string defaultValue, const std::string tableName,
                const unsigned int width, const unsigned int limit,
                const Column::Type type, Column * FK);

    unsigned int getLimit ();

private:
    unsigned int mLimit;
};

