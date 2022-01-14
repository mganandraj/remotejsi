//
// Created by anandrag on 1/13/2022.
//

#ifndef REMOTEJSI_MANAGERSERVICE_H
#define REMOTEJSI_MANAGERSERVICE_H

#include <android/binder_ibinder_jni.h>
#include <aidl/com/example/remotejsi/BnManagerInterface.h>

namespace aidl::com::example::remotejsi {
class ManagerService : public BnManagerInterface {
    ::ndk::ScopedAStatus ping() override;
    ::ndk::ScopedAStatus createJSIInterface(const ::ndk::SpAIBinder& in_remoteJSIInterface, ::ndk::SpAIBinder* _aidl_return) override;
};
}

#endif //REMOTEJSI_MANAGERSERVICE_H
