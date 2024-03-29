// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: binder_driver_data_link.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_binder_5fdriver_5fdata_5flink_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_binder_5fdriver_5fdata_5flink_2eproto

#include <cstdint>
#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021007 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
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
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_binder_5fdriver_5fdata_5flink_2eproto;
namespace BinderDriverDataLink {
class MessageFromClient;
struct MessageFromClientDefaultTypeInternal;
extern MessageFromClientDefaultTypeInternal _MessageFromClient_default_instance_;
class MessageFromServer;
struct MessageFromServerDefaultTypeInternal;
extern MessageFromServerDefaultTypeInternal _MessageFromServer_default_instance_;
}  // namespace BinderDriverDataLink
PROTOBUF_NAMESPACE_OPEN
template<> ::BinderDriverDataLink::MessageFromClient* Arena::CreateMaybeMessage<::BinderDriverDataLink::MessageFromClient>(Arena*);
template<> ::BinderDriverDataLink::MessageFromServer* Arena::CreateMaybeMessage<::BinderDriverDataLink::MessageFromServer>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace BinderDriverDataLink {

// ===================================================================

class MessageFromServer final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:BinderDriverDataLink.MessageFromServer) */ {
 public:
  inline MessageFromServer() : MessageFromServer(nullptr) {}
  ~MessageFromServer() override;
  explicit PROTOBUF_CONSTEXPR MessageFromServer(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MessageFromServer(const MessageFromServer& from);
  MessageFromServer(MessageFromServer&& from) noexcept
    : MessageFromServer() {
    *this = ::std::move(from);
  }

  inline MessageFromServer& operator=(const MessageFromServer& from) {
    if (this == &from) return *this;
    CopyFrom(from);
    return *this;
  }
  inline MessageFromServer& operator=(MessageFromServer&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MessageFromServer& default_instance() {
    return *internal_default_instance();
  }
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
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MessageFromServer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MessageFromServer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MessageFromServer>(arena);
  }
  MessageFromServer* New() const {
    return New(nullptr);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MessageFromServer& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MessageFromServer& from) {
    MessageFromServer::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageFromServer* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "BinderDriverDataLink.MessageFromServer";
  }
  protected:
  explicit MessageFromServer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

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
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // bytes buffer = 4;
  void clear_buffer();
  const std::string& buffer() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_buffer(ArgT0&& arg0, ArgT... args);
  std::string* mutable_buffer();
  PROTOBUF_NODISCARD std::string* release_buffer();
  void set_allocated_buffer(std::string* buffer);
  private:
  const std::string& _internal_buffer() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_buffer(const std::string& value);
  std::string* _internal_mutable_buffer();
  public:

  // uint64 id = 1;
  void clear_id();
  ::uint64_t id() const;
  void set_id(::uint64_t value);
  private:
  ::uint64_t _internal_id() const;
  void _internal_set_id(::uint64_t value);
  public:

  // uint32 type = 2;
  void clear_type();
  ::uint32_t type() const;
  void set_type(::uint32_t value);
  private:
  ::uint32_t _internal_type() const;
  void _internal_set_type(::uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:BinderDriverDataLink.MessageFromServer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr buffer_;
    ::uint64_t id_;
    ::uint32_t type_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_binder_5fdriver_5fdata_5flink_2eproto;
};
// -------------------------------------------------------------------

class MessageFromClient final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:BinderDriverDataLink.MessageFromClient) */ {
 public:
  inline MessageFromClient() : MessageFromClient(nullptr) {}
  ~MessageFromClient() override;
  explicit PROTOBUF_CONSTEXPR MessageFromClient(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MessageFromClient(const MessageFromClient& from);
  MessageFromClient(MessageFromClient&& from) noexcept
    : MessageFromClient() {
    *this = ::std::move(from);
  }

  inline MessageFromClient& operator=(const MessageFromClient& from) {
    if (this == &from) return *this;
    CopyFrom(from);
    return *this;
  }
  inline MessageFromClient& operator=(MessageFromClient&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MessageFromClient& default_instance() {
    return *internal_default_instance();
  }
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
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MessageFromClient* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MessageFromClient* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<MessageFromClient>(arena);
  }
  MessageFromClient* New() const {
    return New(nullptr);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MessageFromClient& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MessageFromClient& from) {
    MessageFromClient::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageFromClient* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "BinderDriverDataLink.MessageFromClient";
  }
  protected:
  explicit MessageFromClient(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

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
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // bytes buffer = 4;
  void clear_buffer();
  const std::string& buffer() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_buffer(ArgT0&& arg0, ArgT... args);
  std::string* mutable_buffer();
  PROTOBUF_NODISCARD std::string* release_buffer();
  void set_allocated_buffer(std::string* buffer);
  private:
  const std::string& _internal_buffer() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_buffer(const std::string& value);
  std::string* _internal_mutable_buffer();
  public:

  // uint64 id = 1;
  void clear_id();
  ::uint64_t id() const;
  void set_id(::uint64_t value);
  private:
  ::uint64_t _internal_id() const;
  void _internal_set_id(::uint64_t value);
  public:

  // uint32 type = 2;
  void clear_type();
  ::uint32_t type() const;
  void set_type(::uint32_t value);
  private:
  ::uint32_t _internal_type() const;
  void _internal_set_type(::uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:BinderDriverDataLink.MessageFromClient)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr buffer_;
    ::uint64_t id_;
    ::uint32_t type_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
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
  _impl_.id_ = ::uint64_t{0u};
}
inline ::uint64_t MessageFromServer::_internal_id() const {
  return _impl_.id_;
}
inline ::uint64_t MessageFromServer::id() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.id)
  return _internal_id();
}
inline void MessageFromServer::_internal_set_id(::uint64_t value) {
  
  _impl_.id_ = value;
}
inline void MessageFromServer::set_id(::uint64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.id)
}

// uint32 type = 2;
inline void MessageFromServer::clear_type() {
  _impl_.type_ = 0u;
}
inline ::uint32_t MessageFromServer::_internal_type() const {
  return _impl_.type_;
}
inline ::uint32_t MessageFromServer::type() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.type)
  return _internal_type();
}
inline void MessageFromServer::_internal_set_type(::uint32_t value) {
  
  _impl_.type_ = value;
}
inline void MessageFromServer::set_type(::uint32_t value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.type)
}

// string msg = 3;
inline void MessageFromServer::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& MessageFromServer::msg() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MessageFromServer::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.msg)
}
inline std::string* MessageFromServer::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromServer.msg)
  return _s;
}
inline const std::string& MessageFromServer::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void MessageFromServer::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* MessageFromServer::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* MessageFromServer::release_msg() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromServer.msg)
  return _impl_.msg_.Release();
}
inline void MessageFromServer::set_allocated_msg(std::string* msg) {
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromServer.msg)
}

// bytes buffer = 4;
inline void MessageFromServer::clear_buffer() {
  _impl_.buffer_.ClearToEmpty();
}
inline const std::string& MessageFromServer::buffer() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromServer.buffer)
  return _internal_buffer();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MessageFromServer::set_buffer(ArgT0&& arg0, ArgT... args) {
 
 _impl_.buffer_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromServer.buffer)
}
inline std::string* MessageFromServer::mutable_buffer() {
  std::string* _s = _internal_mutable_buffer();
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromServer.buffer)
  return _s;
}
inline const std::string& MessageFromServer::_internal_buffer() const {
  return _impl_.buffer_.Get();
}
inline void MessageFromServer::_internal_set_buffer(const std::string& value) {
  
  _impl_.buffer_.Set(value, GetArenaForAllocation());
}
inline std::string* MessageFromServer::_internal_mutable_buffer() {
  
  return _impl_.buffer_.Mutable(GetArenaForAllocation());
}
inline std::string* MessageFromServer::release_buffer() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromServer.buffer)
  return _impl_.buffer_.Release();
}
inline void MessageFromServer::set_allocated_buffer(std::string* buffer) {
  _impl_.buffer_.SetAllocated(buffer, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.buffer_.IsDefault()) {
    _impl_.buffer_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromServer.buffer)
}

// -------------------------------------------------------------------

// MessageFromClient

// uint64 id = 1;
inline void MessageFromClient::clear_id() {
  _impl_.id_ = ::uint64_t{0u};
}
inline ::uint64_t MessageFromClient::_internal_id() const {
  return _impl_.id_;
}
inline ::uint64_t MessageFromClient::id() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.id)
  return _internal_id();
}
inline void MessageFromClient::_internal_set_id(::uint64_t value) {
  
  _impl_.id_ = value;
}
inline void MessageFromClient::set_id(::uint64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.id)
}

// uint32 type = 2;
inline void MessageFromClient::clear_type() {
  _impl_.type_ = 0u;
}
inline ::uint32_t MessageFromClient::_internal_type() const {
  return _impl_.type_;
}
inline ::uint32_t MessageFromClient::type() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.type)
  return _internal_type();
}
inline void MessageFromClient::_internal_set_type(::uint32_t value) {
  
  _impl_.type_ = value;
}
inline void MessageFromClient::set_type(::uint32_t value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.type)
}

// string msg = 3;
inline void MessageFromClient::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& MessageFromClient::msg() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MessageFromClient::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.msg)
}
inline std::string* MessageFromClient::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromClient.msg)
  return _s;
}
inline const std::string& MessageFromClient::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void MessageFromClient::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* MessageFromClient::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* MessageFromClient::release_msg() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromClient.msg)
  return _impl_.msg_.Release();
}
inline void MessageFromClient::set_allocated_msg(std::string* msg) {
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:BinderDriverDataLink.MessageFromClient.msg)
}

// bytes buffer = 4;
inline void MessageFromClient::clear_buffer() {
  _impl_.buffer_.ClearToEmpty();
}
inline const std::string& MessageFromClient::buffer() const {
  // @@protoc_insertion_point(field_get:BinderDriverDataLink.MessageFromClient.buffer)
  return _internal_buffer();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MessageFromClient::set_buffer(ArgT0&& arg0, ArgT... args) {
 
 _impl_.buffer_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:BinderDriverDataLink.MessageFromClient.buffer)
}
inline std::string* MessageFromClient::mutable_buffer() {
  std::string* _s = _internal_mutable_buffer();
  // @@protoc_insertion_point(field_mutable:BinderDriverDataLink.MessageFromClient.buffer)
  return _s;
}
inline const std::string& MessageFromClient::_internal_buffer() const {
  return _impl_.buffer_.Get();
}
inline void MessageFromClient::_internal_set_buffer(const std::string& value) {
  
  _impl_.buffer_.Set(value, GetArenaForAllocation());
}
inline std::string* MessageFromClient::_internal_mutable_buffer() {
  
  return _impl_.buffer_.Mutable(GetArenaForAllocation());
}
inline std::string* MessageFromClient::release_buffer() {
  // @@protoc_insertion_point(field_release:BinderDriverDataLink.MessageFromClient.buffer)
  return _impl_.buffer_.Release();
}
inline void MessageFromClient::set_allocated_buffer(std::string* buffer) {
  _impl_.buffer_.SetAllocated(buffer, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.buffer_.IsDefault()) {
    _impl_.buffer_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
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
