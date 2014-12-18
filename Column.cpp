#include <sstream>
#include "Column.h"
#include "Utilities.h"
#include "columns/IntegerColumn.h"
#include "columns/RealColumn.h"
#include "columns/TemporalColumn.h"
#include "columns/TextColumn.h"

std::map<Column::Type, std::string> Column::mapTypeStrings = Column::initializeMap ();

Column::Column () {
}

Column::~Column () {
}

Column::Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                const std::string name, const std::string defaultValue, const std::string tableName,
                const unsigned int width, const Type type, Column * FK) :
                isPrimaryKey (isPrimaryKey), isNullable (isNullable), isAutoIncrement (isAutoIncrement),
                mName (name), mDefault (defaultValue), mTableName (tableName), mWidth (width),
                mType (type), pForeignKey (FK) {
}

std::string Column::autoPK (std::string PK) {
    return PK;
}

std::string Column::generateData (const unsigned int recordIndex) {
    return "";
}

std::string Column::getName () {
    return mName;
}

std::string Column::getDefault () {
    return mDefault;
}

std::string Column::getStringType () {
    return mapTypeStrings[this->mType];
}

std::string Column::getTableName () {
    return mTableName;
}

Column::Type Column::getType () {
    return mType;
}

unsigned int Column::getWidth () {
    return mWidth;
}

bool Column::getIsPrimaryKey () {
    return isPrimaryKey;
}

bool Column::getIsNullable () {
    return isNullable;
}

bool Column::getIsAutoIncrement () {
    return isAutoIncrement;
}

Column * Column::getForeignKey () {
    return pForeignKey;
}

std::vector <std::string> * Column::getForeignKeyFetched () {
    return &mForeignKeyFetched;
}

unsigned int Column::getLimit () {
    return 0;
}

unsigned int Column::getPrecision () {
    return 0;
}

bool Column::getIsUnsigned () {
    return false;
}

void Column::setWidth (const unsigned int width) {
    mWidth = width;
}

void Column::setForeignKey (Column * const foreignKey) {
    pForeignKey = foreignKey;
}

Column * Column::parseRawData (std::string tableName, std::string name, std::string type, std::string nullable,
                               std::string key, std::string defaultValue, std::string extra) {

    std::string typeName = "", typeParams = "";
    if (type.find ("(") != std::string::npos) {
        typeName = type.substr (0, type.find ("("));
        typeParams = type.substr (typeName.size () + 1, type.find (")") - typeName.size () - 1);
    }
    else
        typeName = type;

    bool isPK = (key == "PRI");
    bool isNull = (nullable == "YES");
    bool isAI = (extra.find ("auto_increment") != std::string::npos);
    bool isUS = (type.find ("unsigned") != std::string::npos);

    Type colType = Column::UNKNOWN;
    for (std::map<Column::Type, std::string>::const_iterator it = mapTypeStrings.begin (); it != mapTypeStrings.end (); ++it) {
        if (it->second == typeName) {
            colType = it->first;
            break;
        }
    }

    switch (colType) {
        case BIT: case TINYINT: case  SMALLINT: case MEDIUMINT: case INT: case BIGINT:
            return (Column *) new IntegerColumn (isPK, isNull, isAI, isUS,
                                                 name, defaultValue, tableName, name.size (),
                                                 Utilities::convertFromString<unsigned int> (typeParams),
                                                 colType, nullptr);
        case CHAR: case VARCHAR: case TINYTEXT: case TEXT: case MEDIUMTEXT: case LONGTEXT:
            return (Column *) new TextColumn (isPK, isNull,
                                              name, defaultValue, tableName, name.size (),
                                              Utilities::convertFromString<unsigned int> (typeParams),
                                              colType, nullptr);
        case DATE: case TIME: case YEAR: case DATETIME: case TIMESTAMP:
            return (Column *) new TemporalColumn (isPK, isNull,
                                              name, defaultValue, tableName, name.size (),                                             
                                              colType, nullptr);
        default:
            return nullptr;
    }
}


