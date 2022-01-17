#include <android/binder_parcel_utils.h>
#include <aidl/com/example/remotejsi/BpHostObjectInterface.h>
#include <aidl/com/example/remotejsi/BnHostObjectInterface.h>
#include <aidl/com/example/remotejsi/IHostObjectInterface.h>
#include <aidl/com/example/remotejsi/BpValueCollectionInterface.h>
#include <aidl/com/example/remotejsi/BnValueCollectionInterface.h>
#include <aidl/com/example/remotejsi/IValueCollectionInterface.h>

namespace aidl {
namespace com {
namespace example {
namespace remotejsi {
static binder_status_t _aidl_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnHostObjectInterface> _aidl_impl = std::static_pointer_cast<BnHostObjectInterface>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*get*/): {
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
    case (FIRST_CALL_TRANSACTION + 1 /*set*/): {
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
    case (FIRST_CALL_TRANSACTION + 2 /*getPropertyNames*/): {

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->getPropertyNames();
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IHostObjectInterface::descriptor, _aidl_onTransact);

BpHostObjectInterface::BpHostObjectInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpHostObjectInterface::~BpHostObjectInterface() {}

::ndk::ScopedAStatus BpHostObjectInterface::get(const ::ndk::SpAIBinder& in_name, ::ndk::SpAIBinder* _aidl_return) {
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
    (FIRST_CALL_TRANSACTION + 0 /*get*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IHostObjectInterface::getDefaultImpl()) {
    return IHostObjectInterface::getDefaultImpl()->get(in_name, _aidl_return);
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
::ndk::ScopedAStatus BpHostObjectInterface::set(const ::ndk::SpAIBinder& in_name, const ::ndk::SpAIBinder& in_value) {
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
    (FIRST_CALL_TRANSACTION + 1 /*set*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IHostObjectInterface::getDefaultImpl()) {
    return IHostObjectInterface::getDefaultImpl()->set(in_name, in_value);
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
::ndk::ScopedAStatus BpHostObjectInterface::getPropertyNames() {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 2 /*getPropertyNames*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IHostObjectInterface::getDefaultImpl()) {
    return IHostObjectInterface::getDefaultImpl()->getPropertyNames();
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) return _aidl_status;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  return _aidl_status;
}
// Source for BnHostObjectInterface
BnHostObjectInterface::BnHostObjectInterface() {}
BnHostObjectInterface::~BnHostObjectInterface() {}
::ndk::SpAIBinder BnHostObjectInterface::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IHostObjectInterface
const char* IHostObjectInterface::descriptor = "com.example.remotejsi.IHostObjectInterface";
IHostObjectInterface::IHostObjectInterface() {}
IHostObjectInterface::~IHostObjectInterface() {}


std::shared_ptr<IHostObjectInterface> IHostObjectInterface::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IHostObjectInterface>(interface);
  }
  return ::ndk::SharedRefBase::make<BpHostObjectInterface>(binder);
}

binder_status_t IHostObjectInterface::writeToParcel(AParcel* parcel, const std::shared_ptr<IHostObjectInterface>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IHostObjectInterface::readFromParcel(const AParcel* parcel, std::shared_ptr<IHostObjectInterface>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IHostObjectInterface::fromBinder(binder);
  return STATUS_OK;
}
bool IHostObjectInterface::setDefaultImpl(std::shared_ptr<IHostObjectInterface> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IHostObjectInterface::default_impl);
  if (impl) {
    IHostObjectInterface::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IHostObjectInterface>& IHostObjectInterface::getDefaultImpl() {
  return IHostObjectInterface::default_impl;
}
std::shared_ptr<IHostObjectInterface> IHostObjectInterface::default_impl = nullptr;
::ndk::ScopedAStatus IHostObjectInterfaceDefault::get(const ::ndk::SpAIBinder& /*in_name*/, ::ndk::SpAIBinder* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IHostObjectInterfaceDefault::set(const ::ndk::SpAIBinder& /*in_name*/, const ::ndk::SpAIBinder& /*in_value*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IHostObjectInterfaceDefault::getPropertyNames() {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IHostObjectInterfaceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IHostObjectInterfaceDefault::isRemote() {
  return false;
}
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
