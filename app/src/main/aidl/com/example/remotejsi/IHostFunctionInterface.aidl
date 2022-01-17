// IHostFunctionInterface.aidl
package com.example.remotejsi;

import com.example.remotejsi.IValueCollectionInterface;

interface IHostFunctionInterface {
    IBinder call(IBinder thisVal, IValueCollectionInterface args, long size);
}