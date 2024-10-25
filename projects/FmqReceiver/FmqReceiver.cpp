#include <iostream>
#include <fmq/MessageQueue.h>
#include <fmq/system_porting.h>
#include <fmq/AidlMessageQueue.h>
#include <aidl/android/hardware/common/fmq/MQDescriptor.h>

int main()
{
    using ::aidl::android::hardware::common::fmq::MQDescriptor;
    using ::aidl::android::hardware::common::fmq::SynchronizedReadWrite;
    using ::android::AidlMessageQueue;

    using MqDataType = int8_t;
    using MqDataMode = SynchronizedReadWrite;
    using DataMQ = AidlMessageQueue<MqDataType, MqDataMode>;
    using DataMQDesc = MQDescriptor<MqDataType, MqDataMode>;

    std::unique_ptr<DataMQ> data_mq_;
    DataMQDesc mq_desc;
    std::string json_str{
        R"(
{
 "GrantorDescriptor_key" : 
 [
  {
   "GrantorDescriptor_extent_key" : 8,
   "GrantorDescriptor_fdIndex_key" : 0,
   "GrantorDescriptor_flags_key" : 0,
   "GrantorDescriptor_offset_key" : 0
  },
  {
   "GrantorDescriptor_extent_key" : 8,
   "GrantorDescriptor_fdIndex_key" : 0,
   "GrantorDescriptor_flags_key" : 0,
   "GrantorDescriptor_offset_key" : 8
  },
  {
   "GrantorDescriptor_extent_key" : 7680,
   "GrantorDescriptor_fdIndex_key" : 0,
   "GrantorDescriptor_flags_key" : 0,
   "GrantorDescriptor_offset_key" : 16
  },
  {
   "GrantorDescriptor_extent_key" : 4,
   "GrantorDescriptor_fdIndex_key" : 0,
   "GrantorDescriptor_flags_key" : 0,
   "GrantorDescriptor_offset_key" : 7696
  }
 ],
 "GrantorDescriptor_size_key" : 4,
 "flags_key" : 1,
 "name_key" : "android_fmq_test_shared_memory",
 "numFds_key" : 1,
 "numInts_key" : 0,
 "quantum_key" : 1
}
    )"
    };
    mq_desc.from_json_descriptor(json_str);
    mq_desc.json_decriptor;

    data_mq_.reset(new DataMQ(mq_desc));
    if (!data_mq_->isValid())
    {
        std::cout << "data mq is invalid";
        return 0;
    }

    std::vector<char> buffer;
    buffer.resize(1024);
    while (true)
    {
        if (data_mq_ == nullptr || !data_mq_->isValid()) break;
        size_t avail_to_read = data_mq_->availableToRead();;
        if (avail_to_read > 0)
        {
            std::size_t size_to_read = ( avail_to_read < 1024 ? avail_to_read : 1023 );
            bool read_status = data_mq_->read((MqDataType*)buffer.data(), size_to_read );
            if ( read_status )
            {
                std::cout << "read: " << buffer.data() << std::endl;
                memset( buffer.data(), 0x00, size_to_read );
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    std::cout << "Hello World!\n";
}


