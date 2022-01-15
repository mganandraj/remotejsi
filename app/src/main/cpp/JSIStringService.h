//
// Created by anandrag on 1/15/2022.
//

#ifndef REMOTEJSI_JSISTRINGSERVICE_H
#define REMOTEJSI_JSISTRINGSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIStringInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
    class JSIStringService : public BnJSIStringInterface {
    public:
        JSIStringService(std::shared_ptr<facebook::jsi::Runtime> runtime, facebook::jsi::String jsString);
        ::ndk::ScopedAStatus utf8(std::string* _aidl_return) override;
    private:
        std::shared_ptr<facebook::jsi::Runtime> runtime_;
        facebook::jsi::String jsString_;
    };
}

#endif //REMOTEJSI_JSISTRINGSERVICE_H
