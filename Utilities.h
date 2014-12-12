#pragma once
#include <sstream>

class Utilities {
public:
    // General converter for numerical values.
    template <typename Type>
    static std::string convertToString (Type toConvert) {
        std::stringstream ss;
        ss << toConvert;
        return ss.str ();
    }
};

