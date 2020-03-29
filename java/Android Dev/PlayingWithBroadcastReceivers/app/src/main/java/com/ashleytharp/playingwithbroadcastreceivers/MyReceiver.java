package com.ashleytharp.playingwithbroadcastreceivers;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * Created by Ashley on 6/3/2015.
 */
public class MyReceiver extends BroadcastReceiver {

    //Basically to make a BroadcastReceiver we subclass BroadCastReceiver.
    //So normally we would make our own class like MyReceiver that extends BroadcastReceiver. To extend
    //BroadcastReceiver, we only have to implement the one callback function onReceive.
    //You will see that this receiver is defined in the app AndroidManifest file with the tag <receiver>. Different receivers are differentiated by
    //name in the manifest, so this receiver will be named: "MyReceiver".

    //You will see elsewhere in the code that we can also define receivers in an anonymous class, and therefore they won't be defined in the manifest.

    @Override
    public void onReceive(Context context, Intent intent){
        Toast.makeText(context, "Intent detected by BroadcastReceiver!", Toast.LENGTH_LONG).show();
    }
}
