#include "internal_property.h"
#include <map>
#include <string>
#include <shared_mutex>

static std::map<std::string, std::string>& g_properties = *new std::map<std::string, std::string>;
static std::shared_mutex g_properties_mutex;

namespace property_internal
{

extern "C"
{
    int __internal_property_set( const char* key, const char* value )
    {
        if( key == nullptr || *key == '\0' ) return -1;
        if( value == nullptr ) value = "";

        bool read_only = !strncmp( key, "ro.", 3 );

        std::lock_guard<std::shared_mutex> locker( g_properties_mutex );

        if( read_only )
        {
            const auto [it, success] = g_properties.insert( { key, value } );
            return success ? 0 : -1;
        }

        if( strlen( value ) >= 92 ) return -1;
        g_properties[key] = value;
        return 0;
    }

    int __internal_property_get( const char* key, char* value )
    {
        std::shared_lock<std::shared_mutex> locker( g_properties_mutex );

        auto it = g_properties.find( key );
        if( it == g_properties.end() )
        {
            *value = '\0';
            return 0;
        }
        snprintf( value, 92, "%s", it->second.c_str() );
        return strlen( value );
    }
}

void import_properties(std::map<std::string, std::string> properties)
{
    std::shared_lock<std::shared_mutex> locker(g_properties_mutex);
    g_properties.merge(std::move(properties));
}

}

