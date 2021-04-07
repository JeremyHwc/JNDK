//
// Created by JeremyHwc on 2021/4/7.
//

#include <base.h>
#include <locale>

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIException_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/jeremy/jndk/jni/JNIException");
    jmethodID mid = env->GetMethodID(cls, "operation", "()I");
    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
    jobject jobj = env->NewObject(cls, constructor);

    // 该方法的调用会产生异常，导致程序崩溃
    env->CallIntMethod(jobj, mid);
    // 通过如下方式进行处理，检测到如果有异常发生，则打印出相应的描述信息，并清除掉该异常，程序不会崩溃
    // 当然这种方式只是隐藏了异常，并为真正解决问题
    jthrowable exc = env->ExceptionOccurred();
    if (exc != nullptr) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIException_nativeThrowException(JNIEnv *env, jobject thiz) {
    // 从Native中向Java中抛出异常
    jclass cls = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(cls, "native throw exception");
}