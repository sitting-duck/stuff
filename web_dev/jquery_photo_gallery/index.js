
// gt means: Select all elements at an index greater than index within the matched set.
// so here it appears we are hiding all the elements inside the slideshow.
$("#slideshow > div:gt(0)").hide();


// It seems to be the case that each of these function calls returns 
// the jquery object, which contains the entire DOM.
setInterval(function() {
  $('#slideshow > div:first')
  	.hide()
    .fadeOut(1000)
    .next()
    .fadeIn(1000)
    .end()
    .appendTo('#slideshow');
}, 1000);