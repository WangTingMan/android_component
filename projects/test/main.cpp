#include "timer_test.h"
#include <iostream>
#include <chrono>
#include <log/log.h>

#include "binder_data_link/server_test.h"

int main()
{
    bool is_server = false;

    if( is_server )
    {
        __set_default_log_file_name( "E:\\VCLAB\\component\\x64\\Debug\\rpc_server.txt" );
        server_start_test();
    }
    else
    {
        __set_default_log_file_name( "E:\\VCLAB\\component\\x64\\Debug\\rpc_client.txt" );
        client_start_test();
    }

    system("pause");
    return 0;
}

