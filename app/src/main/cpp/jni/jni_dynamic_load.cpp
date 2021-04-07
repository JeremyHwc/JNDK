//
// Created by JeremyHwc on 2021/4/4.
//
#include <base.h>
#include <jvm.h>

// 类名字符串，通过宏定义进行定义
#define JAVA_CLASS "com/jeremy/jndk/load/JNIDynamicLoad"

jstring getMessage(JNIEnv *env, jobject jobj) {
    return env->NewStringUTF("this is msg");
}

jint plus(JNIEnv *env, jobject jobj, int x, int y) {
    return x + y;
}

// 对函数注册的方法进行一个封装
// 参数中的name对应的是Java当中的类名：如JAVA_CLASS所示
int registerNativeMethods(JNIEnv *env, const char *name, JNINativeMethod *methods, jint nMethods) {
    jclass jcls;
    jcls = env->FindClass(name);
    if (jcls == nullptr) {
        return JNI_FALSE;
    }
    // RegisterNatives返回0则表示成功，小于0则表示失败
    if (env->RegisterNatives(jcls, methods, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// 定义
static JNINativeMethod gMethods[] = {
        {"getNativeString", "()Ljava/lang/String;", (void *) getMessage},
        {"sum",             "(II)I",                (void *) plus}
};

// 每一个动态库在被加载的过程中，都会被系统去回调这个方法，在这个方法中，我们就可以去执行我们的动态注册。
// env可以理解为一个函数表，通过env我们可以调用到jni中为我们提供的一些函数。可以通过JavaVM去拿到
// 在Android NDK开发当中，如果正确，定义的宏值一般都是0，如果失败定义的宏值就是一些负数
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **> (&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    // 保存JavaVm，以供全局使用
    jvm::setJvm(vm);

    registerNativeMethods(env, JAVA_CLASS, gMethods, 2);
    LOGD("jni onload call");
    return JNI_VERSION_1_6;
}