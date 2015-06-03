package com.ashleytharp.playingwithbroadcastreceivers;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class MainActivity extends ActionBarActivity {

    //Broadcast receivers simply respond to broadcast messages from other applications or from the system itself.  These messages are sometimes
    //called events or intents. For example, applications can also initiate broadcasts to let other applications know that some data has been downloaded to the
    //device and is available for them to use. A broadcast receiver will intercept that broadcast and will initiate appropriate action in response to the message.
    private BroadcastReceiver mBroadcastReceiver;

    //now let's make a BroadcastReceiver that is defined in an anonymous class. This means that it's <intent-filter> won't be registered in the manifest. Instead,
    //everytime this activity resumes, we are going to reregister it using this activity's context.  If this activity is paused or stopped we are going to
    //unregister it.  This means that this receiver is only listening during the life of this activity.
    private BroadcastReceiver mLocalBroadcastReceiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //we create a broadcast receiver here (look in the manifest to find where we register the BroadCastReveiver) This is a normal BroadcastReceiver.
        mBroadcastReceiver = new MyReceiver();

        //now we're going to create a BroadcastReceiver that is defined by an anonymous class inside this activity.  This receiver will only listen for events
        //during the life of this activity.
        mLocalBroadcastReceiver = new BroadcastReceiver() {

            //woohoo! We are inside an anonymous class! Check inside of onResume to see where we register this local BroadcastReceiver
            @Override
            public void onReceive(Context context, Intent intent) {
                Toast.makeText(context, "Intent detected by local BroadcastReceiver!", Toast.LENGTH_LONG).show();
            }
        };
    }

    @Override
    public void onResume(){
        super.onResume();

        //We are registering the BroadcastReceiver that is local to this activity here.  This is similar to when we defined the <intent-filter> for the
        //other receiver in the manifest, except that we are doing it in code.
        LocalBroadcastManager.getInstance(this).registerReceiver(mLocalBroadcastReceiver, new IntentFilter("android.intent.action.BOOT_COMPLETED"));
    }

    @Override
    public void onPause(){
        super.onPause();

        //We are unregistering the BroadcastReceiver that is local to this activity here.  This is similar to when we defined the <intent-filter> for the
        //other receiver in the manifest, except that we are doing it in code.
        LocalBroadcastManager.getInstance(this).unregisterReceiver(mLocalBroadcastReceiver);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
