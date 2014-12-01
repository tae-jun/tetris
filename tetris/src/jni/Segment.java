package jni;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

public class Segment {

	private SegmentThread segThread;

	private static final String tag = "Segment";
	private static Segment segInstance;

	private Segment() {
		segThread = new SegmentThread();
		segThread.setName("SegmentThread");
		segThread.start();
	}

	public static Segment getInstance() {
		if (segInstance == null) {
			synchronized (Segment.class) {
				if (segInstance == null)
					segInstance = new Segment();
			}
		}

		return segInstance;
	}
	
	/**
	 * Print number
	 * @param num
	 */
	public void setNum(int num){
		
	}

	/**
	 * 0x10 = BRICK1, 0x11 = BRICK2, 0x12 = BRICK3, ... , 0x06 = BRICK7
	 * 
	 * @param ledData
	 *            Hex integer. 0x00~0x09 equal 0~9, and 0x0a~0x0f equal a~f
	 *            (small letter)
	 * @return
	 */
	private native int control(int ledData);

	private class SegmentThread extends Thread {
		Handler handler;
		private Looper mLooper;
		private static final String tag = "SegmentThread";

		public void run() {
			Looper.prepare();
			synchronized (this) {
				mLooper = Looper.myLooper();
				notifyAll();
			}
			Looper.loop();
		}

		public synchronized void waitUntilReady() {
			if (handler == null)
				setHandler();
		}

		private void setHandler() {
			this.handler = new Handler(getLooper()) {
				@Override
				public void handleMessage(Message msg) {
					/*
					 * TODO################################
					 */
				}
			};

			Log.d(tag, "Segment Thread handler created");
		}

		private Looper getLooper() {
			if (mLooper == null)
				synchronized (this) {
					while (mLooper == null) {
						try {
							wait();
						} catch (InterruptedException e) {
						}
					}
				}

			return mLooper;
		}

		private void requestToMainThread(Runnable runnable) {
			new Handler(Looper.getMainLooper()).post(runnable);
		}
	}
}