
#include "com_tck_NdkSimple.h"
#include "com_tck_NdkSimple1.h"


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