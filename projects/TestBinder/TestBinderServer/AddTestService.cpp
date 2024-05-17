#include "AddTestService.h"
#include <binder/IPCThreadState.h>

#include <iostream>

int android::AddTestService::Add(int a, int b) {
    auto currrent_ipc_state = android::IPCThreadState::self();
    pid_t calling_pid = 0;
    uid_t calling_uid = 0;
    if( currrent_ipc_state )
    {
        calling_pid = currrent_ipc_state->getCallingPid();
        const char* calling_sid = currrent_ipc_state->getCallingSid();
        if( !calling_sid )
        {
            calling_sid = "No calling sid";
        }
        calling_uid = currrent_ipc_state->getCallingUid();
    }

    std::cout << "From pid " << calling_pid << "'s calling: "
        << a << " + " << b << " = " << a + b << std::endl;
    return a + b;
}
