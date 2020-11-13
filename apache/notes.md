install the zip from apachelounge.com/downloads, 

rename the dir to apache and put it in the root dir of the c drive, 
change Apache24 to apace in the conf file in the conf dir, and set serverName to be localhost:80
you'll have to uncomment that line, 

you can run it as a windows service by doing
open cmd as an admin, 
```
cd C:\apache\bin
httpd -k install
```

it will run as a service now. If there are any errors in your config file though, you need to fix those first, 

