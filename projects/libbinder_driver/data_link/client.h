#pragma once
#include <functional>
#include <memory>
#include <string>

#include "message_types.h"

namespace data_link
{

class client
{

public:

    static std::shared_ptr<client> make_one();

    virtual ~client() {};

    virtual void connect( std::string a_address ) = 0;

    virtual void send_message( std::shared_ptr<binder_ipc_message> a_message ) = 0;

    virtual void register_message_incoming_callback( message_callback a_callback ) = 0;

    virtual connection_status get_connection_status() = 0;

    virtual void register_connection_status_callback( std::function<void( connection_status )> a_callback ) = 0;

private:


};

}

