#include <stdio.h>

//����һ���ṹ��ָ��ı���
/*typedef const struct JNINativeInterface * JNIEnv;

struct JNINativeInterface
{
	//�ṹ�巽��ָ��
	char* (*NewStringUTF)(JNIEnv*,char*);
};

char* NewStringUTF(JNIEnv* env, char* c_str) {
	//c_str->jstring
	return c_str;
}


char *getSingnaturePassword(JNIEnv* env) {
	//JNIEnv* ��ʵ��һ������ָ�� ����->���õ����������һ��ָ��
	//*ȡֵ
	return (*env)->NewStringUTF(env, "kkk");
}

void main(){
	 JNINativeInterface nativeInterface;
	//�ṹ�巽��ָ�븳ֵ
	nativeInterface.NewStringUTF = NewStringUTF;
	//���ݵĲ�����JNIEnv*

	JNIEnv env = &nativeInterface;//һ��ָ��
	JNIEnv* jniEnv = &env;//����ָ��
	//
	char* jsting = getSingnaturePassword(jniEnv);

	//����java��
	printf("%s", jsting);

getchar();
}*/