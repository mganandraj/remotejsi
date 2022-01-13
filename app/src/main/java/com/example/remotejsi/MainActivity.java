package com.example.remotejsi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.ConditionVariable;
import android.os.IBinder;
import android.util.Log;
import android.widget.TextView;

import com.example.remotejsi.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements ServiceConnection {

    private static final String LOG_TAG = "remotejsi-MainActivity";

    // Used to load the 'remotejsi' library on application startup.
    static {
        System.loadLibrary("remotejsi");
    }

    private IJSIAidlInterface mService = null;
    private volatile boolean mIsServiceConnected = false;
    private final ConditionVariable mServiceConnectionWaitLock = new ConditionVariable();


    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    @Override
    protected void onResume() {
        super.onResume();

        Intent intent = new Intent();
        intent.setClassName("com.example.remotejsi",
                "com.example.remotejsi.JSIService");

        Log.d(LOG_TAG, "[App] [java] bindService");

        bindService(intent, this, BIND_AUTO_CREATE);

        new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                runOnUiThread(new SetTextRunnable("Waiting to talk to IMyService..."));

                // Not connected to service yet?
                while(!mIsServiceConnected)
                {
                    mServiceConnectionWaitLock.block(); // waits for service connection
                }

                String returnedString = talkToService();

                runOnUiThread(new SetTextRunnable("Talked to IMyService. Returned : " + returnedString));
            }
        }).start();
    }

    /**
     * A native method that is implemented by the 'remotejsi' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    @Override
    public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
        Log.d(LOG_TAG, "[App] [java] onServiceConnected");
        onServiceConnected(iBinder);
        mIsServiceConnected = true;
        mServiceConnectionWaitLock.open(); // breaks service connection waits
    }

    @Override
    public void onServiceDisconnected(ComponentName componentName) {
        mIsServiceConnected = false;
        onServiceDisconnected();
        Log.d(LOG_TAG, "[App] [java] onServiceDisconnected");
    }

    public native void onServiceConnected(IBinder binder);
    public native void onServiceDisconnected();
    public native String talkToService();

    private class SetTextRunnable implements Runnable
    {
        final String mText;

        SetTextRunnable(String text)
        {
            mText = text;
        }

        @Override
        public void run()
        {
            // mTV.setText(mText);
            Log.d(LOG_TAG, "[SetTextRunnable] :: " + mText);
        }
    }
}