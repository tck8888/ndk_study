
#include "com_tck_NdkSimple.h"
#include "com_tck_NdkSimple1.h"


/*

*/
JNIEXPORT jstring JNICALL Java_com_tck_NdkSimple_getSingnaturePassword
(JNIEnv* env, jobject jobj) {
	//JNIEnv* ��ʵ��һ������ָ�� ����->���õ����������һ��ָ��
	//*ȡֵ
	return (*env)->NewStringUTF(env,"1234567");
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_changeName
(JNIEnv* env, jobject jobj) {
	//3.
	jclass j_clz = (*env)->GetObjectClass(env, jobj);

	//2. ��ȡjfield
	jfieldID j_field = (*env)->GetFieldID(env, j_clz,"name", "Ljava/lang/String;");
	//1. ��ȡname����
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