$(document).ready(function () {
		
	
	//function for when the click me button is clicked.  (when clicked it will append the hex color input form to the document)
	$(#click_me_button).on('click', function (event) {
	
		//prevents the url from adding '#' at the end
		event.preventDefault
		
		//first create the hex color input field
		$(document.body).append("test");
	
	});
	
	//function for when the go button is clicked on the hex color input form
	$('#go_button').on ('click', function (event) {

		//prevents the url from adding '#' at the end
		event.preventDefault ();

		//create red and green hello and world words and put them in the span 
		//inside the inner-div-hello-world
		var red = '<i>hello </i>',
			green = '<i>world</i>',
			$hw = $('#inner-div-hello-world span');
		
		$(red)
			.css ('color', '#FF0000')
			.css ('font-style', 'normal')
			.appendTo ($hw);
		
		$(green)
			.css ('color', '#00FF00')
			.css ('font-style', 'normal')
			.appendTo ($hw);
			
			
		//grab the hex color string input field
		$hex_field = $('#hex_color_string_input_field');
		
		//get the string from the hex color input field
		var hex_color_string = $hex_field.val();
		
		var hex_string_was_valid = isValidHexColorString(hex_color_string);		
		
		if(hex_string_was_valid){

			//todo: add feature where if user forgets '#' char it will still work
			$(document.body).css("background-color", hex_color_string);
			
		}
		
	});
	
});

function isValidHexColorString(inputString){

	//todo: test this regex for all hex values
	return /(^#[0-9A-F]{6}$)|(^#[0-9A-F]{3}$)/i.test(inputString);
	
}

function getStyleSheet(){

	//at the moment there is only one style sheet
	return document.stylesheets[0];

}