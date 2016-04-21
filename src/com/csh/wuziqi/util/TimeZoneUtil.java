package com.csh.wuziqi.util;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

/**
 * ��ͬʱ����Ӧ��ʱ�䴦������
 * 
 * @author csh
 * 
 */
public class TimeZoneUtil {
	/**
	 * �ж��û����豸ʱ���Ƿ�Ϊ���������й��� 2014��7��31��
	 * 
	 * @return
	 */
	public static boolean isInEasternEightZones() {
		boolean defaultVaule = true;
		if (TimeZone.getDefault() == TimeZone.getTimeZone("GMT+08"))
			defaultVaule = true;
		else
			defaultVaule = false;
		return defaultVaule;
	}

	/**
	 * ���ݲ�ͬʱ����ת��ʱ�� 2014��7��31��
	 * 
	 * @param time
	 * @return
	 */
	public static Date transformTime(Date date, TimeZone oldZone,
			TimeZone newZone) {
		Date finalDate = null;
		if (date != null) {
			int timeOffset = oldZone.getOffset(date.getTime())
					- newZone.getOffset(date.getTime());
			finalDate = new Date(date.getTime() - timeOffset);
		}
		return finalDate;

	}

	public static String getCurrentTime(String format) {
		Date date = new Date();
		SimpleDateFormat sdf = new SimpleDateFormat(format, Locale.getDefault());
		String currentTime = sdf.format(date);
		return currentTime;
	}

	public static String getCurrentTime() {
		return getCurrentTime("yyyy-MM-dd  HH:mm:ss");
	}

	public static String timeSatck2Date(String time, String format) {
		SimpleDateFormat formats = new SimpleDateFormat(format);
		long t = Long.valueOf(time);
		return formats.format(new Date(t * 1000));
	}
}
