//
// Created by anandrag on 1/13/2022.
//

#include <android/binder_ibinder_jni.h>
#include "RemoteJSIService.h"

#include <android/log.h>

#define LOG_TAG "remotejsi-nativeremotejsiservice"

#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)

#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__)

namespace aidl {
    namespace com {
        namespace example {
            namespace remotejsi {

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
        }
    }
}