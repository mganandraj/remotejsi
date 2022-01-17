// IHostObjectInterface.aidl
package com.example.remotejsi;

import com.example.remotejsi.IValueCollectionInterface;

interface IHostObjectInterface {
    IBinder get(IBinder name);
    void set(IBinder name, IBinder value);
    void getPropertyNames();
}