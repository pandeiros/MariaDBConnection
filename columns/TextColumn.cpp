#include "TextColumn.h"

TextColumn::TextColumn () {
}

TextColumn::~TextColumn () {
}

TextColumn::TextColumn (const bool isPrimaryKey, const bool isNullable, const std::string name,
                        const std::string defaultValue, const std::string tableName,
                        const unsigned int width, const unsigned int limit,
                        const Column::Type type, Column * FK) :
                        mLimit (limit) {
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

unsigned int TextColumn::getLimit () {
    return mLimit;
}