#include <sstream>
#include "Column.h"

std::map<Column::Type, std::string> Column::mapTypeStrings = Column::initializeMap ();

Column::Column () {
}

Column::~Column () {
}

Column::Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                const std::string name, const std::string defaultValue, const std::string tableName,
                const unsigned int width, const Type type, const Column * FK) :
                isPrimaryKey (isPrimaryKey), isNullable (isNullable), isAutoIncrement (isAutoIncrement),
                mName (name), mDefault (defaultValue), mTableName(tableName), mWidth (width),
                mType (type), pForeignKey (const_cast<Column*>(FK)) {
}

std::string Column::getName () {
    return mName;
}

std::string Column::getDefault () {
    return mDefault;
}

std::string Column::getStringType () {
    switch (this->mType) {
        case Column::BIT:
            return "bit";
        case Column::DATE:
            return "date";
        case Column::FLOAT:
            return "float";
        case Column::INT:
            return "int";
        case Column::VARCHAR:
            return "varchar";
        default:
            return "unknown";
    }
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

    Type colType;
    unsigned int limit = 0, precision = 0;
    std::stringstream ss;
    if (typeName == "varchar") {
        colType = Column::VARCHAR;
        ss.str (typeParams);
        ss >> limit;
    }
    else if (typeName == "int") {
        colType = Column::INT;
        ss.str (typeParams);
        ss >> limit;
    }
    else if (typeName == "bit") {
        colType = Column::BIT;
    }
    else if (typeName == "date") {
        colType = Column::DATE;
    }
    // TODO else if (typeName == "float")
    else {
        colType = Column::UNKNOWN;       
    }

    return new Column();// (isPK, isNull, isAI, isUS, name, defaultValue, tableName, name.size (), limit, precision, colType, nullptr);

}
