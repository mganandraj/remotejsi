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
class IJSIStringStaticsInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IJSIStringStaticsInterface();
  virtual ~IJSIStringStaticsInterface();



  static std::shared_ptr<IJSIStringStaticsInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIStringStaticsInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIStringStaticsInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IJSIStringStaticsInterface> impl);
  static const std::shared_ptr<IJSIStringStaticsInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createFromNullTerminatedAscii(const std::vector<int8_t>& in_chars, ::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIStringStaticsInterface> default_impl;
};
class IJSIStringStaticsInterfaceDefault : public IJSIStringStaticsInterface {
public:
  ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromNullTerminatedAscii(const std::vector<int8_t>& in_chars, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
