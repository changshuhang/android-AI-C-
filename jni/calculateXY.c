#include <calculateXY.h>

jint calculateXY(JNIEnv* env, jobject thiz, jint startX, jint startY,
		jint jiange, jint xp, jint yp, jint number) {

	int width = jiange * number;
	int height = jiange * number;
	int x = 0;
	int y = 0;
	int i = 0;
	int tempValue = 0;
	//�ȶ�y��������ж�
	if (yp < startY - jiange / 2 || yp > startY + height + jiange / 2) {
		//y���򳬳��˷�Χ
		return -1;
	} else {
		//x
		if (xp < startX - jiange / 2) {
			x = 0;
		} else if (xp > startX + width + jiange / 2) {
			x = number;
		} else {
			for (i = 0; i <= number; i++) {
				tempValue = startX + i * jiange;
				if (xp >= tempValue - jiange / 2
						&& xp <= tempValue + jiange / 2) {
					x = i;
					break;
				}
			}
		}
		//y
		if (yp < startY - jiange / 2) {
			y = 0;
		} else if (yp > startY + width + jiange / 2) {
			y = number;
		} else {
			for (i = 0; i <= number; i++) {
				tempValue = startY + i * jiange;
				if (yp >= tempValue - jiange / 2
						&& yp <= tempValue + jiange / 2) {
					y = i;
					break;
				}
			}
		}

		return x * 100 + y;
	}
}
