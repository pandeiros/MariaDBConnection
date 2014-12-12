#include <sstream>
#include "Column.h"

Column::Column () {
}

Column::~Column () {
}

Column::Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
                const bool isUnsigned, const std::string name, const unsigned int width,
                const unsigned int limit, const unsigned int precision, const Type type,
                const Column * FK) :
                isPrimaryKey (isPrimaryKey), isNullable (isNullable), isAutoIncrement (isAutoIncrement),
                isUnsigned(isUnsigned), mName (name), mWidth (width), mLimit (limit), 
                mPrecision (precision), mType (type), pForeignKey (const_cast<Column*>(FK)) {
}

unsigned int Column::getWidth () {
    return mWidth;
}

std::string Column::getName () {
    return mName;
}

void Column::setWidth (const unsigned int width) {
    mWidth = width;
}


Column Column::parseRawData (std::string name, std::string type, std::string nullable,
                             std::string key, std::string defaultValue, std::string extra) {
    std::string typeName = type.substr (0, type.find ("("));
    std::string typeParams = type.substr (typeName.size (), type.find (")") - typeName.size () - 1);

    bool isPK = (key == "PRI");
    bool isNull = (nullable == "YES");
    bool isAI = (extra.find ("auto_increment") != std::string::npos);
    bool isUS = (type.find ("unsigned") != std::string::npos);

    Type colType;
    unsigned int limit, precision;
    std::stringstream ss;
    if (typeName == "varchar") {
        colType = Column::VARCHAR;
        ss.str (typeParams);
        ss >> limit;
        precision = 0;
    }
    else if (typeName == "int") {
        colType = Column::INT;
        ss.str (typeParams);
        ss >> limit;
        precision = 0;
    }
    else if (typeName == "bit") {
        colType = Column::BOOL;
        limit = 0;
        precision = 0;
    }
    else if (typeName == "date") {
        colType = Column::DATE;
        limit = 0;
        precision = 0;
    }
    // TODO else if (typeName == "float")

    return Column (isPK, isNull, isAI, isUS, name, name.size (), limit, precision, colType, nullptr);

}
