// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: binder_driver_data_link.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_binder_5fdriver_5fdata_5flink_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_binder_5fdriver_5fdata_5flink_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_binder_5fdriver_5fdata_5flink_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_binder_5fdriver_5fdata_5flink_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_binder_5fdriver_5fdata_5flink_2eproto;
namespace BinderDriverDataLink {
class MessageFromClient;
class MessageFromClientDefaultTypeInternal;
extern MessageFromClientDefaultTypeInternal _MessageFromClient_default_instance_;
class MessageFromServer;
class MessageFromServerDefaultTypeInternal;
extern MessageFromServerDefaultTypeInternal _MessageFromServer_default_instance_;
}  // namespace BinderDriverDataLink
PROTOBUF_NAMESPACE_OPEN
template<> ::BinderDriverDataLink::MessageFromClient* Arena::CreateMaybeMessage<::BinderDriverDataLink::MessageFromClient>(Arena*);
template<> ::BinderDriverDataLink::MessageFromServer* Arena::CreateMaybeMessage<::BinderDriverDataLink::MessageFromServer>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace BinderDriverDataLink {

// ===================================================================

class MessageFromServer :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:BinderDriverDataLink.MessageFromServer) */ {
 public:
  MessageFromServer();
  virtual ~MessageFromServer();

  MessageFromServer(const MessageFromServer& from);
  MessageFromServer(MessageFromServer&& from) noexcept
    : MessageFromServer() {
    *this = ::std::move(from);
  }

  inline MessageFromServer& operator=(const MessageFromServer& from) {
    CopyFrom(from);
    return *this;
  }
  inline MessageFromServer& operator=(MessageFromServer&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MessageFromServer& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageFromServer* internal_default_instance() {
    return reinterpret_cast<const MessageFromServer*>(
               &_MessageFromServer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MessageFromServer& a, MessageFromServer& b) {
    a.Swap(&b);
  }
  inline void Swap(MessageFromServer* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MessageFromServer* New() const final {
    return CreateMaybeMessage<MessageFromServer>(nullptr);
  }

  MessageFromServer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MessageFromServer>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MessageFromServer& from);
  void MergeFrom(const MessageFromServer& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageFromServer* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "BinderDriverDataLink.MessageFromServer";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_binder_5fdriver_5fdata_5flink_2eproto);
    return ::descriptor_table_binder_5fdriver_5fdata_5flink_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 3,
    kBufferFieldNumber = 4,
    kIdFieldNumber = 1,
    kTypeFieldNumber = 2,
  };
  // string msg = 3;
  void clear_msg();
  const std::string& msg() const;
  void set_msg(const std::string& value);
  void set_msg(std::string&& value);
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  std::string* mutable_msg();
  std::string* release_msg();
  void set_allocated_msg(std::string* msg);

  // bytes buffer = 4;
  void clear_buffer();
  const std::string& buffer() const;
  void set_buffer(const std::string& value);
  void set_buffer(std::string&& value);
  void set_buffer(const char* value);
  void set_buffer(const void* value, size_t size);
  std::string* mutable_buffer();
  std::string* release_buffer();
  void set_allocated_buffer(std::string* buffer);

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // uint32 type = 2;
  void clear_type();
  ::PROTOBUF_NAMESPACE_ID::uint32 type() const;
  void set_type(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // @@protoc_insertion_point(class_scope:BinderDriverDataLink.MessageFromServer)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr buffer_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_binder_5fdriver_5fdata_5flink_2eproto;
};
// -------------------------------------------------------------------

class MessageFromClient :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:BinderDriverDataLink.MessageFromClient) */ {
 public:
  MessageFromClient();
  virtual ~MessageFromClient();

  MessageFromClient(const MessageFromClient& from);
  MessageFromClient(MessageFromClient&& from) noexcept
    : MessageFromClient() {
    *this = ::std::move(from);
  }

  inline MessageFromClient& operator=(const MessageFromClient& from) {
    CopyFrom(from);
    return *this;
  }
  inline MessageFromClient& operator=(MessageFromClient&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const MessageFromClient& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageFromClient* internal_default_instance() {
    return reinterpret_cast<const MessageFromClient*>(
               &_MessageFromClient_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MessageFromClient& a, MessageFromClient& b) {
    a.Swap(&b);
  }
  inline void Swap(MessageFromClient* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline MessageFromClient* New() const final {
    return CreateMaybeMessage<MessageFromClient>(nullptr);
  }

  MessageFromClient* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MessageFromClient>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const MessageFromClient& from);
  void MergeFrom(const MessageFromClient& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageFromClient* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "BinderDriverDataLink.MessageFromClient";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_binder_5fdriver_5fdata_5flink_2eproto);
    return ::descriptor_table_binder_5fdriver_5fdata_5flink_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 3,
    kBufferFieldNumber = 4,
    kIdFieldNumber = 1,
    kTypeFieldNumber = 2,
  };
  // string msg = 3;
  void clear_msg();
  const std::string& msg() const;
  void set_msg(const std::string& value);
  void set_msg(std::string&& value);
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  std::string* mutable_msg();
  std::string* release_msg();
  void set_allocated_msg(std::string* msg);

  // bytes buffer = 4;
  void clear_buffer();
  const std::string& buffer() const;
  void set_buffer(const std::string& value);
  void set_buffer(std::string&& value);
  void set_buffer(const char* value);
  void set_buffer(const void* value, size_t size);
  std::string* mutable_buffer();
  std::string* release_buffer();
  void set_allocated_buffer(std::string* buffer);

  // uint64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // uint32 type = 2;
  void clear_type();
  ::PROTOBUF_NAMESPACE_ID::uint32 type() const;
  void set_type(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // @@protoc_insertion_point(class_scope:BinderDriverDataLink.MessageFromClient)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr buffer_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint32 type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_binder_5fdriver_5fdata_5flink_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MessageFromServer

// uint64 id = 1;
inline void MessageFromServer::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 MessageFromServer::id() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.id)
  return id_;
}
inline void MessageFromServer::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.id)
}

// uint32 type = 2;
inline void MessageFromServer::clear_type() {
  type_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MessageFromServer::type() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.type)
  return type_;
}
inline void MessageFromServer::set_type(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.type)
}

// string msg = 3;
inline void MessageFromServer::clear_msg() {
  msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageFromServer::msg() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.msg)
  return msg_.GetNoArena();
}
inline void MessageFromServer::set_msg(const std::string& value) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.msg)
}
inline void MessageFromServer::set_msg(std::string&& value) {
  
  msg_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:BinderDriverDataLink.MessageFromServer.msg)
}
inline void MessageFromServer::set_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:BinderDriverDataLink.MessageFromServer.msg)
}
inline void MessageFromServer::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:BinderDriverDataLink.MessageFromServer.msg)
}
inline std::string* MessageFromServer::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromServer.msg)
  return msg_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageFromServer::release_msg() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromServer.msg)
  
  return msg_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageFromServer::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromServer.msg)
}

// bytes buffer = 4;
inline void MessageFromServer::clear_buffer() {
  buffer_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageFromServer::buffer() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.buffer)
  return buffer_.GetNoArena();
}
inline void MessageFromServer::set_buffer(const std::string& value) {
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.buffer)
}
inline void MessageFromServer::set_buffer(std::string&& value) {
  
  buffer_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:BinderDriverDataLink.MessageFromServer.buffer)
}
inline void MessageFromServer::set_buffer(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:BinderDriverDataLink.MessageFromServer.buffer)
}
inline void MessageFromServer::set_buffer(const void* value, size_t size) {
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:BinderDriverDataLink.MessageFromServer.buffer)
}
inline std::string* MessageFromServer::mutable_buffer() {
  
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromServer.buffer)
  return buffer_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageFromServer::release_buffer() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromServer.buffer)
  
  return buffer_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageFromServer::set_allocated_buffer(std::string* buffer) {
  if (buffer != nullptr) {
    
  } else {
    
  }
  buffer_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), buffer);
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromServer.buffer)
}

// -------------------------------------------------------------------

// MessageFromClient

// uint64 id = 1;
inline void MessageFromClient::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 MessageFromClient::id() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.id)
  return id_;
}
inline void MessageFromClient::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.id)
}

// uint32 type = 2;
inline void MessageFromClient::clear_type() {
  type_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 MessageFromClient::type() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.type)
  return type_;
}
inline void MessageFromClient::set_type(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.type)
}

// string msg = 3;
inline void MessageFromClient::clear_msg() {
  msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageFromClient::msg() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.msg)
  return msg_.GetNoArena();
}
inline void MessageFromClient::set_msg(const std::string& value) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.msg)
}
inline void MessageFromClient::set_msg(std::string&& value) {
  
  msg_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:BinderDriverDataLink.MessageFromClient.msg)
}
inline void MessageFromClient::set_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:BinderDriverDataLink.MessageFromClient.msg)
}
inline void MessageFromClient::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:BinderDriverDataLink.MessageFromClient.msg)
}
inline std::string* MessageFromClient::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromClient.msg)
  return msg_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageFromClient::release_msg() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromClient.msg)
  
  return msg_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageFromClient::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromClient.msg)
}

// bytes buffer = 4;
inline void MessageFromClient::clear_buffer() {
  buffer_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& MessageFromClient::buffer() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.buffer)
  return buffer_.GetNoArena();
}
inline void MessageFromClient::set_buffer(const std::string& value) {
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.buffer)
}
inline void MessageFromClient::set_buffer(std::string&& value) {
  
  buffer_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:BinderDriverDataLink.MessageFromClient.buffer)
}
inline void MessageFromClient::set_buffer(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:BinderDriverDataLink.MessageFromClient.buffer)
}
inline void MessageFromClient::set_buffer(const void* value, size_t size) {
  
  buffer_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:BinderDriverDataLink.MessageFromClient.buffer)
}
inline std::string* MessageFromClient::mutable_buffer() {
  
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromClient.buffer)
  return buffer_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* MessageFromClient::release_buffer() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromClient.buffer)
  
  return buffer_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void MessageFromClient::set_allocated_buffer(std::string* buffer) {
  if (buffer != nullptr) {
    
  } else {
    
  }
  buffer_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), buffer);
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromClient.buffer)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace BinderDriverDataLink

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_binder_5fdriver_5fdata_5flink_2eproto