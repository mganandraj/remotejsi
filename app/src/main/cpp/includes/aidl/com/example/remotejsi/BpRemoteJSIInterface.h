#pragma once

#include "aidl/com/example/remotejsi/IRemoteJSIInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BpRemoteJSIInterface : public ::ndk::BpCInterface<IRemoteJSIInterface> {
public:
  BpRemoteJSIInterface(const ::ndk::SpAIBinder& binder);
  virtual ~BpRemoteJSIInterface();

  ::ndk::ScopedAStatus handshakeAck() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
