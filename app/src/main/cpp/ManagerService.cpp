//
// Created by anandrag on 1/13/2022.
//

#include <android/binder_ibinder_jni.h>
#include <android/binder_ibinder.h>
#include "ManagerService.h"
#include "JSIService.h"

#define LOG_TAG "remotejsi-managerservice"
#include "logging.h"

#include <set>

namespace aidl::com::example::remotejsi {
::ndk::ScopedAStatus ManagerService::createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) {
    auto jsiService = ::ndk::SharedRefBase::make<JSIService>(IRemoteJSIInterface::fromBinder(in_remoteJSIInterface));
    ::ndk::SpAIBinder binder = jsiService->asBinder();
    *_aidl_return = binder;
    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus ManagerService::ping() {
    return ::ndk::ScopedAStatus::ok();
}
}