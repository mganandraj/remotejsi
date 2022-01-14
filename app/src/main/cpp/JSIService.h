//
// Created by anandrag on 1/12/2022.
//

#ifndef REMOTEJSI_JSISERVICE_H
#define REMOTEJSI_JSISERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIInterface.h>

#include <aidl/com/example/remotejsi/BpRemoteJSIInterface.h>

namespace aidl::com::example::remotejsi {
class JSIService : public BnJSIInterface {
public:

    std::shared_ptr<IRemoteJSIInterface> g_spRemoteJSIInterface;


    ::ndk::ScopedAStatus
    basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean,
               float in_aFloat, double in_aDouble,
               const std::string &in_aString) override;

    // ::ndk::ScopedAStatus get(::ndk::SpAIBinder* _aidl_return) override;
    // ::ndk::ScopedAStatus
    // handshake(const ::ndk::SpAIBinder &in_remoteJSIInterface, std::string* _aidl_return) override;

    ::ndk::ScopedAStatus eval(const std::string& in_aString, std::string* _aidl_return) override;

    // std::unique_ptr<facebook::hermes::HermesRuntime> m_runtime;
};
}

#endif //REMOTEJSI_JSISERVICE_H
