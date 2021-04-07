package com.jeremy.jndk.jni;

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
