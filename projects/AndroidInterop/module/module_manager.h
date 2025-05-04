#pragma once
#include "abstract_module.h"

#include <memory>
#include <shared_mutex>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

class module_manager : public abstract_module
{

public:

    static std::shared_ptr<module_manager> get_instance();

    module_manager();

    int init()override;

    void stop()override;

    void release()override;

    std::shared_ptr<abstract_module> get_module( std::string const& a_name );

    std::shared_ptr<abstract_module> get_module( uint8_t a_type );

    template<typename ModuleType, typename = typename std::enable_if<
        std::is_base_of<abstract_module, ModuleType>::value,
        std::true_type>::type>
    auto get_module(std::string const& a_name) -> std::shared_ptr<ModuleType>
    {
        auto module_ = get_module(a_name);
        return std::dynamic_pointer_cast<ModuleType>(module_);
    }

    template<typename ModuleType>
    auto get_modules() -> std::vector<std::shared_ptr<ModuleType>>
    {
        std::vector<std::shared_ptr<ModuleType>> modules;
        std::lock_guard locker(m_mutex);
        for (auto& ele : m_modules)
        {
            auto module_ = std::dynamic_pointer_cast<ModuleType>( ele.second );
            if (module_)
            {
                modules.push_back(module_);
            }
        }
        return modules;
    }

    bool add_new_module( std::shared_ptr<abstract_module> a_module );

private:

    void load_basic_modules();

    std::shared_mutex m_mutex;
    std::unordered_map<std::string, std::shared_ptr<abstract_module>> m_modules;

};

