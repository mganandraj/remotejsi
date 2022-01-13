//
// Created by anandrag on 1/12/2022.
//

#include <android/binder_ibinder_jni.h>
#include "JSIService.h"
#include "RemoteJSIService.h"

#include <android/log.h>

#define LOG_TAG "remotejsi-nativejsiservice"

#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)

#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__)

namespace aidl {
    namespace com {
        namespace example {
            namespace remotejsi {

                ::ndk::ScopedAStatus JSIService::basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString)  {
                    //LOGD("[MyService] [cpp] basicTypes: int=%d, long=%ld, bool=%d, float=%f, double=%f, string=%s",
                   //      in_anInt, in_aLong, in_aBoolean, in_aFloat, in_aDouble, in_aString.c_str());

                   return ::ndk::ScopedAStatus::ok();
                }

                ::ndk::ScopedAStatus JSIService::handshake(const ::ndk::SpAIBinder &in_remoteJSIInterface) {
                    // std::shared_ptr<IRemoteJSIInterface> g_spRemoteJSIInterface;
                    LOGD("[JSIService] [cpp] handshake");
                    g_spRemoteJSIInterface = IRemoteJSIInterface::fromBinder(in_remoteJSIInterface);
                    LOGD("[JSIService] [cpp] handshake -- received remote interface");
                    g_spRemoteJSIInterface->handshakeAck();
                    return ::ndk::ScopedAStatus::ok();
                }

                /*::ndk::ScopedAStatus get(::ndk::SpAIBinder* _aidl_return) {
                    static RemoteJSIService myService;
                    // ::ndk::SpAIBinder authzBinder(myService.asBinder());
                    *_aidl_return = myService.asBinder();
                }*/
            }
        }
    }
}

