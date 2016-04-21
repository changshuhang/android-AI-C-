#include <checksuccess.h>

//����
jint totalLineNumberCheck = 19;
//ȫ������
jint qipanTwoCheck[19][19];

jintArray checkSuccess(JNIEnv* env, jobject thiz, jintArray jintarray, jint x,
		jint y, jint type) {
	jintArray javaArray;
	jint nativeArray[3];
	int length = totalLineNumberCheck * totalLineNumberCheck;
	jint qipanOne[length];
	int i = 0;

	(*env)->GetIntArrayRegion(env, jintarray, 0, length, qipanOne);
	//��ɶ�ά����
	for (i = 0; i < length; i++) {
		qipanTwoCheck[i / totalLineNumberCheck][i % totalLineNumberCheck] =
				qipanOne[i];
	}
	//�Զ�ά��������ж�
	//�԰˸���������ݽ����ж�
	if (up_bottom(x, y, type) >= 5) {
		nativeArray[0] = 1;
		nativeArray[1] = x;
		nativeArray[2] = y;
	} else if (left_right(x, y, type) >= 5) {
		nativeArray[0] = 1;
		nativeArray[1] = x;
		nativeArray[2] = y;
	} else if (leftup_rightbottom(x, y, type) >= 5) {
		nativeArray[0] = 1;
		nativeArray[1] = x;
		nativeArray[2] = y;
	} else if (leftbottom_righttop(x, y, type) >= 5) {
		nativeArray[0] = 1;
		nativeArray[1] = x;
		nativeArray[2] = y;
	} else {
		nativeArray[0] = 0;
		nativeArray[1] = x;
		nativeArray[2] = y;
	}

	javaArray=(*env)->NewIntArray(env,3);
	(*env)->SetIntArrayRegion(env,javaArray,0,3,nativeArray);

	return javaArray;
}

//up-dowm
int up_bottom(int x, int y, int type) {
	int i = 0;
	int totalNumber = 1;
	//����
	for (i = y - 1; i >= 0; i--) {
		if (qipanTwoCheck[x][i] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
	}

	//����
	for (i = y + 1; i < totalLineNumberCheck; i++) {
		if (qipanTwoCheck[x][i] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
	}

	return totalNumber;
}

//left_right
int left_right(int x, int y, int type) {
	int i = 0;
	int totalNumber = 1;
	//����
	for (i = x - 1; i >= 0; i--) {
		if (qipanTwoCheck[i][y] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
	}

	//����
	for (i = x + 1; i < totalLineNumberCheck; i++) {
		if (qipanTwoCheck[i][y] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
	}

	return totalNumber;
}

//leftup-rightbottom
int leftup_rightbottom(int x, int y, int type) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	//����
	i = x - 1;
	j = y - 1;
	for (; i >= 0 && j >= 0;) {
		if (qipanTwoCheck[i][j] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
		i--;
		j--;
	}

	//����
	i = x + 1;
	j = y + 1;
	for (; i < totalLineNumberCheck && j < totalLineNumberCheck;) {
		if (qipanTwoCheck[i][j] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
		i++;
		j++;
	}

	return totalNumber;
}

//leftbottom-righttop
int leftbottom_righttop(int x, int y, int type) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	//����
	i = x - 1;
	j = y + 1;
	for (; i >= 0 && j < totalLineNumberCheck;) {
		if (qipanTwoCheck[i][j] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
		i--;
		j++;
	}

	//����
	i = x + 1;
	j = y - 1;
	for (; i < totalLineNumberCheck && j >= 0;) {
		if (qipanTwoCheck[i][j] == type) {
			totalNumber++;
			if (totalNumber >= 5) {
				return totalNumber;
			}
		} else {
			break;
		}
		i++;
		j--;
	}

	return totalNumber;
}
