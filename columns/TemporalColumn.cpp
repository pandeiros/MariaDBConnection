#include "TemporalColumn.h"

std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > TemporalColumn::dateRanges = TemporalColumn::initializeDateRanges ();
std::map <Column::Type, std::pair< std::tuple<int, int, int>, std::tuple<int, int, int> > > TemporalColumn::timeRanges = TemporalColumn::initializeTimeRanges ();

TemporalColumn::TemporalColumn () {
}

TemporalColumn::~TemporalColumn () {
}

TemporalColumn::TemporalColumn (const bool isPrimaryKey, const bool isNullable,
                                const std::string name, const std::string defaultValue, const std::string tableName,
                                const unsigned int width, const Column::Type type, Column * FK) {
    this->isPrimaryKey = isPrimaryKey;
    this->mName = name;
    this->mDefault = defaultValue;
    this->mTableName = tableName;
    this->mWidth = width;
    this->mType = type;
    this->pForeignKey = FK;
    this->isNullable = isNullable;
    this->isAutoIncrement = isAutoIncrement;
}

std::string TemporalColumn::generateData (const unsigned int recordIndex) {
    std::string result = "";

    int year, month, day, hour, min, sec;
    bool date = false, time = false;

    if (dateRanges.find (this->mType) != dateRanges.end ())
        date = true;

    if (timeRanges.find (this->mType) != timeRanges.end ())
        time = true;

    if (date) {
        year = std::get<0> (dateRanges[this->mType].first) + rand () % (std::get<0> (dateRanges[this->mType].second) - std::get<0> (dateRanges[this->mType].first));
        month = std::get<1> (dateRanges[this->mType].first) + rand () % (std::get<1> (dateRanges[this->mType].second) - std::get<1> (dateRanges[this->mType].first));
        day = std::get<2> (dateRanges[this->mType].first) + rand () % (std::get<2> (dateRanges[this->mType].second) - std::get<2> (dateRanges[this->mType].first));
        result += Utilities::convertToString<int> (year) + "-" + Utilities::convertToString<int> (month)+ "-" + Utilities::convertToString<int> (day);

    }

    return result;
}