#pragma once

#include <android/binder_interface_utils.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class IRemoteJSIInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IRemoteJSIInterface();
  virtual ~IRemoteJSIInterface();



  static std::shared_ptr<IRemoteJSIInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IRemoteJSIInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IRemoteJSIInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IRemoteJSIInterface> impl);
  static const std::shared_ptr<IRemoteJSIInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus handshakeAck() = 0;
private:
  static std::shared_ptr<IRemoteJSIInterface> default_impl;
};
class IRemoteJSIInterfaceDefault : public IRemoteJSIInterface {
public:
  ::ndk::ScopedAStatus handshakeAck() override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
