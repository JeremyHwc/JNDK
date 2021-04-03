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
- Java中调用native方法的函数类型
- JNI头文件的创建方式以及命名方式

### 2.2 函数的动态注册

### 2.3 Java与JNI基础数据类型转换

### 2.4 Java与JNI字符串转换

### 2.5 Java与JNI引用类型转换

### 2.6 JNI方法Java类字段

### 2.7 JNI访问Java类方法

### 2.8 JNI子线程访问Java方法

### 2.9 JNI访问Java构造方法

## 3. 引用管理和异常处理

### 3.1 JNI引用类型管理

### 3.2 JNI异常处理

## 4. 线程创建与同步、Bitmap处理

### 4.1 JNI线程的创建

### 4.2 JNI线程的同步

### 4.3 JNI中Bitmap操作

## 5. 总结