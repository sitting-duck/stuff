### Learning Stuff about NGINX

```
server {
    root /www/data;

    location / {
    }

    location /images/ {
    }

    location ~ \.(mp3|mp4) {
        root /www/media;
    }
}
```

Okay. This is saying that NGINX will search for uris that start with images, in the /www/data/images dir in the file system. 

So we see at the top that /www/data is the root. 
We can see that there are two locations, the root dir, and the images dir. 

If the uri ends with the .mp3 or .mp4 extension (remember that all we're doing here is serving stuff, and the uri is just a request for some stuff to be served)

So like, get this, the uri comes in, and there are 3 choices here, if the uri starts with images, we can start searching in one location, if the uri starts with nothing (I suppose?) we can start searching in the root dir, and if it ends with mp3 or mp4 extension then we can start searching in media. 


```
location / {
    root /data;
    index index.html index.php;
}

location ~ \.php {
    fastcgi_pass localhost:8000;
    #...
}
```
Let's say the uri starts with /. We start looking for index, can't find it, index.htlm, can't find it, and then index.php. We finally do find this one. Now we do an internal redirect. Look at that second location. The internal redirect to /path/index.php is mapped to the second location. As a result, the request is proxied. 

```
server {
    root /www/data;

    location /images/ {
        try_files $uri /images/default.gif;
    }
}
```
Ok so we check to see if the file exists in images, and if it doesn't we return default.gif, which is probably a picture of some dumb mascot shrugging.
That $uri refers to the uri requested. 



