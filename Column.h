#pragma once
#include <string>

class Column {
public:
    // Possible simple types for columns
    enum Type {
        VARCHAR,
        INT,
        FLOAT,
        BOOL,
        DATE
    };

    // Converts given raw std::string values to a new Column object
    static Column parseRawData (std::string name, std::string type, std::string nullable,
                                std::string key, std::string defaultValue, std::string extra);

    // Cons. & Des.
    Column ();
    ~Column ();

    // Constructor with column info
    Column (const bool isPrimaryKey, const bool isNullable, const bool isAutoIncrement, 
            const bool isUnsigned, const std::string name, const unsigned int width, 
            const unsigned int limit, const unsigned int precision, const Type type, 
            const Column * FK);

    // Getters
    unsigned int getWidth ();
    std::string getName ();

    // Setters
    void setWidth (const unsigned int width);

private:
    // Column information
    bool isPrimaryKey;
    bool isNullable;
    bool isAutoIncrement;
    bool isUnsigned;
    std::string mName;
    unsigned int mWidth;
    unsigned int mLimit;
    unsigned int mPrecision;
    Type mType;

    // Relation constraints
    Column * pForeignKey;
};

