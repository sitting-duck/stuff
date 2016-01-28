$.fn.insertForm = function () {

	//the hex color input field and its button that we are going to toggle the attachment of
	var hex_color_html = '<input type="text" class="hex_color_input" id="hex_color_string_input_field">',
		hex_go_btn_html = '<a href="#" class="button_type" id="go_button">go</a>',
		click_btn = '<a href="#" class="button_type" id="click_me_button">Click Me</a>';
	
	function isValidHexColorString(inputString){

		//todo: test this regex for all hex values
		return /(^#[0-9A-F]{6}$)|(^#[0-9A-F]{3}$)/i.test(inputString);
		
	}

	function toggle () {
		return isOdd (callCount ());
	}

	/* this is magic that allows us to have a static count variable */
	function callCount () {
		callCount.count = ++callCount.count || 1;
		return callCount.count;
	}

	/* this is so we can toggle attachment of the form on and off */
	function isOdd (number) {
		return number % 2 == 1;
	}
	
	// function for when the go button is clicked on the hex color input form
	var onGoBtnClicked = function (event, $container) {
		//prevents the url from adding '#' at the end
		event.preventDefault ();
		
		//grab the hex color string input field
		$hex_field = $container.find('#hex_color_string_input_field');
		
		//get the string from the hex color input field
		var hex_color_string = $hex_field.val();
		
		var hex_string_was_valid = isValidHexColorString(hex_color_string);		
		
		if (hex_string_was_valid) {

			//todo: add feature where if user forgets '#' char it will still work
			$('body').css("background-color", hex_color_string);
			
		}
	};
	
	//function for when the click me button is clicked.  (when clicked it will append the hex color input form to the document)
	var onClickMeClicked = function (event, $container) {
		//prevents the url from adding '#' at the end
		event.preventDefault();		
	
		//the click me button toggles attachment of form on and off
		if (toggle ()) {
			$container.append (hex_color_html);						
			$(hex_go_btn_html)
				.on ('click', function (event) {
					onGoBtnClicked (event, $container);
				})
				.appendTo ($container);
		
		} else {
			$container.find("#hex_color_string_input_field").remove();
			$container.find("#go_button").remove();
		
		}
	};
	
	
	this.each (function () {
		var $container = $(this);
		
		// insert the clickme into my container
		$(click_btn)
			.on ('click', function (event) {
				onClickMeClicked (event, $container)
			})
			.appendTo (this);
	});
}