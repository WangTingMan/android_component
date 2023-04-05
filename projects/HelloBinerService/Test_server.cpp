#define LOG_TAG "TestService"
//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "IHelloService.h"

#define SOCKET_BUFFER_SIZE      (32768U)

using namespace android;

int main(void)
{
    // 关键点1 初始化binder
    sp<ProcessState> proc(ProcessState::self());

    // 关键点2 获得BpServiceManager
    sp<IServiceManager> sm = defaultServiceManager();

    // 关键点3
    sm->addService(String16("hello"), new BnHelloService());

    // 关键点4 创建新的子线程，并开始处理驱动上报的消息
    ProcessState::self()->startThreadPool();

    // 关键点5 主线程 循环，循环并处理驱动上报的消息
    IPCThreadState::self()->joinThreadPool();//辅助类 IPCThreadState的分析

    return 0;
}