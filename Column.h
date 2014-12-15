#pragma once
#include <string>

class Column {
public:
    // Possible simple types for columns
    enum Type {
        UNKNOWN = 0,
        VARCHAR = 1,
        INT = 1 << 1,
        FLOAT = 1 << 2,
        BOOL = 1 << 3,
        DATE = 1 << 4
    };

    // Converts given raw std::string values to a new Column object
    static Column parseRawData (std::string tableName, std::string name, std::string type, std::string nullable,
                                std::string key, std::string defaultValue, std::string extra);

    // Cons. & Des.
    Column ();
    ~Column ();

    // Constructor with column info
    Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement,
            const bool isUnsigned, const std::string name, const std::string defaultValue, const std::string tableName,
            const unsigned int width, const unsigned int limit, const unsigned int precision, 
            const Type type, const Column * FK);

    // Getters
    std::string getName ();
    std::string getDefault ();
    std::string getStringType ();
    std::string getTableName ();
    Type getType ();
    unsigned int getWidth ();
    unsigned int getLimit ();
    unsigned int getPrecision ();
    bool getIsPrimaryKey ();
    bool getIsNullable ();
    bool getIsAutoIncrement ();
    bool getIsUnsigned ();
    Column * getForeignKey ();
  
    // Setters
    void setWidth (const unsigned int width);
    void setForeignKey (Column * const foreignKey);

private:
    // Column information
    bool isPrimaryKey;
    bool isNullable;
    bool isAutoIncrement;
    bool isUnsigned;
    std::string mName;
    std::string mDefault;
    std::string mTableName;
    unsigned int mWidth;
    unsigned int mLimit;
    unsigned int mPrecision;
    Type mType;

    // Relation constraints
    Column * pForeignKey;
};

