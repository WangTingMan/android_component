#include "tag_handler_manager.h"

tag_handler_manager& tag_handler_manager::get_instance()
{
    static tag_handler_manager instance;
    return instance;
}

tag_handler_manager::~tag_handler_manager()
{
    m_current_index = 1;
    m_registered_handler.reset();
}

uint64_t tag_handler_manager::register_tag_handler( std::function<void( bool )> a_handler )
{
    std::lock_guard<std::recursive_mutex> locker( m_mutex );
    uint64_t ret = m_current_index++;
    (*m_registered_handler)[ret] = a_handler;
    return ret;
}

std::function<void( bool )> tag_handler_manager::find_tag_handler( uint64_t a_tag_id ) const
{
    std::lock_guard<std::recursive_mutex> locker( m_mutex );
    std::function<void( bool )> fun;
    auto it = m_registered_handler->find( a_tag_id );
    if( it != m_registered_handler->end() )
    {
        fun = it->second;
    }
    return fun;
}

void tag_handler_manager::delete_tag_handler( uint64_t a_tag_id )
{
    if( a_tag_id == 0 )
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> locker( m_mutex );
    if( m_registered_handler )
    {
        m_registered_handler->erase( a_tag_id );
    }
}

