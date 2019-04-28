package com.tck;

import java.util.UUID;

public class NdkSimple1 {

    public String name = "tck";
    public static int age = 29;



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
    static {
        System.load("D:/c_project/ndk_study/JniSimple/JniSimple/Debug/JniSimple.dll");
    }
}
