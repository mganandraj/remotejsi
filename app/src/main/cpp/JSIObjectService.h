//
// Created by anandrag on 1/15/2022.
//

#ifndef REMOTEJSI_JSIOBJECTSERVICE_H
#define REMOTEJSI_JSIOBJECTSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIObjectInterface.h>

#include <hermes/hermes.h>

namespace aidl::com::example::remotejsi {
    class JSIObjectService : public BnJSIObjectInterface {
    public:
        JSIObjectService(std::shared_ptr<facebook::jsi::Runtime> runtime, facebook::jsi::Object jsObject);


    private:
        std::shared_ptr<facebook::jsi::Runtime> runtime_;
        facebook::jsi::Value jsObject_;
    };
}

#endif //REMOTEJSI_JSIOBJECTSERVICE_H
