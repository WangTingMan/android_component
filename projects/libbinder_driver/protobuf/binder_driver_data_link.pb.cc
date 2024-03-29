// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: binder_driver_data_link.proto

#include "binder_driver_data_link.pb.h"

#include <algorithm>
#include <cstdint>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace BinderDriverDataLink {
PROTOBUF_CONSTEXPR MessageFromServer::MessageFromServer(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.msg_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.buffer_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.id_)*/::uint64_t{0u}
  , /*decltype(_impl_.type_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct MessageFromServerDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MessageFromServerDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MessageFromServerDefaultTypeInternal() {}
  union {  // NOLINT(misc-non-private-member-variables-in-classes)
    MessageFromServer _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MessageFromServerDefaultTypeInternal _MessageFromServer_default_instance_;
PROTOBUF_CONSTEXPR MessageFromClient::MessageFromClient(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.msg_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.buffer_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.id_)*/::uint64_t{0u}
  , /*decltype(_impl_.type_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct MessageFromClientDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MessageFromClientDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MessageFromClientDefaultTypeInternal() {}
  union {  // NOLINT(misc-non-private-member-variables-in-classes)
    MessageFromClient _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MessageFromClientDefaultTypeInternal _MessageFromClient_default_instance_;
}  // namespace BinderDriverDataLink
static ::_pb::Metadata file_level_metadata_binder_5fdriver_5fdata_5flink_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_binder_5fdriver_5fdata_5flink_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_binder_5fdriver_5fdata_5flink_2eproto = nullptr;

const ::uint32_t TableStruct_binder_5fdriver_5fdata_5flink_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromServer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromServer, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromServer, _impl_.type_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromServer, _impl_.msg_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromServer, _impl_.buffer_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromClient, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromClient, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromClient, _impl_.type_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromClient, _impl_.msg_),
  PROTOBUF_FIELD_OFFSET(::BinderDriverDataLink::MessageFromClient, _impl_.buffer_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::BinderDriverDataLink::MessageFromServer)},
  { 10, -1, -1, sizeof(::BinderDriverDataLink::MessageFromClient)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::BinderDriverDataLink::_MessageFromServer_default_instance_._instance,
  &::BinderDriverDataLink::_MessageFromClient_default_instance_._instance,
};

const char descriptor_table_protodef_binder_5fdriver_5fdata_5flink_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\035binder_driver_data_link.proto\022\024BinderD"
  "riverDataLink\"J\n\021MessageFromServer\022\n\n\002id"
  "\030\001 \001(\004\022\014\n\004type\030\002 \001(\r\022\013\n\003msg\030\003 \001(\t\022\016\n\006buf"
  "fer\030\004 \001(\014\"J\n\021MessageFromClient\022\n\n\002id\030\001 \001"
  "(\004\022\014\n\004type\030\002 \001(\r\022\013\n\003msg\030\003 \001(\t\022\016\n\006buffer\030"
  "\004 \001(\0142\214\001\n\023BinderDriverService\022u\n\033Bidirec"
  "tionalStreamMessages\022\'.BinderDriverDataL"
  "ink.MessageFromClient\032\'.BinderDriverData"
  "Link.MessageFromServer\"\000(\0010\001B5\n\025io.grpc."
  "binder.driverB\024BinderDriverDataLinkP\001\242\002\003"
  "BNDb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_binder_5fdriver_5fdata_5flink_2eproto = {
    false, false, 411, descriptor_table_protodef_binder_5fdriver_5fdata_5flink_2eproto,
    "binder_driver_data_link.proto",
    &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_binder_5fdriver_5fdata_5flink_2eproto::offsets,
    file_level_metadata_binder_5fdriver_5fdata_5flink_2eproto, file_level_enum_descriptors_binder_5fdriver_5fdata_5flink_2eproto,
    file_level_service_descriptors_binder_5fdriver_5fdata_5flink_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_getter() {
  return &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_binder_5fdriver_5fdata_5flink_2eproto(&descriptor_table_binder_5fdriver_5fdata_5flink_2eproto);
namespace BinderDriverDataLink {

// ===================================================================

class MessageFromServer::_Internal {
 public:
};

MessageFromServer::MessageFromServer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:BinderDriverDataLink.MessageFromServer)
}
MessageFromServer::MessageFromServer(const MessageFromServer& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MessageFromServer* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.msg_){}
    , decltype(_impl_.buffer_){}
    , decltype(_impl_.id_){}
    , decltype(_impl_.type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_msg().empty()) {
    _this->_impl_.msg_.Set(from._internal_msg(), 
      _this->GetArenaForAllocation());
  }
  _impl_.buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_buffer().empty()) {
    _this->_impl_.buffer_.Set(from._internal_buffer(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.id_, &from._impl_.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.type_) -
    reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  // @@protoc_insertion_point(copy_constructor:BinderDriverDataLink.MessageFromServer)
}

inline void MessageFromServer::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.msg_){}
    , decltype(_impl_.buffer_){}
    , decltype(_impl_.id_){::uint64_t{0u}}
    , decltype(_impl_.type_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

MessageFromServer::~MessageFromServer() {
  // @@protoc_insertion_point(destructor:BinderDriverDataLink.MessageFromServer)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MessageFromServer::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.msg_.Destroy();
  _impl_.buffer_.Destroy();
}

void MessageFromServer::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MessageFromServer::Clear() {
// @@protoc_insertion_point(message_clear_start:BinderDriverDataLink.MessageFromServer)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.msg_.ClearToEmpty();
  _impl_.buffer_.ClearToEmpty();
  ::memset(&_impl_.id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.type_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MessageFromServer::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // uint32 type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 16)) {
          _impl_.type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // string msg = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_msg();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "BinderDriverDataLink.MessageFromServer.msg"));
        } else {
          goto handle_unusual;
        }
        continue;
      // bytes buffer = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_buffer();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* MessageFromServer::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:BinderDriverDataLink.MessageFromServer)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // uint32 type = 2;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_type(), target);
  }

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "BinderDriverDataLink.MessageFromServer.msg");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_msg(), target);
  }

  // bytes buffer = 4;
  if (!this->_internal_buffer().empty()) {
    target = stream->WriteBytesMaybeAliased(
        4, this->_internal_buffer(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:BinderDriverDataLink.MessageFromServer)
  return target;
}

size_t MessageFromServer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:BinderDriverDataLink.MessageFromServer)
  size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  // bytes buffer = 4;
  if (!this->_internal_buffer().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_buffer());
  }

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_id());
  }

  // uint32 type = 2;
  if (this->_internal_type() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MessageFromServer::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MessageFromServer::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MessageFromServer::GetClassData() const { return &_class_data_; }


void MessageFromServer::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MessageFromServer*>(&to_msg);
  auto& from = static_cast<const MessageFromServer&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:BinderDriverDataLink.MessageFromServer)
  GOOGLE_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_msg().empty()) {
    _this->_internal_set_msg(from._internal_msg());
  }
  if (!from._internal_buffer().empty()) {
    _this->_internal_set_buffer(from._internal_buffer());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  if (from._internal_type() != 0) {
    _this->_internal_set_type(from._internal_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MessageFromServer::CopyFrom(const MessageFromServer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:BinderDriverDataLink.MessageFromServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageFromServer::IsInitialized() const {
  return true;
}

void MessageFromServer::InternalSwap(MessageFromServer* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.msg_, lhs_arena,
      &other->_impl_.msg_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.buffer_, lhs_arena,
      &other->_impl_.buffer_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MessageFromServer, _impl_.type_)
      + sizeof(MessageFromServer::_impl_.type_)  // NOLINT
      - PROTOBUF_FIELD_OFFSET(MessageFromServer, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MessageFromServer::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_getter, &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_once,
      file_level_metadata_binder_5fdriver_5fdata_5flink_2eproto[0]);
}

// ===================================================================

class MessageFromClient::_Internal {
 public:
};

MessageFromClient::MessageFromClient(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:BinderDriverDataLink.MessageFromClient)
}
MessageFromClient::MessageFromClient(const MessageFromClient& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MessageFromClient* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.msg_){}
    , decltype(_impl_.buffer_){}
    , decltype(_impl_.id_){}
    , decltype(_impl_.type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_msg().empty()) {
    _this->_impl_.msg_.Set(from._internal_msg(), 
      _this->GetArenaForAllocation());
  }
  _impl_.buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_buffer().empty()) {
    _this->_impl_.buffer_.Set(from._internal_buffer(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.id_, &from._impl_.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.type_) -
    reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  // @@protoc_insertion_point(copy_constructor:BinderDriverDataLink.MessageFromClient)
}

inline void MessageFromClient::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.msg_){}
    , decltype(_impl_.buffer_){}
    , decltype(_impl_.id_){::uint64_t{0u}}
    , decltype(_impl_.type_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.msg_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.msg_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.buffer_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.buffer_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

MessageFromClient::~MessageFromClient() {
  // @@protoc_insertion_point(destructor:BinderDriverDataLink.MessageFromClient)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MessageFromClient::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.msg_.Destroy();
  _impl_.buffer_.Destroy();
}

void MessageFromClient::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MessageFromClient::Clear() {
// @@protoc_insertion_point(message_clear_start:BinderDriverDataLink.MessageFromClient)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.msg_.ClearToEmpty();
  _impl_.buffer_.ClearToEmpty();
  ::memset(&_impl_.id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.type_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MessageFromClient::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // uint32 type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 16)) {
          _impl_.type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // string msg = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_msg();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "BinderDriverDataLink.MessageFromClient.msg"));
        } else {
          goto handle_unusual;
        }
        continue;
      // bytes buffer = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_buffer();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* MessageFromClient::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:BinderDriverDataLink.MessageFromClient)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt64ToArray(1, this->_internal_id(), target);
  }

  // uint32 type = 2;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_type(), target);
  }

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "BinderDriverDataLink.MessageFromClient.msg");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_msg(), target);
  }

  // bytes buffer = 4;
  if (!this->_internal_buffer().empty()) {
    target = stream->WriteBytesMaybeAliased(
        4, this->_internal_buffer(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:BinderDriverDataLink.MessageFromClient)
  return target;
}

size_t MessageFromClient::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:BinderDriverDataLink.MessageFromClient)
  size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string msg = 3;
  if (!this->_internal_msg().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  // bytes buffer = 4;
  if (!this->_internal_buffer().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_buffer());
  }

  // uint64 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt64SizePlusOne(this->_internal_id());
  }

  // uint32 type = 2;
  if (this->_internal_type() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MessageFromClient::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MessageFromClient::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MessageFromClient::GetClassData() const { return &_class_data_; }


void MessageFromClient::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MessageFromClient*>(&to_msg);
  auto& from = static_cast<const MessageFromClient&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:BinderDriverDataLink.MessageFromClient)
  GOOGLE_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_msg().empty()) {
    _this->_internal_set_msg(from._internal_msg());
  }
  if (!from._internal_buffer().empty()) {
    _this->_internal_set_buffer(from._internal_buffer());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  if (from._internal_type() != 0) {
    _this->_internal_set_type(from._internal_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MessageFromClient::CopyFrom(const MessageFromClient& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:BinderDriverDataLink.MessageFromClient)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageFromClient::IsInitialized() const {
  return true;
}

void MessageFromClient::InternalSwap(MessageFromClient* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.msg_, lhs_arena,
      &other->_impl_.msg_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.buffer_, lhs_arena,
      &other->_impl_.buffer_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MessageFromClient, _impl_.type_)
      + sizeof(MessageFromClient::_impl_.type_)  // NOLINT
      - PROTOBUF_FIELD_OFFSET(MessageFromClient, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MessageFromClient::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_getter, &descriptor_table_binder_5fdriver_5fdata_5flink_2eproto_once,
      file_level_metadata_binder_5fdriver_5fdata_5flink_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace BinderDriverDataLink
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::BinderDriverDataLink::MessageFromServer*
Arena::CreateMaybeMessage< ::BinderDriverDataLink::MessageFromServer >(Arena* arena) {
  return Arena::CreateMessageInternal< ::BinderDriverDataLink::MessageFromServer >(arena);
}
template<> PROTOBUF_NOINLINE ::BinderDriverDataLink::MessageFromClient*
Arena::CreateMaybeMessage< ::BinderDriverDataLink::MessageFromClient >(Arena* arena) {
  return Arena::CreateMessageInternal< ::BinderDriverDataLink::MessageFromClient >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
