#include "module_manager.h"
#include "ipc_manager.h"

#define MODULE_MANAGER_NAME "module_manager"

std::shared_ptr<module_manager> module_manager::get_instance()
{
    static std::shared_ptr<module_manager> instance =
        std::make_shared<module_manager>();
    return instance;
}

module_manager::module_manager()
{
    set_module_name(MODULE_MANAGER_NAME);
    load_basic_modules();
}

int module_manager::init()
{
    std::unique_lock locker(m_mutex);
    std::unordered_map<std::string, std::shared_ptr<abstract_module>> modules;
    modules = std::move(m_modules);
    locker.unlock();
    for( auto it = modules.begin(); it != modules.end(); ++it )
    {
        it->second->init();
    }

    locker.lock();
    if (!m_modules.empty())
    {
        locker.unlock();
        init();
    }

    if( !locker.owns_lock() )
    {
        locker.lock();
    }
    m_modules.merge(modules);
    return 0;
}

void module_manager::stop()
{
    for( auto it = m_modules.begin(); it != m_modules.end(); ++it )
    {
        it->second->stop();
    }
}

void module_manager::release()
{
    for( auto it = m_modules.begin(); it != m_modules.end(); ++it )
    {
        it->second->release();
    }
}

std::shared_ptr<abstract_module> module_manager::get_module( std::string const& a_name )
{
    std::shared_lock locker(m_mutex);
    std::shared_ptr<abstract_module> ret;
    auto it = m_modules.find( a_name );
    if( it != m_modules.end() )
    {
        ret = it->second;
    }
    return ret;
}

std::shared_ptr<abstract_module> module_manager::get_module( uint8_t a_type )
{
    std::shared_lock locker(m_mutex);
    for( auto it = m_modules.begin(); it != m_modules.end(); ++it )
    {
        if( it->second->get_type() == a_type )
        {
            return it->second;
        }
    }
    return nullptr;
}

bool module_manager::add_new_module( std::shared_ptr<abstract_module> a_module )
{
    std::lock_guard locker(m_mutex);
    m_modules.insert_or_assign( a_module->get_module_name(), a_module );
    return true;
}

void module_manager::load_basic_modules()
{
    add_new_module(std::make_shared<ipc_manager>());
}
