#include <android/binder_parcel_utils.h>
#include <aidl/com/example/remotejsi/BpJSISymbolInterface.h>
#include <aidl/com/example/remotejsi/BnJSISymbolInterface.h>
#include <aidl/com/example/remotejsi/IJSISymbolInterface.h>

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

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IJSISymbolInterface::descriptor, _aidl_onTransact);

BpJSISymbolInterface::BpJSISymbolInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpJSISymbolInterface::~BpJSISymbolInterface() {}

// Source for BnJSISymbolInterface
BnJSISymbolInterface::BnJSISymbolInterface() {}
BnJSISymbolInterface::~BnJSISymbolInterface() {}
::ndk::SpAIBinder BnJSISymbolInterface::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IJSISymbolInterface
const char* IJSISymbolInterface::descriptor = "com.example.remotejsi.IJSISymbolInterface";
IJSISymbolInterface::IJSISymbolInterface() {}
IJSISymbolInterface::~IJSISymbolInterface() {}


std::shared_ptr<IJSISymbolInterface> IJSISymbolInterface::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IJSISymbolInterface>(interface);
  }
  return ::ndk::SharedRefBase::make<BpJSISymbolInterface>(binder);
}

binder_status_t IJSISymbolInterface::writeToParcel(AParcel* parcel, const std::shared_ptr<IJSISymbolInterface>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IJSISymbolInterface::readFromParcel(const AParcel* parcel, std::shared_ptr<IJSISymbolInterface>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IJSISymbolInterface::fromBinder(binder);
  return STATUS_OK;
}
bool IJSISymbolInterface::setDefaultImpl(std::shared_ptr<IJSISymbolInterface> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IJSISymbolInterface::default_impl);
  if (impl) {
    IJSISymbolInterface::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IJSISymbolInterface>& IJSISymbolInterface::getDefaultImpl() {
  return IJSISymbolInterface::default_impl;
}
std::shared_ptr<IJSISymbolInterface> IJSISymbolInterface::default_impl = nullptr;
::ndk::SpAIBinder IJSISymbolInterfaceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IJSISymbolInterfaceDefault::isRemote() {
  return false;
}
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
