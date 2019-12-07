package com.corduro.corduropaymobilesdkdemoapp.signup;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;

import com.corduro.corduropaymobilesdkdemoapp.MainActivity;
import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.ICorduroPayMobileCallback;
import com.corduro.paymobilesdk.utils.RequestStatus;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class CorduroCreateAccountActivity extends Activity implements ICorduroPayMobileCallback {

	//textboxes
	private EditText usernameTextBox = null;
	private EditText passwordTextBox = null;
	private EditText pinTextBox = null;
	private EditText firstNameTextBox = null;
	private EditText lastNameTextBox = null;
	private EditText phoneNumberTextBox = null;
	private EditText emailTextBox = null;

	private ProgressBar progressBar = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_corduro_create_account);

		progressBar = getProgressBarView();
	}

	/*
		This function will be called when the user clicks the create account button
	 */
	public void onClickCreateAccountButton(View view){
		corduroPayMobileController.signUp(
				getApplicationName(),
				getApplicationVersion(),
				this,
				"",
				getPin(),
				"",
				getPassword(),
				getEmail(),
				getLastName(),
				getUserName(),
				"",
				"",
				"",
				getPhoneNumber(),
				"",
				getFirstName()
		);

		showProgressBar();
	}

	/*
		This function will be called when the user clicks the create account button
	 */
	public void onClickCancelButton(View view){
		goBackToMainActivity();
	}

	@Override
	public void onRequestComplete(RequestStatus requestStatus) {
		hideProgressBar();
		showToast(requestStatus);

		if(requestWasSuccessful(requestStatus)) {
			//we logged in successfully so we go back to the main activity
			goBackToMainActivity();

		} else {
			// Perhaps the user left a field blank or entered a password that was too short, so we stay on this screen and let the user try again
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

	public String getUserName(){
		usernameTextBox = getUserNameTextBoxView();
		return usernameTextBox.getText().toString();
	}

	public String getPassword(){
		passwordTextBox = getPasswordTextBoxView();
		return passwordTextBox.getText().toString();
	}

	public String getPin(){
		pinTextBox = getPinTextBoxView();
		return pinTextBox.getText().toString();
	}

	public String getFirstName(){
		firstNameTextBox = getFirstNameTextBoxView();
		return firstNameTextBox.getText().toString();
	}

	public String getLastName(){
		lastNameTextBox = getLastNameTextBoxView();
		return lastNameTextBox.getText().toString();
	}

	public String getPhoneNumber(){
		phoneNumberTextBox = getPhoneNumberTextBoxView();
		return phoneNumberTextBox.getText().toString();
	}

	public String getEmail(){
		emailTextBox = getEmailTextBoxView();
		return emailTextBox.getText().toString();
	}

	public ProgressBar getProgressBarView(){
		return (ProgressBar) findViewById(R.id.progress_bar_create_account_activity);
	}

	private void showProgressBar(){
		progressBar.setVisibility(View.VISIBLE);
	}

	private void hideProgressBar(){
		progressBar.setVisibility(View.GONE);
	}

	public EditText getUserNameTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_user_name_text_box);
	}

	public EditText getPasswordTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_password_text_box);
	}

	public EditText getPinTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_pin_text_box);
	}

	public EditText getFirstNameTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_first_name_text_box);
	}

	public EditText getLastNameTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_last_name_text_box);
	}

	public EditText getPhoneNumberTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_phone_number_text_box);
	}

	public EditText getEmailTextBoxView(){
		return (EditText) findViewById(R.id.create_account_activity_email_text_box);
	}

	private String getApplicationName(){
		return getResources().getString(R.string.app_name);
	}

	private String getApplicationVersion(){
		return getResources().getString(R.string.application_version);
	}
}
