#pragma once

#include "aidl/com/example/remotejsi/IManagerInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpManagerInterface : public ::ndk::BpCInterface<IManagerInterface> {
public:
  BpManagerInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpManagerInterface();

  ::ndk::ScopedAStatus ping() override;
  ::ndk::ScopedAStatus createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
