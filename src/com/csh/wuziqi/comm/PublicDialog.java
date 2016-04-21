package com.csh.wuziqi.comm;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.TextView;

import com.csh.wuziqi.R;

public class PublicDialog extends Dialog
		implements android.view.View.OnClickListener {

	private int type = -1;
	private String message = "";

	private TextView textView1;

	public PublicDialog(Context context, boolean cancelable,
			OnCancelListener cancelListener) {
		super(context, cancelable, cancelListener);
	}

	public PublicDialog(Context context, int theme) {
		super(context, theme);
	}

	public PublicDialog(Context context) {
		super(context);
	}

	public PublicDialog(Context context, int type, String message) {
		this(context,R.style.self_dialog);
		this.type = type;
		this.message = message;
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setCanceledOnTouchOutside(false);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		super.setContentView(R.layout.public_no_button);
		this.textView1 = (TextView) findViewById(R.id.content_dialog);
		this.textView1.setText(message);
	}

	public interface ICom {
		public void com();
	}

	public interface ICea {
		public void cea();
	}

	private ICom iCom;
	private ICea iCea;

	public void setICom(ICom iCom) {
		this.iCom = iCom;
	}

	public void setICea(ICea iCea) {
		this.iCea = iCea;
	}

	public void dismissSelf() {
		if (isShowing()) {
			dismiss();
		}
		if (this.iCea != null) {
			this.iCea.cea();
		}
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.textView2:
			dismiss();
			if (this.iCom != null) {
				this.iCom.com();
			}
			break;
		case R.id.textView3:
			dismiss();
			if (this.iCea != null) {
				this.iCea.cea();
			}
			break;
		}
	}
}
