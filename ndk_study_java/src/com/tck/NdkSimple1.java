package com.tck;

public class NdkSimple1 {

    public String name ="tck";
    public static int age =29;


    public native void changeName();
    public native static void changeAge();

    static {
        System.load("D:/c_project/ndk_study/JniSimple/JniSimple/Debug/JniSimple.dll");
    }
}
