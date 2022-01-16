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
  std::shared_ptr<BnJSIObjectInterface> _aidl_impl = std::static_pointer_cast<BnJSIObjectInterface>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*has*/): {
      ::ndk::SpAIBinder in_name;
      bool _aidl_return;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_name);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->has(in_name, &_aidl_return);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      _aidl_ret_status = AParcel_writeBool(_aidl_out, _aidl_return);
      if (_aidl_ret_status != STATUS_OK) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*get*/): {
      ::ndk::SpAIBinder in_name;
      ::ndk::SpAIBinder _aidl_return;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_name);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->get(in_name, &_aidl_return);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_out, _aidl_return);
      if (_aidl_ret_status != STATUS_OK) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 2 /*set*/): {
      ::ndk::SpAIBinder in_name;
      ::ndk::SpAIBinder in_value;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_name);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_value);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->set(in_name, in_value);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IJSIObjectInterface::descriptor, _aidl_onTransact);

BpJSIObjectInterface::BpJSIObjectInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpJSIObjectInterface::~BpJSIObjectInterface() {}

::ndk::ScopedAStatus BpJSIObjectInterface::has(const ::ndk::SpAIBinder& in_name, bool* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_name);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*has*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IJSIObjectInterface::getDefaultImpl()) {
    return IJSIObjectInterface::getDefaultImpl()->has(in_name, _aidl_return);
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_ret_status = AParcel_readBool(_aidl_out.get(), _aidl_return);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
::ndk::ScopedAStatus BpJSIObjectInterface::get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_name);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 1 /*get*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IJSIObjectInterface::getDefaultImpl()) {
    return IJSIObjectInterface::getDefaultImpl()->get(in_name, _aidl_return);
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
::ndk::ScopedAStatus BpJSIObjectInterface::set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_name);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_value);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 2 /*set*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IJSIObjectInterface::getDefaultImpl()) {
    return IJSIObjectInterface::getDefaultImpl()->set(in_name, in_value);
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
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
::ndk::ScopedAStatus IJSIObjectInterfaceDefault::has(const ::ndk::SpAIBinder& /*in_name*/, bool* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IJSIObjectInterfaceDefault::get(const ::ndk::SpAIBinder& /*in_name*/, ::ndk::SpAIBinder* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IJSIObjectInterfaceDefault::set(const ::ndk::SpAIBinder& /*in_name*/, const ::ndk::SpAIBinder& /*in_value*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
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
