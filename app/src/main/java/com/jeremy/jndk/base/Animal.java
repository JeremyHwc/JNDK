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
