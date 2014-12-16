#pragma once
#include <string>
#include <vector>
#include <map>

class Column {
public:
    // Possible simple types for columns
    enum Type {
        UNKNOWN,
        BIT, TINYINT, SMALLINT, MEDIUMINT, INT, BIGINT,         // Integer
        FLOAT, DOUBLE, DECIMAL,                                 // Real
        CHAR, VARCHAR, TINYTEXT, TEXT, MEDIUMTEXT, LONGTEXT,    // Text
        DATE, TIME, YEAR, DATETIME, TIMESTAMP                   // Temporal
    };

    static std::map <Type, std::string> mapTypeStrings;

    // Converts given raw std::string values to a new Column object
    static Column * parseRawData (std::string tableName, std::string name, std::string type, std::string nullable,
                                std::string key, std::string defaultValue, std::string extra);

    // Cons. & Des.
    Column ();
    ~Column ();

    // Constructor with column info
    Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
            const std::string name, const std::string defaultValue, const std::string tableName,
            const unsigned int width, const Type type, Column * FK);

    // Getters
    std::string getName ();
    std::string getDefault ();
    std::string getStringType ();
    std::string getTableName ();
    Type getType ();
    unsigned int getWidth ();
    bool getIsPrimaryKey ();
    bool getIsNullable ();
    bool getIsAutoIncrement ();
    Column * getForeignKey ();

    // Virtual getters
    virtual unsigned int getLimit ();
    virtual unsigned int getPrecision ();
    virtual bool getIsUnsigned ();

    // Setters
    void setWidth (const unsigned int width);
    void setForeignKey (Column * const foreignKey);

protected:
    // Column information
    bool isPrimaryKey;
    bool isNullable;
    bool isAutoIncrement;
    std::string mName;
    std::string mDefault;
    std::string mTableName;
    unsigned int mWidth;
    Type mType;

    // Relation constraints
    Column * pForeignKey;

    // Creates pairs Type - string
    static std::map<Type, std::string> initializeMap () {
        std::map<Type, std::string> map;
        map[UNKNOWN] = "";
        map[BIT] = "bit";
        map[TINYINT] = "tinyint";
        map[SMALLINT] = "smallint";
        map[MEDIUMINT] = "mediumint";
        map[INT] = "int";
        map[BIGINT] = "bigint";
        map[FLOAT] = "float";
        map[DOUBLE] = "double";
        map[DECIMAL] = "decimal";
        map[CHAR] = "char";
        map[VARCHAR] = "varchar";
        map[TINYTEXT] = "tinytext";
        map[TEXT] = "text";
        map[MEDIUMTEXT] = "mediumtext";
        map[LONGTEXT] = "longtext";
        map[DATE] = "date";
        map[TIME] = "time";
        map[YEAR] = "year";
        map[DATETIME] = "datetime";
        map[TIMESTAMP] = "timestamp";

        return map;
    }
};

