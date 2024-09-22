
#include <iostream>
#include <hwbinder/Parcel.h>
#include <hidl/HidlBinderSupport.h>

int main()
{
    android::hardware::Parcel parcel;
    ::android::status_t _hidl_err;
    parcel.writeInt32(20);
    {
        std::vector<int> values{ 1,2,3,4,5 };
        ::android::hardware::hidl_vec<int> _hidl_out_audioCapabilities(values);
        size_t _hidl__hidl_out_audioCapabilities_parent;
        _hidl_err = parcel.writeBuffer(&_hidl_out_audioCapabilities, sizeof(_hidl_out_audioCapabilities),
            &_hidl__hidl_out_audioCapabilities_parent);
        size_t _hidl__hidl_out_audioCapabilities_child;

        _hidl_err = ::android::hardware::writeEmbeddedToParcel(
            _hidl_out_audioCapabilities,
            &parcel,
            _hidl__hidl_out_audioCapabilities_parent,
            0 /* parentOffset */, &_hidl__hidl_out_audioCapabilities_child);
    }


    const ::android::hardware::hidl_vec<int>* _hidl_out_audioCapabilities;
    android::hardware::Parcel _hidl_reply;
    _hidl_reply.setData(parcel.data(), parcel.dataSize());
    auto value = _hidl_reply.readInt32();
    size_t _hidl__hidl_out_audioCapabilities_parent;
    _hidl_err = _hidl_reply.readBuffer(sizeof(*_hidl_out_audioCapabilities),
        &_hidl__hidl_out_audioCapabilities_parent, reinterpret_cast<const void**>(&_hidl_out_audioCapabilities));

    size_t _hidl__hidl_out_audioCapabilities_child;

    _hidl_err = ::android::hardware::readEmbeddedFromParcel(
        const_cast<::android::hardware::hidl_vec<int> &>(*_hidl_out_audioCapabilities),
        _hidl_reply,
        _hidl__hidl_out_audioCapabilities_parent,
        0 /* parentOffset */, &_hidl__hidl_out_audioCapabilities_child);

    std::vector<int> read_results(_hidl_out_audioCapabilities->begin(), _hidl_out_audioCapabilities->end());
    std::cout << "Hello World!\n";
    return 0;
}

