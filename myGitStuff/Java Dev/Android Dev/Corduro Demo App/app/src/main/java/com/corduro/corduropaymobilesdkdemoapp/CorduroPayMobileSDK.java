package com.corduro.corduropaymobilesdkdemoapp;

public class CorduroPayMobileSDK {

	//This is the handle to the CorduroPaymbile SDK and its API methods.  You're going to use this CorduroPayMobileSDK object to make your payments.
	//You'll see that this attr is public and static so that your activities can access this handle easily.  However, there are other ways to go about this.
	//Putting it in a class like this that can be imported anywhere you like is merely convenient.
	//One thing you should NOT do is instantiate a NEW instance of the CorduroPayMobileSDK controller object in all of your activities that use it.
	//If you did that you would have to connect each new controller to the Corduro server which would waste a lot of time and space.
	//You may find it more practical in your implementation to pass it as an extra in your intents or store it a global data cache of some sort if you like.
	public static com.corduro.paymobilesdk.CorduroPayMobile corduroPayMobileController = null;

}
