//
// Created by anandrag on 1/13/2022.
//

#include <android/binder_ibinder_jni.h>
#include "RemoteJSIService.h"

#define LOG_TAG "remotejsi-nativeremotejsiservice"
#include "logging.h"

namespace aidl::com::example::remotejsi {

::ndk::ScopedAStatus RemoteJSIService::handshakeAck() {
    LOGD("[JSIService] [cpp] handshakeAck");
    return ::ndk::ScopedAStatus::ok();
}
}