package com.corduro.corduropaymobilesdkdemoapp.login;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;

import com.corduro.corduropaymobilesdkdemoapp.MainActivity;
import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.corduropaymobilesdkdemoapp.signup.CorduroCreateAccountActivity;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.ICorduroPayMobileCallback;
import com.corduro.paymobilesdk.utils.RequestStatus;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class CorduroLoginActivity extends Activity implements ICorduroPayMobileCallback {

	//textboxes
	private EditText usernameTextBox = null;
	private EditText passwordTextBox = null;

	//progress spinner
	private ProgressBar spinner = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_corduro_login);

		spinner = getSpinnerView();
	}

	/*
		This function will be called when the user clicks the login button
	 */
	public void onClickLoginButton(View view){

		corduroPayMobileController.login(
				getApplicationName(),							   //your application name
				getApplicationVersion(),							//your app version
				getUsername(),									  //username entered by the user
				getPassword(),									  //password entered by the user
				getApplicationIdNumber(),						   //your application id number, this will be given to you by Corduro
				this);											  //listener.  We are saying here that this class implements a funciton called onRequestComplete which will listen
																	//for the results of our login request


				//Note: instead of passing "this" or a class that implements ICorduroPayMobileCallback, we could also pass an anonymous class here,
				//instead of "this" we would pass: new CorduroPayMobileCallback(){
				//
				//@Override
				//public void onRequestComplete(RequestStatus requestStatus){
				//  //your code here
				// }
				// });
				//you should implement whatever is most convenient for you in your code.
				//using anonymous classes you would also be able to define more than one callback in each activity,
				//which is fine albeit less modular.

		showProgressSpinner();
	}

	/*
		This function will be called when the user clicks the cancel button
	 */
	public void onClickCancelButton(View view){
		goBackToMainActivity();
	}

	/*
		This function will be called when the user clicks the create account button
	 */
	public void onClickCreateAccountButton(View view){
		goToCreateAccountActivity();
	}

	/*
		because we specified this class as a listener, this function is called when the login request completes.
	 */
	@Override
	public void onRequestComplete(RequestStatus requestStatus) {

		hideProgressSpinner();
		showToast(requestStatus);

		if( requestWasSuccessful(requestStatus) ) {
			//we logged in successfully so we go back to the main activity
			goBackToMainActivity();

		} else {
			// Perhaps the username or password were incorrect for example, so we stay on this screen and let the user try again
		}

	}

	private void showToast(RequestStatus requestStatus){
		CommonUtils.showToast(getApplicationContext(), requestStatus.msg);
	}

	private boolean requestWasSuccessful(RequestStatus requestStatus){
		return CorduroPayMobile.requestWasSuccessful(requestStatus);
	}

	private void goBackToMainActivity(){
		Intent goBackToMainActivity = new Intent(this, MainActivity.class);
		startActivity(goBackToMainActivity);
	}

	private void goToCreateAccountActivity(){
		Intent goToCreateAccountActivity = new Intent(this, CorduroCreateAccountActivity.class);
		startActivity(goToCreateAccountActivity);
	}

	public ProgressBar getSpinnerView(){
		return (ProgressBar) findViewById(R.id.progress_bar_login_activity);
	}

	private void showProgressSpinner(){
		spinner.setVisibility(View.VISIBLE);
	}

	private void hideProgressSpinner(){
		spinner.setVisibility(View.GONE);
	}

	private String getUsername(){
		usernameTextBox = getUsernameTextBoxView();
		return usernameTextBox.getText().toString();
	}

	private String getPassword(){
		passwordTextBox = getPasswordTextBoxView();
		return passwordTextBox.getText().toString();
	}

	private String getApplicationName(){
		return getResources().getString(R.string.app_name);
	}

	private String getApplicationVersion(){
		return getResources().getString(R.string.application_version);
	}

	private Integer getApplicationIdNumber(){
		return Integer.parseInt(getResources().getString(R.string.application_id_number));
	}

	private EditText getUsernameTextBoxView(){
		return (EditText) findViewById(R.id.login_activity_user_name_text_box);
	}

	private EditText getPasswordTextBoxView(){
		return (EditText) findViewById(R.id.login_activity_password_text_box);
	}
}
