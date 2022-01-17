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
  virtual ::ndk::ScopedAStatus eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus cloneValue(int8_t in_valueType, bool in_boolValue, double in_doubleValue, const ::ndk::SpAIBinder& in_pointerBinder, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_bytes, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createValueCollection(::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createFunctionFromHostFunction(const ::ndk::SpAIBinder& in_hostFunct, const ::ndk::SpAIBinder& in_propId, int64_t in_paramCount, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_func, const ::ndk::SpAIBinder& in_thisObj, const ::ndk::SpAIBinder& in_args, int64_t in_argsCount, ::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus callAsConstructor(const ::ndk::SpAIBinder& in_func, const ::ndk::SpAIBinder& in_args, int64_t in_argsCount, ::ndk::SpAIBinder* _aidl_return) = 0;
private:
  static std::shared_ptr<IJSIInterface> default_impl;
};
class IJSIInterfaceDefault : public IJSIInterface {
public:
  ::ndk::ScopedAStatus eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus cloneValue(int8_t in_valueType, bool in_boolValue, double in_doubleValue, const ::ndk::SpAIBinder& in_pointerBinder, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_bytes, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createValueCollection(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus createFunctionFromHostFunction(const ::ndk::SpAIBinder& in_hostFunct, const ::ndk::SpAIBinder& in_propId, int64_t in_paramCount, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus call(const ::ndk::SpAIBinder& in_func, const ::ndk::SpAIBinder& in_thisObj, const ::ndk::SpAIBinder& in_args, int64_t in_argsCount, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus callAsConstructor(const ::ndk::SpAIBinder& in_func, const ::ndk::SpAIBinder& in_args, int64_t in_argsCount, ::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
