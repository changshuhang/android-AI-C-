package com.csh.wuziqi.util;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Matrix;

public class ImageUtils {

	public Bitmap compressImage(Bitmap bitmap, int target_size) {
		ByteArrayOutputStream boas = new ByteArrayOutputStream();
		bitmap.compress(Bitmap.CompressFormat.JPEG, 100, boas);
		int quality = 100;
		int length = boas.toByteArray().length / 1024;
		while (length > target_size) {
			boas.reset();
			quality -= 10;
			bitmap.compress(Bitmap.CompressFormat.JPEG, quality, boas);
			length = boas.toByteArray().length / 1024;
		}
		byte[] data = boas.toByteArray();
		int cp_length = data.length;
		return BitmapFactory.decodeByteArray(data, 0, cp_length);
	}

	// �ڶ���ͼƬ��������Сѹ������������·����ȡͼƬ��ѹ������
	public Bitmap getimage(String srcPath, int image_size) {
		BitmapFactory.Options newOpts = new BitmapFactory.Options();
		// ��ʼ����ͼƬ����ʱ��options.inJustDecodeBounds ���true��
		newOpts.inJustDecodeBounds = true;
		Bitmap bitmap = BitmapFactory.decodeFile(srcPath, newOpts);// ��ʱ����bmΪ��

		newOpts.inJustDecodeBounds = false;
		int w = newOpts.outWidth;
		int h = newOpts.outHeight;
		// ���������ֻ��Ƚ϶���800*480�ֱ��ʣ����ԸߺͿ���������Ϊ
		float hh = 800f;// �������ø߶�Ϊ800f
		float ww = 480f;// �������ÿ��Ϊ480f
		// ���űȡ������ǹ̶��������ţ�ֻ�ø߻��߿�����һ�����ݽ��м��㼴��
		int be = 1;// be=1��ʾ������
		if (w > h && w > ww) {// �����ȴ�Ļ����ݿ�ȹ̶���С����
			be = (int) (newOpts.outWidth / ww);
		} else if (w < h && h > hh) {// ����߶ȸߵĻ����ݿ�ȹ̶���С����
			be = (int) (newOpts.outHeight / hh);
		}
		if (be <= 0)
			be = 1;
		newOpts.inSampleSize = be;// �������ű���
		// ���¶���ͼƬ��ע���ʱ�Ѿ���options.inJustDecodeBounds ���false��
		bitmap = BitmapFactory.decodeFile(srcPath, newOpts);

		return compressImage(bitmap, image_size);// ѹ���ñ�����С���ٽ�������ѹ��
	}

	// ������ͼƬ��������Сѹ������������BitmapͼƬѹ������
	public Bitmap comp(Bitmap image, int image_size) {

		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		image.compress(Bitmap.CompressFormat.JPEG, 100, baos);
		if (baos.toByteArray().length / 1024 > image_size) {// �ж����ͼƬ����image_size
															// kb,����ѹ������������ͼƬ��BitmapFactory.decodeStream��ʱ���
			baos.reset();// ����baos�����baos
			image.compress(Bitmap.CompressFormat.JPEG, 50, baos);// ����ѹ��50%����ѹ��������ݴ�ŵ�baos��
		}
		ByteArrayInputStream isBm = new ByteArrayInputStream(baos.toByteArray());
		BitmapFactory.Options newOpts = new BitmapFactory.Options();
		// ��ʼ����ͼƬ����ʱ��options.inJustDecodeBounds ���true��
		newOpts.inJustDecodeBounds = true;
		Bitmap bitmap = BitmapFactory.decodeStream(isBm, null, newOpts);
		newOpts.inJustDecodeBounds = false;
		int w = newOpts.outWidth;
		int h = newOpts.outHeight;
		// ���������ֻ��Ƚ϶���800*480�ֱ��ʣ����ԸߺͿ���������Ϊ
		float hh = 800f;// �������ø߶�Ϊ800f
		float ww = 480f;// �������ÿ��Ϊ480f
		// ���űȡ������ǹ̶��������ţ�ֻ�ø߻��߿�����һ�����ݽ��м��㼴��
		int be = 1;// be=1��ʾ������
		if (w > h && w > ww) {// �����ȴ�Ļ����ݿ�ȹ̶���С����
			be = (int) (newOpts.outWidth / ww);
		} else if (w < h && h > hh) {// ����߶ȸߵĻ����ݿ�ȹ̶���С����
			be = (int) (newOpts.outHeight / hh);
		}
		if (be <= 0)
			be = 1;
		newOpts.inSampleSize = be;// �������ű���
		// ���¶���ͼƬ��ע���ʱ�Ѿ���options.inJustDecodeBounds ���false��
		isBm = new ByteArrayInputStream(baos.toByteArray());
		bitmap = BitmapFactory.decodeStream(isBm, null, newOpts);

		return compressImage(bitmap, image_size);// ѹ���ñ�����С���ٽ�������ѹ��
	}

	public static void saveImage(Bitmap bitmap, File file, int quality) {
		if (!file.getParentFile().exists()) {
			file.getParentFile().exists();
		}
		try {
			FileOutputStream outputStream = new FileOutputStream(file);
			if (bitmap.compress(Bitmap.CompressFormat.JPEG, quality,
					outputStream)) {
				outputStream.flush();
				outputStream.close();
			}
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

	public void transImage(String fromFile, String toFile, int width,
			int height, int quality) {
		try {
			Bitmap bitmap = BitmapFactory.decodeFile(fromFile);
			int bitmapWidth = bitmap.getWidth();
			int bitmapHeight = bitmap.getHeight();
			float scaleWidth = (float) width / bitmapWidth;
			float scaleHeight = (float) height / bitmapHeight;
			Matrix matrix = new Matrix();
			matrix.postScale(scaleWidth, scaleHeight);
			Bitmap resizeBitmap = Bitmap.createBitmap(bitmap, 0, 0,
					bitmapWidth, bitmapHeight, matrix, true);
			// save file
			File myCaptureFile = new File(toFile);
			FileOutputStream out = new FileOutputStream(myCaptureFile);
			if (resizeBitmap.compress(Bitmap.CompressFormat.JPEG, quality, out)) {
				out.flush();
				out.close();
			}
			// realse memory resources
			if (!bitmap.isRecycled()) {
				bitmap.recycle();
			}
			if (!resizeBitmap.isRecycled()) {
				resizeBitmap.recycle();
			}
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

	// ֱ������ͼƬ
	public Bitmap getBitmap(String path, int inSampleSize) {
		Options options = new Options();
		options.inSampleSize = inSampleSize;
		return BitmapFactory.decodeFile(path, options);
	}

	// ���߶�ѹ������ͼƬ
	public static Bitmap getBitmap(String path, int width, int heigh) {
		Options options = new Options();
		options.inJustDecodeBounds = true;
		Bitmap bitmap = BitmapFactory.decodeFile(path, options);
		int xScale = options.outWidth / width;
		int yScale = options.outHeight / heigh;
		if (xScale > yScale) {
			options.inSampleSize = xScale;
		} else {
			options.inSampleSize = yScale;
		}
		options.inSampleSize = 2 * options.inSampleSize;
		options.inJustDecodeBounds = false;
		bitmap = BitmapFactory.decodeFile(path, options);

		return bitmap;
	}

	/**
	 * ��path�л�ȡͼƬ��Ϣ
	 * 
	 * @param path
	 * @return
	 */
	public Bitmap decodeBitmap(String path, int width, int height) {
		BitmapFactory.Options op = new BitmapFactory.Options();
		op.inJustDecodeBounds = true;
		Bitmap bmp = BitmapFactory.decodeFile(path, op); // ��ȡ�ߴ���Ϣ
		// ��ȡ������С
		int wRatio = (int) Math.ceil(op.outWidth / width);
		int hRatio = (int) Math.ceil(op.outHeight / height);
		// �������ָ����С������С��Ӧ�ı���
		if (wRatio > 1 && hRatio > 1) {
			if (wRatio > hRatio) {
				op.inSampleSize = wRatio;
			} else {
				op.inSampleSize = hRatio;
			}
		}
		op.inJustDecodeBounds = false;
		bmp = BitmapFactory.decodeFile(path, op);
		return bmp;
	}
}
