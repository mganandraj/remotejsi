package com.example.remotejsi;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class JSIService extends Service {

    // Used to load the 'native-lib' library on application startup.
    static
    {
        System.loadLibrary("remotejsi");
        System.loadLibrary("hermes");
    }

    private IBinder mBinder;

    private static final String LOG_TAG = "remotejsi-JSIService";

    public JSIService() {
    }

    @Override
    public void onCreate()
    {
        super.onCreate();

        mBinder = createServiceBinder();

        if(null == mBinder)
        {
            Log.w(LOG_TAG, "[MyService] [java] Binder is null");
        }
        else
        {
            Log.d(LOG_TAG, "[MyService] [java] Binder is ready");
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d(LOG_TAG, "[MyService] [java] A client binds the service");
        return mBinder;
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native IBinder createServiceBinder();
}