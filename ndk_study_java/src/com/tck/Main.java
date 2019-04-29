package com.tck;

import jdk.nashorn.internal.objects.Global;

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
        //NdkSimple1.callGetUUID();

        //Point point = NdkSimple1.createPoint();
        // System.out.println("point.getX()="+point.getX()+" , point.getY()="+point.getY());

        //数组排序
//        int[] arr = {1, 4, 99, 88};
//        for (int i = 0; i < arr.length; i++) {
//            System.out.print( arr[i] + "\t");
//        }
//        System.out.println("====\n");
//        NdkSimple1.sort(arr);
//        for (int i = 0; i < arr.length; i++) {
//            System.out.print(arr[i] + "\t");
//        }

        //局部引用和全局引用
        NdkSimple1.saveGlobalRef("tck");
        System.out.println(NdkSimple1.getGlobalRef());
        //删除全局引用
        NdkSimple1.delGlobalRef();

        String globalRef = NdkSimple1.getGlobalRef();

        if (globalRef == null) {
            System.out.println("删除成功");
        }else {
            System.out.println("删除失败");
        }
    }
}
