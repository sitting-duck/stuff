package com.corduro.corduropaymobilesdkdemoapp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.corduropaymobilesdkdemoapp.login.CorduroLoginActivity;
import com.corduro.corduropaymobilesdkdemoapp.wallet.DisplayWalletActivity;
import com.corduro.paymobilesdk.CorduroPayMobile;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

//these are the activities that will be launched after the user taps a button
//the Corduro Paymobile API functions are contained within this class.


public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		//You MUST call connect before the CorduroPayMobileSDK controller can be used. Since this is the main activity, the onCreate activity for the main activity of your app is an
		//appropriate place to do this. The reason for this is that certain security steps are taken during this connection phase that must be done before any other CorduroPayMobile
		//features can be used.
		corduroPayMobileController = CorduroPayMobile.connect();
	}

	/*
		This function will be called when the user clicks the login button
	 */
	public void onClickLoginButton(View view){

		//Since the user has clicked the login button, the Corduro login activity is launched and the user is taken to the Login screen.
		//You can see the code for the login activity in CorduroLoginActivity.java
		Intent corduroLoginActivity = new Intent(this, CorduroLoginActivity.class);
		startActivity(corduroLoginActivity);
	}

	 /*
		This function will be called when the user clicks the logout button
	 */
	public void onClickLogoutButton(View view){
		corduroPayMobileController.logout();
		showToast(getLogoutMessage());
	}

	 /*
		This function will be called when the user clicks the wallet features button
	 */
	public void onClickWalletFeaturesButton(View view){

		//Since the user has clicked the wallet features button, the Corduro Wallet Activity is launched and the user is taken to a screen where they can add, view
		//and edit their own personal wallet items such as bank accounts and credit cards.
		if(corduroPayMobileController.isCurrentSessionLoggedIn()) {

			//if an attempt is made to load a wallet for a session, unless the user is logged in, loadWallet will throw an exception
			//This makes sense because a wallet is always attached to a user.
			// Attempting to call loadWallet when there is no user logged in does not make sense
			Intent corduroDisplayWalletActivity = new Intent(this, DisplayWalletActivity.class);
			startActivity(corduroDisplayWalletActivity);
		}else{
			//instead of letting your app crash when an exception is thrown, you could perhaps warn your users before even calling the function that they
			//have not logged in
			showToast( getPleaseLoginToViewWalletMessage() );
		}
	}

	public void showToast(String toastString){
		CommonUtils.showToast(getApplicationContext(), toastString);
	}

	public String getPleaseLoginToViewWalletMessage(){
		return getResources().getString(R.string.please_login_to_view_wallet_prompt);
	}

	public String getLogoutMessage(){
		return getResources().getString(R.string.logout_message);
	}
}
