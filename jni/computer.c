#include <computer.h>

#include "dateself.c"

//����
jint totalLineNumberComputer = 19;
//ȫ������
jint qipanTwoComputer[19][19];

//x,y����Է��ո��µ����ӣ�type�����Լ�����Ӫ
jint computer_next(JNIEnv* env, jobject thiz, jintArray jintarray, jint x,
		jint y, jint type) {
	int length = totalLineNumberComputer * totalLineNumberComputer;
	jint qipanOne[length];
	//�Լ���Ӫ�����ӵĸ���
	int selfQiZiNumber = 0;
	int i = 0;
	(*env)->GetIntArrayRegion(env, jintarray, 0, length, qipanOne);
	//��ɶ�ά����
	for (i = 0; i < length; i++) {
		qipanTwoComputer[i / totalLineNumberComputer][i
				% totalLineNumberComputer] = qipanOne[i];
	}

	//1.��ͳ���Լ���Ӫ�����ӵĸ���
	selfQiZiNumber = getTotalQiZiNumber(type);
	LOGI("init success----> %d", selfQiZiNumber);

	if (selfQiZiNumber <= 0) {
		//�µ�һ������ʱ
		return getFirstZuoBiaoXYDuiFang(type);
	} else if (selfQiZiNumber == 1) {
		//�µ�һ������ʱ
		LOGI("init type----> %d", type);
		return getSecondZuoBiaoXY(type);
	} else {
		//�����������Լ������巽ʽ
		return calculaterMaxSelf(type);
	}
}

//�������������Լ��µ�����
int calculaterMaxSelf(int type) {
	int i = 0;
	int j = 0;
	int tempValue = 0;
	int duishouType = 0;

	if (type == 1) {
		duishouType = 2;
	} else {
		duishouType = 1;
	}

	//�������
	clear();

	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] == 0) {
				//���ĵ�ΪNULLʱ�Ž������ݼ���
				//1--�ȼ����Լ�
				tempValue = getIsYouQiZi(i, j, type);
				if (tempValue == -1) {
					//���������ۼ���
				} else if (tempValue == 0) {
					//�Ա�û���Լ��ĵ�,�����м���
				} else {
					//�������ۼ���
					dealXiQiZiSelf(type, i, j);
				}
				//2--�������
				tempValue = getIsYouQiZiDuiShou(i, j, duishouType);
				if (tempValue == -1) {
					//���������ۼ���
				} else if (tempValue == 0) {
					//�Ա�û���Լ��ĵ�,�����м���
				} else {
					//�������ۼ���
					dealXiQiZiDuiShou(duishouType, i, j);
				}
			}
		}
	}

	//����
	selectSortSTL();

	//�������ݼ���
	LOGI("last jihe----> %s", "zui hou de shu ju ji he !");
	printAll();

	//ȡ���������ֵ
	return getMaxValue();

}

//�����Լ��¸����Ӻ�����̽����Ӱ��
void dealXiQiZiSelf(int type, int x, int y) {
	struct CalculateData1 *jiedian;
	int dealValue[4];
	int i = 0;
	int j = 0;
	int sortTemp = 0;
	//1,top_bottom
	dealValue[0] = getTopBottmNumber(type, x, y);
	//2,left_right
	dealValue[1] = getLeftRightNumber(type, x, y);
	//3,leftup-rightbottom
	dealValue[2] = getLeftUpRightBottomNumber(type, x, y);
	//4,leftbottom-righttop
	dealValue[3] = getLeftBottomRightUpNumber(type, x, y);

	//�Խ����������
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			if (dealValue[j] > dealValue[i]) {
				sortTemp = dealValue[i];
				dealValue[i] = dealValue[j];
				dealValue[j] = sortTemp;
			}
		}
	}

	//�Խ�����д���
	LOGI("deal jieg----> %d,%d,%d,%d,%d,%d", x, y, dealValue[0], dealValue[1],
			dealValue[2], dealValue[3]);
	jiedian = getNew();
	jiedian->weight = calculateWeigthSelf(dealValue);
	jiedian->x = x;
	jiedian->y = y;
	jiedian->number = 1;

	add(jiedian);
}

//����Է��¸����Ӻ�����̽����Ӱ��
void dealXiQiZiDuiShou(int type, int x, int y) {
	struct CalculateData1 *jiedian;
	int dealValue[4];
	int i = 0;
	int j = 0;
	int sortTemp = 0;
	//1,top_bottom
	dealValue[0] = getTopBottmNumber(type, x, y);
	//2,left_right
	dealValue[1] = getLeftRightNumber(type, x, y);
	//3,leftup-rightbottom
	dealValue[2] = getLeftUpRightBottomNumber(type, x, y);
	//4,leftbottom-righttop
	dealValue[3] = getLeftBottomRightUpNumber(type, x, y);

	//�Խ����������
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			if (dealValue[j] > dealValue[i]) {
				sortTemp = dealValue[i];
				dealValue[i] = dealValue[j];
				dealValue[j] = sortTemp;
			}
		}
	}

	//�Խ�����д���
	LOGI("deal jieg----> %d,%d,%d,%d,%d,%d", x, y, dealValue[0], dealValue[1],
			dealValue[2], dealValue[3]);
	jiedian = getNew();
	jiedian->weight = calculateWeigthDuiShou(dealValue);
	jiedian->x = x;
	jiedian->y = y;
	jiedian->number = 1;

	add(jiedian);
}

//��������ӵ�Ȩ��
int calculateWeigthDuiShou(int dealValue[]) {
	int weigth = 0;
	int temp = 0;
	if (getWeigthNumber(dealValue, 50) > 0 || getWeigthNumber(dealValue, 51) > 0
			|| getWeigthNumber(dealValue, 52) > 0) {
		//��52,51,50, ����ǻ������Ļ�����990��
		weigth = 990;
	} else if (getWeigthNumber(dealValue, 42) > 0
			|| getWeigthNumber(dealValue, 41) > 1) {
		//��42, ����ǻ������Ļ�����800��--�ͷ�
		//����ϸ��
		if (getWeigthNumber(dealValue, 41) == 1) {
			weigth = 750 + 40;
		} else if (getWeigthNumber(dealValue, 32) > 0) {
			temp = getWeigthNumber(dealValue, 32);
			weigth = 750 + temp * 9;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 750 + temp * 8;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 750 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 750 + temp * 5;
		} else {
			weigth = 750;
		}
	} else if (getWeigthNumber(dealValue, 32) > 1) {
		//��32>1, ����ǻ������Ļ�����960��--�׷�
		//����ϸ��
		if (getWeigthNumber(dealValue, 32) == 1) {
			weigth = 650 + 40;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 650 + temp * 9;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 650 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 650 + temp * 5;
		} else {
			weigth = 650;
		}
	} else if (getWeigthNumber(dealValue, 41) == 1) {
		//��41==1, ����ǻ������Ļ�����550��
		if (getWeigthNumber(dealValue, 32) > 0) {
			temp = getWeigthNumber(dealValue, 32);
			weigth = 600 + temp * 9;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 600 + temp * 8;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 600 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 600 + temp * 5;
		} else {
			weigth = 600;
		}
	} else if (getWeigthNumber(dealValue, 32) == 1) {
		//��32==1, ����ǻ������Ļ�����450��
		if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 600 + temp * 9;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 600 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 600 + temp * 5;
		} else {
			weigth = 600;
		}
	} else if (getWeigthNumber(dealValue, 22) > 1) {
		//��22>1, ����ǻ������Ļ�����800��
		if (getWeigthNumber(dealValue, 22) == 1) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 250 + 40;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 250 + temp * 5;
		} else {
			weigth = 250;
		}
	} else {
		if (getWeigthNumber(dealValue, 22) == 1) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 150 + 40;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 150 + temp * 5;
		} else {
			weigth = 150;
		}
	}

	return weigth;
}

//��������ӵ�Ȩ��
int calculateWeigthSelf(int dealValue[]) {
	int weigth = 0;
	int temp = 0;
	if (getWeigthNumber(dealValue, 50) > 0 || getWeigthNumber(dealValue, 51) > 0
			|| getWeigthNumber(dealValue, 52) > 0) {
		//��52,51,50, ����ǻ������Ļ�����1000��
		weigth = 1000;
	} else if (getWeigthNumber(dealValue, 42) > 0
			|| getWeigthNumber(dealValue, 41) > 1) {
		//��42, ����ǻ������Ļ�����800��--�׷�
		//����ϸ��
		if (getWeigthNumber(dealValue, 41) == 1) {
			weigth = 800 + 50;
		} else if (getWeigthNumber(dealValue, 32) > 0) {
			temp = getWeigthNumber(dealValue, 32);
			weigth = 800 + temp * 9;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 800 + temp * 8;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 800 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 800 + temp * 5;
		} else {
			weigth = 800;
		}
	} else if (getWeigthNumber(dealValue, 32) > 1) {
		//��32>1, ����ǻ������Ļ�����960��--�׷�
		//����ϸ��
		if (getWeigthNumber(dealValue, 32) == 1) {
			weigth = 700 + 50;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 700 + temp * 9;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 700 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 700 + temp * 5;
		} else {
			weigth = 700;
		}
	} else if (getWeigthNumber(dealValue, 41) == 1) {
		//��41==1, ����ǻ������Ļ�����940��
		if (getWeigthNumber(dealValue, 32) > 0) {
			temp = getWeigthNumber(dealValue, 32);
			weigth = 600 + temp * 9;
		} else if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 600 + temp * 8;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 600 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 600 + temp * 5;
		} else {
			weigth = 600;
		}
	} else if (getWeigthNumber(dealValue, 32) == 1) {
		//��32==1, ����ǻ������Ļ�����900��
		if (getWeigthNumber(dealValue, 31) > 0) {
			temp = getWeigthNumber(dealValue, 31);
			weigth = 600 + temp * 9;
		} else if (getWeigthNumber(dealValue, 22) > 0) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 600 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 600 + temp * 5;
		} else {
			weigth = 600;
		}
	} else if (getWeigthNumber(dealValue, 22) > 1) {
		//��22>1, ����ǻ������Ļ�����800��
		if (getWeigthNumber(dealValue, 22) == 1) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 300 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 300 + temp * 5;
		} else {
			weigth = 300;
		}
	} else {
		if (getWeigthNumber(dealValue, 22) == 1) {
			temp = getWeigthNumber(dealValue, 22);
			weigth = 200 + temp * 6;
		} else if (getWeigthNumber(dealValue, 21) > 0) {
			temp = getWeigthNumber(dealValue, 21);
			weigth = 200 + temp * 5;
		} else {
			weigth = 200;
		}
	}

	return weigth;
}

//ȡ�ø���
int getWeigthNumber(int dealValue[], int value) {
	int number = 0;
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (value == dealValue[i]) {
			number++;
		}
	}

	return number;
}

//�ж�һ��null�����Ӷ���
int getIsYouQiZiDuiShou(int x, int y, int type) {
	if (qipanTwoComputer[x][y] != 0) {
		//��λ���Ѿ���������
		return -1;
	} else {
		//����
		if (x - 1 >= 0 && y - 1 >= 0
				&& qipanTwoComputer[x - 1][y - 1] == type) {
			return 1;
		}
		//��
		if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == type) {
			return 1;
		}
		//����
		if (x + 1 < totalLineNumberComputer && y - 1 >= 0
				&& qipanTwoComputer[x + 1][y - 1] == type) {
			return 1;
		}
		//��
		if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == type) {
			return 1;
		}
		//��
		if (x + 1 < totalLineNumberComputer && y >= 0
				&& qipanTwoComputer[x + 1][y] == type) {
			return 1;
		}
		//����
		if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x - 1][y + 1] == type) {
			return 1;
		}
		//��
		if (x >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x][y + 1] == type) {
			return 1;
		}
		//����
		if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x + 1][y + 1] == type) {
			return 1;
		}

		//û��ָ��������
		return 0;
	}
}

//�ж�һ��null�������Ա��Ƿ���ָ�����͵�����
int getIsYouQiZi(int x, int y, int type) {
	if (qipanTwoComputer[x][y] != 0) {
		//��λ���Ѿ���������
		return -1;
	} else {
		//����
		if (x - 1 >= 0 && y - 1 >= 0
				&& qipanTwoComputer[x - 1][y - 1] == type) {
			return 1;
		}
		//��
		if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == type) {
			return 1;
		}
		//����
		if (x + 1 < totalLineNumberComputer && y - 1 >= 0
				&& qipanTwoComputer[x + 1][y - 1] == type) {
			return 1;
		}
		//��
		if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == type) {
			return 1;
		}
		//��
		if (x + 1 < totalLineNumberComputer && y >= 0
				&& qipanTwoComputer[x + 1][y] == type) {
			return 1;
		}
		//����
		if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x - 1][y + 1] == type) {
			return 1;
		}
		//��
		if (x >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x][y + 1] == type) {
			return 1;
		}
		//����
		if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x + 1][y + 1] == type) {
			return 1;
		}

		//û��ָ��������
		return 0;
	}
}

//ȡ�õڶ��������ӵ�����
jint getSecondZuoBiaoXY(int type) {
	int i = 0, j = 0;
	int value = -1;
	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] == type) {
				//�ҵ���һ���µ����ӣ��ж�ѭ��
				value = 100 * i + j;
				break;
			}
			if (value != -1) {
				break;
			}
		}
	}

	return calculateFangXiang(value / 100, value % 100);
}

//ȡ�õ�һ�������ӵ�����,�Լ�����
jint getFirstZuoBiaoXYDuiFang(int type) {
	int i = 0, j = 0;
	int value = -1;

	//�ҵ��Ѿ��µ�Ψһ������
	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] != 0) {
				//�ҵ���һ���µ����ӣ��ж�ѭ��
				value = 100 * i + j;
				break;
			}
			if (value != -1) {
				break;
			}
		}
	}

	return calculateFangXiang(value / 100, value % 100);
}

//ȡ�õ�һ�������ӵ�����,�Լ�����
jint getFirstZuoBiaoXYSelf() {
	jint first[] = { 8 * 100 + 8, 9 * 100 + 8, 10 * 100 + 8, 8 * 100 + 9, 9
			* 100 + 9, 10 * 100 + 9, 8 * 100 + 10, 9 * 100 + 10, 10 * 100 + 10 };
	int temp1 = sizeof(first);
	int temp2 = sizeof(jint);
	int temp3 = temp1 / temp2;
	int temp4 = getRand0Max(temp3);
	return first[temp4];
}

//ͳ�����ӵĸ���
int getTotalQiZiNumber(int type) {
	int totalNumber = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] == type) {
				totalNumber++;
			}
		}
	}

	return totalNumber;
}

//ȡ��һ��0-max���������
int getRand0Max(int max) {
	return (int) (rand() % max);
}

//�ж��м����������������
int calculateFangXiang(int x, int y) {
	int qiziXY[8];
	int totalFangXiang = 0;

	//����
	if (x - 1 >= 0 && y - 1 >= 0 && qipanTwoComputer[x - 1][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y - 1);
		totalFangXiang++;
	}
	//��
	if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x) + (y - 1);
		totalFangXiang++;
	}
	//����
	if (x + 1 < totalLineNumberComputer && y - 1 >= 0
			&& qipanTwoComputer[x + 1][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y - 1);
		totalFangXiang++;
	}
	//��
	if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y);
		totalFangXiang++;
	}
	//��
	if (x + 1 < totalLineNumberComputer && y >= 0
			&& qipanTwoComputer[x + 1][y] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y);
		totalFangXiang++;
	}
	//����
	if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x - 1][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y + 1);
		totalFangXiang++;
	}
	//��
	if (x >= 0 && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x) + (y + 1);
		totalFangXiang++;
	}
	//����
	if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x + 1][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y + 1);
		totalFangXiang++;
	}

	return qiziXY[getRand0Max(totalFangXiang)];
}

//ȡ��leftbottom-righttop���������
int getLeftBottomRightUpNumber(int type, int x, int y) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	int houtou = 0;
	//����
	i = x - 1;
	j = y + 1;
	for (; i >= 0 && j < totalLineNumberCheck;) {
		if (qipanTwoComputer[i][j] == type) {
			totalNumber++;
		} else {
			break;
		}
		i--;
		j++;
	}
	if (i >= 0 && j < totalLineNumberCheck) {
		if (qipanTwoComputer[i][j] == 0) {
			houtou++;
		}
	}

	//����
	i = x + 1;
	j = y - 1;
	for (; i < totalLineNumberCheck && j >= 0;) {
		if (qipanTwoComputer[i][j] == type) {
			totalNumber++;
		} else {
			break;
		}
		i++;
		j--;
	}

	if (i >= 0 && j < totalLineNumberCheck) {
		if (qipanTwoComputer[i][j] == 0) {
			houtou++;
		}
	}

	if (totalNumber >= 5) {
		totalNumber = 5;
	}

	return totalNumber * 10 + houtou;
}

//ȡ��leftup-rightbottom���������
int getLeftUpRightBottomNumber(int type, int x, int y) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	int houtou = 0;
	//����
	i = x - 1;
	j = y - 1;
	for (; i >= 0 && j >= 0;) {
		if (qipanTwoComputer[i][j] == type) {
			totalNumber++;
		} else {
			break;
		}
		i--;
		j--;
	}

	if (i >= 0 && j < totalLineNumberCheck) {
		if (qipanTwoComputer[i][j] == 0) {
			houtou++;
		}
	}

	//����
	i = x + 1;
	j = y + 1;
	for (; i < totalLineNumberCheck && j < totalLineNumberCheck;) {
		if (qipanTwoComputer[i][j] == type) {
			totalNumber++;
		} else {
			break;
		}
		i++;
		j++;
	}

	if (i < totalLineNumberCheck && j < totalLineNumberCheck) {
		if (qipanTwoComputer[i][j] == 0) {
			houtou++;
		}
	}

	if (totalNumber >= 5) {
		totalNumber = 5;
	}

	return totalNumber * 10 + houtou;
}

//ȡ��left_right���������
int getLeftRightNumber(int type, int x, int y) {
	int i = 0;
	int totalNumber = 1;
	int houtou = 0;
	//����
	for (i = x - 1; i >= 0; i--) {
		if (qipanTwoComputer[i][y] == type) {
			totalNumber++;
		} else {
			break;
		}
	}

	if (i >= 0) {
		if (qipanTwoComputer[i][y] == 0) {
			houtou++;
		}
	}

	//����
	for (i = x + 1; i < totalLineNumberCheck; i++) {
		if (qipanTwoComputer[i][y] == type) {
			totalNumber++;
		} else {
			break;
		}
	}

	if (i < totalLineNumberCheck) {
		if (qipanTwoComputer[i][y] == 0) {
			houtou++;
		}
	}

	if (totalNumber >= 5) {
		totalNumber = 5;
	}

	return totalNumber * 10 + houtou;
}

//ȡ��top_bottom���������
int getTopBottmNumber(int type, int x, int y) {
	int i = 0;
	int totalNumber = 1;
	int houtou = 0;
	//����
	for (i = y - 1; i >= 0; i--) {
		if (qipanTwoComputer[x][i] == type) {
			totalNumber++;
		} else {
			break;
		}
	}

	if (i >= 0) {
		if (qipanTwoComputer[x][i] == 0) {
			houtou++;
		}
	}

	//����
	for (i = y + 1; i < totalLineNumberCheck; i++) {
		if (qipanTwoComputer[x][i] == type) {
			totalNumber++;
		} else {
			break;
		}
	}

	if (i < totalLineNumberCheck) {
		if (qipanTwoComputer[x][i] == 0) {
			houtou++;
		}
	}

	if (totalNumber >= 5) {
		totalNumber = 5;
	}

	return totalNumber * 10 + houtou;
}
