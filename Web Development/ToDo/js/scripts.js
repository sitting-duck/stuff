$(document).ready (function () {

	//callback when add button is clicked
	$('#add_button').on('click', function (event) {		
	
		//grab the text from the to do input field
		var to_do_item_text = $('#input_field').val();

		//clear the input field
		$('#input_field')[0].reset();
		
		//construct the list item
		var list_item = "<div>" +
		"<li>" + to_do_item_text +
		"<a href='#' class='button' id='x_button'>X</a>" + "</li>" +
		"</div>";
	
		//append the item to the list
		$('#list').append(list_item);


	});

});
