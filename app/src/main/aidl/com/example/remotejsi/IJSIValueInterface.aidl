// IJSIValueInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IJSIValueInterface {
    // Undefined: 0
    // Null: 1
    // Boolean: 2
    // Number: 3
    // Symbol: 4
    // String: 5
    // Object: 6
    // TODO ... enum ?
    byte getType();

    double getNumber();
    boolean getBoolean();

    IBinder getString();
    IBinder getObject();
    IBinder getSymbol();

}