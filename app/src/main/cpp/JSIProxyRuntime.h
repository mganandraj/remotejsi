//
// Created by anandrag on 1/14/2022.
//

#ifndef REMOTEJSI_JSIPROXYRUNTIME_H
#define REMOTEJSI_JSIPROXYRUNTIME_H


#include "ManagerService.h"

#include <jsi/jsi.h>
#include <memory.h>

namespace com::example::remotejsi {
std::unique_ptr<facebook::jsi::Runtime> makeJSIProxyRuntime(std::shared_ptr<aidl::com::example::remotejsi::IManagerInterface> managerService);
}

#endif //REMOTEJSI_JSIPROXYRUNTIME_H
