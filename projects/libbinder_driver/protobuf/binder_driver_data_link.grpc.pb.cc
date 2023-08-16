// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: binder_driver_data_link.proto

#include "binder_driver_data_link.pb.h"
#include "binder_driver_data_link.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace BinderDriverDataLink {

static const char* BinderDriverService_method_names[] = {
  "/BinderDriverDataLink.BinderDriverService/BidirectionalStreamMessages",
};

std::unique_ptr< BinderDriverService::Stub> BinderDriverService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BinderDriverService::Stub> stub(new BinderDriverService::Stub(channel));
  return stub;
}

BinderDriverService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_BidirectionalStreamMessages_(BinderDriverService_method_names[0], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>* BinderDriverService::Stub::BidirectionalStreamMessagesRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>::Create(channel_.get(), rpcmethod_BidirectionalStreamMessages_, context);
}

::grpc::ClientAsyncReaderWriter< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>* BinderDriverService::Stub::AsyncBidirectionalStreamMessagesRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_BidirectionalStreamMessages_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>* BinderDriverService::Stub::PrepareAsyncBidirectionalStreamMessagesRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_BidirectionalStreamMessages_, context, false, nullptr);
}

BinderDriverService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BinderDriverService_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< BinderDriverService::Service, ::BinderDriverDataLink::MessageFromClient, ::BinderDriverDataLink::MessageFromServer>(
          std::mem_fn(&BinderDriverService::Service::BidirectionalStreamMessages), this)));
}

BinderDriverService::Service::~Service() {
}

::grpc::Status BinderDriverService::Service::BidirectionalStreamMessages(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::BinderDriverDataLink::MessageFromServer, ::BinderDriverDataLink::MessageFromClient>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace BinderDriverDataLink
