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

std::string TextColumn::autoPK (std::string PK) {
    // TODO Create new PK based strictly on type of column
    if (PK == "")
        return "A";
    else {
        for (int i = PK.size () - 1; i >= 0; --i) {
            if (PK[i] == 'Z') {
                PK[i] = 'A';
                if (i == 0) {
                   PK += 'A';           
                }
                else {
                    PK[i - 1] = (char)((int)(PK[i - 1]) + 1);
                }
            }
            else {
               PK[i] = (char)((int)(PK[i]) + 1);
               break;
            }
        }
    }

    return PK;
}

std::string TextColumn::generateData (const unsigned int recordIndex) {
    std::string result;
    int range = 1 + rand () % mLimit;
    for (unsigned int i = 0; i < range; ++i) {
        result += (char)(65 + rand () % (90 - 65 + 1));
    }

    return result;
}