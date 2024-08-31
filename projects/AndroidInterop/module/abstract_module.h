#pragma once
#include <string>
#include <memory>

class abstract_module : public std::enable_shared_from_this<abstract_module>
{

public:

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

protected:

    virtual void set_module_name( std::string a_name )final
    {
        m_name = a_name;
    }

private:

    std::string m_name{ "NULL" };
    uint8_t m_type = 0x00;
};

