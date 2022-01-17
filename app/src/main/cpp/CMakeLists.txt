# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("remotejsi")

find_library(log-lib
        log
)

find_library(binder_ndk-lib
        binder_ndk
)

message(STATUS  "project_dir: ${project_dir}")
add_library(hermes SHARED IMPORTED)
set_target_properties(hermes
        PROPERTIES IMPORTED_LOCATION
        ${project_dir}/build/hermes/jni/${ANDROID_ABI}/libhermes.so
)

add_library(bindercommon
        SHARED
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSIInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IRemoteJSIInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IManagerInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSIBufferInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSIValueInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSIStringInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSIObjectInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IJSISymbolInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IValueCollectionInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IHostFunctionInterface.cpp
        ${project_dir}/src/main/cpp/aidl/com/example/remotejsi/IHostObjectInterface.cpp
        )

target_include_directories (bindercommon
        PRIVATE
        ${project_dir}/src/main/cpp/includes
        includes
        )

target_link_libraries( # Specifies the target library.
        bindercommon
        ${log-lib}
        ${binder_ndk-lib})

add_library(jsiimpl
        SHARED
        jsiimpl.cpp JSIService.cpp JSIValueService.cpp JSIStringService.cpp JSIObjectService.cpp
        JSISymbolService.cpp ManagerService.cpp HostFunctionService.cpp HostObjectService.cpp JSIValueCollectionService.cpp
)

target_include_directories (jsiimpl
        PRIVATE
        ${project_dir}/src/main/cpp/includes
        includes
        ${project_dir}/../node_modules/hermes-engine/android/include
)

target_link_libraries( # Specifies the target library.
        jsiimpl
        hermes
        bindercommon
        ${log-lib}
        ${binder_ndk-lib})


add_library(jsiproxy
        SHARED
        jsiproxy.cpp JSIProxyRuntime.cpp RemoteJSIService.cpp JSIBufferService.cpp
        )

target_include_directories (jsiproxy
        PRIVATE
        ${project_dir}/src/main/cpp/includes
        includes
        ${project_dir}/../node_modules/hermes-engine/android/include
        )

target_link_libraries( # Specifies the target library.
        jsiproxy
        bindercommon
        hermes
        ${log-lib}
        ${binder_ndk-lib})