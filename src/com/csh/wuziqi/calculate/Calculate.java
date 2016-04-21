package com.csh.wuziqi.calculate;

import com.csh.wuziqi.view.QiPanView;
import com.csh.wuziqi.view.QiZi;

public class Calculate {

	private QiPanView qiPanView;

	public Calculate(QiPanView qiPanView) {
		this.qiPanView = qiPanView;
	}

	public int getComputerXiaQi(QiZi[][] qiZis, int xg, int yg, int type) {
		int[] qizipan = new int[19 * 19];
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (qiZis[i][j] != null) {
					qizipan[i * 19 + j] = qiZis[i][j].getZhenYing();
				} else {
					qizipan[i * 19 + j] = 0;
				}
			}
		}

		return computerXiaQi(qizipan, xg, yg, type);
	}

	public int getCalculateXY(int startX, int startY, int jiange, int xp,
			int yp, int number) {
		return calculateXY(startX, startY, jiange, xp, yp, number);
	}

	public int[] getCheckSuccess(QiZi[][] qiZis, int x, int y) {
		int[] qizipan = new int[19 * 19];
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (qiZis[i][j] != null) {
					qizipan[i * 19 + j] = qiZis[i][j].getZhenYing();
				} else {
					qizipan[i * 19 + j] = 0;
				}
			}
		}

		return checkSuccess(qizipan, x, y, qiZis[x][y].getZhenYing());
	}

	public native int calculateXY(int startX, int startY, int jiange, int xp,
			int yp, int number);

	public native int computerXiaQi(int[] jintarray, int xg, int yg, int type);

	// 判断是否胜利
	public native int[] checkSuccess(int[] jintarray, int x, int y, int type);

	// 取消提示对话框
	public void dismissTiShi() {
		this.qiPanView.dismissTiShi();
	}

	static {
		System.loadLibrary("calculate");
	}

}
