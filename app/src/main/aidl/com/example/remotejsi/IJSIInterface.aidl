// IJSIInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIInterface {
    // String eval(String aString);

    // Returns JSValueBinder
    IBinder eval(IBinder bufferBinder, String sourceURL);

    IBinder createObject();

    IBinder createFromAscii(in byte[] chars, long length);
    IBinder createFromUtf8(in byte[] bytes, long length);
}