
#include "com_tck_NdkSimple.h"
#include "com_tck_NdkSimple1.h"

#include <stdlib.h>

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

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_callAddMethod
(JNIEnv* env, jobject jobj) {
	//ȥ����java�ķ���
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
	//����
	(*env)->ReleaseStringUTFChars(env, j_string, c_str);
	printf("c_uuid = %s", c_str);

}

JNIEXPORT jobject JNICALL Java_com_tck_NdkSimple1_createPoint
(JNIEnv* env, jclass jcls) {
	

	jclass point_clas = (*env)->FindClass(env, "com/tck/Point");
	//����java��Ķ����ǣ����캯����id ,���캯���ķ���<init>
	jmethodID  j_mid = (*env)->GetMethodID(env, point_clas,"<init>","(II)V" );

	jobject j_point = (*env)->NewObject(env, point_clas, j_mid, 11, 12);

	//ʹ��set���������Ը�ֵ
	jmethodID  j_mids = (*env)->GetMethodID(env, point_clas, "setX","(I)V");
	(*env)->CallVoidMethod(env, j_point, j_mids,666);

	//ͨ��SetIntField�������Ե�ֵ
	jfieldID j_field=(*env)->GetFieldID(env, point_clas,"y","I");
	(*env)->SetIntField(env, j_point, j_field,1000);

	return j_point;

}
int compare(const jint* number1, const jint* number2) {
	return *number1 - *number2;
}
//����
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_sort
(JNIEnv* env, jclass jcls, jintArray jarr) {
	jint *intArray = (*env)->GetIntArrayElements(env, jarr,NULL);
	int length = (*env)->GetArrayLength(env, jarr);
	//��һ��������������׵�ַ
	//����ĳ���
	//�����������͵Ĵ�С
	//�����һ���ȽϷ���ָ��
	qsort(intArray,length,sizeof(int), compare);

	//ͬ������
	//0:ͬ�����ݵ�jarr ͬʱ�ͷ�intArray
	//JNI_COMMIT:ͬ������ �����ͷ�
	//JNI_ABORT:��ͬ������ ���ͷ�
	(*env)->ReleaseIntArrayElements(env, jarr, intArray, 0);
}

jstring globalStr;

//native������java���󣬹���
//native�������ڴ����
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_localRef
(JNIEnv* env, jclass jcls) {

	jclass str_claz = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, str_claz, "<init>", "()V");
	jobject jobj = (*env)->NewObject(env, str_claz, jmid);

	//����,������ʹ�� ��̬���ٲ���Ҫ
	(*env)->DeleteLocalRef(env, jobj);
}

JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_saveGlobalRef
(JNIEnv* env, jclass jcls, jstring jstr) {
	//����ȫ�ֱ���

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


//�ֲ�����
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



//ȫ�ֻ���
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

//�쳣����
JNIEXPORT void JNICALL Java_com_tck_NdkSimple1_exception
(JNIEnv* env, jclass jcls) {
	jfieldID jid = (*env)->GetStaticFieldID(env, jcls, "name3", "Ljava/lang/String;");
	//1.���ȴ�ʩ
	jthrowable throwable = (*env)->ExceptionOccurred(env);
	if (throwable) {
		//����쳣
		printf("���쳣");
		(*env)->ExceptionClear(env);
		jclass jclzz = (*env)->FindClass(env,"java/lang/NoSuchFieldException" );
		(*env)->ThrowNew(env, jclzz,"û���ҵ�name3");
		return;
			//jid = (*env)->GetStaticFieldID(env, jcls, "name1", "Ljava/lang/String;");
	}

	jstring name = (*env)->NewStringUTF(env, "tck");
	(*env)->SetStaticObjectField(env, jcls, jid, name);

}



/*void main() {

	//����ָ�� ֵ���ܸ� ��ַ�ǿ��Ը� const ��*֮ǰ
	//�������� �����ٴθ�ֵ

	//ָ�볣�� ��ַ���ܱ����¸�ֵ const ��*֮��
	//


}*/