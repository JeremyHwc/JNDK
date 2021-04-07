//
// Created by JeremyHwc on 2021/4/7.
//

#include <base.h>

extern "C"
JNIEXPORT jobject JNICALL
Java_com_jeremy_jndk_jni_JNIConstructorClass_invokeAnimalConstructors(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/jeremy/jndk/base/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jstring name = env->NewStringUTF("this is animal name");
    jobject animal = env->NewObject(cls, mid, name);
    return animal;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_jeremy_jndk_jni_JNIConstructorClass_allocObjectConstructor(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/jeremy/jndk/base/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jobject animal = env->AllocObject(cls);
    jstring name = env->NewStringUTF("this is animal name 2");
    env->CallNonvirtualVoidMethod(animal, cls, mid, name);

    return animal;
}
