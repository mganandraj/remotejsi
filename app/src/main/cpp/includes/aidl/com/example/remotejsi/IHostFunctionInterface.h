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
#include <aidl/com/example/remotejsi/IValueCollectionInterface.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
class IHostFunctionInterface : public ::ndk::ICInterface {
public:
  static const char* descriptor;
  IHostFunctionInterface();
  virtual ~IHostFunctionInterface();



  static std::shared_ptr<IHostFunctionInterface> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IHostFunctionInterface>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IHostFunctionInterface>* instance);
  static bool setDefaultImpl(std::shared_ptr<IHostFunctionInterface> impl);
  static const std::shared_ptr<IHostFunctionInterface>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_thisVal, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& in_args, int64_t in_size, ::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IHostFunctionInterface> default_impl;
};
class IHostFunctionInterfaceDefault : public IHostFunctionInterface {
public:
  ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_thisVal, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& in_args, int64_t in_size, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
