#pragma once
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace Json
{
    class Value;
}

struct binder_transaction_data;

namespace data_link
{

enum class connection_status : uint8_t
{
    disconnected,
    connecting,
    connected,
    disconnecting
};

enum class binder_message_type : uint32_t
{
    invalid = 0,
    ping_service_manager,
    register_service,
    binder_transaction,
};

class binder_ipc_message
{

public:

    static constexpr std::string_view s_m_is_from_service_manager_key{ "is_from_service_manager" };
    static constexpr std::string_view s_end_point_key{ "endpoint" };
    static constexpr std::string_view s_raw_buffer_size_key{ "raw_buffer_size" };
    static constexpr std::string_view s_source_connection_id_key{ "source_connection_id" };
    static constexpr std::string_view s_debug_info_key{ "debug_info" };

    binder_ipc_message( bool a_auto_incread_id = true );

    virtual ~binder_ipc_message(){}

    virtual void fill_json_value( Json::Value& a_value )const noexcept;

    virtual bool parse_from_json( Json::Value& a_value );

    bool parse_from_message( std::string const& a_msg );

    std::string to_string();

    uint64_t get_id()const
    {
        return m_id;
    }

    void set_id( uint64_t a_id )
    {
        m_id = a_id;
    }

    binder_message_type get_type()const
    {
        return m_type;
    }

    void set_endpoint( std::string a_endpoint )
    {
        m_endpoint = a_endpoint;
    }

    std::string const& get_endpoint()const noexcept
    {
        return m_endpoint;
    }

    void set_from_client( bool a_from_client = true )
    {
        m_is_from_service_manager = a_from_client;
    }

    bool is_from_client()const noexcept
    {
        return m_is_from_service_manager;
    }

    std::string extract_raw_buffer()
    {
        m_raw_buffer_size = 0;
        return std::move( m_raw_buffer );
    }

    uint32_t get_raw_buffer_size()
    {
        return m_raw_buffer_size;
    }

    void set_raw_buffer( std::string a_buffer )
    {
        m_raw_buffer = std::move( a_buffer );
        m_raw_buffer_size = m_raw_buffer.size();
    }

    std::string const& get_source_connection_id()const
    {
        return m_source_connection_id;
    }

    std::string const& get_debug_info()const noexcept
    {
        return m_debug_info;
    }

    void set_debug_info( std::string a_debug_info )
    {
        m_debug_info = a_debug_info;
    }

protected:

    void set_type( binder_message_type a_type )
    {
        m_type = a_type;
    }

    void set_connection_name( std::string a_name )
    {
        m_source_connection_id = a_name;
    }

private:

    static std::atomic<uint64_t> s_next_id;

    uint64_t m_id = 0;
    binder_message_type m_type = binder_message_type::invalid;
    bool m_is_from_service_manager = false;
    std::string m_endpoint; // from or to which endpoint
    uint32_t m_raw_buffer_size = 0;
    std::string m_raw_buffer;
    std::string m_source_connection_id; // who send this message
    std::string m_debug_info; // just used for debug. maybe empty.
};

struct binder_ping_message : public binder_ipc_message
{
    binder_ping_message()
    {
        set_type( binder_message_type::ping_service_manager );
    }

    void fill_json_value( Json::Value& a_value )const noexcept override;

    bool parse_from_json( Json::Value& a_value )override;

    static constexpr std::string_view s_ping_message_key{ "m_ping_message" };
    std::string m_ping_message;
};

struct register_service_message : public binder_ipc_message
{
    register_service_message()
    {
        set_type( binder_message_type::register_service );
    }

    void fill_json_value( Json::Value& a_value )const noexcept override;

    bool parse_from_json( Json::Value& a_value )override;

    static constexpr std::string_view s_service_name_key{ "service_name" };
    static constexpr std::string_view s_register_result_key{ "register_result" };
    std::string m_service_name;
    uint32_t m_register_result = 0; // register result. service manager will fill it.
};

struct binder_transaction_message : public binder_ipc_message
{

    enum class transaction_state : uint32_t
    {
        init,       // this transaction is inited. who send this message, who set this value
        handling,   // this transaction is handling. who handle this message, who set this value
        completed   // this transaction is done.
    };

    static std::string state_to_string( transaction_state a_state );

    binder_transaction_message( bool a_auto_incread_id = true )
        : binder_ipc_message( a_auto_incread_id )
    {
        set_type( binder_message_type::binder_transaction );
    }

    void fill_json_value( Json::Value& a_value )const noexcept override;

    bool parse_from_json( Json::Value& a_value )override;

    void init_transaction_context( binder_transaction_data* a_binder_transaction_data/*in*/);

    void parse_transaction_context( binder_transaction_data* a_binder_transaction_data/*out*/);

    static constexpr std::string_view s_tr_code_key{ "tr_code" };
    static constexpr std::string_view s_tr_data_ptr_offsets_key{ "tr_data_ptr_offsets" };
    static constexpr std::string_view s_tr_offsets_size_key{ "tr_offsets_size" };
    static constexpr std::string_view s_is_reply_key{ "is_reply" };
    static constexpr std::string_view s_transaction_state_key{ "transaction_state" };
    static constexpr std::string_view s_tr_service_name_key{ "tr_service_name" };

    transaction_state m_transaction_state = transaction_state::init; // When reply this message, means that this trasaction has been done.
    uint32_t m_tr_code = 0;
    uint32_t m_tr_offsets_size = 0;
    uint32_t m_tr_target_binder_handle = 0;
    uint32_t m_tr_data_ptr_offsets = 0;
    std::string m_tr_service_name; // which service should handle this message
    bool m_is_reply = false;
};

std::shared_ptr<binder_ipc_message> create( binder_message_type a_msg_type, bool a_auto_incread_id = true );

using message_callback = std::function<void(std::shared_ptr<binder_ipc_message>)>;

}

