package com.corduro.corduropaymobilesdkdemoapp.wallet;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;

import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.ICorduroPayMobileCallback;
import com.corduro.paymobilesdk.representations.wallet.CorduroWalletItem;
import com.corduro.paymobilesdk.utils.CorduroDEBUG;
import com.corduro.paymobilesdk.utils.RequestStatus;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class EditCardActivity extends AppCompatActivity implements ICorduroPayMobileCallback {

    public static final String TAG = "EditCardActivity";

    private CorduroWalletItem mWalletItem = null;

    private ProgressBar progressBar = null;
    private EditText aliasField = null;

    private EditText nameOnCardField = null;

    private EditText cardNumberField = null;

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
        mWalletItem = getWalletItem();
        setContentView();

    }

    private CorduroWalletItem getWalletItem() {
        return getIntent().getParcelableExtra("WALLET_ITEM");
    }

    /*
		This function is called when the user clicks the add card button
	 */
    public void onClickEditCardButtonInEditCardActivity(View view){

        try {

            corduroPayMobileController.updateCreditCardWalletItem( getCardNumber(),
                                                                    getBillingPostalCode(),
                                                                    getWalletItemId(),
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

    public String getWalletItemId(){
        Intent intentThatStartedThisActivity = getIntent();
        return intentThatStartedThisActivity.getStringExtra("WALLET_ID");
    }

    public void goBackToWalletActivity(){

        Intent goBackToWalletActivity = new Intent(this, DisplayWalletActivity.class);
        startActivity(goBackToWalletActivity);
    }

    public void setContentView(){

        setContentView(R.layout.activity_edit_card);

        progressBar = getProgressBarView();

        aliasField = getAliasView();
        aliasField.setText(mWalletItem.name);

        try{

            nameOnCardField = getNameOnCardView();
            nameOnCardField.setText(mWalletItem.getNameOnCard());

            cardNumberField = getCardNumberView();
            cardNumberField.setText(mWalletItem.getCardNumber());

            expiredMonthField = getExpiredMonthView();
            expiredMonthField.setText(mWalletItem.getExpirationMonth());

            expiredYearField = getExpiredYearView();
            expiredYearField.setText(mWalletItem.getExpirationYear2Digits());

        }
        catch(Exception e){

            showToast(e.getMessage());
            CorduroDEBUG.log("ERROR: " + e.getMessage());

        }

        billingFirstNameField = getBillingFirstNameView();
        billingFirstNameField.setText(mWalletItem.getBillingFirstName());

        billingLastNameField = getBillingLastNameView();
        billingLastNameField.setText(mWalletItem.getBillingLastName());

        billingAddress1Field = getBillingAddress1View();
        billingAddress1Field.setText(mWalletItem.getBillingAddress1());

        billingAddress2Field = getBillingAddress2View();
        billingAddress2Field.setText(mWalletItem.getBillingAddress2());

        billingCityField = getBillingCityView();
        billingCityField.setText(mWalletItem.getBillingCity());

        billingStateField = getBillingStateView();
        billingStateField.setText(mWalletItem.getBillingState());

        billingCountryField = getBillingCountryView();
        billingCountryField.setText(mWalletItem.getBillingCountry());

        billingPostalCodeField = getBillingPostalCodeView();
        billingPostalCodeField.setText(mWalletItem.getBillingPostalCode());

    }

    private EditText getAliasView(){
        return (EditText) findViewById(R.id.alias_field_edit_card_activity);
    }

    private String getAlias(){
        return aliasField.getText().toString();
    }

    private EditText getNameOnCardView(){
        return (EditText) findViewById(R.id.name_on_card_field_edit_card_activity);
    }

    private String getNameOnCard(){
        return nameOnCardField.getText().toString();
    }

    private EditText getCardNumberView(){
        return (EditText) findViewById(R.id.card_number_field_edit_card_activity);
    }

    private String getCardNumber(){
        return cardNumberField.getText().toString();
    }

    private EditText getExpiredMonthView(){
        return (EditText) findViewById(R.id.expired_month_field_edit_card_activity);
    }

    private String getExpiredMonth(){
        return expiredMonthField.getText().toString();
    }

    private EditText getExpiredYearView(){
        return (EditText) findViewById(R.id.expired_year_field_edit_card_activity);
    }

    private String getExpiredYear(){
        return expiredYearField.getText().toString();
    }

    private EditText getBillingFirstNameView(){
        return (EditText) findViewById(R.id.billing_first_name_field_edit_card_activity);
    }

    private String getBillingFirstName(){
        return billingFirstNameField.getText().toString();
    }

    private EditText getBillingLastNameView(){
        return (EditText) findViewById(R.id.billing_last_name_field_edit_card_activity);
    }

    private String getBillingLastName(){
        return billingLastNameField.getText().toString();
    }

    private EditText getBillingAddress1View(){
        return (EditText) findViewById(R.id.billing_address_1_field_edit_card_activity);
    }

    private String getBillingAddress1(){
        return billingAddress1Field.getText().toString();
    }

    private EditText getBillingAddress2View(){
        return (EditText) findViewById(R.id.billing_address_2_field_edit_card_activity);
    }

    private String getBillingAddress2(){
        return billingAddress2Field.getText().toString();
    }

    private EditText getBillingCityView(){
        return (EditText) findViewById(R.id.billing_city_field_edit_card_activity);
    }

    private String getBillingCity(){
        return billingCityField.getText().toString();
    }

    private EditText getBillingStateView(){
        return (EditText) findViewById(R.id.billing_state_field_edit_card_activity);
    }

    private String getBillingState(){
        return billingStateField.getText().toString();
    }

    private EditText getBillingCountryView(){
        return (EditText) findViewById(R.id.billing_country_field_edit_card_activity);
    }

    private String getBillingCountry(){
        return billingCountryField.getText().toString();
    }

    private EditText getBillingPostalCodeView(){
        return (EditText) findViewById(R.id.billing_postal_code_field_edit_card_activity);
    }

    private String getBillingPostalCode(){
        return billingPostalCodeField.getText().toString();
    }

    public ProgressBar getProgressBarView(){
        return (ProgressBar) findViewById(R.id.progress_bar_edit_card_activity);
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
