package com.tck;

public class NdkSimple {
    public native String getSingnaturePassword();

    static {
        System.load("D:/c_project/ndk_study/JniSimple/JniSimple/Debug/JniSimple.dll");
    }
}
