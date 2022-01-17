// IValueCollectionInterface.aidl
package com.example.remotejsi;

// Declare any non-default types here with import statements

interface IValueCollectionInterface {
    void add(IBinder value);
    IBinder get(long index);
    long getCount();
}