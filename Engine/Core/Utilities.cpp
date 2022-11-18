#include "Utilities.h"
#include <algorithm>

std::string dbf::toLower(const std::string& str)
{
    //convert string to lower case and return changed string
    std::string retStr;
    for (int i=0; i < str.length(); i++)
    {
        retStr.push_back(tolower(str[i]));
       
    }

    return retStr;
}

std::string dbf::toUpper(const std::string& str)
{
    std::string retStr;
    for (int i=0; i < str.length(); i++)
    {
        retStr.push_back(toupper(str[i]));

    }

    return retStr;
}

bool dbf::compareIgnoreCase(const std::string& str1, const std::string& str2)
{
    //return false if strings are not same size
    if (str1.length() != str2.length())
    {
        return false;
    }
    else
    {
        //return false if strings dont match
        for (int i=0; i < str1.length(); i++)
        {
            if (tolower(str1[i]) != tolower(str2[i])) {
                return false;
            }
        }
        return true;
    }

    
    
}
