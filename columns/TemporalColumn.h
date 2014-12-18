#pragma once
#include <string>
#include "../Column.h"
#include "../Utilities.h"

class TemporalColumn : public Column {
public:
    TemporalColumn ();
    ~TemporalColumn ();

    TemporalColumn (const bool isPrimaryKey, const bool isNullable,
                    const std::string name, const std::string defaultValue, const std::string tableName,
                    const unsigned int width, const Column::Type type, Column * FK);

    virtual std::string generateData (const unsigned int recordIndex);

private:
    static std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > dateRanges;
    static std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > timeRanges;

    static std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > initializeDateRanges () {
        std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > map;
        map[Column::DATE] = std::make_pair (std::make_tuple (1000,01,01), std::make_tuple (9999,12,31));
        return map;
    }

    static std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > initializeTimeRanges () {
        std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > map;

        return map;
    }
};

