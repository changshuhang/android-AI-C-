package com.csh.wuziqi.view;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import com.csh.wuziqi.calculate.Calculate;
import com.csh.wuziqi.comm.PublicDialog;
import com.csh.wuziqi.util.ToastUtil;

public class QiPanView extends View {

	// �ܵĿ�ȣ��߶�
	private int totalWidth = 0, totalHeight = 0;
	// ���£����ҵĸ߶�
	private int right = 0, left = 0, top = 0, bottom = 0;
	// �����ߵļ��
	private int jianGe = 0;
	// ���ӵİ뾶
	private int qiZiRadius = 0;
	// �ߵ���ɫ
	private int lineColor = Color.BLACK;
	// ʵ����������ɫ
	private int shiXinColor = Color.BLACK;
	// �ڷ����ӵ���ɫ
	private int heiFangColor = Color.BLACK;
	// �׷����ӵ���ɫ
	private int baiFangColor = Color.WHITE;
	// ��Ȧ����ɫ
	private int waiQuanColor = Color.GREEN;
	// ʤ������ɫ
	private int successColor = Color.RED;
	// �����ߵĸ���
	private int numberLine = 19;

	// ����
	private QiZi[][] qiZis = new QiZi[19][19];

	private Paint paintLine;
	private Paint paintShiXin;

	// �����ӷ�
	private int xiaQiZiFang = 1;

	// ����
	Calculate calculate;

	// �Ƿ����ڽ�����Ϸ
	private boolean isRunningGame = false;

	// ����������ʱ����ʾ�Ի���
	private PublicDialog publicDialog;

	// �ϴζԷ��µ�����
	private int preDuiFangX = -1, preDuiFangY = -1;

	// �Ƿ��Ѿ�������Ϸ
	private boolean isOver = false;

	// ���岽��
	private List<RetreatBean> listBZ = new ArrayList<>();

	private Handler handler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			switch (msg.what) {
			case 1:
				invalidate();
				break;
			case 2:
				showTiShi();
				break;
			case 3:
				dismissTiShi();
				break;

			default:
				break;
			}
		}

	};

	public QiPanView(Context context, AttributeSet attrs, int defStyleAttr,
			int defStyleRes) {
		super(context, attrs, defStyleAttr, defStyleRes);
		// TODO Auto-generated constructor stub
		init();
	}

	public QiPanView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		// TODO Auto-generated constructor stub
		init();
	}

	public QiPanView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
		init();
	}

	public QiPanView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		init();
	}

	/*
	 * ��ʼ������
	 */
	private void init() {
		setBackgroundColor(Color.TRANSPARENT);

		this.paintLine = new Paint();
		this.paintLine.setColor(lineColor);
		this.paintLine.setAntiAlias(true);
		this.paintLine.setStrokeWidth(2f);
		this.paintLine.setStyle(Style.FILL);

		this.paintShiXin = new Paint();
		this.paintShiXin.setColor(shiXinColor);
		this.paintShiXin.setAntiAlias(true);
		this.paintShiXin.setStrokeWidth(2f);
		this.paintShiXin.setStyle(Style.FILL);

		calculate = new Calculate(this);
	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		// TODO Auto-generated method stub
		super.onMeasure(widthMeasureSpec, heightMeasureSpec);
		totalWidth = MeasureSpec.getSize(widthMeasureSpec);
		totalHeight = MeasureSpec.getSize(heightMeasureSpec);
		Log.e("test", "totalWidth=" + totalWidth + ";totalHeight="
				+ totalHeight);

		this.jianGe = (totalWidth) / (numberLine + 1);
		this.qiZiRadius = this.jianGe / 3;
		this.left = this.jianGe;
		this.right = this.left;
		this.top = (this.totalHeight - this.left * (numberLine - 1)) / 2;
		this.bottom = this.top;
	}

	@Override
	protected void onDraw(Canvas canvas) {
		// TODO Auto-generated method stub
		super.onDraw(canvas);
		// ���ư�ɫ����Ļ

		// ��������
		// ��
		for (int i = 0; i < numberLine; i++) {
			canvas.drawLine(this.left, this.top + i * this.jianGe,
					this.totalWidth - this.right, this.top + i * this.jianGe,
					paintLine);
		}
		// ��
		for (int i = 0; i < numberLine; i++) {
			canvas.drawLine(this.left + i * this.jianGe, this.top, this.left
					+ i * this.jianGe, this.totalHeight - this.bottom,
					paintLine);
		}
		// ����9����λ��
		canvas.drawCircle(this.left + 3 * this.jianGe, this.top + 3
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 3 * this.jianGe, this.top + 9
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 3 * this.jianGe, this.top + 15
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 9 * this.jianGe, this.top + 3
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 9 * this.jianGe, this.top + 9
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 9 * this.jianGe, this.top + 15
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 15 * this.jianGe, this.top + 3
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 15 * this.jianGe, this.top + 9
				* this.jianGe, this.jianGe / 7, paintShiXin);
		canvas.drawCircle(this.left + 15 * this.jianGe, this.top + 15
				* this.jianGe, this.jianGe / 7, paintShiXin);

		for (int i = 0; i < numberLine; i++) {
			for (int j = 0; j < numberLine; j++) {
				if (qiZis[i][j] != null) {
					qiZis[i][j].drawSelf(canvas);
				}
			}
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		// TODO Auto-generated method stub
		if (!isRunningGame) {
			// û�����ڽ�����Ϸ��ֱ�ӷ���
			return false;
		}
		if (isOver) {
			ToastUtil.getInstance(getContext()).showToast("��Ϸ�Ѿ�����!");
			return false;
		}
		// ����ǵ��Է���������
		if (xiaQiZiFang == 2) {
			ToastUtil.getInstance(getContext()).showToast("������������!");
			return false;
		}

		int x = (int) event.getX();
		int y = (int) event.getY();
		switch (event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			int value = calculate.getCalculateXY(this.left, this.top,
					this.jianGe, x, y, numberLine - 1);
			if (value != -1) {
				int xi = value / 100;
				int yi = value % 100;
				if (qiZis[xi][yi] != null) {
					// �Ѿ�������
					ToastUtil.getInstance(getContext()).showToast(
							"�Ѿ��������ˣ�����������!");
				} else {
					// û�����ӣ�����������
					xiaQiZi(xi, yi);

					// ����Ƿ�ʤ��
					int[] successType = calculate
							.getCheckSuccess(qiZis, xi, yi);
					if (successType[0] == 1) {
						if (onSuccess != null) {
							onSuccess.success(xiaQiZiFang);
							isOver = true;
							qiZis[successType[1]][successType[2]]
									.setSuccess(true);
						}

						// ˢ�½���
						invalidate();
					} else {
						// ˢ�½���
						invalidate();

						// ��ʼ��������
						computerXia();
					}

				}
			}
			break;
		case MotionEvent.ACTION_UP:

			break;
		case MotionEvent.ACTION_MOVE:

			break;

		default:
			break;
		}
		return false;
	}

	private void xiaQiZi(int xi, int yi) {
		QiZi qiZi;
		if (xiaQiZiFang == 1) {
			qiZi = new QiZi(xiaQiZiFang, left + xi * jianGe, top + yi * jianGe,
					baiFangColor, waiQuanColor, successColor, qiZiRadius, true,
					false);

			xiaQiZiFang = 2;
		} else {
			qiZi = new QiZi(xiaQiZiFang, left + xi * jianGe, top + yi * jianGe,
					heiFangColor, waiQuanColor, successColor, qiZiRadius, true,
					false);

			xiaQiZiFang = 1;
		}

		qiZis[xi][yi] = qiZi;

		RetreatBean retreatBean = new RetreatBean(listBZ.size(), xi, yi,
				xiaQiZiFang == 1 ? 2 : 1);
		listBZ.add(retreatBean);

		// ��������µ�����
		if (listBZ.size() > 1) {
			RetreatBean bean = listBZ.get(listBZ.size() - 2);
			qiZis[bean.x][bean.y].setGangXia(false);
		}

		// ˢ�½���
		Message message = new Message();
		message.what = 1;
		handler.sendMessage(message);
	}

	// ���¿�ʼ
	public void restart() {
		for (int i = 0; i < numberLine; i++) {
			for (int j = 0; j < numberLine; j++) {
				qiZis[i][j] = null;
			}
		}

		listBZ.clear();
		xiaQiZiFang = 1;
		isOver = false;

		// ˢ�½���
		Message message = new Message();
		message.what = 1;
		handler.sendMessage(message);
	}

	// ����
	public void retreatBack() {

		if (listBZ.size() > 0) {
			int len = listBZ.size();

			if (isOver) {
				isOver = false;
				// ���ڿ�ʼ���巽
				if (xiaQiZiFang == 1) {
					// ��
					RetreatBean bean = listBZ.get(len - 1);
					qiZis[bean.x][bean.y] = null;
					listBZ.remove(len - 1);

					bean = listBZ.get(this.listBZ.size() - 1);
					qiZis[bean.x][bean.y] = null;
					listBZ.remove(this.listBZ.size() - 1);
				} else {
					// ����
					RetreatBean bean = listBZ.get(len - 1);
					qiZis[bean.x][bean.y] = null;
					listBZ.remove(len - 1);
				}
				// ��������µ�����
				if (listBZ.size() > 0) {
					RetreatBean b = listBZ.get(listBZ.size() - 1);
					qiZis[b.x][b.y].setGangXia(true);
				}

				xiaQiZiFang = 1;
			} else {
				for (int i = len - 1; i >= 0; i--) {
					RetreatBean bean = listBZ.get(i);
					if (bean.type == 1) {
						qiZis[bean.x][bean.y] = null;

						RetreatBean bean1 = listBZ.get(i + 1);
						qiZis[bean1.x][bean1.y] = null;

						listBZ.remove(i + 1);
						listBZ.remove(i);

						// ��������µ�����
						if (listBZ.size() > 0) {
							RetreatBean b = listBZ.get(listBZ.size() - 1);
							qiZis[b.x][b.y].setGangXia(true);
						}

						break;
					}
				}
			}

			// ˢ�½���
			Message message = new Message();
			message.what = 1;
			handler.sendMessage(message);
		} else {
			ToastUtil.getInstance(getContext()).showToast("û�п��Ժ��˵�������!");
		}
	}

	// ��������
	public void computerXia() {
		new Thread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				// ��ʾ��ʾ
				Message message = new Message();
				message.what = 2;
				handler.sendMessage(message);
				// ���Լ���
				int value = calculate.getComputerXiaQi(qiZis, preDuiFangX,
						preDuiFangY, xiaQiZiFang);
				Log.e("test", "value=" + value);
				xiaQiZi(value / 100, value % 100);

				// ����Ƿ�ʤ��
				int[] successType = calculate.getCheckSuccess(qiZis,
						value / 100, value % 100);
				if (successType[0] == 1) {
					if (onSuccess != null) {
						onSuccess.success(xiaQiZiFang);
						isOver = true;
						qiZis[successType[1]][successType[2]].setSuccess(true);
					}
				}

				// ȡ����ʾ
				Message message1 = new Message();
				message1.what = 3;
				handler.sendMessage(message1);
			}
		}).start();
	}

	// �ӿ�����
	public interface OnSuccess {
		public void success(int type);
	}

	private OnSuccess onSuccess;

	public void setOnSuccess(OnSuccess onSuccess) {
		this.onSuccess = onSuccess;
	}

	// ----------------------
	public void showTiShi() {
		if (publicDialog == null) {
			publicDialog = new PublicDialog(getContext(), 0, "�������ڼ��������ӣ����Ժ�...");
		}
		publicDialog.show();
	}

	public void dismissTiShi() {
		if (publicDialog != null) {
			publicDialog.dismissSelf();
		}
	}

	public boolean isRunningGame() {
		return isRunningGame;
	}

	public void setRunningGame(boolean isRunningGame) {
		this.isRunningGame = isRunningGame;
		isOver = false;
	}
}
