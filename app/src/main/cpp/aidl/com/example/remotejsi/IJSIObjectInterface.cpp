#include <android/binder_parcel_utils.h>
#include <aidl/com/example/remotejsi/BpJSIObjectInterface.h>
#include <aidl/com/example/remotejsi/BnJSIObjectInterface.h>
#include <aidl/com/example/remotejsi/IJSIObjectInterface.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
static binder_status_t _aidl_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  (void)_aidl_binder;
  (void)_aidl_code;
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IJSIObjectInterface::descriptor, _aidl_onTransact);

BpJSIObjectInterface::BpJSIObjectInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpJSIObjectInterface::~BpJSIObjectInterface() {}

// Source for BnJSIObjectInterface
BnJSIObjectInterface::BnJSIObjectInterface() {}
BnJSIObjectInterface::~BnJSIObjectInterface() {}
::ndk::SpAIBinder BnJSIObjectInterface::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IJSIObjectInterface
const char* IJSIObjectInterface::descriptor = "com.example.remotejsi.IJSIObjectInterface";
IJSIObjectInterface::IJSIObjectInterface() {}
IJSIObjectInterface::~IJSIObjectInterface() {}


std::shared_ptr<IJSIObjectInterface> IJSIObjectInterface::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IJSIObjectInterface>(interface);
  }
  return ::ndk::SharedRefBase::make<BpJSIObjectInterface>(binder);
}

binder_status_t IJSIObjectInterface::writeToParcel(AParcel* parcel, const std::shared_ptr<IJSIObjectInterface>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IJSIObjectInterface::readFromParcel(const AParcel* parcel, std::shared_ptr<IJSIObjectInterface>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IJSIObjectInterface::fromBinder(binder);
  return STATUS_OK;
}
bool IJSIObjectInterface::setDefaultImpl(std::shared_ptr<IJSIObjectInterface> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IJSIObjectInterface::default_impl);
  if (impl) {
    IJSIObjectInterface::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IJSIObjectInterface>& IJSIObjectInterface::getDefaultImpl() {
  return IJSIObjectInterface::default_impl;
}
std::shared_ptr<IJSIObjectInterface> IJSIObjectInterface::default_impl = nullptr;
::ndk::SpAIBinder IJSIObjectInterfaceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IJSIObjectInterfaceDefault::isRemote() {
  return false;
}
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
