//
// Created by anandrag on 1/13/2022.
//

#include <android/binder_ibinder_jni.h>
#include "RemoteJSIService.h"

#define LOG_TAG "remotejsi-nativeremotejsiservice"
#include "logging.h"

namespace aidl::com::example::remotejsi {

/*::ndk::ScopedAStatus RemoteJSIService::basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString)  {
    //LOGD("[MyService] [cpp] basicTypes: int=%d, long=%ld, bool=%d, float=%f, double=%f, string=%s",
    //      in_anInt, in_aLong, in_aBoolean, in_aFloat, in_aDouble, in_aString.c_str());

    return ::ndk::ScopedAStatus::ok();
}*/

::ndk::ScopedAStatus RemoteJSIService::handshakeAck() {
    LOGD("[JSIService] [cpp] handshakeAck");
    return ::ndk::ScopedAStatus::ok();
}
}