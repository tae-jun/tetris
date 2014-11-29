package jni;

import android.os.AsyncTask;

/**
 * Singleton class Use method Gpio.getInstance() to get instance
 * 
 * @author Jun
 * 
 */
public class GpioTh extends  {
	// Load library when class loaded
	static {
		System.loadLibrary("gpio");
	}

	private OnClickListener listener = null;

	private static GpioTh ins = null;
	public static final int KEYCODE_GPIO = 100;

	private GpioTh() {
		setGpioAsyncTask();
	}

	/**
	 * Set litener for gpio button
	 * 
	 * @param listener
	 */
	public void setOnClickListener(OnClickListener listener) {
		this.listener = listener;
	}

	/**
	 * Return -1 = ERROR Return 0 = Good
	 * 
	 * @return
	 */
	private native int waitClick();

	private void setGpioAsyncTask() {
		GpioAsync async = new GpioAsync();
		async.execute();
	}

	public static synchronized GpioTh getInstance() {
		if (ins == null) {
			ins = new GpioTh();
		}
		return ins;
	}

	private class GpioAsync extends AsyncTask<Void, Void, Integer> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			// Before background task
		}

		@Override
		protected Integer doInBackground(Void... params) {
			// Wait until GPIO button pressed
			return waitClick();
		}

		@Override
		protected void onPostExecute(Integer result) {
			super.onPostExecute(result);
			// After background task
			if (listener != null)
				listener.onClick(result);

			setGpioAsyncTask();
		}
	}

	public interface OnClickListener {
		/**
		 * 0 = success, -1 = error
		 * 
		 * @param result
		 */
		void onClick(Integer result);
	}

}