#ifndef _DATESELF_H_
#define _DATESELF_H_

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//
//
//#ifdef __cplusplus
//}
//#endif

#include <jni.h>
#include <android/log.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	long num;
	float score;
	struct CalculateData1 *next;
} CalculateData1;

#define LENGTH sizeof(struct CalculateData1)

int getMaxValue(void);
void add(void);
void printAll(void);

#endif
