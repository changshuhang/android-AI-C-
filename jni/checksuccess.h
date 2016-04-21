#ifndef _CHECKSUCCESS_H_
#define _CHECKSUCCESS_H_

#include <jni.h>
#include <android/log.h>
#include <stdio.h>

jintArray checkSuccess(JNIEnv* env, jobject thiz, jintArray jintarray, jint x,
		jint y, jint type);
int up_bottom(int x, int y, int type);
int left_right(int x, int y, int type);
int leftup_rightbottom(int x, int y, int type);
int leftbottom_righttop(int x, int y, int type);

#endif
