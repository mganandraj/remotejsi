package com.example.remotejsi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.ConditionVariable;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.remotejsi.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements JSIProxy.JSIProxyListener {

    private static final String LOG_TAG = "remotejsi-MainActivity";


    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        // TextView tv = binding.sampleText;
        // tv.setText(stringFromJNI());

        JSIProxy.INSTNACE.setListener(this);

        Button startServiceButton = binding.startServiceButton;
        startServiceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                intent.setClassName("com.example.remotejsi",
                        "com.example.remotejsi.JSIImplService");
                Log.d(LOG_TAG, "[App] [java] bindService");
                bindService(intent, JSIProxy.INSTNACE, BIND_AUTO_CREATE);
            }
        });

        Button startRuntimeButton = binding.startRuntimeButton;
        startRuntimeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                JSIProxy.INSTNACE.startRuntime();
            }
        });
    }

    /*@Override
    protected void onResume() {
        super.onResume();


        new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                runOnUiThread(new SetTextRunnable("Waiting to talk to IMyService..."));



                String returnedString = talkToService();

                runOnUiThread(new SetTextRunnable("Talked to IMyService. Returned : " + returnedString));
            }
        }).start();
    }*/

    @Override
    public void onServiceStatusChanged(String status) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                binding.serviceStatusTextview.setText(status);
            }
        });
    }
}