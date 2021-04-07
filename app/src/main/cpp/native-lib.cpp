#include <jni.h>
#include <string>
//#include "people/People.h"
// 相对路径搜索
//#include <people/People.h>
#include <People.h>
#include <base.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    People people;
//    return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF(people.getString().c_str());
}

// extern "C"的作用是
// JNIEnv当中存在很多函数
// jobject代表着java层的调用对象
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_MainActivity_getString(JNIEnv *env, jobject thiz) {
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeByte(JNIEnv *env, jobject thiz, jbyte b) {
    LOGD("java byte value is %d", b);
    jbyte c_byte = b + (jbyte) 10;
    return c_byte;
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeChar(JNIEnv *env, jobject thiz, jchar ch) {
    LOGD("java char value is %c", ch);
    jchar c_char = ch + (jchar) 3;
    return c_char;
}

extern "C"
JNIEXPORT jshort JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeShort(JNIEnv *env, jobject thiz, jshort sh) {
    LOGD("java short value is %d", sh);
    jshort c_short = sh + (jshort) 10;
    return c_short;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeInt(JNIEnv *env, jobject thiz, jint num) {
    LOGD("java int value is 23%d", num);
    int c_num = num * 2;
    return c_num;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeLong(JNIEnv *env, jobject thiz, jlong l) {
    LOGD("java long value is %lld", l);
    jlong c_long = l + 100;
    return c_long;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeFloat(JNIEnv *env, jobject thiz, jfloat f) {
    LOGD("java float value is %f", f);
    jdouble c_float = f + (jfloat) 10.0;
    return c_float;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeDouble(JNIEnv *env, jobject thiz, jdouble d) {
    LOGD("java long value is %f", d);
    jdouble c_double = d + 20.0;
    return c_double;

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeBoolean(JNIEnv *env, jobject thiz, jboolean value) {
    LOGD("java boolean value is %d", value);
    jboolean c_bool = (jboolean) !value;
    return c_bool;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_jni_JNIString_callNativeString(JNIEnv *env, jobject thiz, jstring str_) {
    // 这里如果直接填false，会报错：error: cannot initialize a parameter of type 'jboolean *' (aka 'unsigned char *') with an rvalue of type 'bool'
    // 参数修改为0
    const char *str = env->GetStringUTFChars(str_, 0);
    LOGD("java string is %s", str);
    env->ReleaseStringUTFChars(str_, str);
    return env->NewStringUTF("this is C style string");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIString_stringMethod(JNIEnv *env, jobject thiz, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, 0);
    int length = env->GetStringLength(jstr);
    int utfLength = env->GetStringUTFLength(jstr);
    LOGD("java string length is %d", length);
    LOGD("java string utf length is %d", utfLength);

    char buf[128];
    env->GetStringUTFRegion(jstr, 0, length, buf);
    LOGD("jstring is %s", buf);
    env->ReleaseStringUTFChars(jstr, str);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_jni_JNIReferenceType_callNativeStringArray(JNIEnv *env, jobject thiz,
                                                                jobjectArray str_array) {
    int len = env->GetArrayLength(str_array);
    LOGD("length is %d", len);
    jstring firstStr = static_cast<jstring>(env->GetObjectArrayElement(str_array, 0));
    const char *str = env->GetStringUTFChars(firstStr, 0);
    LOGD("first str is %s", str);
    env->ReleaseStringUTFChars(firstStr, str);

    return env->NewStringUTF(str);
}
