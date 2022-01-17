#pragma once

#include "aidl/com/example/remotejsi/IHostObjectInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpHostObjectInterface : public ::ndk::BpCInterface<IHostObjectInterface> {
public:
  BpHostObjectInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpHostObjectInterface();

  ::ndk::ScopedAStatus get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) override;
  ::ndk::ScopedAStatus getPropertyNames() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
