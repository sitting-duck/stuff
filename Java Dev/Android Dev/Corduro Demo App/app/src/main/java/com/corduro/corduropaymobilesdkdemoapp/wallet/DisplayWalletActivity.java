package com.corduro.corduropaymobilesdkdemoapp.wallet;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.ProgressBar;

import com.corduro.corduropaymobilesdkdemoapp.R;
import com.corduro.corduropaymobilesdkdemoapp.commonutils.CommonUtils;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.ICorduroPayMobileCallback;
import com.corduro.paymobilesdk.representations.wallet.CorduroWallet;
import com.corduro.paymobilesdk.representations.wallet.CorduroWalletItem;
import com.corduro.paymobilesdk.utils.CorduroDEBUG;
import com.corduro.paymobilesdk.utils.RequestStatus;

import java.util.ArrayList;

import static com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK.corduroPayMobileController;

public class DisplayWalletActivity extends Activity implements ICorduroPayMobileCallback, AdapterView.OnItemClickListener{

	private final static String TAG = "DisplayWalletActivity";

	//progress spinner
	private ProgressBar spinner = null;

	CorduroWallet mWallet = null;

	ArrayList<String> walletItemNames;

	ArrayAdapter<String> walletItemArrayAdapter = null;

	ListView walletItemListView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_corduro_wallet);

		spinner = getSpinnerView();

		//we are going to display to the user a list of wallet items to the user so let's grab those items from the Corduro server
		CorduroDEBUG.log(TAG, TAG + "::onCreate(): corduroPayMobileController: " + corduroPayMobileController);

		try{
			corduroPayMobileController.loadWallet(this);
		}catch(Exception e){
			CorduroDEBUG.log(TAG, "ERROR: " + e.getMessage(), e);
		}

		showProgressSpinner();
	}

	@Override
	public void onRequestComplete(RequestStatus requestStatus) {
		CorduroDEBUG.log(TAG, TAG + "::onRequestComplete()");
		hideProgressSpinner();

		if(requestWasSuccessful(requestStatus)) {

			//get the list of wallet items from the Corduro server
			try{
				mWallet = corduroPayMobileController.getWallet();
			}
			catch(Exception e){
				CorduroDEBUG.log(TAG, "ERROR: " + e.getMessage());
			}


			//get the names for each wallet item, we will display a list of names and the user can click on a wallet item to see details
			walletItemNames = getWalletItemNamesFromWalletItems(mWallet);
			walletItemArrayAdapter = createAdapterFromArrayList(walletItemNames);
			walletItemListView = getWalletItemListView();
			walletItemListView.setAdapter(walletItemArrayAdapter);

			//when the user taps a wallet item in the list, the onItemClick function defined in this file will be called
			walletItemListView.setOnItemClickListener(this);

		} else {

			showToast(requestStatus);

		}
	}

	/*
		This function will be called when the user clicks a wallet item
	 */
	@Override
	public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
		//we're going to launch a new page to look at the details for that wallet item and pass the wallet item with the intent
		Intent goToWalletItemDetailView = new Intent(this, DisplayWalletItemDetailActivity.class);

		//store the wallet item position so we can get it on the other side
		goToWalletItemDetailView.putExtra("WALLET_ITEM_POSITION", position);
		goToWalletItemDetailView.putExtra("WALLET", mWallet);

		//let's go
		startActivity(goToWalletItemDetailView);

	}

	/*
		This function will be called when the user click on the add card button
	 */
	public void onClickAddCardButtonInDisplayWalletActivity(View view){
		hideProgressSpinner();
		Intent goToAddCardActivity = new Intent(this, AddCardActivity.class);
		startActivity(goToAddCardActivity);
	}

	/*
		This function will be called when the user click on the add bank account button
	 */
	public void onClickAddBankAccountButtonInDisplayWalletActivity(View view){
		hideProgressSpinner();
		Intent goToAddBankAccountActivity = new Intent(this, AddBankAccountActivity.class);
		startActivity(goToAddBankAccountActivity);
	}

	public ProgressBar getSpinnerView(){
		return (ProgressBar) findViewById(R.id.progress_bar_wallet_activity);
	}

	private void showProgressSpinner(){
		spinner.setVisibility(View.VISIBLE);
	}

	private void hideProgressSpinner(){
		spinner.setVisibility(View.GONE);
	}

	private boolean requestWasSuccessful(RequestStatus requestStatus){
		return CorduroPayMobile.requestWasSuccessful(requestStatus);
	}

	private void showToast(RequestStatus requestStatus){
		CommonUtils.showToast(getApplicationContext(), requestStatus.msg);
	}

	private ArrayAdapter<String> createAdapterFromArrayList(ArrayList<String> listOfStrings){
		return new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, listOfStrings);
	}

	private ListView getWalletItemListView(){
		return (ListView) findViewById(R.id.wallet_item_list_view);
	}

	public ArrayList<String> getWalletItemNamesFromWalletItems(CorduroWallet wallet){
		ArrayList<String> tempWalletItemNames = new ArrayList<String>();

		for(int i = 0; i < wallet.length(); i++){
			tempWalletItemNames.add(wallet.get(i).name);
		}

		return tempWalletItemNames;
	}
}
