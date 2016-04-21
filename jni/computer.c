#include <computer.h>

#include "dateself.c"

//个数
jint totalLineNumberComputer = 19;
//全部棋子
jint qipanTwoComputer[19][19];

//x,y代表对方刚刚下的棋子，type代表自己的阵营
jint computer_next(JNIEnv* env, jobject thiz, jintArray jintarray, jint x,
		jint y, jint type) {
	int length = totalLineNumberComputer * totalLineNumberComputer;
	jint qipanOne[length];
	//自己阵营的棋子的个数
	int selfQiZiNumber = 0;
	int i = 0;
	(*env)->GetIntArrayRegion(env, jintarray, 0, length, qipanOne);
	//变成二维数组
	for (i = 0; i < length; i++) {
		qipanTwoComputer[i / totalLineNumberComputer][i
				% totalLineNumberComputer] = qipanOne[i];
	}

	//1.线统计自己阵营的棋子的个数
	selfQiZiNumber = getTotalQiZiNumber(type);
	LOGI("init success----> %d", selfQiZiNumber);

	if (selfQiZiNumber <= 0) {
		//下第一个棋子时
		return getFirstZuoBiaoXYDuiFang(type);
	} else if (selfQiZiNumber == 1) {
		//下第一个棋子时
		LOGI("init type----> %d", type);
		return getSecondZuoBiaoXY(type);
	} else {
		//计算有利于自己的下棋方式
		return calculaterMaxSelf(type);
	}
}

//计算最有利于自己下的棋子
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

	//清空数据
	clear();

	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] == 0) {
				//当改点为NULL时才进行数据计算
				//1--先计算自己
				tempValue = getIsYouQiZi(i, j, type);
				if (tempValue == -1) {
					//不进行理论计算
				} else if (tempValue == 0) {
					//旁边没有自己的点,不进行计算
				} else {
					//进行理论计算
					dealXiQiZiSelf(type, i, j);
				}
				//2--计算对手
				tempValue = getIsYouQiZiDuiShou(i, j, duishouType);
				if (tempValue == -1) {
					//不进行理论计算
				} else if (tempValue == 0) {
					//旁边没有自己的点,不进行计算
				} else {
					//进行理论计算
					dealXiQiZiDuiShou(duishouType, i, j);
				}
			}
		}
	}

	//排序
	selectSortSTL();

	//最后的数据集合
	LOGI("last jihe----> %s", "zui hou de shu ju ji he !");
	printAll();

	//取得数据最大值
	return getMaxValue();

}

//假设自己下该棋子后对棋盘界面的影响
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

	//对结果进行排序
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			if (dealValue[j] > dealValue[i]) {
				sortTemp = dealValue[i];
				dealValue[i] = dealValue[j];
				dealValue[j] = sortTemp;
			}
		}
	}

	//对结果进行处理
	LOGI("deal jieg----> %d,%d,%d,%d,%d,%d", x, y, dealValue[0], dealValue[1],
			dealValue[2], dealValue[3]);
	jiedian = getNew();
	jiedian->weight = calculateWeigthSelf(dealValue);
	jiedian->x = x;
	jiedian->y = y;
	jiedian->number = 1;

	add(jiedian);
}

//假设对方下该棋子后对棋盘界面的影响
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

	//对结果进行排序
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			if (dealValue[j] > dealValue[i]) {
				sortTemp = dealValue[i];
				dealValue[i] = dealValue[j];
				dealValue[j] = sortTemp;
			}
		}
	}

	//对结果进行处理
	LOGI("deal jieg----> %d,%d,%d,%d,%d,%d", x, y, dealValue[0], dealValue[1],
			dealValue[2], dealValue[3]);
	jiedian = getNew();
	jiedian->weight = calculateWeigthDuiShou(dealValue);
	jiedian->x = x;
	jiedian->y = y;
	jiedian->number = 1;

	add(jiedian);
}

//计算该棋子的权重
int calculateWeigthDuiShou(int dealValue[]) {
	int weigth = 0;
	int temp = 0;
	if (getWeigthNumber(dealValue, 50) > 0 || getWeigthNumber(dealValue, 51) > 0
			|| getWeigthNumber(dealValue, 52) > 0) {
		//成52,51,50, 如果是机器方的话给予990分
		weigth = 990;
	} else if (getWeigthNumber(dealValue, 42) > 0
			|| getWeigthNumber(dealValue, 41) > 1) {
		//成42, 如果是机器方的话给予800分--低分
		//继续细分
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
		//成32>1, 如果是机器方的话给予960分--底分
		//继续细分
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
		//成41==1, 如果是机器方的话给予550分
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
		//成32==1, 如果是机器方的话给予450分
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
		//成22>1, 如果是机器方的话给予800分
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

//计算该棋子的权重
int calculateWeigthSelf(int dealValue[]) {
	int weigth = 0;
	int temp = 0;
	if (getWeigthNumber(dealValue, 50) > 0 || getWeigthNumber(dealValue, 51) > 0
			|| getWeigthNumber(dealValue, 52) > 0) {
		//成52,51,50, 如果是机器方的话给予1000分
		weigth = 1000;
	} else if (getWeigthNumber(dealValue, 42) > 0
			|| getWeigthNumber(dealValue, 41) > 1) {
		//成42, 如果是机器方的话给予800分--底分
		//继续细分
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
		//成32>1, 如果是机器方的话给予960分--底分
		//继续细分
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
		//成41==1, 如果是机器方的话给予940分
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
		//成32==1, 如果是机器方的话给予900分
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
		//成22>1, 如果是机器方的话给予800分
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

//取得个数
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

//判断一个null的棋子对手
int getIsYouQiZiDuiShou(int x, int y, int type) {
	if (qipanTwoComputer[x][y] != 0) {
		//该位置已经有棋子了
		return -1;
	} else {
		//左上
		if (x - 1 >= 0 && y - 1 >= 0
				&& qipanTwoComputer[x - 1][y - 1] == type) {
			return 1;
		}
		//上
		if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == type) {
			return 1;
		}
		//右上
		if (x + 1 < totalLineNumberComputer && y - 1 >= 0
				&& qipanTwoComputer[x + 1][y - 1] == type) {
			return 1;
		}
		//左
		if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == type) {
			return 1;
		}
		//右
		if (x + 1 < totalLineNumberComputer && y >= 0
				&& qipanTwoComputer[x + 1][y] == type) {
			return 1;
		}
		//左下
		if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x - 1][y + 1] == type) {
			return 1;
		}
		//下
		if (x >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x][y + 1] == type) {
			return 1;
		}
		//右下
		if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x + 1][y + 1] == type) {
			return 1;
		}

		//没有指定的数据
		return 0;
	}
}

//判断一个null的棋子旁边是否有指定类型的棋子
int getIsYouQiZi(int x, int y, int type) {
	if (qipanTwoComputer[x][y] != 0) {
		//该位置已经有棋子了
		return -1;
	} else {
		//左上
		if (x - 1 >= 0 && y - 1 >= 0
				&& qipanTwoComputer[x - 1][y - 1] == type) {
			return 1;
		}
		//上
		if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == type) {
			return 1;
		}
		//右上
		if (x + 1 < totalLineNumberComputer && y - 1 >= 0
				&& qipanTwoComputer[x + 1][y - 1] == type) {
			return 1;
		}
		//左
		if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == type) {
			return 1;
		}
		//右
		if (x + 1 < totalLineNumberComputer && y >= 0
				&& qipanTwoComputer[x + 1][y] == type) {
			return 1;
		}
		//左下
		if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x - 1][y + 1] == type) {
			return 1;
		}
		//下
		if (x >= 0 && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x][y + 1] == type) {
			return 1;
		}
		//右下
		if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
				&& qipanTwoComputer[x + 1][y + 1] == type) {
			return 1;
		}

		//没有指定的数据
		return 0;
	}
}

//取得第二个下棋子的坐标
jint getSecondZuoBiaoXY(int type) {
	int i = 0, j = 0;
	int value = -1;
	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] == type) {
				//找到第一个下的棋子，中断循环
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

//取得第一个下棋子的坐标,自己先下
jint getFirstZuoBiaoXYDuiFang(int type) {
	int i = 0, j = 0;
	int value = -1;

	//找到已经下的唯一的棋子
	for (i = 0; i < totalLineNumberComputer; i++) {
		for (j = 0; j < totalLineNumberComputer; j++) {
			if (qipanTwoComputer[i][j] != 0) {
				//找到第一个下的棋子，中断循环
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

//取得第一个下棋子的坐标,自己先下
jint getFirstZuoBiaoXYSelf() {
	jint first[] = { 8 * 100 + 8, 9 * 100 + 8, 10 * 100 + 8, 8 * 100 + 9, 9
			* 100 + 9, 10 * 100 + 9, 8 * 100 + 10, 9 * 100 + 10, 10 * 100 + 10 };
	int temp1 = sizeof(first);
	int temp2 = sizeof(jint);
	int temp3 = temp1 / temp2;
	int temp4 = getRand0Max(temp3);
	return first[temp4];
}

//统计棋子的个数
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

//取得一个0-max的随机数字
int getRand0Max(int max) {
	return (int) (rand() % max);
}

//判断有几个方向可以下棋子
int calculateFangXiang(int x, int y) {
	int qiziXY[8];
	int totalFangXiang = 0;

	//左上
	if (x - 1 >= 0 && y - 1 >= 0 && qipanTwoComputer[x - 1][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y - 1);
		totalFangXiang++;
	}
	//上
	if (x >= 0 && y - 1 >= 0 && qipanTwoComputer[x][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x) + (y - 1);
		totalFangXiang++;
	}
	//右上
	if (x + 1 < totalLineNumberComputer && y - 1 >= 0
			&& qipanTwoComputer[x + 1][y - 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y - 1);
		totalFangXiang++;
	}
	//左
	if (x - 1 >= 0 && y >= 0 && qipanTwoComputer[x - 1][y] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y);
		totalFangXiang++;
	}
	//右
	if (x + 1 < totalLineNumberComputer && y >= 0
			&& qipanTwoComputer[x + 1][y] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y);
		totalFangXiang++;
	}
	//左下
	if (x - 1 >= 0 && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x - 1][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x - 1) + (y + 1);
		totalFangXiang++;
	}
	//下
	if (x >= 0 && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x) + (y + 1);
		totalFangXiang++;
	}
	//右下
	if (x + 1 < totalLineNumberComputer && y + 1 < totalLineNumberComputer
			&& qipanTwoComputer[x + 1][y + 1] == 0) {
		qiziXY[totalFangXiang] = 100 * (x + 1) + (y + 1);
		totalFangXiang++;
	}

	return qiziXY[getRand0Max(totalFangXiang)];
}

//取得leftbottom-righttop方向的数据
int getLeftBottomRightUpNumber(int type, int x, int y) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	int houtou = 0;
	//向上
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

	//向下
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

//取得leftup-rightbottom方向的数据
int getLeftUpRightBottomNumber(int type, int x, int y) {
	int i = 0;
	int j = 0;
	int totalNumber = 1;
	int houtou = 0;
	//向上
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

	//向下
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

//取得left_right方向的数据
int getLeftRightNumber(int type, int x, int y) {
	int i = 0;
	int totalNumber = 1;
	int houtou = 0;
	//向上
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

	//向下
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

//取得top_bottom方向的数据
int getTopBottmNumber(int type, int x, int y) {
	int i = 0;
	int totalNumber = 1;
	int houtou = 0;
	//向上
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

	//向下
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
