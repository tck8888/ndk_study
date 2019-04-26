package com.tck;

/**
 * javah -d ../jni -jni com.tck.NdkSimple1
 */
public class Main {

    public static void main(String[] args) {
//        NdkSimple1 ndkSimple = new NdkSimple1();
//        System.out.println("改变之前="+ndkSimple.name);
//        ndkSimple.changeName();
//        System.out.println("改变之后="+ndkSimple.name);

        System.out.println("改变之前age="+NdkSimple1.age);
        NdkSimple1.changeAge();
        System.out.println("改变之后age="+NdkSimple1.age);
    }
}
