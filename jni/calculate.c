#include <jni.h>
#include <android/log.h>
#include <stdio.h>

#include <checksuccess.c>
#include <calculateXY.c>
#include <computer.c>

//���ݵ������������x,y��ֵ
jint Java_com_csh_wuziqi_calculate_Calculate_calculateXY(JNIEnv* env,
		jobject thiz, jint startX, jint startY, jint jiange, jint xp, jint yp,
		jint number) {

	return calculateXY(env, thiz, startX, startY, jiange, xp, yp, number);
}

//�ж��Ƿ�ʤ��
jintArray Java_com_csh_wuziqi_calculate_Calculate_checkSuccess(JNIEnv* env,
		jobject thiz, jintArray jintarray, jint x, jint y, jint type) {

	return checkSuccess(env, thiz, jintarray, x, y, type);
}

//����������
jint Java_com_csh_wuziqi_calculate_Calculate_computerXiaQi(JNIEnv* env,
		jobject thiz, jintArray jintarray, jint xg, jint yg, jint type) {

	__android_log_print(ANDROID_LOG_DEBUG, "com.csh.wuziqi from C",
			"init success----> %s class.", "com/csh/wuziqi/Calculate");

	return computer_next(env, thiz, jintarray, xg, yg, type);
}
