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
//取得leftbottom-righttop方向的数据
int getLeftBottomRightUpNumber(int type, int x, int y) ;
//取得leftup-rightbottom方向的数据
int getLeftUpRightBottomNumber(int type, int x, int y);
//取得left_right方向的数据
int getLeftRightNumber(int type, int x, int y);
//取得top_bottom方向的数据
int getTopBottmNumber(int type, int x, int y) ;
//取得个数
int getWeigthNumber(int dealValue[],int value);
//判断一个null的棋子对手
int getIsYouQiZiDuiShou(int x, int y, int type) ;

//计算该棋子的权重
int calculateWeigthSelf(int dealValue[]);
//计算该棋子的权重
int calculateWeigthDuiShou(int dealValue[]);
//假设对方下该棋子后对棋盘界面的影响
void dealXiQiZiDuiShou(int type, int x, int y);
//假设自己下该棋子后对棋盘界面的影响
void dealXiQiZiSelf(int type, int x, int y);

jint getSecondZuoBiaoXY(int type);
jint getFirstZuoBiaoXYSelf();
jint getFirstZuoBiaoXYDuiFang(int type);
int getTotalQiZiNumber(int type);
int getRand0Max(int max);
int calculateFangXiang(int x, int y);

#endif
