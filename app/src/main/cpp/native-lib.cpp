#include <jni.h>
#include <string>
//#include "people/People.h"
// 相对路径搜索
//#include <people/People.h>
#include <People.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    People people;
//    return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF(people.getString().c_str());
}