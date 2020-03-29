package com.corduro.corduropaymobilesdkdemoapp.wallet;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;

import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.ICorduroPayMobileCallback;
import com.corduro.paymobilesdk.utils.CorduroDEBUG;
import com.corduro.paymobilesdk.utils.RequestStatus;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class AddCardActivity extends Activity implements ICorduroPayMobileCallback {

	public static final String TAG = "AddCardActivity";

	private ProgressBar progressBar = null;

	private EditText aliasField = null;

	private EditText nameOnCardField = null;

	private EditText cardNumberField = null;

	private EditText cvvField = null;

	private EditText expiredMonthField = null;

	private EditText expiredYearField = null;

	private EditText billingFirstNameField = null;

	private EditText billingLastNameField = null;

	private EditText billingAddress1Field = null;

	private EditText billingAddress2Field = null;

	private EditText billingCityField = null;

	private EditText billingStateField = null;

	private EditText billingCountryField = null;

	private EditText billingPostalCodeField = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView();
	}

	/*
		This function is called when the user clicks the add card button
	 */
	public void onClickAddCardButtonInAddCardActivity(View view){

		try {
			corduroPayMobileController.addCardToWallet( getCardNumber(),
														getBillingPostalCode(),
														getCvv(),
														getExpiredMonth(),
														getAlias(),
														getExpiredYear(),
														getNameOnCard(),
														getBillingFirstName(),
														getBillingLastName(),
														getBillingAddress1(),
														getBillingAddress2(),
														getBillingCity(),
														getBillingState(),
														getBillingCountry(),
														getBillingPostalCode(),
														this);

														showProgressBar();

		} catch (Exception e) {
			CorduroDEBUG.log(TAG, e.getMessage(), e);
			showToast(e.getMessage());
		}

	}

	@Override
	public void onRequestComplete(RequestStatus requestStatus) {

		hideProgressBar();

		showToast(requestStatus.msg);

		if(requestWasSuccessful(requestStatus)) {

			//we added a new card successfully so we go back to the main activity
			goBackToWalletActivity();

		}
	}

	public void goBackToWalletActivity(){

		Intent goBackToWalletActivity = new Intent(this, DisplayWalletActivity.class);
		startActivity(goBackToWalletActivity);
	}

	private void setContentView(){
		setContentView(R.layout.activity_add_card);

		progressBar = getProgressBarView();

		aliasField = getAliasView();
		nameOnCardField = getNameOnCardView();
		cardNumberField = getCardNumberView();
		cvvField = getCvvView();
		expiredMonthField = getExpiredMonthView();
		expiredYearField = getExpiredYearView();
		billingFirstNameField = getBillingFirstNameView();
		billingLastNameField = getBillingLastNameView();
		billingAddress1Field = getBillingAddress1View();
		billingAddress2Field = getBillingAddress2View();
		billingCityField = getBillingCityView();
		billingStateField = getBillingStateView();
		billingCountryField = getBillingCountryView();
		billingPostalCodeField = getBillingPostalCodeView();
	}

	private EditText getAliasView(){
		return (EditText) findViewById(R.id.alias_field_add_add_bank_account_activity);
	}

	private String getAlias(){
		return aliasField.getText().toString();
	}

	private EditText getNameOnCardView(){
		return (EditText) findViewById(R.id.name_on_card_field_add_card_activity);
	}

	private String getNameOnCard(){
		return nameOnCardField.getText().toString();
	}

	private EditText getCardNumberView(){
		return (EditText) findViewById(R.id.card_number_field_add_card_activity);
	}

	private String getCardNumber(){
		return cardNumberField.getText().toString();
	}

	private EditText getCvvView(){
		return (EditText) findViewById(R.id.cvv_field_add_card_activity);
	}

	private String getCvv(){
		return cvvField.getText().toString();
	}

	private EditText getExpiredMonthView(){
		return (EditText) findViewById(R.id.expired_month_field_add_card_activity);
	}

	private String getExpiredMonth(){
		return expiredMonthField.getText().toString();
	}

	private EditText getExpiredYearView(){
		return (EditText) findViewById(R.id.expired_year_field_add_card_activity);
	}

	private String getExpiredYear(){
		return expiredYearField.getText().toString();
	}

	private EditText getBillingFirstNameView(){
		return (EditText) findViewById(R.id.billing_first_name_field_add_card_activity);
	}

	private String getBillingFirstName(){
		return billingFirstNameField.getText().toString();
	}

	private EditText getBillingLastNameView(){
		return (EditText) findViewById(R.id.billing_last_name_field_add_card_activity);
	}

	private String getBillingLastName(){
		return billingLastNameField.getText().toString();
	}

	private EditText getBillingAddress1View(){
		return (EditText) findViewById(R.id.billing_address_1_field_add_card_activity);
	}

	private String getBillingAddress1(){
		return billingAddress1Field.getText().toString();
	}

	private EditText getBillingAddress2View(){
		return (EditText) findViewById(R.id.billing_address_2_field_add_card_activity);
	}

	private String getBillingAddress2(){
		return billingAddress2Field.getText().toString();
	}

	private EditText getBillingCityView(){
		return (EditText) findViewById(R.id.billing_city_field_add_card_activity);
	}

	private String getBillingCity(){
		return billingCityField.getText().toString();
	}

	private EditText getBillingStateView(){
		return (EditText) findViewById(R.id.billing_state_field_add_card_activity);
	}

	private String getBillingState(){
		return billingStateField.getText().toString();
	}

	private EditText getBillingCountryView(){
		return (EditText) findViewById(R.id.billing_country_field_add_card_activity);
	}

	private String getBillingCountry(){
		return billingCountryField.getText().toString();
	}

	private EditText getBillingPostalCodeView(){
		return (EditText) findViewById(R.id.billing_postal_code_field_add_card_activity);
	}

	private String getBillingPostalCode(){
		return billingPostalCodeField.getText().toString();
	}

	public ProgressBar getProgressBarView(){
		return (ProgressBar) findViewById(R.id.progress_bar_add_card_activity);
	}

	private void showProgressBar(){
		progressBar.setVisibility(View.VISIBLE);
	}

	private void hideProgressBar(){

		runOnUiThread(new Runnable() {
			@Override
			public void run() {

				try {

					progressBar.setVisibility(View.GONE);

				} catch (Exception e) {
					Log.e(TAG, "ERROR: ", e);
				}

			}
		});

	}

	private void showToast(String string){
		CommonUtils.showToast(getApplicationContext(), string);
	}

	private boolean requestWasSuccessful(RequestStatus requestStatus){
		return CorduroPayMobile.requestWasSuccessful(requestStatus);
	}


}
