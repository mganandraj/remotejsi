//
// Created by anandrag on 1/14/2022.
//

#ifndef REMOTEJSI_JSIBUFFERSERVICE_H
#define REMOTEJSI_JSIBUFFERSERVICE_H


#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIBufferInterface.h>

#include <jsi/jsi.h>

namespace aidl::com::example::remotejsi {
    class JSIBufferService : public BnJSIBufferInterface {
    public:
        JSIBufferService(const std::shared_ptr<const facebook::jsi::Buffer> buffer);

        ::ndk::ScopedAStatus data(std::vector<int8_t>* _aidl_return);
        ::ndk::ScopedAStatus size(int64_t* _aidl_return);

    private:
        std::shared_ptr<const facebook::jsi::Buffer> buffer_;
    };
}


#endif //REMOTEJSI_JSIBUFFERSERVICE_H
