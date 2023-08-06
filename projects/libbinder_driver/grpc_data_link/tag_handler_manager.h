#pragma once
#include <functional>
#include <map>
#include <memory>
#include <mutex>

class tag_handler_manager
{

public:

    static tag_handler_manager& get_instance();

    uint64_t register_tag_handler( std::function<void( bool )> a_handler );

    std::function<void( bool )> find_tag_handler( uint64_t ) const;

    void delete_tag_handler( uint64_t );

private:

    tag_handler_manager()
    {
        m_registered_handler = std::make_shared<std::map<uint64_t, std::function<void( bool )>>>();
    };

    ~tag_handler_manager();

    mutable std::recursive_mutex m_mutex;
    std::shared_ptr<std::map<uint64_t, std::function<void( bool )>>> m_registered_handler;
    uint64_t m_current_index = 1;
};

