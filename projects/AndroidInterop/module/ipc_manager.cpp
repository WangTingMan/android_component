#include "ipc_manager.h"
#include <android/binder_process.h>

#include <Zhen/logging.h>
#include "mtk/mtk_aidl_local_service.h"
#include "mtk/mtk_hidl_local_service.h"
#include "qcom/qcom_hidl_local_service.h"
#include "aosp/aosp_aidl_local_service.h"
#include "module_manager.h"

#include <fmq/MessageQueue.h>
#include <fmq/AidlMessageQueue.h>
#include <aidl/android/hardware/common/fmq/MQDescriptor.h>

#include <cutils/properties.h>

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

using ::aidl::android::hardware::common::fmq::MQDescriptor;
using ::aidl::android::hardware::common::fmq::SynchronizedReadWrite;
using ::android::AidlMessageQueue;

using MqDataType = int8_t;
using MqDataMode = SynchronizedReadWrite;
using DataMQ = AidlMessageQueue<MqDataType, MqDataMode>;
using DataMQDesc = MQDescriptor<MqDataType, MqDataMode>;

#define MTK_AIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.mtk_aidl_audio_local_service_enabled"
#define MTK_HIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.mtk_hidl_audio_local_service_enabled"
#define AOSP_AIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.aospaidl_audio_local_service_enabled"
#define QCOM_HIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.qcom_hidl_audio_local_service_enabled"

class ipc_manager_impl
{

public:

    std::string get_fmq_json_descriptor()
    {
        auto desc = m_data_mq->dupeDesc();
        std::string json_descriptor = desc.json_decriptor;
        return json_descriptor;
    }

    void init()
    {
        m_data_mq = std::make_unique<DataMQ>( kDataMqSize,
                                              /* EventFlag */ true );
    }

private:

    std::unique_ptr<DataMQ> m_data_mq;
};

ipc_manager::ipc_manager()
{
    set_module_name(s_module_name);
    m_impl = std::make_shared<ipc_manager_impl>();

    bluetooth_module::pcm_configuration pcm_capabilities;
    pcm_capabilities.bits_per_sample = 16;
    pcm_capabilities.channel_type = bluetooth_module::channel_mode::stereo;
    pcm_capabilities.sample_rate_hz = 44100;
    m_local_psm_capabilities.push_back( pcm_capabilities );
}

int ipc_manager::init()
{
    if (bluetooth_module::init_status::deinitialized != get_init_status())
    {
        LogError() << "Not deinitialized stauts.";
        return 0;
    }

    load_config();

    m_impl->init();

    trigger_run();

    auto mtk_aidl_service = std::make_shared<mtk_aidl_local_service>();
    module_manager::get_instance()->add_new_module(mtk_aidl_service);
    m_audio_services.emplace_back(std::move(mtk_aidl_service));

    auto aosp_aidl_service = std::make_shared<aosp_aidl_local_service>();
    module_manager::get_instance()->add_new_module(aosp_aidl_service);
    m_audio_services.emplace_back(std::move(aosp_aidl_service));

    auto mtk_hidl_service = std::make_shared<mtk_hidl_local_service>();
    module_manager::get_instance()->add_new_module(mtk_hidl_service);
    m_audio_services.emplace_back( std::move( mtk_hidl_service ) );

    auto qcom_hidl_service = std::make_shared<qcom_hidl_local_service>();
    module_manager::get_instance()->add_new_module( qcom_hidl_service );
    m_audio_services.emplace_back( std::move( qcom_hidl_service ) );

    set_init_status(bluetooth_module::init_status::initialized);
    return 0;
}

void ipc_manager::stop()
{

}

void ipc_manager::release()
{

}

void ipc_manager::trigger_run()
{
    std::shared_ptr<std::promise<void>> promise;
    promise = std::make_shared<std::promise<void>>();
    std::future<void> future = promise->get_future();
    m_running_thread = std::thread( &ipc_manager::run_detail, this, promise );
    future.wait_for( std::chrono::seconds( 1 ) );
}

void ipc_manager::run_detail( std::shared_ptr<std::promise<void>> a_promise )
{
    a_promise->set_value();
    a_promise.reset();

    LogDebug() << "Start to run ipc manager.";
    ABinderProcess_joinThreadPool();
}

std::string ipc_manager::get_fmq_json_descriptor()
{
    return m_impl->get_fmq_json_descriptor();
}

void ipc_manager::set_selected_pcm_configuration(bluetooth_module::pcm_configuration a_pcm_config)
{
    m_pcm_config = a_pcm_config;
}

void ipc_manager::start_stream()
{
    for (auto& ele : m_audio_services )
    {
        if (ele)
        {
            ele->start_stream();
        }
    }
}

void ipc_manager::stop_stream()
{
    for (auto& ele : m_audio_services )
    {
        if (ele)
        {
            ele->stop_stream();
        }
    }
}

void ipc_manager::suspend_stream()
{
    for (auto& ele : m_audio_services )
    {
        if (ele)
        {
            ele->suspend_stream();
        }
    }
}

void ipc_manager::request_presentaion_delay()
{
    for( auto& ele : m_audio_services )
    {
        if( ele )
        {
            ele->request_presentaion_delay();
        }
    }
}

void ipc_manager::load_config()
{
    property_set( MTK_HIDL_AUDIO_LOCAL_SERVICE_ENABLED, "0" );
    property_set( MTK_AIDL_AUDIO_LOCAL_SERVICE_ENABLED, "0" );

    property_set( AOSP_AIDL_AUDIO_LOCAL_SERVICE_ENABLED, "0" );

    property_set( QCOM_HIDL_AUDIO_LOCAL_SERVICE_ENABLED, "1" );
}

