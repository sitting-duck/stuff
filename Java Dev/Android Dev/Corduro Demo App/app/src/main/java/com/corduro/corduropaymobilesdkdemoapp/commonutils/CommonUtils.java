package com.corduro.corduropaymobilesdkdemoapp.commonutils;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.widget.Toast;

import com.corduro.corduropaymobilesdkdemoapp.CorduroPayMobileSDK;
import com.corduro.paymobilesdk.CorduroPayMobile;
import com.corduro.paymobilesdk.utils.RequestStatus;

public class CommonUtils extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	public static void showToast(Context aContext, String message){
		Context context = aContext;
		CharSequence text = message;
		int duration = Toast.LENGTH_SHORT;
		Toast toast = Toast.makeText(context, text, duration);
		toast.show();
	}

	public static CorduroPayMobile getCorduroPayMobileController(){
		return CorduroPayMobileSDK.corduroPayMobileController;
	}
}
