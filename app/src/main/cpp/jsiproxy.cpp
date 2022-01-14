#include <jni.h>
#include <string>
#include <set>

#include <stdlib.h>

#include "JSIService.h"
#include "RemoteJSIService.h"
#include "ManagerService.h"

#include <android/binder_ibinder_jni.h>

#define LOG_TAG "remotejsi-native-lib"
#include "logging.h"

using namespace aidl::com::example::remotejsi;
using namespace std;

#include <aidl/com/example/remotejsi/BpManagerInterface.h>
std::shared_ptr<IManagerInterface> g_spManagerService;

extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_JSIProxy_onServiceConnected(
        JNIEnv* env,
        jobject /* this */,
        jobject binder)
{
    AIBinder* pBinder = AIBinder_fromJavaBinder(env, binder);

    const ::ndk::SpAIBinder spBinder(pBinder);
    g_spManagerService = IManagerInterface::fromBinder(spBinder);

    LOGD("[App] [cpp] onServiceConnected");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_JSIProxy_onServiceDisconnected(
        JNIEnv* env,
        jobject /* this */)
{
    g_spManagerService = nullptr;

    LOGD("[App] [cpp] onServiceDisconnected");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_remotejsi_JSIProxy_talkToService(
        JNIEnv* env,
        jobject /* this */)
{
    /*::ndk::ScopedAStatus basicTypesResult = g_spManagerService->basicTypes(2021, 65535000,
                                                               true, 3.14f, 3.141592653589793238, "Hello, World!");*/

    ::ndk::ScopedAStatus pingResult = g_spManagerService->ping();
    if(pingResult.isOk())
    {
        LOGD("[App] [cpp] IMyService.ping - Succeeded");
    }
    else
    {
        LOGE("[App] [cpp] IMyService.ping - Failed");
    }


    static std::set<std::shared_ptr<IJSIInterface>> g_jsiServices;

    std::shared_ptr<IJSIInterface> jsiService;
    ::ndk::SpAIBinder jsiServiceBinder;
    std::string result;

    static std::set<std::shared_ptr<RemoteJSIService>> g_remoteJSIServices;
    std::shared_ptr<RemoteJSIService> remoteJSIService = std::make_shared<RemoteJSIService>();
    g_remoteJSIServices.insert(remoteJSIService);

    ::ndk::SpAIBinder remoteJSIServiceBinder = remoteJSIService->asBinder();
    ::ndk::ScopedAStatus createJSIResult = g_spManagerService->createJSIInterface(
            remoteJSIServiceBinder, &jsiServiceBinder);
    if (createJSIResult.isOk()) {
        LOGD("[App] [cpp] IMyService.createJSI - Succeeded");
    } else {
        LOGE("[App] [cpp] IMyService.createJSI - Failed");
    }

    jsiService = IJSIInterface::fromBinder(jsiServiceBinder);
    g_jsiServices.insert(jsiService);
    // ::ndk::ScopedAStatus r = jsiService->basicTypes();
    jsiService->eval("\"xyz\"", &result);
    LOGE("[App] [cpp] Successfully called the JSI service result: %s", result.c_str());
    
    std::string sRet("Succeess");
    return env->NewStringUTF(sRet.c_str());
}