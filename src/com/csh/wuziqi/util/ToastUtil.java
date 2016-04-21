package com.csh.wuziqi.util;

import android.content.Context;
import android.widget.Toast;

/**
 * 控制Toast的显示时间
 * 
 * 
 */
public class ToastUtil {
	private Context mContext;
	private Toast mToast;
	private static ToastUtil instance;

	private ToastUtil(Context mContext) {
		super();
		this.mContext = mContext;
		if(mContext!=null){
			this.mToast = Toast.makeText(mContext, "", Toast.LENGTH_SHORT);
		}
		
	}

	public static ToastUtil getInstance(Context context) {
		if (instance == null) {
			if(context!=null){
				instance = new ToastUtil(context);
			}
			
		}
		return instance;
	}

	public void showToast(String text) {
		if (mToast == null) {
			mToast = Toast.makeText(mContext, text, Toast.LENGTH_SHORT);
		} else {
			mToast.setText(text);
			mToast.setDuration(Toast.LENGTH_SHORT);
		}
		mToast.show();
	}

	public void cancelToast() {
		if (mToast != null) {
			mToast.cancel();
		}
	}
}
