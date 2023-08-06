#pragma once
#include <functional>
#include <memory>
#include <string>

#include "message_types.h"

namespace data_link
{

class server
{

public:

    static std::shared_ptr<server> make_one();

    virtual ~server() {};

    virtual void listen_on
        ( 
        std::string a_address,
        bool a_accupy_current_thread
        ) = 0;

    virtual void send_message( std::shared_ptr<binder_ipc_message> a_message ) = 0;

    virtual void register_message_incoming_callback( message_callback a_callback ) = 0;

private:


};

}
