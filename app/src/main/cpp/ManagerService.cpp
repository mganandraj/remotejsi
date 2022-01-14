//
// Created by anandrag on 1/13/2022.
//

#include <android/binder_ibinder_jni.h>
#include "ManagerService.h"
#include "JSIService.h"

#define LOG_TAG "remotejsi-managerservice"
#include "logging.h"

#include <set>

namespace aidl::com::example::remotejsi {
static std::set<std::shared_ptr<JSIService>> g_jsiServices;
static std::set<std::shared_ptr<IRemoteJSIInterface>> g_jsiRemoteServices;

::ndk::ScopedAStatus ManagerService::createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) {
    std::shared_ptr<IRemoteJSIInterface> spRemoteJSIInterface;
    LOGD("[ManagerService] [cpp] createJSIInterface");
    spRemoteJSIInterface = IRemoteJSIInterface::fromBinder(in_remoteJSIInterface);
    LOGD("[ManagerService] [cpp] createJSIInterface -- received remote interface");
    spRemoteJSIInterface->handshakeAck();
    g_jsiRemoteServices.insert(spRemoteJSIInterface);

    std::shared_ptr<JSIService> jsiService = std::make_shared<JSIService>();
    g_jsiServices.insert(jsiService);
    *_aidl_return = jsiService->asBinder();
    // return env->NewGlobalRef(AIBinder_toJavaBinder(env, myService.asBinder().get()));

    return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus ManagerService::ping() {
    return ::ndk::ScopedAStatus::ok();
}
}