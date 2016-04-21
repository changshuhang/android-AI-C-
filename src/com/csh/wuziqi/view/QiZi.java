package com.csh.wuziqi.view;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Style;

public class QiZi {

	// �����
	private int xPoint;
	private int yPoint;
	// ��ɫ
	private int colorShiTi;
	private int colorWaiQuan;
	private int colorSuccess;
	// �뾶��С
	private int radius;
	// �Ƿ��Ǹո��µ�����
	private boolean isGangXia;
	// �Ƿ�ʤ��
	private boolean isSuccess;
	//��Ӫ 1--�׷�  2--�ڷ�
	private int zhenYing;

	private Paint paint;

	public QiZi(int zhenYing,int xPoint, int yPoint, int colorShiTi, int colorWaiQuan,
			int colorSuccess, int radius, boolean isGangXia, boolean isSuccess) {
		this.xPoint = xPoint;
		this.yPoint = yPoint;
		this.colorShiTi = colorShiTi;
		this.colorWaiQuan = colorWaiQuan;
		this.colorSuccess = colorSuccess;
		this.radius = radius;
		this.isGangXia = isGangXia;
		this.isSuccess = isSuccess;
		this.zhenYing=zhenYing;

		paint = new Paint();
		paint.setAntiAlias(true);
		paint.setStyle(Style.FILL);
		paint.setStrokeWidth(2f);
	}

	public int getZhenYing() {
		return zhenYing;
	}

	public void setZhenYing(int zhenYing) {
		this.zhenYing = zhenYing;
	}

	public int getxPoint() {
		return xPoint;
	}

	public void setxPoint(int xPoint) {
		this.xPoint = xPoint;
	}

	public int getyPoint() {
		return yPoint;
	}

	public void setyPoint(int yPoint) {
		this.yPoint = yPoint;
	}

	public int getColorShiTi() {
		return colorShiTi;
	}

	public void setColorShiTi(int colorShiTi) {
		this.colorShiTi = colorShiTi;
	}

	public int getColorWaiQuan() {
		return colorWaiQuan;
	}

	public void setColorWaiQuan(int colorWaiQuan) {
		this.colorWaiQuan = colorWaiQuan;
	}

	public int getColorSuccess() {
		return colorSuccess;
	}

	public void setColorSuccess(int colorSuccess) {
		this.colorSuccess = colorSuccess;
	}

	public int getRadius() {
		return radius;
	}

	public void setRadius(int radius) {
		this.radius = radius;
	}

	public boolean isGangXia() {
		return isGangXia;
	}

	public void setGangXia(boolean isGangXia) {
		this.isGangXia = isGangXia;
	}

	public boolean isSuccess() {
		return isSuccess;
	}

	public void setSuccess(boolean isSuccess) {
		this.isSuccess = isSuccess;
	}

	public void drawSelf(Canvas canvas) {
		paint.setStyle(Style.FILL);
		paint.setColor(colorShiTi);
		canvas.drawCircle(xPoint, yPoint, radius, paint);

		paint.setStyle(Style.STROKE);
		if (isSuccess) {
			paint.setColor(colorSuccess);
			canvas.drawCircle(xPoint, yPoint, radius+3, paint);
		} else {
			if (isGangXia) {
				paint.setColor(colorWaiQuan);
				canvas.drawCircle(xPoint, yPoint, radius+3, paint);
			}
		}
	}

}
