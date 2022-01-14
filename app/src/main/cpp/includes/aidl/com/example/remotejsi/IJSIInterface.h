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
class IJSIInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIInterface();
  virtual ~IJSIInterface();



  static std::shared_ptr<IJSIInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIInterface> impl);
  static const std::shared_ptr<IJSIInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus eval(const std::string& in_aString, std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIInterface> default_impl;
};
class IJSIInterfaceDefault : public IJSIInterface {
public:
  ::ndk::ScopedAStatus eval(const std::string& in_aString, std::string* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
