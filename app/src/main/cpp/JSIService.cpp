//
// Created by anandrag on 1/12/2022.
//

#include <android/binder_ibinder_jni.h>
#include "JSIService.h"
#include "RemoteJSIService.h"

#include <hermes/hermes.h>
#include <jsi/jsi.h>

#define LOG_TAG "remotejsi-nativejsiservice"
#include "logging.h"

class JSI_EXPORT StringBuffer : public facebook::jsi::Buffer {
public:
    StringBuffer(std::string s) : s_(std::move(s)) {}
    size_t size() const override {
        return s_.size();
    }
    const uint8_t* data() const override {
        return reinterpret_cast<const uint8_t*>(s_.data());
    }

private:
    std::string s_;
};

namespace aidl::com::example::remotejsi {

::ndk::ScopedAStatus JSIService::basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString)  {
    //LOGD("[MyService] [cpp] basicTypes: int=%d, long=%ld, bool=%d, float=%f, double=%f, string=%s",
   //      in_anInt, in_aLong, in_aBoolean, in_aFloat, in_aDouble, in_aString.c_str());

   return ::ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus JSIService::eval(const std::string& in_aString, std::string* _aidl_return) {
    auto script = std::make_shared<StringBuffer>(in_aString);
    std::string sourceUrl = "MyScript";
    std::unique_ptr<facebook::hermes::HermesRuntime> runtime = facebook::hermes::makeHermesRuntime();
    facebook::jsi::Value result = runtime->evaluateJavaScript(script, sourceUrl);
    if(result.isString()) {
        facebook::jsi::String stringRes = result.getString(*runtime);
        *_aidl_return = stringRes.utf8(*runtime);
    } else {
        *_aidl_return = std::string("non-string return value from script evaluation");
    }

    return ::ndk::ScopedAStatus::ok();
}

/* ::ndk::ScopedAStatus JSIService::handshake(const ::ndk::SpAIBinder &in_remoteJSIInterface, std::string* _aidl_return) {
    // std::shared_ptr<IRemoteJSIInterface> g_spRemoteJSIInterface;
    LOGD("[JSIService] [cpp] handshake");
    g_spRemoteJSIInterface = IRemoteJSIInterface::fromBinder(in_remoteJSIInterface);
    LOGD("[JSIService] [cpp] handshake -- received remote interface");
    g_spRemoteJSIInterface->handshakeAck();

    auto script = std::make_shared<StringBuffer>("\"abcd\"");
    std::string sourceUrl = "MyScript";
    std::unique_ptr<facebook::hermes::HermesRuntime> runtime = facebook::hermes::makeHermesRuntime();
    facebook::jsi::Value result = runtime->evaluateJavaScript(script, sourceUrl);
    if(result.isString()) {
        facebook::jsi::String stringRes = result.getString(*runtime);
        *_aidl_return = stringRes.utf8(*runtime);
    } else {
        *_aidl_return = std::string("non-string return value from script evaluation");
    }

    return ::ndk::ScopedAStatus::ok();
}*/

/*::ndk::ScopedAStatus get(::ndk::SpAIBinder* _aidl_return) {
    static RemoteJSIService myService;
    // ::ndk::SpAIBinder authzBinder(myService.asBinder());
    *_aidl_return = myService.asBinder();
}*/
}
