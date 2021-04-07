//
// Created by JeremyHwc on 2021/4/4.
//

#ifndef JNDK_JVM_H
#define JNDK_JVM_H


#include <jni.h>

class jvm {
public:
    static void setJvm(JavaVM *jvm);

    static JavaVM *getJvm();
};


#endif //JNDK_JVM_H
