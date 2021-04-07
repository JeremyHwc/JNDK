//
// Created by JeremyHwc on 2021/4/7.
//
#include <base.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_jni_JNIReference_errorCacheLocalReference(JNIEnv *env, jobject thiz) {
    // 局部引用会在程序结束之后，会被程序自动释放掉，所以这里就不需要我们刻意去释放掉
    // 但是是不是我们可以在程序内写无数个局部引用，等到程序结束以后自动释放掉呢？事实上是不可以的。
    // 如果局部引用过多，程序会有崩溃提示，提示程序局部引用过多，超过了512的阈值。因此，我们在使用局部引用的时候
    // 如果可以尽早地释放，就使用env->DeleteLocalRef(cls);尽早释放掉，尤其是在for循环当中，如下代码所示
    jclass localRefs = env->FindClass("java/lang/String");

    jmethodID strMid = env->GetMethodID(localRefs, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("string");

//    for (int i = 0; i < 1000; ++i) {
//        jclass cls = env->FindClass("java/lang/String");
//
//        env->DeleteLocalRef(cls);
//    }
    
    return static_cast<jstring>(env->NewObject(localRefs, strMid, str));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_jni_JNIReference_cacheWithGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass stringClass = nullptr;
    if (stringClass == nullptr) {
        jclass cls = env->FindClass("java/lang/String");
        stringClass = static_cast<jclass>(env->NewGlobalRef(cls));
        env->DeleteLocalRef(cls);
        LOGD("use not cached");
    } else{
        LOGD("use cached");
    }
    jmethodID strMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("string");

    return static_cast<jstring>(env->NewObject(stringClass, strMid, str));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIReference_useWeakGlobalReference(JNIEnv *env, jobject thiz) {
    static jclass stringClass = nullptr;
    if (stringClass == nullptr) {
        jclass cls = env->FindClass("java/lang/String");
        stringClass = static_cast<jclass>(env->NewWeakGlobalRef(cls));
        env->DeleteLocalRef(cls);
        LOGD("use not cached");
    } else{
        LOGD("use cached");
    }
    jmethodID strMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
    jboolean isGc = env->IsSameObject(stringClass, nullptr);
}