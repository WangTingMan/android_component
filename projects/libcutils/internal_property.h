#pragma once
#include <functional>
#include <map>
#include <string>

namespace property_internal
{

    using foreach_fun = std::function<void( const char* /*name*/, const char* /*value*/, void* /*cookie*/ )>;

extern "C"
{
    int __internal_property_set( const char* key, const char* value );
    int __internal_property_get( const char* key, char* value );
}

    void import_properties( std::map<std::string,std::string> properties );
    void foreach_properties( foreach_fun a_fun, void* user_data );
}


