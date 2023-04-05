#include "IHelloService.h"
#include <corecrt_io.h>

namespace android {

    class BpHelloService : public BpInterface<IHelloService>
    {
    public:
        BpHelloService(const sp<IBinder>& impl) : BpInterface<IHelloService>(impl)
        {
        }

        void sayhello(void)
        {
            Parcel data, reply;
            data.writeInt32(0);
            data.writeString16(String16("IHelloService"));
            remote()->transact(HELLO_SVR_CMD_SAYHELLO, data, &reply);
        }

        int sayhello_to(const char* name)
        {
            Parcel data, reply;
            int exception;

            data.writeInt32(0);
            data.writeString16(String16("IHelloService"));
            data.writeString16(String16(name));
            remote()->transact(HELLO_SVR_CMD_SAYHELLO_TO, data, &reply);
            exception = reply.readInt32();
            if (exception)
                return -1;
            else
                return reply.readInt32();
        }

        int get_fd(void)
        {
            Parcel data, reply;
            int exception;

            data.writeInt32(0);
            data.writeString16(String16("IHelloService"));
            remote()->transact(HELLO_SVR_CMD_GET_FD, data, &reply);

            exception = reply.readInt32();
            if (exception)
                return -1;
            else
            {
                int rawFd = reply.readFileDescriptor();
                return dup(rawFd);
            }
        }
    };

    const ::android::StaticString16 IHelloService_descriptor_static_str16((u"android.media.IHelloService")); 
    const ::android::String16 IHelloService::descriptor(IHelloService_descriptor_static_str16);

    const ::android::String16& IHelloService::getInterfaceDescriptor() const {
        return IHelloService::descriptor;
    }

    ::android::sp<IHelloService> IHelloService::asInterface(const ::android::sp<::android::IBinder>& obj) {
        ::android::sp<IHelloService> intr; if (obj != nullptr) {
            intr = ::android::sp<IHelloService>::cast(obj->queryLocalInterface(IHelloService::descriptor)); if (intr == nullptr) {
                intr = ::android::sp<BpHelloService>::make(obj);
            }
        } return intr;
    }

    ::android::sp<IHelloService> IHelloService::default_impl;
    
    bool IHelloService::setDefaultImpl(::android::sp<IHelloService> impl) {
        (void)((!!(!IHelloService::default_impl)) || (_wassert(L"!IHelloService::default_impl", L"E:\\VCLAB\\HelloBinerService\\BpHelloService.cpp", (unsigned)(56)), 0)); if (impl) {
            IHelloService::default_impl = std::move(impl); return true;
        } return false;
    }
    
    const ::android::sp<IHelloService>& IHelloService::getDefaultImpl() {
        return IHelloService::default_impl;
    }
    
    IHelloService::IHelloService()
    {}
    
    IHelloService::~IHelloService() {};
}