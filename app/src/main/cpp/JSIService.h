//
// Created by anandrag on 1/12/2022.
//

#ifndef REMOTEJSI_JSISERVICE_H
#define REMOTEJSI_JSISERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIInterface.h>

#include <aidl/com/example/remotejsi/BpRemoteJSIInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
class JSIService : public BnJSIInterface {
public:
    JSIService(std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface);
    ::ndk::ScopedAStatus eval(const ::ndk::SpAIBinder& in_bufferBinder, const std::string& in_sourceURL, ::ndk::SpAIBinder* _aidl_return) override;

    ::ndk::ScopedAStatus createObject(::ndk::SpAIBinder* _aidl_return) override;
    ::ndk::ScopedAStatus createFromAscii(const std::vector<int8_t>& in_chars, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;
    ::ndk::ScopedAStatus createFromUtf8(const std::vector<int8_t>& in_bytes, int64_t in_length, ::ndk::SpAIBinder* _aidl_return) override;

private:
    std::shared_ptr<facebook::hermes::HermesRuntime> runtime_;
    std::shared_ptr<IRemoteJSIInterface> remoteJsiInterface_;
};
}

#endif //REMOTEJSI_JSISERVICE_H
