Note: this did not work well for me on Windows for some reason, but I was able to do this easily on Ubuntu with no issue.

The AWS website will let you access the logging, but it is really not very easy to search at all. 

I am still unclear actually as to how to use their search bar, but I could be remembering incorrectly. 

I did discover that I can use the aws cli pretty easily and that, the command for fetching a large number of logs may take a little while to complete but it is well worth it because I can search the logs with ``grep -rn``

So first you gotta find your ``log-group-name``. This is basically you naming the lambda or other entity that made these logs.


Do this to just spew out all the log group names:
```
aws logs get-log-group-fields --log-group-name
```

You can easily find the one you want if you named it well.

I like to use this if I remember part of a log group name but not the whole thing:
```
aws logs describe-log-groups | grep "thePartIRemember"
```

