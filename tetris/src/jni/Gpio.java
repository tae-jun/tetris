package jni;

import java.util.ArrayList;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * Singleton class Use method Gpio.getInstance() to get instance
 * 
 * @author Jun
 * 
 */
public class Gpio {

	private ArrayList<OnClickListener> listeners;
	private GpioThread gpioThread;
	private Handler onGpioBtnClickHandler;

	private static Gpio gpioInstance;
	private static final String tag = "Gpio";
	private static final int GPIO_CLICK = 0;
	private static final int GPIO_CLICK_FAIL = -1;

	public static final int KEYCODE_GPIO = 100;

	@SuppressLint("HandlerLeak")
	private Gpio() {
		this.listeners = new ArrayList<Gpio.OnClickListener>();

		// Startup thread
		onGpioBtnClickHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				if (msg.what == GPIO_CLICK) {
					for (int i = 0; i < listeners.size(); i++) {
						listeners.get(i).onClick(GPIO_CLICK);
					}
				} else if (msg.what == GPIO_CLICK_FAIL) {
					for (int i = 0; i < listeners.size(); i++) {
						listeners.get(i).onClickFail(GPIO_CLICK_FAIL);
					}
				}
			}
		};

		gpioThread = new GpioThread(onGpioBtnClickHandler);
		gpioThread.setName("GpioThread");
		gpioThread.start();

		Log.d(tag, "GPIO instance created");
	}

	public void addOnClickListener(OnClickListener listener) {
		this.listeners.add(listener);
	}

	public static Gpio getInstance() {
		if (gpioInstance == null) {
			synchronized (Gpio.class) {
				if (gpioInstance == null)
					gpioInstance = new Gpio();
			}
		}

		return gpioInstance;
	}

	/**
	 * Return -1 = ERROR Return 0 = Good
	 * 
	 * @return
	 */
	private native int waitClick();

	private class GpioThread extends Thread {
		private Handler handler;

		public GpioThread(Handler handler) {
			this.handler = handler;
		}

		@Override
		public void run() {
			boolean runThread = true;
			while (runThread) {
				// Wait for GPIO button clicked
				int result = waitClick();
				handler.sendEmptyMessage(result);
				// Stop if cannot find GPIO module
				if (result == GPIO_CLICK_FAIL)
					runThread = false;
			}

			Log.e(tag, "GPIO Thread stopped");
		}
	}

	public interface OnClickListener {

		void onClick(int result);

		void onClickFail(int result);
	}
}