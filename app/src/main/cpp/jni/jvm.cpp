//
// Created by JeremyHwc on 2021/4/4.
//

#include <jvm.h>
#include <base.h>

static JavaVM *gVM = nullptr;

#ifdef __cplusplus
extern "C" {
#endif
void jvm::setJvm(JavaVM *jvm) {
    gVM = jvm;
}

JavaVM *jvm::getJvm() {
    return gVM;
}
#ifdef __cplusplus
}
#endif

