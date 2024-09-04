#include <iostream>
#include <thread>

#include <fmq/MessageQueue.h>
#include <fmq/AidlMessageQueue.h>
#include <aidl/android/hardware/common/fmq/MQDescriptor.h>

// Here the buffer size is based on SBC
static constexpr uint32_t kPcmFrameSize = 4;  // 16 bits per sample / stereo
// SBC is 128, and here we choose the LCM of 16, 24, and 32
static constexpr uint32_t kPcmFrameCount = 96;
static constexpr uint32_t kRtpFrameSize = kPcmFrameSize * kPcmFrameCount;
// The max counts by 1 tick (20ms) for SBC is about 7. Since using 96 for the
// PCM counts, here we just choose a greater number
static constexpr uint32_t kRtpFrameCount = 10;
static constexpr uint32_t kBufferSize = kRtpFrameSize * kRtpFrameCount;
static constexpr uint32_t kBufferCount = 2;  // double buffer
static constexpr uint32_t kDataMqSize = kBufferSize * kBufferCount;

int main()
{
    using ::aidl::android::hardware::common::fmq::MQDescriptor;
    using ::aidl::android::hardware::common::fmq::SynchronizedReadWrite;
    using ::android::AidlMessageQueue;

    using MqDataType = int8_t;
    using MqDataMode = SynchronizedReadWrite;
    using DataMQ = AidlMessageQueue<MqDataType, MqDataMode>;
    using DataMQDesc = MQDescriptor<MqDataType, MqDataMode>;

    std::unique_ptr<DataMQ> data_mq(
        new DataMQ(kDataMqSize, /* EventFlag */ true));

    auto desc = data_mq->dupeDesc();
    std::string json_descriptor = desc.json_decriptor;
    std::cout << "json descriptor:\n" << json_descriptor << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (int i = 0; i < 1000; ++i)
    {
        std::string write_str{ "hello. this is " };
        write_str.append(std::to_string(i));
        write_str.append(" message.");
        bool ret = data_mq->write((MqDataType*)write_str.data(), write_str.size());
        std::cout << std::boolalpha << "write result " << ret << ": " << write_str << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    system("pause");
}


