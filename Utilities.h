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

    template <typename Type>
    static Type convertFromString (const std::string toConvert) {
        if (toConvert == "")
            return Type();
        std::stringstream ss;
        ss.str (toConvert);
        Type result;
        ss >> result;
        return result;
    }
};

