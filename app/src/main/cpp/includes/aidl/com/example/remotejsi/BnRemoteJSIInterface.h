#pragma once

#include "aidl/com/example/remotejsi/IRemoteJSIInterface.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class BnRemoteJSIInterface : public ::ndk::BnCInterface<IRemoteJSIInterface> {
public:
  BnRemoteJSIInterface();
  virtual ~BnRemoteJSIInterface();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
