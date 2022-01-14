// IJSIInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIInterface {
    String eval(String aString);

    // Returns JSValueBinder
    // IBinder eval(IBinder bufferBinder, String sourceURL);
}