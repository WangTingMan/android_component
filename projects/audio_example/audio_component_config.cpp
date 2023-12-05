
#define WINSOCK_API_LINKAGE

#include "audio_component_config.h"
#include <base\native_library.h>
#include <base\files\file_path.h>
#include <base/logging.h>
#include <linux/MessageLooper.h>
#include <binderwrapper/service.h>

extern "C"
{
    typedef void* (*get_audio_module_type)();
    typedef int32_t( *load_android_audio_type )( );
}

audio_component_config& audio_component_config::get_instance()
{
    static audio_component_config instance;
    return instance;
}

audio_component_config::audio_component_config()
{
    m_observer.force_set( new BluetoothObserver );
    MessageLooper::GetDefault().PostTask( std::bind( &audio_component_config::register_observer, this ) );
    MessageLooper::GetDefault().PostTask( std::bind( &audio_component_config::load_android_bluetooth_audio, this ) );
}

void audio_component_config::register_observer()
{
    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    android::sp<android::IBinder> binder = sm->getService( android::String16( IBluetoothService::descriptor ) );
    if( !binder )
    {
        MessageLooper::GetDefault().PostDelayTask( 1000, std::bind( &audio_component_config::register_observer, this ) );
        return;
    }

    android::sp<IBluetoothService> iservice = interface_cast<IBluetoothService>( binder );
    iservice->RegisterObserver( m_observer );
}

void audio_component_config::load_android_bluetooth_audio()
{
    base::NativeLibraryLoadError error;
    std::string lib_name{ "android.hardware.bluetooth.audio-impl.so" };
    auto lib = base::LoadNativeLibrary( lib_name, &error);
    if( lib == NULL )
    {
        LOG( ERROR ) << "Cannot load library: " << lib_name;
        return;
    }

    load_android_audio_type factoryFunction;
    factoryFunction = (load_android_audio_type)( base::GetFunctionPointerFromNativeLibrary
        ( lib, "createIBluetoothAudioProviderFactory" ) );
    if( factoryFunction )
    {
        factoryFunction();
    }
    else
    {
        LOG( ERROR ) << "Cannot load symbol: " << "createIBluetoothAudioProviderFactory";
    }
}

void audio_component_config::load_all_component()
{
    for( auto& ele : m_components )
    {
        base::NativeLibraryLoadError error;
        auto lib = base::LoadNativeLibrary( ele.component, &error );
        get_audio_module_type get_module;
        get_module = (get_audio_module_type)( base::GetFunctionPointerFromNativeLibrary(lib,"get_audio_module") );
        m_audio_module = (audio_module*)get_module();
        if( m_audio_module )
        {
            break;
        }
    }

    if( !m_audio_module )
    {
        return;
    }

    memset( &m_module, 0x00, sizeof( hw_module_t ) );
    std::string id_name{ "audio_hw_if" };
    hw_device_t* device_ = nullptr;
    int ret_value = 0;

    ret_value = m_audio_module->common.methods->open( &m_module, id_name.c_str(), &device_ );
    m_audio_hw = reinterpret_cast<audio_hw_device*>( device_ );
    ret_value = m_audio_hw->init_check( m_audio_hw );
}

void audio_component_config::handle_connection_status_changed( std::vector<uint8_t> a_addr, bool a_connected )
{
    LOG( INFO ) << ( a_connected ? "connected" : "disconnected" );
}

void audio_component_config::handle_active_device_changed( std::vector<uint8_t> a_addr )
{
    int ret_value = 0;
    audio_io_handle_t handle_ = 0;
    audio_devices_t audio_device_ = AUDIO_DEVICE_OUT_BLUETOOTH_A2DP;
    audio_output_flags_t flags_ = AUDIO_OUTPUT_FLAG_DIRECT_PCM;
    audio_config audio_config_;
    audio_stream_out* audio_out = nullptr;
    std::string device_address = { "00:11:22:AA:BB:CC" };
    ret_value = m_audio_hw->open_output_stream( m_audio_hw, handle_, audio_device_, flags_, &audio_config_, &audio_out, device_address.c_str() );

    char buffer[12] = { 0 };
    if( audio_out )
    {
        audio_out->write( audio_out, buffer, 10 );
    }
    m_audio_hw->dump( m_audio_hw, 20 );

    std::string parameters{ "audio_hw_if" };
    ret_value = m_audio_hw->set_parameters( m_audio_hw, parameters.c_str() );
}

