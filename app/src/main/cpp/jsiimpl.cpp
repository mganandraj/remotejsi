#include <jni.h>
#include <string>
#include <set>
#include <stdlib.h>

#include "ManagerService.h"
#include <android/binder_ibinder_jni.h>

#define LOG_TAG "remotejsi-native-lib"
#include "logging.h"

using namespace aidl::com::example::remotejsi;
using namespace std;

static std::set<std::shared_ptr<ManagerService>> g_managerServices;
extern "C" JNIEXPORT jobject JNICALL
Java_com_example_remotejsi_JSIImplService_createServiceBinder(
        JNIEnv* env,
        jobject /* this */) {
    std::shared_ptr<ManagerService> managerService = std::make_shared<ManagerService>();
    g_managerServices.insert(managerService);

    return env->NewGlobalRef(AIBinder_toJavaBinder(env, managerService->asBinder().get()));
}