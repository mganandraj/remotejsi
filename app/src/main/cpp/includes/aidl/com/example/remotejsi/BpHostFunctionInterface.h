#pragma once

#include "aidl/com/example/remotejsi/IHostFunctionInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpHostFunctionInterface : public ::ndk::BpCInterface<IHostFunctionInterface> {
public:
  BpHostFunctionInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpHostFunctionInterface();

  ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_thisVal, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& in_args, int64_t in_size, ::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
