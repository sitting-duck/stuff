$(document).ready (function () {

	/*
		callback when add button is clicked. Add button adds a to do to the list
	*/
	$('#add_button').on('click', function (event) {			
	
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
	
	/*
		callback when x button is clicked. X button removes the corresponding item from the list
	*/
	$('#list_container').on('click', '.x_button', function (event) {		

		//prevents the url from getting mangled because this button is technically a link
		event.preventDefault();		
		
		//remove the corresponding list item from the list
		this.closest('.list_item').remove();
		
		/*
			extracts the number from the id string
		*/
		function getNumberFromId(id_string){
		
			return /d+/.test(id_string);
		
		}
	
	
	});
	
	/*
			incremental counter. Used to id to do items as they are made 
		*/
		function callCount () {
			callCount.count = ++callCount.count || 1;
			return callCount.count;
		}

});
