#include "BluetoothAudioPortClient.h"

#include <android/binder_manager.h>

namespace bluetooth_module {

class bluetooth_audio_port_client_impl : public bluetooth_audio_port_client
{

public:
    bluetooth_audio_port_client_impl( const char* service_name );
    presentation_position get_presentation_postion()override;
    bool start_stream( bool a_low_latency )override;
    bool stop_stream()override;
    bool suspend_stream()override;
    bool update_source_metadata( std::vector<playback_track_metadata> a_source_meta_data )override;
    bool update_sink_metadata( std::vector<record_track_metadata> a_source_meta_data )override;
    bool set_latency_mode( latency_mode a_latency )override;

private:


};

bluetooth_audio_port_client_impl::bluetooth_audio_port_client_impl( const char* service_name )
{

}

presentation_position bluetooth_audio_port_client_impl::get_presentation_postion()
{
    presentation_position postion;
    return postion;
}

bool bluetooth_audio_port_client_impl::start_stream( bool a_low_latency )
{
    return true;
}

bool bluetooth_audio_port_client_impl::stop_stream()
{
    return true;
}

bool bluetooth_audio_port_client_impl::suspend_stream()
{
    return true;
}

bool bluetooth_audio_port_client_impl::update_source_metadata( std::vector<playback_track_metadata> a_source_meta_data )
{
    return true;
}

bool bluetooth_audio_port_client_impl::update_sink_metadata( std::vector<record_track_metadata> a_source_meta_data )
{
    return true;
}

bool bluetooth_audio_port_client_impl::set_latency_mode( latency_mode a_latency )
{
    return true;
}

std::shared_ptr<bluetooth_audio_port_client> bluetooth_audio_port_client::create_aidl()
{
    static constexpr char kBluetoothAudioAidlServiceName[] =
        "android.hardware.bluetooth.audio.IBluetoothAudioProviderFactory/default";

    if( AServiceManager_isDeclared( kBluetoothAudioAidlServiceName ) )
        return std::make_shared<bluetooth_audio_port_client_impl>( kBluetoothAudioAidlServiceName );

    return std::shared_ptr<bluetooth_audio_port_client>();
}

}

