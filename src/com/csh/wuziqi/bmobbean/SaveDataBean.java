package com.csh.wuziqi.bmobbean;

import java.io.Serializable;

import cn.bmob.v3.BmobObject;

public class SaveDataBean extends BmobObject implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = -4725891597894352876L;

	//  ±º‰
	private String date;
	// ≤Ω÷Ë
	private String message;

	public String getDate() {
		return date;
	}

	public void setDate(String date) {
		this.date = date;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

}
