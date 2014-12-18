#include "IntegerColumn.h"

std::map<Column::Type, std::pair<long long, long long> > IntegerColumn::mapRanges = IntegerColumn::initializeMapRanges ();

IntegerColumn::IntegerColumn () {
}

IntegerColumn::~IntegerColumn () {
}

IntegerColumn::IntegerColumn (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                              const bool isUnsigned, const std::string name, const std::string defaultValue, const std::string tableName,
                              const unsigned int width, const unsigned int limit,
                              const Column::Type type, Column * FK) :
                              isUnsigned (isUnsigned), mLimit (limit) {
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

unsigned int IntegerColumn::getLimit () {
    return mLimit;
}

bool IntegerColumn::getIsUnsigned () {
    return isUnsigned;
}

std::string IntegerColumn::autoPK (std::string PK) {
    // TODO Create new PK based strictly on type of column
    if (PK == "")
        return "1";
    int intPK = Utilities::convertFromString<int> (PK);
    ++intPK;
    return Utilities::convertToString<int> (intPK);
}

std::string IntegerColumn::generateData (const unsigned int recordIndex) {
    std::string result = "";
    long long number = 0;
    if (isUnsigned) {
        number = 0 + rand () % (mapRanges[this->mType].second * 2 + 1);
    }
    else {
        number = mapRanges[this->mType].first + rand () % (mapRanges[this->mType].second - mapRanges[this->mType].first);
    }

    result = Utilities::convertToString<long long> (number);

    if (mLimit > 0) {
        return result.substr (0, mLimit);
    }
    else
        return result;
}