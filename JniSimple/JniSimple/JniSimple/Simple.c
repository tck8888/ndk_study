
#include "com_tck_NdkSimple.h"
#include "com_tck_NdkSimple1.h"

#include <stdlib.h>

/*

*/
JNIEXPORT jstring JNICALL Java_com_tck_NdkSimple_getSingnaturePassword
(JNIEnv* env, jobject jobj) {
	//JNIEnv* 其实是一个二级指针 所以->调用的情况必须是一级指针
	//*取值
	return (*env)->NewStringUTF(env,"1234567");
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_changeName
(JNIEnv* env, jobject jobj) {
	//3.
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2. 获取jfield
	jfieldID j_field = (*env)->GetFieldID(env, j_clz,"name", "Ljava/lang/String;");
	//1. 获取name属性
	jstring j_string=(*env)->GetObjectField(env, jobj, j_field);

	
	char* c_str = (*env)->GetStringUTFChars(env, j_string, NULL);

	printf("name is %s\n", c_str);
	jstring yysName = (*env)->NewStringUTF(env,"yys");
	(*env)->SetObjectField(env, jobj, j_field, yysName);

}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_changeAge
(JNIEnv* env, jclass jcls) {
	jfieldID j_field = (*env)->GetStaticFieldID(env, jcls,"age", "I");
	jint j_int = (*env)->GetStaticIntField(env, jcls,j_field);

	printf("old age is %d\n", j_int);
	j_int += 20;
	(*env)->SetStaticIntField(env, jcls, j_field, j_int);

}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_callAddMethod
(JNIEnv* env, jobject jobj) {
	//去调用java的方法
	jclass jclazz = (*env)->GetObjectClass(env, jobj);
	jmethodID  j_mid = (*env)->GetMethodID(env, jclazz, "add","(II)I" );
	jint j_int = (*env)->CallIntMethod(env, jobj, j_mid,2,3);
	printf("j_int=%d", j_int);
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_callGetUUID
(JNIEnv* env, jclass jcls) {
	jmethodID  j_mid = (*env)->GetStaticMethodID(env, jcls, "getUUID", "()Ljava/lang/String;");
	jstring j_string = (*env)->CallStaticObjectMethod(env, jcls, j_mid);
	char *c_str = (*env)->GetStringUTFChars(env, j_string,NULL);
	//回收
	(*env)->ReleaseStringUTFChars(env, j_string, c_str);
	printf("c_uuid = %s", c_str);

}

JNIEXPORT jobject JNICALL Java_com_tck_NdkSimple1_createPoint
(JNIEnv* env, jclass jcls) {
	

	jclass point_clas = (*env)->FindClass(env, "com/tck/Point");
	//构建java层的对象是，构造函数的id ,构造函数的方法<init>
	jmethodID  j_mid = (*env)->GetMethodID(env, point_clas,"<init>","(II)V" );

	jobject j_point = (*env)->NewObject(env, point_clas, j_mid, 11, 12);

	//使用set方法给属性赋值
	jmethodID  j_mids = (*env)->GetMethodID(env, point_clas, "setX","(I)V");
	(*env)->CallVoidMethod(env, j_point, j_mids,666);

	//通过SetIntField设置属性的值
	jfieldID j_field=(*env)->GetFieldID(env, point_clas,"y","I");
	(*env)->SetIntField(env, j_point, j_field,1000);

	return j_point;

}
int compare(const jint* number1, const jint* number2) {
	return *number1 - *number2;
}
//排序
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_sort
(JNIEnv* env, jclass jcls, jintArray jarr) {
	jint *intArray = (*env)->GetIntArrayElements(env, jarr,NULL);
	int length = (*env)->GetArrayLength(env, jarr);
	//第一个参数：数组的首地址
	//数组的长度
	//数组数据类型的大小
	//数组的一个比较方法指针
	qsort(intArray,length,sizeof(int), compare);

	//同步数据
	//0:同步数据到jarr 同时释放intArray
	//JNI_COMMIT:同步数据 不会释放
	//JNI_ABORT:不同步数据 会释放
	(*env)->ReleaseIntArrayElements(env, jarr, intArray, 0);
}

jstring globalStr;

//native构建的java对象，管理
//native构建的内存管理
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_localRef
(JNIEnv* env, jclass jcls) {

	jclass str_claz = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, str_claz, "<init>", "()V");
	jobject jobj = (*env)->NewObject(env, str_claz, jmid);

	//回收,不能在使用 静态开辟不需要
	(*env)->DeleteLocalRef(env, jobj);
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_saveGlobalRef
(JNIEnv* env, jclass jcls, jstring jstr) {
	//保存全局变量

	globalStr = (*env)->NewGlobalRef(env, jstr);
}

JNIEXPORT jstring JNICALL Java_com_tck_NdkSimple1_getGlobalRef
(JNIEnv* env, jclass jcls ) {
	/*if (globalStr!=NULL) {
		return globalStr;
	}
	else {
		return "";
	}*/
	return globalStr;
	
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_delGlobalRef
(JNIEnv* env, jclass jcls) {
	(*env)->DeleteGlobalRef(env, globalStr);
	//globalStr = NULL;
	
}


//局部缓存
/*JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_staticLocalCache
(JNIEnv* env, jclass jcls, jstring str) {
	
	static jfieldID jid = NULL;
	if (jid==NULL) {
		jid = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	}
	else {
		printf("filedId is Not NULL\n");
	}
	
	(*env)->SetStaticObjectField(env, jcls, jid, str);
}*/



//全局缓存
static jfieldID jid_name = NULL;
static jfieldID jid_name1 = NULL;
static jfieldID jid_name2 = NULL;

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_staticLocalCache
(JNIEnv* env, jclass jcls, jstring str) {
	(*env)->SetStaticObjectField(env, jcls, jid_name, str);
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_initStaticCache
(JNIEnv* env, jclass jcls) {
	jid_name = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	jid_name1 = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	jid_name2 = (*env)->GetStaticFieldID(env, jcls, "name2", "Ljava/lang/String;");
}

//异常处理
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_exception
(JNIEnv* env, jclass jcls) {
	jfieldID jid = (*env)->GetStaticFieldID(env, jcls, "name3", "Ljava/lang/String;");
	//1.补救措施
	jthrowable throwable = (*env)->ExceptionOccurred(env);
	if (throwable) {
		//清除异常
		printf("有异常");
		(*env)->ExceptionClear(env);
		jclass jclzz = (*env)->FindClass(env,"java/lang/NoSuchFieldException" );
		(*env)->ThrowNew(env, jclzz,"没有找到name3");
		return;
			//jid = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	}

	jstring name = (*env)->NewStringUTF(env, "tck");
	(*env)->SetStaticObjectField(env, jcls, jid, name);

}



/*void main() {

	//常量指针 值不能改 地址是可以改 const 在*之前
	//常量变量 不能再次赋值

	//指针常量 地址不能被重新赋值 const 在*之后
	//


}*/