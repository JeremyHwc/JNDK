# NDK学习笔记

[toc]

## 1. CMake编译

### 1.1 C++ 文件编译成so的语法

```c++
# 将cpp文件编译成so动态库的语法
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )
```



### 1.2 so动态库之间的互相关联

```c++
# 将native-lib链接到log库
target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
```

## 2. Java与JNI的交互

### 2.1 在Java中调用JNI方法

- Java方法中加载动态库so

  ```java
  // Used to load the 'native-lib' library on application startup.
  static {
      System.loadLibrary("native-lib");
  }
  ```

- Java中调用native方法的函数类型

  在Java代码中申明需要调用的native 方法

  ```java
  public native String getString();
  ```

- JNI头文件的创建方式以及命名方式

  ```java
  // extern "C"的作用是
  // JNIEnv当中存在很多函数
  // jobject代表着java层的调用对象
  extern "C"
  JNIEXPORT jstring JNICALL
  Java_com_jeremy_jndk_MainActivity_getString(JNIEnv *env, jobject thiz) {
  }
  ```

### 2.2 函数的动态注册

在2.1中JNI方法的注册时采用的静态注册，在cpp文件中申明的格式是"**JAVA_包名__类名\_方法名**"。静态注册的格式JNI中的方法和Java的方法名称必须保持一致。

下面我们讲解JNI方法的动态注册，在动态库加载的时候，把方法动态注册到系统中去，相比于静态注册，可以省去每次调用过程当中的查找过程。

### 2.3 Java与JNI基础数据类型转换

#### 2.3.1 JNI中基础类型的定义

| Java    | JNI      |
| ------- | -------- |
| char    | jchar    |
| byte    | jbyte    |
| short   | jshort   |
| int     | jint     |
| long    | jlong    |
| float   | jfloat   |
| double  | jdouble  |
| boolean | jboolean |

#### 2.3.2 Java与JNI中的基础数据类型转换实践

```java
public class JNIBasicType {
    static {
        System.loadLibrary("native-lib");
    }

    public native char callNativeChar(char ch);

    public native byte callNativeByte(byte b);

    public native short callNativeShort(short sh);

    public native int callNativeInt(int num);

    public native long callNativeLong(long l);

    public native float callNativeFloat(float f);

    public native double callNativeDouble(double d);

    public native boolean callNativeBoolean(boolean bool);
}
```

```c++
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

}extern "C"
JNIEXPORT jboolean JNICALL
Java_com_jeremy_jndk_jni_JNIBasicType_callNativeBoolean(JNIEnv *env, jobject thiz, jboolean value) {
    LOGD("java boolean value is %d", value);
    jboolean c_bool = (jboolean) !value;
    return c_bool;
}
```

### 2.4 Java与JNI字符串转换

#### 2.4.1 JNI中字符串类型的定义

#### 2.4.2 Java中的字符串与JNI中字符串的转换调用实践

#### 2.4.3 JNI中字符串操作的必备函数

```cpp
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
    const char * str = env->GetStringUTFChars(jstr, 0);
    int length = env->GetStringLength(jstr);
    int utfLength = env->GetStringUTFLength(jstr);
    LOGD("java string length is %d", length);
    LOGD("java string utf length is %d", utfLength);

    char buf[128];
    env->GetStringUTFRegion(jstr, 0, length, buf);
    LOGD("jstring is %s", buf);
    env->ReleaseStringUTFChars(jstr, str);
}
```

### 2.5 Java与JNI引用类型转换

#### 2.5.1 JNI中引用类型的定义

#### 2.5.2 Java中引用类型与JNI中引用类型的转换调用实践

| Java Reference      | Native        |
| ------------------- | ------------- |
| All objects         | jobect        |
| java.lang.Class     | jclass        |
| java.lang.String    | jstring       |
| Obect[]             | jobjectArray  |
| boolean[]           | jbooleanArray |
| byte[]              | jbyteArray    |
| java.lang.Throwable | jthrowable    |
| char[]              | jcharArray    |
| short[]             | jshortArray   |
| int[]               | jintArray     |
| long[]              | jlongArray    |
| float[]             | jfloatArray   |
| double[]            | jdoubleArray  |

注意：JNI中不存在String[]。Java中的String[]对应到JNI中就是jobjectArray。



```java
package com.jeremy.jndk.jni;

public class JNIReferenceType {
    static {
        System.loadLibrary("native-lib");
    }

    public native String callNativeStringArray(String[] strArray);
}

```

```cpp
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeremy_jndk_jni_JNIReferenceType_callNativeStringArray(JNIEnv *env, jobject thiz,jobjectArray str_array) {
    int len = env->GetArrayLength(str_array);
    LOGD("length is %d", len);
    jstring firstStr = static_cast<jstring>(env->GetObjectArrayElement(str_array, 0));
    const char *str = env->GetStringUTFChars(firstStr, 0);
    LOGD("first str is %s", str);
    env->ReleaseStringUTFChars(firstStr,str);

    return env->NewStringUTF(str);
}
```



### 2.6 JNI方法Java类字段

| Java      | JNI                   |
| --------- | --------------------- |
| boolean   | Z                     |
| byte      | B                     |
| char      | C                     |
| short     | S                     |
| int       | I                     |
| long      | J                     |
| float     | F                     |
| double    | D                     |
|           |                       |
| String    | Ljava/lang/String;    |
| Class     | Ljava/lang/Class;     |
| Throwable | Ljava/lang/Throwable; |
| Object    | Ljava/lang/Object;    |
| int[]     | [I                    |
| Object[]  | [Ljava/lang/Object;   |
|           |                       |



#### 2.6.1 通过JNI去访问Java类中的字段

#### 2.6.2 访问并修改类实例的字段

#### 2.6.3 访问并修改类的静态字段

```java
package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.Animal;

public class JNIAccessField {
    static {
        System.loadLibrary("native-lib");
    }

    public static int num;

    public native void accessStaticField(Animal animal);

    public native void accessInstanceField(Animal animal);

    public static native void staticAccessInstanceField();
}

```

```c++
#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_accessStaticField(JNIEnv *env, jobject thiz,
                                                          jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetStaticFieldID(cls, "num", "I");
    jint num = env->GetStaticIntField(cls, fid);
    env->SetStaticIntField(cls, fid, ++num);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_accessInstanceField(JNIEnv *env, jobject thiz,
                                                            jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jstring str = env->NewStringUTF("this is new name");
    env->SetObjectField(animal, fid, str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessField_staticAccessInstanceField(JNIEnv *env, jclass cls) {
    jfieldID fid = env->GetStaticFieldID(cls, "num", "I");
    jint num = env->GetStaticIntField(cls, fid);
    env->SetStaticIntField(cls, fid, ++num);
}
```

### 2.7 JNI访问Java类方法

2.7.1 通过JNI去访问Java类中的方法

2.7.2 访问Java类实例的方法

2.7.3 访问Java类的静态方法

| Java                   | JNI                   |
| ---------------------- | --------------------- |
| String fun();          | ()Ljava/lang/String;  |
| long f(int i,Class c); | (ILjava/lang/Class;)J |
| String(byte[] bytes);  | ([B)V                 |

```java
package com.jeremy.jndk.base;

import com.jeremy.jndk.util.LogUtil;

public class Animal {
    protected String name;
    public static int num = 0;

    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public static int getNum() {
        return num;
    }

    // C++调用Java的实例方法
    public void callInstanceMethod(int num) {
        LogUtil.i("call instance method and num is " + num);
    }

    // C++调用Java的类方法
    public static String callStaticMethod(String str) {
        if (str != null) {
            LogUtil.i("call static method with " + str);
        } else {
            LogUtil.i("call static method str is null");
        }

        return "";
    }

    // C++调用java的静态方法
    public static String callStaticMethod(String[] strs, int num) {
        if (strs != null) {
            for (String str : strs) {
                LogUtil.i("str in array is " + str);

            }
        }
        LogUtil.i("num is " + num);
        return "";
    }
}

```

```c++
#include <base.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessMethod_accessStaticMethod(JNIEnv *env, jobject thiz,
                                                            jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetStaticMethodID(cls, "callStaticMethod",
                                           "(Ljava/lang/String;)Ljava/lang/String;");
    jstring str = env->NewStringUTF("jstring");
    env->CallStaticObjectMethod(cls, mid, str);

    jmethodID sMid = env->GetStaticMethodID(cls, "callStaticMethod",
                                            "([Ljava/lang/String;I)Ljava/lang/String;");

    jclass strClass = env->FindClass("java/lang/String");
    int size = 2;
    jobjectArray strArray = env->NewObjectArray(size, strClass, nullptr);
    jstring strItem;
    for (int i = 0; i < size; i ++) {
        strItem = env->NewStringUTF("string in native");
        env->SetObjectArrayElement(strArray, i, strItem);
    }
    env->CallStaticObjectMethod(cls, sMid, strArray, size);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIAccessMethod_accessInstanceMethod(JNIEnv *env, jobject thiz,
                                                              jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetMethodID(cls, "callInstanceMethod", "(I)V");
    env->CallVoidMethod(animal, mid, 2);
}
```



### 2.8 JNI子线程访问Java方法

#### 2.8.1 JNI函数内回调Java方法

#### 2.8.2 JNI函数通过接口参数回调Java方法

#### 2.8.3 JNI子线程如何回调Java的主线程方法

```java
package com.jeremy.jndk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.jeremy.jndk.base.ICallbackMethod;
import com.jeremy.jndk.base.IThreadCallback;
import com.jeremy.jndk.jni.JNIIvokeMethod;
import com.jeremy.jndk.util.LogUtil;

public class JniActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni);
        JNIIvokeMethod jniIvokeMethod = new JNIIvokeMethod();
        findViewById(R.id.button).setOnClickListener(v -> {
            jniIvokeMethod.nativeCallback(() ->
                    LogUtil.i("thread name is " + Thread.currentThread().getName())
            );
            jniIvokeMethod.nativeThreadCallback(() ->
                    LogUtil.i("thread name is " + Thread.currentThread().getName())
            );
        });
    }
}
```

```java
package com.jeremy.jndk.base;

public interface ICallbackMethod {
    void callback();
}
```

```c++
package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.ICallbackMethod;
import com.jeremy.jndk.base.IThreadCallback;

public class JNIIvokeMethod {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public native void nativeCallback(ICallbackMethod iCallbackMethod);

    public native void nativeThreadCallback(IThreadCallback iThreadCallback);
}
```

```c
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
```

```c++
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
```

```c++
//
// Created by JeremyHwc on 2021/4/4.
//

#include <base.h>
#include <pthread.h>
#include <jvm.h>

void *threadCallback(void *);

static jclass threadClazz;
static jmethodID threadMethod;
static jobject threadObject;

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIIvokeMethod_nativeCallback(JNIEnv *env, jobject thiz,
                                                       jobject callback) {
    LOGD("nativeCallback");
    jclass callbackClazz = env->GetObjectClass(callback);
    jmethodID callbackMethod = env->GetMethodID(callbackClazz, "callback", "()V");
    env->CallVoidMethod(callback, callbackMethod);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeremy_jndk_jni_JNIIvokeMethod_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                             jobject callback) {
    threadObject = env->NewGlobalRef(callback);
    threadClazz = env->GetObjectClass(callback);
    threadMethod = env->GetMethodID(threadClazz, "callback", "()V");

    pthread_t handle;
    pthread_create(&handle, nullptr, threadCallback, nullptr);
}

void *threadCallback(void *) {
    // 注意JNIEnv是不可以跨线程的,所以需要在so库加载的时候，将JavaVm进行保存
    JavaVM *gVm = jvm::getJvm();
    JNIEnv *env = nullptr;
    if (gVm->AttachCurrentThread(&env, nullptr) == 0) {
        env->CallVoidMethod(threadObject, threadMethod);

        // DetachCurrentThread方法必须与AttachCurrentThread配套使用
        gVm->DetachCurrentThread();
    }
    return 0;
}
```

### 2.9 JNI访问Java构造方法

#### 2.9.1 JNI调用类的构造方法创建类实例

#### 2.9.2 两种不同的实现方式

```java
private void testJNIConstructorClass() {
        JNIConstructorClass jniConstructorClass = new JNIConstructorClass();
        findViewById(R.id.sample_button).setOnClickListener(v -> {
            LogUtil.i("name is " + jniConstructorClass.allocObjectConstructor().getName());
            LogUtil.i("name is " + jniConstructorClass.invokeAnimalConstructors().getName());
        });
    }
```

```java
package com.jeremy.jndk.jni;

import com.jeremy.jndk.base.Animal;

public class JNIConstructorClass {
    static {
        System.loadLibrary("native-lib");
    }

    public native Animal invokeAnimalConstructors();
    public native Animal allocObjectConstructor();
}

```

```c++
//
// Created by JeremyHwc on 2021/4/7.
//

#include <base.h>
// 方式1
extern "C"
JNIEXPORT jobject JNICALL
Java_com_jeremy_jndk_jni_JNIConstructorClass_invokeAnimalConstructors(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/jeremy/jndk/base/Animal");
    jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jstring name = env->NewStringUTF("this is animal name");
    jobject animal = env->NewObject(cls, mid, name);
    return animal;
}

// 方式2
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

```



## 3. 引用管理和异常处理

### 3.1 JNI引用类型管理

#### 3.1.1 JNI中的三种引用类型

- 全局引用
- 局部引用
- 弱引用

这三种引用如果使用得到，可以提升我们的程序性能。如果使用不得当可能造成程序的内存泄漏，甚至程序崩溃。因此，掌握不同引用类型的使用还是相当重要的。

```c++
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
```

### 3.2 JNI异常处理

#### 3.2.1 JNI调用Java方法时的异常处理

#### 3.2.2 在JNI中抛出异常，交由上层处理

```c++
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
```

## 4. 线程创建与同步、Bitmap处理

### 4.1 JNI线程的创建

- C++ 11存在一个Thread库，可以进行线程的创建
- Posix API介绍及线程库

### 4.2 JNI线程的同步

### 4.3 JNI中Bitmap操作

## 5. 总结