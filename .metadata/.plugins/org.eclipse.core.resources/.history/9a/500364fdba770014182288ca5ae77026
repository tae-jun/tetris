package myandroid.testapp;

import jni.Gpio;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.KeyEvent;
import android.widget.Button;
import android.content.Intent;
import android.util.Log;

public class MainActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// 시작 액티비티
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		Log.d("[TetrisLog]", "Tetris#onCreate()");
		
		// Start Button 등록
		Button startButton = (Button) findViewById(R.id.startGame);
		startButton.setOnClickListener(new Button.OnClickListener() {

			public void onClick(View v) {
				// Intent 생성
				Intent intent = new Intent(MainActivity.this, TetrisActivity.class);
				// Activity 시작
				startActivity(intent);
			}
		});
	}
}
