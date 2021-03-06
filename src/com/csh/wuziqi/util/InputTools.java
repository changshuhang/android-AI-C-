package com.csh.wuziqi.util;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

public class InputTools {

	public static void hideSoftInputMode(Context context, View windowToken) {
		InputMethodManager imm = ((InputMethodManager) context
				.getSystemService(Context.INPUT_METHOD_SERVICE));
		imm.hideSoftInputFromWindow(windowToken.getWindowToken(),
				InputMethodManager.HIDE_NOT_ALWAYS);
	}

	public static void showSoftInputMode(Context context, View windowToken) {
		InputMethodManager imm = ((InputMethodManager) context
				.getSystemService(Context.INPUT_METHOD_SERVICE));
		imm.showSoftInputFromInputMethod(windowToken.getWindowToken(),
				InputMethodManager.HIDE_NOT_ALWAYS);
	}

	// �����������
	public static void HideKeyboard(View v) {
		InputMethodManager imm = (InputMethodManager) v.getContext()
				.getSystemService(Context.INPUT_METHOD_SERVICE);
		if (imm.isActive()) {
			imm.hideSoftInputFromWindow(v.getWindowToken(),
					InputMethodManager.HIDE_NOT_ALWAYS);
		}
	}

	// ��ʾ�������
	public static void ShowKeyboard(View v) {
		InputMethodManager imm = (InputMethodManager) v.getContext()
				.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.showSoftInput(v, InputMethodManager.SHOW_FORCED);
	}

	// ǿ����ʾ���߹ر�ϵͳ����
	public static void KeyBoard(final EditText txtSearchKey, final String status) {
		Timer timer = new Timer();
		timer.schedule(new TimerTask() {
			@Override
			public void run() {
				InputMethodManager m = (InputMethodManager) txtSearchKey
						.getContext().getSystemService(
								Context.INPUT_METHOD_SERVICE);
				if (status.equals("open")) {
					m.showSoftInput(txtSearchKey,
							InputMethodManager.SHOW_FORCED);
				} else {
					m.hideSoftInputFromWindow(txtSearchKey.getWindowToken(), 0);
				}
			}
		}, 300);
	}

	// ͨ����ʱ��ǿ�������������
	public static void TimerHideKeyboard(final View v) {
		Timer timer = new Timer();
		timer.schedule(new TimerTask() {
			@Override
			public void run() {
				InputMethodManager imm = (InputMethodManager) v.getContext()
						.getSystemService(Context.INPUT_METHOD_SERVICE);
				if (imm.isActive()) {
					imm.hideSoftInputFromWindow(v.getApplicationWindowToken(),
							0);
				}
			}
		}, 10);
	}

	// ���뷨�Ƿ���ʾ��
	public static boolean KeyBoard(EditText edittext) {
		boolean bool = false;
		InputMethodManager imm = (InputMethodManager) edittext.getContext()
				.getSystemService(Context.INPUT_METHOD_SERVICE);
		if (imm.isActive()) {
			bool = true;
		}
		return bool;
	}
}
