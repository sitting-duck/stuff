package com.corduro.corduropaymobilesdkdemoapp.wallet;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TextView;

import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.paymobilesdk.representations.wallet.CorduroWallet;
import com.corduro.paymobilesdk.representations.wallet.CorduroWalletItem;
import com.corduro.paymobilesdk.utils.CorduroDEBUG;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class DisplayWalletItemDetailActivity extends Activity {

	private final String TAG = "DisplayWalletItemDetailActivity";

	private CorduroWalletItem mWalletItem = null;

	private TableLayout tableLayout = null;

	private TextView creditCardNumberTextView = null;

	private TextView bankAccountNumberTextView = null;

	private TextView typeTextView = null;

	private TextView billingAddress1TextView = null;

	private TextView billingAddress2TextView = null;

	private TextView billingCityTextView = null;

	private TextView billingCountryTextView = null;

	private TextView billingPostalCodeTextView = null;

	private TextView billingStateTextView = null;

	private Button editCardButton = null;

	private Button editBankAccountButton = null;

	private CorduroWallet mWallet = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		try{
			mWallet = corduroPayMobileController.getWallet();
		}
		catch(Exception e){
			CorduroDEBUG.log(TAG, "ERROR: " + e.getMessage());
			showToast(e.getMessage());
		}
		mWalletItem = mWallet.get(getWalletItemPosition());

		setContentView();

	}

	private void setEditWalletItemButtonOnClickListener(){

		if(mWalletItem.isCard()){

			editCardButton.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View view) {
					Intent goToEditCardActivity = new Intent(view.getContext(), EditCardActivity.class);
					goToEditCardActivity.putExtra("WALLET_ITEM", mWalletItem);
					startActivity(goToEditCardActivity);
				}

			});

		}else if(mWalletItem.isBankAccount()){

			editBankAccountButton.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View view) {
					Intent goToEditBankAccountActivity = new Intent(view.getContext(), EditBankAccountActivity.class);
					goToEditBankAccountActivity.putExtra("WALLET_ITEM", mWalletItem);
					startActivity(goToEditBankAccountActivity);
				}

			});

		}else{

			goBackToWallet();

		}
	}

	private void displayWalletItemData(){
		if(mWalletItem.isCard()){

			displayCreditCardNumber(mWalletItem);

		}else if(mWalletItem.isBankAccount()){

			displayBankAccountNumber(mWalletItem);

		}else{
			showToast(getErrorString());
			goBackToWallet();
		}
	}

	private void displayEditWalletItemButton(){
		if(mWalletItem.isCard()){

			displayEditCardButton();

		}else if(mWalletItem.isBankAccount()){

			displayEditBankAccountButton();

		}else{
			showToast(getErrorString());
			goBackToWallet();
		}
	}

	private void displayCreditCardNumber(CorduroWalletItem walletItem){

		String creditCardNumber;
		creditCardNumberTextView = new TextView(this);
		setLayoutParams(creditCardNumberTextView);
		try{
			creditCardNumber = walletItem.getCardNumber();
			creditCardNumberTextView.setText("Credit Card Number: " + creditCardNumber);
			tableLayout.addView(creditCardNumberTextView);
		}catch(Exception exception){
			displayError(creditCardNumberTextView);
		}
	}

	private void displayEditCardButton(){
		editCardButton = new Button(this);
		setLayoutParams(editCardButton);
		setEditCardButtonText();
		tableLayout.addView(editCardButton);
	}


	private void displayBankAccountNumber(CorduroWalletItem walletItem){

		String bankAccountNumber;
		bankAccountNumberTextView = new TextView(this);
		setLayoutParams(bankAccountNumberTextView);
		try{
			bankAccountNumber = walletItem.getBankAccountNumber();
			bankAccountNumberTextView.setText("Bank Account Number" + bankAccountNumber);
			tableLayout.addView(bankAccountNumberTextView);
		}catch(Exception exception){
			displayError(bankAccountNumberTextView);
		}
	}

	private void displayEditBankAccountButton(){
		editBankAccountButton = new Button(this);
		setLayoutParams(editBankAccountButton);
		setEditBankAccountButtonText();
		tableLayout.addView(editBankAccountButton);
	}

	private void displayType(CorduroWalletItem walletItem){
		typeTextView = new TextView(this);
		setLayoutParams(typeTextView);
		typeTextView.setText("Type: " + walletItem.type);
		tableLayout.addView(typeTextView);
	}

	private void displayBillingAddress(CorduroWalletItem walletItem){

		billingAddress1TextView = new TextView(this);
		setLayoutParams(billingAddress1TextView);
		billingAddress1TextView.setText(walletItem.billingAddress1);
		tableLayout.addView(billingAddress1TextView);

		billingAddress2TextView = new TextView(this);
		setLayoutParams(billingAddress2TextView);
		billingAddress2TextView.setText(walletItem.billingAddress2);
		tableLayout.addView(billingAddress2TextView);

		billingCountryTextView = new TextView(this);
		setLayoutParams(billingCountryTextView);
		billingCountryTextView.setText(walletItem.billingCountry);
		tableLayout.addView(billingCountryTextView);

		billingCityTextView = new TextView(this);
		setLayoutParams(billingCityTextView);
		billingCityTextView.setText(walletItem.billingCity);
		tableLayout.addView(billingCityTextView);

		billingStateTextView = new TextView(this);
		setLayoutParams(billingStateTextView);
		billingStateTextView.setText(walletItem.billingState);
		tableLayout.addView(billingStateTextView);

		billingPostalCodeTextView = new TextView(this);
		setLayoutParams(billingPostalCodeTextView);
		billingPostalCodeTextView.setText(walletItem.billingPostalCode);
		tableLayout.addView(billingPostalCodeTextView);

	}

	private int getWalletItemPosition(){
		return getIntent().getExtras().getInt("WALLET_ITEM_POSITION");
	}

	private void displayError(TextView textView){
		textView.setText(getErrorString());
	}

	private String getErrorString(){
		return getString(R.string.error);
	}

	private void showToast(String message){
		CommonUtils.showToast(getApplicationContext(), message);
	}

	private void goBackToWallet(){
		Intent goBackToDisplayWalletActivity = new Intent(this, DisplayWalletActivity.class);
		startActivity(goBackToDisplayWalletActivity);
	}

	private void setContentView() {
		setContentView(R.layout.activity_display_wallet_item_detail);

		tableLayout = getLayout();

		displayWalletItemData();

		displayType(mWalletItem);

		displayBillingAddress(mWalletItem);

		displayEditWalletItemButton();

		setEditWalletItemButtonOnClickListener();
	}

	private TableLayout getLayout(){
		return (TableLayout) findViewById(R.id.display_wallet_item_detail_table_layout);
	}

	private void setLayoutParams(TextView textView){
		textView.setLayoutParams(new TableLayout.LayoutParams(TableLayout.LayoutParams.WRAP_CONTENT, TableLayout.LayoutParams.WRAP_CONTENT));
	}

	private void setLayoutParams(Button button){
		button.setLayoutParams(new TableLayout.LayoutParams(TableLayout.LayoutParams.WRAP_CONTENT, TableLayout.LayoutParams.WRAP_CONTENT));
	}

	private String getEditCardButtonString(){
		return getResources().getString(R.string.edit_card_button_text);
	}

	private String getEditBankAccountButtonString(){
		return getResources().getString(R.string.edit_bank_account_button_text);
	}

	private void setEditCardButtonText(){
		editCardButton.setText(getEditCardButtonString());
	}

	private void setEditBankAccountButtonText(){
		editBankAccountButton.setText(getEditBankAccountButtonString());
	}
}
