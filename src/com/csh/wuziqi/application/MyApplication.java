package com.csh.wuziqi.application;

import org.litepal.LitePalApplication;

import android.content.Context;
import cn.bmob.push.BmobPush;
import cn.bmob.v3.Bmob;
import cn.bmob.v3.BmobInstallation;
import cn.bmob.v3.update.BmobUpdateAgent;

import com.bmob.BmobConfiguration;
import com.bmob.BmobPro;

public class MyApplication extends LitePalApplication {

	private String SDK = "2d3c754d7f9810a9fbd60f997c68d5f0";

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		// crash收集
		// CrashHandler.getInstance().init(getApplicationContext());
		// CrashReport.initCrashReport(this, appId, isDebug); // 初始化SDK
		LitePalApplication.initialize(this);
		initConfig(this);
	}

	/**
	 * 初始化文件配置--Bmob
	 * 
	 * @param context
	 */
	private void initConfig(Context context) {
		BmobConfiguration config = new BmobConfiguration.Builder(context)
				.customExternalCacheDir("JKGJ").build();
		BmobPro.getInstance(context).initConfig(config);
		// 初始化 Bmob SDK
		Bmob.initialize(context, SDK);
		// 初始化AppVersion表,自动创建AppVersion表
		BmobUpdateAgent.initAppVersion(this);
		// 使用推送服务时的初始化操作
		BmobInstallation.getCurrentInstallation(this).save();
		// 启动推送服务
		BmobPush.startWork(this, SDK);
	}

}
