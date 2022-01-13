//
// Created by anandrag on 1/12/2022.
//

#ifndef REMOTEJSI_JSISERVICE_H
#define REMOTEJSI_JSISERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnJSIAidlInterface.h>

namespace aidl {
    namespace com {
        namespace example {
            namespace remotejsi {
                class JSIService : public BnJSIAidlInterface
                {
                public:
                    ::ndk::ScopedAStatus basicTypes(int32_t in_anInt, int64_t in_aLong, bool in_aBoolean, float in_aFloat, double in_aDouble, const std::string& in_aString) override;
                };

            }
        }
    }
}

#endif //REMOTEJSI_JSISERVICE_H
