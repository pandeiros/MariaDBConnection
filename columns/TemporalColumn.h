#pragma once
#include <string>
#include "../Column.h"

class TemporalColumn : public Column {
public:
    TemporalColumn ();
    ~TemporalColumn ();

    TemporalColumn (const bool isPrimaryKey, const bool isNullable,
                    const std::string name, const std::string defaultValue, const std::string tableName,
                    const unsigned int width, const Column::Type type, Column * FK);
};

