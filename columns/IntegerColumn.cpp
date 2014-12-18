#include "IntegerColumn.h"

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

std::string IntegerColumn::Column::autoPK (std::string PK) {
    // TODO Create new PK based strictly on type of column
    int intPK = Utilities::convertFromString<int> (PK);
    ++intPK;
    return Utilities::convertToString<int> (intPK);
}