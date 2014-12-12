#include <sstream>
#include "Column.h"

Column::Column () {
}

Column::~Column () {
}

Column::Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                const bool isUnsigned, const std::string name, const std::string defaultValue,
                const unsigned int width, const unsigned int limit, const unsigned int precision,
                const Type type, const Column * FK) :
                isPrimaryKey (isPrimaryKey), isNullable (isNullable), isAutoIncrement (isAutoIncrement),
                isUnsigned(isUnsigned), mName (name), mDefault (defaultValue), mWidth (width), mLimit (limit), 
                mPrecision (precision), mType (type), pForeignKey (const_cast<Column*>(FK)) {
}

std::string Column::getName () {
    return mName;
}

std::string Column::getDefault () {
    return mDefault;
}

std::string Column::getStringType () {
    switch (this->mType) {
        case Column::BOOL:
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

Column::Type Column::getType () {
    return mType;
}

unsigned int Column::getWidth () {
    return mWidth;
}

unsigned int Column::getLimit () {
    return mLimit;
}

unsigned int Column::getPrecision () {
    return mPrecision;
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

bool Column::getIsUnsigned () {
    return isUnsigned;
}

void Column::setWidth (const unsigned int width) {
    mWidth = width;
}

Column Column::parseRawData (std::string name, std::string type, std::string nullable,
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
        colType = Column::BOOL;
    }
    else if (typeName == "date") {
        colType = Column::DATE;
    }
    // TODO else if (typeName == "float")
    else {
        colType = Column::UNKNOWN;       
    }

    return Column (isPK, isNull, isAI, isUS, name, defaultValue,name.size (), limit, precision, colType, nullptr);

}
