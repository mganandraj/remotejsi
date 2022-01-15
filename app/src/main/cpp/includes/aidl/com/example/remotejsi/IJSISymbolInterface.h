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
class IJSISymbolInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSISymbolInterface();
  virtual ~IJSISymbolInterface();



  static std::shared_ptr<IJSISymbolInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSISymbolInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSISymbolInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSISymbolInterface> impl);
  static const std::shared_ptr<IJSISymbolInterface>& getDefaultImpl();
private:
  static std::shared_ptr<IJSISymbolInterface> default_impl;
};
class IJSISymbolInterfaceDefault : public IJSISymbolInterface {
public:
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
