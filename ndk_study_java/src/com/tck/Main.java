package com.tck;

/**
 * javah -d ../jni -jni com.tck.NdkSimple1
 * javap -p -s D:\c_project\ndk_study\ndk_study_java\out\production\ndk_study_java\com\tck\Nd
 * kSimple1.class
 */
public class Main {

    public static void main(String[] args) {
       NdkSimple1 ndkSimple = new NdkSimple1();
//        System.out.println("改变之前="+ndkSimple.name);
//        ndkSimple.changeName();
//        System.out.println("改变之后="+ndkSimple.name);

//        System.out.println("改变之前age="+NdkSimple1.age);
//        NdkSimple1.changeAge();
//        System.out.println("改变之后age="+NdkSimple1.age);

        //c调用java方法
       // ndkSimple.callAddMethod();
        NdkSimple1.callGetUUID();
    }
}
