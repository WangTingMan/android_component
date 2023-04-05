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
    // �ؼ���1 ��ʼ��binder
    sp<ProcessState> proc(ProcessState::self());

    // �ؼ���2 ���BpServiceManager
    sp<IServiceManager> sm = defaultServiceManager();

    // �ؼ���3
    sm->addService(String16("hello"), new BnHelloService());

    // �ؼ���4 �����µ����̣߳�����ʼ���������ϱ�����Ϣ
    ProcessState::self()->startThreadPool();

    // �ؼ���5 ���߳� ѭ����ѭ�������������ϱ�����Ϣ
    IPCThreadState::self()->joinThreadPool();//������ IPCThreadState�ķ���

    return 0;
}