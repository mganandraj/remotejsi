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
class IManagerInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IManagerInterface();
  virtual ~IManagerInterface();



  static std::shared_ptr<IManagerInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IManagerInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IManagerInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IManagerInterface> impl);
  static const std::shared_ptr<IManagerInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus ping() = 0;
  virtual ::ndk::ScopedAStatus createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IManagerInterface> default_impl;
};
class IManagerInterfaceDefault : public IManagerInterface {
public:
  ::ndk::ScopedAStatus ping() override;
  ::ndk::ScopedAStatus createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
