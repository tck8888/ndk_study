#include <stdio.h>

//定义一个结构体指针的别名
/*typedef const struct JNINativeInterface * JNIEnv;

struct JNINativeInterface
{
	//结构体方法指针
	char* (*NewStringUTF)(JNIEnv*,char*);
};

char* NewStringUTF(JNIEnv* env, char* c_str) {
	//c_str->jstring
	return c_str;
}


char *getSingnaturePassword(JNIEnv* env) {
	//JNIEnv* 其实是一个二级指针 所以->调用的情况必须是一级指针
	//*取值
	return (*env)->NewStringUTF(env, "kkk");
}

void main(){
	 JNINativeInterface nativeInterface;
	//结构体方法指针赋值
	nativeInterface.NewStringUTF = NewStringUTF;
	//传递的参数是JNIEnv*

	JNIEnv env = &nativeInterface;//一级指针
	JNIEnv* jniEnv = &env;//二级指针
	//
	char* jsting = getSingnaturePassword(jniEnv);

	//传递java层
	printf("%s", jsting);

getchar();
}*/