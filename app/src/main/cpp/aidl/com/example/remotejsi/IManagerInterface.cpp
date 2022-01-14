#include <android/binder_parcel_utils.h>
#include <aidl/com/example/remotejsi/BpManagerInterface.h>
#include <aidl/com/example/remotejsi/BnManagerInterface.h>
#include <aidl/com/example/remotejsi/IManagerInterface.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
static binder_status_t _aidl_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnManagerInterface> _aidl_impl = std::static_pointer_cast<BnManagerInterface>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*ping*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->ping();
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*createJSIInterface*/): {
      ::ndk::SpAIBinder in_remoteJSIInterface;
      ::ndk::SpAIBinder _aidl_return;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_remoteJSIInterface);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->createJSIInterface(in_remoteJSIInterface, &_aidl_return);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_out, _aidl_return);
      if (_aidl_ret_status != STATUS_OK) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IManagerInterface::descriptor, _aidl_onTransact);

BpManagerInterface::BpManagerInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpManagerInterface::~BpManagerInterface() {}

::ndk::ScopedAStatus BpManagerInterface::ping() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*ping*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IManagerInterface::getDefaultImpl()) {
    return IManagerInterface::getDefaultImpl()->ping();
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
::ndk::ScopedAStatus BpManagerInterface::createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_remoteJSIInterface);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 1 /*createJSIInterface*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IManagerInterface::getDefaultImpl()) {
    return IManagerInterface::getDefaultImpl()->createJSIInterface(in_remoteJSIInterface, _aidl_return);
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_out.get(), _aidl_return);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
// Source for BnManagerInterface
BnManagerInterface::BnManagerInterface() {}
BnManagerInterface::~BnManagerInterface() {}
::ndk::SpAIBinder BnManagerInterface::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IManagerInterface
const char* IManagerInterface::descriptor = "com.example.remotejsi.IManagerInterface";
IManagerInterface::IManagerInterface() {}
IManagerInterface::~IManagerInterface() {}


std::shared_ptr<IManagerInterface> IManagerInterface::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IManagerInterface>(interface);
  }
  return ::ndk::SharedRefBase::make<BpManagerInterface>(binder);
}

binder_status_t IManagerInterface::writeToParcel(AParcel* parcel, const std::shared_ptr<IManagerInterface>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IManagerInterface::readFromParcel(const AParcel* parcel, std::shared_ptr<IManagerInterface>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IManagerInterface::fromBinder(binder);
  return STATUS_OK;
}
bool IManagerInterface::setDefaultImpl(std::shared_ptr<IManagerInterface> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IManagerInterface::default_impl);
  if (impl) {
    IManagerInterface::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IManagerInterface>& IManagerInterface::getDefaultImpl() {
  return IManagerInterface::default_impl;
}
std::shared_ptr<IManagerInterface> IManagerInterface::default_impl = nullptr;
::ndk::ScopedAStatus IManagerInterfaceDefault::ping() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IManagerInterfaceDefault::createJSIInterface(const ::ndk::SpAIBinder& /*in_remoteJSIInterface*/, ::ndk::SpAIBinder* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IManagerInterfaceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IManagerInterfaceDefault::isRemote() {
  return false;
}
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
