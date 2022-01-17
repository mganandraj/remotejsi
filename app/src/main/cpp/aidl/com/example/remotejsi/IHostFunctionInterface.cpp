#include <android/binder_parcel_utils.h>
#include <aidl/com/example/remotejsi/BpHostFunctionInterface.h>
#include <aidl/com/example/remotejsi/BnHostFunctionInterface.h>
#include <aidl/com/example/remotejsi/IHostFunctionInterface.h>
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
  std::shared_ptr<BnHostFunctionInterface> _aidl_impl = std::static_pointer_cast<BnHostFunctionInterface>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*call*/): {
      ::ndk::SpAIBinder in_thisVal;
      std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface> in_args;
      int64_t in_size;
      ::ndk::SpAIBinder _aidl_return;

      _aidl_ret_status = ::ndk::AParcel_readRequiredStrongBinder(_aidl_in, &in_thisVal);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::aidl::com::example::remotejsi::IValueCollectionInterface::readFromParcel(_aidl_in, &in_args);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = AParcel_readInt64(_aidl_in, &in_size);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->call(in_thisVal, in_args, in_size, &_aidl_return);
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

static AIBinder_Class* _g_aidl_clazz = ::ndk::ICInterface::defineClass(IHostFunctionInterface::descriptor, _aidl_onTransact);

BpHostFunctionInterface::BpHostFunctionInterface(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpHostFunctionInterface::~BpHostFunctionInterface() {}

::ndk::ScopedAStatus BpHostFunctionInterface::call(const ::ndk::SpAIBinder& in_thisVal, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& in_args, int64_t in_size, ::ndk::SpAIBinder* _aidl_return) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinder().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeRequiredStrongBinder(_aidl_in.get(), in_thisVal);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::aidl::com::example::remotejsi::IValueCollectionInterface::writeToParcel(_aidl_in.get(), in_args);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_writeInt64(_aidl_in.get(), in_size);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinder().get(),
    (FIRST_CALL_TRANSACTION + 0 /*call*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | FLAG_PRIVATE_LOCAL
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IHostFunctionInterface::getDefaultImpl()) {
    return IHostFunctionInterface::getDefaultImpl()->call(in_thisVal, in_args, in_size, _aidl_return);
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
// Source for BnHostFunctionInterface
BnHostFunctionInterface::BnHostFunctionInterface() {}
BnHostFunctionInterface::~BnHostFunctionInterface() {}
::ndk::SpAIBinder BnHostFunctionInterface::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IHostFunctionInterface
const char* IHostFunctionInterface::descriptor = "com.example.remotejsi.IHostFunctionInterface";
IHostFunctionInterface::IHostFunctionInterface() {}
IHostFunctionInterface::~IHostFunctionInterface() {}


std::shared_ptr<IHostFunctionInterface> IHostFunctionInterface::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_clazz)) { return nullptr; }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IHostFunctionInterface>(interface);
  }
  return ::ndk::SharedRefBase::make<BpHostFunctionInterface>(binder);
}

binder_status_t IHostFunctionInterface::writeToParcel(AParcel* parcel, const std::shared_ptr<IHostFunctionInterface>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IHostFunctionInterface::readFromParcel(const AParcel* parcel, std::shared_ptr<IHostFunctionInterface>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IHostFunctionInterface::fromBinder(binder);
  return STATUS_OK;
}
bool IHostFunctionInterface::setDefaultImpl(std::shared_ptr<IHostFunctionInterface> impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IHostFunctionInterface::default_impl);
  if (impl) {
    IHostFunctionInterface::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IHostFunctionInterface>& IHostFunctionInterface::getDefaultImpl() {
  return IHostFunctionInterface::default_impl;
}
std::shared_ptr<IHostFunctionInterface> IHostFunctionInterface::default_impl = nullptr;
::ndk::ScopedAStatus IHostFunctionInterfaceDefault::call(const ::ndk::SpAIBinder& /*in_thisVal*/, const std::shared_ptr<::aidl::com::example::remotejsi::IValueCollectionInterface>& /*in_args*/, int64_t /*in_size*/, ::ndk::SpAIBinder* /*_aidl_return*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IHostFunctionInterfaceDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IHostFunctionInterfaceDefault::isRemote() {
  return false;
}
}  // namespace remotejsi
}  // namespace example
}  // namespace com
}  // namespace aidl
