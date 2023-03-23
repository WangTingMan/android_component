#include "iniparser.h"
#include "cutils/properties.h"
#include "internal_property.h"

#include <memory>
#include <filesystem>
#include <mutex>
#include <cassert>
#include <string>
#include <string_view>
#include <map>

#include <base/strings/string_util.h>

void RemoveAndroidPrefixIfExsit(std::string& value)
{
    auto lst = value.find_last_of(':');
    if (lst != std::string::npos)
    {
        ++lst;
        std::string temp = value.substr(lst);
        value = temp;
    }
}

extern "C" {

void parse_property_from_ini(const char* file)
{
    std::filesystem::path originPath(file);
    if (!std::filesystem::exists(originPath))
    {
        return;
    }

    dictionary* ini = nullptr;
    ini = iniparser_load(file);
    std::shared_ptr<dictionary> mIni;
    mIni.reset(ini, [](void* p)
        {
            dictionary* ini_ = reinterpret_cast<dictionary*>(p);
            iniparser_freedict(ini_);
        });

    std::map<std::string, std::string> properties;
    for (int i = 0; i < ini->size; ++i)
    {
        std::string key, value;
        if (ini->key[i])
        {
            key.assign(ini->key[i]);
        }
        else
        {
            continue;
        }

        if (ini->val[i])
        {
            value.assign(ini->val[i]);
        }
        else
        {
            continue;
        }

        RemoveAndroidPrefixIfExsit(key);
        properties[key] = value;
    }

    property_internal::import_properties(std::move(properties));
}

}
