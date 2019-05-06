package com.tck;

import java.util.UUID;

public class NdkSimple1 {

    public String name = "tck";
    public static int age = 29;
    public static String name1;
    public static String name2;



    public int add(int num1, int num2) {
        return num1 + num2;
    }

    public static String getUUID() {
        return UUID.randomUUID().toString();
    }

    public native void changeName();

    public native static void changeAge();

    public native void callAddMethod();

    public static native void callGetUUID();

    public static native Point createPoint();

    public static native void sort(int[] arr);

    public static native void localRef();

    public static native void saveGlobalRef(String str);

    public static native String getGlobalRef();

    public static native void delGlobalRef();

    public static native void staticLocalCache(String value);

    public static native void initStaticCache();

    public static native void exception() throws NoSuchFieldException;


    static {
        System.load("D:/c_project/ndk_study/JniSimple/JniSimple/Debug/JniSimple.dll");
    }
}
