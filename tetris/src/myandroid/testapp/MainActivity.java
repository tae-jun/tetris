package myandroid.testapp;

import jni.Gpio.*;
import jni.Gpio;
import jni.Led;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.content.Intent;
import android.util.Log;

public class MainActivity extends Activity {
	// Load library
	static {
		System.loadLibrary("native");
	}

	private final String tag = "MainActivity";

	public static final int HANDLE_GPIO = 0;
	public static final int HANDLE_LED = 1;
	public static final int HANDLE_7SEGMENT = 2;

	private static TextView txt;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		Log.d(tag, "MainActivity created");

		txt = (TextView) findViewById(R.id.txt);

		// Start Button 등록
		Button startButton = (Button) findViewById(R.id.startGame);
		startButton.setOnClickListener(new Button.OnClickListener() {

			public void onClick(View v) {
				// Intent 생성
				Intent intent = new Intent(MainActivity.this,
						TetrisActivity.class);
				// Activity 시작
				startActivity(intent);
			}
		});

		// Initialize LED
		Led.getInstance().setLed("00000000");

		// Initialize GPIO Button
		Gpio.getInstance().addOnClickListener(new OnClickListener() {

			public void onClickFail(int result) {
				appendText("GPIO module not found");
				appendText("GPIO Thread is going to be stopped");
			}

			public void onClick(int result) {
				// TODO Auto-generated method stub

			}
		});
	}

	public static void appendText(String msg) {
		txt.setText(txt.getText() + "\n" + msg);
	}
}
