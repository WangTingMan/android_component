#include <iostream>
#include "hci_backend.h"
#include "hci_detail.h"
#include <binder/IPCThreadState.h>

using namespace bluetooth::hal;
std::shared_ptr<HciBackendCallbacks> callback;

int main()
{
#ifdef __set_default_log_file_name_defined
    __set_default_log_file_name( nullptr, true );
#endif

    callback = std::make_shared<HciBackendCallbacksDetail>();
    std::shared_ptr<HciBackend> hci;
    hci = HciBackend::CreateAidl();
    hci->initialize( callback );

    android::IPCThreadState::self()->joinThreadPool();
    std::cout << "Hello World!\n";
}

