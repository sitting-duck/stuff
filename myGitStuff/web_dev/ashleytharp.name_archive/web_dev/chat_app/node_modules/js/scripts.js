$(document).ready(function () {
	
	var random_name_string = getRandomString();

	var span_element = '<span>' + random_name_string + '</span>';
	
	//put the heading on the page (your name: dsfgsdkj)
	$('#your_name_heading').append(span_element);
	
	//grab the chat box for later use
	var chat_box = $('#text_box');
	
	//insert "connecting" prompt into the text area
	chat_box.val('connecting to localhost:3000...');
	
		
	/*
		for generating a random string
	*/
	function getRandomString(){
	
		var text = "";
		var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		
		for(var i = 0; i < 5; i++){
			
			text += possible.charAt(Math.floor(Math.random() * possible.length));
			
		}
		
		return text;
	
	}

});