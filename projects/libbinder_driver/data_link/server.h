#pragma once
#include <functional>
#include <memory>
#include <string>

#include "message_types.h"

namespace data_link
{

class client;

class server
{

public:

    using new_client_callback = std::function<void( std::shared_ptr<client> )>;

    static std::shared_ptr<server> make_one();

    virtual ~server() {};

    virtual void listen_on
        ( 
        std::string a_address,
        bool a_accupy_current_thread
        ) = 0;

    virtual void new_client_connected( new_client_callback a_new_client_callback ) = 0;

private:


};

}
