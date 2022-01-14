package com.example.remotejsi;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.ConditionVariable;
import android.os.IBinder;
import android.util.Log;

// TODO:: Quick and dirty singleton .. Need to relook.
public class JSIProxy implements ServiceConnection {

    static {
        System.loadLibrary("jsiproxy");
    }

    public interface JSIProxyListener {
        void onServiceStatusChanged(String status);
    }

    public static JSIProxy INSTNACE = new JSIProxy();
    private static final String LOG_TAG = "JSIPROXY";

    private JSIProxyListener mListener = null;

    // private IJSIInterface mService = null;
    private volatile boolean mIsServiceConnected = false;
    private final ConditionVariable mServiceConnectionWaitLock = new ConditionVariable();

    public void setListener(JSIProxyListener listener) {
        mListener = listener;
    }

    private void blockTillConnected() {
        while(!mIsServiceConnected)
        {
            mServiceConnectionWaitLock.block(); // waits for service connection
        }
    }

    @Override
    public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
        Log.d(LOG_TAG, "[App] [java] onServiceConnected");
        onServiceConnected(iBinder);
        mIsServiceConnected = true;
        mServiceConnectionWaitLock.open(); // breaks service connection waits
        mListener.onServiceStatusChanged("Service connected");
    }

    @Override
    public void onServiceDisconnected(ComponentName componentName) {
        mIsServiceConnected = false;
        onServiceDisconnected();
        Log.d(LOG_TAG, "[App] [java] onServiceDisconnected");
        mListener.onServiceStatusChanged("Service disconnected");
    }

    public void startRuntime() {
        talkToService();
    }

    private native void onServiceConnected(IBinder binder);
    private native void onServiceDisconnected();
    private native String talkToService();
}
