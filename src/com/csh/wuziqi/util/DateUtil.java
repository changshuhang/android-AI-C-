package com.csh.wuziqi.util;

import java.text.ParseException;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.Random;

public class DateUtil {

	// ʱ���ʽ
	public static final String DATEFESHI = "yyyy-MM-dd HH:mm";

	// Ҫ��ʾ��ʱ���ʽ
	public static final String SHOW_DATEFESHI1 = "yy/MM/dd";

	/*
	 * ȡ�õ�ǰ��longֵ
	 */
	public static long getDateLong(String date) {
		long l = 0l;
		try {
			l = new SimpleDateFormat(DATEFESHI).parse(date).getTime();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return l;
	}

	/*
	 * ȡ�õ�ǰ��Stringֵ
	 */
	public static String getDateString(String type, Long date) {

		return new SimpleDateFormat(type).format(new Date(date));
	}

	/*
	 * ȡ��Ҫ��ʾ��ʱ���ʽ
	 */
	public static String getDateShow(String geshi, String date) {
		Date d = null;
		try {
			d = new SimpleDateFormat(DATEFESHI).parse(date);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new SimpleDateFormat(geshi).format(d);
	}

	/*
	 * ȡ�ü�����ʱ�䣬��ʽgeshi
	 */
	public static String getDateNumberShow(String geshi, long date, int number) {
		Date d = new Date(date);
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH),
				cal.get(Calendar.DAY_OF_MONTH) + number);
		d = cal.getTime();

		return new SimpleDateFormat(geshi).format(d);
	}

	public static long getChaValue(int h, int m) {
		Date d = new Date();
		Calendar calStart = Calendar.getInstance();
		calStart.setTime(d);
		calStart.set(Calendar.HOUR_OF_DAY, h);
		calStart.set(Calendar.MINUTE, m);
		Calendar calEnd = Calendar.getInstance();
		calEnd.setTime(d);
		calEnd.set(Calendar.DAY_OF_MONTH, calEnd.get(Calendar.DAY_OF_MONTH) + 1);
		return calEnd.getTimeInMillis() - calStart.getTimeInMillis();
	}

	public static final int daysBetween(long early, long late) {

		java.util.Calendar calst = java.util.Calendar.getInstance();
		java.util.Calendar caled = java.util.Calendar.getInstance();
		calst.setTime(new Date(early));
		caled.setTime(new Date(late));
		// ����ʱ��Ϊ0ʱ
		calst.set(java.util.Calendar.HOUR_OF_DAY, 0);
		calst.set(java.util.Calendar.MINUTE, 0);
		calst.set(java.util.Calendar.SECOND, 0);
		caled.set(java.util.Calendar.HOUR_OF_DAY, 0);
		caled.set(java.util.Calendar.MINUTE, 0);
		caled.set(java.util.Calendar.SECOND, 0);
		// �õ�����������������
		int days = ((int) (caled.getTime().getTime() / 1000) - (int) (calst
				.getTime().getTime() / 1000)) / 3600 / 24;
		return days;
	}

	public static long getXNextDate(long data, int x) {
		Date d = new Date(data);
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH),
				cal.get(Calendar.DAY_OF_MONTH) + x);
		d = cal.getTime();

		return d.getTime();
	}

	public static long getSevenNextDate(long data) {
		Date d = new Date(data);
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH),
				cal.get(Calendar.DAY_OF_MONTH) + 7);
		d = cal.getTime();

		return d.getTime();
	}

	public static long getSevenPreDate(long data) {
		Date d = new Date(data);
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH),
				cal.get(Calendar.DAY_OF_MONTH) - 7);
		d = cal.getTime();

		return d.getTime();
	}

	/*
	 * ȡ����һ���ʱ�䣬��ʽΪgeshi
	 */
	public static String getDateNextShow(String geshi, String date) {
		Date d = null;
		SimpleDateFormat formatter = new SimpleDateFormat(DATEFESHI);
		ParsePosition pos = new ParsePosition(0);
		d = formatter.parse(date, pos);
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		cal.set(cal.get(Calendar.YEAR), cal.get(Calendar.MONTH),
				cal.get(Calendar.DAY_OF_MONTH) + 1);
		d = cal.getTime();

		return new SimpleDateFormat(geshi).format(d);
	}

	/*
	 * ȡ�õ�ǰʱ���Сʱ����Ŀ
	 */
	@SuppressWarnings("deprecation")
	public static double getDateHH(String date) {
		Date d = null;
		try {
			d = new SimpleDateFormat(DATEFESHI).parse(date);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		double t = d.getHours();
		t += d.getMinutes() * 1.0 / 60;

		return t;
	}

	/**
	 * hh:mm
	 * 
	 * @return ����ʱ������ HH:mm
	 */
	public static String getDateHHmm(String date) {
		Date d = null;
		SimpleDateFormat formatter = new SimpleDateFormat(DATEFESHI);
		ParsePosition pos = new ParsePosition(0);
		d = formatter.parse(date, pos);
		return new SimpleDateFormat("HH:mm").format(d);
	}

	/**
	 * ��ȡ����ʱ��
	 * 
	 * @return ����ʱ������ yyyy-MM-dd HH:mm:ss
	 */
	public static Date getNowDate() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(currentTime);
		ParsePosition pos = new ParsePosition(8);
		Date currentTime_2 = formatter.parse(dateString, pos);
		return currentTime_2;
	}

	/**
	 * ��ȡ����ʱ��
	 * 
	 * @return���ض�ʱ���ʽ yyyy-MM-dd
	 */
	public static Date getNowDateShort() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
		String dateString = formatter.format(currentTime);
		ParsePosition pos = new ParsePosition(8);
		Date currentTime_2 = formatter.parse(dateString, pos);
		return currentTime_2;
	}

	/**
	 * ��ȡ����ʱ��
	 * 
	 * @return�����ַ�����ʽ yyyy-MM-dd HH:mm:ss
	 */
	public static String getStringDate() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(currentTime);
		return dateString;
	}

	/**
	 * ��ȡ����ʱ��
	 * 
	 * @return ���ض�ʱ���ַ�����ʽyyyy-MM-dd
	 */
	public static String getStringDateShort() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
		String dateString = formatter.format(currentTime);
		return dateString;
	}

	/**
	 * ��ȡʱ�� Сʱ:��;�� HH:mm:ss
	 * 
	 * @return
	 */
	public static String getTimeShort() {
		SimpleDateFormat formatter = new SimpleDateFormat("HH:mm:ss");
		Date currentTime = new Date();
		String dateString = formatter.format(currentTime);
		return dateString;
	}

	/**
	 * ����ʱ���ʽ�ַ���ת��Ϊʱ�� yyyy-MM-dd HH:mm:ss
	 * 
	 * @param strDate
	 * @return
	 */
	public static Date strToDateLong(String strDate) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		ParsePosition pos = new ParsePosition(0);
		Date strtodate = formatter.parse(strDate, pos);
		return strtodate;
	}

	/** * ����ʱ���ʽʱ��ת��Ϊ�ַ��� yyyy-MM-dd HH:mm:ss * * @param dateDate * @return */
	public static String dateToStrLong(java.util.Date dateDate) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(dateDate);
		return dateString;
	}

	/**
	 * ����ʱ���ʽʱ��ת��Ϊ�ַ��� yyyy-MM-dd
	 * 
	 * @param dateDate
	 * @param k
	 * @return
	 */
	public static String dateToStr(java.util.Date dateDate) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
		String dateString = formatter.format(dateDate);
		return dateString;
	}

	/**
	 * ����ʱ���ʽ�ַ���ת��Ϊʱ�� yyyy-MM-dd
	 * 
	 * @param strDate
	 * @return
	 */
	public static Date strToDate(String strDate) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
		ParsePosition pos = new ParsePosition(0);
		Date strtodate = formatter.parse(strDate, pos);
		return strtodate;
	}

	/**
	 * �õ�����ʱ��
	 * 
	 * @return
	 */
	public static Date getNow() {
		Date currentTime = new Date();
		return currentTime;
	}

	/**
	 * ��ȡһ�����е����һ��
	 * 
	 * @param day
	 * @return
	 */
	public static Date getLastDate(long day) {
		Date date = new Date();
		long date_3_hm = date.getTime() - 3600000 * 34 * day;
		Date date_3_hm_date = new Date(date_3_hm);
		return date_3_hm_date;
	}

	/**
	 * �õ�����ʱ��
	 * 
	 * @return �ַ��� yyyyMMdd HHmmss
	 */
	public static String getStringToday() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyyMMdd HHmmss");
		String dateString = formatter.format(currentTime);
		return dateString;
	}

	/**
	 * �õ�����Сʱ
	 */
	public static String getHour() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(currentTime);
		String hour;
		hour = dateString.substring(11, 13);
		return hour;
	}

	/**
	 * �õ����ڷ���
	 * 
	 * @return
	 */
	public static String getTime() {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String dateString = formatter.format(currentTime);
		String min;
		min = dateString.substring(14, 16);
		return min;
	}

	/**
	 * �����û������ʱ���ʾ��ʽ�����ص�ǰʱ��ĸ�ʽ �����yyyyMMdd��ע����ĸy���ܴ�д��
	 * 
	 * @param sformat
	 *            yyyyMMddhhmmss
	 * @return
	 */
	public static String getUserDate(String sformat) {
		Date currentTime = new Date();
		SimpleDateFormat formatter = new SimpleDateFormat(sformat);
		String dateString = formatter.format(currentTime);
		return dateString;
	}

	/**
	 * ����Сʱʱ���Ĳ�ֵ,���뱣֤����ʱ�䶼��"HH:MM"�ĸ�ʽ�������ַ��͵ķ���
	 */
	public static String getTwoHour(String st1, String st2) {
		String[] kk = null;
		String[] jj = null;
		kk = st1.split(":");
		jj = st2.split(":");
		if (Integer.parseInt(kk[0]) < Integer.parseInt(jj[0]))
			return "0";
		else {
			double y = Double.parseDouble(kk[0]) + Double.parseDouble(kk[1])
					/ 60;
			double u = Double.parseDouble(jj[0]) + Double.parseDouble(jj[1])
					/ 60;
			if ((y - u) > 0)
				return y - u + "";
			else
				return "0";
		}
	}

	/**
	 * �õ��������ڼ�ļ������
	 */
	public static String getTwoDay(String sj1, String sj2) {
		SimpleDateFormat myFormatter = new SimpleDateFormat("yyyy-MM-dd");
		long day = 0;
		try {
			java.util.Date date = myFormatter.parse(sj1);
			java.util.Date mydate = myFormatter.parse(sj2);
			day = (date.getTime() - mydate.getTime()) / (24 * 60 * 60 * 1000);
		} catch (Exception e) {
			return "";
		}
		return day + "";
	}

	/**
	 * ʱ��ǰ�ƻ���Ʒ���,����JJ��ʾ����.
	 */
	public static String getPreTime(String sj1, String jj) {
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String mydate1 = "";
		try {
			Date date1 = format.parse(sj1);
			long Time = (date1.getTime() / 1000) + Integer.parseInt(jj) * 60;
			date1.setTime(Time * 1000);
			mydate1 = format.format(date1);
		} catch (Exception e) {
		}
		return mydate1;
	}

	/**
	 * �õ�һ��ʱ���Ӻ��ǰ�Ƽ����ʱ��,nowdateΪʱ��,delayΪǰ�ƻ���ӵ�����
	 */
	public static String getNextDay(String nowdate, String delay) {
		try {
			SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
			String mdate = "";
			Date d = strToDate(nowdate);
			long myTime = (d.getTime() / 1000) + Integer.parseInt(delay) * 24
					* 60 * 60;
			d.setTime(myTime * 1000);
			mdate = format.format(d);
			return mdate;
		} catch (Exception e) {
			return "";
		}
	}

	/**
	 * �ж��Ƿ�����
	 * 
	 * @param ddate
	 * @return
	 */
	public static boolean isLeapYear(String ddate) {

		/**
		 * ��ϸ��ƣ� 1.��400���������꣬���� 2.���ܱ�4������������ 3.�ܱ�4����ͬʱ���ܱ�100������������
		 * 3.�ܱ�4����ͬʱ�ܱ�100������������
		 */
		Date d = strToDate(ddate);
		GregorianCalendar gc = (GregorianCalendar) Calendar.getInstance();
		gc.setTime(d);
		int year = gc.get(Calendar.YEAR);
		if ((year % 400) == 0)
			return true;
		else if ((year % 4) == 0) {
			if ((year % 100) == 0)
				return false;
			else
				return true;
		} else
			return false;
	}

	/**
	 * ��������ʱ���ʽ 26 Apr 2006
	 * 
	 * @param str
	 * @return
	 */
	public static String getEDate(String str) {
		SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
		ParsePosition pos = new ParsePosition(0);
		Date strtodate = formatter.parse(str, pos);
		String j = strtodate.toString();
		String[] k = j.split(" ");
		return k[2] + k[1].toUpperCase() + k[5].substring(2, 4);
	}

	/**
	 * ��ȡһ���µ����һ��
	 * 
	 * @param dat
	 * @return
	 */
	public static String getEndDateOfMonth(String dat) {// yyyy-MM-dd
		String str = dat.substring(0, 8);
		String month = dat.substring(5, 7);
		int mon = Integer.parseInt(month);
		if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8
				|| mon == 10 || mon == 12) {
			str += "31";
		} else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
			str += "30";
		} else {
			if (isLeapYear(dat)) {
				str += "29";
			} else {
				str += "28";
			}
		}
		return str;
	}

	/**
	 * �ж϶���ʱ���Ƿ���ͬһ����
	 * 
	 * @param date1
	 * @param date2
	 * @return
	 */
	public static boolean isSameWeekDates(Date date1, Date date2) {
		Calendar cal1 = Calendar.getInstance();
		Calendar cal2 = Calendar.getInstance();
		cal1.setTime(date1);
		cal2.setTime(date2);
		int subYear = cal1.get(Calendar.YEAR) - cal2.get(Calendar.YEAR);
		if (0 == subYear) {
			if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
					.get(Calendar.WEEK_OF_YEAR))
				return true;
		} else if (1 == subYear && 11 == cal2.get(Calendar.MONTH)) {
			// ���12�µ����һ�ܺ�������һ�ܵĻ������һ�ܼ���������ĵ�һ��
			if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
					.get(Calendar.WEEK_OF_YEAR))
				return true;
		} else if (-1 == subYear && 11 == cal1.get(Calendar.MONTH)) {
			if (cal1.get(Calendar.WEEK_OF_YEAR) == cal2
					.get(Calendar.WEEK_OF_YEAR))
				return true;
		}
		return false;
	}

	/**
	 * ����������,���õ���ǰʱ�����ڵ�����ǵڼ���
	 * 
	 * @return
	 */
	public static String getSeqWeek() {
		Calendar c = Calendar.getInstance(Locale.CHINA);
		String week = Integer.toString(c.get(Calendar.WEEK_OF_YEAR));
		if (week.length() == 1)
			week = "0" + week;
		String year = Integer.toString(c.get(Calendar.YEAR));
		return year + week;
	}

	/**
	 * ����ʱ��֮�������
	 * 
	 * @param date1
	 * @param date2
	 * @return
	 */
	public static long getDays(String date1, String date2) {
		if (date1 == null || date1.equals(""))
			return 0;
		if (date2 == null || date2.equals(""))
			return 0;
		// ת��Ϊ��׼ʱ��
		SimpleDateFormat myFormatter = new SimpleDateFormat("yyyy-MM-dd");
		java.util.Date date = null;
		java.util.Date mydate = null;
		try {
			date = myFormatter.parse(date1);
			mydate = myFormatter.parse(date2);
		} catch (Exception e) {
		}
		long day = (date.getTime() - mydate.getTime()) / (24 * 60 * 60 * 1000);
		return day;
	}

	/**
	 * ȡ�����ݿ����� ���ɸ�ʽΪyyyymmddhhmmss+kλ�����
	 * 
	 * @param k
	 *            ��ʾ��ȡ��λ������������Լ���
	 */

	public static String getNo(int k) {

		return getUserDate("yyyyMMddhhmmss") + getRandom(k);
	}

	/**
	 * ����һ�������
	 * 
	 * @param i
	 * @return
	 */
	public static String getRandom(int i) {
		Random jjj = new Random();
		// int suiJiShu = jjj.nextInt(9);
		if (i == 0)
			return "";
		String jj = "";
		for (int k = 0; k < i; k++) {
			jj = jj + jjj.nextInt(9);
		}
		return jj;
	}
}
