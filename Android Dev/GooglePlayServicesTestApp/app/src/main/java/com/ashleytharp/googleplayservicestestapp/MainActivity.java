package com.ashleytharp.googleplayservicestestapp;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentSender;
import android.os.AsyncTask;
import android.support.v4.app.FragmentActivity;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.ErrorDialogFragment;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.drive.Drive;
import com.google.android.gms.common.api.GoogleApiClient.OnConnectionFailedListener;
import com.google.android.gms.drive.DriveApi;
import com.google.android.gms.drive.query.Filters;
import com.google.android.gms.drive.query.Query;
import com.google.android.gms.drive.query.SearchableField;

public class MainActivity extends FragmentActivity implements GoogleApiClient.ConnectionCallbacks, OnConnectionFailedListener {

    private GoogleApiClient mGoogleApiClient;

    //request code to use when launching the resolution Activity. In onConnectionFailed we run through some failure resolution and we
    //would use this code there. Still unclear on why this 1001...derp
    private static final int REQUEST_RESOLVE_ERROR = 1001;

    //the error message. In onConnectionFailed we run through some failure resolution and we
    //would use this code there.
    private static final String DIALOG_ERROR = "ERRRRRRROOOORRR!!! :(";

    //this string indicates that the app is in a state of error
    private static final String STATE_RESOLVING_ERROR = "resolving_error";

    //keeps track of the app state while the user is resolving the error
    // to avoid repetitive attempts to resolve the same error. For example if somebody rotated the screen, we
    //would need this flag so that when the activity is refreshed, we know that we are still working on the same error
    private boolean mResolvingError = false;

    /**
     * Called when this activity is create.
     * @param savedInstanceState - this savedInstanceState bundle is populated in onSaveInstanceState so that we can keep these state
     *                           variables between activity refreshes
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //grab the xml docuument activity_main for the layout on the screen
        setContentView(R.layout.activity_main);

        //grab that state variables saved before the activity refreshed
        mResolvingError = (savedInstanceState != null && savedInstanceState.getBoolean(STATE_RESOLVING_ERROR, false));

        //now let's make a client.  This client is going to connect to the google cloud service
        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .addApi(Drive.API) //GoogleApiClient is going to attempt to connect to this API
                .addScope(Drive.SCOPE_FILE)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .build();
    }

    /**
     * this function is called after onCreate()
     */
    @Override
    protected void onStart(){
        super.onStart();

        //if(!mResolvingError){
        //    mGoogleApiClient.connect();
        //}
    }

    @Override
    protected void onStop(){
        mGoogleApiClient.disconnect();
        super.onStop();
    }

    /**
     * if our activity becomes interrupted and has to be refreshed, such as when the user rotates the screen,
     * this onSaveInstanceState callback will be called and we can save all our handly app state variables
     * in this bundle outState
     * @param outState - we can put any handy app state variables in this bundle to be retrieved when the activity is
     *                 refreshed, such as from rotating the screen.
     */
    @Override
    protected void onSaveInstanceState(Bundle outState){}

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

    /**
     *Execution directs to this function once the connection to Google Play Services has been made
     * @param connectionHint: no idea what this is for
     */
    @Override
    public void onConnected(Bundle connectionHint) {

    }

    /**
     * pretty self explanatory
     * @param causeOfSuspension: the error code received when the connection was suspended
     */
    @Override
    public void onConnectionSuspended(int causeOfSuspension) {
        // The connection has been interrupted.
        // Disable any UI components that depend on Google APIs
        // until onConnected() is called.
    }

    /**
     *When you receive a call to the onConnectionFailed() callback, you should call hasResolution() on the provided ConnectionResult object.
     * If it returns true, you can request the user take immediate action to resolve the error by calling startResolutionForResult() on the
     * ConnectionResult object. The startResolutionForResult() behaves the same as startActivityForResult()} and launches the appropriate
     * activity for the user to resolve the error (such as an activity to select an account).

     If hasResolution() returns false, you should instead call GooglePlayServicesUtil.getErrorDialog(), passing it the error code. This returns
     a Dialog provided by Google Play services that's appropriate for the given error. The dialog may simply provide a message explaining the
     error, but it may also provide an action to launch an activity that can resolve the error (such as when the user needs to install a newer
     version of Google Play services).

     * @param connectionResult
     */
    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {

        //if we are already attempt to resolve an error exit this function, we don't need to troubleshoot all of them
        if(mResolvingError){
            //already attempting to resolve an error
            return;

            //but if not, we check to see if this particular error has a resolution defined in GoogleAPiClient.
        }else if(connectionResult.hasResolution()){
            try{
                mResolvingError = true;
                connectionResult.startResolutionForResult(this, REQUEST_RESOLVE_ERROR);
            }catch(IntentSender.SendIntentException sendIntentExceptionError){
                //An Intent is a messaging object you can use to request an action from another app component.
                //startResolutionForResult probably tried to send an Intent to something in the GoogleAPIClient
                //and we are catching that error here.
                //Since there was an error when trying to resolve this error on this connection attempt, but we know we can resolve this type of
                //error, the only thing to do here is to attempt to connect again.
                mGoogleApiClient.connect();
            }
        }
        //if there turns out to be no resolution defined in the GoogleClientApi then we just output a message for the user depending on the error
        //code. We might tell the user something like "invalid credentials" or "create an account you, guy"
        else{
            showErrorDialog(connectionResult.getErrorCode());
            mResolvingError = true;
        }
    }

    private void showErrorDialog(int errorCode){

        //Let's create a fragment for the error dialog!
        ErrorDialogFragment dialogFragment = new ErrorDialogFragment();
        //pass the error that should be displayed. This Bundle is just a container for all the things that we want to give to the error dialog fragment
        Bundle bundle = new Bundle();
        bundle.putInt(DIALOG_ERROR,errorCode);
        dialogFragment.setArguments(bundle);
        dialogFragment.show(this.getFragmentManager(), "woohoo error dialog!");
    }

    /**
     * This function is somewhat vaguely named, but basically this callback is called after we finish resolving an
     * error, or the error dialog completes.
     * if the REQUEST code is REQUEST_RESOLVE_ERROR, we are saying that there was an error, so what we should do
     * is see if it is okay to attempt to connect again.  If the REQUEST code is anything else, that means that
     * there was no error and so we don't have to do anything here.
     * if RESULT code is RESULT_OK it does not mean necessarily that the error was resolved, it just means that
     * it's okay for us to attempt to connect again.
     *

     * @param requestCode - what kind of request made
     * @param resultCode - the result of that request
     * @param data - data is not used in this function, but could be if the request returned a data bundle...
     */
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data){

        if(requestCode == REQUEST_RESOLVE_ERROR){
                //we are basically done trying to attempt to solve this error because we are in the result callback
               //This mResolvingError boolean keeps track of the app state while the user is resolving the error
               // to avoid repetitive attempts to resolve the same error.
                mResolvingError = false;
            //if we were resolving an error and we got the result RESULT_OK, that means that it is okay to
            //attempt to connect again.
            if(resultCode == RESULT_OK){

                //here we make sure that the app is not already connected or attempting to connect
                if(!mGoogleApiClient.isConnecting() && !mGoogleApiClient.isConnected()){
                    //yay! we can try to connect again!
                    mGoogleApiClient.connect();
                }
            }
        }
    }

    /**
     * this is an asynchrous call to fetch a file from the google play services cloud service
     *
     * @param fileName - name of the file we are fetching from the google pay services server
     */
    private void loadFile(String fileName){
        //create a query for a specific file name in Drive
        Query query = new Query.Builder()
                .addFilter(Filters.eq(SearchableField.TITLE, fileName))
                .build();

        //invoke the query asynchronously with a callback method
        Drive.DriveApi.query(mGoogleApiClient, query)
                //A ResultCallback is an interface for receiving a Result from a PendingResult as an asynchronous callback.
                //we may not always
                .setResultCallback(new ResultCallback<DriveApi.MetadataBufferResult>() {
                    @Override
                    public void onResult(DriveApi.MetadataBufferResult result) {
                        //Success! Now we have to handle the query result...
                    }
                });
    }
}
