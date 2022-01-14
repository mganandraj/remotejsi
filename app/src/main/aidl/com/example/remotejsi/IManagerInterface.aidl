// IManagerInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IManagerInterface {
    void ping();
    IBinder createJSIInterface(IBinder remoteJSIInterface);
}