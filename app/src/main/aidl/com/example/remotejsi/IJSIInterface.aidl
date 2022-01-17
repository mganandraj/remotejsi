// IJSIInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIInterface {
    // String eval(String aString);

    // Returns JSValueBinder
    IBinder eval(IBinder bufferBinder, String sourceURL);

    IBinder createObject();

    // This is wierd .. Need to find a more elegant solution ..
    IBinder cloneValue(byte valueType, boolean boolValue, double doubleValue, IBinder pointerBinder);

    IBinder createFromAscii(in byte[] chars, long length);
    IBinder createFromUtf8(in byte[] bytes, long length);

    IBinder createValueCollection();
    IBinder createFunctionFromHostFunction(IBinder hostFunct, IBinder propId, long paramCount);

    IBinder call(IBinder func, IBinder thisObj, IBinder args, long argsCount);
    IBinder callAsConstructor(IBinder func, IBinder args, long argsCount);
}