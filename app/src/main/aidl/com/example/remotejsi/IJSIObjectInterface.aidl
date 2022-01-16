// IJSIObjectInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIObjectInterface {
    boolean has(IBinder name);
    IBinder get(IBinder name);
    void set(IBinder name, IBinder value);
}