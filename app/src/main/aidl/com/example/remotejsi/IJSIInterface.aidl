// IJSIInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIInterface {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    void basicTypes(int anInt, long aLong, boolean aBoolean, float aFloat,
             double aDouble, String aString);

    // IBinder get();

    String handshake(IBinder remoteJSIInterface);
}