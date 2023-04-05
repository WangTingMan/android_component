#ifndef ANDROID_IHELLOERVICE_H
#define ANDROID_IHELLOERVICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#define HELLO_SVR_CMD_SAYHELLO     1
#define HELLO_SVR_CMD_SAYHELLO_TO  2
#define HELLO_SVR_CMD_GET_FD       3 //后面会单独分析这个部分

namespace android {
    class IHelloService : public IInterface
    {
    public:

        static const ::android::String16 descriptor;
        static ::android::sp<IHelloService> asInterface(const ::android::sp<::android::IBinder>& obj);
        virtual const ::android::String16& getInterfaceDescriptor() const;
        IHelloService();
        virtual ~IHelloService();
        static bool setDefaultImpl(::android::sp<IHelloService> impl);
        static const ::android::sp<IHelloService>& getDefaultImpl();
    private:
        static ::android::sp<IHelloService> default_impl;
    public:;
        virtual void sayhello(void) = 0;
        virtual int sayhello_to(const char* name) = 0;
        virtual int get_fd(void) = 0;
    };

    class BnHelloService : public BnInterface<IHelloService>
    {
    private:
        int fd;
    public:
        virtual status_t    onTransact(uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags = 0);
        virtual void sayhello(void);
        virtual int sayhello_to(const char* name);
        virtual int get_fd(void); //后面会单独分析这个部分

        BnHelloService();
        BnHelloService(int fd);
    };
}
#endif