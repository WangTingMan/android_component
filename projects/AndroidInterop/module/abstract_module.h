#pragma once
#include <string>
#include <memory>

#include <boost/signals2.hpp>

#include "module/common_types.h"

class abstract_module : public std::enable_shared_from_this<abstract_module>
{

public:

    abstract_module()
        : m_init_status(bluetooth_module::init_status::deinitialized)
    {

    }

    virtual ~abstract_module();

    virtual int init();

    virtual void stop();

    virtual void release();

    virtual std::string get_module_name()const final
    {
        return m_name;
    }

    void set_type( uint8_t a_type )
    {
        m_type = a_type;
    }

    uint8_t get_type()const
    {
        return m_type;
    }

    void set_init_status(bluetooth_module::init_status a_status)
    {
        m_init_status = a_status;
        m_init_status_signal(m_init_status);
    }

    bluetooth_module::init_status get_init_status()const
    {
        return m_init_status;
    }

protected:

    virtual void set_module_name( std::string a_name )final
    {
        m_name = a_name;
    }

private:

    std::string m_name{ "NULL" };
    uint8_t m_type = 0x00;
    bluetooth_module::init_status m_init_status;
    boost::signals2::signal<void(bluetooth_module::init_status)> m_init_status_signal;
};

