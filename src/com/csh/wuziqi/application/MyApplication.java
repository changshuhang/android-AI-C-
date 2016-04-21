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
		// crash�ռ�
		// CrashHandler.getInstance().init(getApplicationContext());
		// CrashReport.initCrashReport(this, appId, isDebug); // ��ʼ��SDK
		LitePalApplication.initialize(this);
		initConfig(this);
	}

	/**
	 * ��ʼ���ļ�����--Bmob
	 * 
	 * @param context
	 */
	private void initConfig(Context context) {
		BmobConfiguration config = new BmobConfiguration.Builder(context)
				.customExternalCacheDir("JKGJ").build();
		BmobPro.getInstance(context).initConfig(config);
		// ��ʼ�� Bmob SDK
		Bmob.initialize(context, SDK);
		// ��ʼ��AppVersion��,�Զ�����AppVersion��
		BmobUpdateAgent.initAppVersion(this);
		// ʹ�����ͷ���ʱ�ĳ�ʼ������
		BmobInstallation.getCurrentInstallation(this).save();
		// �������ͷ���
		BmobPush.startWork(this, SDK);
	}

}
