#pragma once
#include <map>
#include <string>

namespace property_internal
{

extern "C"
{
    int __internal_property_set( const char* key, const char* value );
    int __internal_property_get( const char* key, char* value );
}

    void import_properties( std::map<std::string,std::string> properties );

}


