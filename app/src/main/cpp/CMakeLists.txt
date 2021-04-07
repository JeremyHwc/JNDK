# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

#cmake_minimum_required(VERSION 3.10.2)
cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.

project("jndk")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# CMake创建变量,CMake不区分大小写
#SET(var hello)
set(var hello)
# 打印变量的值
message(${var})

message(${CMAKE_CURRENT_LIST_DIR})
IF (true)
    message(${CMAKE_CURRENT_LIST_DIR})
ENDIF ()

# 将cpp文件编译成so动态库的语法
# 其中SHARED表示编译出来的库是动态库，STATIC编译出来就是静态的共享库
add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        people/People.cpp
        jni/jni_access_field.cpp
        jni/jni_access_method.cpp
        jni/jni_reference.cpp
        jni/jni_reference_type.cpp
        jni/jni_basic_type.cpp
        jni/jni_exception.cpp
        jni/jni_string.cpp
        jni/jni_constructor_class.cpp)

add_library(dynamic-lib
        SHARED
        jni/jni_dynamic_load.cpp
        jni/jni_invoke_method.cpp
        jni/jni_thread.cpp
        jni/jvm.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# 将people路径下的文件全部添加到搜索路径
include_directories(people/)
include_directories(base/)

# 查找log库，并命名为log-lib.so
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 将so库进行关联
target_link_libraries(
        dynamic-lib
        ${log-lib}
)

target_link_libraries(
        native-lib
        ${log-lib}
)
