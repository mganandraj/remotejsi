#include <jni.h>
#include <string>

#include <stdlib.h>

#include "JSIService.h"

#include <android/binder_ibinder_jni.h>

#include <android/log.h>
#define LOG_TAG "remotejsi-native-lib"
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##__VA_ARGS__)


using namespace aidl::com::example::remotejsi;
using namespace std;

//#include <utils/RefBase.h>
//#include <utils/Log.h>
// #include <binder/TextOutput.h>

// #include <binder/IInterface.h>
/*#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>*/


// using namespace android;

#include <aidl/com/example/remotejsi/BpJSIAidlInterface.h>
std::shared_ptr<IJSIAidlInterface> g_spMyService;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_remotejsi_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_remotejsi_JSIService_createServiceBinder(
        JNIEnv* env,
        jobject /* this */) {
    // std::string hello = "Hello from C++";
    // return env->NewStringUTF(hello.c_str());

    static JSIService myService;
    return env->NewGlobalRef(AIBinder_toJavaBinder(env, myService.asBinder().get()));
}



extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_MainActivity_onServiceConnected(
        JNIEnv* env,
        jobject /* this */,
        jobject binder)
{
    AIBinder* pBinder = AIBinder_fromJavaBinder(env, binder);

    const ::ndk::SpAIBinder spBinder(pBinder);
    g_spMyService = IJSIAidlInterface::fromBinder(spBinder);

    LOGD("[App] [cpp] onServiceConnected");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_remotejsi_MainActivity_onServiceDisconnected(
        JNIEnv* env,
        jobject /* this */)
{
    g_spMyService = nullptr;

    LOGD("[App] [cpp] onServiceDisconnected");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_remotejsi_MainActivity_talkToService(
        JNIEnv* env,
        jobject /* this */)
{
    ::ndk::ScopedAStatus basicTypesResult = g_spMyService->basicTypes(2021, 65535000,
                                                               true, 3.14f, 3.141592653589793238, "Hello, World!");

    if(basicTypesResult.isOk())
    {
        LOGD("[App] [cpp] IMyService.basicTypes - Succeeded");
    }
    else
    {
        LOGE("[App] [cpp] IMyService.basicTypes - Failed");
    }

  /*  ComplexType ct(2021, 65535000, true, 3.14f,3.141592653589793238,
                   "Hello, World!");

    std::string sReturnedString;

    ScopedAStatus complexTypeResult = g_spMyService->complexType(ct, &sReturnedString);

    if(complexTypeResult.isOk())
    {
        LOGD("[App] [cpp] IMyService.complexType - Succeeded");
    }
    else
    {
        LOGE("[App] [cpp] IMyService.complexType - Failed");
    }

    ComplexType returnedComplexObject;

    ScopedAStatus returnComplexTypeResult = g_spMyService->returnComplexType(2021,
                                                                             65535000, true, 3.14f, 3.141592653589793238,
                                                                             "Hello, World!", &returnedComplexObject);

    if(returnComplexTypeResult.isOk())
    {
        LOGD("[App] [cpp] IMyService.complexType - Succeeded");
    }
    else
    {
        LOGE("[App] [cpp] IMyService.complexType - Failed");
    }

    std::string sRet;
    returnedComplexObject.toString(&sRet);*/

    std::string sRet("Succeess");
    return env->NewStringUTF(sRet.c_str());
}