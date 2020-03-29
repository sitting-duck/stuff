You would write something like this if for example you were writing client side code for an Android application that took mobile payments. 

The server would return some credit card data from the server, and some regex would be used to extract, the expiration date for example from that data. 

Since we are dealing with text, there are all sorts of ways the data could come back wrong, so the regex extraction has to take that into account. 

Tests like this ensure that the Regex properly works. Each time a new failure scenario is discovered a test is written for that case.

wrote this little test to make sure that my regex was good for extracting the expiration date info from credit info returned from the server, more details later.  
(Obviously, this is not actual data, credit card number etc. are all fake)

