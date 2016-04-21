package com.csh.wuziqi;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;

import com.csh.wuziqi.view.QiPanView;
import com.csh.wuziqi.view.QiPanView.OnSuccess;

public class MainActivity extends Activity implements OnClickListener,
		OnSuccess {

	private QiPanView qiPanView;

	private TextView textViewStart;
	private TextView textViewHuiQi;
	private TextView textViewRestart;

	private Handler handler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch (msg.what) {
			case 1:
				Dialog dialog = new AlertDialog.Builder(MainActivity.this)
						.setTitle("胜利提示")
						.setMessage((Integer)msg.obj == 2 ? "白方胜利" : "黑方胜利 ")
						.setPositiveButton("重新开始",
								new DialogInterface.OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog,
											int which) {
										// TODO Auto-generated method stub
										dialog.dismiss();
										// 重新开始
										qiPanView.restart();
									}
								})
						.setNegativeButton("取消",
								new DialogInterface.OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog,
											int which) {
										// TODO Auto-generated method stub
										dialog.dismiss();
									}
								}).create();
				dialog.show();
				break;

			default:
				break;
			}
		}

	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		super.setContentView(R.layout.activity_main);

		this.qiPanView = (QiPanView) findViewById(R.id.qiPanView1);
		this.textViewStart = (TextView) findViewById(R.id.textView2);
		this.textViewHuiQi = (TextView) findViewById(R.id.textView1);
		this.textViewRestart = (TextView) findViewById(R.id.textView3);

		this.textViewHuiQi.setOnClickListener(this);
		this.textViewStart.setOnClickListener(this);
		this.textViewRestart.setOnClickListener(this);
		this.qiPanView.setOnSuccess(this);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.textView1:
			// 悔棋
			this.qiPanView.retreatBack();
			break;
		case R.id.textView2:
			// 开始
			this.qiPanView.setRunningGame(true);
			// this.qiPanView.computerXia();
			break;
		case R.id.textView3:
			// 重新开始
			this.qiPanView.restart();
			break;

		default:
			break;
		}
	}

	@Override
	public void success(int type) {
		// TODO Auto-generated method stub
		Message message = new Message();
		message.what = 1;
		message.obj=type;
		handler.sendMessage(message);
	}

}
