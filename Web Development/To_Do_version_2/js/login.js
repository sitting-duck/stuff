$(document).ready (function () {

	//set up node module dependencies
	var express = require('express');
	var mysql   = require('mysql');

	/*
		callback when 'sign in' button is clicked
	*/
	$('#sign_in_button').on('click', function (event) {					
		
		//prevents the url from getting mangled because this button is technically a link
		event.preventDefault();
		
		//get the username and password from the page
		var username = $('#user_name_input').val();				
		var password = $('#password_input').val();	

		//construct sql query to see if that user name and password are valid
		
		
		return;
	
		//prevents the url from getting mangled because this button is technically a link
		event.preventDefault();
	
		var input_field = $('#input_field');
	
		//grab the text from the to do input field
		var to_do_item_text = input_field.val();
		
		//we do not add empty items to the list
		if(to_do_item_text === ""){
			
			return;
		
		}

		//reset the input field to be empty so user can enter next item
		input_field.val("");
		
		//generate to do item number
		var item_number = callCount();					
		
		//construct the list item
		//var list_item = "<div>" +
		//"<li class='list_item'>" + to_do_item_text +
		//"<a href='#' class='x_button' id='" + item_number + "'>X</a>" + "</li>" +
		//"</div>";
		var list_item = 
		'<li class="list_item">' + '<div id="div_list_item">' + to_do_item_text + '   ' +
		'<a href="#" class="x_button" id="' + item_number + '">X</a></div></li>';			
		
		console.log(list_item);
	
		//append the item to the list
		$('#the_list').append(list_item);				

	});

});