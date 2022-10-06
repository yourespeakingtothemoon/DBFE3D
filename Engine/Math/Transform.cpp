#include "Transform.h"

bool dbf::Transform::write(const rapidjson::Value& value) const
{

    return true;
}

bool dbf::Transform::read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);
    READ_DATA(value, rotation);
    
    return true;
}
