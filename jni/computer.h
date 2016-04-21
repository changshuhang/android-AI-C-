#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <jni.h>
#include <android/log.h>
#include <stdio.h>

#include <math.h>
#include <stdlib.h>

#define LOG_TAG    "com.csh.wuziqi from C"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

jint computer_next(JNIEnv* env, jobject thiz, jintArray jintarray, jint x,
		jint y, jint type);

int calculaterMaxSelf(int type);
//ȡ��leftbottom-righttop���������
int getLeftBottomRightUpNumber(int type, int x, int y) ;
//ȡ��leftup-rightbottom���������
int getLeftUpRightBottomNumber(int type, int x, int y);
//ȡ��left_right���������
int getLeftRightNumber(int type, int x, int y);
//ȡ��top_bottom���������
int getTopBottmNumber(int type, int x, int y) ;
//ȡ�ø���
int getWeigthNumber(int dealValue[],int value);
//�ж�һ��null�����Ӷ���
int getIsYouQiZiDuiShou(int x, int y, int type) ;

//��������ӵ�Ȩ��
int calculateWeigthSelf(int dealValue[]);
//��������ӵ�Ȩ��
int calculateWeigthDuiShou(int dealValue[]);
//����Է��¸����Ӻ�����̽����Ӱ��
void dealXiQiZiDuiShou(int type, int x, int y);
//�����Լ��¸����Ӻ�����̽����Ӱ��
void dealXiQiZiSelf(int type, int x, int y);

jint getSecondZuoBiaoXY(int type);
jint getFirstZuoBiaoXYSelf();
jint getFirstZuoBiaoXYDuiFang(int type);
int getTotalQiZiNumber(int type);
int getRand0Max(int max);
int calculateFangXiang(int x, int y);

#endif
