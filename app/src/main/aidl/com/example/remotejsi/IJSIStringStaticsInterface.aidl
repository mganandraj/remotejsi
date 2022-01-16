// IJSIStringStaticsInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIStringStaticsInterface {
    IBinder createFromAscii(in byte[] chars, long length);
    IBinder createFromUtf8(in byte[] chars, long length);
    IBinder createFromNullTerminatedAscii(in byte[] chars);

    // TODO:: implement strictEquals
}